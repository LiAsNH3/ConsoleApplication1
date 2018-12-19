// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include<stdlib.h>

int main() {
	int N = 4, i, j, matrix_size;//从0开始编号到最终编号为N
	int ni = 0;
	double *A, *F;
	double h;
	h = 1.0 / N;
	matrix_size = (N + 1)*(N + 1);
	A = (double *)calloc(sizeof(double), matrix_size*matrix_size);
	F = (double *)calloc(sizeof(double), matrix_size);
	//将矩阵初始化为0
	for (i = 0; i < matrix_size; i++) {
		for (j = 0; j < matrix_size; j++) {
			*(A + i + j*matrix_size) = 0;
		}
		*(F + i) = 0;
	}


	printf("h=%lf\n", h);
	for (i = 1; i<N; i++) {
		for (j = 1; j < N; j++) {
			ni = i + j*(N + 1);
			//*(A + i + j * (N + 1) + (i + j * (N + 1)) * N * N) = -4;
			*(A + ni + ni*matrix_size) = -4;
			//*(A + i + j * (N + 1) + (i + (j + 1) * (N + 1)) * N * N) = 1;
			*(A + ni + (i + (j + 1) * (N + 1))*matrix_size) = 1;
			//*(A + i + j * (N + 1) + (i + (j - 1) * (N + 1)) * N * N) = 1;
			*(A + ni + (i + (j - 1) * (N + 1))*matrix_size) = 1;
			//*(A + i + j * (N + 1) + (i + 1 + j * (N + 1)) * N * N) = 1;
			*(A + ni + (i + 1 + j * (N + 1))*matrix_size) = 1;
			//*(A + i + j * (N + 1) + (i - 1 + j * (N + 1)) * N * N) = 1;
			*(A + ni + (i - 1 + j * (N + 1))*matrix_size) = 1;
			*(F + ni) = h*i*h*j*h*h;
			printf("%lf \n", *(F + ni));
		}
	}

	//下边界
	j = 0;
	for (i = 0; i < N+1; i++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = 0;
	}

	//上边界
	j = N;
	for (i = 0; i <= N; i++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = 0;
	}

	//左边界
	i = 0;
	for (j = 0; j <= N; j++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = h*j;
	}

	//右边界
	i = N;
	for (j = 0; j <= N; j++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		*(F + i + j*(N + 1)) = 1-h*j;
	}


	//整合边界条件，去掉多余信息
	//下边界
	int k = 0,r;
	j = 0;
	for (i = 0; i < N + 1; i++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		for (k = 0; k < matrix_size; k++) {
			if (*(A + ni + k*matrix_size) != 0) {
				for (r = 0; r < matrix_size; r++) {
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);
				}
			}
		}
		*(F + i + j*(N + 1)) = 0;
	}

	//经数据输入到文件
	FILE *fp;
	fp = fopen("matrix.txt", "w+");
	if (fp == NULL)printf("the file open failed!!!");

	for (i = 0; i<matrix_size; i++) {
		for (j = 0; j<matrix_size; j++) {
			fprintf(fp, "%lf    ", *(A + i + j*matrix_size));
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	fp = fopen("F.txt", "w+");
	if (fp == NULL)printf("the file open failed!!!");
	for (i = 0; i<matrix_size; i++) {
		fprintf(fp, "%lf\n", *(F + i));
	}
	fclose(fp);
	free(A);
	free(F);
	system("pause");
	return 0;
}
