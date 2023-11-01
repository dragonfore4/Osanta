#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// #include <sys/types.h>

int main(/*int argv, char ** argc*/){
    pid_t pid;
    int i = 0,num = 0,sum = 0;;
    printf("Enter a postitive number");
    scanf("%d",&num);
    if(num <= 0){
        printf("you did not enter a positive number\n");
        exit(1);
    }
    if(pid = fork() > 0){
        
        for (i = 0;i <= num;i++)
            sum += i;
        wait(NULL);
        // printf("I am parent my sum = %d\n",sum);
        // exit(0);
    }
    else{
        // int sum =0;
        for(i = 1;i <=2 * num;i++)
            sum += i;
        printf("I am child my sum = %d\n",sum);
        exit(0);
    }
    printf("I am parent my sum = %d\n",sum);
    exit(0);
    return 0;
}
