#pragma once
#include "CTank.h"

class CPlayer : public CTank
{
public:
  CPlayer(const char *name, CPosition pos, int nLifeNum);
  ~CPlayer();

  //��ʼ��
  void init();

  //���ӻ���
  void addScore(int nScore);

  //����ɱ����
  void addKillNum(int nKillNum);

  //��ȡ����
  int getScore();

  //��ȡɱ����
  int getKillNum();

  //�����¼�
  void onDown();
  void onUp();
  void onRight();
  void onLeft();
  void onFire();

  //������
  bool onHitBy(int nDamage);

  //��ɱ����
  void onKillEnemy(CLifeEntity& life);

  //����
  void revive();

  //������������
  void addLifeNum(int num);

  //���
  void addMagazine(int num);

  //�����ӵ��ٶ�
  void setBulletSpeed(int speed);

private:
  //����
  int m_nScore;
  //ɱ����
  int m_nKillNum;
  //��������
  int m_nLifeNum;
  //��ʼ����
  CPosition init_pos;
  //��ʼ����ֵ
  int init_lifenum;
};

