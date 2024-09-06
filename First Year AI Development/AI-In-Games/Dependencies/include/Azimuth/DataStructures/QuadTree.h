#pragma once

#include "QuadTreeNode.h"

template<typename DATA>
class QuadTree
{
public:
	QuadTree(const Rectangle& _bounds);
	~QuadTree();

	void Insert(QuadTreeData<DATA>* _data);
	void Remove(QuadTreeData<DATA>* _data);
	void Update(QuadTreeData<DATA>* _data);

	void Draw();

	vector< QuadTreeData<DATA>*> Query(const Rectangle& _area);

private:
	QuadTreeNode<DATA>* m_root;
};

template<typename DATA>
inline QuadTree<DATA>::QuadTree(const Rectangle& _bounds)
{
	m_root = new QuadTreeNode<DATA>(_bounds);
}

template<typename DATA>
inline QuadTree<DATA>::~QuadTree()
{
	if (m_root != nullptr)
	{
		delete m_root;
		m_root = nullptr;
	}
}

template<typename DATA>
inline void QuadTree<DATA>::Insert(QuadTreeData<DATA>* _data)
{
	if (m_root != nullptr)
		m_root->Insert(_data);
}

template<typename DATA>
inline void QuadTree<DATA>::Remove(QuadTreeData<DATA>* _data)
{
	if (m_root != nullptr)
		m_root->Remove(_data);
}

template<typename DATA>
inline void QuadTree<DATA>::Update(QuadTreeData<DATA>* _data)
{
	if (m_root != nullptr)
		m_root->Update(_data);
}

template<typename DATA>
inline void QuadTree<DATA>::Draw()
{
	if (m_root != nullptr)
		m_root->Draw();
}

template<typename DATA>
inline vector<QuadTreeData<DATA>*> QuadTree<DATA>::Query(const Rectangle& _area)
{
	vector<QuadTreeData<DATA>*> data;
	if (m_root != nullptr)
		data = m_root->Query(_area);

	return data;
}
