/*****************************************
 * Assignment 4
 * Question 1
 * Name:    Chakka Surya Saketh
 * Roll no: AI22BTECH11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code performs a BFS on a graph representation of a maze .txt file
 * This code borrows deque implementation from 1st assignemnt 
 * It utilizes adjacency matrix to traverse the maze, marking the shortest path with 'o' upon successful completion.
 * The code prints the solved maze marking the shortest path with 'o' and all other extra vertices traversed with '.'
 *
 ***********************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Adjust the maxrows and maxcols according to the maze size in .txt file
#define MAXROWS 60
#define MAXCOLS 60
#define MAXSIZE (MAXCOLS*MAXROWS + 50)

int rows = 0;
int cols = 0;

// Structure to represent a node in the maze
struct node
{
    int x;
    int y;
    // Single index coordinate system value
    int num;
    char data;
    struct node *parent;
    int visited;
};

/** Function to create a new node in the maze
 *
 * @param x x coordinate of the node
 * @param y y coordinate of the node
 * @param num coordinate of the node in single index system
 * @return pointer containing the node with data
 */
struct node *create_node(int x, int y, int num, char data)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->x = x;
    newNode->y = y;
    newNode->num = num;
    newNode->data = data;
    newNode->visited = 0;
    newNode->parent = NULL;
    return newNode;
}

// Importing the deque implementation from 1st question 1st assignemnt 
// Define the deque structure
struct deque
{
    struct node *arr[MAXSIZE];
    int head, tail;
};

/** Initialises the struct deque
 *
 * @param q the pointer of a structure deque
 */
void initDeque(struct deque *q)
{
    q->head = -1;
    q->tail = -1;
}

/** Checks whether the the deque passed is empty or not
 *
 * @param q the pointer of a structure deque
 * @return true if the deque is empty, false otherwise
 */
bool isEmpty(struct deque *q)
{
    return (q->head == -1 && q->tail == -1);
}

/** Adds a specified integer at the begining of the deque
 *
 * @param q the pointer of a structure deque
 * @param x the element to be added in the deque
 */
void add_first(struct deque *q, struct node *no)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == MAXSIZE - 1))
    {
        printf("DEQUE OVERFLOW. Unable to add coordinate (%d, %d)\n", no->x, no->y);
    }
    else if (isEmpty(q))
    {
        q->head = q->tail = MAXSIZE - 1;
        q->arr[q->head] = no;
    }
    else
    {
        if (q->head == 0)
            q->head = MAXSIZE;
        q->head -= 1;
        q->arr[q->head] = no;
    }
}

/** Removes the element at the begining of the deque
 *
 * @param q the pointer of a structure deque
 * @return the number removed from the deque or -256 if the deque is empty
 */
struct node *remove_first(struct deque *q)
{
    struct node *temp = create_node(0, 0, 0, 'Y');
    if (isEmpty(q))
    {
        printf("DEQUE UNDERFLOW\n");
    }
    else if (q->head == q->tail)
    {
        temp = q->arr[q->head];
        q->head = q->tail = -1;
    }
    else
    {
        temp = q->arr[q->head];
        if (q->head == MAXSIZE - 1)
            q->head = -1;
        q->head += 1;
    }
    return temp;
}

/** Adds a specified integer at the ending of the deque
 *
 * @param q the pointer of a structure deque
 * @param x the element to be added in the deque
 */
void add_last(struct deque *q, struct node *no)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == MAXSIZE - 1))
    {
        printf("DEQUE OVERFLOW. Unable to add coordinates (%d, %d)\n", no->x, no->y);
    }
    else if (isEmpty(q))
    {
        q->tail = q->head = 0;
        q->arr[q->tail] = no;
    }
    else
    {
        if (q->tail == MAXSIZE - 1)
            q->tail = -1;
        q->tail += 1;
        q->arr[q->tail] = no;
    }
}

/** Removes the element at the end of the deque
 *
 * @param q the pointer of a structure deque
 * @return the number removed from the deque or -256 if the deque is empty
 */
struct node *remove_last(struct deque *q)
{
    struct node *temp = create_node(0, 0, 0, 'Y');
    if (isEmpty(q))
    {
        printf("DEQUE UNDERFLOW\n");
    }
    else if (q->head == q->tail)
    {
        temp = q->arr[q->tail];
        q->head = q->tail = -1;
    }
    else
    {
        temp = q->arr[q->tail];
        if (q->tail == 0)
            q->tail = MAXSIZE;
        q->tail -= 1;
    }
    return temp;
}

/** Changes the x-coordinate and y-coordinate to single index coordinate system
 *
 * @param x The x-cooordinate in the maze
 * @param y The y-cooordinate in the maze
 * @return integer specifying the location in the maze in single index coordinate system
 */
