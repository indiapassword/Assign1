#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
sem_t wrt;
pthread_mutex_t mutex;
int balance = 500;
int numreader = 0;

void *credit_writer(void *wno)
{
    int amount = 500;

    sem_wait(&wrt);
    balance = balance + amount;
    printf("Writer %d has credited the amount Rs- %d current balance is Rs- %d\n", (*((int *)wno)), amount, balance);
    sem_post(&wrt);
}
void *debit_writer(void *wno)
{
    int amount = 100;
    sem_wait(&wrt);
    balance = balance - amount;

    printf("Writer %d has debited the amount %d current balance is %d\n", (*((int *)wno)), amount, balance);
    sem_post(&wrt);
}
void *reader(void *rno)
{

    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d: read balance as %d\n", *((int *)rno), balance);

    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{

    pthread_t reader_thread_id[10], writer_thread_id[5];
    char c[] = {'D', 'C', 'C', 'D', 'C'};
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&reader_thread_id[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        if (c[i] == 'C')
            pthread_create(&writer_thread_id[i], NULL, (void *)credit_writer, (void *)&a[i]);
        else
            pthread_create(&writer_thread_id[i], NULL, (void *)debit_writer, (void *)&a[i]);
    }
    for (int i = 5; i < 10; i++)
    {
        pthread_create(&reader_thread_id[i], NULL, (void *)reader, (void *)&a[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(reader_thread_id[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(writer_thread_id[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
