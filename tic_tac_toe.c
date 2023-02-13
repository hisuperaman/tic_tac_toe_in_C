//Author - @github theaman05

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int gameover;
int value[3][3];
char val_sign[2] = {'X', 'O'};
char p1_name[10], p2_name[10];

struct num_sign
{
    char player1;
    char player2;
}num, sign;

void setup(char action);

int intro()
{
    char action;
    gameover = 0;
    system("cls");
    printf("Welcome to Tic Tac Toe!\n");
    printf("Rules\n");
    printf("1. Player will be asked to choose a sign [O or X] \n");
    printf("2. Player will enter number from 1 to 9 to fill the board with their respective sign\n");
    printf("Type\n");
    printf("1 to start\n");
    printf("2 for leaderboard\n");
    printf("3 to exit\n");
    action = getch();
    system("cls");
    setup(action);
}

void start()
{
    printf("Enter name\n");
    printf("Player1: ");
    scanf("%s", p1_name);
    printf("Player2: ");
    scanf("%s", p2_name);

    printf("%s Enter your sign[x/o]\n", p1_name);
    sign.player1 = getch();
    while(sign.player1!='O' && sign.player1!='X')
    {
        if(sign.player1=='o' || sign.player1=='x')
        {
            sign.player1 -= 32;
            break;
        }
        else
        {
            printf("Enter valid input[x/o]\n");
            sign.player1 = getch();
        }
    }

    for(int z=0; z<2; z++)
    {
        if(val_sign[z]!=sign.player1)
        {
            sign.player2 = val_sign[z];
        }
    }
}

void init_board()
{
    int k=49;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            value[i][j] = k;
            k++;
        }
    }
}

void setup(char action)
{
    FILE *fp;
    int asking = 1;
    char ch;
    char ask;
    switch(action)
    {
        case '1':
            start();
            break;
        case '2':
            fp = fopen("leaderboard.txt", "r");
            if(fp==NULL)
            {
                printf("No record found\n");
            }
            else
            {
                printf("Player1 \t Player2 \t Winner\n");
                while(!feof(fp))
                {
                    ch = fgetc(fp);
                    printf("%c", ch);
                }
            }
            fclose(fp);

            while(asking)
            {
                printf("\n\nPress\n1 to go back\n2 to clear leaderboard\n3 to exit\n");
                ask = getch();
                if(ask=='1')
                {
                    intro();
                    asking = 0;
                }
                else if(ask=='2')
                {
                    fp = fopen("leaderboard.txt", "w");
                    fclose(fp);
                    printf("Cleared successfully!\nPress any key to continue");
                    getch();
                    intro();
                    asking = 0;
                }
                else if(ask=='3')
                {
                    exit(0);
                }
                else
                {
                    system("cls");
                    printf("Enter valid input");
                }
            }
            break;
        case '3':
            exit(0);
        default:
            printf("Please enter valid input\nPress any key to continue");
            getch();
            intro();
    }
}

void draw()
{
    system("cls");
    printf("\tTic Tac Toe\n");
    printf("%c | %c | %c \n", value[0][0], value[0][1], value[0][2]);
    printf("--|---|--\n");
    printf("%c | %c | %c \n", value[1][0], value[1][1], value[1][2]);
    printf("--|---|--\n");
    printf("%c | %c | %c \n", value[2][0], value[2][1], value[2][2]);
    printf("\n\n%s--> %c \t %s--> %c\n\n", p1_name, sign.player1, p2_name, sign.player2);
}

void op(char n, char n2, char sign_p1, char sign_p2, int *p)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(value[i][j]==n)
            {
                value[i][j] = sign_p1;
                *p+=1;
            }
            else if(value[i][j]==n2)
            {
                value[i][j] = sign_p2;
                *p+=1;
            }
        }
    }
}

void input(int p)
{
    num.player1 = 0;
    num.player2 = 0;
    if(p==1)
    {
        printf("%s\n", p1_name);
        num.player1 = getch();
    }
    else
    {
        printf("%s\n", p2_name);
        num.player2 = getch();
    }
}

int logic()
{
    int p1_row=0, p2_row=0, p1_col=0, p2_col=0, res, i, j;
    int p1_diag=0, p2_diag=0, p1_diag1=0, p2_diag1=0;
    int filled;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(value[i][j]=='X'||value[i][j]=='O')
            {
                (value[i][j]==sign.player1)?(p1_row++):(p2_row++);
                if(p1_row==3 || p2_row==3)
                {
                    gameover = 1;
                    (p1_row==3)?(res = 1):(res = 2);
                }
            }
        }
        p1_row = 0;
        p2_row = 0;
    }

    for(j=0; j<3; j++)
    {
        for(i=0; i<3; i++)
        {
            if(value[i][j]=='X'||value[i][j]=='O')
            {
                (value[i][j]==sign.player1)?(p1_col++):(p2_col++);
                if(p1_col==3 || p2_col==3)
                {
                    gameover = 1;
                    (p1_col==3)?(res = 1):(res = 2);
                }
            }
        }
        p1_col = 0;
        p2_col = 0;
    }

    filled = 0;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(value[i][j]=='X'||value[i][j]=='O')
            {
                filled+=1;
            }
        }
    }
    if(filled==9)
    {
        gameover = 1;
        res = 0;
    }

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            if(i==j && (value[i][j]=='X'||value[i][j]=='O'))
            {
                (value[i][j]==sign.player1)?(p1_diag++):(p2_diag++);
                if(p1_diag==3||p2_diag==3)
                {
                    gameover = 1;
                    (p1_diag==3)?(res=1):(res=2);
                }
            }
        }
    }

    int k=2;
    for(i=0; i<3; i++)
    {
        if(value[i][k]=='X'||value[i][k]=='O')
        {
            (value[i][k]==sign.player1)?(p1_diag1++):(p2_diag1++);
            if(p1_diag1==3||p2_diag1==3)
            {
                gameover = 1;
                (p1_diag1==3)?(res=1):(res=2);
            }
        }
        k--;
    }

    return res;
}

void main()
{
    int p, result, replay=1;
    char ask, again;
    FILE *fp;

    intro();
    while(replay)
    {
        p=1;
        init_board();
        while(!gameover)
        {
            if(p>2){p=1;}

            draw();
            input(p);
            op(num.player1, num.player2, sign.player1, sign.player2, &p);
            result = logic();
        }
        draw();

        fp = fopen("leaderboard.txt", "a");
        fprintf(fp, "%s \t\t %s \t\t", p1_name, p2_name);

        if(result==1)
        {
            printf("%s wins!\n", p1_name);
            fprintf(fp, " %s\n", p1_name);
        }
        else if(result==2)
        {
            printf("%s wins!\n", p2_name);
            fprintf(fp, " %s\n", p2_name);
        }
        else
        {
            printf("Draw!\n");
            fprintf(fp, " Draw\n");
        }
        fclose(fp);

        printf("Press 1 to replay else press any key to continue\n");
        ask = getch();
        (ask=='1')?(replay=1, gameover=0):(replay=0);
    }
    while(1)
    {
        printf("\nPress\n1 to go to main menu\n2 to exit\n");
        again = getch();
        if(again=='1'){main();}
        else if(again=='2'){break;}
        else
        {
            printf("Enter valid input\n");
            continue;
        }
        getch();
    }
}