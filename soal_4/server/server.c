#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 8080
#define MAX_ANIME_COUNT 1000
#define MAX_FIELDS 4
#define MAX_FIELD_LENGTH 100
#define CSV_FILENAME "/home/nayla/soal_4/myanimelist.csv"
#define CHANGE_LOG_FILENAME "/home/nayla/soal_4/change.log"

typedef struct {
    char day[MAX_FIELD_LENGTH];
    char genre[MAX_FIELD_LENGTH];
    char title[MAX_FIELD_LENGTH];
    char status[MAX_FIELD_LENGTH];
} Anime;

Anime animeList[MAX_ANIME_COUNT];
int animeCount = 0;

void readCSV() {
    FILE *file = fopen(CSV_FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    
    char line[MAX_FIELDS * MAX_FIELD_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%[^,],%s", animeList[animeCount].day, animeList[animeCount].genre, animeList[animeCount].title, animeList[animeCount].status);
        animeCount++;
    }
    fclose(file);
}

void writeToChangeLog(char *type, char *message) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char date_str[20];
    strftime(date_str, sizeof(date_str), "[%d/%m/%y]", tm_now);

    FILE *file = fopen(CHANGE_LOG_FILENAME, "a");
    if (file == NULL) {
        printf("Error opening change log file.\n");
        return;
    }

    fprintf(file, "%s [%s] %s\n", date_str, type, message);
    fclose(file);
}

void sendAnimeList(int new_socket) {
    char response[1024] = {0};
    for (int i = 0; i < animeCount; i++) {
        strcat(response, animeList[i].title);
        strcat(response, "\n");
    }
    send(new_socket, response, strlen(response), 0);
}

void SendAnimeByGenre(char *buffer, int new_socket) {
    char *genrePtr = strstr(buffer, "genre ");
    if (genrePtr != NULL) {
        genrePtr += strlen("genre ");

        char genre[MAX_FIELD_LENGTH];
        sscanf(genrePtr, "%[^\n]", genre);

        char response[1024] = {0};
        for (int i = 0; i < animeCount; i++) {
            if (strstr(animeList[i].genre, genre) != NULL) {
                strcat(response, animeList[i].title);
                strcat(response, "\n");
            }
        }
        send(new_socket, response, strlen(response), 0);
    } else {
        send(new_socket, "Invalid Command", strlen("Invalid Command"), 0);
    }
}

void sendAnimeByDay(int new_socket, char *day) {
    char response[1024] = {0};
    for (int i = 0; i < animeCount; i++) {
        if (strcmp(animeList[i].day, day) == 0) {
            strcat(response, animeList[i].title);
            strcat(response, "\n");
        }
    }
    send(new_socket, response, strlen(response), 0);
}

void sendAnimeByStatus(int new_socket, char *input) {
    char response[1024] = {0};
    int found = 0;
        for (int i = 0; i < animeCount; i++) {
            if (strcmp(animeList[i].title, input) == 0) {
                strcat(response, animeList[i].status);
                strcat(response, "\n");
                found = 1;
                break;
            } else if (strcmp(animeList[i].status, input) == 0) {
                strcat(response, animeList[i].title);
                strcat(response, "\n");
            }
        }
        send(new_socket, response, strlen(response), 0);
    }

void addAnime(int new_socket,char *animeDetails) {
    if (animeCount >= MAX_ANIME_COUNT) {
        printf("Anime list is full. Cannot add more.\n");
        return;
    }

    char day[MAX_FIELD_LENGTH], genre[MAX_FIELD_LENGTH], title[MAX_FIELD_LENGTH], status[MAX_FIELD_LENGTH];
    sscanf(animeDetails, "%[^,],%[^,],%[^,],%s", day, genre, title, status);

    strcpy(animeList[animeCount].day, day);
    strcpy(animeList[animeCount].genre, genre);
    strcpy(animeList[animeCount].title, title);
    strcpy(animeList[animeCount].status, status);

    animeCount++;
    char logMessage[1024];
    sprintf(logMessage, "%s berhasil ditambahkan", title);
    writeToChangeLog("ADD", logMessage);
    send(new_socket, "anime berhasil ditambahkan.\n", strlen("anime berhasil ditambahkan.\n"), 0);
}

