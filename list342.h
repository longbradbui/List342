#ifndef LIST_342_H_
#define LIST_342_H_
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* CONTRACT DECLARATION */

template <class T>
struct Node
{
    T *data;    // A pointer to the data value
    Node *next; //  A pointer to the next Node
};

template <class T>
class List342
{
    friend ostream &operator<<(ostream &outstream, const List342<T> &rhs_list)
    {
        if (rhs_list.head_ptr_ == nullptr)
        {
            cerr << "This is an empty list";
        }
        Node<T> *current = rhs_list.head_ptr_;
        while (current != nullptr)
        {
            T temp = *(current->data);
            outstream << temp;
            current = current->next;
        }
        return outstream;
    }

public:
    List342();                              // Default Constructor
    List342(string file_name);              // Parameterized Contructor: Read from file
    List342(const List342<T> &parent_list); // Copy Contructor
    ~List342();                             // Default Destructor
    bool BuildList(string file_name);
    bool Insert(T *obj);
    bool Remove(T target, T &result);
    bool Peek(T target, T &result) const;
    bool Merge(List342<T> &list1);
    void DeleteList();
    int Size() const;
    bool operator==(const List342<T> &rhs_list) const;      //  Equality comparison
    bool operator!=(const List342<T> &rhs_list) const;      //  Inequality comparison
    List342<T> &operator=(const List342<T> &rhs_list);      //  Performs Deep Copy of two sorted lists
    List342<T> &operator+=(const List342<T> &rhs_list);     //  Returns a reference to the lhs list (sorted)
    List342<T> operator+(const List342<T> &rhs_list) const; //  Returns a new list (sorted)
    template <class U>
    friend ostream &operator<<(ostream &outstream, const List342<T> &rhs_list);
    template <class U>
    friend istream &operator>>(istream &instream, List342<T> &rhs_list);

private:
    Node<T> *head_ptr_;
};
#endif

/* CONSTRUCTOR IMPLEMENTATION */

template <class T>
List342<T>::List342()
{
    this->head_ptr_ = nullptr;
}

template <class T>
List342<T>::List342(const List342<T> &parent_list)
{
    this->head_ptr_ = nullptr;
    *(this) = parent_list;
}

template <class T>
List342<T>::List342(string file_name)
{
    BuildList(file_name);
};

template <class T>
List342<T>::~List342()
{
    this->DeleteList();
}

/* ACTION IMPLEMENTATION */

template <class T>
int List342<T>::Size() const
{
    int size = 0;
    Node<T> *current_node = head_ptr_;
    while (current_node != nullptr)
    {
        size++;
        current_node = current_node->next;
    }
    return size;
}

template <class T>
bool List342<T>::BuildList(string file_name)
{
    if (file_name.size() <= 0)
    {
        return false;
    }
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file.is_open())
    {
        return false;
    }
    T temp;
    while (!in_file.eof())
    {
        in_file >> temp;
        Insert(&temp);
    }
    return true;
}

template <class T>
bool List342<T>::Insert(T *obj)
{
    // Object passed is pointing to null reference
    if (obj == nullptr)
    {
        cerr << "Cannot insert NULL data, please try again." << endl;
        return false;
    }
    // Empty List
    if (head_ptr_ == nullptr)
    {
        head_ptr_ = new Node<T>();
        head_ptr_->data = new T(*(obj));
        head_ptr_->next = nullptr;
        return true;
    }
    // First in Line
    if (*(head_ptr_->data) > *(obj))
    {
        Node<T> *insert_node = new Node<T>();
        insert_node->data = new T(*(obj));
        insert_node->next = head_ptr_;
        head_ptr_ = insert_node;
        return true;
    }
    // Check for duplication at beginning
    if (*(head_ptr_->data) == *(obj))
    {
        return false;
    }
    // All others
    Node<T> *current_node = head_ptr_;
    while ((current_node->next != nullptr) && (*(current_node->next->data) < *(obj)))
    {
        current_node = current_node->next;
    }
    // Check for duplicates
    if ((current_node->next != nullptr) && (*(current_node->next->data) == *(obj)))
    {
        return false;
    }
    // Insert new node somewhere in between
    Node<T> *insert_node = new Node<T>();
    insert_node->data = new T(*(obj));
    insert_node->next = current_node->next;
    current_node->next = insert_node;
    return true;
}

