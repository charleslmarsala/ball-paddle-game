#include <SFML/Graphics.hpp>
#include <cmath>
#include "padswarheader.h"
#include <iostream>

//---------------------------------------------------------

// Function declarations (prototypes)
void setup(Ball &theBall, Borders &theWalls, MovingBlock &thePaddle, MovingBlock &thePaddle2);
Direction processInput();
bool update(Direction &input, Ball &ball, float delta, Borders theWalls, MovingBlock &thePaddle,MovingBlock &thePaddle2, bool &started, bool gameOver);
void render(sf::RenderWindow &window, Ball ball, float delta, Borders theWalls, MovingBlock thePaddle, MovingBlock thePaddle2);
int getCollision(Ball* pBall, Block* pBlock);
bool checkCollision(Ball *pBall, Block* pBlock);
bool checkBlockCollision(Block movingBlock, Block stationary);
bool doCollisionChecks(Ball &theBall, MovingBlock& thePaddle, MovingBlock &thePaddle2, Borders theWalls);
int main_game();
//------------------------------------------------------
Properties windowPropertiesl;

/**
 * The main application of the program.
 * @return OS status message (0=Success)
 */
int main() {

    int mousePosX, mousePosY;

    //Window config
    sf::RenderWindow renderWindow(sf::VideoMode(1200, 800),
                                  "GUI game");

    //Event Variables
    sf::Event event;

    sf::Texture mainMenuImg;
    mainMenuImg.loadFromFile("C:/Users/charl/CLionProjects/untitled11/Start Game.png");
    sf::Sprite sprite(mainMenuImg);


// Images, Sprites

    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mousePosX = event.mouseButton.x;
                    mousePosY = event.mouseButton.y;


                    if (mousePosX > 436 && mousePosX < 744 && mousePosY < 356 && mousePosY > 264) {
                        renderWindow.close();
                        main_game();
                    }  if (mousePosX > 511 && mousePosX < 700 && mousePosY < 536 && mousePosY > 461) {
                        renderWindow.close();
                    }
                }
            }

        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}

int game_over_window() {

    int mousePosX, mousePosY;

    //Window config
    sf::RenderWindow gameOverWindow(sf::VideoMode(1200, 800),
                                    "Game Over!");

    //Event Variables
    sf::Event event;

    sf::Texture gameOverImg;
    gameOverImg.loadFromFile("C:/Users/charl/CLionProjects/untitled11/GameOver2.png");
    sf::Sprite sprite2(gameOverImg);


// Images, Sprites

    while (gameOverWindow.isOpen()) {
        while (gameOverWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed)
                gameOverWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mousePosX = event.mouseButton.x;
                    mousePosY = event.mouseButton.y;

                    std::cout << mousePosX << "\n" << mousePosY << std::endl;

                    if (mousePosX > 385 && mousePosX < 812 && mousePosY < 456 && mousePosY > 341) {
                        gameOverWindow.close();
                        main();
                    }
                }
            }

        }
        gameOverWindow.clear();
        gameOverWindow.draw(sprite2);
        gameOverWindow.display();
    }
}


int main_game(){

    // create a 2d graphics window
    sf::RenderWindow window(sf::VideoMode(windowPropertiesl.WINDOW_WIDTH, windowPropertiesl.WINDOW_HEIGHT), "Paddle Wars");
    window.clear(windowPropertiesl.WINDOW_COLOR);

    //-------------------------------------------------

    Ball theBall;
    Borders theWalls;
    MovingBlock thePaddle;
    MovingBlock thePaddle2;
    setup(theBall, theWalls, thePaddle, thePaddle2);
    //--------------------------------------------------

    // timing variables for the main game loop
    sf::Clock clock;
    sf::Time startTime = clock.getElapsedTime();
    sf::Time stopTime = startTime;
    float delta = 0.0;
    bool gameOver = false;
    bool started = false;

    while (!gameOver)
    {
        // calculate frame time
        stopTime = clock.getElapsedTime();
        delta += (stopTime.asMilliseconds() - startTime.asMilliseconds());
        startTime = stopTime;

        // process events
        sf::Event event;

        while (!gameOver && window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                gameOver = true;
        }

        // Process user input
        // ------------------------------------------------
        Direction userInput = processInput();
        if (userInput == Exit)
            gameOver = true;

        // Process Updates
        // ------------------------------------------------
        if (delta >= windowPropertiesl.FRAME_RATE) {    // if we have made it at least a full frame time

            gameOver = update(userInput, theBall, delta, theWalls, thePaddle, thePaddle2, started, gameOver);

            // subtract the frame-rate from the current frame-time
            // for each full frame covered by this update
            while (delta >= windowPropertiesl.FRAME_RATE)
                delta -= windowPropertiesl.FRAME_RATE;
        }

        // Render the window
        // -----------------------------------------------
        render(window, theBall, delta, theWalls, thePaddle, thePaddle2);
    }


    // end main game loop
    // game ending, close the graphics window

    window.close();
    game_over_window();

    return 0;   // return success to the OS
} // end main

