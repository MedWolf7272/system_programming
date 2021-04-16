#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_KEY 0x1234
int main(int argc, char *argv[], char *enpv[]) 
{
    pid_t num;
    int status;
    int start = 5, end = 20, interval=4;
    //float* array[] = new float[n];
    int len = 1+(end-start);
    int shm_id = shmget(SHM_KEY, len*sizeof(int),IPC_CREAT|0644);
    if (shm_id == -1) 
    {
      perror("Shared memory1");
      return 1;
    }
    //std::vector<double> array;
    int counter=0;
    for (int i=0; i<interval; ++i)
    {
        num = fork();
        if (num==-1)
        {
            printf("can't  do fork-ing");
            exit (-1);
        }
        else if (num==0)
        {
            std::string numb_cgild = std::to_string(i), start_in = std::to_string(start), end_in=std::to_string(end); 
            std::string adr=std::to_string(shm_id);
            //printf("i'm child No - %d\n", i+1);
            execl("child", "./child", numb_cgild.c_str(), start_in.c_str(), end_in.c_str(), adr.c_str() , NULL);
            
            exit(0);
        }  
    }
    if (num>0)
    {
        printf("Searching siple numbers in between %d and %d\nFound:\n", start, end);
        //printf("i'm parent\n");            
        wait(&status);
        //printf("Childr is dead [1]\n");
        wait(&status);
        //printf("Childr is dead [2]\n");
        wait(&status);
        //printf("Childr is dead [3]\n");
        wait(&status);
        //printf("All children are dead. Nice\n");
        int *bufptr=(int*)shmat(shm_id, NULL, 0);
        if (bufptr == (void *) -1) 
        {
        perror("Shared memory attach4\n");
        return 1;
        }
        for (int i=0; i<len; i++)
        {
            if (bufptr[i]!=0)
            {
            printf("%d\t", bufptr[i]);
            }
            
        }
        printf("\nThats all, folks\n");
        int check = shmdt(bufptr);
        if (check == -1) 
        {
        perror("Shared memory detach5\n");
        return 1;
        }
    }
    
} 
