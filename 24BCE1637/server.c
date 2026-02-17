#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    time_t current_time;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    printf("Socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("Bind successful\n");

    listen(server_fd, 5);
    printf("Server is listening...\n");

    addr_size = sizeof(client_addr);

    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    printf("Client connected\n");

    current_time = time(NULL);
    strcpy(buffer, ctime(&current_time));

    send(client_fd, buffer, strlen(buffer), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}

