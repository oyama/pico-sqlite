#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pico/stdlib.h>
#include "fallback.h"

int flock(int fd, int operation) {
printf("flock\n");
    return 0;
}

ssize_t pread(int d, void *buf, size_t nbyte, off_t offset) {
    off_t head = lseek(d, 0, SEEK_CUR);

    ssize_t size = read(d + offset, buf, nbyte);
    lseek(d, head, SEEK_SET);
    return size;
}

ssize_t pwrite(int d, const void *buf, size_t nbyte, off_t offset) {
    off_t head = lseek(d, 0, SEEK_CUR);

    ssize_t size = write(d + offset, buf, nbyte);
    lseek(d, head, SEEK_SET);
    return size;
}

ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize) {
    strncpy(buf, path, bufsize);
    return strlen(path);
}

unsigned int sleep(unsigned int seconds) {
    sleep_ms(seconds * 1000);
    return 0;
}

int utimes(const char *path, const struct timeval times[2]) {
    return -1;
}

int chmod(const char *path, mode_t mode) {
    return 0;
}

int symlink(const char *path1, const char *path2) {
    return 0;
}

int chdir(const char *path) {
    return 0;
}

int fsync(int fildes) {
    return 0;
}

int getrusage(int who, struct rusage *r_usage) {
    return 0;
}

char *getcwd(char *buf, size_t size) {
    if (buf == NULL) {
        buf = calloc(1, size);
    }
    strcpy(buf, "/");
    return buf;
}

uid_t getuid(void) { return 1; }

int fchmod(int fildes, mode_t mode) { return 0; }
int fchown(int fildes, uid_t owner, gid_t group) { return 0; }
uid_t geteuid(void) { return 1; }

char *_fgets(char * restrict str, int size, FILE * restrict stream) {
    for (size_t i = 0; (int)i < size; i++) {
        uint8_t ch = getchar_timeout_us(1000);
        if (ch == 0xFF) {
            i--;
            continue;
        }
        putchar(ch);
        if (ch == 0x08) {
            i--;
            str[i] = '\0';
        } else {
           str[i] = ch;
        }
        if (ch == '\r') {
            putchar('\n');
            str[i + 1] = '\n';
            str[i + 2] = '\0';
            return str;
        }
    }
    str[size] = '\0';
    return str;
}