//Function Definitions
//----------------------------------------------------------
/**
 * Function that sets up the values of the structs objects
 * @param theBall
 * @param theWalls
 * @param thePaddle
 * @param theBricks
 */
void setup(Ball &theBall, Borders &theWalls, MovingBlock &thePaddle, MovingBlock &thePaddle2) {


    // Borders settings
    theWalls.leftBlock.left = 0.0;
    theWalls.leftBlock.top = 0.0;
    theWalls.leftBlock.width = WALL_THICKNESS;
    theWalls.leftBlock.height = windowPropertiesl.WINDOW_HEIGHT;
    theWalls.leftBlock.color = WALL_COLOR;
    theWalls.topBlock.left = 0.0;
    theWalls.topBlock.top = 0.0;
    theWalls.topBlock.width = windowPropertiesl.WINDOW_WIDTH;
    theWalls.topBlock.height = WALL_THICKNESS;
    theWalls.topBlock.color = WALL_COLOR;
    theWalls.rightBlock.left = windowPropertiesl.WINDOW_WIDTH - WALL_THICKNESS;
    theWalls.rightBlock.top = 0.0;
    theWalls.rightBlock.width = WALL_THICKNESS;
    theWalls.rightBlock.height = windowPropertiesl.WINDOW_WIDTH;
    theWalls.rightBlock.color = WALL_COLOR;
    theWalls.bottomBlock.left = 0.;
    theWalls.bottomBlock.top = windowPropertiesl.WINDOW_HEIGHT - WALL_THICKNESS;
    theWalls.bottomBlock.width = windowPropertiesl.WINDOW_WIDTH;
    theWalls.bottomBlock.height = WALL_THICKNESS;
    theWalls.bottomBlock.color = WALL_COLOR;

    // Paddle settings
    thePaddle.settings.left = (windowPropertiesl.WINDOW_WIDTH - windowPropertiesl.PADDLE_WIDTH) / 2.0;
    thePaddle.settings.top = windowPropertiesl.WINDOW_HEIGHT - (2.0 * windowPropertiesl.PADDLE_THICKNESS);
    thePaddle.settings.width = windowPropertiesl.PADDLE_WIDTH;
    thePaddle.settings.height = windowPropertiesl.PADDLE_THICKNESS;
    thePaddle.settings.color = windowPropertiesl.PADDLE_COLOR;
    thePaddle.settings.rectangle.setSize(sf::Vector2f(thePaddle.settings.width, thePaddle.settings.height));
    thePaddle.settings.rectangle.setFillColor(sf::Color::Red);
    thePaddle.x_velocity = 0.0;
    thePaddle.y_velocity = 0.0;

    thePaddle2.settings.left = (windowPropertiesl.WINDOW_WIDTH - windowPropertiesl.PADDLE_WIDTH) / 2.0;
    thePaddle2.settings.top = (2.0 * windowPropertiesl.PADDLE_THICKNESS);
    thePaddle2.settings.width = windowPropertiesl.PADDLE_WIDTH;
    thePaddle2.settings.height = windowPropertiesl.PADDLE_THICKNESS;
    thePaddle2.settings.color = windowPropertiesl.PADDLE_COLOR;
    thePaddle2.settings.rectangle.setSize(sf::Vector2f(thePaddle2.settings.width, thePaddle2.settings.height));
    thePaddle2.settings.rectangle.setFillColor(sf::Color::Blue);
    thePaddle2.x_velocity = 0.0;
    thePaddle2.y_velocity = 0.0;

    // Ball Settings
    theBall.radius = windowPropertiesl.BALL_RADIUS;
    theBall.coordinateX = thePaddle.settings.left + (thePaddle.settings.width / 2.0);
    theBall.coordinateY = thePaddle.settings.top - theBall.radius - 1;
    theBall.velocityX = 0.0;
    theBall.velocityY = 0.0;
    theBall.color = windowPropertiesl.BALL_COLOR;

}

