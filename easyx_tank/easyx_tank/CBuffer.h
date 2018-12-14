#pragma once
#include "CPosition.h"
#include "CTank.h"

#define TYPE_PROTECT_TIME 10000 //10�뱣��ʱ��
#define TYPE_STOPROBOT_TIME 10000 //10����ͣʱ��

class CBuffer : public CPosition
{
public:
  enum emBufferType
  {
    TYPE_ADDLIFE,
    TYPE_STOPTIME,
    TYPE_IRONHOME,
    TYPE_BOMB,
    TYPE_ADDBULLET,
    TYPE_PROTECT
  };

public:
  //����
  CBuffer(emBufferType type);
  ~CBuffer();

  //��ʾ
  void show();

  //�����ʾ
  void clear();

  //������
  void onTouch(CTank &tank);

  //��������
  void setPos(int x, int y);

  //������ʾ״̬
  void setVisible(bool bFlag);

  //�Ƿ���ʾ
  bool isShow();

public:
  //buffer����
  emBufferType m_emBufferType;
  //�Ƿ���ʾ
  bool m_bShowFlag;
};

