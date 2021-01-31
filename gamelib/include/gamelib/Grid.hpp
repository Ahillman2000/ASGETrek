//
// Created by alexa on 27/11/2020.
//

#ifndef ASGETREK_GRID_HPP
#define ASGETREK_GRID_HPP

#endif // ASGETREK_GRID_HPP

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Grid
{
 public:
  Grid() = default;
  ~Grid() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename);
  std::unique_ptr<ASGE::Sprite>& getSprite();
  bool isOccupied() const;
  void setOccupied(bool Occupied);
  /*TODO - placement function
   *     - text?
   */

 private:
  std::unique_ptr<ASGE::Sprite> grid;
  bool occupied = false;
};
