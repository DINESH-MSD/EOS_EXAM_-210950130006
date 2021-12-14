#include<stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

int *count;
sem_t s2;


int main(int argc,char const *argv[])
{ 

    int shmd;
    sem_init(&s2,1,1);
    shmd=shm_open("/dictionary.txt",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
    ftruncate(shmd,sizeof(int));
    count=(int *)mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED,shmd,0);
    while(1)
    {   
        sem_wait(&s2);
        scanf("%d",&number);
        *count=number;
        printf("COUNT: %d",*count);
        sem_post(&s2);
    }
    sem_destroy(&s2);
    shmd=shm_unlink("/dictionary.txt");
    return 0;
}