#include <stdio.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */
/* Network */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdarg.h>


int connection;
struct addrinfo hints, *res;
char sbuf[512];

void sendToServer(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(sbuf, 512, fmt, ap);
    va_end(ap);
    printf("<< %s", sbuf);
    write(connection, sbuf, strlen(sbuf));
}


void connectToServer(char *addr, char *port){
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(addr, port, &hints, &res);
    connection = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(connection, res->ai_addr, res->ai_addrlen);
}

int main(){
	int sl;
	/* TODO: read from configuration file */
    char *node = "chat.freenode.net";
    char *port = "6667";
	char *nick = "test_jarvis";
    char *channel = "#testjarvis1234566";

	connectToServer(node, port);
	/*loginToIRC(nick, channel)*/

    sendToServer("USER %s 0 0 :%s\r\n", nick, nick);
    sendToServer("NICK %s\r\n", nick);

	while ((sl = read(connection, sbuf, 512))) {
		printf("Wpisano:\n%s\n\n", sbuf);
	}

	freeaddrinfo(res);

	return 0;
}
