#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int balance = 500;

void *credit_writer(void *wno)
{
    int amount = 500;
    balance = balance + amount;
    printf("Writer %d has credited Rs- %d. Current balance: Rs- %d\n", *((int *)wno), amount, balance);
}

void *debit_writer(void *wno)
{
    int amount = 100;
    balance = balance - amount;
    printf("Writer %d has debited Rs- %d. Current balance: Rs- %d\n", *((int *)wno), amount, balance);
}

void *reader(void *rno)
{
    printf("Reader %d: read balance as Rs- %d\n", *((int *)rno), balance);
}

int main()
{
    pthread_t reader_thread_id[10], writer_thread_id[5];
    char c[] = {'D', 'C', 'C', 'D', 'C'};
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&reader_thread_id[i], NULL, reader, &a[i]);
    }
    for (int i = 0; i < 5; i++)
    {

        if (c[i] == 'C')
            pthread_create(&writer_thread_id[i], NULL, credit_writer, &a[i]);
        else
            pthread_create(&writer_thread_id[i], NULL, debit_writer, &a[i]);
    }
    for (int i = 5; i < 10; i++)
    {
        pthread_create(&reader_thread_id[i], NULL, reader, &a[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(reader_thread_id[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(writer_thread_id[i], NULL);
    }

    return 0;
}
