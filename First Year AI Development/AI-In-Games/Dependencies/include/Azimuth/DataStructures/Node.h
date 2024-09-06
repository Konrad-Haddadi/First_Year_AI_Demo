#pragma once

#include "Azimuth/Azimuth.h"
#include <raylib/raylib.h>
#include "Azimuth/Collections/LinkedList.h"
#include <string>

using std::string;

template<typename T>
class TreeNode
{
public:
	TreeNode(T* _value, string _id);

	~TreeNode();

	void SetData(T _value);
	void SetID(string _id);
	void SetParent(TreeNode<T>* _val);

	void AddChild(T* _node, string _id);
	void RemoveChild(string _id);


	// Keeps children of child removed
	void RemoveChildEx(string _id);

	void ClearChildren();
	int ChildCount() { return m_children.Count(); }

	bool HasChildren() { return !m_children.IsEmpty(); }

	string GetID() { return m_id; }
	T GetData() { return *m_value; }
	T* GetRef() { return m_value; }

	TreeNode<T>* GetChild(string _id);

	TreeNode<T>* GetChildAt(int _num);
	TreeNode<T>* GetParent() { return m_parent; }
	LinkedList<TreeNode<T>*> GetChildren() { return m_children; }



private:
	// this could also be a pointer to another object if you like	
	T* m_value;
	string m_id;
	TreeNode<T>* m_parent;

	// _node's children
	LinkedList<TreeNode<T>*> m_children;
};

template<typename T>
inline TreeNode<T>::TreeNode(T* _value, string _id)
	: m_value(_value), m_id(_id)
{
}

template<typename T>
inline TreeNode<T>::~TreeNode()
{
	ClearChildren();
}

template<typename T>
inline void TreeNode<T>::SetData(T _value)
{
	*m_value = _value;
}

template<typename T>
inline void TreeNode<T>::SetParent(TreeNode<T>* _val)
{
	if (m_parent != nullptr)
	{
		m_parent->RemoveChild(GetID());
		m_parent = _val;
	}
	else
		m_parent = _val;

}

template<typename T>
inline void TreeNode<T>::SetID(string _id)
{
	m_id = _id;
}

template<typename T>
inline void TreeNode<T>::AddChild(T* _val, string _id)
{
	TreeNode<T>* node = new TreeNode(_val, _id);
	m_children.PushBack(node);
	node->SetParent(this);
}


template<typename T>
inline void TreeNode<T>::RemoveChild(string _id)
{
	if (GetChild(_id) != nullptr)
	{
		if (GetChild(_id)->HasChildren())
		{
			for (int i = 0; i < GetChild(_id)->GetChildren().Count(); i++)
			{
				m_children.PushBack(m_children.At(i));
			}
		}
		m_children.Remove(m_children.Find(GetChild(_id)));
	}

}

template<typename T>
inline TreeNode<T>* TreeNode<T>::GetChildAt(int _num)
{
	if (m_children.IsEmpty())
		return nullptr;

	else if (_num < 0 || _num > m_children.Count())
		return nullptr;
	else
		return m_children.At(_num);
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::GetChild(string _id)
{
	for (auto iter = m_children.Begin(); iter != m_children.End(); ++iter)
	{
		if (dynamic_cast<TreeNode<T>*>(*iter)->GetID() == _id)
			return dynamic_cast<TreeNode<T>*>(*iter);
	}

	return nullptr;
}


template<typename T>
inline void TreeNode<T>::ClearChildren()
{
	for (int i = m_children.Count() - 1; i >= 0; i--)
	{
		RemoveChild(m_children.At(i)->GetID());
	}
}