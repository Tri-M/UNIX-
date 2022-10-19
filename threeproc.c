#include<stdio.h>
#include<unistd.h>

int main(){
        int fd[2];
        int res1,res2;  
        pipe(fd);
        res1=fork();
        if(res1==0){
                dup2(fd[1],1);
                close(fd[0]);
                close(fd[1]);
                execlp("ls","ls", NULL);   
        }
        else{
                wait(NULL);
                close(fd[1]);
                int fd1[2];   
                pipe(fd1);
                res2=fork();
                if(res2==0){
                        dup2(fd[0],0);
                        dup2(fd1[1],1);
                        close(fd[0]);
                        close(fd1[0]);
                        close(fd1[1]);
                        execlp("head","head","-5",NULL);   
                }

                else{
                        wait(NULL);
                        dup2(fd1[0],0);
                        close(fd[0]);
                        close(fd1[0]);
                        close(fd1[1]);
                        execlp("wc","wc","-c",NULL);   
                }
        }
}