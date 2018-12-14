#pragma once
#include "CPosition.h"

/*
  ������
*/
class CLifeEntity
{
public:
  enum emLifeType
  {
    LF_TANK,   //̹��
    LF_BARRIER //�ϰ���
  };

public:
  CLifeEntity(CPosition m_pos, emLifeType emType, int HP);

  ~CLifeEntity();

  bool SubHp(int nHP);

  //����
  void toAlive();

  //����
  void toDie();

  //�Ƿ񻹻���
  bool isAlive();

  //�����˻���
  virtual bool onHitBy(int nDamage);

  //��ʾ
  virtual void show();

  //��ȡ����ֵ
  int GetHP();
  void SetHP(int nHP);

  //��������
  void SetLifeType(emLifeType m_emType);
  emLifeType GetLifeType();

public:
  //����
  CPosition m_pos;
private:
  //����ֵ
  int m_nHP;
  //����������
  emLifeType m_emType;
  //�Ƿ񻹻���
  bool m_bAliveFlag;
};

