#include <stdio.h>

int main() {
	int arow, acol;
	printf("Enter the rows and columns for Matrix a: ");
	scanf("%d %d", &arow, &acol);
	int a[arow][acol];

	for (int i = 0; i < arow; i++) {
		for (int j = 0; j < acol; j++) {
			printf("Enter the number for the a[%d][%d]\n: ",i,j);
			scanf("%d", &a[i][j]);
		}
	}

	
	return 0;
}
