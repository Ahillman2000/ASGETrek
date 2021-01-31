//
// Created by alexa on 11/12/2020.
//

#ifndef ASGETREK_TORPEDO_HPP
#define ASGETREK_TORPEDO_HPP

#endif // ASGETREK_TORPEDO_HPP

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Torpedo
{
 public:
  Torpedo()  = default;
  ~Torpedo() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename, short z_order);
  std::unique_ptr<ASGE::Sprite>& getSprite();
  [[nodiscard]] bool isFired() const;
  void setFired(bool Fired);

 private:
  std::unique_ptr<ASGE::Sprite> torpedo;
  bool fired = false;
};
