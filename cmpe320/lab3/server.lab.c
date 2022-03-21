#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //close()

#include <sys/socket.h> // socket(), connect(), send(), recv()
#include <arpa/inet.h>  // sockaddr_in, inet_addr()

#define BUFSIZE 64
#define PENDING 16

#define MAX_CANDIDATE 20

// Structure for the candidates
typedef struct {
	char text[BUFSIZE];
	int tally;
} vote_t;

vote_t response[MAX_CANDIDATE];

void vote_tally(char* new_vote) {
    int i = 0;
    for(i = 0; i < MAX_CANDIDATE; i++) {
        if(strcmp("", response[i].text) == 0) {
            break;
        }
        if(strcmp(new_vote, response[i].text) == 0) {
            // if they're the same, update tally
            response[i].tally++;
            return;
        }
        // It's not this one
    }
    // If you got here, its not in the array
    strcpy(response[i].text, new_vote);
    response[i].tally++;
    printf("New response, number %d: %s\n", i+1, response[i].text);
}

void vote_printout() {
    printf("The current votes are:\n");
    for(int i = 0; i < MAX_CANDIDATE; i++){
        if(strcmp("", response[i].text) == 0)
            break;
        printf("# %s: %d\n\n", response[i].text, response[i].tally);
    }
}

void die(char *msg) {
    fprintf(stderr, "DEAD: %s\n", msg);
    exit(1);
}

void handle(int sock) {
    char buffer[BUFSIZE] = "";
    int size = 0;

    if ((size = recv(sock, buffer, BUFSIZE, 0)) < 0)
        die("recv() failed");
    
    if(strncmp(buffer, "dead", 4) == 0) { 
        if(fork() == 0) {
            exit(0);
        } else {
            return;
        }
    }

    vote_tally(buffer);
    vote_printout();
    
    while (size > 0) {
        if(send(sock, buffer, size, 0) != size)
            die("send() failed");
        if((size = recv(sock, buffer, BUFSIZE, 0)) < 0)
            die("recv() failed");
    }

    close(sock);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <port num>\n", argv[0]);
        exit(1);
    }

    int sock;

    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        die("socket() failed");

    int port_num = atoi(argv[1]);
    struct sockaddr_in serv_addr; // server address
    serv_addr.sin_family       = AF_INET; 
    serv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
    serv_addr.sin_port         = htons(port_num);

    if(bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        die("bind() failed");

    if(listen(sock, PENDING) < 0)
        die("listen() failed");

    struct sockaddr_in client_addr;
    unsigned int client_len;

    int i = 0;
    while (1) {
        int client_sock;

        if ((client_sock = accept(sock, (struct sockaddr *) &client_addr, &client_len)) < 0)
            die("accept() failed");
        
        printf("Handling client: %s\n", inet_ntoa(client_addr.sin_addr));
        
        handle(client_sock);       
    }
}