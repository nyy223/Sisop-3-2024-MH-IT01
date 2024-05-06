#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SHM_NAME "/shm_csv_files"
#define SHM_SIZE 1024 * 1024

int main() {
    int shm_fd;
    char *shm_base, *ptr;

    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("Failed to open shared memory");
        return EXIT_FAILURE;
    }

    shm_base = mmap(0, SHM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
        perror("Failed to map shared memory");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    ptr = shm_base;
    char fileName[1024];

    while (ptr < shm_base + SHM_SIZE && *ptr != '\0') {
        if (sscanf(ptr, "%[^\n]\n", fileName) == 1) {
            if (strstr(fileName, ".csv")) {
                char source[1024], dest[1024];
                sprintf(source, "/home/kali/PraktikumSisop3/Soal1/new-data/%s", fileName);
                sprintf(dest, "/home/kali/PraktikumSisop3/Soal1/microservices/database/%s", fileName);

                if (access(source, F_OK) != -1) {
                    if (rename(source, dest) == 0) {
                        printf("Successfully moved file: %s\n", fileName);
                        FILE *logFile = fopen("/home/kali/PraktikumSisop3/Soal1/microservices/database/db.log", "a");
                        if (logFile) {
                            time_t now = time(NULL);
                            struct tm *t = localtime(&now);
                            const char* type = strstr(fileName, "trashcan") ? "Trash Can" : "Parking Lot";

                            fprintf(logFile, "[%02d/%02d/%04d %02d:%02d:%02d] [%s] [%s]\n",
                                    t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                                    t->tm_hour, t->tm_min, t->tm_sec,
                                    type,
                                    fileName);
                            fclose(logFile);
                        } else {
                            perror("Failed to open log file");
                        }
                    } else {
                        perror("Failed to move file");
                    }
                } else {
                    perror("File does not exist");
                }
            }
            ptr += strlen(fileName) + 1;
        } else {
            while (*ptr != '\n' && ptr < shm_base + SHM_SIZE) ptr++;
            ptr++;
        }
    }

    munmap(shm_base, SHM_SIZE);
    close(shm_fd);

    return EXIT_SUCCESS;
}
