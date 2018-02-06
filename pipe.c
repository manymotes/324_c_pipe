#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char* argv[])
{

extern char** environ;


if (argc <= 4) {
		printf("No program to exec.  Exiting...\n");
		exit(0);
	}


	int tripmine = 0;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "PIPE") == 0)
		{
			//printf("FOUND \"%s\"\n", argv[i]);
			tripmine = i;
		}
	}

	char* arg1[tripmine + 1]; 
	//printf("first argLINE \n");
	pid_t pid, pid2;

	int  fd[2];
     pipe(fd);
     //int  pipeB[2];
     //pipe(pipeB);
     char str[60];



	for (int j = 1; j < tripmine; j++)
	{
	 arg1[j - 1] = argv[j];
	 //printf("added \"%s\"\n", argv[j]);
	}
	arg1[tripmine ] = 0;
	//printf("\n");

 char *arg2[2]; 
	



	for (int k = tripmine+ 1; k <= argc; k++)
	{
	 arg2[k -tripmine - 1] = argv[k];
	 //printf("added \"%s\"\n", argv[k]);
	}
	arg2[argc - tripmine+1] = 0;


	//printf("\n");


	pid=fork();
    if (pid==0)
    { 
       
    	
    	dup2(fd[1], STDOUT_FILENO);
    	close(fd[0]);
    	close(fd[1]);
    /* child process */
    //      static char *argv[]={"echo","Foo is my name.",NULL};
    	//printf("%s %s %s \n", arg1[0],arg1[1], arg1[2]);
            execve(arg1[0], &arg1[0], environ);
    	//execl(arg1[0],arg1[1], arg1[2], NULL);

//printf("first argLINE \n");
        
        exit(0); /* only if execv fails */
    }
    else
    { /* pid!=0; parent process */
           waitpid(pid,0,0); /* wait for child to exit */
	}

    	pid2=fork();
    if (pid2==0)
    { 
    	
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
    	 close(fd[0]);
    /* child process */
    //      static char *argv[]={"echo","Foo is my name.",NULL};
    	//printf("in child 2 \n");
           // execve(arg1[0], &arg1[], null);

    	//FILE* reader = fdopen(fd[0],"r");
    	//fgets( str, 60, reader);

    	//execl(arg2[0], str, NULL,NULL);
    	
		

		//execl(arg2[0], str, NULL);

		//printf(" index 0:  %s\n", arg2[0]);
		// int sizearr = sizeof(arg2)/sizeof(*arg2);
		//  printf(" array size:  %d\n", sizearr );
		//  printf("arg2 0: %s\n", arg2[0] );
		//  printf("arg2 1: %s\n", arg2[1] );
		
	execve(arg2[0], &arg2[0], environ);

		 

    
   //printf("first argLINE \n");
           exit(0); /* only if execv fails */
    }
    else
    { /* pid!=0; parent process */
           waitpid(pid2,0,0); /* wait for child to exit */

    	
    }

 
		close(fd[0]);
    	close(fd[1]);	
    	kill(pid, SIGKILL);
    	kill(pid2, SIGKILL);
return 0;
	

}