template <class T>
bool List342<T>::Remove(T target, T &result)
{
    // Empty List
    if (head_ptr_ == nullptr)
    {
        cerr << "List in empty, please try again." << endl;
        return false;
    }
    // First in line
    if (*(head_ptr_->data) == (target))
    {
        Node<T> *temporary = head_ptr_;
        head_ptr_ = head_ptr_->next;
        result = *(temporary->data);
        delete temporary->data;
        delete temporary;
        return true;
    }
    // All others
    Node<T> *current_node = head_ptr_;
    // Continuously move towards the end of the list
    while ((current_node->next != nullptr) && (*(current_node->next->data) < (target)))
    {
        current_node = current_node->next;
    }
    // If traversing till nullptr but have not found the target
    if ((current_node->next == nullptr) || (*(current_node->next->data) != (target)))
    {
        cerr << "Cannot find the item in the list, please try again." << endl;
        return false;
    }
    // Remove somewhere in between
    Node<T> *temp = current_node->next;
    current_node->next = current_node->next->next;
    result = *(temp->data);
    delete temp->data;
    delete temp;
    return true;
}

template <class T>
bool List342<T>::Merge(List342 &list1)
{
    // If the two lists are empty
    if ((this->head_ptr_ == nullptr) && (list1.head_ptr_ == nullptr))
    {
        cerr << "Cannot merge two empty lists, please try again." << endl;
        return false;
    }
    // Empty list1 passed in
    if ((list1.head_ptr_ == nullptr))
    {
        cerr << "Cannot merge with an empty list, please try again." << endl;
        return false;
    }
    // Same address
    if ((this == &list1))
    {
        cerr << "Two lists have the same address, please try again." << endl;
        return false;
    }
    // If the calling list is empty
    if ((list1.head_ptr_ != nullptr) && (this->head_ptr_ == nullptr))
    {
        this->head_ptr_ = list1.head_ptr_;
        list1.head_ptr_ = nullptr;
        return true;
    }
    // Declare auxiliary pointers
    Node<T> *destination = this->head_ptr_;
    Node<T> *source = list1.head_ptr_;
    Node<T> *previous_node = nullptr;
    while ((destination != nullptr) && (source != nullptr))
    {
        // If node from list1 is greater than node from the calling list
        if (*(source->data) > *(destination->data))
        {
            previous_node = destination;
            destination = destination->next;
        }
        // If node from list1 is smaller than node from the calling list
        else if (*(source->data) < *(destination->data))
        {
            // Append at the beginning of the calling list
            if (previous_node == nullptr)
            {
                list1.head_ptr_ = source->next;
                source->next = this->head_ptr_;
                this->head_ptr_ = source;
                source = list1.head_ptr_;
            }
            // Append somewhere in between previous node and current node of lhs list
            else
            {
                previous_node->next = source;
                source = source->next;
                previous_node->next->next = destination;
                previous_node = previous_node->next;
            }
        }
        // If found duplicate values
        else
        {
            Node<T> *duplicate_node = source;
            source = source->next;
            delete duplicate_node->data;
            delete duplicate_node;
        }
    }
    // Attach remaining nodes from source to the end of destination
    if (source != nullptr)
    {
        if (previous_node == nullptr)
        {
            // If the lhs list is empty, update the head pointer of lhs
            this->head_ptr_ = list1.head_ptr_;
        }
        else
        {
            // Otherwise, attach the remaining nodes from rhs to the end of lhs
            previous_node->next = source;
        }
        // Empty rhs list
        list1.head_ptr_ = nullptr;
    }
    return true;
}

