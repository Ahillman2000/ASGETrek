//
// Created by alexa on 11/12/2020.
//
#include <gamelib/Torpedo.hpp>

bool Torpedo::initialiseSprite(ASGE::Renderer* renderer,const std::string &filename, short z_order)
{
  torpedo = renderer->createUniqueSprite();
  torpedo->setGlobalZOrder(z_order);

  return torpedo->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Torpedo::getSprite()
{
  return torpedo;
}
bool Torpedo::isFired() const
{
  return fired;
}
void Torpedo::setFired(bool Fired)
{
  Torpedo::fired = Fired;
}
