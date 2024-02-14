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
            cerr << "Empty List" << endl;
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
    friend istream &operator<<(istream &instream, List342<T> &rhs_list);

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
    this->DeleteList();
}

/* ACTION IMPLEMENTATION */

template <class T>
int List342<T>::Size() const
{
    int size = 0;
    // Node pointer current node points to the same location with head_ptr
    Node<T> *current_node = head_ptr_;
    while (current_node != nullptr)
    {
        size++;
        current_node = current_node->next; // Continuously move towards the end of the list
    }
    return size;
}

template <class T>
bool List342<T>::BuildList(string file_name)
{
    // Open the file for reading
    ifstream my_file;
    // If the file name is empty or invalid input, print an error message then return
    if (file_name.size() <= 0)
    {
        cerr << "Invalid file name. Please try again. \n";
        return false;
    }
    my_file.open(file_name);
    // If the file cannot be opened, print an error message then return
    if (!my_file.is_open())
    {
        cerr << "File: " << file_name << " cannot be opened. Please try again.\n";
        return false;
    }
    // Instantiate a boolean flag to keep track of the status
    bool end_of_file = false;
    // Allocate memory for reading data from the file
    T *file_reader = new T;
    while (!end_of_file)
    {
        my_file >> *(file_reader);
        Insert(file_reader);
    }
    // The end of the file has been reached
    if (my_file.eof())
    {
        end_of_file = true;
        delete file_reader;
        file_reader = nullptr;
    }
    // Close the file
    my_file.close();
    return true;
}

template <class T>
bool List342<T>::Insert(T *obj)
{
    // Null object passed in
    if (obj == nullptr)
    {
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
    if (*(head_ptr_->data) >= *(obj))
    {
        Node<T> *insert_node = new Node<T>();
        insert_node->data = new T(*(obj));
        insert_node->next = head_ptr_;
        head_ptr_ = insert_node;
        return true;
    }
    // All others
    Node<T> *current_node = head_ptr_;
    while ((current_node->next != nullptr) && *(current_node->next->data) < *(obj))
    {
        current_node = current_node->next;
    }
    // Check for duplicates
    if (current_node->next != nullptr && *(current_node->next->data) == *(obj))
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
        return false;
    }
    // First in line
    if (*(head_ptr_->data) == (target))
    {
        Node<T> *temp = head_ptr_;
        head_ptr_ = head_ptr_->next;
        result = *(temp->data);
        delete temp->data;
        delete temp;
        return true;
    }
    // All others
    Node<T> *current_node = head_ptr_;
    // Continuously move towards the end of the list
    while (current_node->next != nullptr && *(current_node->next->data) < (target))
    {
        current_node = current_node->next;
    }
    // If traversing till null but have not found the target, return
    if (current_node->next == nullptr || *(current_node->next->data) != (target))
    {
        return false;
    }
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
    // Empty List, or same address
    if (this->head_ptr_ == nullptr || list1.head_ptr_ == nullptr || this == &list1)
    {
        return false;
    }
    // If the lhs list is pointing to null reference but list1 is not
    if (list1.head_ptr_ != nullptr && this->head_ptr_ == nullptr)
    {
        this->head_ptr_ = list1.head_ptr_;
        list1.head_ptr_ = nullptr;
        return true;
    }
    // Declare auxiliary pointers
    Node<T> *lhs_current_node = this->head_ptr_;
    Node<T> *rhs_current_node = list1.head_ptr_;
    Node<T> *previous_node = nullptr;
    Node<T> *duplicate_node = nullptr;
    while (lhs_current_node != nullptr && rhs_current_node != nullptr)
    {
        // If found duplicate values
        if (*(rhs_current_node->data) == *(lhs_current_node->data))
        {
            duplicate_node = rhs_current_node;
            rhs_current_node = rhs_current_node->next;
            delete duplicate_node;
        }
        // If node from list1 is greater than node from the calling list
        else if (*(rhs_current_node->data) > *(lhs_current_node->data))
        {
            previous_node = lhs_current_node;
            lhs_current_node = lhs_current_node->next;
        }
        // If node from list1 is smaller than node from the calling list
        else // (*(rhs_current_node->data) < *(lhs_current_node->data))
        {
            // Append at the beginning of the calling list
            if (previous_node == nullptr)
            {
                list1.head_ptr_ = rhs_current_node->next;
                rhs_current_node->next = this->head_ptr_;
                this->head_ptr_ = rhs_current_node;
                rhs_current_node = list1.head_ptr_;
            }
            // Append somewhere in between previous node and current node of lhs list
            else
            {
                previous_node->next = rhs_current_node;
                rhs_current_node = rhs_current_node->next;
                previous_node->next->next = lhs_current_node;
                previous_node = previous_node->next;
            }
        }
    }
    // Attach remaining nodes from rhs to the end of lhs
    if (rhs_current_node != nullptr)
    {
        if (previous_node == nullptr)
        {
            // If the lhs list is empty, update the head pointer of lhs
            this->head_ptr_ = list1.head_ptr_;
        }
        else
        {
            // Otherwise, attach the remaining nodes from rhs to the end of lhs
            previous_node->next = rhs_current_node;
        }
        // Empty rhs list
        list1.head_ptr_ = nullptr;
    }
    return true;
}

template <class T>
bool List342<T>::Peek(T target, T &result) const
{
    // If head pointer is pointing to null reference
    if (head_ptr_ == nullptr)
    {
        return false;
    }
    // If target is at the beginning of the list
    if (*(head_ptr_->data) == target)
    {
        result = *(head_ptr_->data);
        return true;
    }
    // If target is located after the first Node
    Node<T> *current_node = head_ptr_;
    while (current_node != nullptr)
    {
        if (*(current_node->data) == target)
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
    while (head_ptr_ != nullptr)
    {
        Node<T> *current_node = head_ptr_;
        head_ptr_ = head_ptr_->next;
        delete current_node->data;
        delete current_node;
    }
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
bool List342<T>::operator!=(const List342<T> &rhs_list) const
{
    return !(*this == rhs_list);
}

// template <class T>
// List342<T> &List342<T>::operator+=(const List342<T> &rhs_list)
// {
//     return *this;
// }

// template <class T>
// List342<T> List342<T>::operator+(const List342<T> &rhs_list)
// {
// }
