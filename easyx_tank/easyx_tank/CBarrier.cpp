#include "CBarrier.h"
#include <iostream>
#include "GameConst.h"

CBarrier::CBarrier(emBarrierType emType, CPosition pos, int nHP)
  : m_emType(emType), CLifeEntity(pos, CLifeEntity::LF_BARRIER, nHP)
{
}

//��ȡ����
CBarrier::emBarrierType CBarrier::getType()
{
  return m_emType;
}

void CBarrier::setType(emBarrierType type)
{
  m_emType = type;
}

bool CBarrier::onHitBy(int nDamage)
{

  if (SubHp(nDamage) == false)
  {
    if (getType() == CBarrier::BAR_HOME)
    {
      //�����ʾ
      ui->DrawHomeBaseDie(m_pos.getX(), m_pos.getY());
      printf("[�ϳ�] : ��~,������Ⱥ����!!\r\n");
      g_Game->ShowGameOver();
      g_Game->Sound.PlayPlayerCrackSound();
      ui->Wait(1000);
      g_Game->GameOver();
    }
    else
    {
      //�����ʾ
      ClearThis();
    }

    //��������
    toDie();
    return true;
  }
  else
  {
    show();
    ui->flush();
  }

  return false;
}

void CBarrier::ClearThis()
{
  ui->ClearRect(m_pos.getX(), m_pos.getY(), BARRIER_SIZE, BARRIER_SIZE);
}

void CBarrier::show()
{
  ui->DrawElement(m_pos.getX(), m_pos.getY(), m_emType);
}

//��������
void CBarrier::SetBarrier(emBarrierType emType, CPosition pos, int nHP)
{
  m_emType = emType;
  m_pos = pos;
  SetHP(nHP);
  m_emType = emType;
  SetLifeType(CLifeEntity::LF_BARRIER);
}

CBarrier::CBarrier() : CLifeEntity({}, CLifeEntity::LF_BARRIER, 1)
{
}

CBarrier::~CBarrier()
{
}
