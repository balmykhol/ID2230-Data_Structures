#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAXROWS 1025
#define MAXCOLS 100

int tointeger(char arr[])
{
    int temp = 0;
    int i = 0;
    while (arr[i] != '\0')
    {
        temp += arr[i] - 48;
        temp *= 10;
        i++;
    }
    return temp / 10;
}

int bst;
// int q = 0;
int check_2(int start, int end, int arr[])
{
    int check = check_2(start + 1, end / 2, arr);
    if (check == 0)
    {
        return 0;
    }
    check = check_2(end / 2 + 2, end, arr);
    if (check == 0)
    {
        return 0;
    }
    if (start >= end)
    {
        return 1;
    }
    else
    {
        for (int i = start; i <= end / 2; i++)
        {
            if (arr[i] >= arr[start - 1])
            {
                return 0;
            }
        }
        for (int q = end / 2 + 1; q <= end; q++)
        {
            if (arr[q] <= arr[start - 1])
            {
                return 0;
            }
        }
        return 1;
    }
}
int main()
{
    char car[MAXROWS * MAXCOLS * 2];
    fgets(car, MAXROWS * MAXCOLS * 2, stdin);
    int arr[MAXROWS];
    char car2[MAXCOLS][MAXROWS];
    int k, l = 0;
    for (int i = 1; car[i] != '\0'; i++)
    {
        if (car[i] == ' ' || car[i] == ']')
        {
            arr[l] = tointeger(car2[l]);
            k = 0;
            l++;
        }
        else
        {
            car2[l][k] = car[i];
            k++;
        }
    }
    // for (int i = 0; i < l; i++)
    // {
    //     printf("%d ", arr[i]);
    // }

    // int arr[10] = {8, 9, 7, 5, 6, 10, 4};
    int rows = l;
    int temp = rows + 1;
    while (temp != 0)
    {
        if (temp % 2 == 1 && temp != 1)
        {
            printf("Error, not a complete binary tree");
            break;
        }
        temp /= 2;
    }

    int check2 = check_2(1, rows - 1, arr);
    printf("yes %d", check2);
}