

#include "TXLib.h"


//ОШИБКИ!

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
    bool visible;
    HDC image_right;
    HDC image_left;
    HDC image;

void draw()
   {
    if(x < 0)
    {
         vx = - vx;
         image = image_right;
    }
    if(x > 2000 - 1)
    {
        vx = - vx;
        image = image_left;
    }
    txTransparentBlt (txDC(), x, y, 260, 280, image, 0, 0, TX_WHITE);
    x = x + vx;
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
  int w;
  int h;
  int vx;
  bool visible;
  HDC image;

  void draw()
  {
    if(visible) txTransparentBlt (txDC(), x, y, w, h, image, 0, 0, TX_WHITE);
  }




 };


//ЗАКУЛИСЬЕ
int main()
{
    {//МУЗЫКА
    if(true)
   {
    txPlaySound ("Muz/Zone Triggers.wav", SND_LOOP);
   }



    }
    txCreateWindow (1920, 946);
    //фон
        HDC fon_image1 = txLoadImage ("Pic/Derevna2.bmp");
        HDC fon_image2 = txLoadImage ("Pic/Svalka.bmp");
        HDC fon_image3 = txLoadImage ("Pic/svalka2.bmp");
        HDC fon_image4 = txLoadImage ("Pic/Bar.bmp");
        HDC fon_image5 = txLoadImage ("Pic/Agroprom.bmp");
        HDC fon_image6 = txLoadImage ("Pic/spusk.bmp");
        HDC fon_image7 = txLoadImage ("Pic/podzem.bmp");
        HDC fon_dead = txLoadImage ("Pic/dead.bmp");
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
        Crow crow = {200, 25, 50, true, txLoadImage ("Pic/crow_right.bmp"), txLoadImage ("Pic/crow_left.bmp"), crow.image_right};
    //враги
        Enemy dog = {1600, 500, 450, 400, 20, false, txLoadImage ("Pic/Dog.bmp")};
        Enemy psidog = {1600, 500, 650, 400, 25, false, txLoadImage ("Pic/Psevdopes.bmp")};
        Enemy pig = {1600, 400, 800, 500, 30, false, txLoadImage ("Pic/kaban3.bmp")};
        Enemy snork = {1600, 500, 730, 450, 40, false, txLoadImage ("Pic/Snork.bmp")};
    //Меню
        Button btn = {710, 550, 500, 50, "Новая игра"};
        Button btn_about = {710, 650, 500, 50, "Опции"};
        Button btn_exit = {710, 750, 500, 50, "Выход в Виндоус"};
        string PAGE = "menu";


    //ТО ЧТО ПРОИСХОДИТ
    while (true)
    {
        txSetColor (TX_BLACK);
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();
      if(GetAsyncKeyState (VK_ESCAPE))
      {
        PAGE = "menu";
      }
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
         break;
       }

       }
      if(PAGE == "Settings")
      {
        txSetColor(TX_WHITE);
       txDrawText (250, 75, 1700, 700, "Вы сталкер по кличке Акробат, вы утаиваете происхождение своей клички и попали в зону в самый неподходящий момент. \n"
                            "В зоне произошёл мощьнейший выброс, после которого произошло нашестивие мутантов, которые добили остатки группировок, \n"
                            "Сейчас вашей главной задачей является поиск виновных в этом, \n"
                            "        УПРАВЛЕНИЕ         \n"
                            "Вправо - D \n"
                            "Влево - A \n"
                            "Присесть - S \n"
                            "Прыжок - Пробел \n"
                            "Выстрел - G \n"
                            "Выход в меню - ESC \n");





       }
      if(PAGE == "game")
       {

            //рисование
            fon.draw();
            if(fon.image == fon_image1)
                bar[0].draw();
            stalker.draw();
            if(crow.visible) crow.draw();
            if(fon.image == fon_image2)
                dog.draw();
            if(fon.image == fon_image3)
                psidog.draw();
                pig.draw();
                snork.draw();

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
               stalker.vx = 30;
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




            //Тексты
            {
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
            //текст главного героя
            if(fon.image == fon_image4)
            {
            txSetColor(TX_YELLOW);
            txTextOut(250, 75, "Даже в баре 100 Рентген никого, Что же вызвало это нашествие? надо идти на Агропром, может там найдутся выжившие.");




            }
            //текст глвного героя(агропром)
            if(fon.image == fon_image6)
            {
                txSetColor(TX_YELLOW);
                txTextOut(250, 75, "Так, а вот и спуск в Подземелья, возможно там будут выжившие.");
            }
            //текст главного героя(подземелья)
            if(fon.image == fon_image7)
            {
                txSetColor(TX_YELLOW);
                txTextOut(250, 75, "Надо быть начеку, эти подземелья окутаны страхом и тайнами.");

            }




            }


            //переход на другую локацию
              if(stalker.x > 1500 && fon.image == fon_image1)
               {
                    fon.image = fon_image2;
                    stalker.x = 500;
                    dog.visible = true;
               }
              if(stalker.x > 1400 && fon.image == fon_image2)
               {
                    fon.image = fon_image3;
                    stalker.x = 450;
                    psidog.visible = true;

               }
              if(stalker.x > 1400 && fon.image == fon_image3)
               {

                    fon.image = fon_image4;
                    stalker.x = 350;
                    pig.visible = true;


               }
              if(stalker.x > 1400 && fon.image == fon_image4)
               {
                    fon.image = fon_image5;
                    stalker.x = 250;
                    snork.visible = true;


               }
              if(stalker.x > 1400 && fon.image == fon_image5)
               {
                    fon.image = fon_image6;
                    stalker.x = 250;
                    snork.visible = true;

               }
              if(stalker.x > 1000 && fon.image == fon_image6)
                {
                    fon.image = fon_image7;
                    stalker.x = 1500;
                    crow.visible = false;


                }

            //Противники
            {
            //собака
            if(dog.visible && dog.x > stalker.x) dog.x -= dog.vx;
            if(dog.visible && dog.x < stalker.x) dog.x += dog.vx;

            if (dog.visible && dog.x < stalker.x+499) stalker.visible = false;
            if (bul.x > dog.x && dog.visible)
                {
                    dog.visible = false;
                    bul.visible = false;
                }

            //собака страшная
            if(psidog.visible && psidog.x > stalker.x) psidog.x -= psidog.vx;
            if(dog.visible && dog.x < stalker.x) dog.x += dog.vx;

            if (psidog.visible && psidog.x < stalker.x+499) stalker.visible = false;
            if (bul.x > psidog.x && psidog.visible)
               {
                    psidog.visible = false;
                    bul.visible = false;
               }

            //кабан
            if(pig.visible && pig.x > stalker.x) pig.x -= pig.vx;
            if(pig.visible && pig.x < stalker.x) pig.x += pig.vx;

            if (pig.visible && pig.x < stalker.x+499) stalker.visible = false;
            if (bul.x > pig.x && pig.visible)
               {
                    pig.visible = false;
                    bul.visible = false;
               }

            //снорк
            if(snork.visible && snork.x > stalker.x) snork.x -= snork.vx;
            if(snork.visible && snork.x < stalker.x) snork.x += snork.vx;

            if (snork.visible && snork.x < stalker.x+499) stalker.visible = false;
            if (bul.x > snork.x && snork.visible)
               {
                    snork.visible = false;
                    bul.visible = false;
               }









            }






            //Экран
            if(stalker.visible == false)
            {
             fon.image = fon_dead;


            }

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
     txDeleteDC (dog.image);
     txDeleteDC (psidog.image);
     txDeleteDC (pig.image);
     txDeleteDC (snork.image);

    txTextCursor (false);
    txDisableAutoPause();
    return 0;
    }