/**
 * Function detects balls position and assign specific checkpoint to calculate
 * the expected cardinal heading value
 * @param pBall
 * @param pBlock
 * @return cardinal
 */
int getCollision(Ball* pBall, Block* pBlock){
    float checkPointX, checkPointY;
    int cardinal = 0;

    if (pBall->coordinateX < pBlock->left){
        checkPointX = pBlock->left;
    } else if(pBall->coordinateX > (pBlock->left + pBlock->width)){
        checkPointX = pBlock->left + pBlock->width;
    } else {
        checkPointX = pBall->coordinateX;
    }

    if (pBall->coordinateY < pBlock->top){
        checkPointY = pBlock->top;
    } else if(pBall->coordinateY > (pBlock->top + pBlock->height)){
        checkPointY = pBlock->top + pBlock->height;
    } else{
        checkPointY = pBall->coordinateY;
    }

    float diffX = checkPointX - pBall->coordinateX;
    float diffY = (windowPropertiesl.WINDOW_HEIGHT - checkPointY) - (windowPropertiesl.WINDOW_HEIGHT - pBall->coordinateY);
    double distance = std::sqrt(pow(diffX,2.0)+ pow(diffY,2.0));

    if (distance <= pBall->radius){
        double theta = std::atan2(diffY, diffX);
        double degrees = 90.0 - theta * 180 / M_PI;
        if (degrees <= 0){
            degrees += 360;
        }
        cardinal = int(degrees);
    }

    return cardinal;

}

/**
 * check if a collision is happening set ball properties according to cardinal value
 * @param pBall - Ball pointer
 * @param pBlock - Block pointer
 * @return bool - isColliding
 */
bool checkCollision(Ball* pBall, Block* pBlock){
    bool isColliding = false;
    int cardinal = getCollision(pBall, pBlock);

    if (cardinal != 0) {
        isColliding = true;
        if (cardinal > 225 && cardinal < 315){
            pBall->velocityX = pBall->velocityX * -1;
            pBall->coordinateX = pBlock->left + pBlock->width + pBall->radius +1;

        } else if (cardinal > 45 && cardinal < 135){
            pBall->velocityX = pBall->velocityX * -1;
            pBall->coordinateX =  pBlock->left - pBall->radius -1;
        }
        if (cardinal >= 315 || cardinal <= 45){
            pBall->velocityY = pBall->velocityY * -1;
            pBall->coordinateY = pBlock->top + pBlock->height + pBall->radius +1;

        } else if (cardinal >= 135 && cardinal <= 225){
            pBall->velocityY = pBall->velocityY * -1;
            pBall->coordinateY = pBlock->top - pBall->radius -1;
        }
    }
    return isColliding;
}
/**
 * Function that checks the colision between a movie block and a stationary block.
 * @param movingBlock
 * @param stationary
 * @return
 */
bool checkBlockCollision(Block movingBlock, Block stationary){
    bool isColliding = false;

    if (movingBlock.left < stationary.left + stationary.width &&
        movingBlock.left + movingBlock.width > stationary.left &&
        movingBlock.top < stationary.top + stationary.height &&
        movingBlock.top + movingBlock.height > stationary.top) {
        isColliding = true;
    }
    return isColliding;
}

