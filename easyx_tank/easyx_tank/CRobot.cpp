#include "CRobot.h"
#include <iostream>
#include "GameConst.h"
#include <time.h>

CRobot::CRobot(std::string strTankName, emTankType emType, CPosition pos, emTankCamp camp) : CTank(strTankName, emType, pos, camp)
{
  //��ʼ����
  init_pos = pos;
}

CRobot::~CRobot()
{
}

void CRobot::init()
{
  //��ʼ������
  __super::init();
  //����״̬
  setTankStatus(CTank::STATUS_ENEMYINIT, 0);
  //λ�ø�λ
  m_pos = init_pos;
  //ʱ��
  m_nStopTime = 0;
  //��ʼʱ��
  startTime = 0;
}

//����
void CRobot::revive()
{
  //���
  __super::toAlive();
  //��״̬
  init();
}

bool CRobot::moveLeft()
{
  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toLeft();

  if (pos.toLeft(nSpeed))
  {
    if (pos.getX() <= 0)
    {
      return false;
    }
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_LEFT);
      return true;
    }
  }
  return false;
}

bool CRobot::moveDown()
{
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
      return true;
    }
  }
  return false;
}

bool CRobot::moveUp()
{
  //��ȡ�ٶ�
  int nSpeed = getMoveSpeed();
  CPosition pos = m_pos;

  //�ı䷽��
  toUp();

  if (pos.toUp(nSpeed))
  {
    if (pos.getY() <= 0)
    {
      return false;
    }
    //��ײ���
    if (g_Game->CheckTankCrash(*this, pos) == false)
    {
      move(CTank::DR_UP);
      return true;
    }
  }
  return false;
}

bool CRobot::moveRight()
{

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
      return true;
    }
  }
  return false;
}

bool CRobot::onHitBy(int nDamage)
{
  if (SubHp(nDamage) == false)
  {
    //����
    g_Game->Sound.PlayTankCrackSound();
    //�����ʾ
    clearCurPos();
    //��������
    toDie();
    return true;
  }
  return false;
}

void CRobot::create()
{
  bAnimeDieFlag = true;
  __super::toDie();
}

void CRobot::onKillEnemy(CLifeEntity & life)
{
}

void CRobot::motion()
{
  //������ֹͣ����
  if (m_nStopTime > 0)
  {
    if (startTime == 0)
    {
      startTime = clock();
    }
    clock_t endTime = clock();
    if (endTime - startTime < m_nStopTime)
    {
      return;
    }
    else
    {
      m_nStopTime = 0;
      startTime = 0;
    }
  }

  int nProb = rand() % 200;

  //��;ת��ļ��� %2
  if (nProb <= 4)
  {
    m_emDir = (emTankDirection)(rand() % 4);
  }

  switch (m_emDir)
  {
  case CTank::DR_UP:
  {
    if (moveUp() == false)
    {
      if (nProb < 15)
      {
        m_emDir = (emTankDirection)(2 + rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_DOWN:
  {
    if (moveDown() == false)
    {
      if (nProb < 15)
      {
        m_emDir = (emTankDirection)(2 + rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_LEFT:
  {
    if (moveLeft() == false)
    {
      if (nProb < 20)
      {
        m_emDir = (emTankDirection)(rand() % 2);
      }
    }
  }
    break;
  case CTank::DR_RIGHT:
  {
    if (moveRight() == false)
    {
      if (nProb < 20)
      {
        m_emDir = (emTankDirection)(rand() % 2);
      }
    }
  }
    break;
  }

  //����ļ���
  if (nProb < ENEMY_LEVEL)
  {
    fire();
  }
}

void CRobot::SetStopTime(int nTime)
{
  m_nStopTime = nTime;
}

void CRobot::toDie()
{
  __super::toDie();
  //��������������
  g_Game->nDieRobotNum++;
  //���ʤ��
  if (g_Game->nDieRobotNum >= ROBOT_NUMBER)
  {
    std::cout << "���ʤ��!\r\n" << std::endl;
    ui->Wait(1000);
    g_Game->PlayerWin();
  }
}
