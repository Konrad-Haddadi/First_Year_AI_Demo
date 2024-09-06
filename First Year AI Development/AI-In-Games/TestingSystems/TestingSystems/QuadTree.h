#pragma once

#include "QuadTreeData.h"

#include <vector>
#include <queue>
#include <raylib/raymath.h>

#include <typeinfo>

using std::vector;
using std::queue;

#define QUAD_TREE_LEAFS 4

template<typename DATA>
class QuadTreeNode
{
public:
	static int maxDepth;
	static int maxObjectsPerNode;

	vector<QuadTreeNode<DATA>*> children;
	vector<QuadTreeData<DATA>*> contents;
	int currentDepth;
	Rectangle bounds;

public:
	QuadTreeNode(const Rectangle& _bounds);
	~QuadTreeNode();

	bool IsLeaf();
	int NumObjects();

	void Insert(QuadTreeData<DATA>* _data);
	void Remove(QuadTreeData<DATA>* _data);
	void Update(QuadTreeData<DATA>* _data);

	void Draw();

	vector<QuadTreeData<DATA>*> Query(const Rectangle& _area);

private:
	void Shake();
	void Split();
	void Reset();

	Vector2 GetMin(Rectangle _rect);
	Vector2 GetMax(Rectangle _rect);
	Rectangle FromMinMax(Vector2 _min, Vector2 _max);
};

template<typename DATA>
int QuadTreeNode<DATA>::maxDepth = 5;
template<typename DATA>
int QuadTreeNode<DATA>::maxObjectsPerNode = 15;

template<typename DATA>
inline QuadTreeNode<DATA>::QuadTreeNode(const Rectangle& _bounds)
	: bounds(_bounds), currentDepth(0)
{
}

template<typename DATA>
inline QuadTreeNode<DATA>::~QuadTreeNode()
{
	for (auto& child : children)
		delete child;

	for (auto& data : contents)
		delete data;

	children.clear();
	contents.clear();
}

template<typename DATA>
inline bool QuadTreeNode<DATA>::IsLeaf()
{
	return children.empty();
}

template<typename DATA>
inline int QuadTreeNode<DATA>::NumObjects()
{
	Reset();

	int objCount = contents.size();

	for (auto& data : contents)
		data->flag = true;

	queue<QuadTreeNode<DATA>*> toProcess;
	toProcess.push(this);

	while (!toProcess.empty())
	{
		// Get the item at the back of the queue
		QuadTreeNode<DATA>* processsing = toProcess.front();

		// Check processsing this node is a branch
		if (!processsing->IsLeaf())
		{
			// Add all child nodes to the queue
			for (auto& child : processsing->children)
				toProcess.push(child);
		}
		else
		{
			// This is a leaf node, so process the data and count the items
			for (auto& data : processsing->constents)
			{
				if (!data->flag)
				{
					objCount++;
					data->flag = true;
				}
			}
		}
		// Remove the currently processing node
		toProcess.pop();
	}

	// Reset all flags for safety
	Reset();
	return objCount;
}

template<typename DATA>
inline void QuadTreeNode<DATA>::Insert(QuadTreeData<DATA>* _data)
{
	// Make sure this node would actually encapsulate the data
	if (!CheckCollisionRecs(_data->bounds, bounds))
		return;

	// Of theis is a ;eaf node and adding this data would push its contents cap over the limit, split
	if (IsLeaf() && contents.size() + 1 > maxObjectsPerNode)
		Split();

	if (IsLeaf())
	{
		// This is a leaf node so it can contain the data
		contents.push_back(_data);
	}
	else
	{
		// Recursively attempt to insert data into the quad tree
		for (auto& child : children)
			child->Insert(_data);
	}
}

template<typename DATA>
inline void QuadTreeNode<DATA>::Remove(QuadTreeData<DATA>* _data)
{
	// Check if this is a leaf as only leaf's can contrains data
	if (IsLeaf())
	{
		int removeIndex = -1;

		for (int i = 0; i < contents.size(); i++)
		{
			// Is this the data we want to remove
			if (contents[i]->data == _data->data)
			{
				// It is so store the index and break out of the loop
				removeIndex = i;
				break;
			}
		}

		//Did we find the item in the list?
		if (removeIndex != -1)
		{
			// Remove it from the list
			contents.erease(contents.begin() + removeIndex);
		}
	}
	else
	{
		// We are a branch so try to remvoe from children
		for (auto& child : children)
			child->Remove(_data);
	}

	// Shake to balance the tree
	Shake();

}

template<typename DATA>
inline void QuadTreeNode<DATA>::Update(QuadTreeData<DATA>* _data)
{
	Remove(_data);
	Insert(_data);
}

