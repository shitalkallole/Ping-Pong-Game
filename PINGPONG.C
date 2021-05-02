#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<stdlib.h>//for random
//function declaration
//keyword with first used for calling its first type
void call_left_bound_first();
void call_lower_bound_first();
void call_right_bound_first();
void call_upper_bound_first();
//keyword with second used for calling its second type
void call_left_bound_second();
void call_lower_bound_second();
void call_right_bound_second();
void call_upper_bound_second();
//initial make rectangles
void createFile();//used to create file
void keyboardHit();//any keyboard event
int animationStart();//describe animation
void showBallRac();//show the ball and racket
void basicInitialization();//to assign memory of all images
void initial();//initialy make all rectangles
void changeDia(); //to change the rectangle of above given
void homePage();//to show sk01 presents
void secondPage();//to show game info
int thirdPage();//to show menus
void thirdPageLine();//prints line
void thirdPageSelectColor();//select color for menus change accordingly
void printrecmenuLeft();//print left rec in menu
void printrecmenuRight();//print right rec in menu
void thirdPrint();//prints the menus  and changes accordingly
void helpMenu();//show help menu
void highscoreMenu();//show high score
void partOfMain();
void initializationV();
void writeDataOnFile(char*);
void minValueFile();
//global variable declaration
//flag used for globally checking which among four type called
//dir used to call first or second in its type
//x1,y1,x2,y2 denote the (left,upper) and (right,lower) coordinates of ball
//left_bound , right_bound, lower_bound,upper_bound denote the wall coordinate
//x1_before,x1_after,y1_before,y1_after used to check which direction to pass the ball
//inc is to increment the ball ,incrac for racket increment,delay_time is the delay_time
int checkelse,flag,dir;
int x1,x2,y1,y2;
int left_bound,right_bound,lower_bound,upper_bound;
int x1_before,x1_after,y1_before,y1_after;
int racket_x1,racket_y1,racket_x2,racket_y2;
int inc,delay_time,incrac,over;
//make initial rec var
int make_x1,make_x2,make_y1,make_y2;
int color,color1,detectvalue,beforered;
void *buf,*buf1,*upperrecwhite,*upperrecblack,*racketblack,*racketyellow,*clearprinted;

