#include <stdio.h>
#include <stdlib.h>

#define time 6
#define MB_COUNT (1024*time)
#define MB_BYTE (1024 * 1024)

void do_writing(const unsigned long max_idx, unsigned long *ptr)
{
	unsigned long idx = 0;
	
	for (idx = 0; idx <= max_idx ; idx++, ptr++) {
		*ptr = idx;
	}

}
void do_rw(const unsigned long max_idx, unsigned long *ptr_start)
{
	unsigned long *ptr = NULL;
	unsigned long idx = 0;
	ptr = ptr_start;
	for (idx = 0; idx <= max_idx; idx++, ptr++) {
		if (idx != *ptr) {
			printf(" Miss num in Ptr addr = %p, value = %lu; idx = %lu\n", ptr, *ptr, idx);
		}

		if (idx == max_idx) {
			printf("The last Ptr addr = %p, value = %lu\n", ptr, *ptr);
		}
	}
	

}
int main () {


	/* 4bytes * 256 = 1KB */

	const unsigned long byte_count = (unsigned long)MB_BYTE * (unsigned long)MB_COUNT;
	const unsigned long max_idx = (byte_count)/sizeof(unsigned long) - 1;
	unsigned long *ptr_start = NULL;
	unsigned long *ptr = NULL;
	ptr_start = ptr = (unsigned long *)malloc(byte_count);
	//printf("Try to malloc %u MB...\n", 5*byte_count/MB_BYTE);
	if( ptr == NULL ) {
		printf("malloc %luMB failed\n", byte_count/MB_COUNT);
	} else {
		printf("malloc success\n");
		printf("Ptr start = %p; addr = %p; max_idx=%lu\n", ptr_start, ptr, max_idx);
	}
	do_writing(max_idx, ptr);
	//do_writing(max_idx, ptr_start);

	printf("Reset addr %p to start = %p; \n", ptr, ptr_start);
	free(ptr_start);
	printf("Complete\n");
	return 0;
}
