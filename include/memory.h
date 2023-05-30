#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_MEMORY_SIZE 1000000000 // 1 Gbyte
#define PAGE_SIZE 8000 // 8 kbytes

typedef struct {
    int page_number;
    int referenced;
} Page;

typedef struct {
    int segment_number;
    Page* pages;
} Segment;

Segment* allocateSegment(int segment_number, int num_pages);
void deallocateSegment(Segment* segment);
int allocatePage(Segment* segment, int page_number);

#endif //MEMORY



