#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// #include <sys/types.h>

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
                int num_gc = 3; // 7.1
                for (j = 0; j < num_gc; j++)
                {
                    pidsub = fork();//7.2
                    if (pidsub == 0)
                    {
                        printf("child %d forked grandchild %d\n", i, j);
                        exit(0);//7.3
                    }
                }
                while(wait(NULL)!=-1);//7.4
                exit(0);
            }
            else{
                int num_gc = 4;//7.5
                for(j =0;j<num_gc;j++){
                    pidsub = fork();
                    if(pidsub == 0){//7.6
                        printf("child %d forked grandchild %d\n", i, j);
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
//7.9 ไม่จำเป็นเพราะ process ลูกมี exit(0) รับประกันว่าจะไม่ทำ code ซ้ำต่อ
//7.10 18บรรทัด
//7.11 17ตัว
//7.12 No เพราะ ลำดับจะจัดการโดย OS
