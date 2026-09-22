#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    struct sockaddr_in server_address;
    int server_fd;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8083);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(server_fd,
             (struct sockaddr *)&server_address,
             sizeof(server_address)) == -1)
    {

        perror("bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) == -1)
    {

        perror("lisen failed");
        close(server_fd);
        return 1;
    }

    int client_fd;
    client_fd = accept(server_fd, NULL, NULL);

    if (client_fd == -1)
    {
        perror("lisen failed");
        close(server_fd);
        return 1;
    }

    char buffer[4096];

    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received == -1)
    {
        perror("recv failed");
        close(server_fd);
        return 1;
    }

    buffer[bytes_received] = '\0';

    FILE *file = fopen("index.html", "rb");

    if (file == NULL)
    {
        perror("File failed to open");
        close(client_fd);
        close(server_fd);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *body = malloc(file_size + 1);

    fread(body, 1, file_size, file);
    body[file_size] = '\0';

    char response[1024];
    const char *header = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html\r\n"
                         "Content-Length: %ld\r\n"
                         "Connection: close\r\n"
                         "\r\n";

    int head_len = snprintf(response, sizeof(response), header, file_size);
    send(client_fd, response, head_len, 0);
    send(client_fd, body, file_size, 0);

    printf("Browser connected! Client FD: %d\n", client_fd);

    printf("Server run on http://localhost:8083 \n");

    close(server_fd);
    close(client_fd);

    return 0;
}