// ConsoleApplication1.cpp : 对于微分方程
// \Delta u=x*y,(x,y)\in (0,1)\times(0,1)
// u(0,y)=y,u(1,y)=1-y,u(x,0)=0,u(x,1)=0
//的五点差分格式的系数矩阵生成和右端项生成
//
#include <stdio.h>
#include<stdlib.h>

int main() {
	int N = 5, i, j, matrix_size;//从0开始编号到最终编号为N
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
			//printf("%lf \n", *(F + ni));
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

	//for (i = 0; i < matrix_size; i++)
	//	printf("%lf\n", *(F + i));


	/************************去掉矩阵多余的零，得到最终只含有非边界点的方程的系数矩阵和右端项**************/
	double *AA, *FF;
	int var;//当前矩阵的行数和列数
	int *index;
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
			*(A + j + i*var) = *(AA + (*(index_fei+j)) + i*matrix_size);
		}
	}
	free(AA);

	////输出系数矩阵
	for (i = 0; i < var; i++) {
		for (j = 0; j < var; j++)
			printf("%lf ", *(A + i*var + j));
		printf("\n");
	}



	/***********************去掉右端项里面多余的零*****************************************/
	for (i = 0; i < var; i++) {
		*(FF + i) = *(F + *(index_fei + i));
	}
	free(F);

	
	

	//将数据输入到文件
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


	/***************************************************************************************/
	//实现多色排序
	int L = 1;//记录颜色种数
	int *c;//记录每个节点所分配的颜色号
	int *I;//所有节点组成的集合
	int *T;//已经标记过颜色的节点集合
	int num_T = 0, adj_num = 0;//TODO
	int *S;//记录尚未标记颜色的节点
	int *t;//辅助数组
	int flag = 0;//set S=I\T
	int kk = 0;//select kk \in S
	int *adj;//记录kk节点的临接点

	c = (int *)calloc(sizeof(int), var + 1);
	I = (int *)calloc(sizeof(int), var + 1);
	T = (int *)calloc(sizeof(int), var + 1);
	S = (int *)calloc(sizeof(int), var + 1);
	t = (int *)calloc(sizeof(int), var + 1);
	adj = (int *)calloc(sizeof(int), var + 1);
	if (c == NULL || I == NULL || T == NULL || S == NULL || t == NULL) {
		printf("failed!!!!");
	}


	//初始化
	for (i = 0; i < var + 1; i++) {
		*(c + i) = 0;
		*(I + i) = i;
		*(T + i) = 0;
		*(S + i) = 0;
		*(t + i) = 0;
		*(adj + i) = 0;
	}
	*(c + 1) = L;
	*(T + 1) = 1;

	num_T = 1;



	while (num_T != var) {
		kk = 0;
		for (i = 1; i < var + 1; i++) {
			flag = 0;
			for (j = 1; j < num_T + 1; j++) {//以0为结束点
				if (*(I + i) == *(T + j)) {
					flag = 1;
					break;
				}
			}
			if (flag != 1) {
				kk = (*(I + i));
				printf("kk=%d \n", kk);
				break;
			}
		}

		for (i = 1; i < var + 1; i++)*(adj + i) = 0;

		for (i = 1, k = 1; i <var + 1; i++) {//寻找kk点的临接点
			if (*(A + i - 1 + (kk - 1)*var) != 0) {
				*(adj + k) = i;
				adj_num = k - 1;
				k++;
			}
		}

		adj_num = adj_num + 1;
		for (i = 1; i <adj_num + 1; i++) {
			flag = 0;
			for (j = 1; j < num_T + 1; j++) {
				if (*(adj + i) == *(T + j)) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				*(t + *(c + *(adj + i))) = 1;
			}
		}

		for (i = 0; i < var; i++) {
			printf("%d ", *(adj + i));
		}
		printf("\n");
		for (i = 0; i < var; i++) {
			printf("%d ", *(T + i));
		}
		printf("\n");
		for (i = 0; i < var; i++) {
			printf("%d ", *(t + i));
		}
		printf("\n");


		for (j = 1; j <= var; j++) {
			if (*(t + j) == 0)break;
		}

		*(c + kk) = j;
		if (j == L + 1)L++;

		for (i = 1; i <adj_num + 1; i++) {
			flag = 0;
			for (j = 1; j < num_T + 1; j++) {
				if (*(adj + i) == *(T + j)) {
					*(t + *(c + *(adj + i))) = 0;
					break;
				}
			}
		}

		*(T + num_T) = kk;
		num_T++;
	}
	printf("L=%d\n", L);
	for (i = 0; i < var; i++) {
		printf("%d\n", *(c + i));
	}
	
	free(I);
	free(S);
	free(adj);
	free(t);
	free(T);


	//向量c存储了对应顶点的颜色编号，c第一个元素为无用元素
	//L存储对应颜色种类


	free(c);
	fclose(fp);
	free(A);
	free(FF);

	system("pause");
	return 0;
}
