#include "CTank.h"
#include "GameConst.h"
#include "CGameUI.h"
#include <iostream>
#include <string>
#include "CThread.h"
#include <time.h>

void CTank::init()
{
  //��ǰ�ƶ�����
  m_nMoveDis = 0;
  //�ӵ�����
  m_nCountBullet = 0;
  //����״̬
  bAnimeFlag = false;
  bMoveFlag = false;
  bFrameFlag = false;
  bAnimeDieFlag = false;
  nFrameTime = 0;
  nAnimeFrameNum = 0;
  ::memset(m_aryBulletBuf, 0, sizeof(m_aryBulletBuf));
  /*
  ���ݿ���
  ����ֵ,�˺�,�ƶ��ٶ�,�ӵ��ٶ�
  */
  SetHP(g_aryTankInfo[m_emType][0]); //����ֵ
  m_nPower = g_aryTankInfo[m_emType][1];//�˺�
  m_nMoveSpeed = g_aryTankInfo[m_emType][2];//�ƶ��ٶ�
  m_nBulletSpeed = g_aryTankInfo[m_emType][3];//�ӵ��ٶ�
  m_nMagazine = g_aryTankInfo[m_emType][4];; //Ĭ�ϵ�����
}

/*
  ̹��
*/
CTank::CTank(std::string strTankName,
  emTankType emType, 
  CPosition pos, 
  emTankCamp camp)
  : m_strTankName(strTankName), CLifeEntity(pos, CLifeEntity::LF_TANK, 0)//���๹��
{
  //����
  m_emType = emType;
  //��Ӫ
  m_emCamp = camp;
  //����
  m_emDir = DR_UP;
  //��ʾλ��
  PrevPos = pos;

  //��ʼ������
  init();
  
}

CTank::~CTank()
{
  for (int i = 0; i < 5; i++)
  {
    if (m_aryBulletBuf[i] != nullptr)
    {
      delete m_aryBulletBuf[i];
      m_aryBulletBuf[i] = nullptr;
    }
  }
}

bool CTank::move(emTankDirection emDir)
{
  if (isAlive() == false)
  {
    return false;
  }

  if (m_emTankStatus == STATUS_ENEMYINIT || m_emTankStatus == STATUS_PLAYERINIT || m_emTankStatus == STATUS_DIE)
  {
    return false;
  }

  //����
  /*g_Game->Sound.PlayMoveSound();*/

  //�ƶ�״̬
  bMoveFlag = true;

  //�ٶ�
  m_nMoveDis = m_nMoveSpeed;
  //����
  m_emDir = emDir;
  //�����ϴ�λ��
  PrevPos = m_pos;

  switch (emDir)
  {
  case CTank::DR_UP:
  {
    m_pos.toUp(m_nMoveDis);
  }
    break;
  case CTank::DR_RIGHT:
  {
    m_pos.toRight(m_nMoveDis);
  }
    break;
  case CTank::DR_DOWN:
  {
    m_pos.toDown(m_nMoveDis);
  }
    break;
  case CTank::DR_LEFT:
  {
    m_pos.toLeft(m_nMoveDis);
  }
    break;
  }

  //��ʾ
  show();
  return false;
}

