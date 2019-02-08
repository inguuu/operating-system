#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {

	struct timeval tp1, tp2,tp3,tp4;// 시간 측정 t1,t2 부모 t3 t4 자식
	int res;
	int hisSum[256] = { 0 };//개수합
	int fd;
	int wd;
	int num1, num2,num3;//파라미터 
	char filename[100];
	unsigned char data;
	
	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);
	
	if (argv[3] == NULL ) { // 사용자가 3번째 파라미터를 입력 하지 않으면 1로 인식한다.
		num3 = 1;
	}
	else{
		num3 = atoi(argv[3]);
	}

	int div = 0;// 데이터파일 개수/ 자식 프로세스 개수 몫
	int rem = 0;// 데이터파일 개수% 자식 프로세스 개수 나머지
	int tid = -1;
	int i = 0;
	pid_t pid;
	int status;
	div = (num2 - num1 + 1) / num3;
	rem = (num2 - num1 + 1) % num3;
	float tvalue;
	float tvalue2;

	res = gettimeofday(&tp1, NULL);
	assert(res == 0);

	for (int i = 0; i < num3; i++) {
		tid++;
		pid = fork();
		res = gettimeofday(&tp3, NULL);
		assert(res == 0);
		if (pid == 0) {
			break;
		}
	}

	if(pid==0)
	//printf("%d pid num\n", getpid());
	if (rem == 0) {// 나머지가 없으면 모든 프로세서가 몫만크만 처리하면 된다. ex)hw2 1 100 10
		if (pid == 0) {
			
				for (int j = num1; j < div+num1; j++) {
					int histogram[256] = { 0 };//개수 
					sprintf(filename, "data%d.bin", j+div*tid ); // 파일명을 만듭니다
					fd = open(filename, O_RDWR);
					assert(fd);
					
					
					
					int size= lseek(fd, 0, SEEK_END);
					lseek(fd, 0, SEEK_SET);
					unsigned char *buffer;
					buffer = (unsigned char*)malloc(sizeof(unsigned char)*size);
					read(fd, buffer, sizeof(unsigned char)*size);

					for (int i = 0; i < size; i++) {
						
						histogram[buffer[i]]++;
					}

					wd = open("histogram.bin", O_RDWR);
					lockf(wd, F_LOCK, 1024);
					lseek(wd, 0, SEEK_SET);
					read(wd, &hisSum, 1024);
					lseek(wd, 0, SEEK_SET);
					for (int i = 0; i < 256; i++) {
       					assert(wd);
						hisSum[i] += histogram[i];
					    write(wd, &hisSum[i], sizeof(int));
					}
					lockf(wd, F_ULOCK, 1024);
					lseek(wd, 0, SEEK_SET);
					close(wd);
			}		
				res = gettimeofday(&tp4, NULL);
				tvalue2 = tvalue = tp4.tv_sec - tp3.tv_sec + (tp4.tv_usec - tp3.tv_usec) / 1000000.0;
				printf("Child Process tid: %d Elappsed time is %f.\n", tid,1000 * tvalue);
			exit(0);
		}
	}
	else if(rem != 0) { // 나머지가 0이 아니면 몇개의 프로세서에는 데이터 파일을 하나씩 더 처리해야한다.  ex)hw2 1 11 10 하나는 2개 처리
		if (pid == 0) {
			
			if(tid<rem){// 하나씩 더 처리해야 하는 프로세서
					for (int j =num1 ; j <= div +num1 ; j++) {
						int histogram[256] = { 0 };//개수 
						sprintf(filename, "data%d.bin", (div+1)*tid+j);// 파일에 대한 수식을 넣고 파일을 만듭니다.
						fd = open(filename, O_RDWR);
						assert(fd);

						unsigned char *buffer;

						int size = lseek(fd, 0, SEEK_END);
						lseek(fd, 0, SEEK_SET);
						buffer = (unsigned char*)malloc(sizeof(unsigned char)*size);
						read(fd, buffer, sizeof(unsigned char)*size);
						

						wd = open("histogram.bin", O_RDWR);

						
					}
			}
			
			if (rem<=tid) {// 몫 만큼 처리해도되는 프로세서
				
			}
			res = gettimeofday(&tp4, NULL);
			tvalue2= tvalue = tp4.tv_sec - tp3.tv_sec + (tp4.tv_usec - tp3.tv_usec) / 1000000.0;
			printf("Child Process tid: %d Elappsed time is %f.\n", tid,1000 * tvalue);
			exit(0);
		}
	}
	for (int i = 1; i <= num3; i++) {
		wait(&status);
		if (i == num3) {
			res = gettimeofday(&tp2, NULL);
			assert(res == 0);
			tvalue = tp2.tv_sec - tp1.tv_sec + (tp2.tv_usec - tp1.tv_usec) / 1000000.0;
			printf("Parent Process Elappsed time is %f.\n", 1000 * tvalue);//msec으로 구하기 위해 *1000
		}
		
	}

}
	