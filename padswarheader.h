#ifndef UNTITLED11_PADSWARHEADER_H
#define UNTITLED11_PADSWARHEADER_H

#include <SFML/Graphics.hpp>

// Global Constants
const float WALL_THICKNESS = 8.0;
const sf::Color WALL_COLOR = sf::Color::Black;

//---------------------------------------------
// ball properties
class Ball {
public:
    float radius;
    float coordinateX;
    float coordinateY;
    float velocityX;
    float velocityY;
    sf::Color color;
};

//Walls
class Block{
public:
    float left;
    float top;
    float width;
    float height;
    sf::Color color;
    sf::RectangleShape rectangle;
};

//Borders
struct Borders{
public:
    Block leftBlock;
    Block topBlock;
    Block rightBlock;
    Block bottomBlock;
};

class MovingBlock{
public:
    Block settings;
    float x_velocity;
    float y_velocity;
};
// --------------------------------------------------------
class Properties {
public:
    // window properties
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    const sf::Color WINDOW_COLOR = sf::Color::White;

    // drawing properties
    const float FRAME_RATE = (1.0 / 30.0) * 1000.0;       // FPS in ms
    const sf::Color BALL_COLOR = sf::Color::Black;

    // Ball properties
    const float BALL_RADIUS = 10.0;

    // Speed values
    const float BALL_SPEED_X = BALL_RADIUS * 25 / 1000.0;    // speed horizontally
    const float BALL_SPEED_Y = BALL_RADIUS * 10 / 1000.0;   // span  vertically

    // Paddle properties
    const float PADDLE_WIDTH = 80.0;
    const float PADDLE_THICKNESS = 10.0;
    const float PADDLE_SPEED = PADDLE_WIDTH / 10.0 / 1000.0;
    sf::Color PADDLE_COLOR = sf::Color::Black;
};


//---------------------------------------------------------

// Type definitions
enum Direction{
    Exit = -1,
    None = 0,
    Left = 1,
    Up = 2,
    Right = 3,
    Down = 4,
    Start = 5,
    Left_up = 6,
    Right_up = 7
};

//---------------------------------------------------------

#endif // untitled11_PADSWARHEADER_H
