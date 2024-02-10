#ifndef LIST_342_H_
#define LIST_342_H_
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* CONTRACT DECLARATION */
/* Node Struct */



/* List342 Class */
template <class T>
class List342
{
public:
	struct Node
	{
		T* data = nullptr;     // A pointer to the data value
		Node* next = nullptr; //  A pointer to the next Node 
	};
	/* CONSTRUCTOR and DESTRUCTOR */
	List342();                                  // Default Constructor
	List342(string file_name);                 //  Parameterized Contructor: Read from file
	List342(const List342<T>& parent_list);   //   Copy Contructor
	~List342();                              //    Default Destructor
	/* ACTIONS */
	bool BuildList(string file_name);
	bool Insert(T* obj);
	bool Remove(T target, T& result);
	bool Peek(T target, T& result) const;
	bool Merge(List342<T>& list1);
	void DeleteList();
	int Size() const;
	/* OPERATOR OVERLOADING */
	friend ostream& operator<<(ostream& outstream, const List342<T> rhs_list);
	bool operator==(const List342<T>& rhs_list);                 //  Equality comparison
	bool operator!=(const List342<T>& rhs_list);                //   Inequality comparison
	List342<T>& operator=(const List342<T>& rhs_list);         //    Performs Deep Copy of two sorted lists
	List342<T>& operator+=(const List342<T>& rhs_list);       //     Returns a reference to the lhs list (sorted)
	List342<T> operator+(const List342<T>& rhs_list) const;  //      Returns a new list (sorted)
private:
	Node* head_ptr_ = nullptr;
};
#endif

/* CONSTRUCTOR IMPLEMENTATION */
template <class T>
List342<T>::List342()
{
	this->head_ptr_ = nullptr;
}

template <class T>
List342<T>::List342(const List342<T> & parent_list)
{
	this->head_ptr_ = nullptr;
	*this = parent_list;
}

template <class T>
List342<T>::List342(string file_name)
{
	BuildList(file_name);
};

template <class T>
List342<T>::~List342()
{
	DeleteList();
}

/* ACTION IMPLEMENTATION */
template <class T> 
bool List342<T>::BuildList(string file_name)
{

}

template <class T>
bool List342<T>::Insert(T* obj)
{
    // If object is pointing to null reference
    if (obj == nullptr)
    {
        return false;
    }
    // If head pointer is pointing to null reference
    if (head_ptr_ == nullptr)
    {
        head_ptr_ = new Node();
        head_ptr_->data = new T(*obj);
        return true;
    }
    // If value pointed by object is less than value pointed by head pointer
    Node* insert_node = new Node();
    insert_node->data = new T(*obj);
    if (*insert_node->data < *head_ptr_->data)
    {
        insert_node->next = head_ptr_;
        head_ptr_ = insert_node;
        return true;
    }
    // Essentially, current node is pointing to head pointer
    // and previous node is pointing to null reference
    Node* current_node = head_ptr_;
    Node* previous_node = nullptr;
    // While: current node is not pointing to null reference 
    // and value of current node is less than value of pointer object 
    while ((current_node->next != nullptr) && (*current_node->data < *insert_node->data))
    {
        previous_node = current_node; // previous node points to what current node is pointing
        current_node = current_node->next; // current node points to next node
    }// exits out the loop if one of two conditions fail
    // Check for duplication
    if (previous_node != nullptr && *previous_node->data == *insert_node->data)
    {
        delete insert_node;
        return false;
    }
    insert_node->next = current_node;
    if (previous_node != nullptr)
    {
        previous_node->next = insert_node;
    }

    return true;
}