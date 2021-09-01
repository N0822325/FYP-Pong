#include "FYP/Renderer.h"
#include "FYP/Objects.h"

class Player
{
private:
  Object* object;

  int xPos;
  int inputBuffer[2] { 0,0 };

public:

  Player(bool isLeft) {
    if(isLeft) xPos = 20;
    else xPos = 480;
  }

  Object* getObject() { return object; }
  void setObject(Object* object_) { object = object_; }


  void addSpeed(int speed) {
    if (inputBuffer[0] == 0) inputBuffer[0] = speed;
    else inputBuffer[1] = speed;
  }
  void removeSpeed(int speed) {
    if (inputBuffer[0] == speed) inputBuffer[0] = 0;
    else inputBuffer[1] = 0;
  }


  void update()
  {
    int speed = 0;
    if (inputBuffer[1] != 0) speed = inputBuffer[1];
    else if (inputBuffer[0] != 0) speed = inputBuffer[0];

    if (speed > 0) {
      if (object->getBounds()[1].y+10 < 500)
        { object->addTranslation(0,speed,0); }
      else { object->setTranslation(xPos,500,0); }
    }
    else if (speed < 0) {
      if (object->getBounds()[1].x-10 > 0)
        { object->addTranslation(0,speed,0); }
      else { object->setTranslation(xPos,15,0); }
    }
  }

  void draw()
    { object->draw(); }

};

class Ball
{
private:
  Object* object;

  int xPos;
  int speed[2];

public:
  Ball()
  {
    int angle = rand() % 1;
    speed[0] = (rand() % 3) + 1;
    speed[1] = angle+1;
  }

  void setObject(Object* object_) { object = object_; }

  void reset()
  {
    object->setTranslation(255,255,0);
    int angle = rand() % 1;
    speed[0] = (rand() % 3) + 1;
    speed[1] = angle+1;
  }

  bool update(Player* p1, Player* p2)
  {
    if (object->overlaps(p1->getObject()))
    {
      speed[0] = -(speed[0] - 1);
    }
    else if (object->overlaps(p2->getObject()))
    {
      speed[0] = -(speed[0] + 1);
    }
    else if (object->getBounds()[1].y > 500)
    {
      speed[1] = -speed[1];
    }
    else if (object->getBounds()[1].x < 0)
    {
      speed[1] = -speed[1];
    }
    else if (object->getBounds()[0].y > 500)
    {
      reset(); return true;
    }
    else if (object->getBounds()[0].x < 0)
    {
      reset(); return true;
    }

    object->addTranslation(speed[0],speed[1],0);
    return false;
  }

  void draw()
    { object->draw(); }

};
