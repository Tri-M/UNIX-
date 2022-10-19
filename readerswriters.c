
// #include <stdio.h>
// #include <string.h>
// #include<stdlib.h>
// #include<fcntl.h>
// #include<unistd.h>
// #include<pthread.h>
// #include<semaphore.h>

// sem_t mutex,writeblock;
// int data = 0,rcount = 0;

// void *reader(void *arg)
// {
//         int f;
//         f = ((int)arg);
//         sem_wait(&mutex);
//         rcount = rcount + 1;
//         printf("\nReader %d has arrived \n",f);
//         if(rcount==1)
//                 sem_wait(&writeblock);
//         sem_post(&mutex);
//         printf("\nReader Entered %d Data read by the reader is %d\n",f,data);
//         sleep(4);
//         sem_wait(&mutex);
//         rcount = rcount - 1;
//         printf("\nReader Exiting : %d Remaining Readers:%d \n",f,rcount);

//         if(rcount==0)
//         {
//                 printf("\nNo readers Writers can write\n");
//                 sem_post(&writeblock);
//         }
//         sem_post(&mutex);
// }

// void *writer(void *arg)
// {
//         int f;
//         f = ((int) arg);
//         printf("\nWriter %d has arrived\n",f);
//         sem_wait(&writeblock);
//         data++;
//         printf("\nWriter Entered %d Data writen by the writer is %d\n",f,data);
//         sleep(2);
//         printf("\nWriter Exiting : %d\n",f);
//         sem_post(&writeblock);
// }
// int main()
// {
//         int i,b;
//         pthread_t rtid[5],wtid[5];
//         sem_init(&mutex,0,1);
//         sem_init(&writeblock,0,1);
//         for(i=0;i<=2;i++)
//         {
//                 pthread_create(&wtid[i],NULL,writer,(void *)i);
//                 sleep(2);
//                 pthread_create(&rtid[i],NULL,reader,(void *)i);
//         }
//         for(i=0;i<=2;i++)
//         {
//                 pthread_join(wtid[i],NULL);
//                 pthread_join(rtid[i],NULL);
//         }
// }

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    cnt = cnt*2;
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt);
    sem_post(&wrt);

}
void *reader(void *rno)
{   
    
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt);
        
    }
    pthread_mutex_unlock(&mutex);
    
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt);

  
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt);
        
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[10],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; 

    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}