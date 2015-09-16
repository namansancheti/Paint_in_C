/* 13103480 - Naman Sancheti */
/*****************************************************************************
SOURCE CODE
*****************************************************************************/
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

union REGS i, o;
int leftcolor[15];
int getkey();
void draw_color_panel();
void draw_shape_panel();
void change_color(int,int);
char change_shape(int,int);
void showmouseptr();
void hidemouseptr();
void restrictmouseptr(int,int,int,int);
void getmousepos(int *button,int *x,int *y);

void main()
{
   int gd = DETECT,gm;

   int maxx,maxy,x,y,button,temp1,temp2,key,color,a;
   char ch = 'f' ;            // DEFAULT IS FREE HAND DRAWING
   clrscr();
   for(a=200;a<=1000;a+=10)
   {
   sound(a);
   delay(20);
   }
   nosound();
   textcolor(RED);
   cprintf("\n\t\t\t        ");
   for(a=75;a>=35;a--)
   {
   gotoxy(a,1);
   cprintf("\n\n\nWELCOME  TO");
   delay(40);
   if(a>=36)
   clrscr();
   else
   {}
   }
   textcolor(BLUE);
   for(a=80;a>=35;a--)
   {
   gotoxy(a,1);
   cprintf("\n\n\n\n\nPAINT");
   delay(40);
   if(a>=36)
   clrscr();
   else
   {}
   }
   textcolor(BLUE);
   for(a=65;a>=26;a--)
   {
   gotoxy(a,1);
   cprintf("\n\n\n\n\n\n\nDeveloped by- NAMAN SANCHETI");
   delay(40);
   if(a>=27)
   clrscr();
   else
   {}
   }
   clrscr();
   textcolor(RED);
   cprintf("\n\n\n         WELCOME  TO");
   textcolor(BLUE);
   cprintf("\n\n\n          PAINT");
   textcolor(RED);
   cprintf("\n\n\n  Developed by-NAMAN SANCHETI");
   getch();

   initgraph(&gd,&gm,"C:\\TC\\BGI");

   maxx = getmaxx();
   maxy = getmaxy();

   setcolor(BLUE);
   rectangle(0,0,maxx,maxy);

   setcolor(YELLOW);
   settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
   outtextxy(maxx/2-150,maxy-28,"Press Esc key to exit");
   setcolor(WHITE);

   draw_color_panel();
   draw_shape_panel();

   restrictmouseptr(1,1,maxx-1,maxy-1);
   showmouseptr();
   rectangle(2,2,518,427);
   setviewport(1,1,519,428,1);

   while(1)
   {
      if(kbhit())
      {
	 key = get_key();

	 if( key == 1 )
	 {
	    closegraph();
	    exit(0);
	 }
      }

      getmousepos(&button,&x,&y);

      if( button == 1 )
      {
	 if( x > 4 && x < 635 && y > 431 && y < 457 )
	    change_color( x, y );
	 else if ( x > 529 && x < 625 && y > 40 && y < 280 )
	     ch = change_shape( x, y );

	 getmousepos(&button,&x,&y);
	 temp1 = x ;
	 temp2 = y ;

	 if ( ch == 'f' )
	 {
	    hidemouseptr();
	    while( button == 1 )
	    {
	       getmousepos(&button,&x,&y);
	       line(temp1,temp2,x,y);
	       temp1 = x;
	       temp2 = y;
	       getmousepos(&button,&x,&y);
	    }
	    showmouseptr();
	 }

	 while( button == 1)
	    getmousepos(&button,&x,&y);


	 hidemouseptr(); //TO AVOID INTERFERENCE OF MOUSE WHILE DRAWING

	 if( ch == 'p')
	    putpixel(x,y,getcolor());

	 else if ( ch == 'b' )
	 {
	    setfillstyle(SOLID_FILL,getcolor());
	    bar(temp1,temp2,x,y);
	 }
	 else if ( ch == 'l')
	    line(temp1,temp2,x,y);
	 else if ( ch == 'e')
	    ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));
	 else if ( ch == 'r' )
	    rectangle(temp1,temp2,x,y);
	 else if( ch  == 'd' )
	    circle(temp1,temp2,abs(x-temp1));
	 else if ( ch == 'c' )
	 {
	    ch = 'f';          // SETTING TO FREEHAND DRAWING
	    clearviewport();
	    color = getcolor();
	    setcolor(WHITE);
	    rectangle(2,2,518,427);
	    setcolor(color);
	 }

	 showmouseptr();
      }
   }
}
/*****************************************************************************
FUNCTION TO GET THE KEY PRESSED BY THE USER
*****************************************************************************/
int get_key()
{
   union REGS i,o;

   i.h.ah = 0;
   int86(22,&i,&o);

   return ( o.h.ah );
}
/****************************************************************************
FUNCTION TO DRAW THE COLOR PANEL
****************************************************************************/
void draw_color_panel()
{
   int left, top, c, color;

   left = 100;
   top = 436;

   color = getcolor();
   setcolor(GREEN);
   rectangle(4,431,635,457);
   setcolor(RED);
   settextstyle(TRIPLEX_FONT,0,2);
   outtextxy(10,431,"Colors : ");

   for( c = 1 ; c <= 15 ; c++ )
   {
      setfillstyle(SOLID_FILL, c);
      bar(left, top, left+16, top+16);
      leftcolor[c-1] = left;
      left += 26;
   }

   setcolor(color);
}

