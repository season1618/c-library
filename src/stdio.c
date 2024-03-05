#include "file.h"
#include "output.h"
#include "stdio.h"

struct FILE {
    int fd;
    unsigned char *buf;
    size_t buf_size;
    unsigned char *read_pos, *read_end;
    unsigned char *write_pos, *write_end;
    FILE *next;
};

static unsigned char stdin_buf[BUF_SIZE];
static unsigned char stdout_buf[BUF_SIZE];
static unsigned char stderr_buf[BUF_SIZE];

FILE stdin_file = {
    .fd = 0,
    .buf = stdin_buf,
    .buf_size = BUF_SIZE,
};

FILE stdout_file = {
    .fd = 1,
    .buf = stdout_buf,
    .buf_size = BUF_SIZE,
};

FILE stderr_file = {
    .fd = 2,
    .buf = stderr_buf,
    .buf_size = BUF_SIZE,
};

FILE *const stdin = &stdin_file;
FILE *const stdout = &stdout_file;
FILE *const stderr = &stderr_file;

int printf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stdout, format, ap);
}

int eprintf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
}
