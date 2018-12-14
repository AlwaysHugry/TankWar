#include "CBuffer.h"
#include "GameConst.h"

CBuffer::CBuffer(emBufferType type)
{
  setPos(0, 0);
  m_emBufferType = type;
  m_bShowFlag = false;
}

CBuffer::~CBuffer()
{

}

void CBuffer::show()
{
  if (m_bShowFlag)
  {
    ui->DrawBuffer(getX(), getY(), m_emBufferType);
  }
}

void CBuffer::clear()
{
  ui->ClearRect(getX(), getY(), 30, 28);
  ui->DrawMap();
}

void CBuffer::onTouch(CTank &tank)
{
  //��������
  g_Game->Sound.PlayPropSound();

  switch (m_emBufferType)
  {
  case CBuffer::TYPE_ADDLIFE: //�����������
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //���������
      CPlayer *player = (CPlayer *) &tank;

      //���������ֵ
      player->addLifeNum(1);
    }
  }
    break;
  case CBuffer::TYPE_STOPTIME://ֹͣ������
  {
    //��ͣ���л����˻10����
    g_Game->StopAllRobot(TYPE_STOPROBOT_TIME);
  }
    break;
  case CBuffer::TYPE_IRONHOME://�ұ���
  {
    //�ұ���
    g_Game->ToIronHome();
  }
    break;
  case CBuffer::TYPE_BOMB:    //ɱ�����л��ŵĻ�����
  {
    //ɱ�����л�����
    g_Game->KillAllRobot();
  }
    break;
  case CBuffer::TYPE_ADDBULLET://��ӵ���
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      CPlayer *player = (CPlayer *)&tank;
      //��ӵ���
      player->addMagazine(1);
      //�����ӵ��ٶ�
      player->setBulletSpeed(4);
    }
  }
    break;
  case CBuffer::TYPE_PROTECT: //������
  {
    if (tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //��ӱ�����
      tank.setTankStatus(CTank::STATUS_PROTECT, TYPE_PROTECT_TIME);
    }
  }
    break;
  }

  //��������
  setVisible(false);
  //����Լ�
  this->clear();
}

void CBuffer::setPos(int x, int y)
{
  __super::setPos(x, y);
}

void CBuffer::setVisible(bool bFlag)
{
  m_bShowFlag = bFlag;
}

bool CBuffer::isShow()
{
  return m_bShowFlag;
}
