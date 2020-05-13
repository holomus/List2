#pragma once
#include "List2.h"

struct ListTest
{
	ListTest(MemoryManager& mem) : list(mem) {};
	void test_case_one();
	void test_case_two();
private:
	List2 list;
};

