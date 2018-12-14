#pragma once
#include <graphics.h>
#include "CPosition.h"

#define T_SIZE        32
#define TANK_SIZE     30
#define BARRIER_SIZE  16
#define BULLET_SIZE   6

//̹�˳�ʼ������֡��
#define ANIME_INIT_FRAME_NUM 7
//̹����������֡��
#define ANIME_DIE_FRAME_NUM 4
//�ӵ���ը����֡��
#define ANIME_BULLET_BOOM_FRAME_NUM 4

class CGameUI
{
public:
  enum emChoose
  {
    CHO_SINGLE,
    CHO_DOUBLE
  };
public:
  CGameUI(int nWidth, int nHeight);
  ~CGameUI();

  //����ͼƬ����
  bool LoadImgData();

  //������������
  void LoadPosData();

  //���Ʋ˵�
  void DrawMenu();
  
  //����̹��
  void DrawTank(int x, int y, int type, int nDir);

  //���ƻ���Ԫ�أ� nType = 1 ��ʾש  2 �� 3 ǳ������ 4 �������� 5 �� 
  void DrawElement(int x, int y, int nType);

  //����GameOver
  void DrawGameOver(int x, int y);

  //�����ϳ�
  void DrawHomeBase(int x, int y);
  
  //�����ϳ�����
  void DrawHomeBaseDie(int x, int y);

  //�����ӵ� nDir 4������ ��������
  void DrawBullet(int x, int y, int nDir);

  //�����ӵ���ը 1 2 3 ����ͼƬ
  void DrawBulletBoom(int x, int y, int nType);

  //������ͼƬ nType 0��һ֡ 1�ڶ�֡
  void DrawProtect(int x, int y, int nType);
  
  //������ͼƬ nType �ܹ�7֡
  void DrawTankInit(int x, int y, int nFrame);

  //������ͼƬ nType �ܹ�7֡
  void DrawTankDie(int x, int y, int nFrame);

  //���Ƶ�ͼ
  void DrawMap();

  //����ѡ��ָ��
  void DrawChoose(int x, int y, int nFrame);

  //���Ʋ��� 0 - 5 �ܹ�6��
  void DrawBuffer(int x, int y, int nType);

  //����ѡ�񶯻�
  void PlayChooseAnime();

  //ˢ�»���
  void flush();

  //�൱��sleep
  void Wait(int time);

  //�������
  void ClearRect(int x, int y, int width, int height);

  //���������Ļ
  void Clear();

  //��ȡָ������
  void GetRect(int x, int y, int width, int height);

  //��ԭ��ָ������
  void RestoreRect(int x, int y);

  //��ȡս�����
  int getBattleWidth();
  int getBattleHeight();

  //�˵�ѡ��
  emChoose MenuChoose();

  //ѡ��ָ��
  CPosition ChoosePos;

  int nFrameTime;
  bool nAnimeFrameNum;

public:
  //���ڿ��
  int m_nWidth;
  int m_nHeight;

private:
  //ͼƬ����
  IMAGE ImgMenu;
  IMAGE ImgObject;
  IMAGE ImgProtect[2];

  //��ʱ������
  IMAGE ImgTemp;

  //ս�����
  int m_nBattleWidth;
  int m_nBattleHeight;

  //����̹��,ÿ��4������
  CPosition aryTankpos[7][4];

  bool isInit;
};

