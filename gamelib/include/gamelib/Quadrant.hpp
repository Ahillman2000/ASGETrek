//
// Created by alexa on 10/12/2020.
//

#ifndef ASGETREK_QUADRANT_HPP
#define ASGETREK_QUADRANT_HPP

#endif // ASGETREK_QUADRANT_HPP
#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Quadrant
{
 public:
  Quadrant() = default;
  ~Quadrant() = default;

  void initialiseText(ASGE::Renderer* renderer, std::string string, ASGE::Colour colour, ASGE::Point2D position);
  void setTextString(std::string string);
  void setTextColour(ASGE::Colour colour);
  //void setTextPosition(ASGE::Point2D position);

  std::unique_ptr<ASGE::Text>& getQuadrant();

  [[nodiscard]] int getNumberOfMongolsInQuad() const;
  void setNumberOfMongolsInQuad(int numberOfMongolsInQuad);
  [[nodiscard]] int getNumberOfStarBasesInQuad() const;
  void setNumberOfStarBasesInQuad(int numberOfStarBasesInQuad);
  [[nodiscard]] int getNumberOfStarsInQuad() const;
  void setNumberOfStarsInQuad(int numberOfStarsInQuad);

  [[nodiscard]] bool isDiscovered() const;
  void setDiscovered(bool Discovered);
  [[nodiscard]] bool isAdjacent() const;
  void setAdjacent(bool Adjacent);

 private:
  std::unique_ptr<ASGE::Text> quadrant;

  int number_of_mongols_in_quad = 0;
  int number_of_star_bases_in_quad = 0;
  int number_of_stars_in_quad = 0;

  bool discovered = false;
  bool adjacent = false;
};
