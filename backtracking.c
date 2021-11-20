#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int path_number = 0; //eventually stores the number of paths
char random; //just a random character used at random locations while taking input
int length=0; //eventually stores the length of the shortest path
int count=0; //stores the length of each path at different occasions, used to determine if a particular path is the shortest or not
int shortest_path_number=0; //eventually stores the numer of shortest paths

typedef struct node //used for queue implementation
{
    int xcoord; //x coordinate of the stored element
    int ycoord; //y coordinate of the stored element
    int distance; //distance from the start element
    struct node *next;
} node;

node *path;        //used to save the dequeued node
node *head = NULL; //used for queue
node *tail = NULL; //end of queue

typedef struct tnode //used for stack implementation
{
    int x; //x coordinate
    int y; //y coordinate
    struct tnode *next;
    struct tnode *prev;
} tnode;

tnode *stackhead = NULL;
tnode *stacktop = NULL;

void stack_push(int startx, int starty, int **direction)
{
    tnode *temp;
    temp = (tnode *)malloc(sizeof(tnode));
    temp->x = startx;
    temp->y = starty;
    temp->next = NULL;
    temp->prev = NULL;
    if (stackhead == NULL)
    {
        stackhead = temp;
        stacktop = temp;
    }
    else
    {
        temp->prev = stacktop;
        stacktop->next = temp;
        stacktop = stacktop->next;
    }
}

void stack_pop()
{
    tnode *temp;
    if (stacktop == stackhead)
    {
        stacktop = NULL;
        stackhead = NULL;
    }
    else
    {
        temp = stacktop->prev;
        temp->next = NULL;
        stacktop = temp;
    }
}

void backtracking(int startx, int starty, int finishx, int finishy, int **maze, int **direction, int x, int y) //bakctracking algo
{
    //if direction=0 that means that the top neighbour has to looked into, whether it can be pushed into stack or not, this also indicates that this particular element has not yet been pushed into the stack
    //if direction=1 that means that the left neighbour has to looked into, whether it can be pushed into stack or not
    //if direction=2 that means that the bottom neighbour has to looked into, whether it can be pushed into stack or not
    //if direction=3 that means that the right neighbour has to looked into, whether it can be pushed into stack or not
    //if direction=4 all have been tried, all the neighbours have been looked into
    //before starting with backtracking, the start has been pushed into the stack already in the main function
    if (startx > 0 && maze[startx - 1][starty] == 0 && direction[startx][starty] == 0 && direction[startx - 1][starty] == 0) //checking if the top neighbour can be pushed or not
    {
        direction[startx][starty] = 1; //according to the above mentioned comment, as one of the directions has already been looked at, irrespective of whether it was inserted or not
        stack_push(startx - 1, starty, direction); //push the top element
        count++; //counting the number of elements in the stack at teh moment, start+now pushed element, hence 1++
        if (startx - 1 == finishx && starty == finishy) //if the pushed element, i.e, the top of stack is the finish
        {
            path_number++; //increasing the total number of paths by 1
            display_path(count); //displaying the path, at each point this function is called, count contains the number of elements present in the stack at the moment
            stack_pop(); //and popping the finish so that other directions of the topmost element can be looked at
            count--; //as one element has been popped, the number of elements in the stack has decreased by 1
        }
        else
            backtracking(startx - 1, starty, finishx, finishy, maze, direction, x, y); //if the topmost element is not finish, then simply call backtracking for the topmost element now
    }
    direction[startx][starty] = 1; //according to the above mentioned comment, as one of the directions has already been looked at, irrespective of whether it was inserted or not
    //the same thing is done below for all the four directions
    if (starty > 0 && maze[startx][starty - 1] == 0 && direction[startx][starty] == 1 && direction[startx][starty - 1] == 0)
    {
        direction[startx][starty] = 2;
        stack_push(startx, starty - 1, direction);
        count++;
        if (startx == finishx && starty - 1 == finishy)
        {
            path_number++;
            display_path(count);
            stack_pop();
            count--;
        }
        else
            backtracking(startx, starty - 1, finishx, finishy, maze, direction, x, y);
    }
    direction[startx][starty] = 2;
    if (startx != x - 1 && maze[startx + 1][starty] == 0 && direction[startx][starty] == 2 && direction[startx + 1][starty] == 0)
    {
        direction[startx][starty] = 3;
        stack_push(startx + 1, starty, direction);
        count++;
        if (startx + 1 == finishx && starty == finishy)
        {
            path_number++;
            display_path(count);
            stack_pop();
            count--;
        }
        else
            backtracking(startx + 1, starty, finishx, finishy, maze, direction, x, y);
    }
    direction[startx][starty] = 3;
    if (starty != y - 1 && maze[startx][starty + 1] == 0 && direction[startx][starty] == 3 && direction[startx][starty + 1] == 0)
    {
        direction[startx][starty] = 4; //all directions have been visited, and this element is still present in the stack
        stack_push(startx, starty + 1, direction);
        count++;
        if (startx == finishx && starty + 1 == finishy)
        {
            path_number++;
            display_path(count);
            stack_pop();
            count--;
        }
        else
            backtracking(startx, starty + 1, finishx, finishy, maze, direction, x, y);
    }
    direction[startx][starty] = 0;//all possible neighbours have been visited and yet no path has been found from this element and hence it needs to be popped, so direction=0
    stack_pop();
    count--;
    return;
}

