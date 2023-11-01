#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(/*int argv, char** argc*/) {
    pid_t pid;
    int i = 0;

    // pid = fork();
    //if (pid < 0) exit(-1);
    int id = fork();
    printf("Hello world from id: %d\n", id);
    if (id == 0) {
        printf("child pro\n");

    } else {
        printf("parent\n");
    }
    // if (pid == 0) {
    //     i = 1;
    //     printf("chikd my copy of i is %d\n", i);
    // } else {
    //     i = 2;
    //     printf("my copy of i is %d\n", i);
    // }
    wait(NULL);
    return 0;
}
