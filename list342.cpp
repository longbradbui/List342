#include <iostream>
#include <string>
#include "list342.h"
#include "child.h"
#include "rational.h"
using namespace std;

int main()
{
	cout << "\n-- Unit Testing with Child Class -- " << endl;
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
	cout << "\n-- Unit Testing with Rational Class -- " << endl;
	Rational r;
	Rational r1(1, 1);
	Rational r2(1, 2);
	Rational r3(1, 3);
	Rational r4(1, 4);
	Rational r5(1, 5);
	Rational r6(1, 6);
	Rational r7(1, 7);
	Rational r8(1, 8);
	Rational r9(1, 9);
	Rational r10(1, 10);
	Rational r11(1, 11);
	Rational r12(1, 12);
	Rational r13(1, 13);
	Rational r14(1, 14);
	Rational r15(1, 15);
	Rational r16(1, 16);
	Rational r17(1, 17);
	Rational r18(1, 18);
	Rational r19(1, 19);
	Rational *r20 = nullptr;
	List342<Rational> rational_test, rational_test1, rational_test2, empty_list1, empty_list2;
	rational_test1.Insert(&r1);
	rational_test1.Insert(&r1);
	rational_test1.Insert(&r2);
	rational_test1.Insert(&r3);
	rational_test1.Insert(&r4);
	rational_test1.Insert(&r1);
	rational_test1.Insert(&r5);
	rational_test1.Insert(&r2);
	rational_test1.Insert(&r6);
	rational_test1.Insert(&r1);
	rational_test1.Insert(&r7);
	rational_test1.Insert(&r7);
	rational_test1.Insert(&r6);
	cout << "Size of Rational List #0 [Before Merge]: " << rational_test.Size() << endl;
	cout << "Size of Rational List #1 [Before Merge]: " << rational_test1.Size() << endl;
	cout << "Rational List #1: " << rational_test1 << endl;
	cout << "Start Merging List #0 and List #1 ..." << endl;
	rational_test.Merge(rational_test1);
	cout << "Rational List #0 [After Merge]: " << rational_test << endl;
	cout << "Rational List #1 [After Merge]: " << rational_test1 << endl;
	cout << "Size of Rational List #0 [After Merge]: " << rational_test.Size() << endl;
	cout << "Size of Rational List #1 [After Merge]: " << rational_test1.Size() << endl;
	rational_test2.Insert(&r14);
	rational_test2.Insert(&r2);
	rational_test2.Insert(&r3);
	rational_test2.Insert(&r8);
	rational_test2.Insert(&r10);
	rational_test2.Insert(&r9);
	rational_test2.Insert(&r13);
	rational_test2.Insert(&r5);
	rational_test2.Insert(&r11);
	rational_test2.Insert(&r8);
	rational_test2.Insert(&r12);
	cout << "Rational List #2: " << rational_test2 << endl;
	cout << "Performing Deep Copy from List #2 to List #3 ..." << endl;
	List342<Rational> rational_test3 = rational_test2;
	cout << "Rational List #3: " << rational_test3 << endl;
	cout << "Size of Rational List #0 [Before += operator]: " << rational_test.Size() << endl;
	cout << "Size of Rational List #3 [Before += operator]: " << rational_test3.Size() << endl;
	rational_test3 += rational_test;
	cout << "Performing List #3 += List #0 ..." << endl;
	cout << "Rational List #0 [After += operator]: " << rational_test << endl;
	cout << "Rational List #3 [After += operator]: " << rational_test3 << endl;
	cout << "Size of Rational List #0 [After += operator]: " << rational_test.Size() << endl;
	cout << "Size of Rational List #3 [After += operator]: " << rational_test3.Size() << endl;
	rational_test3.Peek(r10, r);
	cout << "r#10: " << r10 << "r#0: " << r << endl;
	rational_test3.Insert(r20);
	rational_test3.Remove(r15, r);
	rational_test3.Remove(r14, r);
	cout << "r#14: " << r14 << "r#0: " << r << endl;
	rational_test3.Insert(&r14);
	rational_test3.Merge(rational_test3);
	rational_test3.Merge(empty_list1);
	empty_list1.Merge(empty_list2);
	List342<Rational> rational_test4, clone_list3, clone_list4;
	rational_test4.Insert(&r15);
	rational_test4.Insert(&r16);
	rational_test4.Insert(&r17);
	rational_test4.Insert(&r18);
	rational_test4.Insert(&r19);
	cout << "Copy Lists to Clone List by [=] operator ..." << endl;
	clone_list3 = rational_test3;
	clone_list4 = rational_test4;
	cout << (clone_list3 == rational_test3 ? "Clone List #3 is identical to List #3" : "Clone List #3 is not identical to List #3") << endl;
	cout << "Clone List #3 [Before += operator]: " << clone_list3 << endl;
	cout << "Clone List #4 [Before += operator]: " << clone_list4 << endl;
	clone_list3 += clone_list4;
	cout << "Clone List #3 [After += operator]: " << clone_list3 << endl;
	cout << "Clone List #4 [After += operator]: " << clone_list4 << endl;
	cout << "Rational List #3: " << rational_test3 << endl;
	cout << "Rational List #4: " << rational_test4 << endl;
	cout << "Size of Rational List #3 [Before + operator]: " << rational_test3.Size() << endl;
	cout << "Size of Rational List #4 [Before + operator]: " << rational_test4.Size() << endl;
	cout << "Adding List #3 and #4 to form Final List ..." << endl;
	List342<Rational> final_list = rational_test3 + rational_test4;
	cout << "Size of Rational List #3 [After + operator]: " << rational_test3.Size() << endl;
	cout << "Size of Rational List #4 [After + operator]: " << rational_test4.Size() << endl;
	cout << "Final List: " << final_list << endl;
	cout << "\n-- Unit Testing with String List -- " << endl;
	// Test Case 1: Merging empty lists
	List342<string> list1, list2;
	list1 += list2;
	cout << "Merged list after merging empty lists: " << list1 << endl;
	// Test Case 2: Merging lists with one element
	List342<string> list3, list4;
	list3.Insert(new string("Apple"));
	list4.Insert(new string("Banana"));
	list3 += list4;
	cout << "Merged list after merging lists with one element: " << list3 << endl;
	// Test Case 3: Merging lists with duplicate elements
	List342<string> list5, list6;
	list5.Insert(new string("Apple"));
	list5.Insert(new string("Orange"));
	list6.Insert(new string("Apple"));
	list6.Insert(new string("Grape"));
	list5 += list6;
	cout << "Merged list after merging lists with duplicate elements: " << list5 << endl;
	// Test Case 4: Merging sorted lists
	List342<string> list7, list8;
	list7.Insert(new string("Apple"));
	list7.Insert(new string("Banana"));
	list8.Insert(new string("Grape"));
	list8.Insert(new string("Orange"));
	list7 += list8;
	cout << "Merged list after merging sorted lists: " << list7 << endl;
	// Test Case 5: Merging unsorted lists
	List342<std::string> list9, list10;
	list9.Insert(new string("Banana"));
	list9.Insert(new string("Apple"));
	list10.Insert(new string("Orange"));
	list10.Insert(new string("Grape"));
	list9 += list10;
	cout << "Merged list after merging unsorted lists: " << list9 << endl;
	// Test Case 6: Merging lists with null data
	List342<string> list11, list12;
	list11.Insert(nullptr);
	list11.Insert(new string("Apple"));
	list12.Insert(new string("Orange"));
	list12.Insert(nullptr);
	list11 += list12;
	cout << "Merged list after merging lists with null data: " << list11 << endl;
	cout << "\n-- Unit Testing with File Input -- " << endl;
	List342<Child> child;
	child.BuildList("child.txt");
	cout << child << endl;
	List342<Child> us_leaders;
	us_leaders.BuildList("leaders.txt");
	cout << us_leaders << endl;
	List342<string> alphabet;
	alphabet.BuildList("alphabet.txt");
	cout << alphabet << endl;
}
