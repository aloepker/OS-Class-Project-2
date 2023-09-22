#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	if(argc>1){
		printf("Starting loop\n");
		int i;
		int j = atoi(argv[1]);
		for (i=0;i<j;i++){
			printf("Worker PID:%d PPID:%d Iteration: %d Before Sleeping\n",getpid(), getppid(), i+1);
			sleep(1);
			printf("Worker PID:%d PPID:%d Iteration: %d After Sleeping\n",getpid(), getppid(), i+1);
		}
	} else {
		printf("incorrect number of arguments\n");
	}
}
