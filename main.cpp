

#include "TXLib.h"

struct Background
{

};

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

   void draw()
   {
   txTransparentBlt (txDC(), x, y, 499, 600, image, 0, 0, TX_WHITE);
   }
};

struct Barrier
{
  int x;
  int y;
  int w;
  int h;
  bool visible;
  HDC image;

  void draw()
  {
    txTransparentBlt (txDC(), x, y, 800, 820, image, 0, 0, TX_WHITE);// рисование Хаты
  }
   //

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

 struct Crow
 {
  int x;
  int y;
  int vx;
  HDC image;

  void draw()
   {
   txTransparentBlt (txDC(), x, y, 260, 280, image, 0, 0, TX_WHITE);
   x = x + vx;
    if(x > 2000 - 1 || x < 0)
        {
         vx = - vx;
        }
   }
 };



//ЗАКУЛИСЬЕ
int main()
    {
    {//МУЗЫКА
    if(true)
    txPlaySound ("Muz/Dirge for the planet.wav", SND_LOOP);
    }
    txCreateWindow (1920, 946);
    //фон
        HDC  background = txLoadImage ("Pic/Derevna.bmp");
    //сталкер
        Stalkers stalker = {100, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp"), 20};
        int y0Stalker = 1500;
    //пуля
        Bullet  bul = {0, 0, false, 10, 0};
    //Хата
        Barrier bar[1];
        bar[0] = {1265, 70, 1200, 930, true, txLoadImage ("Pic/DOM4.bmp")};
    //ворона
        Crow crow = {200, 25, 50, txLoadImage ("Pic/crow.bmp")};

    //переход на другую локацию
       if(txGetPixel(stalker.x, stalker.y) == RGB(195, 195, 195));
       {
        //fon = txLoadImage ("Pic/Svalka.bmp");
       }

    //ТО ЧТО ПРОИСХОДИТ
    while (!GetAsyncKeyState (VK_ESCAPE))
    {


    txBegin();
        txBitBlt (txDC(), 0, 0, 1920, 946, background);

        //рисование
        bar[0].draw();
        stalker.draw();
        crow.draw();

        //земля
          stalker.y += 10;
          if(stalker.y > y0Stalker - 1200)
          {
            stalker.y = y0Stalker-1200;


          }
        //управление
          if(GetAsyncKeyState (VK_SPACE))//прыжок
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
             stalker.x += stalker.vx;
             stalker.image = stalker.image_right;
           }
          if(GetAsyncKeyState ('A'))//лево
          {
             stalker.x -= stalker.vx;
             stalker.image = stalker.image_left;
           }
          if(GetAsyncKeyState (VK_SHIFT))//бег
          {
           stalker.vx = 100;
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

        //текст Севера
          if( (stalker.x < bar[0].x + bar[0].w) &&
              (stalker.x+500 > bar[0].x) &&
              (stalker.y < bar[0].y+bar[0].h) &&
              (stalker.y+600 > bar[0].y))
     {
       txSetColor(TX_WHITE);
       txTextOut(250, 75, "Кто это?!?! Неужели кто-то выжил после этого нашествия мутантов? Как тебя кличут сталкер? Акробат, будем знакомы, меня Севером кличут. Прошу, убей всех мутантов, выход из деревни за моим домом. ");

     }




     //местоположение на оси X
     //char str[100];
     //sprintf(str, "x= %d y= %d", stalker.x, stalker.y);
     //txTextOut(100, 550, str);



            txEnd();
            txSleep(2);

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);


    }

     txDeleteDC (background);
     txDeleteDC (stalker.image);
     txDeleteDC (crow.image);
     txDeleteDC (bar[0].image);

    txTextCursor (false);
    return 0;
    }

