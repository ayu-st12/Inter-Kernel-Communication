#include <stdio.h>
int main() {
	
	int pid = fork();
	if ( pid == 0 ) {
		//printf( "This is being printed from the child process and its id is %d\n", (int)getpid() );
		//This section will be used from the client's computer to send the code to another computer.
	} 
	else {
		printf( "This is being printed in the parent process:\n"
		        " - the process identifier (pid) of the child is %d\n", pid );
		printf( "Parent's own id is %d\n", (int)getpid() );
	}

	return 0;
}
