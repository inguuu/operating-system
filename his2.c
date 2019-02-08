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
	