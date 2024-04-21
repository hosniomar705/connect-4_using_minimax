#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

char board[6][7];
int arr[7];
int diff();
void player(char);
int insert(char c,int x);
void reinsert(int x);
void print();
int points();
void startgame();
int checkboard();
int search(char a,char b,char c,char d,char e);
long long int minimax(int depth, int isMaximizing,int firstTime);

char player1piece='X';
char AI_player2piece='O';


int main()
{
    char again;
    do
    {
        startgame();
        printf("Play again[Y/N]:");
        scanf(" %c",&again);
    }while (again=='y'||again=='Y');
    return 0;
}
//print the board
void print()
{
    printf(" ");
        for (int c=0;c<7;c++)
        {
            printf(" %d   ",c);
        }
         printf("\n");
    for (int r=0;r<6;r++) {
        for (int c=0;c<7;c++) {
            printf(" [%c] ",board[r][c]);
        }
        printf("\n");
    }
}
//add the piece to the board
int insert(char c,int x)
{
    if((x<0)||(x>6))
    {
       return 3;
    }
    else if(arr[x]!=6)
    {
        board[5-arr[x]][x]=c;
        arr[x]++;
        return 1;
    }
    return 0;
}
//delete piece from the board
void reinsert(int x)
{
        board[6-arr[x]][x]=' ';
        arr[x]--;

}
//game
void startgame()
{
    //board initializaton
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            board[i][j]=' ';
            arr[j]=0;
        }
    }
    //
    srand(time(0));
    int turn=(rand()%2);
    printf("choose the mode:\n1- 1 VS 1\n2- 1 VS AI\n");
    int mode,difficulty;
    //user chooses the mode
    scanf("%d",&mode);
    //user chooses the difficulty
    if (mode==2)
    {
       difficulty=diff();
    }
    printf("each player must choose a column form 0 to 6\n");
    print();
     //user input
     while (checkboard()!=3)
        {
           //player1 turn
           if(turn==0)
           {
                printf("player1 : ");
                player(player1piece);
                //check win
                print();
                if(checkboard()==1)
                {
                    printf("player1 wins\n");
                    return;
                }
                turn=1;
           }
           else if(turn==1)
           {
                //player2 turn
                if (mode==1)
                {
                    printf("player2 : ");
                    player(AI_player2piece);
                    //check win
                    print();
                    if(checkboard()==2)
                    {
                        printf("player2 wins\n");
                        return;
                    }
                }
                //AI turn
                else
                {
                    printf("AI:\n");
                    int result= minimax(difficulty,1,1);
                    print();
                    if(checkboard()==2)
                    {
                         printf("AI wins\n");
                         return;
                    }
                }
                turn=0;
           }

        }
    printf("DRAW\n");

}
//check who won - board is full or not (return 3 if there is place in the board,return 1 if player1 won,return 2 if player2 won,return 3 if the board is full)
int checkboard()
{
    //row
    for(int r=0;r<6;r++)
     {
         for(int c=0;c<4;c++)
         {
             if(search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],AI_player2piece)==4)
             {
                 return 2;
             }
             if(search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],player1piece)==4)
             {
                 return 1;
             }
         }
     }
     //coloum
     for(int c=0;c<7;c++)
     {
         for(int r=0;r<3;r++)
         {
             if(search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],AI_player2piece)==4)
             {
                 return 2;
             }
             if(search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],player1piece)==4)
             {
                 return 1;
             }
         }
     }
     //diagonial
     for(int r=0;r<3;r++)
     {
         for(int c=0;c<4;c++)
         {
             if(search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],AI_player2piece)==4)
             {
                 return 2;
             }
             if(search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],player1piece)==4)
             {
                 return 1;
             }
         }
     }
     for(int r=3;r<6;r++)
     {
         for(int c=0;c<4;c++)
         {
             if(search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],AI_player2piece)==4)
             {
                 return 2;
             }
             if(search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],player1piece)==4)
             {
                 return 1;
             }
         }
     }
    for(int i=0;i<7;i++)
    {
       if(arr[i]!=6)
      {
        return 0;
      }
    }
    return 3;
}
//check how many pieces or empty slots are in a 4 slots
int search(char a,char b,char c,char d,char e)
 {
     int p=0;
     if(a==e)p++;
     if(b==e)p++;
     if(c==e)p++;
     if(d==e)p++;
     return p;
 }
