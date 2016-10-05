/* UDP client in the internet domain */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

void error(char *);

int main(int argc, char *argv[])
{
	int sock, length, n;

	//socket structures
	struct sockaddr_in server, client;

	//hostent datastructure
	struct hostent *hp;
	char buffer[256];
	
	if (argc != 3) 
	{ 
		printf("Usage: server port\n");
		exit(1);
	}

	//specifies that it is a datagram socket
	//and the socket belongs to the INTERNET family
	
	sock= socket(AF_INET, SOCK_DGRAM, 0);
	
	if (sock < 0)
	 error("socket");

	//We initialize the individual fields of the sockaddr_in structure
	//to fill sin_family which takes AF_INET as the value
	server.sin_family = AF_INET;

	//returns the hostname in the form of a hostent structure
	hp = gethostbyname(argv[1]);
	
	if (hp==0) 
	  error("Unknown host");

	//The below function can also be replaced with memcopy
	//but please never use strcpy() it wont work!
	bcopy((char *)hp->h_addr,(char *)&server.sin_addr,hp->h_length);

	//We initialize the individual fields of the sockaddr_in structure
	//to fill sin_port which takes the port number as the value
	//which was given as a command line parameter, remember to convert
	//this value into host to network byte order, it is very important!
	

	server.sin_port = htons(atoi(argv[2]));
	length=sizeof(struct sockaddr_in);
	printf("Please enter the message: ");

	//This initializes the buffer with 0, we can also use memset as a replacement function
	bzero(buffer,256);
	
	//reads the value from the keyboard, stdin = keyboard
	fgets(buffer,255,stdin);

	//sends the buffer, to the server, the fourth parameter is by default zero.
	n=sendto(sock,buffer,strlen(buffer),0,&server,length);
	if (n < 0) 
	 error("Sendto");

	//receives the packet from the server which is stored in the buffer
	n = recvfrom(sock,buffer,256,0,&client, &length);
	if (n < 0)
	 error("recvfrom");

	write(1,"ANOTHER SYSTEM REPLIED: ",24);
	write(1,buffer,n);

	//closes the socket descriptor
	close(sock);
}

void error(char *msg)
{
perror(msg);
exit(0);
}

