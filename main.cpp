

#include "TXLib.h"

struct Stalkers
{
   int x;
   int y;
   HDC image;
   HDC image_left;
   HDC image_right;
   HDC image_sit;
   int vx;
   int vy;
};

struct Barrier
{
  int x;
  int y;
  int w;
  int h;
  bool visible;

  void draw()
  {
    txRectangle(x, y, x+w, y+h);
  }


};

 struct Bullet
 {
   int x;
   int y;
   bool visible;
   int vx;
   int vy;


   void draw()
   {
   txSetColor(TX_YELLOW);
   txSetFillColor(TX_WHITE);
   txCircle(x, y, 5);
   }
 };



int main()
    {
    txCreateWindow (1920, 946);
   //фон
    HDC  background = txLoadImage ("Pic/Derevna.bmp");
    //сталкер
    Stalkers stalker = {500, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp")};
    int y0Stalker = 1500;
   //бандит
    HDC  Crow = txLoadImage ("Pic/Crow.bmp");

    int xCrow = 260;
    int yCrow = 0;
    int vxCrow = 50;

    //пуля
    Bullet  bul = {0, 0, false, 10, 0};
     //барьер
     Barrier bar[3];
     bar[0] = {150, 590, 260, 320, true};
     bar[1] = {250, 590, 260, 320, true};
     bar[2] = {350, 590, 260, 320, true};
     bar[3] = {450, 590, 260, 320, true};


     int x1 = 250;
     int x2 = 510;
     int y1 = 590;
     int y2 = 910;




    while (!GetAsyncKeyState (VK_ESCAPE))
    {
      bar[0].draw();
      bar[1].draw();
      bar[2].draw();
      bar[3].draw();

          txBegin();
          txBitBlt (txDC(), 0, 0, 1920, 946, background);
          txTransparentBlt (txDC(), stalker.x, stalker.y, 499, 600, stalker.image, 0, 0, TX_WHITE);
//земля
          stalker.y += 10;
          if(stalker.y > y0Stalker - 1200)
          {
            stalker.y = y0Stalker-1200;


          }
//управление
          if(GetAsyncKeyState (VK_SPACE))
          {
            stalker.y -= 25;
          }
          if(GetAsyncKeyState ('S'))//вниз
          {
            stalker.y += 20;
            stalker.image = stalker.image_sit;
          }
          if(GetAsyncKeyState ('D'))//право
           {
             stalker.x += 20;
             stalker.image = stalker.image_right;
           }
          if(GetAsyncKeyState ('A'))//лево
           {
             stalker.x -= 20;
             stalker.image = stalker.image_left;
           }

           //пуля
          if (bul.visible)
          {
           txCircle(bul.x, bul.y, 5);
           bul.x = bul.x + bul.vx;
          }
          if(GetAsyncKeyState ('G'))
          {
           bul.x = stalker.x+475;
           bul.y = stalker.y+305;
           if (stalker.image == stalker.image_right)
           {
            bul.vx=bul.vx;
           }
           else if (stalker.image == stalker.image_left)
           {
            bul.vx=-bul.vx;

           }
           bul.visible = true;



          }

 //движение бандита
           txTransparentBlt (txDC(), xCrow, yCrow, 260, 280, Crow, 0, 0, TX_WHITE);
           xCrow = xCrow + vxCrow;
           if(xCrow > 2000 - 1 || xCrow < 0)
           {
              vxCrow = - vxCrow;

           }




          //препядствие

          {
          if(stalker.image == stalker.image_left);
          {
            stalker.x = x2;
           }

           if(stalker.image == stalker.image_right);
           {
            stalker.x = stalker.x-150;
          }

          }
            txEnd();
            txSleep(2);

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);


    }

     txDeleteDC (background);
     txDeleteDC (stalker.image);
     txDeleteDC (Crow);

    txTextCursor (false);
    return 0;
    }

