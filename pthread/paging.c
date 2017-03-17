#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define time 4
#define MB_COUNT (1024*time)
#define MB_BYTE (1024 * 1024)
unsigned long byte_count, max_idx;
unsigned long *ptr_start;
unsigned long *ptr1_start;
unsigned long *ptr2_start;

void pwrite(){
	unsigned long *ptr;
	unsigned long idx;
	ptr = ptr_start;
	int i;
	for(i=0;i<11;i++)
	for (idx = 0; idx <= max_idx ; idx++, ptr++)*ptr = idx;
}
void pwrite1(){
	unsigned long *ptr;
	unsigned long idx;
	ptr = ptr1_start;
	int i;
	for(i=0;i<11;i++)
	for (idx = 0; idx <= max_idx ; idx++, ptr++)*ptr = idx;
}
void pwrite2(){
	unsigned long *ptr;
	unsigned long idx;
	ptr = ptr2_start;
	int i;
	for(i=0;i<11;i++)
	for (idx = 0; idx <= max_idx ; idx++, ptr++)*ptr = idx;
}
int main () {

	/* 4bytes * 256 = 1KB */

	byte_count = (unsigned long)MB_BYTE * (unsigned long)MB_COUNT;
	max_idx = (byte_count)/sizeof(unsigned long) - 1;
	ptr_start = NULL;
	ptr_start = (unsigned long *)malloc(byte_count);
	ptr1_start = (unsigned long *)malloc(byte_count);
	ptr2_start = (unsigned long *)malloc(byte_count);
	if( ptr_start == NULL && ptr1_start ==NULL && ptr2_start == NULL) {
		printf("malloc %luMB failed\n", byte_count/MB_COUNT);
	} else {
		printf("malloc success\n");
	}

	pthread_t t1, t2;
		pthread_create(&t1, NULL, (void*) pwrite1, NULL);
		pthread_create(&t2, NULL, (void*) pwrite2, NULL);
		pwrite();
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	/*	ptr = ptr_start;

		for (idx = 0; idx <= max_idx; idx++, ptr++) {
		if (idx != *ptr) {
		printf("Ptr addr = %p, value = %lu; idx = %lu\n", ptr, *ptr, idx);
		}

		if (idx == max_idx) {
		printf("The last Ptr addr = %p, value = %lu\n", ptr, *ptr);
		}
		}
		*/
	free(ptr_start);
	free(ptr1_start);
	free(ptr2_start);
	printf("Complete\n");
	return 0;
}
