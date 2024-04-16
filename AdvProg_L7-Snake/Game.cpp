#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "Game.h"

using namespace std;

Game::Game(int _width, int _height)
    : width(_width), height(_height),
      squares(_height, vector<CellType>(_width, CELL_EMPTY)),
      snake(*this, Position(_width / 2, _height / 2)),
      currentDirection(Direction::RIGHT),
      status(GAME_RUNNING),
      score(0)
{
    addCherry();
}

Game::~Game()
{
}

void Game::snakeMoveTo(Position pos)
{
    if (getCellType(pos) == CELL_OFF_BOARD || getCellType(pos) == CELL_SNAKE) {
        setGameStatus(GAME_OVER);
        return;
    }

    if (getCellType(pos) == CELL_CHERRY) {
        score++;
        setCellType(pos, CELL_EMPTY);
        addCherry();
    } else {
        setCellType(pos, CELL_SNAKE);
    }
}

void Game::snakeLeave(Position position)
{
    setCellType(position, CELL_EMPTY);
}
void Game::processUserInput(Direction direction)
{
    inputQueue.push(direction);
}
bool Game::canChange(Direction current, Direction next) const
{
    if ((current == UP || current == DOWN) && (next == UP || next == DOWN)) {
        return false;
    } else if ((current == LEFT || current == RIGHT) && (next == LEFT || next == RIGHT)) {
        return false;
    }
    return true;
}

void Game::nextStep()
{
    while (!inputQueue.empty()) {
        Direction next = inputQueue.front();
        inputQueue.pop();
        if (canChange(currentDirection, next)) {
            currentDirection = next;
            break;
        }
    }

    snake.move(currentDirection);
}

void Game::addCherry()
{
    do {
        Position randomPos(rand() % width, rand() % height);
        if (getCellType(randomPos) == CELL_EMPTY) {
            cherryPosition = randomPos;
            setCellType(randomPos, CELL_CHERRY);
            break;
        }
    } while (true);
}

void Game::setCellType(Position pos, CellType cellType)
{
    if (pos.isInsideBox(0, 0, width, height)) {
        squares[pos.y][pos.x] = cellType;
    }
}

CellType Game::getCellType(Position pos) const
{
    return pos.isInsideBox(0, 0, width, height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

vector<Position> Game::getSnakePositions() const
{
    return snake.getPositions();
}

GameStatus Game::getGameStatus()
{
    return status;
}

int Game::getWidth()
{
    return width;
}

int Game::getHeight()
{
    return height;
}

Snake Game::getSnake()
{
    return snake;
}

