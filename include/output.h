#include "file.h"
#include "vararg.h"

int fprint_int(FILE *file, int num);
int fprint_char(FILE *file, int c);
int vfprintf(FILE *file, const char *format, va_list ap);
int fprintf(FILE *file, const char *format, ...);
