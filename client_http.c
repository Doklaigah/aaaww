#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 2048

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    while (1) {
        char request[] =
            "GET /beacon HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "\r\n";

        send(sock, request, strlen(request), 0);

        memset(buffer, 0, BUFFER_SIZE);
        recv(sock, buffer, BUFFER_SIZE - 1, 0);

        sleep(5);
    }

    close(sock);
    return 0;
}
