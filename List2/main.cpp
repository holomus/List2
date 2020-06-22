#include "List2.h"
#include "Mem.h"
#include "ContainerTest.h"

int main() {
	Mem mem(100000000000000);
	ListTest test(mem);

	test.test_case_one();
	test.test_case_two();

	return 0;
}