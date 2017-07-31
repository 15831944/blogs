#include <stdio.h>


int main() {
	unsigned short a = 126;
	unsigned short b = a - 128;
	short c = a - 128;
	unsigned short d = b % 256;

	printf("c = %d %u %x\n", c, c, c);
	printf("b = %d %u %x\n", b, b, b);
	printf("d = %d %u %x\n", d, d, d);
	
	printf("65535 %% 256 = %d", 65535 % 256);
}
