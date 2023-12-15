#include "syscall.h"
#include "output.h"
#include "memory.h"

// B. Kernighan and D. Ritchie, The C Programming Language 2nd edition.

#define NULL 0

#define MIN_ALLOC 4096

ulong cur_break = 0;

union header {
    struct {
        union header *next;
        uint size; // block size / header size
    } data;
    long align_; // force alignment
};

static union header base;
static union header *last = NULL;

void *sbrk(int num_byte) {
    if (cur_break == 0) cur_break = brk(0);
    
    if (num_byte == 0) return (void *)cur_break;

    ulong old_break = cur_break;
    ulong new_break = cur_break + (long)num_byte;
    if (brk(new_break) < new_break) return (void *)-1;
    cur_break = new_break;
    return (void *)old_break;
}

void free(void *addr) {
    union header *head = (union header *)addr - 1;
    union header *p;
    for (p = last; ; p = p->data.next) {
        if (p < head && head < p->data.next) break;
        if (p >= p->data.next && (p < head || head < p->data.next)) break;
    }
    if (head + head->data.size == p->data.next) {
        head->data.next = p->data.next->data.next;
        head->data.size += p->data.next->data.size;
    } else {
        head->data.next = p->data.next;
    }
    if (head == p + p->data.size) {
        p->data.next = head->data.next;
        p->data.size += head->data.size;
    } else {
        p->data.next = head;
    }
    last = p;
}

static union header *morecore(uint num_unit) {
    if (num_unit < MIN_ALLOC) num_unit = MIN_ALLOC;
    char *p = sbrk(num_unit * sizeof(union header));
    if (p == (char *)-1) return 0;
    union header *head = (union header *)p;
    head->data.size = num_unit;
    free((void *)(head + 1));
    return last;
}

void *alloc(uint num_byte) {
    uint num_unit = (num_byte + sizeof(union header) - 1) / sizeof(union header) + 1; // block size / header size

    if (last == NULL) {
        base.data.next = &base;
        base.data.size = 0;
        last = &base;
    }
    
    for (union header *prev = last; ; prev = prev->data.next) {
        union header *cur = prev->data.next;
        if (cur->data.size >= num_unit) {
            if (cur->data.size == num_unit) {
                prev->data.next = cur->data.next;
            } else {
                cur->data.size -= num_unit;
                cur += cur->data.size;
                cur->data.size = num_unit;
            }
            last = prev;
            return (void *)(cur + 1); // next to header
        }
        if (cur == last) {
            cur = morecore(num_unit);
            if (cur == NULL) return NULL;
        }
    }
}