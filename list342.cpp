// program3_description_code.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "list342.h"
#include "child.h"
using namespace std;
int main()
{
	Child c1("Angie", "Ham", 7);
	Child c2("Pradnya", "Dhala", 8);
	Child c3("Bill", "Vollmann", 13);
	Child c4("Cesar", "Ruiz", 6);
	Child c5("Piqi", "Tangi", 7);
	Child c6("Russell", "Wilson", 13);
	Child c7("Hank", "Aaron", 3);
	Child c8("Madison", "Fife", 7);
	Child c9("Miles", "Davis", 65);
	Child c10("John", "Zorn", 4);
	Child c11;

	List342<Child> class1, class2, soccer, chess;
	int a = 1, b = -1, c = 13;
	class1.Insert(&c1);
	class1.Insert(&c2);
	class1.Insert(&c3);
	class1.Insert(&c4);
	class1.Insert(&c5);
	class1.Insert(&c6);
	class1.Insert(&c5);
	cout << "class1: " << class1 << endl; // Line 1 on output.txt

	if (!class1.Insert(&c1))
	{
		cout << "ERROR::: Duplicate" << endl; // Line 2 on output.txt
	}
	class2.Insert(&c4);
	class2.Insert(&c5);
	class2.Insert(&c6);
	class2.Insert(&c7);
	class2.Insert(&c10);
	cout << "Class2: " << class2 << endl; // Line 3 on output.txt

	class1.Merge(class2);
	class2.Merge(class1);
	class1.Merge(class2);
	class1.Merge(class1);
	cout << "class1 and 2 Merged: " << class1 << endl; // Line 4 on output.txt

	class1.Remove(c4, c11);
	class1.Remove(c5, c11);
	class1.Remove(c11, c11);
	if (class1.Remove(c1, c11))
	{
		cout << "Removed from class1, student " << c11 << endl; // Line 5 on output.txt
	}
	cout << "class1: " << class1 << endl; // Line 6 on output.txt

	soccer.Insert(&c6);
	soccer.Insert(&c4);
	soccer.Insert(&c9);
	cout << "soccer: " << soccer << endl; // Line 7 on output.txt
	soccer += class1;
	cout << "soccer += class1 : " << soccer << endl; // Line 8 on output.txt

	List342<Child> football = soccer;
	if (football == soccer)
	{
		cout << "football: " << football << endl; // Line 9 on output.txt
	}
	if (football.Peek(c6, c11))
	{
		cout << c11 << " is on the football team" << endl; // Line 10 in output.txt
	}
	soccer.DeleteList();
	List342<int> numbers;
	numbers.Insert(&a);
	numbers.Insert(&b);
	numbers.Insert(&c);
	cout << "These are the numbers: " << numbers << endl; // Line 11 on output.txt
	numbers.DeleteList();
}
