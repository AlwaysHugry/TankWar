#include <iostream>
#include "CGameUI.h"
#include "GameConst.h"
#include "CTank.h"

int main()
{
  //������ϷUI
  ui = new CGameUI(SCR_WIDTH, SCR_HEIGHT);
  //�������1
  CPlayer player1 = CPlayer("Player1", { 140,385 }, PLAYER1_LIFE_NUM);
  //�������2
  CPlayer player2 = CPlayer("Player2", { 244,385 }, PLAYER2_LIFE_NUM);
  //������Ϸ
  g_Game = new CGame(player1, player2);

  while (1)
  {
    //��ʼ��
    if (g_Game->Init() == false)
    {
      break;
    }

    //��ʾ�˵�
    ui->DrawMenu();

    //ѡ����Ϸģʽ
    CGameUI::emChoose choose = ui->MenuChoose();

    //����ģʽ
    if (choose == CGameUI::CHO_SINGLE)
    {
      //����ģʽ
      g_Game->SetGameMode(CGame::MODE_SINGLE);
    }
    else if (choose == CGameUI::CHO_DOUBLE)
    {
      //˫��ģʽ
      g_Game->SetGameMode(CGame::MODE_DOUBLE);
    }

    //��ȡ��ͼ�ؿ�����
    if (g_Game->LoadMapData() == false)
    {
      printf(">>> ��ȡ�ؿ����ݳ���...\r\n");
      break;
    }

    //��ʼ������
    g_Game->InitData();

    //��ʼ��Ϸ
    g_Game->start();

  }//��������ֻص��˵�

  printf("exit!!\r\n");
  getchar();
  return 0;
}