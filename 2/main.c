//Popa Carmen Gabriela, Pacman, 311CD

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*function which displays the board on the screen;
  it received the number of lines and columns,
  the position of Pacman and of the obstacles,
  and the arrow which represents the character */
void show_board(int N, int M, int x, int y, char arrow,
           int l1, int l2, int l3, int c1, int c2, int c3) {

    int i, j;
    for (i = 0; i<N+2; i++) {
        for (j = 0; j<M+2; j++)
            if (i==y && j==x)
                printf("%c", arrow); //Pacman
            else if ((j==c1 && i==l1) || (j==c2 && i==l2) || (j==c3 && i==l3))
                printf("%c", 'x'); //obstacle
                else if( i==0 || j==0 || i==N+1 || j == M+1)
                    printf("*"); //margins of the board
                else
                    printf(" "); //available to move area

        printf("\n");
    }
}

/*functions which calculate the movement of Pacmam
  they receive pointers to the x or y coordinates
  and increase or increase the value, if possible,
  according to the direction given by the player;
  they also change the arrow which represents Pacman */
void go_left(int *x, char *arrow) {
    if ((*x)-1 != 0) {
        (*x)--;
        (*arrow) = '<';
    }
}

void go_up(int *y, char *arrow) {
    if ((*y)-1 != 0) {
        (*y)--;
        (*arrow) = '^';
    }
}

void go_right(int *x, int M, char *arrow) {
    if ((*x)+1 != M+1) {
        (*x)++;
        (*arrow) = '>';
    }
}

void go_down(int *y, int N, char *arrow) {
    if ((*y)+1 != N+1) {
        (*y)++;
        (*arrow) = 'v';
    }
}

/*function which calculates the movement of the obstacle.
  It received the coordinates of Pacman and pointers
  to the initial coordinates of the obstacle. The function
  determines where the obstacle should move in order to come
  as close to Pacman as possible */
void move_obstacle(int *l, int *c, int x, int y) {
    if (*c == x) //if they are on the same column
        *l -= 1 - 2*(*l < y); //increase or descrease the column value of the obstacle
    else
        if (*l == y) //if they are on the same line
         *c -= 1 - 2*(*c < x); //increase or decrease the line value of the obstacle
        else {
            //move on a diagonal towards Pacman
            *c -= 1 - 2*(*c < x);
            *l -= 1 - 2*(*l < y);
        }
}

/*functions which checks if the game is finished;
  It received the dimensions of the board and the
  coordinates of Pacman and it checks if Pacman is
  in the right-down corner (i.e. N,M) */
int is_game_completed(int x, int y, int N, int M) {
    if (x==M && y==N) return 1;
    return 0;
}

/*functions which checks if the game is lost;
  It received the coordinates of Pacman and of the
  obstacles and it check whether Pacman has touched
  any obstacle and is now dead. */
int is_game_lost(int x, int y, int l1, int l2, int l3,
                 int c1, int c2, int c3) {
    if (x == c1 && y == l1) return 1;
    if (x == c2 && y == l2) return 1;
    if (x == c3 && y == l3) return 1;
    return 0;
}

/*function which determins the development of the game;
  It allows the user to read the direction, it calls the above
  mentioned functions to move Pacman and the obstacles and to
  check if the game is either lost or won and to print the board. */
void play_game(int N, int M, int x, int y, int P, char arrow, char dir,
           int l1, int l2, int l3, int c1, int c2, int c3,
           char m1, char m2, char m3, int nr_mutari) {

        int OK=0; //I assume Pacman hasn't touched any obstacles

        if(is_game_completed(x, y, N, M)) {
            show_board(N, M, x, y, arrow, l1, l2, l3, c1, c2, c3);
            printf("GAME COMPLETED\n");
        } else
           {
            do{
                show_board(N, M, x, y, arrow, l1, l2, l3, c1, c2, c3);
                scanf(" %c", &dir); //reading the direction in which to move - w,a,s,d,q

                if (dir == 'w')
                    go_up(&y, &arrow);
                else if (dir == 'a')
                         go_left(&x, &arrow);
                     else if (dir == 's')
                             go_down(&y, N, &arrow);
                          else if (dir == 'd')
                                  go_right(&x, M, &arrow);

                if (P!=0) {
                    nr_mutari++;
                    if (nr_mutari%2 == 0 && !is_game_lost(x, y, l1, l2, l3, c1, c2, c3)) {
                        //checking for mobile obstacles
                        if (m1 == 'm')
                            move_obstacle(&l1, &c1, x, y);
                        if (m2 == 'm')
                            move_obstacle(&l2, &c2, x, y);
                        if (m3 == 'm')
                            move_obstacle(&l3, &c3, x, y);
                    }

                    OK = is_game_lost(x, y, l1, l2, l3, c1, c2, c3);
                }

            } while( (x!=M || y!=N) && OK == 0 && dir != 'q');

            if (P!=0 && OK==1)
                printf("GAME OVER\n");
            if (is_game_completed(x, y, N, M)) {
                show_board(N, M, x, y, arrow, l1, l2, l3, c1, c2, c3);
                printf("GAME COMPLETED\n");
            }
        }

}

/* the user reads the dimensions of the board, the initial
   coordinates of Pacman, the number of obstacles,
   their type and their coordinates. There can be 0, 1, 2 or 3
   obstacles, hence I added a switch statement according to the value of P.
   If an obstacle is not read, I added it by default at -1, -1 and it will
   be 'fixed' so it doesn't appear on the screen */
int main()
{
    int N, M, x, y, P, l1, l2, l3, c1, c2, c3, nr_mutari = 0;
    char arrow = 'v', dir = '0', m1, m2, m3;

    scanf("%d %d %d %d %d", &N, &M, &x, &y, &P);
    switch(P) {
        case 0:
            play_game(N, M, x, y, P, arrow, dir,
                     -1, -1, -1, -1, -1, -1, 'f', 'f', 'f', nr_mutari);
            break;
        case 1:
            scanf("%d %d %c", &l1, &c1, &m1);
            play_game(N, M, x, y, P, arrow, dir, l1, -1, -1, c1,
                   -1, -1, m1, 'f', 'f', nr_mutari);
            break;

        case 2:
             scanf("%d %d %c %d %d %c", &l1, &c1, &m1, &l2, &c2, &m2);
             play_game(N, M, x, y, P, arrow, dir, l1, l2, -1, c1,
                   c2, -1, m1, m2, 'f', nr_mutari);
             break;

        case 3:
             scanf("%d %d %c %d %d %c %d %d %c", &l1, &c1, &m1,
                   &l2, &c2, &m2, &l3, &c3, &m3);
             play_game(N, M, x, y, P, arrow, dir, l1, l2, l3, c1,
                   c2, c3, m1, m2, m3, nr_mutari);
             break;
    }

    return 0;
}
