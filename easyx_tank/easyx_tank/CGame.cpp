#include "CGame.h"
#include "GameConst.h"
#include <iostream>
#include "CRobot.h"
#include <string>
#include <time.h>
#pragma warning(disable:4996)

CGame::CGame(CPlayer & player1, CPlayer & player2) : Player1(player1), Player2(player2)
{
  //��ʼ��buff
  InitBuffer();
  TankArys.container_tank = nullptr;
  BarArys.container_barrier = nullptr;
  //��ǰ�ؿ�
  nLevelNum = 2;
  //�ؿ�����
  if (MapFile.isInit())
  {
    nTotolLevelNum = MapFile.getMapNum();
    int nSpeed = MapFile.getGameSpeed();
    if (nSpeed == 0)
    {
      nSpeed = 5;
    }
    nGameSpeed = nSpeed;
  }
  srand((unsigned int)time(NULL));
}

CGame::~CGame()
{
  //�ϰ�������
  if (BarArys.container_barrier != nullptr)
  {
    delete[] BarArys.container_barrier;
  }
  //̹������
  if (BarArys.container_barrier != nullptr)
  {
    delete[] TankArys.container_tank;
  }
  //Buffer
  for (int i = 0; i < 6; i++)
  {
    if (BufferArys[i] != nullptr)
    {
      delete BufferArys[i];
    }
  }
  //�ͷ�
  if (GameUi != nullptr)
  {
    delete GameUi;
  }
}

bool CGame::Init()
{
  nDieRobotNum = 0;
  isInit = false;
  bGameOverFlag = false;
  bPlayerWinFlag = false;
  
  //��ͼ��ȡ��
  if (MapFile.isInit() == false)
  {
    printf(">>> ��ȡ��ͼ�ļ�ʧ��...\r\n");
    return false;
  }
  return true;
}

void CGame::InitData()
{
  //��ʼ���ϰ���
  InitBarrier();
  //��ʼ�����
  InitPlayer();
  //��ʼ��������
  InitRobot();
  //��ʼ�����
  isInit = true;
  bGameOverFlag = false;
}

bool CGame::isGameOver()
{
  return bGameOverFlag;
}

void CGame::GameOver()
{
  bGameOverFlag = true;
  std::cout << "GameOver!" << std::endl;
}

bool CGame::isPlayerWin()
{
  return bPlayerWinFlag;
}

void CGame::ReleaseData()
{
  //����������
  for (int i = 0; i < 5; i++)
  {
    //������
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    if (robot != nullptr)
    {
      delete robot;
      TankArys.container_tank[2 + i] = nullptr;
    }
  }

  if (emGameMode == MODE_SINGLE)
  {
    Player1.toDie();
  }
  else if (emGameMode == MODE_DOUBLE)
  {
    Player1.toDie();
    Player2.toDie();
  }
}

void CGame::ShowGameOver()
{
  int x = (ui->getBattleWidth() - T_SIZE * 2) / 2;
  int y = (ui->getBattleHeight() - T_SIZE) / 2;
  ui->DrawGameOver(x, y);
}

void CGame::MotionAllRobot()
{
  if (isGameOver()) return;

  for (int i = 0; i < 5; i++)
  {
    //������
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];

    //�����˴��
    if (robot->isAlive())
    {
      //���û����˵��˶�����
      robot->motion();
    }
  }
}

/*
  ˢ������̹��
*/
void CGame::FlushAllTank()
{
  //��Ϸ��������ʾ
  if (isGameOver()) return;

  int nTankCount = TankArys.nLength;
  //̹��
  CTank **ppTank = TankArys.container_tank;
  //����̹��
  for (int i = 0; i < nTankCount; i++)
  {
    //̹��
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    tank->show();
  }
}

