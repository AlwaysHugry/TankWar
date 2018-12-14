#pragma once
#include "CTank.h"

//�����Ѷ�
#define ENEMY_LEVEL 10

/*
  ������AI�� �̳�tank
*/
class CRobot : public CTank
{
public:
  CRobot(std::string m_strTankName, emTankType emType, CPosition pos, emTankCamp camp = emTankCamp::CAMP_ENEMY);
  ~CRobot();

  //������
  virtual bool onHitBy(int nDamage);

  //��ʼ״̬
  void create();

  //��ʼ������
  void init();

  //����
  void revive();

  //�ƶ�
  bool moveLeft();
  bool moveDown();
  bool moveUp();
  bool moveRight();

  //��ɱ����
  void onKillEnemy(CLifeEntity& life);

  //�˶�
  void motion();

  //����ֹͣʱ��
  void SetStopTime(int nTime);

  //����
  void toDie();

private:
  CPosition init_pos;
  unsigned int m_nStopTime;
  unsigned int startTime;
};

