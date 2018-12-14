#pragma once
#include "CPosition.h"
#include "CLifeEntity.h"
//����
class CTank;

class CBullet : public CPosition
{
public:
  CBullet() = delete;

  CBullet(CTank& tank, int nId, CPosition pos, int nSpeed, int nDir, int nPower);
  
  ~CBullet();

  //�ƶ�
  bool move(int nDistance);

  //����
  void onDie();

  //��ײ������
  void onCrash(CLifeEntity entity);

  //��ʾ
  void show();

  //�ӵ�����
  void fly();

  void clearCurPos();
  void clearPrevPos();

  int getDirection();
  int getSpeed();
  int getPower();
  int getId();
  int getType();

private:
  //�ӵ�Id
  int m_nId;
  //�ӵ��ٶ�
  int m_nSpeed;
  //�ƶ�����
  int m_nDir;
  //�˺�
  int m_nPower;
  //����
  int m_nType;

  //�Ƿ�ը
  bool isBoom;
  bool isAlive;
  bool bSoundFlag;

  int nAnimeFrameNum;
  int nFrameTime;

public:
  //�ϴ�����
  CPosition PrevPos;
  //������
  CTank& m_tank;
};