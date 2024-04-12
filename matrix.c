#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_matrix(int **matrix, int n, int m) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int *convert_bit_to_byte_matrix(int **bit_matrix, int n, int m, int w) {
	int *byte_matrix = malloc(n * w * sizeof(int));

	int k = n * w - 1;
	for(int i = n - 1; i > -1; i--) {
		for(int j = m - 1; j > - 1; j -= 8) {
			int val = 0;
			for (int t = 0; t < 8; t++) {
				val += bit_matrix[i][j - t] * pow(2, t);
			}
			byte_matrix[k--] = val;
		}
	}

	return byte_matrix;
}

int main() {
	int n = 6;
	int m = 5;
	int w = m + (32 - m % 32);
	int **matrix = (int **)malloc(n * sizeof(int *));

	for(int i = 0; i < n; i++) {
		matrix[i] = malloc(w * sizeof(int));
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	convert_bit_to_byte_matrix(matrix, n, w, w / 8);

	return 0;
}