void CGame::FlushAllBullet()
{
  //��Ϸ��������ʾ
  if (isGameOver()) return;
  //̹������
  int nTankCount = TankArys.nLength;
  //̹��
  CTank **ppTank = TankArys.container_tank;
  //����̹��
  for (int i = 0; i < nTankCount; i++)
  {
    //̹��
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    //���������ӵ�
    for (int i = 0; i < 5; i++)
    {
      CBullet *bul = tank->m_aryBulletBuf[i];
      if (bul != nullptr)
      {
        bul->fly();
      }
    }
  }
  
}

void CGame::FlushAllBuff()
{
  for (int i = 0; i < 6; i++)
  {
    CBuffer* buff = BufferArys[i];
    if (buff != nullptr && buff->isShow())
    {
      //��ʾ
      buff->show();
    }
  }
}

void CGame::StopAllRobot(int nTime)
{
  for (int i = 0; i < 5; i++)
  {
    //������
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    //����ж�
    if (robot->isAlive())
    {
      //��ͣ������
      robot->SetStopTime(nTime);
    }
    
  }
}

void CGame::GenerateBuff()
{
  //ȫ���ر�
  for (int i = 0; i < 6; i++)
  {
    CBuffer* buff = BufferArys[i];
    if (buff != nullptr)
    {
      if (buff->isShow())
      {
        //�����ʾ
        buff->clear();
        //������ʾ
        buff->setVisible(false);
      }
    }
  }

  int x = rand() % (ui->getBattleWidth() - TANK_SIZE);
  int y = rand() % (ui->getBattleHeight() - TANK_SIZE);
  int option = rand() % 6;
  BufferArys[option]->setPos(x, y);
  BufferArys[option]->setVisible(true);
  //printf(">>> �콵buff [X = %d,Y = %d]\r\n", x, y);
}

void CGame::KillAllRobot()
{
  //������Ч
  g_Game->Sound.PlayTankCrackSound();

  for (int i = 0; i < 5; i++)
  {
    //������
    CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];
    //����ж�
    if (robot->isAlive())
    {
      //����
      robot->toDie();
    }
  }
}

void CGame::ToIronHome()
{
  //�ϰ���
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  int hX = m_HomePos.getX();
  int hY = m_HomePos.getY();

  //����
  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] != nullptr)
    {
      //��������
      if (pBar[i]->getType() == CBarrier::BAR_HOME) continue;

      //����
      CPosition barPos = pBar[i]->m_pos;

      //�����Աߵ�Χǽ
      if (barPos.getX() >= (hX - TANK_SIZE) &&
        barPos.getX() <= (hX + TANK_SIZE * 2) &&
        barPos.getY() >= (hY - TANK_SIZE) &&
        barPos.getY() <= (hY + TANK_SIZE * 2))
      {
        pBar[i]->SetHP(99);
        pBar[i]->setType(CBarrier::BAR_IRON);
        pBar[i]->toAlive();
      }
    }
  }

  //����ͼ
  ui->DrawMap();
}

void CGame::InitBarrier()
{
  //���˳����������
  int nEmPosCount = 0;
  //�ϰ�������
  int nBarrierCount = 0;
  //xy����
  int x = 0;
  int y = 0;

  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      //��ȡ����
      int nType = g_CurMapData[i][j];

      //���˳�����
      if (nType == 'E')
      {
        if (nEmPosCount < 3)
        {
          x = j * BARRIER_SIZE;
          y = i * BARRIER_SIZE;
          EnemyPosArys[nEmPosCount++].setPos(x, y);
        }
      }
      else if (nType != 0)
      {
        nBarrierCount++;
      }
    }
  }

  //����ռ�
  if (BarArys.container_barrier == nullptr)
  {
    BarArys.container_barrier = new CBarrier *[nBarrierCount] { 0 };
  }
  else
  {
    CBarrier **pBar = BarArys.container_barrier;
    int nCount = BarArys.nLength;

    for (int i = 0; i < nCount; i++)
    {
      if (pBar[i] != nullptr)
      {
        delete pBar[i];
      }
    }
    delete[] BarArys.container_barrier;
    BarArys.container_barrier = new CBarrier *[nBarrierCount] { 0 };
  }
  BarArys.nLength = nBarrierCount;

  nBarrierCount = 0;
  CBarrier **pBar = BarArys.container_barrier;

  //���ݶ�ȡ
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      //��ȡ����
      int nType = g_CurMapData[i][j];
      //XY ��Ե�յؿռ� + 1
      x = j * BARRIER_SIZE;
      y = i * BARRIER_SIZE;

      switch (nType)
      {
      case 1:
      {
        //���ǽ
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_WALL, { x, y }, WALL_LIFE);
        break;
      }
      case 2:
      {
        //�����
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_IRON, { x, y }, 999);
        break;
      }
      case 3:
      {
        //��Ӳ�
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_CLOTH, { x, y }, 2);
        break;
      }
      case 4:
      {
        //���ˮ
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_WATER, { x, y }, 2);
        break;
      }
      case 5:
      {
        //��Ӳ�
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_GRASS, { x, y }, 2);
        break;
      }
      case 6:
      {
        //��ӻ���
        pBar[nBarrierCount++] = new CBarrier(CBarrier::BAR_HOME, { x, y }, 1);
        m_HomePos.setPos(x, y);
        break;
      }
      }//switch

    }//forj
  }//fori
}

