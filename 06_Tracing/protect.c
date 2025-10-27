// protect.c
#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

typedef int (*unlink_t)(const char *pathname);

int unlink(const char *pathname) {
    if (strstr(pathname, "PROTECT")) {
        fprintf(stderr, "Защищенный файл '%s' не может быть удален.\n", pathname);
        errno = EPERM;
        return -1;
    }

    unlink_t original_unlink = dlsym(RTLD_NEXT, "unlink");
    return original_unlink(pathname);
}
