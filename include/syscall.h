int read(int fd, void *buf, int count);
int write(int fd, const void *buf, int count);
void *brk(void *addr);
int getrandom(void *buf, unsigned int len, unsigned int flag);