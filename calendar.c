#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
//#include<windows.h>

int getkey();
void display(int,int,int,int[]);
void calendar(int,int);

//-------------- GOTO function definition ----------------------
void gotoxy(int x,int y)
{
    printf("\033[%d;%dH", y+1, x+1);
}

//------------ Change color -------------------
void SetColor(int ForgC)
{
    printf("\033[%dm",ForgC);
    return;
}


char *month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
char *week[]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

int main()
{
    int nmonth,nyr,ch;
    enteryear:

    
    printf("%s","Enter year:");
    int ret = scanf("%d",&nyr);
    printf("%s","Enter month:");
    ret = scanf("%d", &nmonth);
    
    while(1)
    {
        
        if(nyr<1945)
        {
            //If year less than 1945
            printf("\n\t %s\n","Please enter year above 1945");
            continue;
        }
        else
        {
            //If year greater than equal to 1945
            calendar(nyr,nmonth);
        }
        while(1)
        {
        gotoxy(20,20);printf("(*) Use LEFT, RIGHT, UP and DOWN arrow.");
        gotoxy(20,22);printf("(*) Press P to go to particular year and month.");
        gotoxy(20,24);printf("(*) Press ESC to Exit.");
        ch=getkey();
        switch(ch)
        {
        case 66: //-------- DOWN ARROW -----------
               //Increasing month
                if(nmonth==12)
                {
                    //Jump to next year if month is december
                     nmonth=1;
                     nyr++;
                }
                else
                {
                    nmonth++;
                }
                calendar(nyr,nmonth);
                break;
        case 67: //-------- RIGHT ARROW ----------
            //Increasing Year
                nyr++;
                calendar(nyr,nmonth);
                break;
        case 65: //------- UP ARROW -------------
            // Decreasing Month
                if(nmonth==1)
                {
                    // Jump to previous year if month is january
                    nyr--;
                    nmonth=12;
                }
                else
                    nmonth--;
                calendar(nyr,nmonth);
                break;
        case 68: //-------- LEFT ARROW ----------
            //Decreasing year
                if(nyr==1945)
                {
                    //If year is 1945 and we click left arrow than
                  gotoxy(15,2);printf("Year below 1945 not available");
                }
                else
                {
                    nyr--;
                    calendar(nyr,nmonth);
                }

                break;
        case 27: //--------- ESC KEY ------------
            //Exit program
                system("clear");
                gotoxy(50,14);printf("Exiting program.\n\n\n\n\n");
                //
                exit(0);
        case 112://---------- p KEY ------------
            //Go to particular year and month
            system("clear");
            
            //system("stty -raw echo");
            goto enteryear;
        }
        }
        break;

    }
    getchar();
    return 0;
}


//============== DISPLAYING THE  CALENDAR ===================
void display(int nyr,int nmonth,int tdays,int days[])
{
    int i,j,pos;
    SetColor(31); //Color red
    gotoxy(56,6);printf("%s %d",month[nmonth-1],nyr); //Heading year and month dispalying
    for(i=0,pos=30;i<7;i++,pos+=10)
    {
         if(i==6)
            SetColor(34); //Sunday color blue
         else
            SetColor(32);  //Others day color green
        gotoxy(pos,8);printf("%s",week[i]);
    }

    SetColor(37); //setting the color white

   tdays++; //incrementing the tdays by 1
    if(tdays==0 || tdays==7)
        pos=91; //if tdays is 0 or 7, position is sunday
    if(tdays==1)
        pos=31; //if tdays is 1, position is monday
    if(tdays==2)
        pos=41;  //if tdays is 2, position is tuesday
    if(tdays==3)
        pos=51;  //if tdays is 3, position is wednesday
    if(tdays==4)
        pos=61;  //if tdays is 4, position is thursday
    if(tdays==5)
        pos=71;  //if tdays is 5, position is friday
    if(tdays==6)
        pos=81;  //if tdays is 6, position is saturday

    for(i=0,j=10,pos;i<days[nmonth-1];i++,pos+=10)
    {
        if(pos==91)
            SetColor(36); //Changing color to cyan for sunday
        else
            SetColor(37); //Changing color to white for all days

        gotoxy(pos,j);printf("%d",i+1);
        if(pos==91)
        {
            pos=21; //Moving position to monday
            j++;  //Increasing j by 10 if position is sunday
        }
    }

    SetColor(35); //Changing color to purple

    //Drawing horizontal line
    for(i=22;i<102;i++)
    {
        gotoxy(i,4);printf("%s","─");
        gotoxy(i,17);printf("%s","─");
    }

    //Drawing all the corner of the rectangle
    gotoxy(21,4);printf("%s","┌");
    gotoxy(102,4);printf("%s","┐");
    gotoxy(21,17);printf("%s","└");
    gotoxy(102,17);printf("%s","┘");

    //Drawing vertical line
    for(i=5;i<17;i++)
    {
        gotoxy(21,i);printf("%s","│");
        gotoxy(102,i);printf("%s","│");
    }

    SetColor(33); //Changing color to yellow

    //Drawing left and the right navigation symbol
    gotoxy(24,11);printf("%s","⏪");
    gotoxy(98,11);printf("%s","⏩");

}


int getch(void)    {

        int c;

        c = getchar();

        if (c == 27) {
            c = getchar();
            c = getchar();
        }

        return c;

}

//==============  ARROW KEY ===============
int getkey()
{
    int ch;
    system("stty raw -echo");
    ch = getch();
    system("stty -raw echo");
    return ch;
}

//============ Calculating ====================
void calendar(int nyr,int nmonth)
{
    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int tdays=0,k,myear;
    system("tput reset");
    myear=nyr-1; //Decreasing year by 1
            if(myear>=1945)
            {
                for(k=1945;k<=myear;k++)
                {
                    if(k%4==0) //If the year is a leap year than total no of days is 366
                        tdays=tdays+366;  //counting all the days till nyr - 1
                    else //If the year is a leap year than total no of days is 365
                        tdays=tdays+365;  //counting all the days till nyr - 1
                }
            }

            if(nyr%4==0)
                days[1]=29; //changing value in days array from 28 to 29 since leap year
            else
                days[1]=28; //changing value in days array from 29 to 28 since not a leap year

            for(k=0;k<(nmonth-1);k++)
            {

                tdays=tdays+days[k]; //Adding nmonth-1 days to tdays
            }

            tdays=tdays%7; //Finding the remainder of tdays so it can calculate the position to display
            display(nyr,nmonth,tdays,days); //Passing the value to display
}
