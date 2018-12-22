// ConsoleApplication1.cpp : ����΢�ַ���
// \Delta u=x*y,(x,y)\in (0,1)\times(0,1)
// u(0,y)=y,u(1,y)=1-y,u(x,0)=0,u(x,1)=0
//������ָ�ʽ��ϵ���������ɺ��Ҷ�������
//
#include <stdio.h>
#include<stdlib.h>

int main() {
	int N = 5, i, j, matrix_size;//��0��ʼ��ŵ����ձ��ΪN
	int ni = 0;
	double *A, *F;
	double h;
	h = 1.0 / N;
	matrix_size = (N + 1)*(N + 1);
	A = (double *)calloc(sizeof(double), matrix_size*matrix_size);
	F = (double *)calloc(sizeof(double), matrix_size);
	//�������ʼ��Ϊ0
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

	//�±߽�
	j = 0;
	for (i = 0; i < N+1; i++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = 0;
	}

	//�ϱ߽�
	j = N;
	for (i = 0; i <= N; i++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = 0;
	}

	//��߽�
	i = 0;
	for (j = 0; j <= N; j++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) =1;
		*(F + i + j*(N + 1)) = h*j;
	}

	//�ұ߽�
	i = N;
	for (j = 0; j <= N; j++) {
		*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		*(F + i + j*(N + 1)) = 1-h*j;
	}


