#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

    /* Program Termination Symbol */
    const char terminate = '@';

    /* String delimiter */
    const char delimiter = ' ';

    /* Pipe file ID's */
    int fileID[2];

    /* Parent ID's */
    int pid1, pid2;

    /* String token */
    char * token, * token2;

    /* User input */
    char * user_input, line[100];

    user_input = (char *) malloc(100);

    /* Unix Commands */
    char * command1[10], *command2[10];

    for (int i=0; i<10; i++)
    {
    command1[i] = (char *)malloc(100*sizeof(char));
    command2[i] = (char *)malloc(100*sizeof(char));
    }

    /* Begin main program logic */

    printf("Please enter the first command: \n");

    user_input = gets(line);

    while (user_input[0] != terminate)
    {
    token = (char *) malloc(100*sizeof(char));

    for (int i=0; i<10; i++)
        {
        if (i == 0)
        {
        token = strtok(user_input, &delimiter); 
        } else {
        token = strtok(NULL, &delimiter);
        }

        if (token != NULL)
        {
        strcpy(command1[i], token);
        } else {
        command1[i] = 0;
        }
        }

    printf("Please enter the second command: \n");  
    user_input = gets(line);

    token2 = (char *) malloc(100*sizeof(char));

    for (int i=0; i<10; i++)
    {
        if (i == 0)
        {
        token2 = strtok(user_input, &delimiter);
        } else {
        token2 = strtok(NULL, &delimiter);
        }

        if (token2 != NULL)
        {
        strcpy(command2[i], token2);
        } else {
        command2[i] = 0;
        }
    }   


    /* Pipe and execute user commands */

    /* Create pipe */
    pipe(fileID);

    /* Create child processes */

    pid1 = fork();

    if (pid1 != 0)
    {
        pid2 = fork();
    }

    /* First child process */
    if (pid1 == 0)
    {
        dup2(fileID[1], 1);
        execvp(command1[0], command1);
    }

    /* Second child process */
    if (pid2 == 0)
    {
        dup2(fileID[0], 0);
        execvp(command2[0], command2);
    }   

    /* Wait for children to terminate */
    wait(&pid1);
    wait(&pid2);

    /* Repeat */
        printf("Please enter the first command: \n");
    user_input = gets(line);
    }

    return 0;
}