//give a score based on the state of the board
int points()
 {
     int s=0;
     int p=0;
     for(int r=0;r<6;r++)
     {
         for(int c=0;c<4;c++)
         {
             if((search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],AI_player2piece)==3)&&(search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],' ')==1))
             {
                 s+=5;
             }
             else if((search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],AI_player2piece)==2)&&(search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],' ')==2))
             {
                 s+=2;
             }
             if((search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],player1piece)==3)&&(search(board[r][c],board[r][c+1],board[r][c+2],board[r][c+3],' ')==1))
             {
                 s-=4;
             }
         }
     }
     for(int c=0;c<7;c++)
     {
         for(int r=0;r<3;r++)
         {
             if((search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],AI_player2piece)==3)&&(search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],' ')==1))
             {
                 s+=5;
             }
             else if((search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],AI_player2piece)==2)&&(search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],' ')==2))
             {
                 s+=2;
             }
             if((search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],player1piece)==3)&&(search(board[r][c],board[r+1][c],board[r+2][c],board[r+3][c],' ')==1))
             {
                 s-=4;
             }
         }
     }
     for(int r=0;r<3;r++)
     {
         for(int c=0;c<4;c++)
         {
             if((search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],AI_player2piece)==3)&&(search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],' ')==1))
             {
                 s+=5;
             }
             else if((search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],AI_player2piece)==2)&&(search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],' ')==2))
             {
                 s+=2;
             }
             if((search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],player1piece)==3)&&(search(board[r][c],board[r+1][c+1],board[r+2][c+2],board[r+3][c+3],' ')==1))
             {
                 s-=4;
             }
         }
     }
     for(int r=3;r<6;r++)
     {
         for(int c=0;c<4;c++)
         {
             if((search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],AI_player2piece)==3)&&(search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],' ')==1))
             {
                 s+=5;
             }
             else if((search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],AI_player2piece)==2)&&(search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],' ')==2))
             {
                 s+=2;
             }
             if((search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],player1piece)==3)&&(search(board[r][c],board[r-1][c+1],board[r-2][c+2],board[r-3][c+3],' ')==1))
             {
                 s-=4;
             }
         }
     }
     for(int r=0;r<6;r++)
     {
         if(board[r][3]==AI_player2piece)
         {
             p++;
         }
     }
     s=s+(p*3);
    return s;
 }
 //choose AI difficulty
int diff()
{
    int level;
    printf("Enter the difficulty from (1-6):");
    scanf("%d",&level);
    while((level>6)||(level<1))
    {
        printf("Enter a valid value:");
        scanf("%d",&level);
    }
    return level;
}
//player input
void player(char c)
{
    int player;
    scanf("%d",&player);
    int check1=insert(c,player);
    while((check1==0)||(check1==3))
        {
            if(check1==0)printf("this column is full! please,choose another column\n");
            else if(check1==3)printf("choose a column form 0 to 6\n");
            scanf("%d",&player);
            check1=insert(c,player);
        }

}
//AI algorithm
long long int minimax(int depth, int isMaximizing,int firstTime)
{
    //int finalScore;
    if (checkboard() == 2)
    {
        return 100000000000000+depth;
    }
    else if (checkboard() == 1)
    {
        return -100000000000000-depth;
    }
    else if(depth == 0 || checkboard()==3)
        {
        return points();
        }

    else if(isMaximizing)
        {
            long long int finalScore = -INFINITY;
            int finalc;
                for(int c = 0; c<7; c++)
                    {
                    if(arr[c] <6)
                    {
                        int p = insert(AI_player2piece,c);
                        int score = minimax(depth - 1, 0,0);
                        reinsert(c);
                        //printf("%d,%d\n",c,score);
                        if(score > finalScore)
                        {
                            finalScore = score;
                            finalc = c;
                        }

                    }

                   }
            if(firstTime)
            {
            int p = insert(AI_player2piece,finalc);
            }
            return finalScore;
        }


        else
        {
            long long int finalScore = INFINITY;
            int finalc;
                for(int c = 0; c<7; c++)
                {
                    if(arr[c] <6)
                    {
                        int p = insert(player1piece,c);
                        int score = minimax(depth - 1, 1,0);
                        reinsert(c);
                        if(score < finalScore)
                        {
                            finalScore = score;
                            finalc = c;
                        }

                    }

               }
             return finalScore;
        }
}