void display_path(int count) //displays the path
{
    tnode *temp = stackhead;
    if (random == 'A') //displays all paths
    {
        if(count==length) //to calculate the number of shortest paths, as length stores the length of the shortest path
            shortest_path_number++;
        while (temp != stacktop)
        {
            printf("(%d,%d)->", temp->x, temp->y);
            temp = temp->next;
        }
        printf("(%d,%d)\n", temp->x, temp->y);
    }
    else if(random=='S') //displays only the shortest path
    {
        if (count == length) //if the shortest path found, only then print it
        {
            shortest_path_number++;
            while (temp != stacktop)
            {
                printf("(%d,%d)->", temp->x, temp->y);
                temp = temp->next;
            }
            printf("(%d,%d)\n", temp->x, temp->y);
        }
    }
    return;
}

//after this are functions related to lee algo

int **insert_at_tail(int startx, int starty, int **visited) //inserting element in the queue
{
    visited[startx][starty] = 1; //when an elemnt is inserted, its corresponding visited[][] is marked as 1, else its 0
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->xcoord = startx;
    temp->ycoord = starty;
    if (path==NULL) //path is null only at the very beginning, after that any element which is dequeued becomec path
        temp->distance = 0 ; //hence distance of start from start is 0
    else
        temp->distance=path->distance +1; //else whatever was the distance of the dequequed element +1 , will be the distance of the enqueued element, as the neighbouring element of dequeue are being inserted
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = tail->next;
    }
    return visited;
}

void remove_at_first(void) //dequeuing, the element that is dequeued is for the time pointed at by path, so that its values can be used for comparison
{
    node *temp = head;
    node *temp1;
    temp1 = head->next;
    head = temp1;
    temp->next = NULL;
    path = temp;
}

int lee(int **maze, int finishx, int finishy, int x, int y, int **visited) // lee algorithm, uses BFS
{
    int i=0;
    while (head != NULL) //untill the queue isn't empty, look at the main function, the first element has already been enqueued there
    {
        remove_at_first();
        int i=path->xcoord; //the x coordinate of the dequeued element
        int j=path->ycoord; //the y coordinate of the dequeued element
        if (path->xcoord == finishx && path->ycoord == finishy) //the dequeued element is the final point
        {
            length=path->distance ; //net length of the path
            printf("The shortest possible path is of distance %d\n", path->distance);
            return i + 1; //to indicate that the path been found
        }
        else
        {
            if (i != x - 1 && maze[i + 1][j] == 0 && visited[i + 1][j] == 0) //conditions to see if the bottom neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i + 1, j, visited); //if yes then insert
            if (j != y - 1 && maze[i][j + 1] == 0 && visited[i][j + 1] == 0) //conditions to see if the left neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i, j + 1, visited); //if yes then insert
            if (j > 0 && maze[i][j - 1] == 0 && visited[i][j - 1] == 0) //conditions to see if the right neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i, j - 1, visited); //if yes then insert
            if (i > 0 && maze[i - 1][j] == 0 && visited[i - 1][j] == 0) //conditions to see if the top neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i - 1, j, visited); //if yes then insert
        }
    }
    return i;
}

