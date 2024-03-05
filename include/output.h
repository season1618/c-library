#include "file.h"
#include "vararg.h"

int fprint_int(FILE *file, int num);
int fprint_char(FILE *file, char c);
int fprint_string(FILE *file, char *s);
int vfprintf(FILE *file, const char *format, va_list ap);
int fprintf(FILE *file, const char *format, ...);