/**
 * convert user keyboard input into recognized integer values
 * for left=1/up=2/right=3/down=4
 * @return int - user input (default no-input=0, quit=-1)
 */
Direction processInput() {
    Direction input = None;  // no input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        input = Left;
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        input = Up;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        input = Right;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        input = Down;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        input = Exit;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        input = Start;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        input = Left_up;
    }  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        input = Right_up;
    }
    return input;
}
// end getUserInput

bool doCollisionChecks(Ball &theBall, MovingBlock &thePaddle,MovingBlock &thePaddle2, Borders theWalls){
    bool gameOver = false;
    // --- check vertical collisions ---


    if (!checkCollision(&theBall, &thePaddle.settings) && !checkCollision(&theBall, &thePaddle2.settings)) {
        if (!checkCollision(&theBall, &theWalls.topBlock)) {
            gameOver = checkCollision(&theBall, &theWalls.bottomBlock);
            if (gameOver){
                return gameOver;
            }
        }
    }

    if ((theBall.coordinateY - 3) == (theWalls.topBlock.height + WALL_THICKNESS)){
        gameOver = true;
        return gameOver;
    }

    // --- check horizontal collisions ---
    if (checkCollision(&theBall, &theWalls.leftBlock)) {
        checkCollision(&theBall, &theWalls.rightBlock);
    }

    if (checkBlockCollision(thePaddle.settings, theWalls.leftBlock)){
        thePaddle.x_velocity = 0.0;
        thePaddle.settings.left = theWalls.leftBlock.left + theWalls.leftBlock.width;
    }
    else if (checkBlockCollision(thePaddle.settings, theWalls.rightBlock)) {
        thePaddle.x_velocity = 0.0;
        thePaddle.settings.left = theWalls.rightBlock.left + thePaddle.settings.width - 1;
    }

    if (checkBlockCollision(thePaddle2.settings, theWalls.leftBlock)){
        thePaddle2.x_velocity = 0.0;
        thePaddle2.settings.left = theWalls.leftBlock.left + theWalls.leftBlock.width;
    }
    else if (checkBlockCollision(thePaddle2.settings, theWalls.rightBlock)) {
        thePaddle2.x_velocity = 0.0;
        thePaddle2.settings.left = theWalls.rightBlock.left + thePaddle2.settings.width - 1;
    }

    return gameOver;
}


/**
 * update the state of game objects
 * @param input - user keyboard input
 * @param ball  - update ball position and speed
 * @param delta - current frame time
 */
bool update(Direction &input, Ball &theBall, float delta, Borders theWalls, MovingBlock &thePaddle, MovingBlock &thePaddle2, bool &started, bool gameOver) {
    // adjust velocity directions for user input
    if (input) {
        switch (input) {
            case Left: // Left
                thePaddle.x_velocity -= windowPropertiesl.PADDLE_SPEED;
                break;
            case Right: // Right
                thePaddle.x_velocity += windowPropertiesl.PADDLE_SPEED;
                break;
            case Left_up: // Left
                thePaddle2.x_velocity -= windowPropertiesl.PADDLE_SPEED;
                break;
            case Right_up: // Right
                thePaddle2.x_velocity += windowPropertiesl.PADDLE_SPEED;
                break;

            case Start:
                if (!started) {
                    theBall.velocityX = windowPropertiesl.BALL_SPEED_X;
                    theBall.velocityY = windowPropertiesl.BALL_SPEED_Y * -1;
                    if ((int(delta * 10) & 1) % 2) {
                        theBall.velocityX *= -1;  // ball goes left if odd
                    }
                    started = true;

                }
                break;
        }
        input = None;
    }
    // clear input
    thePaddle.settings.left += thePaddle.x_velocity * delta;
    thePaddle2.settings.left += thePaddle2.x_velocity * delta;

    if (started) {
        theBall.coordinateX += theBall.velocityX * delta;
        theBall.coordinateY += theBall.velocityY * delta;
    } else {
        theBall.coordinateX = thePaddle.settings.left + (thePaddle.settings.width / 2.0);
        theBall.coordinateY = thePaddle.settings.top - theBall.radius - 1;
    }

//Calling Check collision to verify is the ball is colliding
    checkCollision(&theBall, &theWalls.leftBlock);
    checkCollision(&theBall, &theWalls.topBlock);
    checkCollision(&theBall, &theWalls.rightBlock);

    gameOver = doCollisionChecks(theBall, thePaddle, thePaddle2, theWalls);


    return gameOver;
} // end update