void CGame::InitPlayer()
{
  if (emGameMode == MODE_SINGLE)
  {
    //��ʼ������
    Player1.init();

    //̹������
    int nLength = 7;
    //�ռ�
    if (TankArys.container_tank == nullptr)
    {
      TankArys.container_tank = new CTank *[nLength] { 0 };
    }
    //��һ����Player1��̹��
    TankArys.container_tank[0] = &Player1;

    TankArys.nLength = 1;
    nTankNum = nLength;
  }
  else if(emGameMode == MODE_DOUBLE)
  {
    //��ʼ������
    Player1.init();
    Player2.init();

    //̹������
    int nLength = 7;
    //�ռ�
    if (TankArys.container_tank == nullptr)
    {
      TankArys.container_tank = new CTank *[nLength] { 0 };
    }
    //��һ����Player1��̹��
    TankArys.container_tank[0] = &Player1;
    //�ڶ�����Player2��̹��
    TankArys.container_tank[1] = &Player2;

    TankArys.nLength = 2;
    nTankNum = nLength;
  }

  nCurRobotNum = 0;
}

/*
  ��ʼ���������,��ʼ��ʱ��Ϊ����״̬
  ����Ϸ������,ÿһ��ʱ�������û����˸����
*/
void CGame::InitRobot()
{
  //��ʼ������
  std::string str = "Robot";
  //��һ��
  (TankArys.container_tank[2] = new CRobot(str, CTank::TANK3, EnemyPosArys[0], CTank::CAMP_ENEMY))->create();
  //�ڶ���
  (TankArys.container_tank[3] = new CRobot(str, CTank::TANK4, EnemyPosArys[1], CTank::CAMP_ENEMY))->create();
  //������
  (TankArys.container_tank[4] = new CRobot(str, CTank::TANK5, EnemyPosArys[2], CTank::CAMP_ENEMY))->create();
  //���ĸ�
  (TankArys.container_tank[5] = new CRobot(str, CTank::TANK6, EnemyPosArys[0], CTank::CAMP_ENEMY))->create();
  //�����
  (TankArys.container_tank[6] = new CRobot(str, CTank::TANK7, EnemyPosArys[1], CTank::CAMP_ENEMY))->create();
  //������Ҽ������ʼRobot
  TankArys.nLength = 7;
}

void CGame::InitBuffer()
{
  //���buff
  for (int i = 0; i < 6; i++)
  {
    //�������buff
    BufferArys[i] = new CBuffer((CBuffer::emBufferType)i);
  }
}

bool CGame::LoadMapData()
{
  //��ȡ��ͼ����
  return MapFile.getMap(nLevelNum, g_CurMapData);
}

