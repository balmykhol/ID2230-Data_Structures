/**********************************************
 * Assignment 1
 * Question 1
 * Name:    Chakka Surya Saketh
 * Roll no: ai22btech11005
 * E-mail:  ai22btech11005@iith.ac.in
 * Course:  ID2230
 *
 * This C code implements a deque using an array and circular buffer.
 * The code includes functions for initializing, adding, removing, checking emptiness,
 * and printing the deque's contents.
 * All functions except print function run in O(1) average runtime.
 *
 ***********************************************/
#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 100000

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

int main()
{
    struct deque deq;
    // Initialize the deque
    initDeque(&deq);

    int number;
    printf("Enter\t1. add_first\t2. add_last\t3. remove_first\t4. remove_last\t5. print\t-1. exit\n");
    int command = 0;
    while (command != -1)
    {
        printf("Command: ");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            printf("Enter the number to be added: ");
            scanf("%d", &number);
            add_first(&deq, number);
            break;
        case 2:
            printf("Enter the number to be added: ");
            scanf("%d", &number);
            add_last(&deq, number);
            break;
        case 3:
            remove_first(&deq);
            break;
        case 4:
            remove_last(&deq);
            break;
        case 5:
            print(&deq);
            break;
        case -1:
            break;
        default:
            printf("Enter the valid input\n");
            break;
        }
    }
    return 0;
}