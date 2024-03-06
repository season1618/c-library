#include "syscall.h"
#include "file.h"
#include "stdio.h"
#include "memory.h"

struct FILE {
    int fd;
    unsigned char *buf;
    size_t buf_size;
    unsigned char *read_pos, *read_end;
    unsigned char *write_pos, *write_end;
    FILE *next;
};

#define NULL 0

FILE *head = NULL;

#define UNGET 8

#define MIN(a,b) ((a) < (b) ? (a) : (b))

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

FILE *fopen(const char *name, int flag) {
    int fd = open(name, flag, 0666);

    FILE *file = alloc(sizeof(FILE) + UNGET + BUF_SIZE);
    file->fd = fd;
    file->buf = (unsigned char *)file + sizeof(FILE) + UNGET;
    file->buf_size = BUF_SIZE;
    file->read_pos = file->read_end = 0;
    file->write_pos = file->buf;
    file->write_end = file->buf + file->buf_size;
    file->next = head;
    head = file;
}

FILE *fopen_read(const char *name) {
    return fopen(name, READ_MODE_FLAG);
}

FILE *fopen_write(const char *name) {
    return fopen(name, WRITE_MODE_FLAG);
}

size_t fread(void *ptr, size_t size, size_t len, FILE *file) {
    unsigned char *ptr_ = ptr;
    for (size_t rest_size = size * len; rest_size > 0; ) {
        if (file->read_pos == file->read_end) {
            int cnt = read(file->fd, file->buf, file->buf_size);
            if (cnt == 0) {
                return len - (rest_size + size - 1) / size;
            }
            file->read_pos = file->buf;
            file->read_end = file->buf + cnt;
        }
        size_t read_size = MIN(file->read_end - file->read_pos, rest_size);
        for (int i = 0; i < read_size; i++) {
            ptr_[i] = file->read_pos[i];
        }
        ptr_ += read_size;
        file->read_pos += read_size;
        rest_size -= read_size;
    }
    return len;
}

size_t fwrite(const void *ptr, size_t size, size_t len, FILE *file) {
    const unsigned char *ptr_ = ptr;
    for (size_t rest_size = size * len; rest_size > 0; ) {
        for (; file->write_pos < file->write_end && rest_size > 0; ) {
            *file->write_pos = *ptr_;
            file->write_pos++, ptr_++;
            rest_size--;
        }

        if (file->write_pos == file->write_end) {
            if (write(file->fd, file->buf, file->write_pos - file->buf) == -1) return len - (rest_size + size - 1) / size;
            file->write_pos = file->buf;
            file->write_end = file->buf + file->buf_size;
        }
    }
    return len;
}

int fflush(FILE *file) {
    int cnt = write(file->fd, file->buf, file->write_pos - file->buf);
    file->write_pos = file->buf;
    return cnt;
}

void fflush_all() {
    for (FILE *file = head; file != NULL; file = file->next) {
        fflush(file);
    }
}
