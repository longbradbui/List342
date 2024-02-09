#ifndef LIST_342_H_
#define LIST_342_H_
#include <iostream>
#include <vector>
using namespace std;

/* Node Struct */
template<class T>
struct Node
{
	T* data;
	Node* next;
}; 

/* List342 Class*/
template <class T>
class List342
{
public:
	/* CONSTRUCTOR and DESTRUCTOR */
	List342();                                  // Default Constructor
	List342(string file_name);                 //  Parameterized Contructor: Read from file
	List342(List342<T>& input_list);          //   Parameterized Constructor: Read from class
	List342(const List342<T>& parent_list);  //    Copy Contructor
	~List342();                             //     Default Destructor
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
	List342<T>& operator=(const List342<T>& rhs_list);
	bool operator==(const List342<T>& rhs_list);
	bool operator!=(const List342<T>& rhs_list);
	List342<T>& operator+=(const List342<T>& rhs_list);
	List342<T> operator+(const List342<T>& rhs_list) const;
private:
	Node<T>* head_ptr_;


};
#endif

