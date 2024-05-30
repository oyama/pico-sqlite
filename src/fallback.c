#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pico/stdlib.h>


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
    return -1;
}

int chdir(const char *path) {
    return 0;
}

int fsync(int fildes) {
    return 0;
}

int getrusage(int who, struct rusage *r_usage) {
    return -1;
}

char *getcwd(char *buf, size_t size) {
    if (buf == NULL) {
        buf = calloc(1, size);
    }
    strcpy(buf, "/");
    return buf;
}

char *_fgets(char * restrict str, int size, FILE * restrict stream) {
    for (size_t i = 0; i < size; i++) {
        uint8_t ch = getchar_timeout_us(1000);
        if (ch == 0xFF) {
            i--;
            continue;
        }
        putchar(ch);
        str[i] = ch;
        if (ch == '\r') {
            str[i + 1] = '\n';
            str[i + 2] = '\0';
            return str;
        }
    }
    str[size] = '\0';
    return str;
}