bool CTank::fire()
{
  if (isAlive() == false)
  {
    return false;
  }

  //�жϵ����Ƿ�����
  if (m_nCountBullet < m_nMagazine && m_nCountBullet < MAX_BULLET)
  {
    for (int i = 0; i < 5; i++)
    {
      if (m_aryBulletBuf[i] == nullptr)
      {
        CPosition pos = m_pos;
        //�����ʼ����
        switch (m_emDir)
        {
        case CTank::DR_UP:
          pos.toRight((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_RIGHT:
          pos.toRight(TANK_SIZE);
          pos.toDown((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_DOWN:
          pos.toDown(TANK_SIZE);
          pos.toRight((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        case CTank::DR_LEFT:
          pos.toDown((TANK_SIZE - BULLET_SIZE) / 2);
          break;
        }
        //��Ҳ�������
        if (m_emCamp == CAMP_PLAYER)
        {
          //��������
          g_Game->Sound.PlayFireSound();
        }
        //�����ӵ�
        m_aryBulletBuf[i] = new CBullet(*this, i, pos, m_nBulletSpeed, m_emDir, m_nPower);
        //����++
        m_nCountBullet++;
        //����
        break;
      }

    }
  }

  return false;
}

void CTank::onHitEnemy(CLifeEntity& life)
{
  if (isAlive() == false)
  {
    return;
  }
}

void CTank::onKillEnemy(CLifeEntity & life)
{
  if (isAlive() == false)
  {
    return ;
  }
}

bool CTank::onHitBy(int nDamage)
{
  if (isAlive() == false)
  {
    return false;
  }

  return false;
}

void CTank::show()
{
  //����������Ѳ��궯���Ͳ�����ʾ
  if (isAlive() == false && bAnimeDieFlag)
  {
    return;
  }

  if (bMoveFlag)
  {
    //������ϴ�
    clearPrevPos();
  }

  if (m_emTankStatus == STATUS_NONE)
  {
    //��̹��
    ui->DrawTank(m_pos.getX(), m_pos.getY(), m_emType, m_emDir);
  }
  else if (m_emTankStatus == STATUS_ENEMYINIT || m_emTankStatus == STATUS_PLAYERINIT)
  {
    //��ʼ������
    ui->DrawTankInit(m_pos.getX(), m_pos.getY(), nAnimeFrameNum);

    //֡�л�
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 80)
    {
      nFrameTime = tFrame;
      //���֡�ж�
      if (nAnimeFrameNum < ANIME_INIT_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //�����������
    if (nAnimeFrameNum >= ANIME_INIT_FRAME_NUM)
    {
      //����л�������ģʽ
      if (m_emTankStatus == STATUS_PLAYERINIT)
      {
        setTankStatus(CTank::STATUS_PROTECT, 3000);
      }
      else
      {
        setTankStatus(CTank::STATUS_NONE, 0);
      }
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      bFrameFlag = false;
    }

  }
  else if (m_emTankStatus == STATUS_DIE)
  {
    int nX = m_pos.getX() - TANK_SIZE / 2;
    int nY = m_pos.getY() - TANK_SIZE / 2;

    //��������
    ui->DrawTankDie(nX, nY, nAnimeFrameNum);

    //֡�л�
    clock_t tFrame = clock();
    if (nFrameTime == 0 || tFrame - nFrameTime > 120)
    {
      nFrameTime = tFrame;
      //���֡�ж�
      if (nAnimeFrameNum < ANIME_DIE_FRAME_NUM)
      {
        nAnimeFrameNum++;
      }
    }

    //�����������
    if (nAnimeFrameNum >= ANIME_DIE_FRAME_NUM)
    {
      //���ʬ��
      ui->ClearRect(nX, nY, T_SIZE * 2, T_SIZE * 2);
      //�ָ���ͼ
      ui->DrawMap();
      //���������Ƿ񲥷�
      bAnimeDieFlag = true;
      nAnimeFrameNum = 0;
      nFrameTime = 0;
      bFrameFlag = false;
    }
  }
  else if (m_emTankStatus == STATUS_PROTECT)//����ģʽ
  {
    if (bAnimeFlag == false)
    {
      CThread thread = CThread();
      thread.startTankProtectAnime(this);
    }

    if (bMoveFlag == true)
    {
      clock_t tFrame = clock();

      if (nFrameTime == 0 || tFrame - nFrameTime > 120)
      {
        nFrameTime = tFrame;
        bFrameFlag = !bFrameFlag;
      }

      //��̹��
      ui->DrawTank(m_pos.getX(), m_pos.getY(), m_emType, m_emDir);
      //������Ȧ
      ui->DrawProtect(m_pos.getX(), m_pos.getY(), bFrameFlag);
    }
  }
}

//����ϴ�λ��
void CTank::clearPrevPos()
{
  //��ǰλ�ø��ϴ�λ����ȾͲ����
  if (PrevPos.getX() == m_pos.getX() && PrevPos.getY() == m_pos.getY())
  {
    return;
  }
  else
  {
    ui->ClearRect(PrevPos.getX(), PrevPos.getY(), TANK_SIZE, TANK_SIZE);
  }
}

//�����ǰλ��
void CTank::clearCurPos()
{
    ui->ClearRect(m_pos.getX(), m_pos.getY(), TANK_SIZE, TANK_SIZE);
}

CTank::emTankType CTank::getType()
{
  return m_emType;
}

CTank::emTankCamp CTank::getCamp()
{
  return m_emCamp;
}

CTank::emTankDirection CTank::getDirection()
{
  return m_emDir;
}

int CTank::getMoveSpeed()
{
  return m_nMoveSpeed;
}

int CTank::getBulletSpeed()
{
  return m_nBulletSpeed;
}

std::string CTank::getTankName()
{
  return m_strTankName;
}

void CTank::setTankName(const char * pszName)
{
  m_strTankName = pszName;
}

void CTank::setTankName(std::string strName)
{
  m_strTankName = strName;
}

void CTank::setTankStatus(emTankStatus status, int time)
{
  m_emTankStatus = status;
  m_nStatusTime = time;
}

int CTank::getStatusTime()
{
  return m_nStatusTime;
}

void CTank::toUp()
{
  m_emDir = DR_UP;
}

void CTank::toDown()
{
  m_emDir = DR_DOWN;
}

void CTank::toRight()
{
  m_emDir = DR_RIGHT;
}

void CTank::toLeft()
{
  m_emDir = DR_LEFT;
}

void CTank::toDie()
{
  __super::toDie();
  setTankStatus(CTank::STATUS_DIE, 0);
}

void CTank::revive()
{
  //����״̬
  toAlive();
  //���ݳ�ʼ��
  init();
}

void CTank::create()
{
}
