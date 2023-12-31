struct timespec;

int read(int fd, void *buf, int count);
int write(int fd, const void *buf, int count);
unsigned long brk(unsigned long addr);
int clock_gettime(unsigned int clock_id, struct timespec *tp);
int getrandom(void *buf, unsigned int len, unsigned int flag);