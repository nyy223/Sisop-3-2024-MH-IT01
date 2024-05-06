#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int convert_to_number(char* word) {
    if (strcmp(word, "satu") == 0) return 1;
    if (strcmp(word, "dua") == 0) return 2;
    if (strcmp(word, "tiga") == 0) return 3;
    if (strcmp(word, "empat") == 0) return 4;
    if (strcmp(word, "lima") == 0) return 5;
    if (strcmp(word, "enam") == 0) return 6;
    if (strcmp(word, "tujuh") == 0) return 7;
    if (strcmp(word, "delapan") == 0) return 8;
    if (strcmp(word, "sembilan") == 0) return 9;
    return -1;
}

const char* convert_to_words(int number) {
    static const char* words[] = {
        "nol", "satu", "dua", "tiga", "empat",
        "lima", "enam", "tujuh", "delapan", "sembilan",
        "sepuluh", "sebelas", "dua belas", "tiga belas",
        "empat belas", "lima belas", "enam belas",
        "tujuh belas", "delapan belas", "sembilan belas",
        "dua puluh"
    };
    if (number <= 20) {
        return words[number];
    }
    static char buffer[50];
    if (number < 100) {
        sprintf(buffer, "%s puluh %s", words[number / 10], words[number % 10]);
    } else {
        sprintf(buffer, "lebih dari sembilan puluh sembilan");
    }
    return buffer;
}

void log_result(const char* type, const char* message) {
    FILE* file = fopen("histori.log", "a");
    if (!file) {
        perror("Failed to open log file");
        return;
    }
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    char time_str[26];
    strftime(time_str, 26, "%d/%m/%y %H:%M:%S", tm_info);
    fprintf(file, "[%s] [%s] %s\n", time_str, type, message);
    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s -kali|-tambah|-kurang|-bagi\n", argv[0]);
        return 1;
    }

    char operation[10];
    if (strcmp(argv[1], "-kali") == 0) {
        strcpy(operation, "KALI");
    } else if (strcmp(argv[1], "-tambah") == 0) {
        strcpy(operation, "TAMBAH");
    } else if (strcmp(argv[1], "-kurang") == 0) {
        strcpy(operation, "KURANG");
    } else if (strcmp(argv[1], "-bagi") == 0) {
        strcpy(operation, "BAGI");
    } else {
        printf("Invalid operation\n");
        return 1;
    }

    char input1[20], input2[20];
    printf("Enter two numbers in words (e.g., 'tiga tujuh'): ");
    scanf("%s %s", input1, input2);

    int num1 = convert_to_number(input1);
    int num2 = convert_to_number(input2);
    if (num1 == -1 || num2 == -1) {
        printf("Invalid input\n");
        return 1;
    }

    int parent_to_child[2];
    int child_to_parent[2];
    pipe(parent_to_child);
    pipe(child_to_parent);

    pid_t pid = fork();

    if (pid == 0) {
        // Child Process
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        int result;
        read(parent_to_child[0], &result, sizeof(result));
        close(parent_to_child[0]);

        printf("Child: Received result = %d\n", result);  // Diagnostic message

        char message[100];
        if (result < 0) {
            sprintf(message, "ERROR pada %s.", operation);
        } else {
            snprintf(message, 100, "hasil %s %s dan %s adalah %s.",
                     operation, input1, input2, convert_to_words(result));
        }

        write(child_to_parent[1], message, strlen(message) + 1);
        close(child_to_parent[1]);
    } else {
        // Parent Process
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        int result;
        if (strcmp(operation, "KALI") == 0) {
            result = num1 * num2;
        } else if (strcmp(operation, "TAMBAH") == 0) {
            result = num1 + num2;
        } else if (strcmp(operation, "KURANG") == 0) {
            result = num1 - num2;
        } else if (strcmp(operation, "BAGI") == 0) {
            result = num1 / num2;
        }

        if (result < 0) {
            result = -1;
        }

        printf("Parent: Calculated result = %d\n", result);  // Diagnostic message

        write(parent_to_child[1], &result, sizeof(result));
        close(parent_to_child[1]);

        char message[100];
        read(child_to_parent[0], message, sizeof(message));
        close(child_to_parent[0]);

        printf("%s\n", message);
        log_result(operation, message);
    }

    return 0;
}

