

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
  HDC image;

  void draw()
  {
    txBitBlt (txDC(), x, y, w, h, image);
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
   //���
    HDC  background = txLoadImage ("Pic/Derevna.bmp");
    //�������
    Stalkers stalker = {100, 600, txLoadImage ("Pic/Stalker.bmp"), txLoadImage ("Pic/Stalkerleft.bmp"), txLoadImage ("Pic/Stalkerright.bmp"), txLoadImage ("Pic/Stalkersit.bmp")};
    int y0Stalker = 1500;
   //������
    HDC  Crow = txLoadImage ("Pic/Crow.bmp");

    int xCrow = 260;
    int yCrow = 0;
    int vxCrow = 50;

    //����
    Bullet  bul = {0, 0, false, 10, 0};
     //������
     Barrier bar[1];
     bar[0] = {1200, 500, 600, 430, true, txLoadImage ("Pic/DOM.bmp")};


     int x1 = 0;
     int x2 = 640;
     int y1 = 0;
     int y2 = 930;




    while (!GetAsyncKeyState (VK_ESCAPE))
    {


          txBegin();
          txBitBlt (txDC(), 0, 0, 1920, 946, background);

          bar[0].draw();

          txTransparentBlt (txDC(), stalker.x, stalker.y, 499, 600, stalker.image, 0, 0, TX_WHITE);
//�����
          stalker.y += 10;
          if(stalker.y > y0Stalker - 1200)
          {
            stalker.y = y0Stalker-1200;


          }
//����������
          if(GetAsyncKeyState (VK_SPACE))
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
             stalker.x += 20;
             stalker.image = stalker.image_right;
           }
          if(GetAsyncKeyState ('A'))//����
           {
             stalker.x -= 20;
             stalker.image = stalker.image_left;
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

 //�������� �������
           txTransparentBlt (txDC(), xCrow, yCrow, 260, 280, Crow, 0, 0, TX_WHITE);
           xCrow = xCrow + vxCrow;
           if(xCrow > 2000 - 1 || xCrow < 0)
           {
              vxCrow = - vxCrow;

           }




          //�����������

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

