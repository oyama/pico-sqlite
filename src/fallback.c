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

/*
 * Deviates from the original function of fgets to support cursor movement
 */
char *_fgets(char * restrict str, int size, FILE * restrict stream) {
    char escape[4] = {0};
    size_t i = 0;
    memset(str, 0, size);
    while (i < (size_t)size) {
        uint8_t ch = getchar_timeout_us(1000);
        if (ch == 0xFF || ch ==0xFE) {
            continue;
        }
        // manage escape sequence
        if (ch == 0x1B) {
            escape[0] = ch;
            continue;
        } else if (escape[0] == 0x1B && ch == 0x5B) {
            escape[1] = ch;
            continue;
        } else if (escape[0] == 0x1B && escape[1] == 0x5B) {
            escape[2] = ch;
            if (ch == 0x44 && i > 0) {
                i--;
                printf(escape);
            } else if (ch == 0x43) {
                if (i < strlen(str)) {
                    i++;
                    printf(escape);
                }
            }
            escape[0] = '\0';
            continue;
        }
        escape[0] = '\0';

        if (ch == '\b' || ch == 127) {  // backspace or delete key
            if (i == 0)
                continue;

            printf("\b \b");
            i--;
            for (size_t j = i; j < strlen(str); j++) {
                str[j] = str[j + 1];
                putchar(str[j]);
            }
            putchar(' ');
            for (size_t j = i; j < strlen(str) + 1; j++)
                putchar('\b');
            str[strlen(str)] = '\0';
            continue;
        } else if (ch == ' ') {  // space key
            for (size_t j = strlen(str) + 1; i <= j; j--) {
                str[j + 1] = str[j];
                if (j == 0)
                    break;
            }
            str[i] = ch;
            putchar(' ');
            for (size_t j = i + 1; j < strlen(str); j++)
                putchar(str[j]);
            for (size_t j = i; j < strlen(str) - 1; j++)
                putchar('\b');
            i++;
            continue;
        } else if (ch == '\r') {
            i = strlen(str);
            putchar('\n');
            str[i] = '\n';
            str[++i] = '\0';
            return str;
        }

        if (strlen(str) > i) {
            for (size_t j = strlen(str); i <= j; j--) {
                str[j + 1] = str[j];
                if (j == 0)
                    break;
            }
            for (size_t j = i; j < strlen(str); j++)
                putchar(str[j]);
            for (size_t j = i; j < strlen(str); j++)
                putchar('\b');
        }

        putchar(ch);
        str[i] = ch;
        i += 1;
    }
    str[size] = '\0';
    return str;
}
