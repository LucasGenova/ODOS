#include "memory.h"

Segment* allocateSegment(int segment_number, int num_pages) {
    Segment* segment = (Segment*)malloc(sizeof(Segment));
    segment->segment_number = segment_number;
    segment->pages = (Page*)malloc(num_pages * sizeof(Page));

    // inicializa as páginas do segmento
    for (int i = 0; i < num_pages; i++) {
        segment->pages[i].page_number = -1; // página não alocada
        segment->pages[i].referenced = 0; // Página não referenciada
    }

    return segment;
}

void deallocateSegment(Segment* segment) {
    free(segment->pages);
    free(segment);
}

// aloca uma página em um segmento usando segunda chance
int allocatePage(Segment* segment, int page_number) {
    int num_pages = sizeof(segment->pages) / sizeof(segment->pages[0]);
    int index = 0;
    int found = 0;

    while (!found) {
        Page *page = &segment->pages[index];

        if (page->page_number == -1) {
            page->page_number = page_number;
            page->referenced = 1;
            found = 1;
        } else {
            if (page->referenced == 1) {
                page->referenced = 0;
            } else {
                page->page_number = page_number;
                page->referenced = 1;
                found = 1;
            }
        }

        index = (index + 1) % num_pages;
    }

    return index;
}