/**
 * draw the ball on the graphics window
 * @param window - handle to open graphics window
 * @param ball   - structure variable with properties for the ball
 * @param delta  - amount of frame time plus lag (in ms)
 */
void render(sf::RenderWindow &window, Ball ball, float delta, Borders theWalls, MovingBlock thePaddle, MovingBlock thePaddle2 ) {
    // Render drawing objects
    // ------------------------------------------------

    // clear the window with the background color
    window.clear(windowPropertiesl.WINDOW_COLOR);

    // draw the ball
    // ------------------------------------------------
    sf::CircleShape circle;
    circle.setFillColor(ball.color);
    circle.setRadius(ball.radius);

    // set screen coordinates relative to the center of the circle
    circle.setOrigin(0 , 0);

    // calculate current drawing location relative to speed and frame-time
    float xPosition = ball.coordinateX + ball.velocityX * delta;
    float yPosition = ball.coordinateY + ball.velocityY * delta;
    circle.setPosition(xPosition, yPosition);
    window.draw(circle);
    //--------------------------------------------------

    //Defining rectangle properties of each wall
    //--------------------------------------------------
    //Left Rectangle
    theWalls.leftBlock.rectangle.setSize(sf::Vector2(theWalls.leftBlock.width, theWalls.leftBlock.height));
    theWalls.leftBlock.rectangle.setPosition(theWalls.leftBlock.left, theWalls.leftBlock.top);
    theWalls.leftBlock.rectangle.setFillColor(theWalls.leftBlock.color);
    //Top Rectangle
    theWalls.topBlock.rectangle.setSize(sf::Vector2(theWalls.topBlock.width, theWalls.topBlock.height));
    theWalls.topBlock.rectangle.setPosition(theWalls.topBlock.left, theWalls.topBlock.top);
    theWalls.topBlock.rectangle.setFillColor(theWalls.topBlock.color);
    //Right Rectangle
    theWalls.rightBlock.rectangle.setSize(sf::Vector2(theWalls.rightBlock.width, theWalls.rightBlock.height));
    theWalls.rightBlock.rectangle.setPosition(theWalls.rightBlock.left, theWalls.rightBlock.top);
    theWalls.rightBlock.rectangle.setFillColor(theWalls.rightBlock.color);
    //Bottom Rectangle
    theWalls.bottomBlock.rectangle.setSize(sf::Vector2(theWalls.bottomBlock.width, theWalls.bottomBlock.height));
    theWalls.bottomBlock.rectangle.setPosition(theWalls.bottomBlock.left, theWalls.bottomBlock.top);
    theWalls.bottomBlock.rectangle.setFillColor(theWalls.bottomBlock.color);

    //Paddle rendering
    thePaddle.settings.top += thePaddle.y_velocity * delta;
    thePaddle.settings.left += thePaddle.x_velocity * delta;
    thePaddle.settings.rectangle.setPosition(thePaddle.settings.left,thePaddle.settings.top);

    thePaddle2.settings.top += thePaddle2.y_velocity * delta;
    thePaddle2.settings.left += thePaddle2.x_velocity * delta;
    thePaddle2.settings.rectangle.setPosition(thePaddle2.settings.left,thePaddle2.settings.top);


    //Rendering each rectangle
    window.draw(theWalls.leftBlock.rectangle);
    window.draw(theWalls.topBlock.rectangle);
    window.draw(theWalls.rightBlock.rectangle);
    window.draw(theWalls.bottomBlock.rectangle);
    window.draw(thePaddle.settings.rectangle);
    window.draw(thePaddle2.settings.rectangle);


    // show the new window
    // ------------------------------------------------
    window.display();
} // end render