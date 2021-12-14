#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>

char*count;
sem_t s2;
char s1[20];


int main(int argc,char const *srgv[])
{ 

    int shmd;
    sem_init(&s2,1,1);
    shmd=shm_open("/dictionary.txt",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
    ftruncate(shmd,20);
    count=(char *)mmap(NULL,20,PROT_READ | PROT_WRITE,MAP_SHARED,shmd,0);
    while(1)
    {   
        sem_wait(&s2);
        scanf("%s",s1);
        count =s1;
        printf("COUNT: %d",*count);
        sem_post(&s2);
    }
    sem_destroy(&s2);
    shmd=shm_unlink("/dictionary.txt");
    return 0;
}