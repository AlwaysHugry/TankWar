#pragma once
#include "CLifeEntity.h"
#include <string>
#include "CBullet.h"

//��󵯼���
#define MAX_BULLET 5

class CTank : public CLifeEntity
{
public:
  enum emTankType
  {
    TANK1,
    TANK2,
    TANK3,
    TANK4,
    TANK5,
    TANK6,
    TANK7,
    TANK_COUNT = 7
  };

  enum emTankCamp
  {
    CAMP_PLAYER, //���
    CAMP_ENEMY   //����
  };

  enum emTankStatus
  {
    STATUS_NONE = 0,        //��״̬
    STATUS_PLAYERINIT = 5,  //��ҳ�ʼ��״̬
    STATUS_ENEMYINIT,       //���˳�ʼ��״̬
    STATUS_PROTECT,         //̹�˱���״̬
    STATUS_DIE              //����״̬
  };

  enum emTankDirection
  {
    DR_UP,
    DR_DOWN,
    DR_LEFT,
    DR_RIGHT
  };
public:
  CTank(std::string m_strTankName, emTankType emType, CPosition pos, emTankCamp camp = emTankCamp::CAMP_ENEMY);
  ~CTank();

  //��ʼ������
  virtual void init();

  //�ƶ�
  bool move(emTankDirection emDir);

  //����
  bool fire();

  //���е����¼�
  virtual void onHitEnemy(CLifeEntity& life);

  //��ɱ����
  virtual void onKillEnemy(CLifeEntity& life);

  //������
  virtual bool onHitBy(int nDamage);

  //��ʾ
  virtual void show();

  //����ϴ�ͼ��
  void clearPrevPos();

  //�����ǰͼ��
  void clearCurPos();

  //����������

  //geter and seter

  //��ȡ����
  emTankType getType();

  //��ȡ��Ӫ
  emTankCamp getCamp();

  //��ȡ����
  emTankDirection getDirection();

  //��ȡ�ƶ��ٶ�
  int getMoveSpeed();
  
  //��ȡ�ӵ��ٶ�
  int getBulletSpeed();

  //��ȡ����
  std::string getTankName();

  //��������
  void setTankName(const char *pszName);
  void setTankName(std::string strName);

  //����״̬
  void setTankStatus(emTankStatus status, int time);

  //��ȡ״̬ʱ��
  int getStatusTime();

  void toUp();
  void toDown();
  void toRight();
  void toLeft();

  //����
  virtual void toDie();

  //����
  virtual void revive();

  //����״̬
  virtual void create();

protected:
  //̹������
  std::string m_strTankName;
  //̹������
  emTankType m_emType;
  //̹��֣Ӫ
  emTankCamp m_emCamp;

  //����
  emTankDirection m_emDir;
  //�ƶ��ٶ�
  int m_nMoveSpeed;
  //�ӵ��ٶ�
  int m_nBulletSpeed;
  //�˺�,����
  int m_nPower;
  //̹��״̬
  emTankStatus m_emTankStatus;
  //״̬ʱ��
  int m_nStatusTime;
  //��ǰ����
  int m_nMagazine;

public:
  //��ʾ����
  CPosition PrevPos;
  //��ǰ�ƶ�����/
  int m_nMoveDis;
  //����״̬
  bool bAnimeFlag;
  //��������״̬
  bool bAnimeDieFlag;
  //�ƶ�״̬
  bool bMoveFlag;
  //��������֡
  bool bFrameFlag;
  //֡ʱ��
  unsigned int nFrameTime;

  //����֡����
  int nAnimeFrameNum;

  CBullet* m_aryBulletBuf[MAX_BULLET];//�ӵ�
  
  int m_nCountBullet;//��ǰ�����ӵ�����
};
