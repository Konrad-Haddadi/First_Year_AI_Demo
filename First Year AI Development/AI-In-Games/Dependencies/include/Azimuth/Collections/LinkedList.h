#pragma once

#include <initializer_list>
#include <iostream>
#include <string>

using std::string;
using std::initializer_list;

template<class T>
class LinkedList
{
public:
    struct Node
    {
    public:
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& _value) : value(_value) {}
    };


    struct Iterator
    {
    public:
        Node* node;

    public:
        Iterator() : node(nullptr) {}
        Iterator(Node* _node) : node(_node) {}

        Iterator& Next()
        {
            if (node != nullptr)
                node = node->next;

            return *this;
        }

        Iterator& Prev()
        {
            if (node != nullptr)
                node = node->prev;

            return*this;
        }       

    public:
        // Increment / Decrement operators
        Iterator& operator++() { return Next(); }
        Iterator& operator--() { return Prev(); }

        // Equality operators

        bool operator==(const Iterator& _rhs) { return node == _rhs.node; }
        bool operator!=(const Iterator& _rhs) { return node != _rhs.node; }

        // Iterator getters
        Iterator& operator+(const int _shiftAmount)
        {
            Iterator iter = *this;

            for (int i = 0; i < _shiftAmount; i++)
            {
                // Check if ended
                if (iter.Next() == nullptr)
                    return End();
                else
                    iter = iter.Next();
            }
            return iter;
        }

        Iterator& operator-(const int _shiftAmount)
        {
            Iterator iter = *this;

            for (int i = 0; i < _shiftAmount; i++)
            {
                // check if we are outside the bounds of the list
                if (iter.Prev() = nullptr)
                    return Begin();
                else
                    iter = iter.Prev();
            }
            return iter;
        }

        // Dereference Operators

        T& operator*() { return node->value; }
        T* operator->() { return &node->value; }
    };

public:
    LinkedList() = default;
    
    LinkedList(initializer_list<T> _list)
    {
        for (auto iter = _list.begin(); iter != _list.end(); iter++)
            PushBack((*iter));
    }    

    ~LinkedList() = default;

    void PushBack(T _value)
    {
        Node* node = new Node(_value);
        node->next = nullptr;
        node->prev = nullptr;
        m_count++;

        if (IsEmpty())
        {
            m_first = node;
            m_last = node;
        }
        else
        {
            m_last->next = node;
            node->prev = m_last;
            m_last = node;
        }
    }

    void PopBack()
    {
        if (IsEmpty())
            return;

        Node* last = m_last;

        m_last = m_last->prev;

        delete last;
        last = nullptr;

        m_count--;
    }

    void PushFront(T _value)
    {
        Node* node = new Node(_value);
        node->next = nullptr;
        node->prev = nullptr;
        m_count++;

        if (IsEmpty())
        {
            m_first = node;
        }
        else
        {
            m_first->prev = node;
            node->next = m_first;
            m_first = node;
        }

    }

    void PopFront()
    {
        if (IsEmpty())
            return;

        Node* first = m_first;

        m_first = m_first->next;
        
        delete first;
        first = nullptr;

        m_count--;
    }

    void Clear()
    {
        if (IsEmpty())
            return;

        for (int i = m_count; i > 0; i--)
            PopBack();

        m_count = 0;
    }

    Iterator Remove(Iterator _iter)
    {
        if (IsEmpty())
             return nullptr; 

        if (_iter.node->prev != nullptr)
            _iter.node->prev->next = _iter.node->next;
        else
            m_first = _iter.node->next;

        if(_iter.node->next != nullptr)
            _iter.node->next->prev = _iter.node->prev;
        else
            m_last = _iter.node->prev;
        
        if (_iter.node->next != nullptr)
        {
            Node iter = *_iter.node->next;
            delete _iter.node;
            _iter.node = &iter;
        }
        else
        {
            delete _iter.node;
            _iter.node = nullptr;
        }

        m_count--;
        return _iter;
    }   

    Iterator RemoveAt(const int _index)
    {
        return Remove(Find(At(_index)));
    }

    // Find the first iterator / node that constains this value
    Iterator Find(T _value)
    {
        if (IsEmpty())
            return Iterator{};

        for (Iterator iter = Begin(); iter != End(); ++iter)
        {
            if (iter.node->value == _value)
                return iter;            
        }

       return End();
    }    

    // inster the value at this iterator
    void Insert(Iterator _iter, const T& _value)
    {
        Node* node = _iter.node;
        Node* next = node->next;
        Node* prev = node->prev;

        Node* value = new Node(_value);       

        value->prev = node;
        value->next = next;
        next->prev = value;
        node->next = value;

        m_count++;
    }

    // retunr the value at this index
    T& At(const int _index)
    {
        if (_index > m_count)
        {
            return (T&)m_first->value;
        }

        Node* node = m_first;

        for (int i = 0; i < _index; i++)
        {
            node = node->next;            
        }
        return (T&)node->value;
    }

    // check if any node contain this value
    bool Contains(const T& _value)
    {
        if (Find(_value) != Iterator{})
            return true;

        return false;        
    }
    

    void Sort(int(*_comparer)(Iterator, Iterator))
    {        
        T temp;

        for (Iterator iter1 = Begin(); iter1 != End(); ++iter1)
        {           
            for (Iterator iter2 = Begin(); iter2 != End(); ++iter2)
            {
                if (_comparer(iter1, iter2) >= 1)
                {
                    temp = iter1.node->value;
                    iter1.node->value = iter2.node->value;
                    iter2.node->value = temp;
                }               
            }             
        }
    }

    // find the index of this value, otherwise return -1
    int IndexOf(const T& _value)
    {
        int num = 1;

        for (Iterator iter = Begin(); iter != End(); ++iter)
        {
            if (iter.node->value == _value)
                return num;
         
            num++;
        }

        return -1;
    }

    // Is this list completly empty
    bool IsEmpty()
    {    
        if (m_first == nullptr && m_last == nullptr)
            return true;          

        return false;
    }

    //Amount of items in the list
    unsigned int Count() { return m_count; }

    Node* FirstNode() { return m_first; }
    Node* LastNode() { return m_last; }

    Iterator Begin() { return Iterator(m_first); }
    Iterator Back() { return Iterator(m_last); }
    Iterator End() { return Iterator(); }
protected:

private:
    Node* m_first = nullptr;
    Node* m_last = nullptr;
    int m_count;

};