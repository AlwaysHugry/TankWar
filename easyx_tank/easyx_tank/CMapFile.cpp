#include "CMapFile.h"
#pragma warning(disable:4996)

CMapFile::CMapFile()
{
  FILE *fp = fopen(MAP_FILE_CONFIG, "rb+");
  char buf[8] = { 0 };
  m_nMapNum = 0;

  if (fp == NULL)
  {
    m_bInitFlag = false;
    goto EXIT;
  }

  //��һ��
  fgets(buf, 8, fp);
  //������ͼ��
  m_nMapNum = atoi(buf);

  //�ٶ�һ��
  fgets(buf, 8, fp);
  //��Ϸ�ٶ�
  m_nGameSpeed = atoi(buf);

  if (m_nMapNum == 0)
  {
    m_bInitFlag = false;
  }
  else
  {
    m_bInitFlag = true;
  }

EXIT:
  if (fp != NULL)
  {
    fclose(fp);
  }
  //��ʼ��
  m_fp = NULL;
}


CMapFile::~CMapFile()
{
}

bool CMapFile::isInit()
{
  return m_bInitFlag;
}

bool CMapFile::open(const char * pszFileName, emMode mode)
{
  close();
  if (mode == MD_READ)
  {
    m_fp = fopen(pszFileName, "rb");
  }
  else if (mode == MD_WRITE)
  {
    m_fp = fopen(pszFileName, "wb");
  }
  return m_fp != NULL;
}

void CMapFile::close()
{
  if (m_fp != NULL)
  {
    fclose(m_fp);
    m_fp = NULL;
  }
}

bool CMapFile::getMap(int level, unsigned char mapdate[26][26])
{
  bool ret = false;
  //����
  char szName[100] = { 0 };
  //�ؿ��ж�
  if (level <= m_nMapNum)
  {
    //ƴ�ӵ�ͼ�ļ�����
    sprintf(szName, MAP_FILE_FORMAT, level);
    //���ļ�
    if (open(szName, MD_READ))
    {
      //��ȡ����
      if (fread(mapdate, 26 * 26, 1, m_fp) == 1)
      {
        ret = true;
      }
    }
    //�ر��ļ�
    close();
  }
  return ret;
}

bool CMapFile::setMap(int level, unsigned char mapdate[26][26])
{
  bool ret = false;
  //����
  char szName[100] = { 0 };
  //ƴ�ӵ�ͼ�ļ�����
  sprintf(szName, MAP_FILE_FORMAT, level);
  //���ļ�
  if (open(szName, MD_WRITE))
  {
    //��ȡ����
    if (fwrite(mapdate, 26 * 26, 1, m_fp) == 1)
    {
      ret = true;
    }
  }
  //�ر��ļ�
  close();
  return ret;
}

int CMapFile::getMapNum()
{
  return m_nMapNum;
}

int CMapFile::getGameSpeed()
{
  return m_nGameSpeed;
}