int score;
int ball_x1,ball_x2,ball_y1,ball_y2,doit=0;
int highScore=1;
char globalName[6];
FILE *scoreFile;
void main() //start of main()
{
	int gdriver,gmode;

	gdriver=DETECT;
	initgraph(&gdriver,&gmode,"\\turboC3\\BGI");

	cleardevice(); //clear graphics
	initializationV();//basic initialization
	createFile();//this will create file if not exist and get the max score
	homePage();//to show sk01 presents
	secondPage();//to show information about game (animation)
	partOfMain();//all the game code
	cleardevice();
	getch();
	closegraph();

}   //end of main
void partOfMain()
{
	int menuSelected,storeScore=0,temp=0;
	char name[6];
	while(1)
	{
		menuSelected=thirdPage();//show menus
		if(menuSelected==1)
		{
			cleardevice();
			basicInitialization();//Call this function for making memory for all pointer or to storing images or for initialzation

			setbkcolor(0);
			setcolor(15);
			settextstyle(0,0,1);
			outtextxy(6,1,"Score:");  //show the text Score

			while(1)   //start of while loop
			{
				showBallRac();//shows ball and racket

				gotoxy(8,1);//show score
				printf("%d",score);//end of displaying score

				keyboardHit();//any keyboard event
				storeScore=animationStart();//to do animation which return 0 or 1 (1=the game is over and the the score is checked to whether it should be stored or not)
				if(score==78)
				{
					settextstyle(1,0,6);
					setcolor(14);
					outtextxy(100,100,"You Win The Game");
					delay(1500);
					storeScore=1;
				}
			       if(storeScore)  //storeScore=1 if the game is over
			       {
				       minValueFile();
				       if(score>=highScore) //highscore contain the min score
					{
						//this code to store the score of player in file
						cleardevice();
						setcolor(15);
						thirdPageLine();
						settextstyle(1,0,3);
						setcolor(14);
						outtextxy(200,195,"Enter Your Name:  ");
						setcolor(15);
						rectangle(415,205,465,225);
						gotoxy(53,14);
						scanf("%s",name);
						name[5]='\0';
						writeDataOnFile(name);
						cleardevice();
					}
				}
				if(storeScore)
				{
					initializationV(); //reinitialize all();
					storeScore=0;
					break;//to display the menu to user we have to break from this current loop
				}
			} //end of while loop(game execution)
		}
		else if(menuSelected==2)//if High Score menu is selected
		{
			cleardevice();
			highscoreMenu();
			getch();
		}
		else if(menuSelected==3)//if help menu is selected
		{
			cleardevice();
			helpMenu();
			getch();
		}
		else if(menuSelected==4)//if user want to exit
			exit(0);
		cleardevice();
	}//end of while loop(Menus display)
}
void initializationV()
{
	 int temp1;
	 FILE *tempFile;//to store the temporary value genrated randomly

	 checkelse=1,flag=0,dir=0;
	 x1=50,x2=60,y1=140,y2=150;
	 left_bound=10,right_bound=620,lower_bound=435,upper_bound=119;
	 x1_before=0,x1_after=0,y1_before=0,y1_after=0;
	 racket_x1=270,racket_y1=450,racket_x2=340,racket_y2=460;
	 inc=10,delay_time=100,incrac=20,over=0	;
	//make initial rec var
	 make_x1=10,make_x2=55,make_y1=25,make_y2=39;
	 color=0,color1=0,detectvalue=0,beforered=0;
	 score=0;
	//genrate temporary value and assign it to x1 of ball
	//for the purpose of changing values of ball
	tempFile=fopen("rand.txt","r"); //file open in read mode
	if(tempFile!=NULL)
	{
		fscanf(tempFile,"%d",&temp1);
		if(temp1<=500)
			;
		else
			temp1=40;

		temp1=temp1+50;

		x1=x1+temp1;
		x2=x1+10;

		fclose(tempFile);

		tempFile=fopen("rand.txt","w");
		fprintf(tempFile,"%d",temp1);
	}
	else
	{
		tempFile=fopen("rand.txt","w");
		temp1=10;
		fprintf(tempFile,"%d",temp1);

		x1=x1+temp1;
		x2=x1+10;
	}
	fclose(tempFile);
	//end
}
void createFile()
{
	scoreFile=fopen("score.txt","r"); //check that file is present or not
	if(scoreFile==NULL)//if file not present then create
	{
		scoreFile=fopen("score.txt","w");
		highScore=1;
	}
	fclose(scoreFile);
}
void minValueFile()
{
	int count=0,tempdata,min,i;
	char tempname[6];
	FILE *called;
	scoreFile=fopen("score.txt","r");
	while(!feof(scoreFile))
	{
		fscanf(scoreFile,"%s %d",&tempname[0],&tempdata);
		count++;
	}
	fclose(scoreFile);
	if(count>=3)//if there are already 3 players score is stored then to store fourth we have to delete the rcord of player which has min score
	{
		scoreFile=fopen("score.txt","r");
		fscanf(scoreFile,"%s %d",&tempname[0],&tempdata);
		min=tempdata;
		fclose(scoreFile);

		scoreFile=fopen("score.txt","r");
		for(i=0;i<3;i++)
		{
			fscanf(scoreFile,"%s %d",&tempname[0],&tempdata);
			if(tempdata<=min)
			{
				min=tempdata;
				strcpy(globalName,tempname);
			}

		}
		highScore=min;
		called=fopen("called.txt","w");
		fprintf(called,"%s %d",globalName,highScore);
		fclose(called);
	}
	else
		highScore=1;
}
void writeDataOnFile(char *name)
{
	int count=0,i;
	int tempdata;
	char tempname[6];
	FILE *tempfile;
	scoreFile=fopen("score.txt","r");

	while(!feof(scoreFile))
	{
		fscanf(scoreFile,"%s %d",&tempname,&tempdata);
		count++;        //count the no of elements into the file;
	}
	fclose(scoreFile);
	count--;
	if(count<2)//if there are two or less no of player score present then store third as it is
	{
		scoreFile=fopen("score.txt","a");
		fprintf(scoreFile,"%s %d",name,score);
		fclose(scoreFile);
	}
	else//else delete the record of player who has less score and update
	{       tempfile=fopen("tempscore.txt","w");
		scoreFile=fopen("score.txt","r");
		for(i=0;i<3;i++)
		{
		       fscanf(scoreFile,"%s %d",&tempname,&tempdata);
		       if((tempdata==highScore) && (strcmp(globalName,tempname)==0))
				;
		       else
				fprintf(tempfile,"%s %d",tempname,tempdata);
		}
		fprintf(tempfile,"%s %d",name,score);
		fclose(tempfile);
		fclose(scoreFile);

		remove("score.txt");
		rename("tempscore.txt","score.txt");
	}
}
//-------------start of High score Menu()-----------
void highscoreMenu()
{
	int tempdata=0,count=0,i=0,j=0,temp,baseindex[3];
	char tempname[6],*sortname[3],temporary[6];
	FILE *tempFile;
	scoreFile=fopen("score.txt","r");

	fscanf(scoreFile,"%s %d",&tempname,&tempdata);
	fclose(scoreFile);

	thirdPageLine();
	setcolor(14);

	if(tempdata!=0)//if there is data present to display
	{
		scoreFile=fopen("score.txt","r");
		while(!feof(scoreFile))
		{
			fscanf(scoreFile,"%s %d",&tempname,&tempdata);
			count++;
		}//count give the no of records in file
		fclose(scoreFile);

		scoreFile=fopen("score.txt","r");
		while(!feof(scoreFile))
		{
			fscanf(scoreFile,"%s %d",&tempname,&tempdata);
			baseindex[i]=tempdata;
			sortname[i]=(char *)malloc(sizeof(char)*4);
			strcpy(sortname[i],tempname);
			i++;
		}
		fclose(scoreFile);

		settextstyle(1,0,6);
		outtextxy(130,30,"Top 3# Players");
		line(190,180,190,360);
		line(190,360,460,360);
		line(460,180,460,360);
		line(190,180,460,180);

		line(325,180,325,360);//for center one line

		line(190,240,460,240); //for first row
		line(190,280,460,280); //for second row
		line(190,320,460,320); //for third row
		setcolor(5);
		settextstyle(1,0,3);
		outtextxy(230,190,"Name");
		outtextxy(365,190,"Score");
		switch(count)
		{
			case 1: //if only one record present
				gotoxy(30,17);
				printf("%s",sortname[0]);
				gotoxy(49,17);
				printf("%d",baseindex[0]);
				break;
			case 2: //if two record present
				if(baseindex[0]>=baseindex[1])
				{
					gotoxy(30,17);
					printf("%s",sortname[0]);
					gotoxy(49,17);
					printf("%d",baseindex[0]);
					gotoxy(30,20);
					printf("%s",sortname[1]);
					gotoxy(49,20);
					printf("%d",baseindex[1]);

				}
				else
				{       gotoxy(30,17);
					printf("%s",sortname[1]);
					gotoxy(49,17);
					printf("%d",baseindex[1]);
					gotoxy(30,20);
					printf("%s",sortname[0]);
					gotoxy(49,20);
					printf("%d",baseindex[0]);

				}
				break;
			case 3://if three record present sort using bubble sort
					for(i=0;i<2;i++)
					{
						for(j=0;j<3-1-i;j++)
						{
							if(baseindex[j]<baseindex[j+1])
							{
								temp=baseindex[j];
								baseindex[j]=baseindex[j+1];
								baseindex[j+1]=temp;
								strcpy(temporary,sortname[j]);
								strcpy(sortname[j],sortname[j+1]);
								strcpy(sortname[j+1],temporary);
							}
						}
					}
					gotoxy(30,17);
					printf("%s",sortname[0]);
					gotoxy(49,17);
					printf("%d",baseindex[0]);
					gotoxy(30,20);
					printf("%s",sortname[1]);
					gotoxy(49,20);
					printf("%d",baseindex[1]);
					gotoxy(30,22);
					printf("%s",sortname[2]);
					gotoxy(49,22);
					printf("%d",baseindex[2]);
					break;
		}
	}
	else
	       outtextxy(100,190,"There is no data to display");
	free(sortname);

}
//-------------End of High score Menu()-----------
//-------------start of helpMenu()-----------------
void helpMenu()
{
	thirdPageLine();
	setcolor(4);
	settextstyle(1,0,6);
	outtextxy(10,30,"Game Tips");
	setcolor(7);
	settextstyle(1,0,1);
	outtextxy(20,150,"-Press P to pause game any time and Type any key to");
	outtextxy(30,170,"resume game.");
	outtextxy(20,190,"-Press Esc Key to exit from the game.");
	outtextxy(20,210,"-Use Arrow Keys to Move the racket.");
	outtextxy(20,230,"-The speed of ball is increased as you proceed.");
	outtextxy(400,400,"Enter any key to exit");
	setcolor(14);
	settextstyle(1,0,8);
	outtextxy(20,300,"All The Best");
}
//----------------------end of helpMenu()-----------
//----------------------start of homePage()------------
void homePage()
{
	short i;

	for(i=1;i<4;i++)
	{
		setbkcolor(9);
		setcolor(15);
		line(5,20,5,465);//first line
		line(5,465,630,465);//second line
		line(630,465,630,20);//third line
		line(5,20,630,20);//fourth line
		setcolor(4);
		setfillstyle(SOLID_FILL,4);
		rectangle(242-(31*i),200-(5*i),352+(31*i),230+(5*i));
		floodfill(243-(31*i),201-(5*i),4);
		setcolor(0);
		settextstyle(1,0,3+(i-1));
		outtextxy(244-(31*i),210-(10*i),"SK01 Presents");
		delay(1500);
		cleardevice();
	}
	cleardevice();
}
//---------------------end os homePage()---------------
//---------------------start of secondPage()------------
void secondPage()
{
	short x1,y1,x2,y2,casev=2;
	setbkcolor(9);
	settextstyle(4,0,9);
	setcolor(4);
	outtextxy(11,15,"Ping-Pong");
	settextstyle(10,0,5);
	outtextxy(420,120,"GAME");
	setcolor(15);
	line(5,20,5,465);//first line
	line(5,465,630,465);//second line
	line(630,465,630,20);//third line
	line(5,20,630,20);//fourth line
	setcolor(14);
	line(10,350,625,350);
	line(10,402,625,402);
	x1=15;
	y1=351;
	x2=25;
	y2=361;
	while(1)
	{
		setcolor(4);
		setfillstyle(SOLID_FILL,4);
		rectangle(x1,y1,x2,y2);
		floodfill(x1+1,y1+1,4);
		if(y2>=401)
		{
			x1=x1+10;
			y1=y1-10;
			x2=x2+10;
			y2=y2-10;
			casev=1;
		}
		else if(x2>=620)
			break;
		else if(y1<=351)
		{

			x1=x1+10;
			y1=y1+10;
			x2=x2+10;
			y2=y2+10;
			casev=2;
		}
		else
		{
			if(casev==1)
			{
				x1=x1+10;
				y1=y1-10;
				x2=x2+10;
				y2=y2-10;
			}
			else
			{
				x1=x1+10;
				y1=y1+10;
				x2=x2+10;
				y2=y2+10;
			}

		}
		delay(100);
		setcolor(9);
		setfillstyle(SOLID_FILL,9);
		if(casev==1)
		{
			rectangle(x1-10,y1+10,x2-10,y2+10);
			floodfill(x1-9,y1+11,9);
		}
		else
		{
			rectangle(x1-10,y1-10,x2-10,y2-10);
			floodfill(x1-9,y1-9,9);
		}
	}
	cleardevice();
}
//---------------------end of secondPage()--------------
//-------------------------start of thirdPage()----------
int thirdPage()//this displays the menus
{
	char ch1,ch2;
	short select=1;
	setcolor(15);
	thirdPageLine();
	thirdPageSelectColor(4);

	thirdPrint(240,140,"Start Game");
	printrecmenuLeft(225,160);
	printrecmenuRight(435,160);
	thirdPageSelectColor(7);
	thirdPrint(240,190,"High Scores");
	thirdPrint(295,240,"Help");
	thirdPrint(295,290,"Exit");
	while(1)
	{
	ch1=getch();
	if(ch1==0)
	{
		ch2=getch();
		switch(ch2)
		{
			case 72:
				if(select!=1)
				{

				       select--;
				       if(select==1)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);
						thirdPrint(240,140,"Start Game");
						printrecmenuLeft(225,160);
						printrecmenuRight(435,160);
						thirdPageSelectColor(7);
						thirdPrint(240,190,"High Scores");
						thirdPrint(295,240,"Help");
						thirdPrint(295,290,"Exit");
				       }
				       else if(select==2)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);

						thirdPrint(240,190,"High Scores");
						printrecmenuLeft(225,210);
						printrecmenuRight(435,210);
						thirdPageSelectColor(7);
						thirdPrint(240,140,"Start Game");
						thirdPrint(295,240,"Help");
						thirdPrint(295,290,"Exit");

				       }
				       else if(select==3)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);

						thirdPrint(295,240,"Help");
						printrecmenuLeft(225,260);
						printrecmenuRight(435,260);
						thirdPageSelectColor(7);
						thirdPrint(240,140,"Start Game");
						thirdPrint(240,190,"High Scores");
						thirdPrint(295,290,"Exit");

				       }


				}
				break;
			case 80:
				if(select!=4)
				{
				       select++;
				       if(select==2)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);

						thirdPrint(240,190,"High Scores");
						printrecmenuLeft(225,210);
						printrecmenuRight(435,210);
						thirdPageSelectColor(7);
						thirdPrint(240,140,"Start Game");
						thirdPrint(295,240,"Help");
						thirdPrint(295,290,"Exit");

				       }
				       else if(select==3)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);

						thirdPrint(295,240,"Help");
						printrecmenuLeft(225,260);
						printrecmenuRight(435,260);
						thirdPageSelectColor(7);
						thirdPrint(240,140,"Start Game");
						thirdPrint(240,190,"High Scores");
						thirdPrint(295,290,"Exit");

				       }
				       else if(select==4)
				       {
						cleardevice();
						thirdPageLine();
						thirdPageSelectColor(4);

						thirdPrint(295,290,"Exit");
						printrecmenuLeft(225,310);
						printrecmenuRight(435,310);
						thirdPageSelectColor(7);
						thirdPrint(240,140,"Start Game");
						thirdPrint(240,190,"High Scores");
						thirdPrint(295,240,"Help");


				       }

				}
			break;
		}
	}
	else if(ch1==13)
	{
		switch(select)
		{
			case 1:
				return(1);

			case 2:
				return(2);

			case 3:
				return(3);

			case 4:
				exit(0);
	      }
	}
     }
}
void thirdPageLine()
{
	setbkcolor(9);
	line(5,20,5,465);//first line
	line(5,465,630,465);//second line
	line(630,465,630,20);//third line
	line(5,20,630,20);//fourth line
	settextstyle(1,0,4);
}
void thirdPrint(int x,int y,char *ptr)
{
	outtextxy(x,y,ptr);
}
void thirdPageSelectColor(int c)
{
	setcolor(c);
}
void printrecmenuLeft(int x,int y)
{
    short i,j,k=4;
    for(i=x;i>x-5;i--)
    {
	for(j=y-k;j<=y+k;j++)
	{
	      putpixel(i,j,4);
	}
	k--;
    }
}
void printrecmenuRight(int x,int y)
{
	short i,j,k=4;
	for(i=x;i<x+5;i++)
	{
		for(j=y-k;j<=y+k;j++)
		{
			putpixel(i,j,4);
		}
		k--;
	}
}
//----------------------start of keyBoardHit()--------
void keyboardHit()
{
	char ch1,ch2;
	if(kbhit())
	{
	     ch1=getch();
	     if(ch1==0)
	     {
		   ch2=getch();
		   switch(ch2)
		   {
			case 75:
				 if(racket_x1>10) //condition to dont go racket in left window
				 {
					 detectvalue=1;
					 racket_x1=racket_x1-incrac;
					 racket_x2=racket_x2-incrac;
				 }
				 break;
			case 77:
				 if(racket_x2<620)//condition to dont go racket in right window
				 {
					 detectvalue=2;
					 racket_x1=racket_x1+incrac;
					 racket_x2=racket_x2+incrac;
				 }
				 break;
			default:   ;
		   }

	     }
	     else if(ch1==80 || ch1==112) //pause and resume the game
	     {
			outtextxy(220,200,"Type any key to resume...");
			getch();
			putimage(220,200,clearprinted,COPY_PUT);
	     }
	     else if(ch1==27) //to Exit from the Game
	     {
			outtextxy(220,200,"Do you want exit..");
			switch(getch())
			{
				case 'Y':
					exit(0);
				case 'y':
					exit(0);
				default:
					;
			}
			putimage(220,200,clearprinted,COPY_PUT);
	     }
      }
}
//---------------------------end of keyboardHit()--------
int animationStart()
{
	if(x1<=left_bound)//for checking the ball is touched or not to left wall
	{
		if((y1_after-y1_before)>0)
		{
			call_left_bound_first();
		}
		else
		{
			call_left_bound_second();
		}
		x1_after=x1;
		y1_after=y1;
		flag=1;
		checkelse=0;
	}
	else if((x1>=racket_x1-5)&&(x2<=racket_x2+5)&&(y2>=racket_y1-5))//ball is touched the racket
	{
		if(delay_time>40)
			delay_time=delay_time-20;
		if((x1_after-x1_before)>0)
		{
			call_lower_bound_first();
		}
		else
		{
			call_lower_bound_second();
		}
		x1_after=x1;
		y1_after=y1;
		flag=2;
		checkelse=0;

	}
	else if(x2>=right_bound)//for checking the ball is touched or not to right wall
	{
		if((y1_after-y1_before)>0)
		{
			call_right_bound_first();
		}
		else
		{
			call_right_bound_second();
		}
		x1_after=x1;
		y1_after=y1;
		flag=3;
		checkelse=0;
	 }
	 else if(((color=getpixel(x1,y1-1))==15)||((color1=getpixel(x1+10,y1-1))==15))//check that ball touched the white Rec
	 {
		color=getpixel(x1,y1-1);
		color1=getpixel(x1+10,y1-1);
		if((color==15 )&&(color1==15)) //it touched two white rec at the same time so vanish both
		{
			changeDia(x1,y1,x2,1);
			doit=1;
		}
		else if((color==15 )&&(color1==0))//it touched left white rec.
		{
			changeDia(x1,y1,x2,2);
			doit=1;
		}
		else if((color==0)&&(color1==15))//it touched right white rec.
		{
			changeDia(x1+10,y1,x2+10,3);
			doit=1;
		}
		if(doit)
		{
			if((x1_after-x1_before)>0)
			{
				call_upper_bound_first();
			}
			else
			{
				call_upper_bound_second();
			}
			x1_after=x1;
			y1_after=y1;
			flag=4;
			checkelse=0;
			doit=0;
		}
	 }
	 else if(y1<=32)//for checking the ball is touched or not to upper wall
	 {
		if((color=getpixel(x2+1,y2))==15) //check that some right bottom i.e x2 is touched white rec.
			changeDia(x2+1,y2,x2,3);
		else if((color=getpixel(x2-11,y2))==15)//check that some left bottom i.e x2-10 is touched white rec.
			changeDia(x2-11,y2,x2,2);
		if((x1_after-x1_before)>0)
			call_upper_bound_first();
		else
			call_upper_bound_second();
		x1_after=x1;
		y1_after=y1;
		flag=4;
		checkelse=0;
	}
	else if(y1>=racket_y1)//check that ball gone to down i.e Game is Over
	{
		settextstyle(1,0,8);
		setcolor(4);
		outtextxy(100,100,"Game-Over");
		delay(1500);
		return(1);
	}
	else //start of main else
	{
	     if(checkelse)
	     {
			beforered=1;
			ball_x1=x1;
			ball_y1=y1;
			ball_x2=x2;
			ball_y2=y2;

			x1_before=x1;
			y1_before=y1;

			x1=x1+inc;
			y1=y1+inc;
			x2=x2+inc;
			y2=y2+inc;

			x1_after=x1;
			y1_after=y1;

		}
		else
		{
			if(flag==1)
			{
				if(dir==1)
					call_left_bound_first();
				else if(dir==2)
					call_left_bound_second();
				x1_after=x1;
				y1_after=y1;
			}
			else if(flag==2)
			{
				if(dir==1)
					call_lower_bound_first();
				else if(dir==2)
					call_lower_bound_second();
				x1_after=x1;
				y1_after=y1;
			}
			else if(flag==3)
			{
				if(dir==1)
					call_right_bound_first();
				else if(dir==2)
					call_right_bound_second();
				x1_after=x1;
				y1_after=y1;
			}
			else if(flag==4)
			{
				if(dir==1)
					call_upper_bound_first();
				else if(dir==2)
					call_upper_bound_second();
				x1_after=x1;
				y1_after=y1;
			}
		}

	}    //end os main else
	delay(delay_time);
	return(0);
}
//-----------------------start of showBallRac()---------
void showBallRac()
{
	if(beforered==0)
		putimage(x1,y1,buf,COPY_PUT);//make the ball red (only once it is executed)
	else
	{
		putimage(ball_x1,ball_y1,buf1,COPY_PUT);//make the earlier ball black
		putimage(x1,y1,buf,COPY_PUT);//make the next ball red
	}
	if(detectvalue==0)
		putimage(racket_x1,racket_y1,racketyellow,COPY_PUT);//make the initial racket
	else
	{
	       if(detectvalue==1)
	       {
			//when user pressed left side arrow(to go racket left side)
			putimage(racket_x2+1,racket_y1,racketblack,COPY_PUT);//make the black some part of racket(some of the right side)
			putimage(racket_x1,racket_y1,racketyellow,COPY_PUT);//make the yellow
	       }
	       else
	       {
			//when user pressed right side arrow(to go racket right side)
			putimage(racket_x1-20,racket_y1,racketblack,COPY_PUT);//make the black some part of racket(some of the left side)
			putimage(racket_x1,racket_y1,racketyellow,COPY_PUT);//make the yellow
	       }
	       detectvalue=0;
	}
}
//-----------------------end of showBallRac()---------
//------------------------Start of basicInitialization()-------------
void basicInitialization()
{
	make_x1=10,make_x2=55,make_y1=25,make_y2=39;//initialy make the rectangles upper side

	//set color for outline
	setcolor(15);
	line(5,20,5,465);//first line
	line(5,465,630,465);//second line
	line(630,465,630,20);//third line
	line(5,20,630,20);//fourth line

	/*------------------For the purpose of upper side rectangle------------*/
	//make the memory for black rectangle (upper);
	setcolor(0);
	setfillstyle(SOLID_FILL,0);
	rectangle(make_x1,make_y1,make_x2,make_y2);
	floodfill(make_x1+1,make_y1+2,0);
	upperrecblack=malloc(imagesize(make_x1,make_y1,make_x2,make_y2));
	getimage(make_x1,make_y1,make_x2,make_y2,upperrecblack);
	//start of clearprinted
	rectangle(220,200,415,210);
	floodfill(222,202,0);
	clearprinted=malloc(imagesize(220,200,415,210));
	getimage(220,200,415,210,clearprinted);
	//make the memory for white rectangle (upper);
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	rectangle(make_x1,make_y1,make_x2,make_y2);
	floodfill(make_x1+1,make_y1+2,15);
	upperrecwhite=malloc(imagesize(make_x1,make_y1,make_x2,make_y2));
	getimage(make_x1,make_y1,make_x2,make_y2,upperrecwhite);

	initial(); //call the function to make the all white rectangles upper side


	/*------------------For the purpose of ball rectangle------------*/
	//make the memory for red ball
	setcolor(4);
	setfillstyle(SOLID_FILL,4);
	rectangle(x1,y1,x2,y2);
	floodfill(x1+1,y1+2,4);
	buf=malloc(imagesize(x1,y1,x2,y2));
	getimage(x1,y1,x2,y2,buf);

	//make the memory for black ball
	setcolor(0);
	setfillstyle(SOLID_FILL,0);
	rectangle(x1+10,y1+10,x2+10,y2+10);
	floodfill(x1+11,y1+12,0);
	buf1=malloc(imagesize(x1+10,y1+10,x2+10,y2+10));
	getimage(x1+10,y1+10,x2+10,y2+10,buf1);

	/*------------------For the purpose of racket rectangle------------*/
	//make the memory for yellow racket
	setcolor(14);
	setfillstyle(SOLID_FILL,14);
	rectangle(racket_x1,racket_y1,racket_x2,racket_y2);//draw rectangle
	floodfill(racket_x1+2,racket_y1+2,14);
	racketyellow=malloc(imagesize(racket_x1,racket_y1,racket_x2,racket_y2));
	getimage(racket_x1,racket_y1,racket_x2,racket_y2,racketyellow);

	//make the memory for black racket
	setcolor(0);
	setfillstyle(SOLID_FILL,0);
	rectangle(racket_x2+1,racket_y1,racket_x2+20,racket_y2);//draw rectangle
	floodfill(racket_x2+2,racket_y1+2,0);
	racketblack=malloc(imagesize(racket_x2+1,racket_y1,racket_x2+20,racket_y2));
	getimage(racket_x2+1,racket_y1,racket_x2+20,racket_y2,racketblack);

}
//------------------------End of basicInitialization()-------------
//------------------------initial()-------
void initial()
{
	int i,j;
	for(i=0;i<6;i++)
	{
		for(j=0;j<13;j++)
		{
			putimage(make_x1,make_y1,upperrecwhite,COPY_PUT);

			make_x1=make_x2+2;
			make_x2=make_x1+45;
		}
		make_x1=10;
		make_x2=55;
		make_y1=make_y2+2;
		make_y2=make_y1+14;
	}
}
//------------------------------------
//-------------------start of changeDia()
void changeDia(int x1,int y1,int x2,int value)//make the black color of touched white rec
{
	int i,j,color_temp;
	make_x1=10,make_x2=55,make_y1=25,make_y2=39;
	for(i=0;i<6;i++)
	{
		for(j=0;j<13;j++)
		{
			if(/*not black*/((color_temp=getpixel(make_x1+1,make_y1+1))!=0)&&((y1-make_y1)>=0)&&((y1-make_y1)<=15)/*&&(((x1-make_x1)>=0)&&((x1-make_x1)<=46))*/)
			{
				if(((x1-make_x1)>=0)&&((x1-make_x1)<=46))//||(((x1-make_x1)<0)&&((x1-make_x1)>=-46)))
				{
						putimage(make_x1,make_y1,upperrecblack,COPY_PUT);
					score++;
					if(value==1)
					{
						if(x2>make_x2)
						{
							putimage(make_x2+2,make_y1,upperrecblack,COPY_PUT);
							score++;
						}
					}
					break;
				}


			}
			make_x1=make_x2+2;
			make_x2=make_x1+45;
		}
		make_x1=10;
		make_x2=55;
		make_y1=make_y2+2;
		make_y2=make_y1+14;
	}
}
//------------------------call_left_bound_first() & second()----------------
void call_left_bound_first()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1+inc;
	y1=y1+inc;
	x2=x2+inc;
	y2=y2+inc;

	dir=1;
}
void call_left_bound_second()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1+inc;
	y1=y1-inc;
	x2=x2+inc;
	y2=y2-inc;

	dir=2;
}
//-----------------------------end of call_left_bound_first() & second()
//--------------------------call_lower_bound_first() & second()
void call_lower_bound_first()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1+inc;
	y1=y1-inc;
	x2=x2+inc;
	y2=y2-inc;

	dir=1;
}
void call_lower_bound_second()
{

	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1-inc;
	y1=y1-inc;
	x2=x2-inc;
	y2=y2-inc;

	dir=2;
}
//---------------------------------end of call_lower_bound_first() & second()
//------------------------------call_right_bound_first() & second()
void call_right_bound_first()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1-inc;
	y1=y1+inc;
	x2=x2-inc;
	y2=y2+inc;

	dir=1;
}
void call_right_bound_second()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1-inc;
	y1=y1-inc;
	x2=x2-inc;
	y2=y2-inc;

	dir=2;
}
//----------------------------end of call_right_bound_first() & second()
//-------------------------------call_upper_bound_first() & second()
void call_upper_bound_first()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1+inc;
	y1=y1+inc;
	x2=x2+inc;
	y2=y2+inc;

	dir=1;
}
void call_upper_bound_second()
{
	beforered=1;

	ball_x1=x1;
	ball_y1=y1;
	ball_x2=x2;
	ball_y2=y2;

	x1_before=x1;
	y1_before=y1;

	x1=x1-inc;
	y1=y1+inc;
	x2=x2-inc;
	y2=y2+inc;

	dir=2;
}
//---------------------------end of call_upper_bound_first() & second()