// ConsoleApplication1.cpp : 对于微分方程
// \Delta u=x*y,(x,y)\in (0,1)\times(0,1)
// u(0,y)=y,u(1,y)=1-y,u(x,0)=0,u(x,1)=0
//的五点差分格式的系数矩阵生成和右端项生成
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
			*(A + ni + ni*matrix_size) = -4;
			*(A + (i + (j + 1) * (N + 1)) + ni*matrix_size) = 1;
			*(A + (i + (j - 1) * (N + 1)) + ni*matrix_size) = 1;
			*(A + (i + 1 + j * (N + 1)) + ni*matrix_size) = 1;
			*(A + (i - 1 + j * (N + 1)) + ni*matrix_size) = 1;
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


/********************************************************************************/
/*****************整合边界条件，去掉多余信息*************************************/
	//下边界
	int k = 0,r;
	j = 0;
	for (i = 0; i < N + 1; i++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//先遍历矩阵的ni列，找出该列中的非零元，记录非零元所在行号，用该行减去ni行的元素，对应的右端项F也进行这样的操作
		for (k = 0; k < matrix_size; k++) {//遍历列
			if (*(A + ni + k*matrix_size) != 0 && k!=ni){//非零元
				for (r = 0; r < matrix_size; r++) {//遍历行
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//减去操作
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}


	//上边界
	j = N;
	for (i = 0; i <= N; i++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//先遍历矩阵的ni列，找出该列中的非零元，记录非零元所在行号，用该行减去ni行的元素，对应的右端项F也进行这样的操作
		for (k = 0; k < matrix_size; k++) {//遍历列
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//非零元
				for (r = 0; r < matrix_size; r++) {//遍历行
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//减去操作
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}


	//左边界
	i = 0;
	for (j = 0; j <= N; j++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//先遍历矩阵的ni列，找出该列中的非零元，记录非零元所在行号，用该行减去ni行的元素，对应的右端项F也进行这样的操作
		for (k = 0; k < matrix_size; k++) {//遍历列
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//非零元
				for (r = 0; r < matrix_size; r++) {//遍历行
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//减去操作
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}

	//右边界
	i = N;
	for (j = 0; j <= N; j++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//先遍历矩阵的ni列，找出该列中的非零元，记录非零元所在行号，用该行减去ni行的元素，对应的右端项F也进行这样的操作
		for (k = 0; k < matrix_size; k++) {//遍历列
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//非零元
				for (r = 0; r < matrix_size; r++) {//遍历行
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//减去操作
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}

	for (i = 0; i < matrix_size; i++)
		printf("%lf\n", *(F + i));


	/************************去掉矩阵多余的零，得到最终只含有非边界点的方程的系数矩阵和右端项**************/
	double *AA, *FF;
	int var,*index;//当前矩阵的行数
	var = matrix_size - 2 * (N - 1) - 2 * (N + 1);
	AA = (double *)calloc(sizeof(double), matrix_size*var);
	FF = (double *)calloc(sizeof(double), var);
	index = (int*)calloc(sizeof(int), 2*(N-1)+2*(N + 1));//分配内存记录当前矩阵中零行的标号
	if (index == NULL) {
		printf("falied!!!");
	}
	//printf("var=%d\n", var);


	/*********************计算全零行的标号*****************************/
	//下边界
	j = 0;
	k = 0;
	for (i = 0;i < N + 1; i++){
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//上边界
	j = N;
	for (i = 0; i <=N && k<2 * (N - 1) +2 * (N + 1); i++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//左边界
	i = 0;
	for (j = 1; j < N && k<2 * (N - 1) +2 * (N + 1); j++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//右边界
	i = N;
	for (j = 1; j < N && k<2 * (N - 1)  +2 * (N + 1); j++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//输出全零行标号
	/*for (i = 0; i < 2 * (N - 1) +2 * (N + 1); i++)
		printf("index=%d\n", *(index + i));*/

	//得到非全零行标号
	int *index_fei;
	index_fei = (int*)calloc(sizeof(int), var);
	for (i = 0, j = 0; j < matrix_size; j++) {
		for (k = 0; k < 2 * (N - 1)  +2 * (N + 1); k++) {
			if (j == *(index+k))break;
		}
		if (k >= 2 * (N - 1)  +2 * (N + 1)) {
			*(index_fei + i) = j;
			i++;
		}
	}
	////输出标号
	//for (i = 0; i < var; i++)
	//	printf("%d\n", *(index_fei + i));



	/***********************************去掉矩阵中全零行和全零列******/
	//去掉系数矩阵中零行
	for (i = 0; i < var; i++) {
		for (j = 0; j < matrix_size; j++) {
			*(AA + j + i*matrix_size) = *(A + j + (*(index_fei + i))*matrix_size);
		}
	}

	//输出系数矩阵
	//for (i = 0; i < var; i++) {
	//	for (j = 0; j < matrix_size; j++)
	//			printf("%lf ", *(AA + i*matrix_size + j));
	//	printf("\n");
	//}
		

	free(A);
	A = (double *)calloc(sizeof(double), var*var);
	//去掉系数矩阵中零列
	for (i = 0; i < var; i++) {
		for (j= 0; j<var; j++) {
			*(A + j + i*var) = *(AA + (*(index_fei+j)) + i*var);
		}
	}
	free(AA);

	////输出系数矩阵
	//for (i = 0; i < var; i++) {
	//	for (j = 0; j < var; j++)
	//		printf("%lf ", *(A + i*var + j));
	//	printf("\n");
	//}



	/***********************去掉右端项里面多余的零*****************************************/
	//寻找第一个不为零的元的标号
	for (i = 0; i < var; i++) {
		*(FF + i) = *(F + *(index_fei + i));
	}
	free(F);

	
	

	//经数据输入到文件
	FILE *fp;
	fp = fopen("matrix.txt", "w+");
	if (fp == NULL)printf("the file open failed!!!");

	for (i = 0; i<var; i++) {
		for (j = 0; j<var; j++) {
			fprintf(fp, "%lf    ", *(A + i + j*var));
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	fp = fopen("F.txt", "w+");
	if (fp == NULL)printf("the file open failed!!!");
	for (i = 0; i<var; i++) {
		fprintf(fp, "%lf\n", *(FF + i));
	}
	fclose(fp);
	free(A);
	free(FF);
	system("pause");
	return 0;
}
