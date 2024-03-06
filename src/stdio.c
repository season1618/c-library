#include "file.h"
#include "output.h"
#include "stdio.h"

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
