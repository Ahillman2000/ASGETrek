//
// Created by alexa on 27/11/2020.
//

#include "gamelib/Mongol.hpp"

bool Mongol::initialiseSprite(ASGE::Renderer* renderer, const std::string& filename)
{
  mongol = renderer->createUniqueSprite();

  return mongol->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Mongol::getSprite()
{
  return mongol;
}
float Mongol::getHealth() const
{
  return health;
}
void Mongol::setHealth(float Health)
{
  Mongol::health = Health;
}
float Mongol::getDamage() const
{
  return damage;
}
int Mongol::getSector() const
{
  return sector;
}
void Mongol::setSector(int Sector)
{
  Mongol::sector = Sector;
}
int Mongol::getQuadrant() const
{
  return quadrant;
}
void Mongol::setQuadrant(int Quadrant)
{
  Mongol::quadrant = Quadrant;
}
bool Mongol::isAlive() const
{
  return alive;
}
void Mongol::setAlive(bool Alive)
{
  Mongol::alive = Alive;
}
int Mongol::getAction() const
{
  return action;
}
void Mongol::setAction(int Action)
{
  Mongol::action = Action;
}
