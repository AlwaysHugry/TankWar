#pragma once
#include "CLifeEntity.h"

/*
  �ϰ���
*/
class CBarrier : public CLifeEntity
{
public:
  enum emBarrierType
  {
    BAR_WALL  = 1, //ǽ
    BAR_IRON  = 2, //��
    BAR_CLOTH = 3, //��
    BAR_WATER = 4, //ˮ
    BAR_GRASS = 5, //��
    BAR_HOME  = 6, //����
    BAR_COUNT = 5  //������������
  };

  CBarrier();
  CBarrier(emBarrierType emType, CPosition m_pos, int nHP = 1);
  ~CBarrier();

  //��ȡ
  emBarrierType getType();

  void setType(emBarrierType type);

  bool onHitBy(int nDamage);

  void ClearThis();

  void show();

  void SetBarrier(emBarrierType emType, CPosition m_pos, int nHP);

private:
  emBarrierType m_emType;
};

