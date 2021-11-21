# CS201-Project

**GROUP MEMBERS :-**

* Aditi Das – 2020CSB1064
* Isha Goyal – 2020CSB1089
* Jyoti Dhiman– 2020CSB1092

---
**RAT IN THE MAZE:<br/>**
**ANALYSING DIFFERENT MAZE TRAVERSAL ALGORITHMS FOR SHORTEST PATH**

#### 1. First we take the size of the maze as input i.e. no. of rows and columns.
      For size of the maze simply write: 
      x y

#### 2. Then the maze is taken as input from the user where 0 is traversable while 1 is non-traversable. We have 2 different mazes that can be used, you can take           either of them as input.
        The input of the maze is as follows:

        Maze 1 of size 10X10 used:
        0 0 0 0 0 1 1 0 0 0
        1 0 0 0 0 0 1 0 1 0
        1 1 0 1 0 0 0 1 1 0
        0 1 0 0 0 1 0 0 1 0
        1 1 1 0 1 1 1 0 1 0
        0 1 0 0 0 1 1 0 0 1
        1 1 1 1 0 1 1 0 1 0
        1 0 0 0 0 0 0 0 1 1
        0 0 0 0 0 1 1 0 0 0
        1 1 0 1 1 0 0 1 1 0

        Maze 2 of size 4X4 used:
        0 1 1 1
        0 0 1 0
        1 0 1 1
        0 0 0 0

#### 3. The coordinates of start and finish are taken as input next.
        The coordinates must be typed as follows:
        (a,b)

#### 4. User is then given the choice to select any of the three algorithms used to get the shortest path length or the path itself!
         Algorithms used in this project are:
            1. Backtracking using stacks 
              (To find only the shortest paths, the length of the shortest path is a pre-requisite, and hence Lee algorithm will be run along with Backtracking)
            2. Lee algorithm which is based on BFS
            3. Dijkstra's Algorithm which is a greedy algorithm for graphs 
            
           →Enter B for finding all possible paths or shortest path by Backtracking.
            (In this A should be entered for displaying all possible paths while S should be entered for displaying only the shortest path.)
           →Enter L for finding shortest path length by Lee Algorithm. 
           →Enter D for finding shortest path length by Dijkstra's Algorithm.
           →Enter any other character to Quit.
           
#### The user can choose between the above algorithms till he enters any other character other than the ones mentioned. The program terminates after that. We have also used different colors in output for better readability. 
