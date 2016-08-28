//***************************************************************
//                   HEADER FILE USED IN PAINT
//***************************************************************

#include<fstream.h>
#include<process.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<math.h>
#include<dir.h>

int GREY = LIGHTGRAY;

int rec=MAGENTA;
int DetectMouse(void)
     {
	union REGS in,out;
	in.x.ax=0;
	int86(0x33,&in,&out);
	if(out.x.ax==0)
		return(0);
	else
		return(1);
     }

void InitMouse(void)
     {
	union REGS in,out;
	in.x.ax=33;
	int86(0x33,&in,&out);
	return;
     }

void HideMouse(void)
     {
	union REGS in,out;
	in.x.ax=2;
	int86(0x33,&in,&out);
	return;
     }

void ShowMouse(void)
     {
	union REGS in,out;
	in.x.ax=1;
	int86(0x33,&in,&out);
	return;
     }

void WhereMouse(int *x,int *y)
     {
	union REGS in,out;
	in.x.ax=3;
	int86(0x33,&in,&out);
	*x=(int)out.x.cx;
	*y=(int)out.x.dx;
	return;
     }

int ButtClicked(void)
     {
	union REGS imouse,omouse;
	int mc,mr;
	imouse.x.ax = 3;
	int86(0x33,&imouse,&omouse);
	mc=omouse.x.bx;
	return(mc);
     }

int ButtReleased(void)
     {
	int br;
	br=ButtClicked();
	do{}while(ButtClicked()!=0);
	return br;
     }

void draw_button_with_button_name(int x,int y,char *message,int bk=1,int colour=LIGHTGRAY)
     {
	if(bk)
	{
	  setcolor(rec);
	  rectangle(x,y,x+80,y+30);
	}
	setfillstyle(bk,colour);
	floodfill(x+40,y+15,rec);
	setcolor(GREEN);
	settextstyle(0,0,0);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	outtextxy(x+40,y+15,message);
     }

void show_mouse_click_on_button(int a,int b)
     {
	HideMouse();
	setfillstyle(1,7);
	floodfill(a,b,rec);
	delay(50);
	setfillstyle(1,0);
	floodfill(a,b,rec);
	int x=getmaxx()/2,y=getmaxy()/2;
	draw_button_with_button_name(x-120,y-75,"Enter");
	draw_button_with_button_name(x+10,y-75,"View");
	draw_button_with_button_name(x-120,y-35,"Search");
	draw_button_with_button_name(x+10,y-35,"Modify");
	draw_button_with_button_name(x-120,y+5,"Delete");
	draw_button_with_button_name(x+10,y+5,"Help");
	draw_button_with_button_name(x-120,y+45,"Credit");
	draw_button_with_button_name(x+10,y+45,"Exit");
	//outtextxy(x-115,y+110,"Click To Enable\\Disable Sound");
	ShowMouse();
     }


int check_if_mouse_click_is_on_any_button (int a,int b)
     {
	int x=getmaxx(),y=getmaxy();
	if(a>30 && a<70 && b>50 && b<90)
	  return 1;
	else if(a>80 && a<120 && b>50 && b<90)
	  return 2;
	else if(a>130 && a<170 && b>50 && b<90)
	  return 3;
	else if(a>180 && a<220 && b>50 && b<90)
	  return 4;
	else if(a>230 && a<270 && b>50 && b<90)
	  return 5;
	else if(a>280 && a<320 && b>50 && b<90)
	  return 6;
	else if(a>330 && a<370 && b>50 && b<90)
	  return 7;
	else if(a>x-90 && a<x-10 && b>349 && b<379)
	  return 8;
	else if(a>x-90 && a<x-10 && b>100 && b<130)
	  return 9;
	else if(a>x-90 && a<x-10 && b>135 && b<165)
	  return 10;
	else if(a>x-90 && a<x-10 && b>170 && b<200)
	  return 11;
	else if(a>x-90 && a<x-10 && b>205 && b<235)
	  return 12;
	else if(a>x-90 && a<x-10 && b>240 && b<270)
	  return 13;
	else if(a>x-90 && a<x-10 && b>275 && b<305)
	  return 14;
	else if(a>x-90 && a<x-10 && b>310 && b<340)
	  return 15;
	else if(a>x-40 && a<x-10 && b>3 && b<15)
	  return -1;
	else if(a>30 && a<x-100 && b>100 && b<y-50)
	  return 16;
	else
	  return 0;
     }

int currcolor(int button){
 switch(button){
  case 1: return WHITE;break;
  case 2: return BLACK;break;
  case 3: return YELLOW;break;
  case 4: return BLUE;break;
  case 5: return GREEN;break;
  case 6: return RED;break;
  case 7: return GREY;break;
 }
}

