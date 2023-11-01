#include <stdio.h> 
int main() {
	int sum = 0;
	int a = 0;
	int count = 0;
	while (1) {
	printf("Enter a number :" );
	scanf("%d", &a);
	if (a <= 0) break;
	count++;
	sum += a;
	}
	double avr = (double)sum/count;
	printf("sum is %d\n",sum);
	printf("average is %.2f", avr);
	return 0;
}	
