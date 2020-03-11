#include "stdafx.h"
#include <conio.h>
#include <cstdlib>
#include<iostream>

int* TransformToBinary(int);
void XOR(int*, int*);
int* XOR_II(int*, int*, int);
void Multiplication(int*, int*);
void DisplayVector(int*, char*, int);
int* Generation(int, int, int);
int Inverse(int*);
void LeftShift(int*, int);
void LeftShiftByValue(int*, int, int);
void RightShift(int*, int);
void CopyAndInvertVector(int*, int*, int, int);
void InitializeWithZero(int*, int);
void PointAddition(int, int, int, int);
int* XOR_Addition(int*, int*, int*, int*, int*);

int _tmain(int argc, _TCHAR* argv[])
{
	
	int no_a = 349957;
	int no_b = 134137;

	int* alpha = (int*)malloc(24 * sizeof(int));
	int* beta = (int*)malloc(24 * sizeof(int));

	alpha = TransformToBinary(no_a);
	beta = TransformToBinary(no_b);

	DisplayVector(alpha, "Alpha", 24);
	DisplayVector(beta, "Beta ", 24);
	
	//XOR(alpha, beta);

	//int* sum = (int*)malloc(24 * sizeof(int));
	//sum = XOR_II(alpha, beta);
	//DisplayVector(sum, "Suma", 24);

	
	Multiplication(alpha, beta);
	

   /*
   int* galois_vector = (int*)malloc(5 * sizeof(int));

	for (int i = 0; i < 5; i++)
	{
	galois_vector[i] = 0;
	}

	galois_vector = Generation(15,4,15);
	DisplayVector(galois_vector, "Rezultat", 5);
	*/

	//PointAddition(5, 6, 3, 8);

	/*
	int* result = (int*)malloc(5 * sizeof(int));
	result[0] = 0;
	result[1] = 0;
	result[2] = 1;
	result[3] = 1;
	result[4] = 0;

	int power;
	power = Inverse(result);
	printf("Puterea este: %d", power);
	
	/*
	free(alpha);
	free(beta);
	free(sum);
	free(galois_vector);
	free(result);*/
	
	int a;
	std::cin >> a;

	return 0;
}

int* TransformToBinary(int number)
{
	int j = 0;
	int k = 23; //Last index of vector 
	int* vector_inverted = (int*)malloc(24 * sizeof(int));
	int* vector_final = (int*)malloc(24 * sizeof(int));

	//Initialize vectors with 0
	InitializeWithZero(vector_inverted, 24);
	InitializeWithZero(vector_final, 24);


	//Convert to binary and invert vector
	while (number > 0)
	{
		vector_inverted[j] = number % 2;

		number = number / 2;

		vector_final[k] = vector_inverted[j];
		j++;
		k--;
	}

	free(vector_inverted);

	return vector_final;

	//free(vector_final);
}

void XOR(int* alpha, int* beta)
{
	int* sum = (int*)malloc(24 * sizeof(int));

	//XOR operation
	for (int i = 0; i < 24; i++)
	{
		sum[i] = (alpha[i] + beta[i]) % 2;
	}

	DisplayVector(sum, "Sum  ", 24);

	free(sum);
}

int* XOR_II(int* alpha, int* beta, int size)
{
	int* sum = (int*)malloc(size * sizeof(int));

	//XOR operation
	for (int i = 0; i < size; i++)
	{
		sum[i] = (alpha[i] + beta[i]) % 2;
	}

	return sum;
	free(sum);
}

void Multiplication(int* alfa, int* beta)
{
	int* product = (int*)malloc(48 * sizeof(int));
	int* alpha_shifted = (int*)malloc(48 * sizeof(int));
	int* alpha_aux = (int*)malloc(48 * sizeof(int));

	InitializeWithZero(product, 48);
	InitializeWithZero(alpha_shifted, 48);
	InitializeWithZero(alpha_aux, 48);

	int w = 8, m = 3;

	CopyAndInvertVector(alfa, alpha_aux, 24, 48);
	DisplayVector(alpha_aux, "Alpha_a", 48);

	//Multiplication algorithm (unfinished)
	for (int j = w - 1; j >= 0; j--)
	{
		printf("\nFOR1 - \n");
		for (int i = 0; i <= m - 1; i++)
		{
			printf("\nFOR2 - \n");
			if (beta[23 - (w*i + j)] == 1)
			{
				int val = w*i + j;
				
				// A << w*i + j
				LeftShiftByValue(alpha_aux, 48, w*i+j);
				DisplayVector(alpha_aux, "aux_01", 48);

				//C = C + A << w*i + j
				product = XOR_II(product, alpha_aux, 48);
				DisplayVector(product, "produc", 48);
			}
		}

		// C<<1
		LeftShift(product, 48);
		DisplayVector(product, "Pro_sh", 48);
		printf("\n");
	}

	//free(product);
	//free(alpha_shifted);
}

