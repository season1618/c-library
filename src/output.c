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

int vfprintf(FILE *file, const char *format, va_list ap) {
    char buf[1];
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            switch (format[i+1]) {
                case 'd':
                    fprint_int(file, va_arg(ap, int));
                    i++;
                    break;
                default:
                    buf[0] = '%';
                    fwrite(buf, 1, 1, file);
                    continue;
            }
        } else {
            buf[0] = format[i];
            fwrite(buf, 1, 1, file);
        }
    }
}

int fprintf(FILE *file, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    vfprintf(file, format, ap);
}
