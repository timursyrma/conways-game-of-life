#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

void print_matrix(uint8_t *matrix, int n, int m) {
	for(int i = 0; i < n * m; i++) {
		printf("%d ", matrix[i]);
	}
}

uint8_t *convert_bit_to_byte_matrix(int **bit_matrix, int n, int m) {
	size_t new_m = round(m * 1.0 / 8);
	uint8_t *byte_matrix = malloc(n * new_m * sizeof(uint8_t));

	for(int i = 0, k = n * new_m - 1; i < n; i++) {
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
	FILE *fp = fopen("./image.bmp", "wb"); 

	BITMAPFILEHEADER bf;
	memcpy(&bf.bfType, "BM", 2);
	bf.bfSize = 0;
	bf.bsReserved = 0;
	bf.bfOffBits = 62;

	BITMAPINFOHEADER bi;
	bi.biSize = 40;
	bi.biWidth = 8;
	bi.biHeight = 8;
	bi.biPlanes = 1;
	bi.biBitCount = 1;
	bi.biComperssion = 0;
    bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

	RGBQUAD white;
	white.rgbBlue = 255;
	white.rgbGreen = 255;
	white.rgbRed = 255;
	white.rgbReserved = 0;

	RGBQUAD black;
	black.rgbBlue = 0;
	black.rgbGreen = 0;
	black.rgbRed = 0;
	black.rgbReserved = 0;

	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(&white, sizeof(RGBQUAD), 1, fp);
	fwrite(&black, sizeof(RGBQUAD), 1, fp);

	int n;
	int m;
	printf("Enter n and m\n");
	scanf("%d %d", &n, &m);
	int adj_m = m + (32 - m % 32);

	int **board = (int **)malloc(n * sizeof(int *));

	for(int i = 0; i < n; i++) {
		board[i] = malloc(adj_m * sizeof(int));
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	uint8_t *byte_matrix = convert_bit_to_byte_matrix(board, n, adj_m);

	printf("\n");

	print_matrix(byte_matrix, n, round(adj_m * 1.0 / 8));

	fwrite(byte_matrix, 1, n * round(adj_m * 1.0 / 8), fp);

	free(board);
	// free(byte_matrix)

	fclose(fp);
}

