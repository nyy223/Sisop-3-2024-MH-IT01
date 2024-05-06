#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

void sendCommand(int sock, char *command) {
    send(sock, command, strlen(command), 0);
}

void receiveResponse(int sock) {
    char buffer[1024] = {0};
    if (recv(sock, buffer, 1024, 0) < 0) {
        printf("\nRead error\n");
        return;
    }
    printf("Server:\n%s\n", buffer);
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char command[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    while (1) {
        printf("Enter command (type 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);

        sendCommand(sock, command);

        if (strcmp(command, "exit\n") == 0) {
            printf("Exiting...\n");
            break;
        }
        receiveResponse(sock);
    }
    close(sock);
    return 0;
}

