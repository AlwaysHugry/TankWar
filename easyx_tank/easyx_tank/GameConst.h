#pragma once
#include "CGame.h"
#include "CGameUI.h"

//���ڿ��
#define SCR_WIDTH         (640)
#define SCR_HEIGHT        (416)

//ͼƬ�ز�·��
#define IMG_MENU_PATH    "img\\menu.gif"
#define IMG_OBJECT_PATH  "img\\tankAll.gif"

//ǽ������ֵ
#define WALL_LIFE         2
//���˵���ս�����
#define ENEMY_TIME        3   //��λ��
//buff����ս��ʱ��
#define BUFF_TIME         10  //��λ��

//�����������
#define PLAYER1_LIFE_NUM  3
#define PLAYER2_LIFE_NUM  3

//̹������
#define TANK_ENEMEY_NUM   16 //�о�
#define TANK_PLAYER_NUM   2  //���

#define TIME_ROBOT_GENERATE 5000
#define ROBOT_NUMBER 16

//��ά��ͼ����
extern unsigned char g_CurMapData[26][26];

//̹����Ϣ����
extern int g_aryTankInfo[7][5];

//��Ϸ��������ȫ��ָ��
extern CGame *g_Game;

extern CGameUI *ui;