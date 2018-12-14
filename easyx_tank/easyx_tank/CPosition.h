#pragma once
class CPosition
{
public:
  CPosition();
  CPosition(int x,int y);
  ~CPosition();

  //��
  bool toLeft(int nStep);
  //��
  bool toRight(int nStep);
  //��
  bool toUp(int nStep);
  //��
  bool toDown(int nStep);

  //���ù��
  void setPos(int x, int y);

  //����X
  void setX(int x);

  //��ȡX
  int getX();
  
  //����Y
  void setY(int y);

  //��ȡX
  int getY();

private:
  int x;
  int y;
};

