//
// Created by alexa on 10/12/2020.
//

#ifndef ASGETREK_SECTOR_HPP
#define ASGETREK_SECTOR_HPP

#endif // ASGETREK_SECTOR_HPP
//
// Created by alexa on 27/11/2020.
//

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Sector
{
 public:
  Sector() = default;
  ~Sector() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename);
  std::unique_ptr<ASGE::Sprite>& getSprite();
  //[[nodiscard]] bool isOccupied() const;
  void setOccupied(bool Occupied);

 private:
  std::unique_ptr<ASGE::Sprite> grid;
  bool occupied = false;
};
