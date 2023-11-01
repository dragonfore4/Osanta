#include <stdlib.h>  //for atoi()
#include <string.h>  //for strcpy()
#include <unistd.h>  //for pipe
#include <wait.h>    //for wait()
#define SIZE 10      // pipe buffer size
#include <stdio.h>
int main() {
    int pfd[2];
    // storing (pipe) file descriptor
    // returned from pipe()
    int nread;
    int pid;  // pid_t is actually an int
    char buf[SIZE];
    char inbuf[SIZE * 2];
    pipe(pfd);
    // if (pipe(pfd) == -1)
    //{perror("pipe failed\n"); exit(-1);}
    printf("write pipe id = %d ", pfd[1]);
    printf(" read file id = %d\n", pfd[0]);
    pid = fork();
    if (pid == 0) {     // child
        close(pfd[1]);  // tidy unused end
        // read until end of stream
        while ((nread = read(pfd[0], buf, SIZE)) != 0)
            if (nread > 11)
                printf("avoid overflow no conversion %s to int", buf);
            else
                printf("child received %s. After + 5 =  %d\n", buf, atoi(buf) + 5);
        close(pfd[0]);  // properly close unused resource
    } else {
        close(pfd[0]);  // tidy unused end
        // strcpy(inbuf,"4321\0"); //equiv "4321\0"
        sprintf(inbuf, "%ld", 123456789012);
        // newer function - less side effect
        write(pfd[1], inbuf, strlen(inbuf)+1);  // +1 for padded \0
        close(pfd[1]);
        /* q1.5 */;  // wait for child to complete
        wait(NULL);
    }
    return 0;
}