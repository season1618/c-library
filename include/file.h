#define O_RDONLY    00
#define O_WRONLY    01
#define O_RDWR      02
#define O_CREAT   0100
#define O_EXCL    0200
#define O_NOCTTY  0400
#define O_TRUNC  01000
#define O_APPEND 02000

typedef long unsigned int size_t;

#define READ_MODE_FLAG (O_RDONLY)
#define WRITE_MODE_FLAG (O_WRONLY | O_CREAT | O_TRUNC)
#define APPEND_MODE_FLAG (O_WRONLY | O_CREAT | O_APPEND)

struct FILE;
typedef struct FILE FILE;

#define BUF_SIZE 1024

FILE *fopen_read(const char *name);
FILE *fopen_write(const char *name);
size_t fread(void *ptr, size_t size, size_t len, FILE *file);
size_t fwrite(const void *ptr, size_t size, size_t len, FILE *file);
int fflush(FILE *file);
void fflush_all();