/********************************************************************************/
/*****************���ϱ߽�������ȥ��������Ϣ*************************************/
	//�±߽�
	int k = 0,r;
	j = 0;
	for (i = 0; i < N + 1; i++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//�ȱ��������ni�У��ҳ������еķ���Ԫ����¼����Ԫ�����кţ��ø��м�ȥni�е�Ԫ�أ���Ӧ���Ҷ���FҲ���������Ĳ���
		for (k = 0; k < matrix_size; k++) {//������
			if (*(A + ni + k*matrix_size) != 0 && k!=ni){//����Ԫ
				for (r = 0; r < matrix_size; r++) {//������
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//��ȥ����
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}


	//�ϱ߽�
	j = N;
	for (i = 0; i <= N; i++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//�ȱ��������ni�У��ҳ������еķ���Ԫ����¼����Ԫ�����кţ��ø��м�ȥni�е�Ԫ�أ���Ӧ���Ҷ���FҲ���������Ĳ���
		for (k = 0; k < matrix_size; k++) {//������
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//����Ԫ
				for (r = 0; r < matrix_size; r++) {//������
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//��ȥ����
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}


	//��߽�
	i = 0;
	for (j = 0; j <= N; j++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//�ȱ��������ni�У��ҳ������еķ���Ԫ����¼����Ԫ�����кţ��ø��м�ȥni�е�Ԫ�أ���Ӧ���Ҷ���FҲ���������Ĳ���
		for (k = 0; k < matrix_size; k++) {//������
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//����Ԫ
				for (r = 0; r < matrix_size; r++) {//������
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//��ȥ����
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}

	//�ұ߽�
	i = N;
	for (j = 0; j <= N; j++) {
		ni = i + j*(N + 1);
		//*(A + i + j*(N + 1) + (i + j*(N + 1))*matrix_size) = 1;
		//�ȱ��������ni�У��ҳ������еķ���Ԫ����¼����Ԫ�����кţ��ø��м�ȥni�е�Ԫ�أ���Ӧ���Ҷ���FҲ���������Ĳ���
		for (k = 0; k < matrix_size; k++) {//������
			if (*(A + ni + k*matrix_size) != 0 && k != ni) {//����Ԫ
				for (r = 0; r < matrix_size; r++) {//������
					*(A + r + k*matrix_size) -= *(A + r + ni*matrix_size);//��ȥ����
				}
				*(F + k) -= *(F + ni);
			}
		}
		*(F + ni) = 0;
		*(A + ni + ni*matrix_size) = 0;
	}

	//for (i = 0; i < matrix_size; i++)
	//	printf("%lf\n", *(F + i));


	/************************ȥ�����������㣬�õ�����ֻ���зǱ߽��ķ��̵�ϵ��������Ҷ���**************/
	double *AA, *FF;
	int var;//��ǰ���������������
	int *index;
	var = matrix_size - 2 * (N - 1) - 2 * (N + 1);
	AA = (double *)calloc(sizeof(double), matrix_size*var);
	FF = (double *)calloc(sizeof(double), var);
	index = (int*)calloc(sizeof(int), 2*(N-1)+2*(N + 1));//�����ڴ��¼��ǰ���������еı��
	if (index == NULL) {
		printf("falied!!!");
	}
	//printf("var=%d\n", var);


	/*********************����ȫ���еı��*****************************/
	//�±߽�
	j = 0;
	k = 0;
	for (i = 0;i < N + 1; i++){
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//�ϱ߽�
	j = N;
	for (i = 0; i <=N && k<2 * (N - 1) +2 * (N + 1); i++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//��߽�
	i = 0;
	for (j = 1; j < N && k<2 * (N - 1) +2 * (N + 1); j++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//�ұ߽�
	i = N;
	for (j = 1; j < N && k<2 * (N - 1)  +2 * (N + 1); j++) {
		*(index + k) = i + j*(N + 1);
		k++;
	}

	//���ȫ���б��
	/*for (i = 0; i < 2 * (N - 1) +2 * (N + 1); i++)
		printf("index=%d\n", *(index + i));*/

	//�õ���ȫ���б��
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
	////������
	//for (i = 0; i < var; i++)
	//	printf("%d\n", *(index_fei + i));



	/***********************************ȥ��������ȫ���к�ȫ����******/
	//ȥ��ϵ������������
	for (i = 0; i < var; i++) {
		for (j = 0; j < matrix_size; j++) {
			*(AA + j + i*matrix_size) = *(A + j + (*(index_fei + i))*matrix_size);
		}
	}

	//���ϵ������
	//for (i = 0; i < var; i++) {
	//	for (j = 0; j < matrix_size; j++)
	//			printf("%lf ", *(AA + i*matrix_size + j));
	//	printf("\n");
	//}
		

	free(A);
	A = (double *)calloc(sizeof(double), var*var);
	//ȥ��ϵ������������
	for (i = 0; i < var; i++) {
		for (j= 0; j<var; j++) {
			*(A + j + i*var) = *(AA + (*(index_fei+j)) + i*matrix_size);
		}
	}
	free(AA);

	////���ϵ������
	for (i = 0; i < var; i++) {
		for (j = 0; j < var; j++)
			printf("%lf ", *(A + i*var + j));
		printf("\n");
	}



	/***********************ȥ���Ҷ�������������*****************************************/
	for (i = 0; i < var; i++) {
		*(FF + i) = *(F + *(index_fei + i));
	}
	free(F);

	
	

	//���������뵽�ļ�
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
	//ʵ�ֶ�ɫ����
	int L = 1;//��¼��ɫ����
	int *c;//��¼ÿ���ڵ����������ɫ��
	int *I;//���нڵ���ɵļ���
	int *T;//�Ѿ���ǹ���ɫ�Ľڵ㼯��
	int num_T = 0, adj_num = 0;//TODO
	int *S;//��¼��δ�����ɫ�Ľڵ�
	int *t;//��������
	int flag = 0;//set S=I\T
	int kk = 0;//select kk \in S
	int *adj;//��¼kk�ڵ���ٽӵ�

	c = (int *)calloc(sizeof(int), var + 1);
	I = (int *)calloc(sizeof(int), var + 1);
	T = (int *)calloc(sizeof(int), var + 1);
	S = (int *)calloc(sizeof(int), var + 1);
	t = (int *)calloc(sizeof(int), var + 1);
	adj = (int *)calloc(sizeof(int), var + 1);
	if (c == NULL || I == NULL || T == NULL || S == NULL || t == NULL) {
		printf("failed!!!!");
	}


	//��ʼ��
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
			for (j = 1; j < num_T + 1; j++) {//��0Ϊ������
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

		for (i = 1, k = 1; i <var + 1; i++) {//Ѱ��kk����ٽӵ�
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


	//����c�洢�˶�Ӧ�������ɫ��ţ�c��һ��Ԫ��Ϊ����Ԫ��
	//L�洢��Ӧ��ɫ����


	free(c);
	fclose(fp);
	free(A);
	free(FF);

	system("pause");
	return 0;
}
