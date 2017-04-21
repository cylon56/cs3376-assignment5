// file: onepipe.cpp 
// author: M. Amine Belkoura 
// date: 03/04/2015 
// purpose: CS3376 
// description: 
//   this program executes "ls -ltr | grep 3376 | wc -l", by dividing the two command among the child and parent process 

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 

int main(int argc, char **argv)
{ 
int status; 
int childpid1, childpid2, childpid3; 
char *cat_args[] = {"ls", "-ltr", NULL}; 
char *grep_args[] = {"grep", "3376", NULL}; 
char *wc_args[]= {"wc", "-l", NULL};

// create one pipe to send the output of "ls" process to "grep" process 
int pipe1[2];
int pipe2[2];

pipe(pipe1);
pipe(pipe2);


// fork the first child (to execute cat) 
if((childpid1 = fork()) == -1)
	{ 
	perror("Error creating a child process"); 
	exit(1); 
	}

if (childpid1 == 0) 
{ // replace cat's stdout with write part of 1st pipe
	
	//fork second child to execute wc
	if((childpid2 = fork()) == -1)
	{
	perror("Error creating second child process");
	exit(1);
	}
	
	//replace grep's stdout with write of 1st pipe and 
	if(childpid2 == 0)
	{
		//fork third child
		if((childpid = fork()) == -1)
		{	
		perror("Error creating third child process");
		exit(1);
		}

		if(childpid3 == 0)
		{

		dup2(pipe2[1], 1);

		close(pipe2[0]);
		close(pipe2[1]);
	
		execvp(*wc_args, wc_args);
		exit(0);
		}

		else
		{

	dup2(pipe1[1], 1); 
	dup2(pipe2[0], 0);

	// close all pipes (very important!); end we're using was safely copied 
	close(pipe1[0]); 
	close(pipe1[1]); 
	execvp(*cat_args, cat_args); 
	exit(0);
		}

	}

	else
	{
	
	dup2(pipe1[0], 0); 
	close(pipe1[0]); 
	close(pipe1[1]); 
	execvp(*grep_args, grep_args); 
	}
}
	
else 
	{ 
	//parent does nothing
	sleep(1);
	} 
	
}
