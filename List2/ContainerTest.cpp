#include "ContainerTest.h"
#include <iostream>


void ListTest::test_case_one() 
{
	int a_1 = 4;
	double b_1 = 8.0;
	char c_1 = 's';
	int *a = new int(a_1);
	double *b = new double(b_1);
	char *c = new char(c_1);
	cout << "Size of the list: " << list.size << endl;
	list.push_back(a, sizeof(*a));
	list.push_back(b, sizeof(*b));
	list.push_back(c, sizeof(*c));
	if (list.size() != 3)
		cout << "ERROR: push_back doesnt work!!\n";
	else
		cout << "Size of the list: " << list.size << endl << "Test one passed\n";


	float e_1 = 4.4;
	string f_1 = "asfafagfgsdfg";
	long g_1 = 1135467435;
	float *e = new float(e_1);
	string *f = new string(f_1);
	long *g = new long(g_1);
	cout << "Size of the list: " << list.size << endl;
	list.push_front(e, sizeof(*e));
	list.push_front(f, sizeof(*f));
	list.push_front(g, sizeof(*g));
	if (list.size() != 6)
		cout << "ERROR: push_front doesnt work!!\n";
	else
		cout << "Size of the list: " << list.size << endl << "Test two passed\n";

	Container::Iterator *iter = list.begin();
	if (iter != nullptr) {
		bool equal = false;
		size_t size = 0;
		void *elem = nullptr;
		elem = iter->getElement(size);
		equal = sizeof(g_1) == size && memcmp(elem, &g_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(f_1) == size && memcmp(elem, &f_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(e_1) == size && memcmp(elem, &e_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(a_1) == size && memcmp(elem, &a_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(b_1) == size && memcmp(elem, &b_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(c_1) == size && memcmp(elem, &c_1, size) == 0;
		iter->goToNext();
		if (equal)
			cout << "Test three passed\n";
		else
			cout << "ERROR: Push functions or getElement and goToNext functions dont work\n";
	}
	else
		cout << "ERROR: begin or push functions dont work\n";

	cout << "Size of the list: " << list.size << endl;
	list.clear();
	cout << "Size of the list: " << list.size << endl;

}

void ListTest::test_case_two()
{
	Container::Iterator *iter = nullptr;
	try {
		iter = list.begin();
		list.remove(iter);
		cout << "ERROR: remove doesnt work!!\n";
	}
	catch (List2::IteratorError) {
		cout << "Test one passed\n";
	}

	delete iter;

	try {
		iter = list.end();
		list.remove(iter);
		cout << "ERROR: remove doesnt work!!\n";
	}
	catch (List2::IteratorError) {
		cout << "Test two passed\n";
	}

	delete iter;


}