/*
  ��ӻ�����
*/
void CGame::AddRobot()
{
  if (isGameOver()) return;

  //�����˸���������ܳ����޶�����
  if (nCurRobotNum < ROBOT_NUMBER)
  {
    for (int i = 0; i < 5; i++)
    {
      //������
      CRobot *robot = (CRobot *)TankArys.container_tank[2 + i];

      //�ж�λ���Ƿ���Ը���
      if (g_Game->CheckTankCrash(*robot, robot->m_pos))
      {
        //�����Ծ���һ��
        continue;
      }

      //�������,�͸���
      if (robot->isAlive() == false)
      {
        char szBuf[50] = { 0 };
        //ƴ��������
        std::string strName = "Robot";
        //ƴ��
        strName = strName + ::itoa(nCurRobotNum + 1, szBuf, 10);
        //����������
        robot->setTankName(strName);
        //���������
        robot->revive();
        //��ǰ����������+1
        nCurRobotNum++;
        //֪ͨ
        printf("[ %s ] ������ս��!\r\n", strName.c_str());
        break;
      }

    }
      
  }

}

void CGame::PlayerWin()
{
  //�����ؿ�
  int level = nLevelNum + 1;
  if (level <= nTotolLevelNum)
  {
    nLevelNum = level;
  }

  bPlayerWinFlag = true;
  MessageBox(NULL, _T("You Win!"), _T("Game"), MB_OK);
}

void CGame::SetGameMode(emMode GameMode)
{
  emGameMode = GameMode;
}

/*
  ��ʼ
*/
void CGame::start()
{
  //��������
  Sound.PlayStartSound();
  //������Ϸ��ѭ��
  GameLoop();
}

//������ײ���
bool checkRectCrash(int x, int y, int w, int h, 
  int x2, int y2, int w2, int h2)
{
  if (x < x2 + w2 &&
    x + w >= x2 &&
    y < y2 + h2 &&
    h + y >= y2
    )
  {
    return true;
  }
  return false;
}

/*
  ̹����ײ���
*/
bool CGame::CheckTankCrash(CTank& refTank, CPosition pos)
{
  //��Ե��ײ���
  if ((pos.getX() + TANK_SIZE) >= ui->getBattleWidth() || (pos.getY() + TANK_SIZE) >= ui->getBattleHeight())
  {
    return true;
  }

  //buffУ��
  if (refTank.getCamp() == CTank::CAMP_PLAYER)
  {
    for (int i = 0; i < 6; i++)
    {
      CBuffer *buff = BufferArys[i];
      if (buff != nullptr && buff->isShow())
      {
        //��buff
        if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, buff->getX(), buff->getY(), 30, 28))
        {
          //���buff
          buff->onTouch(refTank);
        }
      }
    }
  }

  //�ϰ�����ײ���
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] != nullptr && pBar[i]->isAlive())
    {
      //��ȡ�ϰ�������
      CBarrier::emBarrierType emType = pBar[i]->getType();

      //�����ݺͲ�
      if (emType != CBarrier::BAR_GRASS && emType != CBarrier::BAR_CLOTH)
      {
        CPosition barPos = pBar[i]->m_pos;

        //size
        int nBarW = BARRIER_SIZE;
        int nBarH = BARRIER_SIZE;

        //��С�ж�
        if (emType == CBarrier::BAR_HOME)
        {
          nBarW = BARRIER_SIZE * 2;
          nBarH = BARRIER_SIZE * 2;
        }

        //������ײ���
        if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          return true;
        }
      }
    }

  }

  //̹����ײ���
  CTank **ppTank = TankArys.container_tank;
  nCount = TankArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    //̹��
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    if (tank->isAlive() == false) continue;

    CPosition tankPos = tank->m_pos;

    //��ȡ�Ƚ�̹������
    std::string curName = tank->getTankName();

    //�ų��Լ�
    if (curName.compare(refTank.getTankName()) != 0)
    {
      //̹��λ�ü��
      if (checkRectCrash(pos.getX(), pos.getY(), TANK_SIZE, TANK_SIZE, tankPos.getX(), tankPos.getY(), TANK_SIZE, TANK_SIZE))
      {
        //printf("[ %s ] : �ɶ�!�����ĵ��ҵ�·,��Ҫɱ�� [ %s ]!\r\n", refTank.getTankName().c_str(), curName.c_str());
        return true;
      }
    }
  }

  return false;
}

