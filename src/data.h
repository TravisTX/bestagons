#ifndef DATA_H
#define DATA_H

struct Segment
{
    int Num;
    int Dir;
    int LowVertex;
    int HighVertex;
    int LowLed;
    int HighLed;

    Segment(int num, int dir, int lowVertex, int highVertex)
    {
        this->Num = num;
        this->Dir = dir;
        this->LowVertex = lowVertex;
        this->HighVertex = highVertex;
        this->LowLed = num * LEDS_PER_SEGMENT;
        this->HighLed = num * LEDS_PER_SEGMENT + LEDS_PER_SEGMENT - 1;
    }
};

const int DIR_NE = 0;
const int DIR_E = 1;
const int DIR_SE = 2;
const int DIR_SW = 3;
const int DIR_W = 4;
const int DIR_NW = 5;

#define NUM_SEGMENTS 37
const Segment segments[NUM_SEGMENTS] = {
    Segment(0, DIR_W, 12, 6),
    Segment(1, DIR_E, 6, 0),
    Segment(2, DIR_E, 0, 1),
    Segment(3, DIR_E, 1, 7),
    Segment(4, DIR_E, 7, 8),
    Segment(5, DIR_E, 8, 2),
    Segment(6, DIR_E, 2, 3),
    Segment(7, DIR_E, 3, 9),
    Segment(8, DIR_E, 9, 10),
    Segment(9, DIR_E, 10, 4),
    Segment(10, DIR_E, 4, 5),
    Segment(11, DIR_E, 5, 11),
    Segment(12, DIR_W, 11, 17),
    Segment(13, DIR_E, 17, 23),
    Segment(14, DIR_W, 23, 29),
    Segment(15, DIR_W, 29, 28),
    Segment(16, DIR_W, 28, 22),
    Segment(17, DIR_W, 22, 21),
    Segment(18, DIR_W, 21, 27),
    Segment(19, DIR_W, 27, 26),
    Segment(20, DIR_W, 26, 20),
    Segment(21, DIR_W, 20, 19),
    Segment(22, DIR_W, 19, 25),
    Segment(23, DIR_W, 25, 24),
    Segment(24, DIR_W, 24, 18),
    Segment(25, DIR_E, 18, 12),
    Segment(26, DIR_E, 12, 13),
    Segment(27, DIR_E, 13, 7),
    Segment(28, DIR_E, 13, 19),
    Segment(29, DIR_E, 20, 14),
    Segment(30, DIR_W, 14, 8),
    Segment(31, DIR_E, 14, 15),
    Segment(32, DIR_E, 15, 9),
    Segment(33, DIR_E, 15, 21),
    Segment(34, DIR_E, 22, 16),
    Segment(35, DIR_W, 16, 10),
    Segment(36, DIR_E, 16, 17)};

// index = vertex number
// values = segment numbers connected to that vertex in the following sequence:
// NE, E, SE, SW, W, NW
const int verticies[30][6] = {
    {-1, 2, -1, 1, -1, -1}, // 0
    {-1, -1, 3, -1, 2, -1},
    {-1, 6, -1, 5, -1, -1},
    {-1, -1, 7, -1, 6, -1},
    {-1, 10, -1, 9, -1, -1},
    {-1, -1, 11, -1, 10, -1}, // 5
    {1, -1, 0, -1, -1, -1},
    {-1, 4, -1, 27, -1, 3},
    {5, -1, 30, -1, 4, -1},
    {-1, 8, -1, 32, -1, 7},
    {9, -1, 35, -1, 8, -1}, // 10
    {-1, -1, -1, 12, -1, 11},
    {-1, 26, -1, 25, -1, 0},
    {27, -1, 28, -1, 26, -1},
    {-1, 31, -1, 29, -1, 30},
    {32, -1, 33, -1, 31, -1}, // 15
    {-1, 36, -1, 34, -1, 35},
    {12, -1, 13, -1, 36, -1},
    {25, -1, 24, -1, -1, -1},
    {-1, 21, -1, 22, -1, 28},
    {29, -1, 20, -1, 21, -1}, // 20
    {-1, 17, -1, 18, -1, 33},
    {34, -1, 16, -1, 17, -1},
    {-1, -1, -1, 14, -1, 13},
    {-1, 23, -1, -1, -1, 24},
    {22, -1, -1, -1, 23, -1}, // 25
    {-1, 19, -1, -1, -1, 20},
    {18, -1, -1, -1, 19, -1},
    {-1, 15, -1, -1, -1, 16},
    {14, -1, -1, -1, 15, -1}};

const int STEERING_RAND = 0;
const int STEERING_CW = 1;
const int STEERING_CCW = 2;
const int STEERING_PATH = 3;
const int STEERING_PATH_PINGPONG = 4;

#endif