void DisplayVector(int* vector, char* message, int lenght)
{
	printf("\n%s is:", message);
	for (int i = 0; i < lenght; i++)
	{
		if (i % 8 == 0)
		{
			printf("%s", " ");
		}

		printf("%d", vector[i]);
	}
}

int* Generation(int power, int grad, int return_power)
{
	//x^4+x+1
	int* generating_polynomial = (int*)malloc(5 * sizeof(int));
	generating_polynomial[0] = 1;
	generating_polynomial[1] = 0;
	generating_polynomial[2] = 0;
	generating_polynomial[3] = 1;
	generating_polynomial[4] = 1;

	//x^1
	int* galois_b = (int*)malloc(5 * sizeof(int));
	galois_b[0] = 0;
	galois_b[1] = 0;
	galois_b[2] = 0;
	galois_b[3] = 0;
	galois_b[4] = 1;

	int counter = 0;

	while (power > 0)
	{
		LeftShift(galois_b, 5);

		//Verify if msb is 1 
		if (galois_b[0] == 1)
		{
			galois_b = XOR_II(galois_b, generating_polynomial, 5);
		}

		printf("\nPolinomul shiftat: ");
		
		for (int i = 0; i < 5; i++)
		{
			printf("%d", galois_b[i]);
		}

		power--;
		counter++;

		if (return_power == counter)
		{
			return galois_b;
		}

		
	}

	//return galois_b;

	free(generating_polynomial);
	free(galois_b);
}

int Inverse(int* result)
{
	//x^4+x+1
	int* generating_polynomial = (int*)malloc(5 * sizeof(int));
	generating_polynomial[0] = 1;
	generating_polynomial[1] = 0;
	generating_polynomial[2] = 0;
	generating_polynomial[3] = 1;
	generating_polynomial[4] = 1;

	//Final vector
	int* vector_stop = (int*)malloc(5 * sizeof(int));
	vector_stop[0] = 0;
	vector_stop[1] = 0;
	vector_stop[2] = 0;
	vector_stop[3] = 0;
	vector_stop[4] = 1;

	//Counter
	//This will represent the power of our int* result polynomial
	int power = 0;

	bool ok = false;

	//While our result != vector stop (ok == false), we iterate through our while
	while (ok == false)
	{
		for (int i = 0; i < 4; i++)
			if ((result[i] == vector_stop[i]) && (result[4] == 1))
			{
				ok = true;
			}
			else
			{
				ok = false;
				break;
			}

		if (ok == true)
		{
			return power;
		}
		else
		{
			//If lsb is 1, we do XOR
			if (result[4] == 1)
			{
				result = XOR_II(result, generating_polynomial, 5);
				power++;

				if (result[0] == 1)
				{
					DisplayVector(result, "result", 5);
					RightShift(result, 5);
					DisplayVector(result, "res_sh", 5);
				}
			}
			
			//If lsb isn't equal to 1, we right-shift the vector
			else
			{
				RightShift(result, 5);
				power++;
			}
		}
	}
	free(generating_polynomial);
	free(vector_stop);

	return power;
}

void LeftShift(int* vector, int size)
{
	int* vector_aux = (int*)malloc(size * sizeof(int));

	for (int k = 0; k < size; k++)
	{
		vector_aux[k] = 0;
	}

	int m = size - 1;

	for (int k = size - 1; k >= 0; k--)
	{
		if (m >= 0)
		{
			vector_aux[k - 1] = vector[m];
			m--;
		}
	}

	for (int i = 0; i < size; i++)
	{
		vector[i] = vector_aux[i];
	}

	//free(vector_aux);
}

void RightShift(int* vector, int size)
{
	int* vector_aux = (int*)malloc(size * sizeof(int));

	for (int k = 0; k < size; k++)
	{
		vector_aux[k] = 0;
	}

	int m = 0;

	for (int k = 0; k <= size - 2; k++)
	{
		if (m <= size - 1)
		{
			vector_aux[k + 1] = vector[m];
			m++;
		}
	}
	vector_aux[0] = 0;

	for (int i = 0; i < size; i++)
	{
		vector[i] = vector_aux[i];
	}

	//free(vector_aux);
}

