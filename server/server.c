/* Creates a datagram server. The port number is passed as an argument. This
server runs forever */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

void error(char *msg)
   {
	perror(msg);
	exit(0);
   }


int fire()
{	int pid = fork();
	if ( pid == 0 ) {
		//printf( "This is being printed from the child process and its id is %d\n", (int)getpid() );
		//This section will be used from the client's computer to send the code to another computer.
	} 
	else {
		printf( "This is being printed in the parent process:\n"
		        " - the process identifier (pid) of the child is %d\n", pid );
		printf( "Parent's own id is %d\n", (int)getpid() );
	}

	return pid;
}

int main(int argc, char *argv[])
{
	int sock, length, clientlen, n;
	int rc;
       ///Declare the sockaddr_in structures for the client and the server
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buf[1024];
	
	if (argc < 2) {
	 		fprintf(stderr, "ERROR, no port provided\n");
			exit(0);
         	       }

	///The socket call which returns a file descriptor
	sock=socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0) 
	  error("Opening socket");

	length = sizeof(server);

	///Initializes the server socket structure to zero, as a replacement we can also
	///use memset
	bzero(&server,length);

	///We initialize the values for all the individual fields of the server socket
	///structure remember to make use of the INADDR_ANY to assign the
	///sin_addr.s_addr field and please convert the port number obtained from the
	///command line to network byte order
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(atoi(argv[1]));

	///bind system call
	if (bind(sock,(struct sockaddr *)&server,length)<0)
		error("binding");

	clientlen = sizeof(struct sockaddr_in);
        

		
		///ready to receive a packet from the client, the fourth parameter is by
		///default zero
		n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&clientlen);
	
		if (n < 0) 
		  error("recvfrom");

		//writes output to the screen
		write(1,"Received a datagram: ",21);
		//write(1,buf,n); 
		//writes output to the screen

		//test = buf;

		puts(buf);
		if(strcmp(buf,"fork()"))
		{	
			rc = fire();
			}		

		///sends a packet to the client acknowledging it
		printf("Please enter the message: ");
		//This initializes the buffer with 0, we can also use memset as a replacement function
		bzero(buf,256);
		//reads the value from the keyboard, stdin = keyboard
		//buf = rc ;
		fgets(buf,255,stdin);
		n = sendto(sock,buf,strlen(buf),0,(struct sockaddr *)&client,clientlen);
		
		if (n < 0) 
		  error("sendto");


		///closes the file descriptor

		close(sock);

}
