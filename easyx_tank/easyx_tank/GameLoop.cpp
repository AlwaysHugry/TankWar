#include "CGame.h"
#include "GameConst.h"

/*
  ��Ϸ��Ҫ��ѭ��
*/
void CGame::GameLoop()
{
  //����һ��
  ui->Clear();

  //��ʾ��ͼ
  ui->DrawMap();

  //����CD����
  int count = 0;

  //��Ϸ�߼�ѭ��
  while (!isGameOver() && !isPlayerWin())
  {
    //��ӵ��˵�ս��
    if (count % (ENEMY_TIME * 100) == 0)
    {
      AddRobot();
    }
    
    //���buff��ս��
    if (count % (BUFF_TIME * 100) == 0)
    {
      GenerateBuff();
    }

    //AI�˶�
    MotionAllRobot();

    //ˢ��buff
    FlushAllBuff();

    //������̹��
    FlushAllTank();

    //�����е��ӵ�
    FlushAllBullet();
    
    //���1����
    if (GetAsyncKeyState('W') & 0x8000)
    {
      Player1.onUp();
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
      Player1.onDown();
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
      Player1.onLeft();
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
      Player1.onRight();
    }
    //���1�����
    if (GetAsyncKeyState('J') & 0x8000)
    {
      if (count % 10 == 0)
      {
        Player1.onFire();
      }
    }

    //���2����
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
      Player2.onUp();
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
      Player2.onDown();
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
      Player2.onLeft();
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
      Player2.onRight();
    }
    //���2�����
    if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
    {
      if (count % 10 == 0)
      {
        Player2.onFire();
      }
    }
  
    //��������
    if (!(GetAsyncKeyState(VK_UP) & 0x8000))//��������
    {
      Player1.bMoveFlag = false;
      Player2.bMoveFlag = false;
    }

    //CD��ʱ
    count++;
    //��CPU
    ui->Wait(nGameSpeed);
    //��ռCPU
    //Sleep(nGameSpeed);
  }
  
  //�ͷ�����
  ReleaseData();
  //�����Ļ
  ui->Clear();
}
