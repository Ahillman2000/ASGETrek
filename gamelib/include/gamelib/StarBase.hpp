//
// Created by alexa on 30/11/2020.
//

#ifndef ASGETREK_STARBASE_HPP
#define ASGETREK_STARBASE_HPP

#endif // ASGETREK_STARBASE_HPP

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class  StarBase
{
 public:
  StarBase()  = default;
  ~StarBase() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename);
  std::unique_ptr<ASGE::Sprite>& getSprite();

  [[nodiscard]] int getSector() const;
  void setSector(int Sector);
  [[nodiscard]] int getQuadrant() const;
  void setQuadrant(int Quadrant);

 private:
  std::unique_ptr<ASGE::Sprite> starBase;

  int sector = 0;
  int quadrant = 0;
};
