#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t cpid;
    pid_t gcpid;

    cpid = fork();
    /*if (cpid < 0) {
        fpintf(stderr, "Fork Failed");
        exit(-1);

    } else { */

    if (cpid == 0) { /*child process*/
        gcpid = fork();
        if (gcpid == 0) { /*grandchild*/
            printf("Can you see this3? %d\n", gcpid);
            exit(0);
        }
        execlp("/bin/123ls", "ls", NULL); /*A*/
        // exit(0);
        printf("can you see this2? %d\n",cpid); /*B*/
    }
}
