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

		char name[20];
		sprintf(name, "data%d.bin", data);
		int fd = open(name, O_RDONLY);
		assert(fd);
		int fileSize = lseek(fd, 0, SEEK_END);
		lseek(fd, -fileSize, SEEK_CUR);
		unsigned char *buf = (unsigned char *)malloc(sizeof(unsigned char)*fileSize);
		read(fd, buf, sizeof(unsigned char)*fileSize);

		sem_wait(&mutexhistogram);
		//printf("%d\n", stop);
		if (stop > 0) {
			for (int k = 0; k < fileSize; k++)
			{
				histogram[buf[k]]++;
			}
			stop--;
		}
		
		sem_post(&mutexhistogram);
	}
	
	res = gettimeofday(&tp2, NULL);
	ntvalue = (tp2.tv_sec - tp1.tv_sec + ((tp2.tv_usec - tp1.tv_usec) / 1000000.0)) * 1000.0;
	thd->tvalue = ntvalue;
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
	
	if (argv[3] == NULL)
	{
		tdnum = 1;
		bufsize = 1;
	}
	else if (argv[3] != NULL && argv[4] == NULL)
	{
		tdnum = atoi(argv[3]);
		bufsize = 1;
	}
	else
	{
		tdnum = atoi(argv[3]);
		bufsize = atoi(argv[4]);
	}

	buffers = (int *)malloc(sizeof(int)*bufsize);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, bufsize);
	sem_init(&mutex, 0, 1);
	sem_init(&mutexhistogram, 0, 1);

	wthread td[tdnum];
	pthread_t *thread;
	thread = malloc(sizeof(pthread_t)*tdnum);

	for (int i = 0; i < tdnum; i++){
		td[i].buf = bufsize;
		td[i].id = i + 1;
	    create = pthread_create(&thread[i], NULL, histogramize, (void *)&td[i]);
	}
	for (int j = num1; j < num2+1; j++){
		sem_wait(&empty);
		sem_wait(&mutex);
		buffers[in] = j;
		in = (in + 1) % bufsize;
		sem_post(&mutex);
		sem_post(&full);
	}

	int fd2 = open("histogram.bin", O_RDWR);
	if (fd2 == -1){
		printf("file don't exist\n");
		return 0;
	}


}