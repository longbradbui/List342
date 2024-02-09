#ifndef LIST_342_H_
#define LIST_342_H_
#include <iostream>
#include <vector>
using namespace std;

/* CONTRACT DECLARATION */
/* Node Struct */
template<class T>
struct Node
{
	T* data;     // A pointer to the data value
	Node* next; //  A pointer to the next Node 
}; 

/* List342 Class */
template <class T>
class List342
{
public:
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
	Node<T>* head_ptr_;
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


