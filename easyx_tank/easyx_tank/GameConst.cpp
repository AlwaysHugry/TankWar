#include "GameConst.h"
#include "CGameUI.h"

//��Ϸ��������ȫ��ָ��
CGame *g_Game;

//��Ļ
CGameUI *ui;

unsigned char g_CurMapData[26][26];

//̹����Ϣ����
int g_aryTankInfo[7][5] = 
{
  //����ֵ,�˺�,�ƶ��ٶ�,�ӵ��ٶ�,������
  {  5, 2, 2, 2 ,1},
  {  4, 2, 2, 2 ,1},
  {  2, 8, 3, 5 ,2},
  {  4, 1, 2, 4 ,1},
  {  8, 1, 1, 4 ,4},
  {  10,2, 1, 4 ,3},
  {  4, 2, 3, 4 ,2}
};