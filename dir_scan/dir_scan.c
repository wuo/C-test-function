#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void printdir(char *dir, int depth) {
    DIR* dp;
    struct dirent* entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "can not open directory: %s\n", dir);
        return;
    }

    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", entry->d_name) == 0 ||
                    strcmp("..", entry->d_name) == 0)
                continue;
            //note the meaning of %*s
            printf("%*s%s/\n", depth, " ", entry->d_name);
            printdir(entry->d_name, depth + 4);
        } else {
            printf("%*s%s\n", depth, " ", entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

main() {
    printf("Directory scan of /home:\n");
    printdir("/home", 0);
    printf("done\n");
    exit(0);
}