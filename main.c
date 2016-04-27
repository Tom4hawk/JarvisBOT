#include <stdlib.h>
#include <stdio.h>
#include <string.h>		/* memset */
#include <unistd.h>		/* close */
/*
 * Network 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdarg.h>

#define MSGSIZE 1024


int connectionSocket;
char sbuf[MSGSIZE];

int sendData(char *msg) {
  int len = strlen(msg);
  int bytes_sent = send(connectionSocket,msg,len,0);

  printf(">>%s\n", msg);
  
  return bytes_sent;
}

void sendToServer(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(sbuf, MSGSIZE, fmt, ap);
    va_end(ap);
    printf("<< %s", sbuf);
    sendData(sbuf);
}

void receiveData(){
    int numbytes = recv(connectionSocket, sbuf, MSGSIZE - 1, 0);
    
    sbuf[numbytes] = '\0';

    printf("<<%s\n", sbuf);

    if(strncmp(sbuf, "PING", 4) == 0){
        sendData("PONG");
    } else if(numbytes == 0){
        fprintf(stderr, "======== Lost connection ========");
        close(connectionSocket);
    }
}

void connectToServer(char *addr, char *port)
{
    struct addrinfo hints, *res;
    int error, i;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((error = getaddrinfo(addr, port, &hints, &res)) != 0) {
	    fprintf(stderr, "Getaddrinfo: %s\n", gai_strerror(error));
    }

    if ((connectionSocket =
	 socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    {
	    fprintf(stderr, "Socket creation\n");
    }

    if (connect(connectionSocket, res->ai_addr, res->ai_addrlen) != 0) {
	    close(connectionSocket);
	    fprintf(stderr, "Couldn't connect\n");
    }
    
    for(i=0; i<3; ++i)
        receiveData();

    freeaddrinfo(res);
}

int main()
{
    /*
     * TODO: read from configuration file 
     */
    char *node = "chat.freenode.net";
    char *port = "6667";
    char *nick = "JarvisBOT";
    char *channel = "#klodnicka16/10 letMeIn";

    connectToServer(node, port);
    /*
     * loginToIRC(nick, channel) 
     */

    sendToServer("USER %s 0 0 :%s\r\n", nick, nick);
    sendToServer("NICK %s\r\n", nick);
    sendToServer("JOIN %s\r\n", channel);

    while (1) {
    	receiveData();
    }


    return 0;
}
