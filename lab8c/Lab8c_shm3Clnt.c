// Lab8c_shm3Clnt.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
char *str;
int isLoop1 = 1;
void SIGHandler1(int sig) {
    signal(sig, SIG_IGN);
    // printf("from handler ");
 printf("ppid = %s, Btw SIGUSR1 = %d\n",str,sig);
 isLoop1 = 0;
 signal(sig,SIGHandler1);
}
int main() {
    signal(SIGUSR1, SIGHandler1);

    // ftok to generate unique key
    key_t key = ftok("hash_this", 65);
    int shmid;
    // shmid = shmget(key,1024,0666|IPC_CREAT);
    shmid = shmget(key, 1024, 0666);
    // shmat to attach to shared memory
    str = (char *)shmat(shmid, (void *)0, 0);
    printf("from client first %s\n",str);
    // after attach to shared mem, get ppid
    int ppid = atoi(str);
    sprintf(str, "%d", getpid());
    printf("from client second and the str is: %s T\n",str);
    printf("from client ppid is: %d\n",ppid);
    printf("successfully obtain ppid\n");

    // kill(SIGUSR1, ppid);  // to server
    kill(ppid, SIGUSR1);
    // raise(SIGUSR1);
    printf("upper is kill %d and down is loop from client",ppid);
    while (isLoop1)
        ;  // waiting for signal
    printf("waiting for SIG before writing to server\n");
    sprintf(str, "%s", "os kmitl\n");
    printf("Clnt write to mem & notify: %s\n", str);
    kill(ppid, SIGUSR1);  // to server
    // detach from shared memory
    shmdt(str);
    // destroy the shared memory
    // shmctl(shmid,IPC_RMID,NULL);
    return 0;
}  // main