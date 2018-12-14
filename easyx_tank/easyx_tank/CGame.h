#pragma once
#include "CBarrier.h" //�ϰ�����
#include "CTank.h"
#include "CGameUI.h"
#include "CPlayer.h"
#include "CThread.h"
#include "CSound.h"
#include "CBuffer.h"
#include "CMapFile.h"

class CGame
{
public:
  //��Ϸģʽ
  enum emMode
  {
    MODE_SINGLE,
    MODE_DOUBLE
  };

  //�ϰ�������
  struct tagBarrierContainer
  {
    CBarrier** container_barrier;
    int nLength;
  };

  //̹������
  struct tagTankContainer
  {
    CTank** container_tank;
    int nLength;
  };

public:
  //����
  CGame(CPlayer &player1, CPlayer &player2);
  //����
  ~CGame();
  
  //��ʼ������
  bool Init();
  void InitData();
  void InitBarrier();
  void InitPlayer();
  void InitRobot();
  void InitBuffer();

  //��ȡ��ͼ�ؿ�����
  bool LoadMapData();

  //��ӻ�����
  void AddRobot();

  //������Ϸģʽ
  void SetGameMode(emMode emGameMode);

  //��ʼ��Ϸ
  void start();

  //��Ϸ��ѭ��
  void GameLoop();

  //���ʤ��
  void PlayerWin();

  //�����ײ
  bool CheckTankCrash(CTank& refTank, CPosition pos);
  bool CheckBulletCrash(CBullet& bullet);
  bool isGameOver();
  void GameOver();
  bool isPlayerWin();
  void ReleaseData();
  void ShowGameOver();

  //�˶�����Robot
  void MotionAllRobot();

  //ˢ������̹��
  void FlushAllTank();

  //ˢ�������ӵ�
  void FlushAllBullet();

  //ˢ��buff��ʾ
  void FlushAllBuff();

  //��ͣ���л����˻
  void StopAllRobot(int nTime);

  //������buff
  void GenerateBuff();

  //ɱ�����л�����
  void KillAllRobot();

  //����Χǽ����
  void ToIronHome();

//ȫ����Ϸ����
public:
  //�ϰ�������
  tagBarrierContainer BarArys; 
  //̹������
  tagTankContainer TankArys;
  //ȫ��buffer����
  CBuffer *BufferArys[6];
  //���˳�����
  CPosition EnemyPosArys[3];
  //���1
  CPlayer& Player1;
  //���2
  CPlayer& Player2;

  //��Ϸui
  CGameUI *GameUi;
  //�߳���
  CThread Thread;
  //������
  CSound Sound;

  //��Ϸ�ٶ�
  int nGameSpeed;
  //��ǰ�ؿ�
  int nLevelNum;
  //�ܹؿ���
  int nTotolLevelNum;
  //̹������
  int nTankNum;
  //��ǰ����������
  int nCurRobotNum;
  //��������������
  int nDieRobotNum;
  //��Ϸģʽ
  emMode emGameMode;
  //��Ϸ�Ƿ����
  bool bGameOverFlag;
  //����Ƿ�ʤ��
  bool bPlayerWinFlag;
  //��������
  CPosition m_HomePos;
  //��ͼ�ļ�������
  CMapFile MapFile;
private:
  bool isInit;
};

