/*****************************************
 * Assignment 3
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code implements a simple hash table with chaining
 * The chaining is implemented as an AVL tree
 * The AVL implementation is borrowed from the last assignemnt submission
 * This code expects 1 .txt file in the same folder as the code
 * "inputs.txt" containg the required data to add to the hash table
 *
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// SLOTS defines the size of the hash table
#define SLOTS 100
struct node *table[SLOTS];

// Structure to represent a node in an AVL tree
struct node
{
    long long int data;
    int height;
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Function to create a new node
struct node *createNode(long long int key)
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
struct node *insert(struct node *root, long long int key, struct node *parent)
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
    {
        printf("The element already exists in the hash table.\n");
        return root;
    }
    // Update the height of the current node
    root->height = 1 + max(Height(root->left), Height(root->right));

    // Check the balance factor of this node and perform necessary rotations if needed
    int balance = Balance(root);

    if (balance > 1 && key < root->left->data)
    {
        return rotateRight(root);
    }
    if (balance < -1 && key > root->right->data)
    {
        return rotateLeft(root);
    }
    if (balance > 1 && key > root->left->data)
    {
        return leftRight(root);
    }
    if (balance < -1 && key < root->right->data)
    {
        return rightLeft(root);
    }
    // Return the updated node.
    return root;
}

// Function to delete a node from the AVL tree
struct node *deleteNode(struct node *root, long long int key)
{

    if (root == NULL)
    {
        printf("The element is not part of the hash table.\n");
        return root;
    }
    // Recursively delete the node in the appropriate sub-tree
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
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
                temp = temp->left;
            }
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
        return rotateRight(root);
    }
    if (balance > 1 && Balance(root->left) < 0)
    {
        return leftRight(root);
    }
    if (balance < -1 && Balance(root->right) <= 0)
    {
        return rotateLeft(root);
    }
    if (balance < -1 && Balance(root->right) > 0)
    {
        return rightLeft(root);
    }
    return root;
}

// Function to search for a node in an AVL tree
struct node *searchNode(struct node *root, long long int num)
{
    while (root != NULL)
    {
        if (root->data == num)
            return root;
        else if (root->data > num)
            root = root->left;
        else
            root = root->right;
    }
    printf("The element is not part of the hash table.\n");
    return root;
}

// Function to implement the hash of a key
// I've implemented random hashing from the CLRS textbook
int hash(long long int a, long long int b, long long int p, long long int num)
{
    return (((num * a) + b) % p) % SLOTS;
}

// Function to insert a number into the hash table
void table_insert(long long int a, long long int b, long long int p, long long int num)
{
    int key = hash(a, b, p, num);
    table[key] = insert(table[key], num, NULL);
}

// Function to delete a number from the hash table
void table_delete(long long int a, long long int b, long long int p, long long int num)
{
    int key = hash(a, b, p, num);
    table[key] = deleteNode(table[key], num);
}

// Function to search for a number in the hash table and return its address
struct node *table_search(long long int a, long long int b, long long int p, long long int num)
{
    int key = hash(a, b, p, num);
    return searchNode(table[key], num);
}

// In-order traversal of the tree
void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%lld ", root->data);
        inOrder(root->right);
    }
}

int main()
{
    srand(time(NULL));
    // Generating the parameters for the hash function
    long long int p = 10000931;
    long long int a = rand() % (p - 1) + 1;
    long long int b = rand() % (p - 1) + 1;

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
        table_insert(a, b, p, aadhaarNum[i]);
    }
    for (int i = 0; i < 100; i++)
    {
        table_search(a, b, p, aadhaarNum[i]);
    }
    for (int i = 0; i < 100; i++)
    {
        table_delete(a, b, p, aadhaarNum[i]);
    }
}