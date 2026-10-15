#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd, connfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Creating socket file descriptor (SOCK_STREAM = TCP)
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Allow quick restart on the same port
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept one client connection
    if ((connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0) {
        perror("accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int n = recv(connfd, buffer, MAXLINE - 1, 0);
    buffer[n] = '\0';
    printf("Client: %s\n", buffer);

    send(connfd, hello, strlen(hello), 0);
    printf("Hello message sent.\n");

    close(connfd);
    close(sockfd);
    return 0;
}
