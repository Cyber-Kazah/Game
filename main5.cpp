

#include "TXLib.h"

int main()
    {
    txCreateWindow (1920, 946);
   //фон
    HDC  background = txLoadImage ("Derevna.bmp");


    //сталкер
    HDC  Stalker = txLoadImage ("Stalker.bmp");

    int yStalker = 300;
    int xStalker = 400;
    int y0Stalker = 1500;

    //сталкер влево и вправа
    HDC Stalkerleft = txLoadImage ("Stalkerleft.bmp");
    HDC Stalkerright = txLoadImage ("Stalkerright.bmp");


    HDC Stalker1 = Stalkerleft;
    int xStalker1 = 499;
    int yStalker1 = 600;

    HDC Stalker2 = Stalkerright;
    int xStalker2 = 600;
    int yStalker2 = 600;

   //бандит
    HDC  Bandit = txLoadImage ("Bandit.bmp");

    int xBandit = 100;
    int yBandit = 100;
    int vxBandit = 10;




    //пуля
    int xBullet;
    int yBullet;
    int vx = 5;
    bool Bullet_visible = false;

     //препядствие
     int x1 = 200;
     int x2 = 300;
     int y1 = 400;
     int y2 = 600;




    while (!GetAsyncKeyState (VK_ESCAPE))
    {


          txBegin();
          txBitBlt (txDC(), 0, 0, 1920, 946, background);
          txTransparentBlt (txDC(), xStalker, yStalker, 499, 600, Stalker, 0, 0, TX_WHITE);



//земля
          yStalker += 10;
          if(yStalker > y0Stalker - 1200)
          {
            yStalker = y0Stalker-1200;


          }
//управление
          if(GetAsyncKeyState (VK_SPACE))
          {
            yStalker -= 25;
          }
          if(GetAsyncKeyState ('S'))
          {
            yStalker += 20;
          }
          if(GetAsyncKeyState ('D'))//право
           {
            xStalker += 20;
             Stalker = Stalkerright;
           }
          if(GetAsyncKeyState ('A'))//лево
           {
            xStalker -= 20;
             Stalker = Stalkerleft;
           }
          if (Bullet_visible)
          {
           txCircle(xBullet, yBullet, 3);
           xBullet += vx;
          }
          if(GetAsyncKeyState ('G'))
          {
           xBullet = xStalker+475;
           yBullet = yStalker+305;
           if (Stalker == Stalkerright)
           {
            vx=vx;
           }
           else if (Stalker == Stalkerleft)
           {
            vx=-vx;

           }
           Bullet_visible = true;



          }

 //движение бандита
           txTransparentBlt (txDC(), xBandit, yBandit, 150, 300, Bandit, 0, 0, TX_WHITE);
           xBandit = xBandit + vxBandit;
           if(xBandit > 800 - 100 || xBandit < 0)
           {
              vxBandit = - vxBandit;

           }




          //препядствие
          txRectangle(x1, y1, x2, y2);
          if (xStalker     < x2 &&
              xStalker+150 > x1 &&
              yStalker     < y2 &&
              yStalker     > y1)
          {
          if(Stalker == Stalkerleft);
          {
            xStalker = x2;
           }

           if(Stalker == Stalkerright);
           {
            xStalker = x1-150;
          }

          }
            txEnd();
            txSleep(2);

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);


    }

     txDeleteDC (background);
     txDeleteDC (Stalker);
     txDeleteDC (Bandit);

    txTextCursor (false);
    return 0;
    }

