#include <stdio.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <sys/wait.h>

int main() {
    char userChoice = 'z';
    pid_t cpid;
    while (userChoice != 'q') {
        // print menu
        printf("a: ls \n");
        printf("b: ps \n");
        printf("c: who \n");
        printf("q for quit \n");
        scanf(" %c", &userChoice);
        cpid = fork();
        if (cpid == 0) {
            if(userChoice == 'a') {
                execlp("/bin/ls", "ls", NULL);
            }
            else if(userChoice == 'b')  {
                execlp("/bin/ps", "ls", NULL);
            }
            else if(userChoice == 'c') {
                execlp("/bin/who", "ls", NULL);
            } else {
                exit(0);
            }
        } wait(NULL);
    }
    printf("parent terminated\n");
    return 0;
}