#include "jarvis.h"

int main()
{
    char *node = "chat.freenode.net";
    char *port = "6667";
    char *nick = "JarvisBOT";
    char *nick_password = "JarvisBOT-hardbot";
    char *channel = "#klodnicka16/10 letMeIn";

    connectToServer(node, port);
    loginToIRC(nick, nick_password, channel);

    while (1) {
    	receiveData();
    }


    return 0;
}
