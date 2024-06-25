/*****************************************
 * Assignment 2
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code implements a Binary Search Tree
 * This code expects 2 .txt files in the same folder as the code
 * "inputs.txt" and "delete.txt" each containg the required data to add or delete from the tree
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
// Global variable to keep track of work done
long int workDone = 0;

// Structure to represent a node in the Binary Search Tree (BST)
struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Function to create a new node
struct node *createNode(int key)
{
    struct node *root;
    root = (struct node *)malloc(sizeof(struct node));
    root->data = key;
    root->height = 1;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
}

// Function to find the maximum of two integers
int max(int left, int right)
{
    workDone++;
    if (left > right)
        return left;
    return right;
}

// Function to update the height of a node based on its children's heights
int updateHeight(struct node *root)
{
    workDone++;
    if (root == NULL)
        return 0;
    int temp1 = updateHeight(root->left);
    int temp2 = updateHeight(root->right);
    if (root->left != NULL)
        root->left->height = temp1;
    if (root->right != NULL)
        root->right->height = temp2;
    return max(temp1, temp2) + 1;
}

// Function to insert a new node with the given key into the BST
void insert(struct node *root, int key)
{
    workDone += 3;
    // Initialize a pointer to keep track of the previous node while traversing
    struct node *prev = NULL;
    while (1)
    {
        if (root == NULL)
        {
            workDone += 2;
            // If we've found an empty spot, create a new node and insert it
            if (prev->data > key)
            {
                prev->left = createNode(key);
                prev->left->parent = prev;
            }
            else
            {
                prev->right = createNode(key);
                prev->right->parent = prev;
            }
            break;
        }
        // If the element is already in the BST, print a message
        if (root->data == key)
        {
            printf("Element already in BST\n");
            break;
        }
        // Update the previous node
        prev = root;
        if (root->data > key)
            root = root->left;
        else if (root->data < key)
            root = root->right;
    }
}

// Function to delete a node with the given key from the BST
struct node *deleteNode(struct node *n, int key)
{
    // Initialize a pointer to traverse the tree
    struct node *root = n;
    while (root != NULL && root->data != key)
    {
        workDone++;
        if (root->data > key)
            root = root->left;
        else
            root = root->right;
    }
    // If the element is not found, print an error message
    if (root == NULL)
    {
        printf("Error, the element is not in the BST\n");
    }
    else if (root->left == NULL)
    {
        workDone += 4;
        // If the node to delete is the root, update the root
        if (root->parent == NULL)
            n = root->right;
        if (root->parent->left == root)
            root->parent->left = root->right;
        else
            root->parent->right = root->right;
        if (root->right != NULL)
            root->right->parent = root->parent;
    }
    else if (root->right == NULL)
    {
        workDone += 3;
        // If the node to delete is the root, update the root
        if (root->parent == NULL)
            n = root->left;
        if (root->parent->left == root)
            root->parent->left = root->left;
        else
            root->parent->right = root->left;
        root->left->parent = root->parent;
    }
    else
    {
        workDone += 2;
        // Find the in-order successor
        struct node *temp = root->right;
        while (temp->left != NULL)
        {
            workDone++;
            temp = temp->left;
        }
        if (temp != root->right)
        {
            workDone += 3;
            temp->parent->left = temp->right;
            if (temp->right != NULL)
                temp->right->parent = temp->parent;
            temp->right = root->right;
            temp->right->parent = temp;
        }
        if (root->parent != NULL)
        {
            workDone += 3;
            if (root->parent->left == root)
                root->parent->left = temp;
            else
                root->parent->right = temp;
            temp->parent = root->parent;
        }
        else
        {
            temp->parent = NULL;
        }
        temp->left = root->left;
        temp->left->parent = temp;
        // Update the parent pointer through out the code appropriately
    }
    free(root);
    return n;
}

// Function to perform an in-order traversal of the BST and print the elements
void inOrder(struct node *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("[%d] ", root->data);
    inOrder(root->right);
}

// Prints the data of each tree
void treeData(int heights[], int heights2[])
{
    for (int i = 0; i < 100; i++)
    {
        printf("Tree %d: height before deletion %d height after deletion %d\n", i + 1, heights[i], heights2[i]);
    }
}

int main()
{
    // Initialize an array to store the input data and two arrays to store heights
    int arr[100][1000] = {};
    int heights[100] = {};
    int heights2[100] = {};
    struct node *bst[100];

    // Open the "inputs.txt" file to read input data
    FILE *file = fopen("inputs.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        return 0;
    }

    int rows = 0;
    int cols = 0;
    int num;

    // Read data from the "inputs.txt" file and store it in the array
    while (fscanf(file, "%d", &num) == 1)
    {
        arr[rows][cols] = num;
        cols++;
        if (cols == 1000)
        {
            rows++;
            cols = 0;
        }
    }

    fclose(file);

    // Build BSTs using the input data and calculate their heights
    for (int i = 0; i < 100; i++)
    {
        bst[i] = createNode(arr[i][0]);
        for (int j = 1; j < 1000; j++)
        {
            insert(bst[i], arr[i][j]);
        }
        bst[i]->height = updateHeight(bst[i]);
        heights[i] = bst[i]->height;
    }

    // Initialize an array to store nodes to delete
    int deleteNodes[100][100] = {};
    // Open the "delete.txt" file to read nodes to delete
    file = fopen("delete.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file");
        return 0;
    }

    rows = 0;
    cols = 0;

    // Read data from the "delete.txt" file and store it in the array
    while (fscanf(file, "%d", &num) == 1)
    {
        deleteNodes[rows][cols] = num;
        cols++;
        if (cols == 100)
        {
            rows++;
            cols = 0;
        }
    }
    fclose(file);

    // Delete nodes from the BSTs based on the data in the "delete.txt" file
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            bst[i] = deleteNode(bst[i], arr[i][deleteNodes[i][j]]);
        }
        bst[i]->height = updateHeight(bst[i]);
        heights2[i] = bst[i]->height;
    }
    // Print the total work done and a success message
    treeData(heights, heights2);
    printf("%ld is the total operations for 100 trees\n", workDone);
    printf("Code ran successfully\n");
}