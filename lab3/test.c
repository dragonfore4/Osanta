#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int i, sum = 0;
	printf("argc = %d\n", argc);
	printf("Let's see what is in argv[]\n");

	if(argc > 1) {
		for (i = 1; i < argc; i++) {
			printf("argv[%d] = %s\n", i, argv[i]);
			sum += atoi(argv[i]);
		}
		printf("%d",sum);
	}
	return 0;
}

