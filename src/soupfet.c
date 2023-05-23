#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ascii();
int os();
void kernel();
void host();
void pkg();

int main() {
    ascii();

    printf("\e[1;34m%s\e[m\e[1m@\e[m", getenv("USER"));
    host();
    printf("▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n\n");

    printf("\e[1;31mos\e[m       ");
    os();

    printf("\e[1;34mkernel\e[m   ");
    kernel();

    printf("\e[1;35msh\e[m       %s\n", getenv("SHELL"));

    printf("\e[1;31mwm\e[m       %s\n", getenv("DESKTOP_SESSION"));

    printf("\e[1;33mpkgs\e[m     ");
    fflush(stdout);
    pkg();

    return 0;
}

int os() {
    char* os_path = "/etc/os-release";
    char* lsb_path = "/etc/lsb-release";
    char* path = NULL;

    if (!access(os_path, F_OK)) {
        path = os_path;
    } else if (!access(lsb_path, F_OK)) {
        path = lsb_path;
    } else {
        printf("Linux\n");
        return 1;
    }

    FILE *fp;
    char line[40];
    fp = fopen(path, "r");

    if (fp == NULL) {
        return 1;
    }

    fgets(line, 40, fp);
    char* name = strchr(line, '=') + 1;

    printf("%s", name);
    fclose(fp);
    return 0;
}

void kernel() {
    FILE *fp;
    char line[40];
    fp = fopen("/proc/version", "r");

    fgets(line, 40, fp);
    char* i = strstr(line, "version") + strlen("version") + 1;
    char* f = strchr(i, ' ');
    size_t ln = f - i;

    char ver[ln + 1];
    strncpy(ver, i, ln);
    ver[ln] = '\0';

    printf("%s\n", ver);
    fclose(fp);
}

void host() {
    FILE *fp;
    char line[40];
    fp = fopen("/etc/hostname", "r");

    fgets(line, 40, fp);
    printf("\e[1;34m%s\e[m\n", line);
    fclose(fp);
}

void pkg() {
    char *pkgcount;

    if (!access("/usr/bin/pacman", F_OK)) {
        pkgcount = "pacman -Q | wc -l";
    } else if (!access("/usr/bin/apt", F_OK)) {
        pkgcount = "dpkg --list | wc -l";
    } else if (!access("/usr/bin/xbps-install", F_OK)) {
        pkgcount = "xbps-query -l | wc -l";
    } else if (!access("/usr/bin/dnf", F_OK)) {
        pkgcount = "dnf list installed | wc -l";
    } else {
        pkgcount = "true";
    }
    system(pkgcount);
}

void ascii() {
    printf("\n"
    "    \\    /\\\n"
    "     )  ( ')\n"
    "    (  /  )\n"
    "     \\(__)|\n\n");
}