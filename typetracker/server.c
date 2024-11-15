#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include "include/login.h"
#include "include/signup.h"

#define PORT 8080
#define BUFFER_SIZE 100000

char *response_header =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n\r\n";

char *strsum(char *a, char *b){
    size_t length = strlen(a) + strlen(b) + 1;
    char *result = (char*)malloc(length);
    strcpy(result, a);
    strcat(result, b);
    return result;
}

void answer_submit(int client_socket, char *data){
    printf("%s\n", data);
    char *response_body = strsum("console/", data);
    char *response = strsum(response_header, response_body);
    write(client_socket, response, strlen(response));
    free(response);
}

void answer_login(int client_socket, char *data){
    printf("%s\n", data);
    char *response_body = login(data);
    char *response = strsum(response_header, response_body);
    write(client_socket, response, strlen(response));
    free(response);
}

void answer_signup(int client_socket, char *data){
    printf("%s\n", data);
    char *response_body = signup(data);
    char *response = strsum(response_header, response_body);
    write(client_socket, response, strlen(response));
    free(response);
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0) {
        perror("Failed to read from socket");
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';
    char *body = strstr(buffer, "\r\n\r\n");
    if (body) body += 4;
    char *data = body+5;
    if (strstr(buffer, "POST /submit") != NULL) {
        answer_submit(client_socket, data);
    } else if (strstr(buffer, "POST /login") != NULL){
        answer_login(client_socket, data);
    } else if (strstr(buffer, "POST /signup") != NULL){
        answer_signup(client_socket, data);
    } else if (strstr(buffer, "GET /") != NULL) {
        FILE *file = fopen("index.html", "r");
        if (file == NULL) {
            perror("index.html not found");
            close(client_socket);
            return;
        }

        char file_content[BUFFER_SIZE];
        fread(file_content, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        // 클라이언트로 응답 전송
        write(client_socket, response_header, strlen(response_header));
        write(client_socket, file_content, strlen(file_content));
    }
    close(client_socket);
}

void server_run(){
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓 바인딩
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // 소켓 리스닝
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on http://localhost:%d\n", PORT);

    // 클라이언트 요청 처리
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    }

int main() {
    server_run();
    return 0;
}
