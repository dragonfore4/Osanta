#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
char *str;
int isLoop = 0;
void SIGHandler(int sig) {
 signal(sig, SIG_IGN);
 printf("from handler ");
 printf("%s\n",str);

 signal(sig,SIGHandler);
}
int main() {
 signal(SIGUSR1, SIGHandler);
 // ftok to generate unique key
 key_t key = ftok("hash_this",65);

 // obtain shr_mem start addr
 int shmid=shmget(key,1024, 0666|IPC_CREAT);
 // shmat to attach to shared memory
 str = (char*) shmat(shmid,(void*)0,0);
 while(isLoop) ; //skipped
 //original data in shmMem
 printf("Data in memory: %s\n",str);
 int ppid = atoi(str);
 //kill(SIGUSR1,ppid);
 raise(SIGUSR1);

 //sprintf(str,"%s","os kmitl\n");
 printf("Writing to memory: %s\n",str);

 shmdt(str); //detach from shared memory
 shmctl(shmid,IPC_RMID,NULL);
 return 0; }
4. สร้าง q4 (server)
//Lab8c_shmb4Serv.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
char *str;
int isLoop = 1;
void SIGHandler(int sig) {
 signal(sig, SIG_IGN);
 printf("from handler "); //printf("%s\n",str);
 isLoop = 0;
 signal(sig,SIGHandler); } //handler
int main(int argc, char * argv[]) {
 signal(SIGUSR1, SIGHandler);

 key_t key = ftok("hash_this",65);

 int shmid = shmget(key,1024,0666|IPC_CREAT);
 //int shmid = shmget(key,1024,0666);
 // shmat to attach to shared memory
 str = (char*) shmat(shmid,(void*)0,0);
 int cpid;
 sprintf(str,"%d",getpid()); //ppid for clnt
 //wait SIGUSR1 after child got my pid
 while(isLoop) ;
 isLoop = 1; //preparing for next loop

 cpid = atoi(str);
 kill(cpid,SIGUSR1); // to client
 while(isLoop) ;
 //reading from shmMem
 printf("From child: %s\n",str);

 //detach and remove
 shmdt(str); shmctl(shmid,IPC_RMID,NULL);
 return 0; } //main
//Lab8c_shm3Clnt.c
#include <stdio.h>
#include <sys/ipc.h>