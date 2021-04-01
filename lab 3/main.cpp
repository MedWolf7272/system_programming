#include <iostream>
using namespace std;

int main() {
	int* a = new int[10];
	int* b = new int[10];

	for (int i = 0; i < 10; ++i){
		a[i] = i;
		b[i] = i * 2;
	}
	int sum;

	asm(
		".intel_syntax noprefix\n\t"
		"mov rdx, 0\n\t"
		"mov rcx, 10\n\t"
		"for_loop:\n\t"
		"mov eax, [rsi]\n\t"
		"mov ebx, [rdi]\n\t"
		"imul rax, rbx\n\t"
		"add rdx, rax\n\t"
		"add rsi, 4\n\t"
		"add rdi, 4\n\t"
		"loop for_loop\n\t"
		: "=d" (sum)
		: "S" (a), "D" (b)
		:
	);
	cout << "Sum of elements: " << sum << endl;
	delete b;
	delete a;
	return 0;
}