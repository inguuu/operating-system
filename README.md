# operating-system

**운영체제 프로그래밍**  
1. 히스토그램 프로그램
2. 여러 프로세스를 이용하여 히스토그램을 구하는 프로그램
3. TreadPool을 이용한 프로그램

## 1. 히스토그램 구하는 프로그램

**문제분석**

data.bin의 값이 i면 histogram[i]에 값을 저장한다. 이렇게 data.bin 파일을 다 읽고 histogram에 있는 값들을 hisSum에 합한다. 마찬가지로 총 128개의 data.bin 파일을 반복문으로 모두 읽고 hisSum에 저장을 하고 hisSum에 있는 내용을 histogram.bin에 write함수로 저장한다. 그리고 diff 명령어로 예상 결과값 val.bin과 일치하는지 검사를 하고 하나의 파일을 읽고 histogram.bin까지 반영한 시간을 구하고 128개의 총 시간, 평균, 표준편차도 구해본다.  

**알고리즘**

```

for(i<-파라미트 시작범위; i<=파라미트 종료범위; 1++){// ex) hw1 12 30 12부터 30까지를 의미
{
   tp1<- 시작시간
   open("i번째 data.bin")// i번째 데이터파일을 연다
   histogram[256]// data.bin의 값을 담는곳

    	for(j<-0; j<=256개 데이터;1++){
    	read(i번째 데이터파일을 읽음)
    	histogram[data]++//0값부터 차래대로 저장
   	}
        
        open("histogram.bin")// 내용을 쓰여질 histogram.bin

        for(k<-0; k<=256;1++){
        hisSum[k]<- + histogram[k]//데이터들의 합을 저장
        write(histogram.bin<-hisSum[k])
	}
    tp2<- 종료시간 
    tvalue[i]<- t2-t1// 데이터 하나의 걸린시간
}

tsum<- tvalue의 합// 총 걸린시간
tavg<- tsum/파라미트의 수// 평균시간
tdis<- ((각 tvalue-tavg)의 제곱/ 파라미트의 수)의 루트값// 표준편차

```



**성능평가**

