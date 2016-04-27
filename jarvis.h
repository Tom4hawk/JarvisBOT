#ifndef JARVISBOT_H
	#define JARVISBOT_H
	
	#define MSGSIZE 1024
	
	void connectToServer(char *addr, char *port);
	void loginToIRC(char* nick, char*  nick_password, char*  channel);
    void receiveData();
	/* exported variables
	extern int opterr, optind, optopt;
	extern char *optarg;*/

	/* exported function
	int getopt(int, char **, char *);*/
#endif
