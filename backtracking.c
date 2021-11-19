#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int value = 0; //used to calculate the distance from the source
int i = 0;
int path_number=0;

typedef struct node
{
    int xcoord;
    int ycoord;
    int distance;
    struct node *next;
} node;

node *path;        //used to save the dequeued node
node *head = NULL; //used for queue
node *tail = NULL; //end of queue

typedef struct tnode
{
    int x;
    int y;
    struct tnode *next;
    struct tnode *prev;
} tnode;

tnode *stackhead = NULL;
tnode *stacktop=NULL;

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
    if(stacktop==stackhead)
    {
        stacktop=NULL;
        stackhead=NULL;
    }
    else
    {
        temp = stacktop->prev;
        temp->next = NULL;
        stacktop=temp;
    }
    
}

void backtracking(int startx, int starty, int finishx, int finishy, int **maze, int **direction, int x, int y)
{
    //if direction=0
    //if direction=1
    //if direction=2
    //if direction=3
    //if direction=4 
    if (startx > 0 && maze[startx - 1][starty] == 0 && direction[startx][starty] == 0 && direction[startx-1][starty]!=3)
    {
        direction[startx][starty]=1;
        stack_push(startx-1,starty,direction);
        if(startx-1==finishx && starty==finishy)
        {
            path_number++;
            print_path();
            return;
        }
        else
            backtracking(startx-1,starty,finishx,finishy,maze,direction,x,y);
    }
    else
        direction[startx][starty]=1;
    if (starty > 0 && maze[startx][starty - 1] == 0 && direction[startx][starty] == 1 && direction[startx][starty-1]!=4)
    {
        direction[startx][starty]=2;
        stack_push(startx,starty-1,direction);
        if(startx==finishx && starty-1==finishy)
        {
            path_number++;
            print_path();
            return;
        }
        else
            backtracking(startx,starty-1,finishx,finishy,maze,direction,x,y);
    }
    else
        direction[startx][starty]=2;
    if (startx != x - 1 && maze[startx + 1][starty] == 0 && direction[startx][starty] == 2 && direction[startx+1][starty]!=1)
    {
        direction[startx][starty]=3;
        stack_push(startx+1,starty,direction);
        if(startx+1==finishx && starty==finishy)
        {
            path_number++;
            print_path();
            return;
        }
        else
            backtracking(startx+1,starty,finishx,finishy,maze,direction,x,y);
    }
    else
        direction[startx][starty]=3;
    if (starty != y - 1 && maze[startx][starty + 1] == 0 && direction[startx][starty] == 3 && direction[startx][starty+1]!=2)
    {
        direction[startx][starty]=4;
        stack_push(startx,starty+1,direction);
        if(startx==finishx && starty+1==finishy)
        {
            path_number++;
            print_path();
            return;
        }
        else
            backtracking(startx,starty+1,finishx,finishy,maze,direction,x,y);
    }  
    direction[startx][starty]=4;
    stack_pop();
    return;
}

void print_path()
{
    tnode* temp=stackhead;
    while(temp!=stacktop)
    {
        printf("(%d,%d)->",temp->x,temp->y);
        temp=temp->next;
    }
    printf("(%d,%d)\n",temp->x,temp->y);
    return;
}

int **insert_at_tail(int startx, int starty, int **visited)
{
    visited[startx][starty] = 1;
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->xcoord = startx;
    temp->ycoord = starty;
    temp->distance = value;
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

void remove_at_first(void)
{
    node *temp = head;
    node *temp1;
    temp1 = head->next;
    head = temp1;
    temp->next = NULL;
    path = temp;
}

int lee(int **maze, int startx, int starty, int finishx, int finishy, int x, int y, int **visited) //u can rename it...this is the lee algo
{
    int a = 0, b = 0, c = 0, d = 0;
    while (head != NULL)
    {
        remove_at_first();
        if (path->xcoord == finishx && path->ycoord == finishy)
        {
            printf("The shortest possible path is of distance %d\n", path->distance + 1);
            return i + 1;
        }
        else
        {
            value++;
            if (startx != x - 1 && maze[startx + 1][starty] == 0 && visited[startx + 1][starty] == 0)
            {
                visited = insert_at_tail(startx + 1, starty, visited);
                a = 1;
            }
            if (starty != y - 1 && maze[startx][starty + 1] == 0 && visited[startx][starty + 1] == 0)
            {
                visited = insert_at_tail(startx, starty + 1, visited);
                b = 1;
            }
            if (starty > 0 && maze[startx][starty - 1] == 0 && visited[startx][starty - 1] == 0)
            {
                visited = insert_at_tail(startx, starty - 1, visited);
                c = 1;
            }
            if (startx > 0 && maze[startx - 1][starty] == 0 && visited[startx - 1][starty] == 0)
            {
                visited = insert_at_tail(startx - 1, starty, visited);
                d = 1;
            }
            if (a == 1)
                i = lee(maze, startx + 1, starty, finishx, finishy, x, y, visited);
            if (b == 1)
                i = lee(maze, startx, starty + 1, finishx, finishy, x, y, visited);
            if (c == 1)
                i = lee(maze, startx, starty - 1, finishx, finishy, x, y, visited);
            if (d == 1)
                i = lee(maze, startx - 1, starty, finishx, finishy, x, y, visited);
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
    char random;
    node *path = NULL;
    int **visited;
    int **direction;
    int found;
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
    direction = (int **)malloc(x * sizeof(int *));
    for (i = 0; i < x; i++)
    {
        direction[i] = (int *)malloc(y * sizeof(int));
        for (j = 0; j < y; j++)
        {
            direction[i][j] = 0;
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
                break;
            }
        }
    }
    printf("Enter the coordinates of start and finish, both of which have to be the cells with 0 value, hence traversable\n");
    printf("Start: "); //starting coordinate
    scanf(" %c%d%c%d%c", &random, &startx, &random, &starty, &random);
    if (startx < 0 || startx > x - 1 || starty < 0 || starty > y - 1)
        printf("Error: Wrong inputs\n");
    printf("finish: "); //ending coordinate
    scanf(" %c%d%c%d%c", &random, &finishx, &random, &finishy, &random);
    if (finishx < 0 || finishx > x - 1 || finishy < 0 || finishy > y - 1)
        printf("Error: Wrong inputs\n");
    visited = insert_at_tail(startx, starty, visited);
    found = lee(maze, startx, starty, finishx, finishy, x, y, visited);
    if (found == 0)
        printf("No path\n");
    stack_push(startx, starty, direction);
    backtracking(startx,starty,finishx,finishy,maze,direction,x,y);
    printf("The total paths are: %d\n",path_number);
}

//backtracking using stacks...v have to try getting all teh possible paths from this, then using lee v can find the shortest path also
//have to see if the above is possible
//lee algorithm which is based on BFS...this only gives the shortest path length and not the path itself