#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int i; int sum = 3;
    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0)  {// child
        printf("my copy of i is %d\n",i);
        exit(-1);
        printf("should not be execute\n");
        }
    }
while (wait(NULL) != -1) {
    printf("test\n");
}; // empty loop
printf("bye from main \n", sum);
return 0;
}
