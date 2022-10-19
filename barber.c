#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_CUSTOMERS 7

void *customer(void *num);
void *barber(void *);

void waitingTime(int secs);

sem_t room;
sem_t chair;

sem_t toSleep;

sem_t toHoldBelt;

int completedFlag = 0;

int main(int argc, char *argv[]) {
pthread_t barber_id;
pthread_t tid[MAX_CUSTOMERS];
long RandSeed;
int i, numCustomers, numChairs;
int Number[MAX_CUSTOMERS];

printf("Enter the number of Customers : "); 
scanf("%d",&numCustomers) ;
printf("Enter the number of Chairs : ");
 scanf("%d",&numChairs);


if (numCustomers > MAX_CUSTOMERS) {
printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS);
exit(-1);
}


for (i=0; i<MAX_CUSTOMERS; i++) {
Number[i] = i;
}


sem_init(&room, 0, numChairs);
sem_init(&chair, 0, 1);
sem_init(&toSleep, 0, 0);
sem_init(&toHoldBelt, 0, 0);

pthread_create(&barber_id, NULL, barber, NULL);



for (i=0; i<numCustomers; i++) {
pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
sleep(1);
}

for (i=0; i<numCustomers; i++) {
pthread_join(tid[i],NULL);
sleep(1);
}


completedFlag = 1;
sem_post(&toSleep);
pthread_join(barber_id,NULL);
}

void *customer(void *number) {
int num = *(int *)number;
printf("Customer %d leaving for barber shop.\n", num);
waitingTime(2);
printf("Customer %d arrived at barber shop.\n", num);


sem_wait(&room);
printf("Customer %d entering waiting room.\n", num);

sem_wait(&chair);


sem_post(&room);


printf("Customer %d waking the barber.\n", num);
sem_post(&toSleep);


sem_wait(&toHoldBelt);


sem_post(&chair);
printf("Customer %d leaving barber shop.\n", num);
}

void *barber(void *junk) {

while (!completedFlag) {


printf("The barber is sleeping\n");
sem_wait(&toSleep);


if (!completedFlag) {

printf("The barber is cutting hair\n");
waitingTime(2);
printf("The barber has finished cutting hair.\n");


sem_post(&toHoldBelt);
}
else {
printf("The barber is going home for the day.\n");
}
}
}

void waitingTime(int secs) {
int len;
len = (int) ((1 * secs) + 1);
sleep(len);
}

