#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0
#define WRITE 1

int main(int argc, char *argv[]) {
	if (argc == 1){ // Se verifica que el usuario no haya ingresado nada, de ser el caso, le pedira el programa que desea se ejecute. 
        printf("Indique el programa que desea se ejecute \n"); 
        exit(1);
		} 
	else {
		int i = 0; 
		char* primarg[argc]; 
		char* segarg[argc]; 
		
		// String padre 
		char* prim = strtok(argv[1], " ");
		while(prim != NULL)
		{
			primarg[i] = prim; 
            //printf("%s \n", primarg[i]); 
			prim = strtok(NULL, " ");
			i++; 
		}
        primarg[i] = NULL; // padre
		i = 0; 

		// String hijo
		char *seg = strtok(argv[2], " "); 
		while(seg != NULL) 
		{
			segarg[i] = seg; 
            //printf("%s \n", segarg[i]); 
			seg = strtok(NULL, " "); 
			i++; 
		}
        segarg[i] = NULL; // hijo

		pid_t pid;
  		int   fd[2];

  		if (pipe(fd) == -1) {
			perror("Creating pipe");
			exit(EXIT_FAILURE);
  		}

  		pid = fork();
  		if (pid == -1) {
			perror("fork() failed)");
			exit(EXIT_FAILURE);
  		} else if (pid == 0) {
			// Close the pipe write descriptor.
		close(fd[WRITE]);
		// Redirect STDIN to read from the pipe.
		dup2(fd[READ], STDIN_FILENO);
		// execlp -> Execvp
		execvp(segarg[0], segarg); 
  		} else {
		// The parent process will execute ls.
		// Close the pipe read descriptor.
		close(fd[READ]);
		// Redirect STDOUT to write to the pipe.
		dup2(fd[WRITE], STDOUT_FILENO);
		execvp(primarg[0], primarg); 
  		}
    // notese que a comparacion del anterior punto solo cambian las lineas de los execlp -> execvp 
        
  	}
}



