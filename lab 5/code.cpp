#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <pthread.h>

#define start 5 
#define  end 24
pthread_mutex_t mutex;
int* result= new int[end-start+1];
int found_simple=0;
void* fun_do_stuff(void* args)
{
    int child_number = *(int*)args;
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
            pthread_mutex_lock(&mutex);
            result[found_simple] =number;
            pthread_mutex_unlock(&mutex);
            found_simple++;
            offset++;           
            //printf("%d added. \n", number);
            
        }
    }
    return NULL;
}

int main(int argc, char *argv[], char *enpv[]) 
{
    int interval=4;
    int index[interval];
    pthread_t threads[interval];
    pthread_mutex_init(&mutex, NULL);

    int counter=0;
    for (int i=0; i<interval; ++i)
    {
        index[i]=i;
         pthread_create( &threads[i], NULL, fun_do_stuff, &index[i]);
    }
    for(int i=0; i<interval; i++)
    {
       pthread_join( threads[i], NULL);
    }
    int temp;
    for (int i = 0; i < found_simple - 1; i++) {
        for (int j = 0; j < found_simple - i - 1; j++) {
            if (result[j] > result[j + 1]) {
                // меняем элементы местами
                temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
            }
        }
    }

    printf("Searching siple numbers in between %d and %d\nFound:\n", start, end);

    for(int i=0; i<found_simple; i++)
    {
        if (result[i]!=0)
       printf("%d ", result[i]);
    }
        printf("\nThats all, folks\n");        
        
      return 0;   
    
    
} 