| **체크포인트** **1**                                         |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![그1](https://user-images.githubusercontent.com/49789734/62850633-69034000-bd1e-11e9-9f43-585393150af9.jpg) | 1개의 파일에 대해 제대로 수행되는가? (예를 들어, hw1 4 4) 히스토그램 파일의 내용이 제대로 변경되었는지를 확인할 수 있어야 함                       기존코드에 hisSum을 추가하고 hisSum 데이터를 출력했다. data4.bin에 내용이 옆에 그림과 같은 데이터가 저장되 있는지 알 수 있다. |

​     

| **체크포인트** **2**                                         |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![그2](https://user-images.githubusercontent.com/49789734/62850631-686aa980-bd1e-11e9-9fee-042d629fde03.jpg)| 1에서 128사이의 임의의 두 파라미터를 정해서 프로그램을 수행했을 때 제대로 수행되는 가?                                                                                                                                                   임의의 범위 34 38까지를 입력했을 때 나온 결과다 각 데이터 마다 걸린시간, 총시간, 평균시간, 표준편차가 나오도록 만들었다. |

 

| **체크포인트** **3**                                         |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![그3](https://user-images.githubusercontent.com/49789734/62850635-699bd680-bd1e-11e9-9523-d1b7a09c71c6.jpg)  ![그4](https://user-images.githubusercontent.com/49789734/62850634-69034000-bd1e-11e9-9af7-671b84da6a4a.jpg) | 128개의 파일들에 대해 제대로 수행되는가?                                                               1~128까지의 데이터 파일을 실행 시킨 결과다.데이터 경과시간을 하나씩 구하고 총 걸린시간, 평균, 표준편차까지 출력 되도록 만들었다.그리고 데이터 값을 확인을 위해서 lms에 올라온 val.bin으로 저장하고 diff 함수로 내가 만든 histogram.bin과 비교하였다. |

​     

## 2. 여러 프로세스를 이용하여 히스토그램을 구하는 프로그램

**문제분석**

여러 파일에 나누어진 이진 데이터의 히스토그램 (histogram)을 얻는 프로그램을 구현한다. 이진 데이터의 크기는 다양할 수 있다. 여러 개의 child process들을 생성하여 작업을 분담한다. 각 child process 는 자신에게 할당된 파일들을 읽고 histogram 결과를 수집하여 histogram.bin 파일에 통합한다. 자신이 만든 histogram.bin과 결과 val.bin과 diff 함수로 비교하고 자식 프로세서의 개수의 따른 성능 시간을 확인해본다.

**알고리즘**

```

for(사용자 입력 만큼){
 pid ==0 인 fork 생성 // 자식프로세스 생성
}

생성된 자식 프로세스들은 2가지 경우에 따라서 병렬적으로 수행

case 1: 모두 같은 개수의 데이터파일을 할당 받을 때 
// ex) hw2 1 10 10 => 1 1 1 1 1 1 1 1 1 1 
for{
    몫=데이터 파일개수 /프로세스 개수
    프로세스들은 할당된 몫만큼 읽는다.
     hisSum과 histogram.bin에 저장 
}

case ２: 모두 같은 개수의 데이터파일을 할당 받을 때 
// ex) hw2 1 12 10 => 2 2 1 1 1 1 1 1 1 1 
for{
     if(하나씩 더 할당 받을 자식 프로세스){
        프로세스들은 할당된 몫만큼 읽는다.
         hisSum과 histogram.bin에 저장 
     }

     if(몫만큼만 할당 받을 자식 프로세스 ){
      프로세스들은 할당된 몫만큼 읽는다.
       hisSum과 histogram.bin에 저장 
     }
}
for(자식 프로세스 만큼){
부모는 wait() 자식프로세스가 끝날 때 까지 기다린다.
}

/* 부가설명 */
● 입력된 자식 프로세스만큼 fork로 생성, 생성된 프로세스에 pid로 자식프로세스인지 확인하고 생성된 프로세스에 고유의 번호 tid를 주고 병렬적으로 수행하도록 했다. [2][3]

● 사용자가 자식 프로세스의 파라미터를 입력하지 않을 경우를 조건을 두어서 1로 인식하도록 구현했다.
    ex) hw2 1 128 == hw2 1 128 1

●  sprintf를 이용해서 자식 프로세스는 자기가 할당받은 data.bin을 처리하도록 알고리즘을 만들어 조건을 걸고 수식을 넣어서 수행 시켰다.

● hw1 1 128 10 같이 데이터 파일 범위와 자식 프로세서의 개수의 파라미터를 받기 위해서 atoi함수를 이용해서 argv의 문자열을 숫자열로 인식하도록 했다. [1]

● 여러 프로세스가 동시에 이용할 수 있으므로 파일의 데이터가 오염을 막기 위해 파일을 open한 뒤 읽거나 쓰기 전에 lock을 얻고, 쓰기가 끝난 뒤 lock을 풀어서 구현 했다. [3]

● 첫 번쨰 과제와 달리 64kb가 아닐때도 구현해야 해서 lseek로 파일사이즈에 대해 유동적으로 처리하도록 구현했다. [2]

● 부모 프로세스는 wait()을 자식 프로세스 개수만큼 반복해서 자식 프로세스들이 종료할때까지 기다리고 끝내도록 했다.[3][4]

● 자식 프로세스는 생성부터 exit()전까지의 시간을 측정하고 부모 프로세스는 첫 자식의 생성시간부터 모든 자식이 수행이 끝나는 것을 기다리고 시간을 측정하다. 
```



**실행환경**

| **OS**        | Windows 10 Pro                             |
| ------------- | ------------------------------------------ |
| **Processor** | Intel(R) Core(TM) I5-7200U (2코어 4스레드) |
| **Memory**    | 8GB                                        |

​     

 **수행시간 표** 

| **프로세스** **개수** | **프로세스 수행시간****(ms)** | **프로그램** **수행시간** |            |            |
| --------------------- | ----------------------------- | ------------------------- | ---------- | ---------- |
| **최소**              | **평균**                      | **최대**                  |            |            |
| **1**                 | 381.635986                    | 381.635986                | 381.635986 | 399.401978 |
| **2**                 | 161.419998                    | 163.769965                | 166.119995 | 173.087993 |
| **3**                 | 105.521996                    | 132.630330                | 181.054001 | 204.621002 |
| **4**                 | 86.028999                     | 88.4289987                | 91.724998  | 127.634003 |
| **5**                 | 85.244003                     | 91.1218002                | 96.150002  | 126.620995 |
| **6**                 | 78.695                        | 88.319164                 | 100.547997 | 129.987003 |
| **7**                 | 135.800995                    | 88.307143                 | 135.800995 | 148.378998 |
| **8**                 | 54.152                        | 65.261748                 | 82.289001  | 142.882004 |
| **9**                 | 56.446999                     | 63.955889                 | 75.737999  | 142.296997 |
| **10**                | 42.125999                     | 56.659339                 | 70.505997  | 131.841995 |
| **11**                | 31.938002                     | 54.363545                 | 73.553001  | 155.099991 |
| **12**                | 34.099998                     | 49.586416                 | 65.546996  | 157.781006 |
| **13**                | 28.618                        | 40.826538                 | 50.507     | 158.432999 |
| **14**                | 26.972                        | 37.4283564                | 50.527     | 158.179001 |
| **15**                | 20.532999                     | 32.162066                 | 39.318001  | 157.658997 |
| **16**                | 23.518                        | 31.724437                 | 37.771     | 174.382004 |

  

## 3. thread pool을 이용하여 histogram 구하기



**문제분석**     

여러 파일에 나누어진 이진 데이터의 히스토그램 (histogram)을 얻는 프로그램을 구현한다. 프로그램은 thread pool을 구성하고 처리해야 할 data ﬁle이 있으면 thread pool에서 대기 상태의 thread를 꺼내서 수행시킨다. 한 data ﬁle의 histogram을 구했으면 전역 변수인 배열 histogram[]에 축적한다. 모든 data ﬁle의 처리가 끝났으면 histogram[]을 histogram.bin에 저장하고 thread pool을 해제한 뒤 종료한다

**알고리즘**

```
./hw3 n1 n2 n3 n4
n1 n2 처리할 데이터 개수 
n3 스레드 개수
n4 버퍼사이즈

stop <-  처리할 데이터,bin 총 개수// 전역변수로 work 스레드들이 같이 사용한다.

for (처리할 데이터 만큼 반복){
     sem_wait(&empty);
     sem_wait(&mutex);
     buffers[in] = j;
     in = (in + 1) % bufsize;
     sem_post(&mutex);
     sem_post(&full);
}
for(n3 반복 ){
create (thread)// n3개 스레드 생성 
}

while(1){// n개의 스레드가 병렬적으로 접급 
if(stop==0)// 처리할 데이터 파일을 모두 수행하면 break
break;

   data.bin파일 처리
 
   sem_wait(&full);
   sem_wait(&mutex);
   data = buffers[out];
   out = (out + 1) % thd->buf;
   sem_post(&mutex);
   sem_post(&empty);
    
   if(stop>0){// 0보다 클때만 변경가능
   
   histogram.bin에 저장 
   stop--;
   }   
}

/* 부가설명 */


● thread를 구조체를 만들어서 안에 각각의 고유번호 시간변수 버퍼를 넣었다. [2]

● 사용자가 3, 4번째 파라미터에 대해서 입력을 안했을 때 경우를 나눠서 구현했다.
    ex)hw3 1 128 = hw3 1 128 1 1

●  sprintf를 이용해서 자식 프로세스는 자기가 할당받은 data.bin을 처리하도록 알고리즘을 만들어 조건을 걸고 수식을 넣어서 수행 시켰다.

● hw1 1 128 10 5 같이 데이터 파일 범위, 스레드의 수와 버퍼사이즈의 파라미터를 받기 위해서 atoi함수를 이용해서 argv의 문자열을 숫자열로 인식하도록 했다. [1]

●  Worker thread는 bounded buﬀer에 내용 (ﬁle name 또는 ﬁle 번호)이 있으면 가져오고 없으면 기다리도록 했다.[4]

● 64kb가 아닐때도 구현해야 해서 lseek로 파일사이즈에 대해 유동적으로 처리하도록 구현했다. [2]

●  배열 histogram[]은 여러 thread들이 변경하는 shared data structure이기 때문에 histogram[]에 대 한 접근을 critical section으로  semaphore 함수들을 사용했다.[2][4]

● 사용자가 처리할 데이터 수를 주면 스레드가 병렬적으로 일을 수행하고 빠른 스레드는 더 많은 일을 하게끔 유동적으로 구현했다.

● 스레드 안에 있는 시간변수를 만들어서 각 스레드의 종료시간까지 시간을 측정[2]
```



 **실행환경**     

| **OS**        | Windows 10 Pro                             |
| ------------- | ------------------------------------------ |
| **Processor** | Intel(R) Core(TM) I5-7200U (2코어 4스레드) |
| **Memory**    | 8GB                                        |

​     

 **수행시간 표**

| **Thread pool** **개수** | **thread** **수행시간****(ms)** | **프로그램** **수행시간** |         |         |
| ------------------------ | ------------------------------- | ------------------------- | ------- | ------- |
| **최소**                 | **평균**                        | **최대**                  |         |         |
| **1**                    | 117.666                         | 117.666                   | 117.666 | 122.317 |
| **2**                    | 101.378                         | 101.678                   | 101.978 | 109.438 |
| **3**                    | 89.778                          | 90.642                    | 91.289  | 97.055  |
| **4**                    | 72.457                          | 73.485                    | 74.121  | 77.653  |
| **5**                    | 53.601                          | 54.83                     | 55.785  | 58.805  |
| **6**                    | 47.235                          | 48.366                    | 49.171  | 54.249  |
| **7**                    | 54.327                          | 56.080                    | 58.077  | 61.079  |
| **8**                    | 46.067                          | 48.034                    | 49.373  | 55.227  |
| **9**                    | 49.154                          | 50.611                    | 52.73   | 55.396  |
| **10**                   | 48.205                          | 50.400                    | 52.049  | 55.563  |
| **11**                   | 49.262                          | 51.631                    | 53.985  | 58.990  |
| **12**                   | 46.82                           | 49.499                    | 51.855  | 54.723  |
| **13**                   | 44.569                          | 47.318                    | 49.307  | 52.362  |
| **14**                   | 48.962                          | 51.134                    | 54.355  | 57.560  |
| **15**                   | 52.401                          | 55.269                    | 59.389  | 61.978  |
| **16**                   | 41.227                          | 45.357                    | 47.27   | 51.665  |

​     

​     