void CopyAndInvertVector(int* vector_original, int* vector_final, int size_original, int size_final)
{
	int* vector_aux = (int*)malloc(size_final * sizeof(int));

	InitializeWithZero(vector_aux, size_final);

	for (int i = 0; i < size_original; i++)
	{
		vector_aux[i] = vector_original[i];
	}

	for (int i = 1; i <= size_original; i++)
	{
		vector_final[size_final - i] = vector_aux[size_original - i];
	}
}

void InitializeWithZero(int* vector, int size)
{
	for (int i = 0; i < size; i++)
	{
		vector[i] = 0;
	}
}

void LeftShiftByValue(int* vector, int vector_size, int shift_size)
{
	int* vector_aux = (int*)malloc(vector_size * sizeof(int));

	InitializeWithZero(vector_aux, vector_size);

	for (int i = 0; i < vector_size; i++)
	{
		if ((shift_size + i) < vector_size)
		{
			vector_aux[i] = vector[shift_size + i];
		}
	}

	for (int i = 0; i < vector_size; i++)
	{
		vector[i] = vector_aux[i];
	}
}

void PointAddition(int X_p, int X_q, int Y_p, int Y_q)
{
	int lambda = 0;
	int power_x = 0;
	int power_y = 0;

	int a = 4;

	int* vector_Xp = (int*)malloc(5 * sizeof(int));
	int* vector_Xq = (int*)malloc(5 * sizeof(int));
	int* vector_Xr = (int*)malloc(5 * sizeof(int));

	int* vector_Yp = (int*)malloc(5 * sizeof(int));
	int* vector_Yq = (int*)malloc(5 * sizeof(int));
	int* vector_Yr = (int*)malloc(5 * sizeof(int));

	int* vector_x_XOR = (int*)malloc(5 * sizeof(int));
	int* vector_y_XOR = (int*)malloc(5 * sizeof(int));
	
	int* vector_lambda = (int*)malloc(5 * sizeof(int));
	int* vector_lamda_squared = (int*)malloc(5 * sizeof(int));
	int* vector_a = (int*)malloc(5 * sizeof(int));


	InitializeWithZero(vector_Xp, 5);
	InitializeWithZero(vector_Xq, 5);
	InitializeWithZero(vector_Xr, 5);
	
	InitializeWithZero(vector_Yp, 5);
	InitializeWithZero(vector_Yq, 5);
	InitializeWithZero(vector_Yr, 5);

	InitializeWithZero(vector_x_XOR, 5);
	InitializeWithZero(vector_y_XOR, 5);

	vector_Xp = Generation(15, 4, X_p);
	vector_Xq = Generation(15, 4, X_q);
	vector_Yp = Generation(15, 4, Y_p);
	vector_Yq = Generation(15, 4, Y_q);

	vector_x_XOR = XOR_II(vector_Xp, vector_Xq, 5);
	vector_y_XOR = XOR_II(vector_Yp, vector_Yq, 5);

	power_x = Inverse(vector_x_XOR);
	power_y = Inverse(vector_y_XOR);

	lambda = power_y - power_x;
	int lambda_squared = 2 * lambda;

	vector_lambda = Generation(15, 4, lambda);
	vector_lamda_squared = Generation(15, 4, lambda_squared);
	vector_a = Generation(15, 4, a);

	vector_Xr = XOR_Addition(vector_lamda_squared, vector_lambda, vector_Xp, vector_Xq, vector_a);

	DisplayVector(vector_Xr, "Xr", 5);
}

int* XOR_Addition(int* lamda_squared, int* lambda, int* X_p, int* X_q, int* a)
{
	int* result = (int*)malloc(5 * sizeof(int));
	int* xor_1 = (int*)malloc(5 * sizeof(int));
	int* xor_2 = (int*)malloc(5 * sizeof(int));
	int* xor_3 = (int*)malloc(5 * sizeof(int));

	for (int i = 0; i < 5; i++)
	{
		xor_1[i] = (lamda_squared[i] + lambda[i]) % 2;
		xor_2[i] = (X_p[i] + X_q[i]) % 2;
	}

	for (int i = 0; i < 5; i++)
	{
		xor_3[i] = (xor_2[i] + a[i]) % 2;
	}

	result = XOR_II(xor_1, xor_3, 5);

	return result;
}