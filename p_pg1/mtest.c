#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void hexdump(void* addr, size_t size) {
	unsigned char* p = (unsigned char*)addr;
	for (size_t i = 0; i < size; i++) {
		printf("%02x ", p[i]);
		if ((i + 1) % 16 == 0) printf("\n");
	}
	printf("\n");
}

int main()
{
	uint32_t* ip = malloc(sizeof(uint32_t) * 5);
	printf("%p\n", ip);

	uint32_t* p = NULL;

	*ip = 19;
	*(ip+3) = 10;
	p = (ip+3);
	printf("%p\n", p);

	hexdump(ip, 20);
	free(ip);
	*(ip+3) = 15;
	return 0;
}
