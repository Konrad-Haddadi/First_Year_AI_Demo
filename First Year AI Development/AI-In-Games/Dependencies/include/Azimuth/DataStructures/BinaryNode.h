#pragma once

class BinaryNode
{
public:
	BinaryNode(float _val) { m_value = _val; }
	~BinaryNode();

	void SetLeft(BinaryNode* _val) { m_left = _val; }
	void SetRight(BinaryNode* _val) { m_right = _val; }

	bool HasLeft() { return (m_left != nullptr); }
	bool HasRight() { return (m_right != nullptr); }

	BinaryNode* GetLeft() { return m_left; }
	BinaryNode* GetRight() { return m_right; }
	BinaryNode* GetParent() { return m_parent; }
	int GetData() { return m_value; }


	void SetParent(BinaryNode* _val) { m_parent = _val; }
	void SetData(float _val) { m_value = _val; }
	int ChildCount();

public:

private:
	float m_value;
	float m_childCount;
	
	BinaryNode* m_left;
	BinaryNode* m_right;
	BinaryNode* m_parent;

};