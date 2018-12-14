#pragma once
#include <Windows.h>
#include <MMSystem.h>

class CSound
{
public:
  CSound();
  ~CSound();

  //���ſ�ʼ������
  void PlayStartSound();

  //����̹�˱�ը����
  void PlayTankCrackSound();

  //���ſ�������
  void PlayFireSound();

  //�����ӵ���ը����
  void PlayBulletCrackSound();

  //����̹���ƶ�����
  void PlayMoveSound();

  //�������̹�˱�ը����
  void PlayPlayerCrackSound();
  
  //���ż񵽲�������
  void PlayPropSound();

  MCIDEVICEID dev[20];
  MCI_OPEN_PARMS mciOpen;
  MCI_PLAY_PARMS mciPlay;

};

void SoundPlayer(void *p);