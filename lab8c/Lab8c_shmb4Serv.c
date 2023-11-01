// Lab8c_shmb4Serv.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>
char *str;
int isLoop = 1;
void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    printf("from handler ");  // printf("%s\n",str);
    isLoop = 0;
    signal(sig, SIGHandler);
}  // handler
int main(int argc, char *argv[]) {
    signal(SIGUSR1, SIGHandler);

    key_t key = ftok("hash_this", 65);

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    // int shmid = shmget(key,1024,0666);
    //  shmat to attach to shared memory
    str = (char *)shmat(shmid, (void *)0, 0);
    int cpid;
    sprintf(str, "%d", getpid());  // ppid for clnt
    // printf("%s eiei\n",str);
    // wait SIGUSR1 after child got my pid
    while (isLoop)
        ;
    printf("not this\n");
    isLoop = 1;  // preparing for next loop

    cpid = atoi(str);
    printf("from server the thrid %s\n",str);
    kill(cpid, SIGUSR1);  // to client
    while (isLoop)
        ;
    // reading from shmMem
    printf("From child: %s\n", str);

    // detach and remove
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}  // main
