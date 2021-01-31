//
// Created by alexa on 10/12/2020.
//
#include "gamelib/Sector.hpp"
bool Sector::initialiseSprite(ASGE::Renderer* renderer,const std::string& filename)
{
  grid = renderer->createUniqueSprite();

  return grid->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Sector::getSprite()
{
  return grid;
}
/*bool Sector::isOccupied() const
{
  return occupied;
}*/
void Sector::setOccupied(bool Occupied)
{
  Sector::occupied = Occupied;
}
