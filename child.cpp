#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <vector>
#include <sys/shm.h>

void fun_do_stuff(int child_number, int start, int end, int *result)
{
    //printf("In the func child - %d\n", child_number);
    int offset = child_number*((end-start+1)/4);
    
    int right = start + (child_number+1)*(end-start)/4;
    int left = start + child_number*(end-start)/4;
    if (child_number!=0)
    {
        left++;
    }
    for (int number=left; number<=right; number++)
    {
        //printf("Cild - %d, check number - %d\n", child_number+1, number);
        bool simple = true;
        for (int dev=2; dev<number; dev++)
        {
            //printf("Check siplisity %d\n", number);
            if (number%dev==0)
            {
                //printf("%d - not simple\n", number);
                simple=false;
                dev=number;
                result[offset] =0;
                offset++;
                break;
            }
            else
            {
                //printf("%d - maybe simple\n", number);
                simple=true;
            }
        }
        if (simple)
        {
            //printf("%d - simple\n", number);
            //printf("Add new simple(%d) to arr\n", number);
            result[offset] =number;
            offset++;           
            //printf("%d added. \n", number);
            
        }
    }
}


int main(int argc, char *argv[], char *enpv[]) 
{
    //printf("i'm child No - %s\n", argv[1]);
   int i = std::atoi(argv[1]), start=std::atoi(argv[2]), end=std::atoi(argv[3]), addres=std::atoi(argv[4]);
   
   int *bufptr=(int*)shmat(addres, NULL, 0);
   if (bufptr == (void *) -1) {
      perror("Shared memory attach");
      return 1;
   }  
    fun_do_stuff(i, start, end, bufptr);
    int check = shmdt(bufptr);
    if (check == -1) 
        {
        perror("Shared memory detach6\n");
        return 1;
        }
}