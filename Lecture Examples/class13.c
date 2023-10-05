/* Purpose:
 * Author:
 * Date: Fall 2023
 * Persons discussed w/:
 * References:
 */

#include <stdio.h>

void swapping(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void bs(int n, int a[]){
//void bs(int n, int a[n]){ //[n] has no purpose here, basically
	for (int j = 0; j < n-1; j++) {
		for (int i = 0; i < n-1; i++) {//This line could have an error;
			if (a[i] > a[i+1]) {//Swapping; correctly done?
				swapping(&a[i], &a[i+1]);
			}
		}
	}
	return;
}

int main(int argc, char **argv) { //int main() {
	int n; 
	printf("Enter the number of integers, followed by these integers: ");
	scanf("%d", &n); //In general, we need to check whether we read in a value for `n`;
	int a[n];
	for (int i = 0; i < n; i++)
		if (scanf("%d", &a[i]) != 1) {
			printf("\n");
			return 1;
		}

	bs(n, a); //Pass by value: What is a?

	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}

