
/* RAT IN THE MAZE */
/* 
  Algorithms used in this project are:
   1. Backtracking using stacks
   2. Lee algorithm which is based on BFS
   3. Dijkstra's Algorithm which is a greedy algorithm for graphs 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int path_number = 0; //eventually stores the number of paths
char trash_value;    //just a random character used at random locations while taking input
int length = 0;      //eventually stores the length of the shortest path
int length1 = 0;
int count = 0;                //stores the length of each path at different occasions, used to determine if a particular path is the shortest or not
int shortest_path_number = 0; //eventually stores the numer of shortest paths
int vertices;                 // number of vertices in the graph for Dijkstra
int end;                      // stores end vertex  of maze for Dijkstra Algorithm

void cyan()
{
    printf("\033[1;36m");
}

void red()
{
    printf("\033[1;31m");
}

void white()
{
    printf("\033[1;37m");
}

void blue()
{
    printf("\033[1;34m");
}

typedef struct node //used for queue implementation
{
    int xcoord;   //x coordinate of the stored element
    int ycoord;   //y coordinate of the stored element
    int distance; //distance from the start element
    struct node *next;
} node;

node *path = NULL; //used to save the dequeued node
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

void display_path(int count);

void backtracking(int startx, int starty, int finishx, int finishy, int **maze, int **direction, int x, int y) //bakctracking algo
{
    /* if direction=0 that means that the top neighbour has to looked into, whether it can be pushed into stack or not,
       this also indicates that this particular element has not yet been pushed into the stack
       if direction=1 that means that the left neighbour has to looked into, whether it can be pushed into stack or not
       if direction=2 that means that the bottom neighbour has to looked into, whether it can be pushed into stack or not
       if direction=3 that means that the right neighbour has to looked into, whether it can be pushed into stack or not
       if direction=4 all have been tried, all the neighbours have been looked into */
    /* before starting with backtracking, the start has been pushed into the stack already in the main function */
    if (startx > 0 && maze[startx - 1][starty] == 0 && direction[startx][starty] == 0 && direction[startx - 1][starty] == 0) //checking if the top neighbour can be pushed or not
    {
        direction[startx][starty] = 1;             //according to the above mentioned comment, as one of the directions has already been looked at, irrespective of whether it was inserted or not
        stack_push(startx - 1, starty, direction); //push the top element
        count++;                                   //counting the number of elements in the stack at teh moment, start+now pushed element, hence 1++

        if (startx - 1 == finishx && starty == finishy) //if the pushed element, i.e, the top of stack is the finish
        {
            path_number++;       //increasing the total number of paths by 1
            display_path(count); //displaying the path, at each point this function is called, count contains the number of elements present in the stack at the moment
            stack_pop();         //and popping the finish so that other directions of the topmost element can be looked at
            count--;             //as one element has been popped, the number of elements in the stack has decreased by 1
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

    direction[startx][starty] = 0; //all possible neighbours have been visited and yet no path has been found from this element and hence it needs to be popped, so direction=0
    stack_pop();
    count--;
    return;
}

void display_path(int count) //displays the path
{
    tnode *temp = stackhead;
    if (length1 == 0) //calculates the total number of shortest_paths, by storing the smallest lengths so far in length1
        length1 = count;
    if (count == length1)
        shortest_path_number++;
    else if (count < length1)
    {
        shortest_path_number = 1;
        length1 = count;
    }
    if (trash_value == 'A') //displays all paths
    {
        while (temp != stacktop)
        {
            cyan();
            printf("(%d,%d)->", temp->x, temp->y);
            temp = temp->next;
        }
        printf("(%d,%d)\n", temp->x, temp->y);
        white();
    }
    else if (trash_value == 'S') //displays only the shortest path
    {
        if (count == length) //if the shortest path found, only then print it
        {
            while (temp != stacktop)
            {
                cyan();
                printf("(%d,%d)->", temp->x, temp->y);
                temp = temp->next;
            }
            printf("(%d,%d)\n", temp->x, temp->y);
            white();
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

    if (path == NULL)       //path is null only at the very beginning, after that any element which is dequeued becomec path
        temp->distance = 0; //hence distance of start from start is 0
    else
        temp->distance = path->distance + 1; //else whatever was the distance of the dequequed element +1 , will be the distance of the enqueued element, as the neighbouring element of dequeue are being inserted
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
    int i = 0;
    while (head != NULL) //untill the queue isn't empty, look at the main function, the first element has already been enqueued there
    {
        remove_at_first();
        int i = path->xcoord;                                   //the x coordinate of the dequeued element
        int j = path->ycoord;                                   //the y coordinate of the dequeued element
        if (path->xcoord == finishx && path->ycoord == finishy) //the dequeued element is the final point
        {
            length = path->distance; //net length of the path
            cyan();
            printf("The shortest possible path length calculated by Lee Algorithm is of distance %d units!\n", path->distance);
            white();
            path = NULL;
            return i + 1; //to indicate that the path been found
        }
        else
        {
            if (i != x - 1 && maze[i + 1][j] == 0 && visited[i + 1][j] == 0) //conditions to see if the bottom neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i + 1, j, visited);                 //if yes then insert
            if (j != y - 1 && maze[i][j + 1] == 0 && visited[i][j + 1] == 0) //conditions to see if the left neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i, j + 1, visited);                 //if yes then insert
            if (j > 0 && maze[i][j - 1] == 0 && visited[i][j - 1] == 0)      //conditions to see if the right neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i, j - 1, visited);                 //if yes then insert
            if (i > 0 && maze[i - 1][j] == 0 && visited[i - 1][j] == 0)      //conditions to see if the top neighbour of the dequed element can be inserted or not
                visited = insert_at_tail(i - 1, j, visited);                 //if yes then insert
        }
    }
    return i;
}

int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int graph[vertices][vertices], int src)
{
    int dist[vertices], flag = 0; // The output array. dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[vertices]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < vertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++)
    {

        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < vertices; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
            if (dist[end] != INT_MAX)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }

    if (dist[end] == INT_MAX)
    {
        red();
        printf("No Path\n");
        white();
        return;
    }
    cyan();
    printf("The shortest possible path length calculated by Dijkstra's Algorithm is of distance %d units!\n", dist[end]);
    white();
}

int main()
{
    int x, y, i, j, c1 = 1;
    char *c, algo;
    int startx, starty;
    int finishx, finishy;
    node *path = NULL;
    int **visited; //is a x y size matrix, stores 0 or 1, 0 if the correspondind element of the maze is not yet visited, and 1 if it has been visited, used in lee algo
    int found;     //stores the info whether a path has been found or not
    
    white();
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

    printf("\nEnter the maze. Remember that 0 represents traversable path of the maze while 1 is non-traversable!\n");
    printf("No other value is allowed!\n");
    for (i = 0; i < x; i++)
    {
        scanf(" %[^\n]", c);
        for (j = 0; j < y; j++)
        {
            maze[i][j] = (int)c[2 * j] - 48;
            if (maze[i][j] != 0 && maze[i][j] != 1)
            {
                red();
                printf("Error: Wrong Input!");
                white();
                return 0;
            }
        }
    }

    printf("\nEnter the coordinates of start and finish! Remember they must be cells with cell value 0 so that they are traversable!\n");
    printf("Start: "); //starting coordinate
    scanf(" %c%d%c%d%c", &trash_value, &startx, &trash_value, &starty, &trash_value);
    if (startx < 0 || startx > x - 1 || starty < 0 || starty > y - 1 || maze[startx][starty] == 1)
    {
        red();
        printf("Error: Wrong Inputs!\n");
        white();
        return 0;
    }
    printf("Finish: "); //ending coordinate
    scanf(" %c%d%c%d%c", &trash_value, &finishx, &trash_value, &finishy, &trash_value);
    if (finishx < 0 || finishx > x - 1 || finishy < 0 || finishy > y - 1 || maze[startx][starty] == 1)
    {
        red();
        printf("Error: Wrong Inputs!\n");
        white();
        return 0;
    }
    
    blue();
    printf("\nTo find the shortest path from source to finish you are given three algorithms.\n1. Backtracking using stacks (Will provide you with all possible paths as well!)\n2. Lee Algorithm based on BFS\n3. Dijkstra's shortest path Algorithm\n\n");
    white();
    printf("→Enter B for finding all possible paths or shortest path by Backtracking.\n (To find only the shortest paths, the length of the shortest path is a pre-requisite, and hence Lee algorithm will be run along with Backtracking.)\n→Enter L for finding shortest path length by Lee Algorithm. \n→Enter D for finding shortest path length by Dijkstra's Algorithm.\n→Enter any other character to Quit.\n\nEnter your choice:\n");
    scanf(" %c", &algo);

    while (algo == 'L' || algo == 'B' || algo == 'D')
    {
        switch (algo)
        {

        case 'L':
            length = 0;
            head = NULL;
            tail = NULL;
            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                    visited[i][j] = 0;
            }
            visited = insert_at_tail(startx, starty, visited);  //inserting the start into the queue
            found = lee(maze, finishx, finishy, x, y, visited); //calling lee and storing the return in found
            if (found == 0)
            {
                red();
                printf("No path found!\n");
                white();
            }
            break;

        case 'B':
            path_number = 0;
            shortest_path_number = 0;
            length = 0;
            length1 = 0;
            count = 0;
            head = NULL;
            tail = NULL;
            stacktop = NULL;
            stackhead = NULL;
            for (i = 0; i < x; i++) //a matrix just the same as visited is needed, which i have called direction in backtracking related functioms, stack push, stack pop, backtracking, display path
            {                       // so for that, since visited is not useful anymore, i re-write all elements of visited to 0
                for (j = 0; j < y; j++)
                    visited[i][j] = 0;
            }
            stack_push(startx, starty, visited);
            printf("Do you want to see all possible paths or just the shortest paths?\n");
            printf("Enter A for all paths and S for shortest: \n");
            scanf(" %c", &trash_value);
            if (trash_value != 'S' && trash_value != 'A')
            {
                red();
                printf("Invalid!\n");
                white();
                return 0;
            }
            else if (trash_value == 'A')
            {
                cyan();
                printf("All the possible paths from start to finish are as follows:\n");
                backtracking(startx, starty, finishx, finishy, maze, visited, x, y);
                cyan();
                printf("The total number of shortest paths are: %d\n", shortest_path_number);
                printf("The total paths are: %d\n", path_number);
                white();
            }
            else if (trash_value == 'S')
            {
                visited = insert_at_tail(startx, starty, visited);
                found = lee(maze, finishx, finishy, x, y, visited); //calling lee and storing the return in found
                if (found == 0)
                {
                    red();
                    printf("No path found!\n");
                    white();
                }
                for (i = 0; i < x; i++)
                {
                    for (j = 0; j < y; j++)
                        visited[i][j] = 0;
                }
                backtracking(startx, starty, finishx, finishy, maze, visited, x, y);
                cyan();
                printf("The total number of shortest paths are: %d\n", shortest_path_number);
                printf("The total paths are: %d\n", path_number);
                white();
            }

            break;

        case 'D':
            c1 = 1;
            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                {
                    visited[i][j] = maze[i][j];
                }
            }
            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                {

                    if (visited[i][j] == 0)
                        visited[i][j] = ++c1;
                }
            }
            vertices = c1 - 1;
            int graph[c1 - 1][c1 - 1];
            end = visited[finishx][finishy] - 2;
            memset(graph, 0, sizeof(graph));

            for (i = 0; i < x; i++)
            {
                for (j = 0; j < y; j++)
                {
                    if (visited[i][j] == 1)
                        continue;
                    if (i + 1 < x && (visited[i + 1][j] != 1))
                    {
                        graph[visited[i][j] - 2][visited[i + 1][j] - 2] = 1;
                        graph[visited[i + 1][j] - 2][visited[i][j] - 2] = 1;
                    }
                    if (j + 1 < y && (visited[i][j + 1] != 1))
                    {
                        graph[visited[i][j] - 2][visited[i][j + 1] - 2] = 1;
                        graph[visited[i][j + 1] - 2][visited[i][j] - 2] = 1;
                    }
                }
            }

            dijkstra(graph, visited[startx][starty] - 2);
        }
        printf("\n→Enter B for finding all possible paths or shortest path by Backtracking.\n (To find only the shortest paths, the length of the shortest path is a pre-requisite, and hence Lee algorithm will be run along with Backtracking)\n→Enter L for finding shortest path length by Lee Algorithm. \n→Enter D for finding shortest path length by Dijkstra's Algorithm.\n→Enter any other character to Quit\n\nEnter your choice again:\n");
        scanf(" %c", &algo);
    }

    blue();
    printf("\nEND\n");
    white();

    //freeing memory
    free(maze);
    free(c);
    free(visited);
    return 0;
}
