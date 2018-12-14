#include "CPlayer.h"
#include "GameConst.h"
#include <iostream>

//����
CPlayer::CPlayer(const char *name, CPosition pos,int nLifeNum)
  : m_nLifeNum(nLifeNum), CTank(name, CTank::TANK1, pos, CTank::CAMP_PLAYER)
{
  //��ʼ����
  init_pos = pos;
  //��ʼ����ֵ
  init_lifenum = m_nLifeNum;
  //��ʼ����������
  init();
}

CPlayer::~CPlayer()
{
  
}

void CPlayer::init()
{
  //��ʼ������
  __super::init();
  //����
  m_nScore = 0;
  //ɱ����
  m_nKillNum = 0;
  //����״̬
  setTankStatus(CTank::STATUS_PLAYERINIT, 0);
  //��ʼ����ֵ
  m_nLifeNum = init_lifenum;
  //��ʼ����
  m_pos = init_pos;
  //���÷���
  m_emDir = CTank::DR_UP;
  //���
  toAlive();
}

bool CPlayer::onHitBy(int nDamage)
{
  if (isAlive() == false)
  {
    return false;
  }

  if (m_emTankStatus != STATUS_PROTECT && SubHp(nDamage) == false)
  {
    //����
    g_Game->Sound.PlayPlayerCrackSound();
    //�����ʾ
    g_Game->GameUi->ClearRect(m_pos.getX(), m_pos.getY(), TANK_SIZE, TANK_SIZE);
    //��������
    toDie();
    //������--
    m_nLifeNum--;
    if (m_nLifeNum > 0)
    {
      //����
      revive();
    }
    else
    {
      //��Ϸ����
      g_Game->GameOver();
    }
    return true;
  }

  return false;
}

//��ɱ���˵���
void CPlayer::onKillEnemy(CLifeEntity & life)
{
  if (isAlive() == false)
  {
    return ;
  }

  CLifeEntity::emLifeType lfType = life.GetLifeType();
  if (lfType == CLifeEntity::LF_BARRIER)
  {
    //�ϰ���
    CBarrier *bar = (CBarrier *)&life;
    CBarrier::emBarrierType barType = bar->getType();

    switch (barType)
    {
    case CBarrier::BAR_WALL:
      //printf("���[%s] : ����,ȥ���ǽ��,�ҵ��ҵ�·!\r\n", m_strTankName.c_str());
      break;
    case CBarrier::BAR_IRON:
      printf("���[%s] : �����Ӳ��,�������ɵ���!\r\n", m_strTankName.c_str());
      break;
    case CBarrier::BAR_HOME:
      printf("���[%s] : ���类���˴��,���������Լ���!\r\n", m_strTankName.c_str());
      break;
    }
  }
  else if (lfType == CLifeEntity::LF_TANK)
  {
    //̹��
    CTank *tank = (CTank *)&life;
    //��ȡ��Ӫ
    //printf("���[%s] : С������,��������,�Ҹɵ������ǵ�[%s]!!\r\n", m_strTankName.c_str(), tank->getTankName().c_str());
    //�ӷ�
    m_nScore = m_nScore + 100;
    //ɱ����
    addKillNum(1);
  }
}

void CPlayer::revive()
{
  __super::revive();
  //״̬
  setTankStatus(CTank::STATUS_PLAYERINIT, 0);
  //��ʼ����
  m_pos = init_pos;
}

void CPlayer::addLifeNum(int num)
{
  m_nLifeNum = m_nLifeNum + num;
}

void CPlayer::addMagazine(int num)
{
  int nMag = m_nMagazine + num;;
  if (nMag < MAX_BULLET)
  {
    m_nMagazine = nMag;
  }
}

void CPlayer::setBulletSpeed(int speed)
{
  m_nBulletSpeed = speed;
}

void CPlayer::addScore(int nScore)
{
  m_nScore = m_nScore + nScore;
}

void CPlayer::addKillNum(int nKillNum)
{
  m_nKillNum = m_nKillNum + nKillNum;
}

int CPlayer::getScore()
{
  return m_nScore;
}

int CPlayer::getKillNum()
{
  return m_nKillNum;
}

void CPlayer::onDown()
{
  if (isAlive() == false)
  {
    return ;
  }

  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toDown();

  if (pos.toDown(nSpeed))
  {
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_DOWN);
    }
  }
}

void CPlayer::onUp()
{
  if (isAlive() == false)
  {
    return ;
  }

  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toUp();

  if (pos.toUp(nSpeed))
  {
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_UP);
    }
  }
}

void CPlayer::onRight()
{
  if (isAlive() == false)
  {
    return ;
  }

  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toRight();

  if (pos.toRight(nSpeed))
  {
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_RIGHT);
    }
  }
}

void CPlayer::onLeft()
{
  if (isAlive() == false)
  {
    return;
  }

  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toLeft();

  if (pos.toLeft(nSpeed))
  {
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_LEFT);
    }
  }
}

void CPlayer::onFire()
{
  //����
  fire();
}
