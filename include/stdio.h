#include "file.h"

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;

int printf(const char *format, ...);
int eprintf(const char *format, ...);
