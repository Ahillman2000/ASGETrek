//
// Created by alexa on 27/11/2020.
//

#include "gamelib/Grid.hpp"
bool Grid::initialiseSprite(ASGE::Renderer* renderer,const std::string &filename)
{
  grid = renderer->createUniqueSprite();

  return grid->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Grid::getSprite()
{
  return grid;
}
/*bool Grid::isOccupied() const
{
  return occupied;
}*/
void Grid::setOccupied(bool Occupied)
{
  Grid::occupied = Occupied;
}
