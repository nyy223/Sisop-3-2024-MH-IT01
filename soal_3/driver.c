#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char command[1024];
    char *cmd = NULL;
    char *info = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            cmd = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            info = argv[++i];
        }
    }

    if (!cmd || !info) {
        if (argc == 3) {
            cmd = argv[1];
            info = argv[2];
        } else {
            printf("Usage: ./driver -c [command] -i [value] or ./driver [command] [value]\n");
            return -1;
        }
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    sprintf(command, "%s %s", cmd, info);
    send(sock, command, strlen(command), 0);
    valread = read(sock, buffer, 1024);
    printf("[Driver] : [%s] [%s]\n", cmd, info);
    printf("[Paddock]: [%s]\n", buffer);

    close(sock);
    return 0;
}
