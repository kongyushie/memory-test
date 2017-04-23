#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_writing(const unsigned long max_idx, unsigned long *ptr_start)
{
	unsigned long idx = 0;
	unsigned long *ptr = ptr_start;
	for (idx = 0; idx <= max_idx ; idx++, ptr++) {
		*ptr = idx;
	}

}
void do_rw(const unsigned long max_idx, unsigned long *ptr_start,int write_time)
{
	unsigned long *ptr = NULL;
	unsigned long idx = 0;
	ptr = ptr_start;
	int i;
	for(i=0;i< write_time;i++)
	for (idx = 0, ptr = ptr_start; idx <= max_idx; idx++, ptr++) {
		if (idx != *ptr) {
			printf(" Miss num in Ptr addr = %p, value = %lu; idx = %lu\n", ptr, *ptr, idx);
		}

		if (idx == max_idx) {
			printf("run %d\n", i);
		}
	}
	

}
#define MB_COUNT (1024)
#define MB_BYTE (1024 * 1024)
unsigned long G_count;
int write_time;
void checkInput(int argc, char *argv[])
{
    int i;
    for(i=1;i<argc;i++){
        if (argv[i][1] == 's'){
            char* p;
            G_count = strtol(argv[i+1], &p, 10);
            if (*p != '\0') goto PRINT_ERROR;
            i+=1;
            continue;
        }
        else if(argv[i][1] == 'w'){
            char* p;
            write_time = strtol(argv[i+1], &p, 10);
            if (*p != '\0') goto PRINT_ERROR;
            i+=1;
            continue;
        }
        else{
PRINT_ERROR:
            printf("Input error\n");
            exit(1);       
        }
    }
    //printf("s %lu, w %d\n",G_count,write_time);
    return ;

}
int main (int argc, char *argv[]) {

    checkInput(argc, argv);
	/* 4bytes * 256 = 1KB */
	const unsigned long byte_count = (unsigned long)MB_BYTE * (unsigned long)MB_COUNT * G_count;
	const unsigned long max_idx = (byte_count)/sizeof(unsigned long) - 1;
	unsigned long *ptr_start = NULL;
	unsigned long *ptr = NULL;
	ptr_start = ptr = (unsigned long *)malloc(byte_count);
	printf("Try to malloc %u MB...", MB_COUNT);
	if( ptr == NULL ) {
		printf("malloc %luMB failed\n", byte_count/MB_COUNT);
	} else {
		printf("malloc success\n");
		printf("Ptr start = %p; addr = %p; max_idx=%lu\n", ptr_start, ptr, max_idx);
	}
	do_writing(max_idx, ptr_start);
	do_rw(max_idx, ptr_start,write_time);

	printf("Reset addr %p to start = %p; \n", ptr, ptr_start);
	free(ptr_start);
	printf("Complete\n");
	return 0;
}
