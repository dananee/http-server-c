#include <stdio.h>

#include <sys/socket.h>

#include <unistd.h>
#include <netinet/in.h>

int main()
{
    struct sockaddr_in server_address;
    int server_fd;

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (bind(server_fd,
             (struct sockaddr *)&server_address,
             sizeof(server_address)) == -1)
    {

        perror("bind failed");
        close(server_fd);
        return 1;
    }

    printf("Succss %d", server_fd);
    close(server_fd);

    return 0;
}