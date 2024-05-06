#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHM_NAME "/shm_csv_files"
#define SHM_SIZE 1024 * 1024

int main() {
    DIR *d;
    struct dirent *dir;
    int shm_fd;
    char *shm_base, *shm_ptr;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Failed to open shared memory");
        return EXIT_FAILURE;
    }
    ftruncate(shm_fd, SHM_SIZE);

    shm_base = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
        perror("Failed to map shared memory");
        close(shm_fd);
        return EXIT_FAILURE;
    }

    memset(shm_base, 0, SHM_SIZE);
    shm_ptr = shm_base;

    d = opendir("./new-data");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".csv") &&
                (strstr(dir->d_name, "trashcan") || strstr(dir->d_name, "parkinglot"))) {
                char filePath[1024];
                sprintf(filePath, "./new-data/%s", dir->d_name);

                FILE *file = fopen(filePath, "r");
                if (file == NULL) {
                    perror("Failed to open file");
                    continue;
                }

                int length = sprintf(shm_ptr, "%s\n", dir->d_name);
                shm_ptr += length;

                char line[1024];
                while (fgets(line, sizeof(line), file)) {
                    if (strchr(line, ',') == NULL) continue;
                    line[strcspn(line, "\n")] = 0;

                    length = snprintf(shm_ptr, SHM_SIZE - (shm_ptr - shm_base), "%s\n", line);
                    if (length > SHM_SIZE - (shm_ptr - shm_base)) {
                        fprintf(stderr, "Shared memory is full. Cannot store more data.\n");
                        break;
                    }
                    shm_ptr += length;
                }

                *shm_ptr++ = '\n';

                fclose(file);
            } else {
                char filePath[1024];
                sprintf(filePath, "./new-data/%s", dir->d_name);
                remove(filePath);
            }
        }
        closedir(d);
    }

    munmap(shm_base, SHM_SIZE);
    close(shm_fd);

    return 0;
}
