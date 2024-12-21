#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h> //getchar
#include <ctype.h>
#include <windows.h>
#include <process.h> //Process is a single header cross-platform library that allows users to launch processes, interact with the stdin, stdout, and stderr of the process, and wait for the process to complete.
//procces.h for example for stdin
#define UP 72 
#define DOWN 80
#define LEFT 75
#define RIGHT 77
 
int choice_menu, length, bend_no, len, life, speed,level;   //introducing the variable that i will use in global so len is for the variable to track the head of the snake
char key;
void record();
void load();
int Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy (int x, int y);
void GotoXY(int x,int y); //function for placement in matrix
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
int speed_pointer();
 
struct coordinate //collection variables for the coordinate
{
    int x;
    int y;
    int direction;
};
 
typedef struct coordinate coordinate; // This function typedef struct is to make the program cleaner because we dont need to write struct a lot of time
 
coordinate head, bend[500],food,body[30];
 
int main()
{
   do
    {
 
        menu();
        system("cls");//to clear the page
    }
    while(choice_menu!=5);
 
}
 
int menu()
{
   {
    puts("=======================");
    puts("||        MENU       ||");
    puts("=======================");
    printf("1)Start\n2)Settings\n3)High Scores\n4)Instruction\n5)Exit\n");
    scanf("%d",&choice_menu);
    fflush(stdin);
    if(choice_menu==1)
    {
        start();
    }
    else if(choice_menu==2)
    {
        speed=speed_pointer();
    }
    else if(choice_menu==3)
    {
        Highscore();
    }
    else if(choice_menu==4)
    {
        Print();
    }
    else if(choice_menu==5)
    {
        exit;
    }
    else
    {
        system("cls");
        menu();
 
    }
    return choice_menu;
}
 
}
int start()
{
    char key;
 
 
    system("cls");
 
    load();
 
    length=5;
 
    head.x=25;
 
    head.y=20;
 
    head.direction=RIGHT;
 
    Boarder();
 
    Food(); //to generate food coordinates initially
 
    life=1; //number of extra lives
 
    bend[0]=head;
 
    Move();   //initialing initial bend coordinate
 
    return 0;
}
void Move()
{
    int a,i;
 
    do
    {
 
        Food();
        fflush(stdin);//to clear the output buffer
 
        len=0;
 
        for(i=0; i<30; i++)
 
        {
 
            body[i].x=0;
 
            body[i].y=0;
 
            if(i==length)
 
                break;
 
        }
 
        Delay(length);
 
        Boarder();
 
        if(head.direction==RIGHT)
 
            Right();
 
        else if(head.direction==LEFT)
 
            Left();
 
        else if(head.direction==DOWN)
 
            Down();
 
        else if(head.direction==UP)
 
            Up();
 
        ExitGame();
 
    }
    while(!kbhit());
 
    a=getch();
 
    if(a==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
    key=getch();
 
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
 
    {
 
        bend_no++;
 
        bend[bend_no]=head;
 
        head.direction=key;
 
        if(key==UP)
 
            head.y--;
 
        if(key==DOWN)
 
            head.y++;
 
        if(key==RIGHT)
 
            head.x++;
 
        if(key==LEFT)
 
            head.x--;
 
        Move();
 
    }
 
    else if(key==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
 
    else
 
    {
 
        printf("\a");
 
        Move();
 
    }
}
 
void gotoxy(int x, int y)   //Basically, it gets a handle you can use to write to the console.
                            //SetConsoleCursorPosition then uses that handle and
                            //the coordinates you specified to place the blinking cursor in your command prompt
{                           //i use this one only for the loading screen which is actually not really important.
 
    COORD coord;
 
    coord.X = x;
 
    coord.Y = y;
 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load()
{
    int row,col,c,r,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
}
 
int speed_pointer ()
{
    system("cls");
    puts("=======================");
    puts("||       SPEED       ||");
    puts("=======================");
    printf("1)Easy\n2)Medium\n3)Hard\n");
    scanf("%d",&level);
    fflush(stdin);
    system("cls");
    if (level==1)
    {
        speed=4000000;
    }
    else if(level==2)
    {
        speed=2000000;
    }
    else if(level==3)
    {
        speed=1;
    }
    else
    {
        printf("\nPlease choose the difficulty!");
        getch();
        system("cls");
        speed_pointer();
        menu();
    }
    return speed;
}
int Delay(long double k) //speed for the snake for difficulty
{
    Score();
    long double i;
    for(i=0; i<=(speed); i++);
}
 
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
                        //so if the value of check is increasing it will terminate the round
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;//starting point for the x of the head
            head.y=20;//starting point for the y of the head
            bend_no=0;//the body become zero again
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            menu();
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
 
            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
 
 
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}
 
 
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
 
}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}
void Print()
{
    //GotoXY(10,12);
 
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Your life will decrease as you hit the wall or snake's body.\n\n-> You can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        {
            exit(0);
        }
        start();
}
void record() //https://data-flair.training/blogs/file-handling-in-c/
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time
 
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
 
 
 
    printf("wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        Highscore();
        system("cls");
        fflush(stdin);
    }
    else
    {
 
    }
}
 
void Highscore()
{
    char c;
    FILE *info; //to introduce a file will be open
    system("cls");
    info=fopen("record.txt","r"); //opening a file and only in reading mode
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
 
        fclose(info);
        getch();
        system("cls");
        menu();
}
 
 
int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}