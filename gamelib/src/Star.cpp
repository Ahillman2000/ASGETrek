//
// Created by alexa on 30/11/2020.
//

#include <gamelib/Star.hpp>

bool Star::initialiseSprite(ASGE::Renderer* renderer,const std::string &filename)
{
  star = renderer->createUniqueSprite();

  return star->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Star::getSprite()
{
  return star;
}
int Star::getQuadrant() const
{
  return quadrant;
}
void Star::setQuadrant(int Quadrant)
{
  Star::quadrant = Quadrant;
}
int Star::getSector() const
{
  return sector;
}
void Star::setSector(int Sector)
{
  Star::sector = Sector;
}
