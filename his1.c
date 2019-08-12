#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h> 
#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {

	struct timeval tp1, tp2;
	int res;
	float tvalue[128];// ���� �ð��� ���� �迭
	float tsum;//�� �ð�
	float tavg;//��� �ð�
	float tdis;//ǥ������ ���Ҷ� ��� 

	int hisSum[256] = { 0 };//������
	int fd;
	int wd;
	int num1, num2;//�Ķ���� ����
	char filename[100];
	unsigned char data;
	
	num1=atoi(argv[1]);
	num2=atoi(argv[2]);

	for (int j = num1; j < num2 + 1; j++) {


		res = gettimeofday(&tp1, NULL);
		assert(res == 0);

		int histogram[256] = { 0 };//���� 
		sprintf(filename, "data%d.bin", j);  // ���ϸ��� ����ϴ�
		fd = open(filename, O_RDWR);
		assert(fd);

		for (int i = 0; i < 65536; i++) {//256*64*4
			read(fd, &data, sizeof(data));
			histogram[data]++;
		}
		wd = open("histogram.bin", O_WRONLY);
		for (int i = 0; i < 256; i++) {
			
			assert(wd);
			hisSum[i] += histogram[i];
			write(wd, &hisSum[i], sizeof(int));
			

		}
		close(wd);
		res = gettimeofday(&tp2, NULL);
		assert(res == 0);
		tvalue[j-1] = tp2.tv_sec - tp1.tv_sec + (tp2.tv_usec - tp1.tv_usec) / 1000000.0;
		printf("%d: Elappsed time is %f.\n", j,1000*tvalue[j-1]);//msec���� ���ϱ� ���� *1000
		tsum += tvalue[j - 1];

	}
	
	printf("total time is %f \n", 1000*tsum);//msec���� ���ϱ� ���� *1000
	tavg = tsum / (num2 - num1 + 1);

}