void editAnime(char *animeTitle, char *animeDetails, int new_socket) {
    char *token;
    char oldTitle[MAX_FIELD_LENGTH], oldDay[MAX_FIELD_LENGTH], oldGenre[MAX_FIELD_LENGTH], oldStatus[MAX_FIELD_LENGTH], newDay[MAX_FIELD_LENGTH], newGenre[MAX_FIELD_LENGTH], newTitle[MAX_FIELD_LENGTH], newStatus[MAX_FIELD_LENGTH];
    strcpy(oldTitle, animeTitle); // Gunakan judul lama sebagai acuan untuk pencarian

    token = strtok(animeDetails, ",");
    if (token != NULL) {
        strcpy(newDay, token);
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(newGenre, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(newTitle, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(newStatus, token);

                    int found = 0;
                    for (int i = 0; i < animeCount; i++) {
                        if (strcmp(animeList[i].title, oldTitle) == 0) {
                            found = 1;

                            strcpy(oldDay, animeList[i].day);
                            strcpy(oldGenre, animeList[i].genre);
                            strcpy(oldTitle, animeList[i].title);
                            strcpy(oldStatus, animeList[i].status);
                            
                            strcpy(animeList[i].day, newDay);
                            strcpy(animeList[i].genre, newGenre);
                            strcpy(animeList[i].title, newTitle);
                            strcpy(animeList[i].status, newStatus);
                            
                            char logMessage[1024];
                            sprintf(logMessage, "%s,%s,%s,%s diubah menjadi %s,%s,%s,%s", oldDay, oldGenre, oldTitle, oldStatus, newDay, newGenre, newTitle, newStatus);
                            writeToChangeLog("EDIT", logMessage);

                            send(new_socket, "anime berhasil diedit\n", strlen("anime berhasil diedit\n"), 0);
                            break; 
                        }
                    }

                    if (!found) {
                        char response[1024];
                        sprintf(response, "Anime not found: %s\n", oldTitle);
                        send(new_socket, response, strlen(response), 0);
                    }
                }
            }
        }
    }
}

void deleteAnime(int new_socket,char *animeTitle) {
    for (int i = 0; i < animeCount; i++) {
        if (strcmp(animeList[i].title, animeTitle) == 0) {
            for (int j = i; j < animeCount - 1; j++) {
                strcpy(animeList[j].day, animeList[j + 1].day);
                strcpy(animeList[j].genre, animeList[j + 1].genre);
                strcpy(animeList[j].title, animeList[j + 1].title);
                strcpy(animeList[j].status, animeList[j + 1].status);
            }

            animeCount--;
            char logMessage[1024];
            sprintf(logMessage, "%s berhasil dihapus", animeTitle);
            writeToChangeLog("DEL", logMessage);
            send(new_socket, "anime berhasil dihapus.\n", strlen("anime berhasil dihapus.\n"), 0);
            return;
        }
    }
}


int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    readCSV();

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

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (1) {
        valread = read(new_socket, buffer, 1024);
        if (valread < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "exit\n") == 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Received command from client: %s", buffer);

        if (strncmp(buffer, "tampilkan", 9) == 0) {
            sendAnimeList(new_socket);
        } else if (strncmp(buffer, "genre", 5) == 0) {
            SendAnimeByGenre(buffer, new_socket);
        } else if (strncmp(buffer, "hari", 4) == 0) {
            char day[MAX_FIELD_LENGTH];
            sscanf(buffer, "hari %s", day);
            sendAnimeByDay(new_socket, day);
        } else if (strncmp(buffer, "status ", 7) == 0) {
            char input[MAX_FIELD_LENGTH];
            sscanf(buffer, "%*s %[^\n]", input);
            sendAnimeByStatus(new_socket, input);
        } else if (strncmp(buffer, "add", 3) == 0) {
            char animeDetails[1024];
            sscanf(buffer, "add %[^\n]", animeDetails);
            addAnime(new_socket,animeDetails);
        } else if (strncmp(buffer, "edit", 4) == 0) {
            char animeTitle[MAX_FIELD_LENGTH], animeDetails[1024];
            sscanf(buffer, "edit %[^,], %[^\n]", animeTitle, animeDetails);
            editAnime(animeTitle, animeDetails,new_socket);
        } else if (strncmp(buffer, "delete", 6) == 0) {
            char animeTitle[MAX_FIELD_LENGTH];
            sscanf(buffer, "delete %[^\n]", animeTitle);
            deleteAnime(new_socket,animeTitle);
        } else {
            send(new_socket, "Invalid Command\n", strlen("Invalid Command\n"), 0);
        }
        memset(buffer, 0, sizeof(buffer));
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