template<typename DATA>
inline void QuadTreeNode<DATA>::Draw()
{
	// Drawing the node itself
	DrawRectangleLinesEx(bounds, 2.f, GREEN);

	for (auto& data : contents)
	{
		// Attempt to cast the data to a vector
		if (Vector2* vec = dynamic_cast<Vector2*>(data->data))
		{
			DrawCircleV(*vec, 5.f, PURPLE);
		}
	}

	// Draw the child nodes
	for (auto& child : children)
		child->Draw();
}

template<typename DATA>
inline vector<QuadTreeData<DATA>*> QuadTreeNode<DATA>::Query(const Rectangle& _area)
{
	vector<QuadTreeData<DATA>*> result;

	// If the area being queried isn't inside the bouds of this node return an empty vector
	if (!CheckCollisionRecs(_area, bounds))
		return result;

	if (IsLeaf())
	{
		// Check if this data is inside the desired area
		for (auto& data : contents)
		{
			if (CheckCollisionRecs(data->bounds, _area))
			{
				// add this ata to the results
				result.push_back(data);
			}
		}
	}
	else
	{
		// Quey children
		for (auto& child : children)
		{
			vector<QuadTreeData<DATA>*> childData = child->Query(_area);

			// if the children did hvae data, add it to the results
			if (childData.size() > 0)
			{
				result.insert(result.end(), childData.begin(), childData.end());
			}
		}
	}

	// Return all found data
	return result;
}


template<typename DATA>
inline void QuadTreeNode<DATA>::Shake()
{
	if (!IsLeaf())
	{
		int numObjects = NumObjects();
		if (numObjects == 0)
		{
			// We have no objects in the tree, so clear all children
			for (auto& child : children)
				delete child;

			children.clear();
		}
		else if (numObjects < maxObjectsPerNode)
		{
			queue<QuadTreeData<DATA>*> toProcess;
			toProcess.push(this);

			// iterate through all child nodes and brances
			while (!toProcess.empty())
			{
				QuadTreeNode<DATA>* processing = toProcess.font();
				if (!processing->IsLeaf())
				{
					// we are a branch, so add the children to be processed
					for (auto& child : children)
						toProcess.push(child);
				}
				else
				{
					contents.insert(contents.end(), processing->contents.begin(), processing->constents.end());
				}

				toProcess.pop();
			}

			// Remove the children from this node
			for (auto& child : children)
				delete child;

			children.clear();
		}
	}
}

template<typename DATA>
inline void QuadTreeNode<DATA>::Split()
{
	if (currentDepth + 1 >= maxDepth)
		return;

	Vector2 min = GetMin(bounds);
	Vector2 max = GetMax(bounds);

	Vector2 center = Vector2Add(min, Vector2Scale(Vector2Subtract(max, min), 0.5f));

	Rectangle childBounds[]
	{
		FromMinMax({min.x, min.y}, {center.x, center.y}),
		FromMinMax({center.x, min.y}, {max.x, center.y}),
		FromMinMax({center.x, center.y}, {max.x, max.y}),
		FromMinMax({min.x, center.y}, {center.x, max.y})
	};

	for (int i = 0; i < QUAD_TREE_LEAFS; i++)
	{
		children.push_back(new QuadTreeNode<DATA>(childBounds[i]));
		children[i]->currentDepth = currentDepth + 1;
	}

	vector<QuadTreeData<DATA>*> data = contents;

	while (data.size() > 0)
	{
		for (auto& child : children)
		{
			if (CheckCollisionRecs(child->bounds, (*data.begin())->bounds))
			{
				child->Insert(*data.begin());
				break;
			}
		}

		data.erase(data.begin());
	}

	contents.clear();
}

template<typename DATA>
inline void QuadTreeNode<DATA>::Reset()
{
	if (IsLeaf())
	{
		for (auto& data : contents)
			data->flag = false;
	}
	else
	{
		for (auto& child : children)
			child->Reset();
	}
}

template<typename DATA>
inline Vector2 QuadTreeNode<DATA>::GetMin(Rectangle _rect)
{
	return { _rect.x, _rect.y };
}

template<typename DATA>
inline Vector2 QuadTreeNode<DATA>::GetMax(Rectangle _rect)
{
	return { _rect.x + _rect.width, _rect.y + _rect.height };
}

template<typename DATA>
inline Rectangle QuadTreeNode<DATA>::FromMinMax(Vector2 _min, Vector2 _max)
{

	return { _min.x, _min.y, _max.x - _min.x, _max.y - _min.y };
}
