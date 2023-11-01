/* Program demonstrates the use of kill() */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
int notDone = 1;
int cnt = 0;
void mySIGhandler(int sig) {
    signal(SIGALRM, SIG_IGN);
    // breaks infinite loop by reset notDone
    notDone = 0;
    // printf("loop should break\n");
}
int main(void) {
    // install handler
    signal(SIGALRM, mySIGhandler);
    pid_t pid = fork();
    // if (pid == 0) {
    //     // let parent enters loop (manual synchronization)
    //     sleep(4);  // let parent enters loop
    //     printf("sending SIGALRM\n");
    //     kill(getppid(), SIGALRM);
    //     exit(0);  // send signal and die
    // } else {
    //     printf("parent wait for SIGALRM\n");
    //     while (notDone) cnt++;  // infinite loop
    // }

    if (pid == 0) {
        printf("child created\n");
        printf("child waiting for SIGALRM\n");
        while (notDone) {
            // printf("%d\n",cnt);
            cnt++;
        }
        printf("this line should now be shown\n");
        exit(0);
    } else {
        sleep(2);
        kill(pid, SIGKILL);
        printf("Parent senting SIGKILL\n");
        wait(NULL);
    }
    // Could be time instead of cnt
    // printf("it takes %d\n", cnt);
    // printf("%d", notDone);
    return 0;
}  // main