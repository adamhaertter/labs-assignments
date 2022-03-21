#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //close()

#include <sys/socket.h> // socket(), connect(), send(), recv()
#include <arpa/inet.h>  // sockaddr_in, inet_addr()

#define BUFSIZE 64

void die(char *msg) {
    fprintf(stderr, "DEAD: %s\n", msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        fprintf(stderr, "Usage: %s <server ip> <port num> <message>\n", argv[0]);
        exit(1);
    }

    char *server_ip = argv[1];
    int port_num    = atoi(argv[2]);
    char *msg       = argv[3];

    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        die("socket() failed");

    struct sockaddr_in s_addr; // server address
    s_addr.sin_family       = AF_INET; // similar to PF_INET
    // inet_addr converts a IP string to some C struct that connect can understand
    s_addr.sin_addr.s_addr  = inet_addr(server_ip); // should be 127.0.0.1 from lab notes
    // htons fixes byte ordering (i.e. big/little endian) if needed
    s_addr.sin_port         = htons(port_num);

    connect(sock, (struct sockaddr *) &s_addr, sizeof(s_addr));

    int msg_len = strlen(msg);

    /* SEND the message to the server */
    send(sock, msg, msg_len, 0);

    int total_recv = 0; // counting how many bytes received from the server
    char buffer[BUFSIZE];

    while (total_recv < msg_len) { // the server echoes the msg back
        int rcvd;

        if ((rcvd = recv(sock, buffer, BUFSIZE-1, 0)) <= 0)
            die("recv() failed or connection closed"); //read the man page
        total_recv += rcvd;
        buffer[rcvd] = '\0';
        printf("%s", buffer);
    }

    close(sock);

    return 0;
}