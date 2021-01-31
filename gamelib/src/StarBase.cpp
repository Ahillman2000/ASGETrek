//
// Created by alexa on 30/11/2020.
//

#include <gamelib/StarBase.hpp>

bool StarBase::initialiseSprite(ASGE::Renderer* renderer,const std::string &filename)
{
  starBase = renderer->createUniqueSprite();

  return starBase->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& StarBase::getSprite()
{
  return starBase;
}
int StarBase::getQuadrant() const
{
  return quadrant;
}
void StarBase::setQuadrant(int Quadrant)
{
  StarBase::quadrant = Quadrant;
}
int StarBase::getSector() const
{
  return sector;
}
void StarBase::setSector(int Sector)
{
  StarBase::sector = Sector;
}
