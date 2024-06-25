/*****************************************
 * Assignment 2
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code is a random generator
 * The code generates a .txt file named "delete.txt"
 * There are 100 lines in the .txt file
 * Each line of the txt file contains 100 numbers between 1-1000 in a randomly generated order
 * 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
    
int main(){
    // 2D array to store the generated numbers
    int arr[100][100] = {0};
    int temp[1000] = {0};
    FILE *file;

    // Open the file for writing
    file = fopen("delete.txt", "w");

    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    // Loop to generate random numbers uniquely and store them in the array
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int num = rand() % 1000;
            while (temp[num] == 1)
            {
                num = rand() % 1000;
            }
            temp[num] = 1;
            arr[i][j] = num+1;
        }
        for (int k = 0; k < 100; k++)
        {
            temp[arr[i][k]-1] = 0;
        }
    }

    // Writing the generated numbers to the file
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            fprintf(file, "%d ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    
}