//#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

int global;
static int pin[3] = {0,2,3};
static pthread_t threadPs[2] = {0,0};
static pthread_t ppid = 0;

void *blink1(void *);
void *blink2(void *);
int main (void) {
	int i,j,k, globalZwei = 0;
//		wiringPiSetup();
    for(i = 0; i < 3; i++) {
//		pinMode(pin[i],OUTPUT);
    }
	pthread_create(&threadPs[0], NULL, blink1, &globalZwei);
	pthread_create(&threadPs[1], NULL, blink2, &globalZwei);
	ppid = getpid();
	printf("Elternprozess: Prozessid: %d\n",(int)ppid);
	for (i = 0; i < 2; i++) {
		printf("Kindprozess %d: Threadid: %d\n", i + 1 ,threadPs[i]);
	}
	for (j = 0; j > 3; j++) {
		sleep(4);
		system("ps -e");
	}
	pthread_join(threadPs[0],NULL);
	pthread_kill(threadPs[1], 9);
	for(k = 0; k < 3; k++) {
		//digitalWrite(pin[i],0);
	}
	return 0;
}

void *blink1(void *globalZwei) {
	int i;
	global = 0;
	globalZwei = 0;
	for (i = 0; i < 5; i++) {
		int n = global % 3;
//		digitalWrite(pin[n],1);
		printf("Pin %d blinkt - Global2: %d\n", pin[n], globalZwei);
		sleep(1);
//		digitalWrite(pin[n],0);
		sleep(1);
	}
}

void *blink2(void *globalZwei) {
	while (1) {
		int n = global % 3;
//		digitalWrite(pin[n],1);
        	printf("Pin %d blinkt\n", pin[n]);
		sleep(1);
//		digitalWrite(pin[n],0);
		sleep(1);
        	global = global + 1;
        	globalZwei = globalZwei + 1;
		printf("Global: %d - Global2: %d\n", global, globalZwei);
	}
}
