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
	cout << "Size of the list: " << list.size() << endl;
	list.push_back(a, sizeof(*a));
	list.push_back(b, sizeof(*b));
	list.push_back(c, sizeof(*c));
	if (list.size() != 3) {
		cout << "ERROR: push_back doesnt work!!\n";
		cout << "Test case one failed!!\n";
		delete a, b, c;
		return;
	}
	else
		cout << "Size of the list: " << list.size() << endl << "Test one passed\n";


	float e_1 = 4.4;
	char f_1[] = "asfafagfgsdfg";
	long g_1 = 1135467435;
	float *e = new float(e_1);
	char *f = new char[sizeof(f_1)];
	memcpy(f, f_1, sizeof(f_1));
	long *g = new long(g_1);
	cout << "Size of the list: " << list.size() << endl;
	list.push_front(e, sizeof(*e));
	list.push_front(f, strlen(f) + 1);
	list.push_front(g, sizeof(*g));
	if (list.size() != 6) {
		cout << "ERROR: push_front doesnt work!!\n";
		cout << "Test case one failed!!\n";
		delete a, b, c, e, g;
		delete[] f;
		return;
	}
	else
		cout << "Size of the list: " << list.size() << endl << "Test two passed\n";

	
	Container::Iterator *iter = list.begin();
	if (iter != nullptr) {
		bool equal = false;
		size_t size = 0;
		void *elem = nullptr;
		elem = iter->getElement(size);
		equal = sizeof(g_1) == size && memcmp(elem, &g_1, size) == 0;
		iter->goToNext();
		elem = iter->getElement(size);
		equal = equal && sizeof(f_1) == size && memcmp(elem, f_1, size) == 0;
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
		else {
			cout << "ERROR: Push functions or getElement and goToNext functions dont work\n";
			cout << "Test case one failed!!\n";
			delete a, b, c, e, g;
			delete[] f;
			delete iter;
			return;
		}
	}
	else
		cout << "ERROR: begin or push functions dont work\n";

	delete iter;

	cout << "Size of the list: " << list.size() << endl;
	list.clear();
	cout << "Size of the list: " << list.size() << endl;
	if (list.empty())
		cout << "Test four passed\n";
	else {
		cout << "ERROR: clear function doesnt work!!\n";
		cout << "Test case one failed!!\n";
		delete a, b, c, e, g;
		delete[] f;
		return;
	}
	cout << "Test case one passed!!\n";
}






void ListTest::test_case_two()
{
	Container::Iterator *iter = nullptr;
	try {
		iter = list.begin();
		list.remove(iter);
		cout << "ERROR: remove doesnt work!!\n";
		cout << "Test case two failed!!\n";
		delete iter;
		return;
	}
	catch (List2::IteratorError) {
		cout << "Test one passed\n";
	}

	delete iter;

	try {
		iter = list.end();
		list.remove(iter);
		cout << "ERROR: remove doesnt work!!\n";
		cout << "Test case two failed!!\n";
		delete iter;
		return;
	}
	catch (List2::IteratorError) {
		cout << "Test two passed\n";
	}

	delete iter;

	int a_1 = 4;
	double b_1 = 8.0;
	char c_1 = 's';
	int *a = new int(a_1);
	double *b = new double(b_1);
	char *c = new char(c_1);

	float e_1 = 4.4;
	char f_1[] = "asfafagfgsdfg";
	long g_1 = 1135467435;
	float *e = new float(e_1);
	char *f = new char[sizeof(f_1)];
	memcpy(f, f_1, sizeof(f_1));
	long *g = new long(g_1);


	list.push_back(e, sizeof(*e));
	iter = list.begin();
	list.insert(iter, f, strlen(f) + 1);
	list.insert(iter, g, sizeof(*g));
	list.push_back(a, sizeof(*a));
	list.push_back(b, sizeof(*b));
	list.push_back(c, sizeof(*c));
	
	delete iter;
	iter = list.begin();
	bool equal = false;
	size_t size = 0;
	void *elem = nullptr;
	elem = iter->getElement(size);
	equal = sizeof(g_1) == size && memcmp(elem, &g_1, size) == 0;
	iter->goToNext();
	elem = iter->getElement(size);
	equal = equal && sizeof(f_1) == size && memcmp(elem, f_1, size) == 0;
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
	else {
		cout << "ERROR: Insert function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, c, e, g;
		delete[] f;
		delete iter;
		return;
	}

	delete iter;

	Container::Iterator *iter_end = nullptr;
	iter = list.begin();
	iter_end = list.end();
	int i = 0;
	while (!iter->equals(iter_end)) {
		++i;
		iter->goToNext();
	}
	if (i != list.size()) {
		cout << "ERROR: End function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, c, e, g;
		delete[] f;
		delete iter;
		return;
	}
	else
		cout << "Test four passed\n";

	delete iter;
	delete iter_end;

	//iter = list.begin();
	//list.begin() => list.pop_front() удаляет начальный элемент и наш итератор iter уже никуда не указывает
	//надо быть осторожней с этим 
	//STL контейнер ведет себя также
	list.pop_front();
	iter = list.begin();
	elem = iter->getElement(size);
	if (sizeof(f_1) == size && memcmp(elem, f_1, size) == 0 && list.size() == i - 1) {
		cout << "Test five passed\n";
	}
	else {
		cout << "ERROR: pop_front function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, c, e, g;
		delete[] f;
		delete iter;
		return;
	}
	
	iter->goToNext();
	iter->goToNext();
	iter->goToNext();
	list.pop_back();
	if (iter->hasNext()) {
		cout << "Test six passed\n";
	}
	else {
		cout << "ERROR: pop_front function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, c, e;
		delete[] f;
		delete iter;
		return;
	}
	
	delete iter;
	
	elem = list.front(size);
	if (sizeof(f_1) == size && memcmp(elem, f_1, size) == 0) {
		cout << "Test seven passed\n";
	}
	else {
		cout << "ERROR: front function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, e;
		delete[] f;
		delete iter;
		return;
	}

	elem = list.back(size);
	if (sizeof(b_1) == size && memcmp(elem, &b_1, size) == 0) {
		cout << "Test eight passed\n";
	}
	else {
		cout << "ERROR: front function doesnt work\n";
		cout << "Test case two failed!!\n";
		delete a, b, e;
		delete[] f;
		delete iter;
		return;
	}


	list.clear();

	cout << "Test case two passed!!\n";
}