int currtool(int button){
 switch(button){
  case 9: return 1;break;//pencil
  case 10: return 2;break;//eraser
  case 11: return 3;break;//brush
  case 12: return 4;break;//line
  case 13: return 5;break;//rectangle
  case 14: return 6;break;//circle
  case 15: return 7;break;//ellipse
  case 8: return 8;break;//fill color
 }
}

void initgraphics(void)
     {
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics mode */
	initgraph(&gdriver, &gmode, "");

	/* read result of initialization */
	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1);             /* return with error code */
	}
     }

//Password function
int password(char pwd[])
     {
	char pass[10];int i=1;
	attempt:
	clrscr();
	gotoxy(25,8);textcolor(RED);
	cputs("Unauthorized Access Denied");
	gotoxy(25,11);textcolor(GREEN);
	cputs("Enter Password:");
	int p=0,q;
	while(p!=9)
	{
	 if(p<0)
	  p=0;
	 q=p;
	 pass[p++]=getch();
	 if(pass[q]==char(8))
	 {
	   p=q-1;
	   gotoxy(q+40,11);
	   cputs(" ");
	   gotoxy(q+40,11);
	 }
	 else if(pass[q]==char(0))
	 {
	   char ch=getch();
	   if(ch==char(83))
	   {
	     p=q-1;
	     gotoxy(q+40,11);
	     cputs(" ");
	     gotoxy(q+40,11);
	   }
	 }
	 else
	 {
	   gotoxy(p+40,11);
	   cputs("*");
	 }
	}
	pass[9]='\0';
	if(strcmp(pass,pwd)==0)
	  return 1;
	else
	{
	  textcolor(YELLOW);
	  gotoxy(30,14);
	  sound(1000);
	  cputs("\aWrong Password!");
	  delay(200);
	  nosound();
	  if(i==3) { gotoxy(29,16);cputs("ALL ATTEMPTS OVER");}
	  else { gotoxy(33,16);cputs("Try Again");}
	  delay(1000);
	  i++;
	  if(i==4) return 0;
	  else goto attempt;
	}
     }


