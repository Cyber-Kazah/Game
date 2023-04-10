

#include "TXLib.h"

struct Background
{
    int x;
    int y;
    HDC image;

    void draw()
    {
        txBitBlt (txDC(), x, y, 1920, 946, image);
    }
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
    bool visible;

void draw()
   {
    if(visible) txTransparentBlt (txDC(), x, y, 499, 600, image, 0, 0, TX_WHITE);
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

 struct Button
 {
  int x;
  int y;
  int w;
  int h;
  const char* text;
  COLORREF color;
  COLORREF fill_color;

    void draw()
    {
        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        txRectangle(x, y, x+w, y+h);
        txDrawText(x, y, x+w, y+h, text);
    }

    void change()
    {
        txSetColor(TX_WHITE);
        txSetFillColor(TX_BLACK);
        txRectangle(x, y, x+w, y+h);
        txDrawText(x, y, x+w, y+h, text);
    }

    bool mouse_over()
    {
        if(txMouseX()>x && txMouseX()<x+w && txMouseY()>y && txMouseY()<y+h)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool mouse_click()
    {
        if( txMouseButtons() == 1 && txMouseX() > x && txMouseX() < x+w && txMouseY() > y && txMouseY() < y+h)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
 };

 struct Enemy
 {
  int x;
  int y;
  int vx;
  bool visible;
  HDC image;

  void draw()
  {
    if(visible) txTransparentBlt (txDC(), x, y, 450, 400, image, 0, 0, TX_WHITE);
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
        HDC fon_image1 = txLoadImage ("Pic/Derevna2.bmp");
        HDC fon_image2 = txLoadImage ("Pic/Svalka.bmp");
        HDC fon_menu = txLoadImage ("Pic/Menu.bmp");

        Background fon = {0, 0, fon_image1};

        Background menu = {0, 0, fon_menu};
    //сталкер
        Stalkers stalker = {100, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp"), 20, 0, true};
        int y0Stalker = 1500;
    //пуля
        Bullet  bul = {0, 0, false, 10, 0};
        int napr = 1;
    //Хата
        Barrier bar[1];
        bar[0] = {1265, 70, 1200, 930, true, txLoadImage ("Pic/DOM4.bmp")};
    //ворона
        Crow crow = {200, 25, 50, txLoadImage ("Pic/crow.bmp")};
    //враги
        Enemy dog = {1600, 500, 20, false, txLoadImage ("Pic/Dog.bmp")};

    //Меню
        Button btn = {710, 550, 500, 50, "Новая игра"};
        Button btn_about = {710, 650, 500, 50, "Опции"};
        Button btn_exit = {710, 750, 500, 50, "Выход в Виндоус"};
        string PAGE = "menu";


    //ТО ЧТО ПРОИСХОДИТ
    while (!GetAsyncKeyState (VK_ESCAPE))
    {
        txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();

      if(PAGE == "menu")
      {
        //меню
        menu.draw();
        //переход к игре
        btn.draw();

        if(btn.mouse_over())
        {
            btn.change();
        }

        if(btn.mouse_click())
        {
            PAGE = "game";
        }

       //Пособие
       btn_about.draw();

       if(btn_about.mouse_over())
       {
           btn_about.change();
       }

       if(btn_about.mouse_click())
       {
         PAGE = "Settings";
       }


       //выход
       btn_exit.draw();

       if(btn_exit.mouse_over())
       {
           btn_exit.change();
       }

       if(btn_exit.mouse_click())
       {
         PAGE = "Exit";
       }

       }
      if(PAGE == "game")
       {

            //рисование
            fon.draw();
            if(fon.image == fon_image1)
                bar[0].draw();
            stalker.draw();
            crow.draw();
            if(fon.image == fon_image2)
                dog.draw();

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
               stalker.vx = 1000;
              }

            //пуля
              if (bul.visible)
              {
                   txCircle(bul.x, bul.y, 5);
                   bul.x += bul.vx;

                  if(napr == 1) bul.vx=bul.vx;
                  if(napr == 0) bul.vx=-bul.vx;
              }
              if(GetAsyncKeyState ('G'))
              {
                   bul.x = stalker.x+475;
                   bul.y = stalker.y+305;
                   bul.visible = true;
                   if (stalker.image == stalker.image_right)
                    {
                        napr = 1;
                    }
                    else if (stalker.image == stalker.image_left)
                    {
                        napr = 0;
                    }
              }






            //текст Севера
            if(fon.image == fon_image1)
              if( (stalker.x < bar[0].x + bar[0].w) &&
                  (stalker.x+500 > bar[0].x) &&
                  (stalker.y < bar[0].y+bar[0].h) &&
                  (stalker.y+600 > bar[0].y))
         {
           txSetColor(TX_WHITE);
           txTextOut(250, 75, "Кто это?!?! Неужели кто-то выжил после этого нашествия мутантов? Как тебя кличут сталкер? Акробат, будем знакомы, меня Севером кличут. Прошу, убей всех мутантов, выход из деревни за моим домом. ");

         }
            //переход на другую локацию
              if(stalker.x > 1500)
               {
                    fon.image = fon_image2;
                    stalker.x = 500;
                    dog.visible = true;
               }
            //Противник
            if(dog.visible && dog.x > stalker.x) dog.x -= dog.vx;
            if(dog.visible && dog.x < stalker.x) dog.x += dog.vx;

            if (dog.visible && dog.x < stalker.x+499) stalker.visible = false;
            if (bul.x > dog.visible && dog.x) dog.visible = false;
         //местоположение на оси X
         //char str[100];
         //sprintf(str, "x= %d y= %d", stalker.x, stalker.y);
         //txTextOut(500, 550, str);




        }
        txEnd();
        txSleep(10);



    }

     txDeleteDC (fon.image);
     txDeleteDC (stalker.image);
     txDeleteDC (crow.image);
     txDeleteDC (bar[0].image);

    txTextCursor (false);
    return 0;
    }

