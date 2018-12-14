#pragma once
#include <iostream>

#define MAP_FILE_CONFIG   "./map/map.ini"
#define MAP_FILE_FORMAT   "./map/level%d.dat"

class CMapFile
{
public:
  CMapFile();
  ~CMapFile();

  //ģʽ
  enum emMode
  {
    MD_READ,
    MD_WRITE
  };

  //�Ƿ��ʼ��
  bool isInit();

  //���ļ�
  bool open(const char* pszFileName, emMode mode);

  //�ر��ļ�
  void close();

  //��ȡ��ͼ�ؿ�����
  bool getMap(int level, unsigned char mapdate[26][26]);

  //д��ͼ����
  bool setMap(int level, unsigned char mapdate[26][26]);

  //��ȡ�ؿ���
  int getMapNum();
  
  //��ȡ��Ϸ�ٶ�
  int getGameSpeed();

private:
  FILE * m_fp;
  int m_nMapNum;
  int m_nGameSpeed;
  bool m_bInitFlag;
};

