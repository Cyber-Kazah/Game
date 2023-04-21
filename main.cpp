

#include "TXLib.h"


//������!

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
    txTransparentBlt (txDC(), x, y, 800, 820, image, 0, 0, TX_WHITE);// ��������� ����
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


//���������
int main()
{
    {//������
    if(true)
   {
    txPlaySound ("Muz/Zone Triggers.wav", SND_LOOP);
   }



    }
    txCreateWindow (1920, 946);
    //���
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
    //�������
        Stalkers stalker = {100, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp"), 20, 0, true};
        int y0Stalker = 1500;
    //����
        Bullet  bul = {0, 0, false, 10, 0};
        int napr = 1;
    //����
        Barrier bar[1];
        bar[0] = {1265, 70, 1200, 930, true, txLoadImage ("Pic/DOM4.bmp")};
    //������
        Crow crow = {200, 25, 50, true, txLoadImage ("Pic/crow_right.bmp"), txLoadImage ("Pic/crow_left.bmp"), crow.image_right};
    //�����
        Enemy dog = {1600, 500, 450, 400, 20, false, txLoadImage ("Pic/Dog.bmp")};
        Enemy psidog = {1600, 500, 650, 400, 25, false, txLoadImage ("Pic/Psevdopes.bmp")};
        Enemy pig = {1600, 400, 800, 500, 30, false, txLoadImage ("Pic/kaban3.bmp")};
        Enemy snork = {1600, 500, 730, 450, 40, false, txLoadImage ("Pic/Snork.bmp")};
    //����
        Button btn = {710, 550, 500, 50, "����� ����"};
        Button btn_about = {710, 650, 500, 50, "�����"};
        Button btn_exit = {710, 750, 500, 50, "����� � �������"};
        string PAGE = "menu";


    //�� ��� ����������
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
        //����
        menu.draw();
        //������� � ����
        btn.draw();

        if(btn.mouse_over())
        {
            btn.change();
        }

        if(btn.mouse_click())
        {
            PAGE = "game";
        }

       //�������
       btn_about.draw();

       if(btn_about.mouse_over())
       {
           btn_about.change();
       }

       if(btn_about.mouse_click())
       {
         PAGE = "Settings";
       }


       //�����
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
       txDrawText (250, 75, 1700, 700, "�� ������� �� ������ �������, �� ��������� ������������� ����� ������ � ������ � ���� � ����� ������������ ������. \n"
                            "� ���� ��������� ���������� ������, ����� �������� ��������� ���������� ��������, ������� ������ ������� �����������, \n"
                            "������ ����� ������� ������� �������� ����� �������� � ����, \n"
                            "        ����������         \n"
                            "������ - D \n"
                            "����� - A \n"
                            "�������� - S \n"
                            "������ - ������ \n"
                            "������� - G \n"
                            "����� � ���� - ESC \n");





       }
      if(PAGE == "game")
       {

            //���������
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

            //�����
              stalker.y += 10;
              if(stalker.y > y0Stalker - 1200)
              {
                stalker.y = y0Stalker-1200;


              }
            //����������
              if(GetAsyncKeyState (VK_SPACE))//������
              {
                stalker.y -= 25;
              }
              if(GetAsyncKeyState ('S'))//����
              {
                stalker.y += 20;
                stalker.image = stalker.image_sit;
              }
              if(GetAsyncKeyState ('D'))//�����
              {
                 stalker.x += stalker.vx;
                 stalker.image = stalker.image_right;
               }
              if(GetAsyncKeyState ('A'))//����
              {
                 stalker.x -= stalker.vx;
                 stalker.image = stalker.image_left;
               }
              if(GetAsyncKeyState (VK_SHIFT))//���
              {
               stalker.vx = 30;
              }

            //����
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




            //������
            {
            //����� ������
            if(fon.image == fon_image1)
              if( (stalker.x < bar[0].x + bar[0].w) &&
                  (stalker.x+500 > bar[0].x) &&
                  (stalker.y < bar[0].y+bar[0].h) &&
                  (stalker.y+600 > bar[0].y))
         {
           txSetColor(TX_WHITE);
           txTextOut(250, 75, "��� ���?!?! ������� ���-�� ����� ����� ����� ��������� ��������? ��� ���� ������ �������? �������, ����� �������, ���� ������� ������. �����, ���� ���� ��������, ����� �� ������� �� ���� �����. ");

         }
            //����� �������� �����
            if(fon.image == fon_image4)
            {
            txSetColor(TX_YELLOW);
            txTextOut(250, 75, "���� � ���� 100 ������� ������, ��� �� ������� ��� ���������? ���� ���� �� ��������, ����� ��� �������� ��������.");




            }
            //����� ������� �����(��������)
            if(fon.image == fon_image6)
            {
                txSetColor(TX_YELLOW);
                txTextOut(250, 75, "���, � ��� � ����� � ����������, �������� ��� ����� ��������.");
            }
            //����� �������� �����(����������)
            if(fon.image == fon_image7)
            {
                txSetColor(TX_YELLOW);
                txTextOut(250, 75, "���� ���� ������, ��� ���������� ������� ������� � �������.");

            }




            }


            //������� �� ������ �������
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

            //����������
            {
            //������
            if(dog.visible && dog.x > stalker.x) dog.x -= dog.vx;
            if(dog.visible && dog.x < stalker.x) dog.x += dog.vx;

            if (dog.visible && dog.x < stalker.x+499) stalker.visible = false;
            if (bul.x > dog.x && dog.visible)
                {
                    dog.visible = false;
                    bul.visible = false;
                }

            //������ ��������
            if(psidog.visible && psidog.x > stalker.x) psidog.x -= psidog.vx;
            if(dog.visible && dog.x < stalker.x) dog.x += dog.vx;

            if (psidog.visible && psidog.x < stalker.x+499) stalker.visible = false;
            if (bul.x > psidog.x && psidog.visible)
               {
                    psidog.visible = false;
                    bul.visible = false;
               }

            //�����
            if(pig.visible && pig.x > stalker.x) pig.x -= pig.vx;
            if(pig.visible && pig.x < stalker.x) pig.x += pig.vx;

            if (pig.visible && pig.x < stalker.x+499) stalker.visible = false;
            if (bul.x > pig.x && pig.visible)
               {
                    pig.visible = false;
                    bul.visible = false;
               }

            //�����
            if(snork.visible && snork.x > stalker.x) snork.x -= snork.vx;
            if(snork.visible && snork.x < stalker.x) snork.x += snork.vx;

            if (snork.visible && snork.x < stalker.x+499) stalker.visible = false;
            if (bul.x > snork.x && snork.visible)
               {
                    snork.visible = false;
                    bul.visible = false;
               }









            }






            //�����
            if(stalker.visible == false)
            {
             fon.image = fon_dead;


            }

         //�������������� �� ��� X
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

