

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
  txSetColor(TX_WHITE);
           txSetFillColor(TX_WHITE);
           txRectangle(x, y, x+w, y+h);
           txSetColor(TX_WHITE);
           txDrawText(x, y, x+w, y+h, text);
  }


 };
//���������
int main()
{
    {//������
    if(true)
    txPlaySound ("Muz/Dirge for the planet.wav", SND_LOOP);
    }
    txCreateWindow (1920, 946);
    //���
        HDC fon_image1 = txLoadImage ("Pic/Derevna2.bmp");
        HDC fon_image2 = txLoadImage ("Pic/Svalka.bmp");
        HDC fon_menu = txLoadImage ("Pic/Menu.bmp");

        Background fon = {0, 0, fon_image1};

        Background menu = {0, 0, fon_menu};
    //�������
        Stalkers stalker = {100, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp"), 20};
        int y0Stalker = 1500;
    //����
        Bullet  bul = {0, 0, false, 10, 0};
    //����
        Barrier bar[1];
        bar[0] = {1265, 70, 1200, 930, true, txLoadImage ("Pic/DOM4.bmp")};
    //������
        Crow crow = {200, 25, 50, txLoadImage ("Pic/crow.bmp")};
    //����
        Button btn = {800, 600, 800, 600, "���� ������"};
        string PAGE = "menu";


    //�� ��� ����������
    while (!GetAsyncKeyState (VK_ESCAPE))
    {
      if(PAGE == "menu")
      {
       txBegin();
       menu.draw();
       txEnd();
       txSleep(2);
           btn.draw();

       if(txMouseX() > 50 && txMouseX() < 200 &&
          txMouseY() > 50 && txMouseY() < 100)
       {
           txSetColor(TX_WHITE);
           txSetFillColor(TX_BLACK);
           txRectangle(800, 600, 800, 600);
           txSetColor(TX_WHITE);
           txDrawText(490, 300, 550, 550, " ���� ������");
       }
       if( txMouseButtons() == 1 &&
               txMouseX() > 50 && txMouseX() < 200 &&
               txMouseY() > 50 && txMouseY() < 100)
           {
             PAGE = "game";
           }

      }
      if(PAGE == "game")
       {


            //���������
            fon.draw();
            if(fon.image == fon_image1)
                bar[0].draw();
            stalker.draw();
            crow.draw();


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
               stalker.vx = 1000;
              }

            //����
              if (bul.visible)
              {
               txCircle(bul.x, bul.y, 5);
               bul.x = bul.x + bul.vx;
              }
              if(GetAsyncKeyState ('G'))
              {
               bul.x = stalker.x+475;
               bul.y = stalker.y+305;
              }
              if (stalker.image == stalker.image_right)
              {
                bul.vx=bul.vx;
               }
              else if (stalker.image == stalker.image_left)
              {
                bul.vx=-bul.vx;

               }
               bul.visible = true;





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
            //������� �� ������ �������
              if(stalker.x > 1500)
               {
                    fon.image = fon_image2;
                    stalker.x = 500;
               }




         //�������������� �� ��� X
         //char str[100];
         //sprintf(str, "x= %d y= %d", stalker.x, stalker.y);
         //txTextOut(100, 550, str);




                }

         txSetColor (TX_BLACK);
         txSetFillColor (TX_BLACK);


    }

     txDeleteDC (fon.image);
     txDeleteDC (stalker.image);
     txDeleteDC (crow.image);
     txDeleteDC (bar[0].image);

    txTextCursor (false);
    return 0;
    }

