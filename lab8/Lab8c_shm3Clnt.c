

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
char *str;
int isLoop = 1;
void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    printf("from handler ");
    printf("%s\n", str);
    signal(sig, SIGHandler);
}
int main() {
    signal(SIGUSR1, SIGHandler);
    // ftok to generate unique key
    key_t key = ftok("hash_this", 65);

    // shmget returns an identifier in shmid
    int shmid;
    // int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    shmid = shmget(key, 1024, 0666);

    // shmat to attach to shared memory
    str = (char*) shmat(shmid, (void*)0, 0);

    // after attach to shared mem, get ppid
    int ppid = atoi(str);
    sprintf(str,"%d", getpid());
    printf("successfully obtain ppid\n")

    kill(ppid, SIGUSR1); // to server

    while (isLoop) ; // wait for signal
    printf("waiting for SIG before writing to server\n");

    sprintf(str, "%s", "os kmitl\n");
    printf("Clnt write to mem & notify: %s\n", str);
    kill(ppid, SIGUSR1); // toser
    // detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}