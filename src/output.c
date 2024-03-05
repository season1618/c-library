#include "syscall.h"
#include "file.h"
#include "vararg.h"

int fprint_int(FILE *file, int num) {
    int sign;
    if (num >= 0) {
        sign = 0;
    } else {
        sign = 1;
        num = -num;
    }
    
    char buf[16];
    int i;
    for (i = 15; i >= 0; i--) {
        buf[i] = '0' + num % 10;
        num /= 10;
        if (num == 0) break;
    }
    
    if (sign) {
        i--;
        buf[i] = '-';
    }

    return fwrite(buf + i, 1, 16 - i, file);
}

int fprint_char(FILE *file, char c) {
    return fwrite(&c, 1, 1, file);
}

int fprint_string(FILE *file, char *s) {
    int len = 0;
    while (s[len] != '\0') len++;
    return fwrite(s, 1, len, file);
}

int vfprintf(FILE *file, const char *format, va_list ap) {
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            switch (format[i+1]) {
                case 'c':
                    fprint_char(file, va_arg(ap, int));
                    i++;
                    break;
                case 'd':
                    fprint_int(file, va_arg(ap, int));
                    i++;
                    break;
                case 's':
                    fprint_string(file, (char *)va_arg(ap, long));
                    i++;
                    break;
                default:
                    fwrite(format + i, 1, 1, file);
                    continue;
            }
        } else {
            fwrite(format + i, 1, 1, file);
        }
    }
}

int fprintf(FILE *file, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(file, format, ap);
}
