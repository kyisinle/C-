#include<iostream>
#include<graphics.h> //for gotoxy()
#include<conio.h> //for getche()
#include<dos.h> //for kbhit(), delay()
#include<stdlib.h> //for rand()
using namespace std;

COORD coord={0,0};
void gotoxy(int x,int y)
 {
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

void enemy(int x, int y)
 {
  setcolor(15);
  rectangle(x+1,y+75,x+49,y+100);
  setfillstyle(SOLID_FILL,YELLOW);
  floodfill((x+x+50)/2,(y+75+y+100)/2,15);
 }

void mycar(int x, int y)
 {
  setcolor(15);
  rectangle(x+1,y,x+49,y+100);
  rectangle(x+1,y+25,x+49,y+75);
  setfillstyle(5,RED); //middle block
  floodfill((x+x+50)/2,(y+y+100)/2,15);
  setfillstyle(SOLID_FILL,BLACK); //
  floodfill((x+x+50)/2,(y+y+40)/2,15);
  floodfill((x+x+50)/2,(y+y+160)/2,15);
 }

void myclear(int x,int y)
 {
 setcolor(8);
 rectangle(x+1,y,x+49,y+100);
 rectangle(x+1,y+25,x+49,y+75);
 setfillstyle(SOLID_FILL,8);
 floodfill((x+x+50)/2,(y+y+100)/2,8);
 floodfill((x+x+50)/2,(y+y+40)/2,8);
 floodfill((x+x+50)/2,(y+y+160)/2,8);
 }

 void enemyclear(int x,int y)
 {
 setcolor(8);
 rectangle(x+1,y+75,x+49,y+100);
 setfillstyle(SOLID_FILL,8);
 floodfill((x+x+50)/2,(y+75+y+100)/2,8);
 }

int main()
 {
 int gdriver = DETECT,gmode;
 initgraph(&gdriver,&gmode,"C:\\TC\\BGI");

  int x=300,y=350,ch,life=3,score=0,counter=0;
  gotoxy(90,2);
  cout<<"Welcome to Block Racer!";
  gotoxy(90,3);
  cout<<"Version 1.0.0.0";
  gotoxy(90,22);
  cout<<"Developed by";
  gotoxy(90,23);
  cout<<"Batch 9";
  gotoxy(90,24);
  cout<<"UIT 1st Year 2nd Sem";
  gotoxy(90,25);
  cout<<"Section (C)";
  gotoxy(90,26);
  cout<<"Group II students";
  gotoxy(90,27);
  cout<<"2023 All rights reserved";
  delay(3000);
  gotoxy(90,2);
  cout<<"                                       ";
  gotoxy(90,3);
  cout<<"                                       ";

  setcolor(RED);
  rectangle(249,0,401,getmaxy()); //road //getmaxy() means maximum y coordinate
  setfillstyle(SOLID_FILL,8);
  floodfill(325,getmaxy()/2,RED);

  for(int level=1;(level<=5)&&(life>0);level++){
    if(level==1){
      gotoxy(90,2);
      cout<<"Your Race Will Begin";
      gotoxy(90,3);
      cout<<"in 3 Seconds";
      gotoxy(90,5);
      cout<<"All The Best!";
      delay(3000);
      gotoxy(90,2);
      cout<<"                                 "; //replaces the text at this coordinate with empty space
      gotoxy(90,3);
      cout<<"                                 ";
      gotoxy(90,5);
      cout<<"                ";
      }

  for(int i=0;(i<10)&&(life>0);i++) {

    int accident=0;

       gotoxy(90,5);
       cout<<"Level = "<<level;

       gotoxy(90,9);
       cout<<"Lives = "<<life;

       gotoxy(90,13);
       cout<<"Score = "<<score;

       gotoxy(90,17);
       cout<<"Obstacles Passed = "<<counter;

    int y1=-1,x1=250+((rand()%3)*50); //generate obstacles
    int y2=-1,x2=250+((rand()%3)*50);
    score+= 10;

    while(y1<getmaxy()-1) //range for obstacle movement
    {

        enemyclear(x1,y1);
        enemyclear(x2,y2);
        y1++; //move obstacle downward
        y2++; //move obstacle downward
        if(accident == 1)
        break;

        enemy(x1,y1);
        enemy(x2,y2);
        mycar(x,y);
        delay(3.75-(level*0.75)); //speed up car with level
        if(kbhit()) //arrow keys movement
        {
            mycar(x,y);
            ch=getch();
            switch(ch) {

            case 27: exit(0);
            break;

            case 75:myclear(x,y); //left
                if(x>250)
                    x=x-50;
                    if((x==x1)||(x==x2))
                        if( ( ((y-y1)<100)&&((y-y1)>0) ) || ( ((y-y2)<100)&&((y-y2)>0) ) )
                        {
                            accident=1;
                            x=x+50;
                            mycar(x,y);
                            goto Next1;
                        }
                 mycar(x,y);
                 break;
            case 77:myclear(x,y); //right
                if(x<350)
                    x=x+50;
                    if((x==x1)||(x==x2))
                        if( ( ((y-y1)<100)&&((y-y1)>0) ) || ( ((y-y2)<100)&&((y-y2)>0) ) )
                        {
                            accident=1;
                            x=x-50;
                            mycar(x,y);
                            goto Next1;
                        }
                mycar(x,y);
                break;
            case 72:myclear(x,y); //up
                if(y>100)
                      y=y-5;
                mycar(x,y);
             break;
             case 80:myclear(x,y); //down
                if(y<getmaxy()-105)
                    y=y+5;
                mycar(x,y);
                break;
            }
        }
        if((x==x1)||(x==x2)) //hit
            if( ( ((y-y1)<100)&&((y-y1)>0) ) || ( ((y-y2)<100)&&((y-y2)>0) )|| ((y1-y)<25 && (y1-y)>0) || ((y2-y)<25 && (y2-y)>0) )
                accident=1;

                Next1:
      if(accident==1){
        life =life-1;
        score -= 10;

        if(life==0) {
         gotoxy(90,2);
         cout<<"GAME OVER :(";
         gotoxy(90,3);
         cout<<"Maybe Next Time... ";
         break;
         }

        gotoxy(90,2);
        cout<<"You have lost 1 life!";
        delay(500);
        gotoxy(90,2);
        cout<<"                     ";
        }
    }
        counter++;

        gotoxy(90,5); //overwrite previous assignment expression so score and counter matches messages displayed
        cout<<"Level = "<<level;

        gotoxy(90,9);
        cout<<"Lives = "<<life;

        gotoxy(90,13);
        cout<<"Score = "<<score;

        gotoxy(90,17);
        cout<<"Obstacles Passed = "<<counter;

        if((counter!=0)&&(counter!=50)&&(counter%10==0)){
         gotoxy(90,2);
         cout<<"Next level!";
         delay(500);
         gotoxy(90,2);
         cout<<"           ";
         }

        else if((level==5)&&(counter==50)){
            gotoxy(90,1);
            cout<<"Congratulations!";
            gotoxy(90,2);
            cout<<"You Have Won :)";
        }
  }
}
}

