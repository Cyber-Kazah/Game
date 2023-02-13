

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
    HDC  Bandit = txLoadImage ("Pic/Bandit.bmp");

    int xBandit = 100;
    int yBandit = 100;
    int vxBandit = 50;

    //пуля
    Bullet  bul = {0, 0, false, 10, 0};
     //барьер
     Barrier bar = [3];
     bar[1] = {250, 590, 260, 320};
     bar[2] = {350, 590, 260, 320};
     bar[3] = {450, 590, 260, 320};


     int x1 = 250;
     int x2 = 510;
     int y1 = 590;
     int y2 = 910;




    while (!GetAsyncKeyState (VK_ESCAPE))
    {
      bar.draw();

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
           txTransparentBlt (txDC(), xBandit, yBandit, 150, 300, Bandit, 0, 0, TX_WHITE);
           xBandit = xBandit + vxBandit;
           if(xBandit > 800 - 100 || xBandit < 0)
           {
              vxBandit = - vxBandit;

           }




          //препядствие
          txRectangle(bar.x, bar.y, bar.x+bar.w, bar.y=bar.h);
          if (stalker.x     < bar.x+bar.w &&
              stalker.x+150 > bar.x &&
              stalker.y     < bar.y+bar.h &&
              stalker.y     > bar.y)
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
     txDeleteDC (Bandit);

    txTextCursor (false);
    return 0;
    }