int main()
{
    int x, y, i, j;
    char *c;
    int startx, starty;
    int finishx, finishy;
    node *path = NULL;
    int **visited; //is a x y size matrix, stores 0 or 1, 0 if the correspondind element of the maze is not yet visited, and 1 if it has been visited, used in lee algo
    int found; //stores the info whether a path has been found or not
    printf("Enter the number of rows and columns of the maze: ");
    scanf("%d%d", &y, &x);
    c = (char *)malloc(2 * y * sizeof(char));
    int **maze; //storing the maze
    maze = (int **)malloc(x * sizeof(int *));
    for (i = 0; i < x; i++)
        maze[i] = (int *)malloc(y * sizeof(int));
    visited = (int **)malloc(x * sizeof(int *));
    for (i = 0; i < x; i++)
    {
        visited[i] = (int *)malloc(y * sizeof(int));
        for (j = 0; j < y; j++)
        {
            visited[i][j] = 0;
        }
    }
    printf("Enter the maze. Remember that 0 represents traversal part of the maze while 1 is non-traversable\n");
    printf("No other value is allowed\n");
    for (i = 0; i < x; i++)
    {
        scanf(" %[^\n]", c);
        for (j = 0; j < y; j++)
        {
            maze[i][j] = (int)c[2 * j] - 48;
            if (maze[i][j] != 0 && maze[i][j] != 1)
            {
                printf("Error: wrong input");
                return 0;
            }
        }
    }
    printf("Enter the coordinates of start and finish, both of which have to be the cells with 0 value, hence traversable\n");
    printf("Start: "); //starting coordinate
    scanf(" %c%d%c%d%c", &random, &startx, &random, &starty, &random);
    if (startx < 0 || startx > x - 1 || starty < 0 || starty > y - 1 || maze[startx][starty]==1)
    {
        printf("Error: Wrong inputs\n");
        return 0;
    }
    printf("finish: "); //ending coordinate
    scanf(" %c%d%c%d%c", &random, &finishx, &random, &finishy, &random);
    if (finishx < 0 || finishx > x - 1 || finishy < 0 || finishy > y - 1 || maze[startx][starty]==1)
    {
        printf("Error: Wrong inputs\n");
        return 0;
    }
    visited = insert_at_tail(startx, starty, visited); //inserting the start into the queue
    found = lee(maze, finishx, finishy, x, y, visited); //calling lee and storing the return in found
    if (found == 0)
    {
        printf("No path\n");
        return 0;
    }
    for(i=0;i<x;i++) //a matrix just the same as visited is needed, which i have called direction in backtracking related functioms, stack push, stack pop, backtracking, display path
    {               // so for that, since visited is not useful anymore, i re-write all elements of visited to 0
        for(j=0;j<y;j++)
            visited[i][j]=0;
    }
    stack_push(startx, starty, visited);
    printf("Do you want to see all possible paths or just the shortest paths\n");
    printf("Enter A for all paths and S for shortest: ");
    scanf(" %c", &random);
    if (random != 'S' && random != 'A')
    {
        printf("Invalid\n");
        return 0;
    }
    backtracking(startx, starty, finishx, finishy, maze, visited, x, y);
    printf("The total number of shortest paths are: %d\n",shortest_path_number);
    printf("The total paths are: %d\n", path_number);
}

//backtracking using stacks
//lee algorithm which is based on BFS