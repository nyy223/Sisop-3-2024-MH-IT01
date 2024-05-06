#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "actions.c"

#define PORT 8080

void logMessage(const char* source, const char* command, const char* info) {
    FILE* logFile = fopen("race.log", "a");
    time_t now = time(0);
    struct tm *tm = localtime(&now);
    fprintf(logFile, "[%s] [%02d/%02d/%04d %02d:%02d:%02d]: [%s] [%s]\n", source, tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900, tm->tm_hour, tm->tm_min, tm->tm_sec, command, info);
    fclose(logFile);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char response[1024];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }

        valread = read(new_socket, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0';
            char *command = strtok(buffer, " ");
            char *value = strtok(NULL, " ");

            if (command && value) {
                if (strcmp(command, "Gap") == 0) {
                    float gap = atof(value);
                    strcpy(response, checkGap(gap));
                } else if (strcmp(command, "Fuel") == 0) {
                    float fuel = atof(value);
                    strcpy(response, checkFuel(fuel));
                } else if (strcmp(command, "Tire") == 0) {
                    int tireWear = atoi(value);
                    strcpy(response, checkTire(tireWear));
                } else if (strcmp(command, "TireChange") == 0) {
                    strcpy(response, tireChange(value));
                } else {
                    strcpy(response, "Unknown command");
                }
                logMessage("Driver", command, value);
                logMessage("Paddock", command, response);
                send(new_socket, response, strlen(response), 0);
            }
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
