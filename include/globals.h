#ifndef GLOBALS_H
#define GLOBALS_H

enum Wheel
{
  LEFT = 1,
  RIGHT = 2,
};
enum Direction
{
  FORWARD = 1,
  BACKWARD = -1,
};
enum Commands
{
  LED_ON = 0,
  LED_OFF = 1,
  MOVE_FORWARD = 2,
  MOVE_BACKWARD = 3,
  TURN_LEFT = 4,
  TURN_RIGHT = 5,
  STOP = 6
};


#endif // GLOBALS_H