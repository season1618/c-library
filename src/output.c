#include "syscall.h"
#include "vararg.h"

void print_int(int fd, int num) {
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

    write(fd, buf + i, 16 - i);
}

void print_file_vararg(int fd, const char *format, va_list ap) {
    char buf[1];
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            switch (format[i+1]) {
                case 'd':
                    print_int(fd, va_arg(ap, int));
                    i++;
                    break;
                default:
                    buf[0] = '%';
                    write(fd, buf, 1);
                    continue;
            }
        } else {
            buf[0] = format[i];
            write(fd, buf, 1);
        }
    }
}

void print_file(int fd, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_file_vararg(fd, format, ap);
}

void print(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    print_file_vararg(1, format, ap);
}