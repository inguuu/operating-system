#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

int stop = 0;
int histogram[256] = { 0 };
int *buffers;
int in = 0;
int out = 0;

struct timeval tp3, tp4;
float totaltvalue;

sem_t full;
sem_t empty;
sem_t mutex;
sem_t mutexhistogram;

typedef struct threads{
	int id;
	int buf;
	float tvalue;
}wthread;

void *histogramize(void * thd2)
{
	pthread_t tid;
	tid = pthread_self();
	wthread *thd = (wthread *)thd2;//thread구조체 하나 받는다
	int data;
	struct timeval tp1, tp2;
	float ntvalue;
	int res = gettimeofday(&tp1, NULL);

	while (1) {
		if (stop == 0) {
			sem_post(&full);
			sem_post(&mutex);
			break;
		}
		sem_wait(&full);//바운디드 버퍼 보안
		sem_wait(&mutex);//
		data = buffers[out];// 데이터 
		out = (out + 1) % thd->buf;
		sem_post(&mutex);
		sem_post(&empty);


		
}

int main(int argc, char *argv[])
{
	int res = gettimeofday(&tp3, NULL);
	int num1 = atoi(argv[1]);
	int num2 = atoi(argv[2]);
	int tdnum;
	int bufsize;
	int create;
	stop = num2 - num1+1;

	buffers = (int *)malloc(sizeof(int)*bufsize);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, bufsize);
	sem_init(&mutex, 0, 1);
	sem_init(&mutexhistogram, 0, 1);

	wthread td[tdnum];
	pthread_t *thread;
	thread = malloc(sizeof(pthread_t)*tdnum);

	

}