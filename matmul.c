#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define WAITING_FOR_NUMBER 0
#define IN_NUMBER 1
#define IN_SPACE 2

int state;
int i = 0;
int j = 0;
int k = 0;
int a = 0;
int **c, **d, **p;
int check_matrix(char b, FILE *fp);
int check_matrix_first_row(char b, FILE *fp);
int checkchar(char b);
int check_columns(int nc, int nc1);
int check_rest_of_matrix(char b, FILE *fp, int nc1);

struct value
{
	int rows;
	int columns;
}matrix[2];

int check_matrix(char b, FILE *fp)
{
	int nc1 = 0;
	
	nc1 = check_matrix_first_row(b , fp);
	check_rest_of_matrix(b, fp, nc1);
	
	printf("the number of rows in the matrix %d is %d\n", i + 1 , matrix[i].rows);
	printf("the number of columns in the matrix %d is %d\n", i + 1 , matrix[i].columns);
	i++;
	return 0;
}

int check_matrix_first_row(char b, FILE *fp)
{
	int nc = 1;
	state = WAITING_FOR_NUMBER;
	while ((b = fgetc(fp)) != '\n'){
		if (state == WAITING_FOR_NUMBER && b == ' '){
			continue;
		}
		else if (state == WAITING_FOR_NUMBER && b != ' ' && b != '\t' && b != '\n'){
			state = IN_NUMBER;
			checkchar(b);
		}
		else if (state == IN_NUMBER && b != ' ' && b != '\t' && b != '\n'){
			checkchar(b);
			continue;
		}
		else if (state == IN_NUMBER && b == ' '){
			state = IN_SPACE;
		}
		else if (state == IN_SPACE && b == ' '){
			continue;
		}
		else if (state == IN_SPACE && b != ' ' && b != '\t' && b != '\n'){
			state = IN_NUMBER;
			checkchar(b);
			nc++;
		}
	}

	if (b == '\n'){
		state = WAITING_FOR_NUMBER;
		matrix[i].rows++;
	}
	return nc;
}

int checkchar(char b)
{
	if (b < '0' || b > '9'){
		printf("Matrix contains something other than a number\n");
		exit(EXIT_FAILURE);
	}
	return 1;
}

int check_columns(int nc, int nc1)
{
	if (nc != nc1){
		printf("Error\n");
		printf("Check the matrix to see if there are equal number of columns in all the rows\n");
		exit(EXIT_FAILURE);
	}
	return 1;
}

int check_rest_of_matrix(char b, FILE *fp, int nc1)
{
	int nc = 1;
	int line = 2;
	state = WAITING_FOR_NUMBER;
	while ((b = fgetc(fp)) != EOF){
		if (b != '\n'){
                	if (state == WAITING_FOR_NUMBER && b == ' '){
                        	continue;
                	}   
                	else if (state == WAITING_FOR_NUMBER && b != ' ' && b != '\t' && b != '\n'){
                        	state = IN_NUMBER;
                        	checkchar(b);
                	}   
                	else if (state == IN_NUMBER && b != ' ' && b != '\t' && b != '\n'){
				checkchar(b);
                        	continue;
                	}	   
                	else if (state == IN_NUMBER && b == ' '){
                        	state = IN_SPACE;
                	}   
                	else if (state == IN_SPACE && b == ' '){
                        	continue;
                	}
                	else if (state == IN_SPACE && b != ' ' && b != '\t' && b != '\n'){
                        	state = IN_NUMBER;
				checkchar(b);
				nc++;
                	}
        	}		
		else if (b == '\n'){
			check_columns(nc, nc1);
			nc = 1;
			state = WAITING_FOR_NUMBER;
			matrix[i].rows++;
		}
	}
	matrix[i].columns = nc1;
	return 0;
}

int check_multiply()
{
	if (matrix[0].columns != matrix[1].rows){
		printf("The number of columns in the first matrix is %d\n", matrix[0].columns);
		printf("The number of rows in the second matrix is %d\n", matrix[1].rows);
		printf("Matrices cannot be multiplied as no. of columns in the first matrix is not equal to the number of reows in the second matrix\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int read_matrix()
{
	FILE *fp1;
	if((fp1 = fopen("first-matrix.txt", "r")) == NULL){
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	printf("The contents of first matrix are :\n");
        for (k = 0; k < matrix[0].rows; k++){
                printf("\n");
                for (j = 0; j < matrix[0].columns; j++)
                {
                        while (fscanf(fp1, "%d", &a) != EOF){
				c[k][j] = a;
                                printf("%d\t", c[k][j]);
				a = 0;
                                break;
                        }
                }
        }
        printf("\n");
        fclose(fp1);

        if((fp1 = fopen("second-matrix.txt", "r")) == NULL){
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
        printf("The contents of second matrix are :\n");
        for(k = 0; k < matrix[1].rows; k++){
                printf("\n");
                for(j = 0; j < matrix[1].columns; j++){
                        while(fscanf(fp1, "%d", &a) != EOF){
				d[k][j] = a;
                                printf("%d\t", d[k][j]);
				a = 0;
                                break;
                         }
		}
	}
	printf("\n");
	fclose(fp1);
	return 0;
}

int multiply()
{
	for(i = 0; i < matrix[0].rows; i++){
                for(j = 0; j < matrix[1].columns; j++){
                        p[i][j] = 0;
                        for(k = 0; k < matrix[1].columns; k++)
                        {
                                p[i][j] = p[i][j] + (c[i][k] * d[k][j]);
                        }
                }
        }
	return 0;
}

int display_product()
{
	printf("The product is:\n");
	for(i = 0; i < matrix[0].rows; i++){
                printf("\n");
                for(j = 0; j < matrix[1].columns; j++)
                {
                        printf("%d\t", p[i][j]);
                }
        }
        printf("\n");
	return 0;
}

int create_array()
{
	c = malloc(matrix[0].rows * sizeof(int *));
	for (i = 0; i < matrix[0].rows; i++){
		c[i] = malloc(matrix[0].columns * sizeof(int **));
	}
	d = malloc(matrix[1].rows * sizeof(int *));
	for (i = 0; i < matrix[1].rows; i++){
		d[i] = malloc(matrix[1].columns * sizeof(int **));
	}			
	p = malloc(matrix[0].rows * sizeof(int *));
	for (i = 0; i < matrix[0].rows; i++){
		p[i] = malloc(matrix[1].columns * sizeof(int **));
	}
	return 0;	
	}	

int main(void)
{	
	FILE *fp;
	int b = '0';	

	if ((fp = fopen("first-matrix.txt","r")) == NULL){
                  printf("Error\n");
                  exit(EXIT_FAILURE);
        }
	check_matrix(b, fp);
	fclose(fp);
	if ((fp = fopen("second-matrix.txt","r")) == NULL){
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	check_matrix(b, fp);
	fclose(fp);
	check_multiply();
	create_array();
	read_matrix();
	multiply();
	display_product();
	return 0;
}
