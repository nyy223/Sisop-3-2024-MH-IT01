#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/shm_csv_files"
#define SHM_SIZE 1024 * 1024
#define MAX_LINE_LENGTH 1024

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
    while (*ptr != '\0') {
        char fileName[MAX_LINE_LENGTH];
        sscanf(ptr, "%[^\n]", fileName);
        ptr += strlen(fileName) + 1;

        char bestName[MAX_LINE_LENGTH];
        float bestRating = 0.0, currentRating;

        while (*ptr == '\n') ptr++;

        while (*ptr != '\0' && *ptr != '\n') {
            char name[MAX_LINE_LENGTH];
            sscanf(ptr, "%[^,],%f", name, &currentRating);
            if (currentRating > bestRating) {
                bestRating = currentRating;
                strcpy(bestName, name);
            }
            while (*ptr != '\n' && *ptr != '\0') ptr++;
            if (*ptr == '\n') ptr++;
        }

        char *type = strstr(fileName, "trashcan") ? "Trash Can" : "Parking Lot";

        printf("Type: %s\nFilename: %s\n-------------------\nName: %s\nRating: %.1f\n\n", type, fileName, bestName, bestRating);

        while (*ptr == '\n') ptr++;
    }

    munmap(shm_base, SHM_SIZE);
    close(shm_fd);

    return EXIT_SUCCESS;
}
