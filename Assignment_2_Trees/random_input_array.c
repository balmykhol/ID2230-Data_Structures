/*****************************************
 * Assignment 2
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code is a random generator
 * The code generates a .txt file named "inputs.txt"
 * There are 100 lines in the .txt file
 * Each line of the txt file contains 1-1000 numbers in a randomly generated order
 * 
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>

int main(){
    // 2D array to store the generated numbers
    int arr[100][1000] = {0};
    FILE *file;

    // Opening the file for writing
    file = fopen("array.txt", "w");

    if (file == NULL) {
        printf("Error opening file");
    }

    // Loop to generate random numbers uniquely and store them in the array
    for(int i=1;i<=1000;i++){
        for(int j=0;j<100;j++){
            int num = rand()%1000;
            while(arr[j][num] != 0){
                num = rand()%1000;
            }
            arr[j][num] = i;
        }
    }

    // Writing the generated numbers to the file
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 1000; j++) {
            fprintf(file, "%d ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);

}