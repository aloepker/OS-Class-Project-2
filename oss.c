#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void help(){
	printf("The options for the program are:\n");
	printf("-n <number>   this sets the number of processes to launch\n");
	printf("-s <number>   this sets how many processes can run at once\n");
	printf("-t <number>   this sets the number of loops the worker(s) perform\n");
	printf("example:\n./oss -n 3 -s 2 -t 3\n");
}

int main(int argc, char** argv){
	int option;
	int numWorkers = 0;
	int workerLimit = 0;
	int iter = 0;

	while((option = getopt(argc, argv, "hn:s:t:")) != -1){
		switch(option){
			case 'h':
				help();
				return EXIT_SUCCESS;
			case 'n':
				numWorkers = atoi(optarg);
				break;
			case 's':
				workerLimit = atoi(optarg);
				break;
			case 't':
				iter = atoi(optarg);
				break;
			case '?':
				if ((optopt = 'c')){
					printf("Option %c requires an argument\n", optopt);
				} else if (isprint(optopt)){
					printf("Unknown Character '\\x%x'.\n", optopt);
				}
				return 1;
			default:
				help();
				return EXIT_SUCCESS;
		}


	}

	printf("Number of workers Selected:%d\nNumber of Workers at a time:%d\nNumber of loops for each Worker:%d\n", numWorkers, workerLimit, iter);

	char argString[20];
	sprintf(argString, "%d", iter);
	int i,j;
	int stat;
	pid_t childPid;
	for(i=0;i<numWorkers;i++){
		if(i >= workerLimit) {
			wait(NULL);
		}
		childPid = fork();
		if (childPid == -1){
			printf("Fork Process Failed!\n"); 
			return EXIT_FAILURE;
		}
		if (childPid == 0) {
			execl("./worker","./worker", argString, NULL);
		}
	}
	if(childPid != 0) {
		for (j=0;j<numWorkers;j++){
			wait(&stat);
			printf("A Child Process compleated successfully!\n");
		}

	}

}
