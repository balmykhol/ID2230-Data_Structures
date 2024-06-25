/*****************************************
 * Assignment 2
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code implements AVL Tree
 * This code expects 2 .txt files in the same folder as the code
 * "inputs.txt" and "delete.txt" each containg the required data to add or delete from the tree
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
// Global variable to keep track of work done
long int workDone = 0;

// Structure to represent a node in an AVL tree
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
    struct node *root = (struct node *)malloc(sizeof(struct node));
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

// Function to get the height of a node
int Height(struct node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

// Right rotation of a node
struct node *rotateRight(struct node *root)
{
    workDone += 2;
    if (root != NULL)
    {
        struct node *temp = root->left;
        struct node *temp2 = temp->right;
        temp->right = root;
        root->left = temp2;
        temp->parent = root->parent;
        root->parent = temp;
        if (temp2 != NULL)
            temp2->parent = root;
        root->height = max(Height(root->left), Height(root->right)) + 1;
        temp->height = max(Height(temp->left), Height(temp->right)) + 1;
        return temp;
    }
    return NULL;
}

// Left rotation of a node
struct node *rotateLeft(struct node *root)
{
    workDone += 2;
    if (root != NULL)
    {
        struct node *temp = root->right;
        struct node *temp2 = temp->left;
        temp->left = root;
        root->right = temp2;
        temp->parent = root->parent;
        root->parent = temp;
        if (temp2 != NULL)
            temp2->parent = root;
        root->height = max(Height(root->left), Height(root->right)) + 1;
        temp->height = max(Height(temp->left), Height(temp->right)) + 1;
        return temp;
    }
    return NULL;
}

// Left-Right rotation
struct node *leftRight(struct node *root)
{
    root->left = rotateLeft(root->left);
    return rotateRight(root);
}

// Right-Left rotation
struct node *rightLeft(struct node *root)
{
    root->right = rotateRight(root->right);
    return rotateLeft(root);
}

// Calculate the balance factor of a node
int Balance(struct node *node)
{
    if (node == NULL)
        return 0;
    return Height(node->left) - Height(node->right);
}

// Function to insert a node in the AVL tree
struct node *insert(struct node *root, int key, struct node *parent)
{
    
    if (root == NULL)
    {
        struct node *temp = createNode(key);
        temp->parent = parent;
        return temp;
    }
    // Recursively insert the node in the appropriate sub-tree
    if (key < root->data)
        root->left = insert(root->left, key, root);
    else if (key > root->data)
        root->right = insert(root->right, key, root);
    else
        return root;

    // Update the height of the current node
    root->height = 1 + max(Height(root->left), Height(root->right));

    // Check the balance factor of this node and perform necessary rotations if needed
    int balance = Balance(root);

    if (balance > 1 && key < root->left->data)
    {
        workDone++;
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->data)
    {
        workDone++;
        return rotateLeft(root);
    }
    if (balance > 1 && key > root->left->data)
    {
        workDone++;
        return leftRight(root);
    }
    if (balance < -1 && key < root->right->data)
    {
        workDone++;
        return rightLeft(root);
    }
    // Return the updated node.
    return root;
}

// Function to delete a node from the AVL tree
struct node *deleteNode(struct node *root, int key)
{       workDone++;

    if (root == NULL)
        return root;

    // Recursively delete the node in the appropriate sub-tree
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        workDone += 1;
        if (root->left == NULL)
        {
            if (root->right != NULL)
                root->right->parent = root->parent;
            root = root->right;
        }
        else if (root->right == NULL)
        {
            root->left->parent = root->parent;
            root = root->left;
        }
        else
        {
            // Find the in-order successor of the current node
            struct node *temp = root->right;
            while (temp->left != NULL)
            {
                workDone++;
                temp = temp->left;
            }
            workDone++;
            // Replace the current node's data with the in-order successor's data
            root->data = temp->data;
            // Delete the in-order successor node
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(Height(root->left), Height(root->right));

    // Check the balance factor of this node and perform necessary rotations if needed
    int balance = Balance(root);
    if (balance > 1 && Balance(root->left) >= 0)
    {
        workDone++;
        return rotateRight(root);
    }
    if (balance > 1 && Balance(root->left) < 0)
    {
        workDone++;
        return leftRight(root);
    }
    if (balance < -1 && Balance(root->right) <= 0)
    {
        workDone++;
        return rotateLeft(root);
    }
    if (balance < -1 && Balance(root->right) > 0)
    {
        workDone++;
        return rightLeft(root);
    }
    return root;
}

// In-order traversal of the tree
void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("[%d] ", root->data);
        inOrder(root->right);
    }
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

    // Build AVL trees using the input data and calculate their heights
    for (int i = 0; i < 100; i++)
    {
        bst[i] = createNode(arr[i][0]);
        for (int j = 1; j < 1000; j++)
        {
            bst[i] = insert(bst[i], arr[i][j], NULL);
        }
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

    // Delete nodes from the AVL trees based on the data in the "delete.txt" file
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            bst[i] = deleteNode(bst[i], arr[i][deleteNodes[i][j]]);
        }
        heights2[i] = bst[i]->height;
    }
    // Print the total work done and a success message
    treeData(heights, heights2);
    printf("%ld is the total operations for 100 trees\n", workDone);
    printf("Code ran successfully\n");
}