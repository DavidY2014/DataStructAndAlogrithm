#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int ngx_daemon(){
    int fd;
    switch (fork())
    {
    case -1://创建子进程失败
        /* code */
        return -1;
    case 0://创建子进程成功
        /* code */
        break;
    default:
        //父进程
        exit(0);
    }

    //脱离终端，终端关闭，将跟此子进程无关
    if(setsid() == -1){
        //记录错误日志
        return -1;
    }
    umask(0);//设置为0，不要让它来限制文件权限，以免引起混乱

    fd = open("/dev/null",O_RDWR);
    if(fd == -1){
        return -1;
    }
    if(dup2(fd,STDIN_FILENO) == -1){
        return -1;
    }
    if(dup2(fd,STDOUT_FILENO) == -1){
        return -1;
    }

    if(fd>STDERR_FILENO){
        if(close(fd) == -1){
            return -1;
        }
    }

    return -1;
}


void sig_usr(int signo){
    int status;
    switch (signo)
    {
    case SIGUSR1:
        printf("收到了SIGUSR1开始信号，进程id=%d!\n",getpid());
        sleep(20);
        printf("收到了SIGUSR1结束信号，进程id=%d!\n",getpid());
        break;
    case SIGUSR2:
        printf(">>>>>>>收到了SIGUSR2开始信号，进程id=%d!\n",getpid());
        sleep(5);
        printf("收到了SIGUSR2结束信号，进程id=%d!\n",getpid());
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


int main(){


    if(signal(SIGUSR1,sig_usr) == SIG_ERR){
        printf("无法捕捉SIGUSR1信号");
    }

    if(signal(SIGUSR2,sig_usr) == SIG_ERR){
        printf("无法捕捉SIGUSR2信号");
    }

    for(;;){
            sleep(1);
            printf("休息1秒，进程id=%d\n",getpid());
    }



    // if(ngx_daemon()!=1){
    //     return 1;
    // }
    // else{
    //     for(;;){
    //         sleep(1);
    //         printf("休息1秒，进程id=%d\n",getpid());
    //     }

    // }
    return 0;
}

