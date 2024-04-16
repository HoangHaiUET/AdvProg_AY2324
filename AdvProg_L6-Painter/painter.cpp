#include "painter.h"

/***
    Args: color (SDL_Color): color value

    Returns:
        None
***/
void Painter::setColor(SDL_Color color)
{
    // Set the color value for the Painter
    this->color = color;

    // Set Render Draw Color
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
}



/***
    Args: numPixel (int): number of pixel for jumping forward

    Returns:
        None
***/
void Painter::jumpForward(int numPixel)
{
    // Move the painter's position forward by numPixel pixels
    double rad = (angle / 180) * M_PI;
    x += static_cast<int>(numPixel * cos(rad));
    y -= static_cast<int>(numPixel * sin(rad));
}

/***
    Args: numPixel (int): number of pixel for jumping backward

    Returns:
        None
***/
void Painter::jumpBackward(int numPixel)
{
    // Move the painter's position backward by numPixel pixels
    jumpForward(-numPixel);
}


/***
    Args: degree (double): the value of rotation angle

    Returns:
        None
***/

void Painter::turnLeft(double degree)
{
    // Rotate the painter left by the specified degree
    angle += degree;

    // Ensure the angle stays within the range of 0 to 360 degrees
    angle = fmod(angle, 360.0);
    if (angle < 0) {
        angle += 360.0;
    }
}


/***
    Args: degree (double): the value of rotation angle

    Returns:
        None
***/
void Painter::turnRight(double degree)
{
    // Rotate the painter left by the specified degree
    angle -= degree;

    // Ensure the angle stays within the range of 0 to 360 degrees
    angle = fmod(angle, 360.0);
    if (angle < 0) {
        angle += 360.0;
    }
}

/***
    Args:
        None
    Returns:
        None
***/
void Painter::randomColor()
{
    // Set a random color for the painter
    SDL_Color randomColor = {static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256)};
    setColor(randomColor);
}


/***
Part of code that not need to be implemented
***/
void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
	SDL_RenderClear(renderer);
    setColor(curColor);
}


Painter::Painter(SDL_Window* window, SDL_Renderer *renderer)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0) {
        SDL_GetWindowSize(window, &width, &height);
    }
    this->renderer = renderer;
    setPosition(width/2, height/2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}


void Painter::createCircle(int radius)
{
    double rad = (angle / 180) * M_PI;
    int centerX = x + (int) (cos(rad) * (double) radius);;
    int centerY = y - (int) (sin(rad) * (double) radius);;

    int dx = radius;
    int dy = 0;
    int err = 0;

    while (dx >= dy)
    {
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY + dx);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY + dy);
        SDL_RenderDrawPoint(renderer, centerX - dx, centerY - dy);
        SDL_RenderDrawPoint(renderer, centerX - dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dy, centerY - dx);
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY - dy);

        if (err <= 0)
        {
            dy += 1;
            err += 2*dy + 1;
        }
        if (err > 0)
        {
            dx -= 1;
            err -= 2*dx + 1;
        }
    }
}



void Painter::createParallelogram(int size)
{
	for (int i = 0; i < 2; ++i) {
        moveForward(size);
        turnLeft(60);
        moveForward(size);
        turnLeft(120);
    }
}



void Painter::createSquare(int size)
{
	for (int i = 0; i < 4; ++i) {
        moveForward(size);
	    turnLeft(90);
    }
}


void Painter::moveForward(int numPixel)
{
    int preX = x, preY = y;
    jumpForward(numPixel);
    SDL_RenderDrawLine(renderer, preX, preY, x, y);
}


void Painter::moveBackward(int numPixel)
{
    moveForward(-numPixel);
}

