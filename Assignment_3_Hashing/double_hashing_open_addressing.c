/*****************************************
 * Assignment 3
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code implements open addressing with double hashing
 * This code expects 2 .txt files in the same folder as the code
 * "inputs.txt" containg the required data to add to the hash table
 * "not_in1000.txt" containing 100 keys for unsuccessful searches
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>

// SLOTS defines the size of the hash table
// Uncomment approriate line for other case
#define SLOTS 2013
// #define SLOTS 1021

long long int table[SLOTS] = {0};
int probes = 0;

// First hash function
int hash1(long long int num)
{
    return num % SLOTS;
}

// Second hash fucnction
int hash2(long long int num)
{
    return 1019 - num % 1019;
}

// Function to implement the double hashing of a key accordingly
int hash(long long int num, int i)
{
    return (hash1(num) + i * hash2(num)) % SLOTS;
}

// Function to insert a key into the hash table
void table_insert(int long long num)
{
    int i = 0;
    for (i = 0; i < SLOTS; i++)
    {
        int temp = hash(num, i);
        if (table[temp] == 0 || table[temp] == -1)
        {
            table[temp] = num;
            break;
        }
    }
}

// Function to delete a key from the hash table
void table_delete(long long int num)
{
    int temp;
    for (int i = 0; i < SLOTS; i++)
    {
        temp = hash(num, i);
        if (table[temp] == num)
        {
            table[temp] = -1;
            break;
        }
    }
}

// Function to search for a key in the hash table and return its address
long long int *table_search(long long int num)
{
    for (int i = 0; i < SLOTS; i++)
    {
        probes += 1;
        int temp = hash(num, i);
        if (table[temp] == num)
        {
            // printf("\nThe search is successful");
            probes -= 1;
            return &table[temp];
        }
        else if (table[temp] == 0)
        {
            // printf("\nThe search is unsuccessful");
            probes -= 1;
            return NULL;
        }
    }
    return 0;
}

// Function to generate 200 numbers for successful searches
void generate_random(long long int arr[], long long int arr2[], long long int arr3[])
{
    int temp;
    int check[1000] = {0};
    for (int i = 0; i < 200; i++)
    {
        temp = rand() % 1000;
        while (check[temp] == 1)
        {
            temp = rand() % 1000;
        }
        check[temp] = 1;
        if (i < 100)
            arr2[i] = arr[temp];
        else
            arr3[i - 100] = arr[temp];
    }
}

int main()
{
    printf("%d is the size of hash table", SLOTS);
    // Open the "inputs.txt" file to read keys to insert to hash table
    FILE *file = fopen("inputs.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    long long int aadhaarNum[1000] = {0};
    int cols = 0;
    long long int num;

    // Read data from the "inputs.txt" file and store it in the array
    while (fscanf(file, "%lld", &num) == 1)
    {
        aadhaarNum[cols] = num;
        cols++;
    }
    fclose(file);

    // The code inserts the keys to the hash table in the corresponding slot
    for (int i = 0; i < 1000; i++)
    {
        table_insert(aadhaarNum[i]);
    }

    long long int in1000_1[100] = {0};
    long long int in1000_2[100] = {0};
    generate_random(aadhaarNum, in1000_1, in1000_2);
    long long int *temp2;

    // Search for keys from the in1000_1 array
    for (int i = 0; i < 100; i++)
    {
        temp2 = table_search(in1000_1[i]);
    }
    printf("\nNumber of probes in the first case: %d ", probes);

    probes = 0;

    // Delet keys in the in1000_1 array
    for (int i = 0; i < 100; i++)
    {
        table_delete(in1000_1[i]);
    }

    // Search for keys from the in1000_2 array
    for (int i = 0; i < 100; i++)
    {
        temp2 = table_search(in1000_2[i]);
    }
    printf("\nNumber of probes in the second case: %d ", probes);
    probes = 0;

    // Open the "not_in1000.txt" file to read keys to search in hash table
    file = fopen("not_in1000.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        return 1;
    }

    long long int not_in1000[100] = {0};
    cols = 0;

    // Read data from the "not_in1000.txt" file and store it in the array
    while (fscanf(file, "%lld", &num) == 1)
    {
        not_in1000[cols] = num;
        cols++;
    }
    fclose(file);

    // Search for keys from the not_in1000 array
    for (int i = 0; i < 100; i++)
    {
        temp2 = table_search(not_in1000[i]);
    }
    printf("\nNumber of probes in the third case: %d ", probes);
    probes = 0;
}