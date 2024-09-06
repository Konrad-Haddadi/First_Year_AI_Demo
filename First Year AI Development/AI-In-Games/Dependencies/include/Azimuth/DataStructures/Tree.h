#pragma once

#include "Node.h"

#include <Azimuth/Azimuth.h>
#include <string>



using std::string;

template<typename T>
class Tree
{
public:
	Tree() : m_root(nullptr) {}
	Tree(T* _val, string _id) { SetRoot(new TreeNode<T>(_val, _id)); }
	~Tree();

	bool IsEmpty() { return (m_root == nullptr); }
	void InsertAt(TreeNode<T>* _at, T _val, string _id);
	void InsertAt(string _at, T _val, string _id);
	void Remove(T _val);
	void Remove(string _id);
	void RemoveBranch(T _val);
	void RemoveBranch(string _id);

	int GetCount() { return m_count; }
	void SetRoot(TreeNode<T>* _val);
	void SetRoot(T _val, string _id);
	void SetRootID(string _id);
	void SetRootData(T _val);

	TreeNode<T>* GetRoot() { return m_root; }
	TreeNode<T>* Find(T _val);
	TreeNode<T>* Find(string _id);
	TreeNode<T>* FindAt(TreeNode<T>* _parent, T _val);
	TreeNode<T>* FindAt(TreeNode<T>* _parent, string _id);

private:
	TreeNode<T>* m_root;
	int m_count;

};

template<typename T>
inline Tree<T>::~Tree()
{
	while (m_root != nullptr)
		Remove(m_root->GetData());
}

template<typename T>
inline TreeNode<T>* Tree<T>::Find(T _val)
{
	return FindAt(m_root, _val);
}

template<typename T>
inline TreeNode<T>* Tree<T>::FindAt(TreeNode<T>* _node, T _val)
{
	if (IsEmpty())
		return nullptr;

	if (_node->GetData() == _val)
		return _node;
	else
	{
		for (int i = 0; i < _node->ChildCount(); i++)
		{
			return FindAt(_node->GetChildAt(i), _val);
		}
		return nullptr;
	}
}

// using string 
// _________________________________________________________________________
template<typename T>
inline TreeNode<T>* Tree<T>::Find(string _id)
{
	return FindAt(m_root, _id);
}

template<typename T>
inline TreeNode<T>* Tree<T>::FindAt(TreeNode<T>* _node, string _id)
{
	if (IsEmpty())
		return nullptr;

	if (_node->GetID() == _id)
		return _node;
	else
	{
		for (int i = 0; i < _node->ChildCount(); i++)
		{
			if(FindAt(_node->GetChildAt(i), _id) != nullptr)
				return FindAt(_node->GetChildAt(i), _id);
		}
		return nullptr;
	}
}
// _________________________________________________________________________

template<typename T>
inline void Tree<T>::SetRootID(string _id)
{
	if (m_root == nullptr)
		return;
	else
		m_root->SetData(_id);
}

template<typename T>
inline void Tree<T>::SetRootData(T _val)
{
	if (m_root == nullptr)
		return;
	else
		m_root->SetData(_val);
}

template<typename T>
inline void Tree<T>::SetRoot(TreeNode<T>* _val)
{
	if (m_root == nullptr)
		m_root = _val;
	else
		m_root = _val;
}

template<typename T>
inline void Tree<T>::SetRoot(T _val, string _id)
{
	m_root->SetData(_val);
	m_root->SetID(_id);		
}

template<typename T>
inline void Tree<T>::InsertAt(TreeNode<T>* _at, T _val, string _id)
{
	if (Find(_at) == nullptr)
		return;
	else if (IsEmpty())
	{
		SetRoot(_val, _id);
		return;
	}
	else
		Find(_at->GetID())->AddChild(_val, _id);

	m_count++;
}

template<typename T>
inline void Tree<T>::InsertAt(string _at, T _val, string _id)
{
	if (Find(_at) == nullptr)
		return;
	else if (IsEmpty())
	{
		SetRoot(_val, _id);
		return;
	}
	else
		Find(_at)->AddChild(&_val,_id);

	m_count++;
}

template<typename T>
inline void Tree<T>::Remove(T _val)
{
	if (Find(_val) == nullptr)
		return;

	if (m_root->GetData() == _val)
		m_root = nullptr;
	else
	{
		TreeNode<T>* node = Find(_val);

		for (int i = 0; i < node->ChildCount(); i++)
		{
			node->GetParent()->GetChildren().PushBack(node->GetChildAt(i));
		}

		delete node;
		node = nullptr;
	}
}

template<typename T>
inline void Tree<T>::Remove(string _id)
{
	if (Find(_id) == nullptr)
		return;

	if (m_root->GetID() == _id)
		m_root = nullptr;		
	else
	{
		TreeNode<T>* node = Find(_id);

		for (int i = 0; i < node->ChildCount(); i++)
		{
			node->GetParent()->GetChildren().PushBack(node->GetChildAt(i));
		}	

		delete node;
		node = nullptr;
	}
}

template<typename T>
inline void Tree<T>::RemoveBranch(T _val)
{
	if (Find(_val) == nullptr)
		return;

	if (*m_root->GetData() == _val)
	{
		for (int i = 1; i <= m_root->ChildCount(); i++)
		{
			m_root->RemoveChild(m_root->GetChild(i));
		}
		
		delete m_root;
		m_root = nullptr;
	}
	else
	{
		TreeNode<T>* node = Find(_val);

		for (int i = 1; i <= node->ChildCount(); i++)
		{
			node->RemoveChild(node->GetChild(i));
		}

		delete node;
		node = nullptr;		
	}
}

template<typename T>
inline void Tree<T>::RemoveBranch(string _id)
{
	if (Find(_id) == nullptr)
		return;

	if (m_root->GetID() == _id)
	{
		for (int i = 1; i <= m_root->ChildCount(); i++)
		{
			m_root->RemoveChild(m_root->GetChild(i));
		}

		delete m_root;
		m_root = nullptr;
	}  
	else
	{
		TreeNode<T>* node = Find(_id);

		for (int i = 1; i <= node->ChildCount(); i++)
		{
			node->RemoveChild(node->GetChild(i));
		}

		delete node;
		node = nullptr;
	}
}