template <class T>
bool List342<T>::Peek(T target, T &result) const
{
    // Empty List
    if (head_ptr_ == nullptr)
    {
        return false;
    }
    // First in line
    if (*(head_ptr_->data) == (target))
    {
        result = *(head_ptr_->data);
        return true;
    }
    // All others
    Node<T> *current_node = head_ptr_;
    while (current_node != nullptr)
    {
        if (*(current_node->data) == (target))
        {
            result = *(current_node->data);
            return true;
        }
        else
        {
            current_node = current_node->next;
        }
    }
    return false;
}

template <class T>
void List342<T>::DeleteList()
{
    // Continuously delete data and node itself
    Node<T> *current_node = head_ptr_;
    while (current_node != nullptr)
    {
        Node<T> *next_node = current_node->next;
        delete current_node->data; // Deallocate the data
        delete current_node;       // Deallocate the node
        current_node = next_node;
    }
    head_ptr_ = nullptr;
}

template <class T>
bool List342<T>::operator==(const List342<T> &rhs_list) const
{
    Node<T> *lhs_node = this->head_ptr_;
    Node<T> *rhs_node = rhs_list.head_ptr_;
    while ((lhs_node != nullptr) && (rhs_node != nullptr))
    {
        if (*(lhs_node->data) != *(rhs_node->data))
        {
            return false;
            break;
        }
        else
        {
            lhs_node = lhs_node->next;
            rhs_node = rhs_node->next;
        }
    }
    return true;
}

template <class T>
bool List342<T>::operator!=(const List342<T> &rhs_list) const
{
    return !(*this == rhs_list);
}

template <class T>
List342<T> &List342<T>::operator=(const List342<T> &rhs_list)
{
    // If rhs list is empty or they both pointing to the same address
    if ((this == &rhs_list) || (rhs_list.head_ptr_ == nullptr))
    {
        return *this;
    }
    // Empty Destination
    this->DeleteList();
    // Perform deep copy
    Node<T> *source = rhs_list.head_ptr_;
    Node<T> *destination;
    // Copy over the first node
    destination = new Node<T>();
    destination->data = new T(*(rhs_list.head_ptr_->data));
    this->head_ptr_ = destination;
    source = rhs_list.head_ptr_->next;
    // Loop and copy over
    while (source != nullptr)
    {
        destination->next = new Node<T>();
        destination = destination->next;
        destination->data = new T(*(source->data));
        source = source->next;
    }
    return *this;
}

template <class T>
List342<T> &List342<T>::operator+=(const List342<T> &rhs_list)
{
    if ((this == &rhs_list) || (rhs_list.head_ptr_ == nullptr))
    {
        return *this;
    }
    if ((this->head_ptr_ == nullptr) && (rhs_list.head_ptr_ != nullptr))
    {
        *(this) = rhs_list;
        return *this;
    }
    if ((this->head_ptr_ == nullptr) && (rhs_list.head_ptr_ == nullptr))
    {
        return *this;
    }
    Node<T> *source = rhs_list.head_ptr_;
    Node<T> *destination = this->head_ptr_;
    // Copy over the first node
    if (*(destination->data) > *(source->data))
    {
        this->head_ptr_ = new Node<T>();
        head_ptr_->data = new T(*(source->data));
        head_ptr_->next = destination;
        destination = head_ptr_;
        source = source->next;
    }
    // Loop and copy over
    while ((source != nullptr) && (destination->next) != nullptr)
    {
        if (*(source->data) == *(destination->next->data))
        {
            source = source->next;
        }
        else if (*(source->data) < *(destination->next->data))
        {
            Node<T> *insert_node = new Node<T>();
            insert_node->data = new T(*(source->data));
            insert_node->next = destination->next;
            destination->next = insert_node;
            source = source->next;
        }
        else
        {
            destination = destination->next;
        }
    }
    // If destitnation becomes empty while source is not
    if (destination->next == nullptr)
    {
        while (source != nullptr)
        {
            destination->next = new Node<T>();
            destination = destination->next;
            destination->data = new T(*(source->data));
            source = source->next;
        }
    }
    return *this;
}

template <class T>
List342<T> List342<T>::operator+(const List342<T> &rhs_list) const
{
    List342<T> result = *(this);
    result += rhs_list;
    return result;
}