void main()
{
 int maxx,maxy;
 int a,b;
 char pass[] = "Ajeet1997";

 if(password(pass) == 0)
 exit(0);
 else{

 initgraphics();
  maxx=getmaxx();
  maxy=getmaxy();
 InitMouse();
 ShowMouse();
 setcolor(LIGHTBLUE);
 setlinestyle(0, 0, 3);
 rectangle(0,0,maxx,maxy);
 setfillstyle(1,LIGHTBLUE);
 bar(0,0,maxx,20);
 setlinestyle(0,2,1);
 setcolor(WHITE);setfillstyle(SOLID_FILL,WHITE);
 rectangle(30,50,70,90);
 floodfill(31,51,WHITE);
 rectangle(80,50,120,90);
 setcolor(YELLOW);setfillstyle(1,YELLOW);
 rectangle(130,50,170,90);
 floodfill(131,51,YELLOW);
 setcolor(BLUE);setfillstyle(1,BLUE);
 rectangle(180,50,220,90);
 floodfill(181,51,BLUE);
 setcolor(GREEN);setfillstyle(1,GREEN);
 rectangle(230,50,270,90);
 floodfill(231,51,GREEN);
 setcolor(RED);setfillstyle(1,RED);
 rectangle(280,50,320,90);
 floodfill(281,51,RED);
 setcolor(GREY);setfillstyle(1,GREY);
 rectangle(330,50,370,90);
 floodfill(331,51,GREY);
 setcolor(CYAN);
 rectangle(30,100,maxx-100,maxy-50);
 settextstyle(0,0,0);
 setcolor(WHITE);
 outtextxy(10,5,"Paint");
 //TOOLS
  draw_button_with_button_name(maxx-90,100,"PENCIL");
  draw_button_with_button_name(maxx-90,135,"ERASER");
  draw_button_with_button_name(maxx-90,170,"BRUSH");
  draw_button_with_button_name(maxx-90,205,"LINE");
  draw_button_with_button_name(maxx-90,240,"RECTANGLE");
  draw_button_with_button_name(maxx-90,275,"CIRCLE");
  draw_button_with_button_name(maxx-90,310,"ELLIPSE");
  draw_button_with_button_name(maxx-90,349,"BKG COLOR",11);
//exit_button
 setcolor(RED);setfillstyle(1,RED);
 rectangle(maxx-40,3,maxx-10,15);
 floodfill(maxx-39,4,RED);
 setcolor(WHITE);
 outtextxy(maxx-25,9,"X");
//curr_color_box
 setcolor(CYAN);
 rectangle(maxx-50,70,maxx-30,90);
//background_color_box
 line(maxx-50+5,70,maxx-50+5,70-5);
 line(maxx-50+5,70-5,maxx-30+5,70-5);
 line(maxx-30+5,70-5,maxx-30+5,90-5);
 line(maxx-30+5,90-5,maxx-30,90-5);
//eraser_plus_minus_button
setcolor(CYAN);setfillstyle(1,LIGHTBLUE);
 rectangle(maxx-85,maxy-90,maxx-65,maxy-70);
 rectangle(maxx-63,maxy-90,maxx-43,maxy-70);
floodfill(maxx-84,maxy-89,CYAN);
floodfill(maxx-62,maxy-89,CYAN);
 settextjustify(CENTER_TEXT,CENTER_TEXT);
 setcolor(WHITE);
  outtextxy(maxx-75,maxy-80,"+");
  outtextxy(maxx-53,maxy-80,"-");

 //SCREEN
 int i,j,button = 0,curr_color = WHITE,curr_tool = 1;
 int curr_bk_color = BLACK;
     setcolor(curr_color);setfillstyle(1,curr_color);
     floodfill(maxx-49,71,CYAN);
 setcolor(BLUE);setfillstyle(1,BLUE);
 pieslice(maxx-95,115,0,360,3);
 while(1){
     abc:while(!ButtClicked()){
		WhereMouse(&a,&b);
	}
	button = check_if_mouse_click_is_on_any_button(a,b);
     ab:if(button >= 8 && button != 16){
	setcolor(BLACK);setfillstyle(1,BLACK);
	bar(maxx-99,100,maxx-91,maxy-10);
	setcolor(BLUE);setfillstyle(1,BLUE);
	if(button != 8)
	pieslice(maxx-95,115+35*(button-9),0,360,3);
	else{
	pieslice(maxx-95,maxy-118,0,360,3);
	curr_tool = 8;
	button = 16;
	}
	}
	ShowMouse();
	if(button == 0)
	goto abc;
	if(button == -1)
	{
/*	 FILE *fp=fopen("image.png","w");
	 for(int i=101;i<maxy-50;i++){
	 for(j=31;j<maxx-100;j++)
	 {
	   putc(getpixel(i,j),fp);
	 // unsigned far *cha;
	 // *cha = getpixel(i,j);
	 // fputc(*cha,fp);
	 }
	 }
	 fclose(fp);*/
	 exit(0);
	}
    if(button == 16){
     int p,q,i = 0;
     setcolor(curr_color);
     if(curr_tool == 1){
     while(1){
       while(ButtClicked()){
       int r,s;
	WhereMouse(&p,&q);
	button = check_if_mouse_click_is_on_any_button(p,q);
	if(button == 16){
	HideMouse();
	if(i == 0){
	 putpixel(p,q,curr_color);i++;
	 }
	else{
	 line(r,s,p,q);
	 int c,d;
	 WhereMouse(&c,&d);
	 if(c<=30 || c>=maxx-100 || d<=100 || d>=maxy-50)
	  i = 0;
	  }
	 r = p; s = q;
	 }
       }
       ShowMouse();
       i = 0;
       if(button != 16)
	 goto ab;
      }
     }
     else if(curr_tool == 2){
     int size = 4;
    setcolor(curr_bk_color);setfillstyle(1,curr_bk_color);
     while(1){
       while(ButtClicked()){
	WhereMouse(&p,&q);
	button = check_if_mouse_click_is_on_any_button(p,q);
	if(button == 16 && p>30+size && p<maxx-100-size && q>100+size && q<maxy-50-size){
	HideMouse();

	bar(p-size,q-size,p+size,q+size);
       }
       }
       ShowMouse();
       if(button != 16)
	 goto ab;
      }
      }
      else if(curr_tool == 3){
     int  size = 4;
     setfillstyle(1,curr_color);
     while(1){
       while(ButtClicked()){
	WhereMouse(&p,&q);
	button = check_if_mouse_click_is_on_any_button(p,q);
	if(button == 16 && p>30+size && p<maxx-100-size && q>100+size && q<maxy-50-size){
	HideMouse();
	 pieslice(p,q,0,360,size);
	 }
	 }
       ShowMouse();
       if(button != 16)
	 goto ab;
       }
      }
      else if(curr_tool == 4){
	   int c,d;
	    while(1){
	    if(ButtClicked()){
	     WhereMouse(&c,&d);
	     button = check_if_mouse_click_is_on_any_button(c,d);
	     if(c<=30 || c>=maxx-100 || d<=100 || d>=maxy-50)
	     goto ab;

	     while(ButtClicked()){
	      WhereMouse(&p,&q);
	       button = check_if_mouse_click_is_on_any_button(p,q);
		 if(p<=30)
		  p = 31;
		 else if(p>=maxx-100)
		       p = maxx-101;
		 if(q<=100)
		   q = 101;
		 else if(q>=maxy-50)
		   q = maxy-51;
	      }
	    HideMouse();
	    line(c,d,p,q);
	    }
	    ShowMouse();
	      if(button != 16)
	       goto ab;
	      }

	    }

      else if(curr_tool == 5){
	     int c,d;
	    while(1){
	    if(ButtClicked()){
	     WhereMouse(&c,&d);
	     button = check_if_mouse_click_is_on_any_button(c,d);
	     if(c<=30 || c>=maxx-100 || d<=100 || d>=maxy-50)
	     goto ab;

	     while(ButtClicked()){
	      WhereMouse(&p,&q);
	       button = check_if_mouse_click_is_on_any_button(p,q);
		 if(p<=30)
		  p = 31;
		 else if(p>=maxx-100)
		       p = maxx-101;
		 if(q<=100)
		   q = 101;
		 else if(q>=maxy-50)
		   q = maxy-51;
	      }
	    HideMouse();
	    rectangle(c,d,p,q);
	    }
	    ShowMouse();
	      if(button != 16)
	       goto ab;
	      }
	   }

	   else if(curr_tool == 6){
	     int c,d;
	    while(1){
	    if(ButtClicked()){
	     WhereMouse(&c,&d);
	     button = check_if_mouse_click_is_on_any_button(c,d);
	     if(c<=30 || c>=maxx-100 || d<=100 || d>=maxy-50)
	     goto ab;

	     while(ButtClicked()){
	      WhereMouse(&p,&q);
	       button = check_if_mouse_click_is_on_any_button(p,q);
		 if(p<=30)
		  p = 31;
		 else if(p>=maxx-100)
		       p = maxx-101;
		 if(q<=100)
		   q = 101;
		 else if(q>=maxy-50)
		   q = maxy-51;
	      }
	      float r;
	      r = sqrt(pow((p-c),2)+pow((q-d),2))/2;
	    HideMouse();
	    circle((c+p)/2,(d+q)/2,r);
	    }
	    ShowMouse();
	      if(button != 16)
	       goto ab;
	      }
	   }

	    else if(curr_tool == 7){
	     int c,d;
	    while(1){
	    if(ButtClicked()){
	     WhereMouse(&c,&d);
	     button = check_if_mouse_click_is_on_any_button(c,d);
	     if(c<=30 || c>=maxx-100 || d<=100 || d>=maxy-50)
	     goto ab;

	     while(ButtClicked()){
	      WhereMouse(&p,&q);
	       button = check_if_mouse_click_is_on_any_button(p,q);
		 if(p<=30)
		  p = 31;
		 else if(p>=maxx-100)
		       p = maxx-101;
		 if(q<=100)
		   q = 101;
		 else if(q>=maxy-50)
		   q = maxy-51;
	      }
	    HideMouse();
	    ellipse((p+c)/2,(d+q)/2,0,360,abs(c-p)/2,abs(d-q)/2);
	    }
	    ShowMouse();
	      if(button != 16)
	       goto ab;
	      }
	   }

      else if(curr_tool == 8){
    pq: while(1){
       if(ButtClicked()){
	WhereMouse(&p,&q);
	button = check_if_mouse_click_is_on_any_button(p,q);
	if(button == 16){
	HideMouse();
	setcolor(curr_bk_color);setfillstyle(1,curr_bk_color);
	floodfill(p,q,CYAN);
       }
       else if(button>=1 && button <=7) {
	    curr_bk_color = currcolor(button);
	    setfillstyle(1,curr_bk_color);
	    floodfill(maxx-29,69,CYAN);
	    button = 16;
	    goto pq;
	    }
       }
       ShowMouse();
       if(button != 16 && button != 0)
	 goto ab;
      }
      }
    }

    else if(button < 8 && curr_tool != 8){
     curr_color = currcolor(button);
     setcolor(curr_color);setfillstyle(1,curr_color);
     floodfill(maxx-49,71,CYAN);
     }
    else{
    curr_tool = currtool(button);
    }
 }

// getch();
// cleardevice();
 closegraph();
}
}