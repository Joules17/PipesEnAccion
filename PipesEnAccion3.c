#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define READ 0
#define WRITE 1

// a
int main()
{
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("Creando pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Fork() fallido");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // proceso hijo, es el proceso que recibe el numero random del padre y determina que clasificacion imprimir. 
        int numrecibido;
        // Cerramos el pipe read descriptor 
        close(fd[WRITE]);

        read(fd[READ], &numrecibido, sizeof(int)); // leemos el numero 
        close(fd[READ]); 

        if (numrecibido >= 500) {
            printf("Mayor o igual a 500 \n"); 
        } else {
            printf("Menor a 500 \n"); 
        }
    }
    else
    {
        // Proceso padre, es el proceso que contiene la funcion del numero random [1, 1000]
        srand(time(NULL)); 
        int randomnum = rand() % 1000 + 1;
        printf("%d \n", randomnum); 
        // Cierra el pipe read
        close(fd[READ]);
        write(fd[WRITE], &randomnum, sizeof(int)); // escribimos el numero 
        close(fd[WRITE]); 
    }
}