/****************************************************************************
FUNCTION TO DRAW THE SHAPE PANEL
****************************************************************************/
void draw_shape_panel()
{
   int left, top, c, color;

   left = 529;
   top = 45;

   color = getcolor();
   setcolor(BLUE);
   rectangle(525,40,633,285);

   for( c = 1 ; c <= 8 ; c++ )
   {
      rectangle(left, top, left+100, top+25);
      top += 30;
   }
   setcolor(RED);
   outtextxy(530,45,"Bar");
   outtextxy(530,75,"Line");
   outtextxy(530,105,"Pixel");
   outtextxy(530,135,"Ellipse");
   outtextxy(530,165,"Freehand");
   outtextxy(530,195,"Rectangle");
   outtextxy(530,225,"Circle");
   outtextxy(530,255,"Clear");
   setcolor(color);
}

/****************************************************************************
FUNCTION TO CHANGE THE COLOR
****************************************************************************/
void change_color(int x, int y)
{
   int c;

   for( c = 0 ; c <= 13 ; c++ )
   {
      if( x > leftcolor[c] && x < leftcolor[c+1] && y > 437 && y < 453 )
	 setcolor(c+1);
      if( x > leftcolor[14] && x < 505 && y > 437 && y < 453 )
	 setcolor(WHITE);
   }
}

/****************************************************************************
FUNCTION TO CHANGE THE SHAPE
****************************************************************************/
char change_shape(int x, int y)
{
   if ( x > 529 && x < 625 && y > 45 && y < 70 )
      return 'b';
   else if ( x > 529 && x < 625 && y > 75 && y < 100 )
      return 'l';
   else if ( x > 529 && x < 625 && y > 105 && y < 130 )
      return 'p';
   else if ( x > 529 && x < 625 && y > 135 && y < 160 )
      return 'e';
   else if ( x > 529 && x < 625 && y > 165 && y < 190 )
      return 'f';
   else if ( x > 529 && x < 625 && y > 195 && y < 220 )
      return 'r';
   else if ( x > 529 && x < 625 && y > 225 && y < 250 )
      return 'd'; /* d is for circle */
   else if ( x > 529 && x < 625 && y > 255 && y < 280 )
      return 'c';
}

/****************************************************************************
FUNCTION TO SHOW THE MOUSE POINTER
****************************************************************************/
void showmouseptr()
{
   i.x.ax = 1;
   int86(0x33,&i,&o);
}

/****************************************************************************
FUNCTION TO HIDE THE MOUSE POINTER
****************************************************************************/
void hidemouseptr()
{
   i.x.ax = 2;
   int86(0x33,&i,&o);
}

/****************************************************************************
FUNCTION TO RESTRICT THE MOUSE POINTER
****************************************************************************/
void restrictmouseptr( int x1, int y1, int x2, int y2)
{
   i.x.ax = 7;
   i.x.cx = x1;
   i.x.dx = x2;
   int86(0x33,&i,&o);

   i.x.ax = 8;
   i.x.cx = y1;
   i.x.dx = y2;
   int86(0x33,&i,&o);
}

/****************************************************************************
FUNCTION TO GET THE CURRENT MOUSE POSITION
****************************************************************************/
void getmousepos(int *button,int *x,int *y)
{
   i.x.ax = 3;
   int86(0x33,&i,&o);

   *button = o.x.bx;
   *x = o.x.cx;
   *y = o.x.dx;
}
