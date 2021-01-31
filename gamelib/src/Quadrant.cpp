//
// Created by alexa on 10/12/2020.
//
#include "gamelib/Quadrant.hpp"

void Quadrant::initialiseText(ASGE::Renderer* renderer, std::string string, ASGE::Colour colour, ASGE::Point2D position)
{
  quadrant = std::make_unique<ASGE::Text>();
  quadrant->setFont(renderer->getDefaultFont());
  quadrant->setString(string);
  quadrant->setColour(colour);
  quadrant->setPosition({position.x,position.y});
}

void Quadrant::setTextString(std::string string)
{
  quadrant->setString(string);
}

void Quadrant::setTextColour(ASGE::Colour colour)
{
  quadrant->setColour(colour);
}

/*void Quadrant::setTextPosition(ASGE::Point2D position)
{
  quadrant->setPosition({position.x, position.y});
}*/

std::unique_ptr<ASGE::Text>& Quadrant::getQuadrant()
{
  return quadrant;
}


int Quadrant::getNumberOfMongolsInQuad() const
{
  return number_of_mongols_in_quad;
}
void Quadrant::setNumberOfMongolsInQuad(int numberOfMongolsInQuad)
{
  number_of_mongols_in_quad = numberOfMongolsInQuad;
}
int Quadrant::getNumberOfStarBasesInQuad() const
{
  return number_of_star_bases_in_quad;
}
void Quadrant::setNumberOfStarBasesInQuad(int numberOfStarBasesInQuad)
{
  number_of_star_bases_in_quad = numberOfStarBasesInQuad;
}
int Quadrant::getNumberOfStarsInQuad() const
{
  return number_of_stars_in_quad;
}
void Quadrant::setNumberOfStarsInQuad(int numberOfStarsInQuad)
{
  number_of_stars_in_quad = numberOfStarsInQuad;
}
bool Quadrant::isDiscovered() const
{
  return discovered;
}
void Quadrant::setDiscovered(bool Discovered)
{
  Quadrant::discovered = Discovered;
}
/*bool Quadrant::isAdjacent() const
{
  return adjacent;
}*/
void Quadrant::setAdjacent(bool Adjacent)
{
  Quadrant::adjacent = Adjacent;
}
