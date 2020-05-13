#include "List2.h"
#include "Mem.h"

int main() {
	Mem mem(19);
	List2 l(mem);
	int k = 9;
	l.push_back(&k, sizeof(k));
	return 0;
}