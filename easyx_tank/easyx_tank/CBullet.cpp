#include "CBullet.h"
#include "CTank.h"
#include "GameConst.h"
#include <time.h>

CBullet::CBullet(CTank& tank, int nId, CPosition pos, int nSpeed, int nDir, int nPower)
  : m_tank(tank), m_nId(nId), m_nSpeed(nSpeed), m_nDir(nDir), m_nPower(nPower), CPosition(pos)
{
  if (tank.getCamp() == CTank::CAMP_ENEMY)
  {
    m_nType = 1;
  }
  else if (tank.getCamp() == CTank::CAMP_PLAYER)
  {
    m_nType = 0;
  }
  //��ʾ����
  PrevPos.setPos(getX(), getY());
  //��ը״̬
  isBoom = false;
  //���״̬
  isAlive = true;
  //����״̬
  bSoundFlag = false;
  nAnimeFrameNum = 0;
  nFrameTime = 0;
}

CBullet::~CBullet()
{
}

bool CBullet::move(int nDistance)
{
  if (isBoom == true)
  {
    return false;
  }

  bool ret = false;

  PrevPos = *this;

  switch (m_nDir)
  {
  case 0://DR_UP,
  {
    ret = toUp(nDistance);
    break;
  }
  case 1://DR_DOWN
  {
    ret = toDown(nDistance);
    break;
  }
  case 2://DR_LEFT
  {
    ret = toLeft(nDistance);
    break;
  }
  case 3:// DR_RIGHT
  {
    ret = toRight(nDistance);
    break;
  }
  }

  show();
  return ret;
}

void CBullet::onDie()
{
  if (bSoundFlag == false)
  {
    bSoundFlag = true;
    if (m_tank.getCamp() == CTank::CAMP_PLAYER)
    {
      //�����ӵ�����������
      g_Game->Sound.PlayBulletCrackSound();
    }
    
  }
  
  //��¼��ըǰ����
  //int nX = getX() - (T_SIZE - BULLET_SIZE) / 2;
  //int nY = getY() - (T_SIZE - BULLET_SIZE) / 2;
  //ui->GetRect(nX, nY, T_SIZE, T_SIZE);

  //������ʶ
  isBoom = true;
}

void CBullet::onCrash(CLifeEntity entity)
{
}

void CBullet::show()
{
  if (isAlive && isBoom == false)
  {
    //����ϴ��ӵ��ۼ�
    clearPrevPos();
    //���ӵ�
    ui->DrawBullet(getX(), getY(), m_nDir);
  }
  
  if (isBoom == true)
  {
    int nX = getX() - (T_SIZE - BULLET_SIZE) / 2;
    int nY = getY() - (T_SIZE - BULLET_SIZE) / 2;

    //
    //��������
    ui->DrawBulletBoom(nX, nY, nAnimeFrameNum);

    //֡�л�
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 80)
    {
      nFrameTime = tFrame;
      //���֡�ж�
      if (nAnimeFrameNum < ANIME_BULLET_BOOM_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //�����������
    if (nAnimeFrameNum >= ANIME_BULLET_BOOM_FRAME_NUM)
    {
      //��ԭ����
      //ui->RestoreRect(nX, nY);
      ui->ClearRect(nX, nY, T_SIZE, T_SIZE);
      //����ͼ
      ui->DrawMap();
      //���������Ƿ񲥷�
      isBoom = false;
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      //�ӵ�����--
      m_tank.m_nCountBullet--;
      //��null
      m_tank.m_aryBulletBuf[m_nId] = nullptr;
      //���״̬
      isAlive = false;
      //ɾ������
      delete this;
    }
    
  }
}

//����ϴ�λ��
void CBullet::clearPrevPos()
{
  //��ǰλ�ø��ϴ�λ����ȾͲ����
  if (PrevPos.getX() == getX() && PrevPos.getY() == getY())
  {
    return;
  }
  else
  {
    ui->ClearRect(PrevPos.getX(), PrevPos.getY(), BULLET_SIZE, BULLET_SIZE);
  }
}

//�����ǰλ��
void CBullet::clearCurPos()
{
  ui->ClearRect(getX(), getY(), BULLET_SIZE, BULLET_SIZE);
}

void CBullet::fly()
{
  //��ըʱֹͣ����
  if (isBoom == true)
  {
    //��ʾ����
    show();
    return;
  }

  //�ٶ�����
  CPosition pos = *this;

  bool ret = false;

  switch (m_nDir)
  {
  case 0://DR_UP,
  {
    ret = pos.toUp(m_nSpeed);
    break;
  }
  case 1://DR_DOWN
  {
    ret = pos.toDown(m_nSpeed);
    break;
  }
  case 2://DR_LEFT
  {
    ret = pos.toLeft(m_nSpeed);
    break;
  }
  case 3:// DR_RIGHT
  {
    ret = pos.toRight(m_nSpeed);
    break;
  }
  }

  if (g_Game->CheckBulletCrash(*this))
  {
    //������������
    onDie();
    return;
  }

  move(m_nSpeed);
}

int CBullet::getDirection()
{
  return m_nDir;
}

int CBullet::getSpeed()
{
  return m_nSpeed;
}

int CBullet::getPower()
{
  return m_nPower;
}

int CBullet::getId()
{
  return m_nId;
}

int CBullet::getType()
{
  return m_nType;
}