int getNum(int x, int y)
{
    return x + y * rows;
}

/** Gets the y coordinate of the location in the maze
 *
 * @param number the value of the location of maze in single index coordinate system
 * @return y coordinate
 */
int getY(int number)
{
    return number / rows;
}

/** Gets the x coordinate of the location in the maze
 *
 * @param number the value of the location of maze in single index coordinate system
 * @return x coordinate
 */
int getX(int number)
{
    return (number - (rows * getY(number)));
}

int main()
{
    // Initialize the deque
    struct deque *deq = malloc(sizeof(struct deque));
    initDeque(deq);

    // Prompt user for the maze file name
    printf("Maze file name? ");
    char str[MAXSIZE];
    fgets(str, MAXSIZE, stdin);

    str[strlen(str)-1] = '\0';
    FILE *file = fopen(str, "r");

    // Initialize variables to store maze data and starting positions
    char maze[MAXROWS][MAXCOLS];

    // Read the maze file character by character and add the data to the maze array
    char ch;
    int startingI;
    int startingJ;
    while ((ch = fgetc(file)) != EOF && rows < MAXROWS)
    {
        if (ch == '\n')
        {
            cols = 0;
            rows++;
        }
        else if (cols < MAXCOLS)
        {
            maze[rows][cols] = ch;
            if (ch == 'S')
            {
                startingI = rows;
                startingJ = cols;
            }

            cols++;
        }
    }

    rows = rows + 1;

    // Convert the starting coordinates to a single index
    int starting = getNum(startingI, startingJ);

    fclose(file);

    // Create nodes for each position in the maze containing a pointer to the node
    struct node *vertices[MAXROWS * MAXCOLS];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int index = getNum(i, j);
            vertices[index] = create_node(i, j, index, maze[i][j]);
        }
    }

    int **adjMatrix;
    int temps = MAXROWS * MAXCOLS;

    // I used an adjacency matrix for the maze to graph representation
    // Dynamically allocate memory for rows
    adjMatrix = (int **)malloc(temps * sizeof(int *));

    // Dynamically allocate memory for cols
    for (int i = 0; i < temps; i++) {
    adjMatrix[i] = malloc(temps * sizeof(int));
    }

    for (int i = 0; i < temps; i++) {
        for (int j = 0; j < temps; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Populate adjacency matrix based on the maze structure 
    // check the 4 neighbours for edges
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int index = getNum(i, j);
            if (vertices[index]->data == '#')
            {
                continue;
            }
            else
            {
                if (vertices[index + rows]->data != '#')
                    adjMatrix[index][index+rows] = 1;
                if (vertices[index + 1]->data != '#')
                    adjMatrix[index][index+1] = 1;
                if (vertices[index - rows]->data != '#')
                    adjMatrix[index][index-rows] = 1;
                if (vertices[index - 1]->data != '#')
                    adjMatrix[index][index-1] = 1;
            }
        }
    }

    // Starting the BFS search throughout the maze
    // Mark the starting node as visited and enqueue it
    vertices[starting]->visited = 0;
    vertices[starting]->parent = NULL;
    add_first(deq, vertices[starting]);
    struct node *temp1;
    struct node *temp2;
    int solved = 0;
    int nums[4] = {rows,1,-rows,-1};
    // Perform BFS traversal until the maze is solved or all nodes are visited
    while (!isEmpty(deq) && solved == 0)
    {
        temp1 = remove_last(deq);
        for (int i = 0; i < 4; i++)
        {
            if (adjMatrix[temp1->num][temp1->num + nums[i]] == 1)
            {
                temp2 = vertices[temp1->num + nums[i]];
                if (temp2->visited == 0)
                {
                    temp2->visited = 1;
                    temp2->parent = temp1;
                    add_first(deq, temp2);
                    if (temp2->data == '#')
                    {
                        printf("Error");
                    }
                    if (temp2->data == 'E')
                    {
                        solved = 1;
                        break;
                    }
                    temp2->data = '.';
                }
            }
        }
        temp1->visited = 2;
    }

    // If the maze is solved, mark the shortest path with 'o'
    if(solved){
    for (int i = 0; i < rows * cols; i++)
    {
        if (vertices[i]->data == 'E')
        {
            struct node *temp = vertices[i];
            int count = 0;
            while (temp->data != 'S')
            {
                count++;
                temp = temp->parent;
                if(temp->data != 'S')
                    temp->data = 'o';
            }
            break;
        }
    }
    }

    // Free memory allocated for adjacency matrix
    for (int i = 0; i < rows; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    // If the maze is solved, print the solution
    if (solved == 1)
    {
        int k =0;
        printf("Here is your solved maze: \n");
        printf("The shortest path from S to E is represented by 'o'\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%c ", vertices[getNum(i,j)]->data);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Cannot be solved\n");
    }
}