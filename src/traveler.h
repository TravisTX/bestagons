#ifndef TRAVELER_H
#define TRAVELER_H
#include <FastLED.h>
#include <Arduino.h>
#include "data.h"

class Traveler
{
private:
public:
  int num;
  int pos;
  CRGB color;
  int animDir;
  Segment segment = segments[0];
  int steering;

  Traveler(int num)
  {
    num = num;
    segment = segments[random(0, NUM_SEGMENTS)];
    pos = segment.LowLed;
    animDir = random(0, 1) == 0 ? DIR_E : DIR_W;

    color = CHSV(random(1, 255), 255, 255);
  }

  Traveler(int num, int segmentNum, int pos, int animDir, int steering, CRGB color)
  {
    this->num = num;
    this->segment = segments[segmentNum];
    this->pos = pos;
    this->animDir = animDir;
    this->steering = steering;
    this->color = color;
  }

  void move()
  {
    int segmentEnd = (animDir == segment.Dir) ? segment.HighLed : segment.LowLed;
    if (pos == segmentEnd)
    {
      hop();
    }
    else
    {
      pos += (segment.Dir == animDir) ? 1 : -1;
    }
  }

  void hop()
  {
    switch (steering)
    {
      case STEERING_RAND:
        hopRandom();
        break;
      case STEERING_CW:
        hopClockWise();
        break;
      case STEERING_CCW:
        hopCounterClockWise();
        break;
    }
  }

  void hopRandom()
  {
    int vertex = (animDir == segment.Dir) ? segment.HighVertex : segment.LowVertex;
    while(true)
    {
      int nextSegNum = verticies[vertex][random(0, 6)];
      if (nextSegNum != -1 && nextSegNum != segment.Num)
      {
        finishHop(vertex, nextSegNum);
        break;
      }
    }
  }

  void hopClockWise()
  {
    int vertNum = (animDir == segment.Dir) ? segment.HighVertex : segment.LowVertex;
    int segNum = segment.Num;
    int nextDir = -1;

    if (verticies[vertNum][DIR_NE] == segNum)
      nextDir = DIR_W;
    else if (verticies[vertNum][DIR_E] == segNum)
      nextDir = DIR_NW;
    else if (verticies[vertNum][DIR_SE] == segNum)
      nextDir = DIR_NE;
    else if (verticies[vertNum][DIR_SW] == segNum)
      nextDir = DIR_E;
    else if (verticies[vertNum][DIR_W] == segNum)
      nextDir = DIR_SE;
    else if (verticies[vertNum][DIR_NW] == segNum)
      nextDir = DIR_SW;

    int nextSegNum = verticies[vertNum][nextDir];
    finishHop(vertNum, nextSegNum);
  }

  void hopCounterClockWise()
  {
    int vertNum = (animDir == segment.Dir) ? segment.HighVertex : segment.LowVertex;
    int segNum = segment.Num;
    int nextDir = -1;

    if (verticies[vertNum][DIR_NE] == segNum)
      nextDir = DIR_SE;
    else if (verticies[vertNum][DIR_E] == segNum)
      nextDir = DIR_SW;
    else if (verticies[vertNum][DIR_SE] == segNum)
      nextDir = DIR_W;
    else if (verticies[vertNum][DIR_SW] == segNum)
      nextDir = DIR_NW;
    else if (verticies[vertNum][DIR_W] == segNum)
      nextDir = DIR_NE;
    else if (verticies[vertNum][DIR_NW] == segNum)
      nextDir = DIR_E;

    int nextSegNum = verticies[vertNum][nextDir];
    finishHop(vertNum, nextSegNum);
  }

  void finishHop(int vertex, int nextSegNum)
  {
        segment = segments[nextSegNum];
        if (vertex == segment.LowVertex)
        {
          pos = segment.LowLed;
          animDir = segment.Dir;
        }
        else
        {
          pos = segment.HighLed;
          animDir = segment.Dir == DIR_E ? DIR_W : DIR_E;
        }

  }

};

#endif
