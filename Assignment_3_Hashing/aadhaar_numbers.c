/*****************************************
 * Assignment 3
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code is a random generator
 * The code generates a .txt file named "inputs.txt"
 * The code generates 1000 unique numbers randomly in the range 1-10000000
 * And also generates 100 more unique numbers in that range and saves them to
 * "not_in1000.txt" which is used in the 2nd question
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Arrays to store the generated numbers
    long long int arr[1100] = {0};
    int *temp = (int *)malloc(10000000 * sizeof(int));

    // Open the files for writing
    FILE *file1 = fopen("inputs.txt", "w");
    if (file1 == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    FILE *file2 = fopen("not_in1000.txt", "w");
    if (file2 == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    // Loop to generate random numbers uniquely and store them in the array
    for (int j = 0; j < 1100; j++)
    {
        long long int num = rand() % 10000000;
        while (temp[num] == 1)
        {
            num = rand() % 10000000;
        }
        temp[num] = 1;
        arr[j] = num + 1;
    }

    // Writing the generated numbers to both the files
    for (int j = 0; j < 1000; j++)
    {
        fprintf(file1, "%lld ", arr[j]);
    }
    fclose(file1);
    for (int j = 1000; j < 1100; j++)
    {
        fprintf(file2, "%lld ", arr[j]);
    }
    fclose(file2);

    free(temp);
}