
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <iostream>
#include <string.h>

//using namespace std;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
	std::cout << "Not enough arguements" << std::endl;
	return (0);
	}
	else if(argc > 6)
	{	
	std::cout<< "Too many arguements" <<  std::endl;
	return (0);
	}
int status;
int child1,child2,child3,child4;

int pipe1[2];
int pipe2[2];
int pipe3[2];
int pipe4[2];
	
pipe(pipe1);
pipe(pipe2);
pipe(pipe3);
pipe(pipe4);

char *part1;
char *part2;

if((child1 == fork()) == -1)
	{
	perror("error creating process");
	exit(1);
	}		
if(child1 == 0)
{
	if(argc >= 4)
	{
		if((child2 =fork()) == -1)
			{
			perror("error creating process");
			exit(1);
			}
		if(child2 == 0)
		{
			if(argc >= 5)
			{
				if((child3 =fork()) == -1)
				{
				perror("error creating process");
				exit(1);
				}
				
				if(child3 == 0)
				{
						if(argc == 6)
						{
							if((child4 = fork()) == -1)
							{
							perror("error creating process");
							exit(1);
							}
							if(child4 == 0)
							{
								dup2(pipe4[1], 1);
								
								close(pipe4[0]);
								close(pipe4[1]);
								
								
								part1 = strtok(argv[argc-5], " ");
								part2 = strtok(NULL, " ");
								char *cmd_args[] = {part1, part2, NULL};
								execvp(*cmd_args, cmd_args);
								exit(0);
							}
							else dup2(pipe4[0], 0);
						}
					dup2(pipe3[1], 1);
					
					close(pipe3[0]);
					close(pipe3[1]);
					
					part1 = strtok(argv[argc-4], " ");
					part2 = strtok(NULL, " ");
					char *cmd_args[] = {part1, part2, NULL};
					execvp(*cmd_args, cmd_args);
					exit(0);
				}
				else dup2(pipe3[0], 0);
			}
			dup2(pipe2[1], 1);
			
			close(pipe2[0]);
			close(pipe2[1]);
			
			part1 = strtok(argv[argc-3], " ");
			part2 = strtok(NULL, " ");
			char *cmd_args[] = {part1, part2, NULL};
			execvp(*cmd_args, cmd_args);
			exit(0);
		}
		else dup2(pipe2[0], 0);
	}
	dup2(pipe1[1], 1);
	
	close(pipe1[0]);
	close(pipe1[1]);

	part1 = strtok(argv[argc-2], " ");
	part2 = strtok(NULL, " ");
	char *cmd_args[] = {part1, part2, NULL};
	execvp(*cmd_args, cmd_args);
	exit(0);
}

else
{

	dup2(pipe1[0], 0);
	close(pipe1[0]);
	close(pipe1[1]);
	
	part1 = strtok(argv[argc-1], " ");
	part2 = strtok(NULL, " ");
	char *cmd_args[] = {part1, part2, NULL};
	execvp(*cmd_args, cmd_args);
	sleep(1);
}	

return(0); 
}