/*
  �ӵ���ײ
*/
bool CGame::CheckBulletCrash(CBullet& bullet)
{
  //��Ե��ײ���
  if (bullet.getX() == 0 || bullet.getY() == 0 || (bullet.getX() + BULLET_SIZE) >= ui->getBattleWidth() || (bullet.getY() + BULLET_SIZE) >= ui->getBattleHeight())
  {
    return true;
  }
  
  bool ret = false;

  //�ϰ�����ײ���
  CBarrier **pBar = BarArys.container_barrier;
  int nCount = BarArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    if (pBar[i] == nullptr) continue;
    if (pBar[i]->isAlive() == false) continue;

    //��ȡ�ϰ�������
    CBarrier::emBarrierType emType = pBar[i]->getType();

    //�����ݺͲ�
    if (emType != CBarrier::BAR_GRASS && emType != CBarrier::BAR_CLOTH && emType != CBarrier::BAR_WATER)
    {
      CPosition barPos = pBar[i]->m_pos;

      int nBarW = BARRIER_SIZE;
      int nBarH = BARRIER_SIZE;

      //����
      if (emType == CBarrier::BAR_HOME)
      {
        nBarW = BARRIER_SIZE * 2;
        nBarH = BARRIER_SIZE * 2;

        //������ײ���
        if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          //��֪̹�˻��е���
          bullet.m_tank.onHitEnemy(*pBar[i]);
          //���ñ����лص�����
          pBar[i]->onHitBy(bullet.getPower());
          //����
          return true;
        }
      }
      else
      {
        //������ײ���
        if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, barPos.getX(), barPos.getY(), nBarW, nBarH))
        {
          //��֪̹�˻��е���
          bullet.m_tank.onHitEnemy(*pBar[i]);
          //���ñ����лص�����
          if (pBar[i]->onHitBy(bullet.getPower()) != false)
          {
            //��֪��ɱ
            bullet.m_tank.onKillEnemy(*pBar[i]);
          }
          //�ӵ��ص�
          bullet.onCrash(*pBar[i]);
          //״̬
          ret = true;
        }
      }
      
    }

  }

  //̹����ײ���
  CTank **ppTank = TankArys.container_tank;
  nCount = TankArys.nLength;

  for (int i = 0; i < nCount; i++)
  {
    //̹��
    CTank *tank = ppTank[i];
    if (tank == nullptr) continue;
    if (tank->isAlive() == false) continue;

    CPosition tankPos = tank->m_pos;

    //̹����Ӫ
    CTank::emTankCamp tkCamp = bullet.m_tank.getCamp();
    CTank::emTankCamp tCamp = tank->getCamp();

    if (tkCamp != tCamp)//��Ӫ��ͬ����
    {
      //̹��λ�ü��
      if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, tankPos.getX(), tankPos.getY(), TANK_SIZE, TANK_SIZE))
      {
        //��֪̹�˻��е���
        bullet.m_tank.onHitEnemy(*tank);
        //���ñ����лص�����
        if (tank->onHitBy(bullet.getPower()) != false)
        {
          //��֪��ɱ
          bullet.m_tank.onKillEnemy(*tank);
        }
        //�ӵ��ص�
        bullet.onCrash(*tank);
        //״̬
        ret = true;
      }

      //�ӵ���ײ���
      for (int j = 0; j < 5; j++)
      {
        CBullet *bul = tank->m_aryBulletBuf[j];
        if (bul != nullptr)
        {
          //̹��λ�ü��
          if (checkRectCrash(bullet.getX(), bullet.getY(), BULLET_SIZE, BULLET_SIZE, bul->getX(), bul->getY(), BULLET_SIZE, BULLET_SIZE))
          {
            //״̬
            ret = true;
          }
        }
      }

    }

  }

  return ret;
}