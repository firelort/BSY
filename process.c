//#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void blink1(int *, int *);
void blink2(int *, int *);
int main (void) {
	int pin[3] = {0,2,3};
	pid_t cpids[2] = {0,0};
	pid_t ppid = 0;
	int i,j,k = 0;
	int exitstatus;
//		wiringPiSetup();
    int global;
    for(i = 0; i < 3; i++) {
//		pinMode(pin[i],OUTPUT);
    }

	int temp = fork();
	if (temp == 0) {
	    //Kindprozess
		cpids[0] = getpid();
		printf("Kindprozess 1: Prozessid: %d\n",cpids[0]);
		blink1(pin, &global);
	} else {
	    //Elternprozess
        int temp2 = fork();
        if (temp2 == 0) {
            //Kindprozess 2
            cpids[1] = getpid();
            printf("Kindprozess 2: Prozessid: %d\n",cpids[1]);
            blink2(pin, &global);
        } else {
            global = 99;
            //Elternprozess mit seinen Aufgaben
            ppid = getpid();
            printf("Elternprozess: Prozessid: %d\n",ppid);
            for (j = 0; j > 3; j++) {
                sleep(4);
                system("ps -e");
                printf("Prozessübersicht beendet.\n");
            }
            wait(&exitstatus);
            kill(cpids[1], SIGKILL);
        }
	}

	if (!getppid()) {
		for(k = 0; k < 3; k++) {
			//digitalWrite(pin[i],0);
		}
	}
	printf("Global: %d\n", global);
	return 0;
}

void blink1(int *pin, int *global) {
	int i;
	*global = 0;
    printf("Global(blink1): %d\n", *global);
	for (i = 0; i < 5; i++) {
		int n = (*global) % 3;
//		digitalWrite(pin[n],1);
        printf("Pin %d ist aktiv.\n",pin[n]);
		sleep(1);
//		digitalWrite(pin[n],0);
		sleep(1);
	}
}

void blink2(int *pin, int *global) {
	while (1) {
		int n = (*global) % 3;
//		digitalWrite(pin[n],1);
        printf("Pin %d ist aktiv.\n",pin[n]);
		sleep(1);
//		digitalWrite(pin[n],0);
    	sleep(1);
		printf("Global(blink2): %d\n", *global);
        (*global) = (*global) +1;
	}
}
