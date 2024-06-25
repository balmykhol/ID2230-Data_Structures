/*****************************************
 * Assignment 1
 * Question 2
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code is a maze solver
 * This code borrows deque implementation from 1st question
 * Checks whether the given .txt file has a solution and prints the solution if there exists one
 *
 ***********************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//change the MAXSIZE of the deque according to the maze file 
#define MAXSIZE 1000

int rows = 0;
int cols = 0;

// Define the deque structure
struct deque
{
    int arr[MAXSIZE];
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
void add_first(struct deque *q, int x)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == MAXSIZE - 1))
    {
        printf("DEQUE OVERFLOW. Unable to add %d\n", x);
    }
    else if (isEmpty(q))
    {
        q->head = q->tail = MAXSIZE - 1;
        q->arr[q->head] = x;
    }
    else
    {
        if (q->head == 0)
            q->head = MAXSIZE;
        q->head -= 1;
        q->arr[q->head] = x;
    }
}

/** Removes the element at the begining of the deque
 *
 * @param q the pointer of a structure deque
 * @return the number removed from the deque or -256 if the deque is empty
 */
int remove_first(struct deque *q)
{
    int temp = -256;
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
void add_last(struct deque *q, int x)
{
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == MAXSIZE - 1))
    {
        printf("DEQUE OVERFLOW. Unable to add %d\n", x);
    }
    else if (isEmpty(q))
    {
        q->tail = q->head = 0;
        q->arr[q->tail] = x;
    }
    else
    {
        if (q->tail == MAXSIZE - 1)
            q->tail = -1;
        q->tail += 1;
        q->arr[q->tail] = x;
    }
}

/** Removes the element at the end of the deque
 *
 * @param q the pointer of a structure deque
 * @return the number removed from the deque or -256 if the deque is empty
 */
int remove_last(struct deque *q)
{
    int temp = -256;
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

/** Prints elements of the deque
 *
 * @param q the pointer of a structure deque
 */
void print(struct deque *q)
{
    if (!isEmpty(q))
    {
        printf("Deque: ");
        for (int i = q->head; i != q->tail; i = (i + 1) % MAXSIZE)
        {
            printf("%d ", q->arr[i]);
        }
        printf("%d\n", q->arr[q->tail]);
    }
    else
        printf("Nothing to print\n");
}

#define MAXROWS 1000
#define MAXCOLS 1000

/** Checks whether the current location is same as the required location
 *
 * @param current the current location in the maze
 * @param final the final location in the maze
 * @return true if the current location is the final location, false otherwise
 */
bool reachedFinal(int current, int final)
{
    return (current == final);
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

/** Calculates the distance between the current location and the final location
 *
 * @param number1 The x-cooordinate of current location in the maze
 * @param number2 The y-cooordinate of current location in the maze
 * @param final The final location of the maze in single index coordinate system
 * @return integer specifying the required distance
 */
int distance(int number1, int number2, int final)
{
    return (number1 - getX(final)) * (number1 - getX(final)) + (number2 - getY(final)) * (number2 - getY(final));
}

/** Checks each neighbour of a point and adds to the deque appropriately
 *
 * @param q the pointer of a structure deque
 * @param maze[][] The maze in the txt file
 * @param number1 The x-cooordinate of current location in the maze
 * @param number2 The y-cooordinate of current location in the maze
 * @param final The final location of the maze in single index coordinate system
 */
void exploreAdjacent(struct deque *q, char (*maze)[MAXSIZE], int number1, int number2, int final)
{
    int dis = distance(number1, number2, final);
    int xChange[4] = {0, 0, -1, 1};
    int yChange[4] = {-1, 1, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int newX = number1 + xChange[i];
        int newY = number2 + yChange[i];

        // Check if the new position is within the bounds of the maze
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] != '#' && maze[newX][newY] != '.')
        {
            int newDistance = distance(newX, newY, final);
            int newPosition = getNum(newX, newY);

            if (newDistance > dis)
                add_first(q, newPosition);
            else
                add_last(q, newPosition);
        }
    }
}

int main()
{
    printf("Maze file name? ");
    char str[MAXSIZE];
    fgets(str, MAXSIZE, stdin);

    str[strcspn(str, "\n")] = '\0';
    FILE *file = fopen(str, "r");

    // Initialize variables to store maze data and starting/ending positions
    char maze[MAXROWS][MAXCOLS];
    int startingI, startingJ;
    int endingI, endingJ;

    // Read the maze file character by character and add the data to the maze array
    char ch;
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
            if (ch == 'E')
            {
                endingI = rows;
                endingJ = cols;
            }
            cols++;
        }
    }

    rows = rows + 1;
    int starting = getNum(startingI, startingJ);
    int ending = getNum(endingI, endingJ);

    fclose(file);

    struct deque deq;

    initDeque(&deq);

    // Add the starting position to the first deque
    add_first(&deq, starting);
    bool solved = false;

    printf("Searching for a path ... \n");
    do
    {
        int current = remove_last(&deq);
        maze[getX(current)][getY(current)] = '.';
        if (reachedFinal(current, ending))
        {
            solved = true;
            break;
        }

        // Explore adjacent positions and add them to the deque if they are not traversed yet
        exploreAdjacent(&deq, maze, getX(current), getY(current), ending);
    } while (!(isEmpty(&deq)));
    printf("\n");

    maze[startingI][startingJ] = 'S';
    maze[endingI][endingJ] = 'E';

    // If the maze is solved, print the solution
    if (solved)
    {
        printf("Here is your solved maze: \n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%c", maze[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Cannot be solved\n");
    }
}