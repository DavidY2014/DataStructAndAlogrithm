#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_usr(int signo){
    int status;
    switch (signo)
    {
    case SIGUSR1:
        printf("收到了SIGUSR1信号，进程id=%d!\n",getpid());
        break;
    case SIGCHLD:
        printf("收到了SIGCHLD信号，进程id=%d!\n",getpid());
        pid_t pid = waitpid(-1,&status,WNOHANG);
        if(pid==0)
            return;
        if(pid==-1)
            return;
        return;
        break;
    default:
        break;
    }

}


int g_mygbltest = 0;
int main(){
    pid_t pid;

    printf("进程开始执行\n");
    if(signal(SIGUSR1,sig_usr) == SIG_ERR){
        printf("无法捕捉sigusr1信号");
        exit(1);
    }

    if(signal(SIGCHLD,sig_usr) == SIG_ERR){
        printf("无法捕捉SIGCHLD信号");
        exit(1);
    }



    pid = fork();
    if(pid < 0){
        printf("子进程创建失败");
        exit(1);
    }

    // for(;;){
    //     sleep(1);
    //     printf("sleep 1 second,进程id=%d\n",getpid());
    // }
    // printf("exit");

    if(pid == 0){
        while(1){
            g_mygbltest++;
            sleep(1);
            printf("子进程id=%d,g_mygbltest=%d\n",getpid(),g_mygbltest);
        }

    }else{
        while(1){
            g_mygbltest++;
            sleep(2);
            printf(">>>>>>父进程id=%d,g_mygbltest=%d\n",getpid(),g_mygbltest);
        }
    }

    return 0;
}


