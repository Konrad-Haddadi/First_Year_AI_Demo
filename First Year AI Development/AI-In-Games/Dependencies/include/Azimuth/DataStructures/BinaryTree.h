#pragma once

#include "Azimuth/Azimuth.h"

class BinaryNode;

class BinaryTree
{
public:
	DLL BinaryTree();
	DLL ~BinaryTree();
	
	DLL bool IsEmpty();
	DLL void Insert(int _value);
	DLL void Remove(int _value);

	DLL BinaryNode* Find(int _value);
	DLL int ParentCheck(int _value);

	DLL int GetCount();
	DLL BinaryNode* GetRoot() { return m_root; }

private:
	//Find the node with the specified value.
	bool FindNode(int _searchValue, BinaryNode*& _foundNode, BinaryNode*& _foundParent);

private:
	//The root node of the tree
	BinaryNode* m_root;
	int m_count;
};
