#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(/*int argv, char ** argc*/)
{
    pid_t pid, pidsub;
    int i, j;
    printf("only parent befor fork\n");
    for (i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == 0){ // childen
            if ((i % 2) == 0){
                printf("I am the child on %d\n", i);
                int num_gc = 3; // 7.1
                for (j = 0; j < num_gc; j++)
                {
                    pidsub = fork();//7.2
                    if (pidsub == 0)
                    {
                        printf("I am grandchild num %d of even child no %d\n", j, i);
                        exit(0);//7.3
                    }
                }
                while(wait(NULL)!=-1);//7.4
                exit(0);
            }
            else{
                printf("I am the child no %d\n",i);
                int num_gc = 4;//7.5
                for(j =0;j<num_gc;j++){
                    pidsub = fork();
                    if(pidsub == 0){//7.6
                        printf("I am grandchild sum %d of even shild no %d\n",j,i);
                        exit(0);//7.7
                    }
                }
                while(wait(NULL)!=-1);
                exit(0);//7.8
            }
            // exit(0);//7.9
        }
    }
    while(wait(NULL)!=-1);
    return 0;
}
