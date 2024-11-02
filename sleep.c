#include "types.h"
#include "user.h"


int main(int argc, char *argv[]){
	int num_ticks = atoi(argv[1]);
	if(argc != 2){
		printf(1, "Please enter sleep <number of ticks>\n");
		exit();
	}
	if(num_ticks <=0)printf(1, "Invalid number of ticks\n");
	sleep(num_ticks);
	exit();
}
