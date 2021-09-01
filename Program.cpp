#define SOUND
#include "FYP/Engine.h"
#include "Pong.h"


class FYP : public Engine
{
private:
  Player player1;
  Player player2;
  Ball ball;

public:
  FYP(int width, int height) : player1(true), player2(false)
  {
    construct(width, height, "FYP", 60);
    start();
  }

  void userInitialse() override
  {
    float colour1[4] { 1.0, 1.0, 1.0, 1.0 };
    float bgc[4] { 0.0, 0.0, 0.0 };
    setBackgroundColour(bgc);

    player1.setObject(Plane(20,265,0, 10,30, colour1));
    player2.setObject(Plane(480,265,0, 10,30, colour1));
    ball.setObject(Plane(255,255,0, 10,10, colour1));
  }


  void userInput(XEvent events) override
  {
    if(events.type == KeyRelease)
    {
      if (events.xkey.keycode == 25) {
        player1.removeSpeed(5);
      }
      if (events.xkey.keycode == 39) {
        player1.removeSpeed(-5);
      }
      if (events.xkey.keycode == 111) {
        player2.removeSpeed(5);
      }
      if (events.xkey.keycode == 116) {
        player2.removeSpeed(-5);
      }
    }

    if(events.type == KeyPress)
    {
      if (events.xkey.keycode == 25) {
        player1.addSpeed(5);
      }
      if (events.xkey.keycode == 39) {
        player1.addSpeed(-5);
      }
      if (events.xkey.keycode == 111) {
        player2.addSpeed(5);
      }
      if (events.xkey.keycode == 116) {
        player2.addSpeed(-5);
      }
    }
  }


  void userUpdate(float deltaTime) override
  {
    player1.update();
    player2.update();
    if (ball.update(&player1, &player2))
    {
      std::string aa = "Resources/beep.wav";
      addSound(aa);
    }
  }

  void userDraw() override
  {
    player1.draw();
    player2.draw();
    ball.draw();
  }

};

int main()
{
  FYP nGin(500,500);

  int a;
  std::cin >> a;
  return 1;
}
