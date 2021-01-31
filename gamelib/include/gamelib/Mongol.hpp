//
// Created by alexa on 27/11/2020.
//

#ifndef ASGETREK_MONGOL_HPP
#define ASGETREK_MONGOL_HPP

#endif // ASGETREK_MONGOL_HPP

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Mongol
{
 public:
  Mongol() = default;
  ~Mongol() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename);
  std::unique_ptr<ASGE::Sprite>& getSprite();

  [[nodiscard]] bool isAlive() const;
  void setAlive(bool Alive);
  [[nodiscard]] float getHealth() const;
  void setHealth(float Health);
  [[nodiscard]] float getDamage() const;

  [[nodiscard]] int getAction() const;
  void setAction(int Action);

  [[nodiscard]] int getSector() const;
  void setSector(int Sector);
  [[nodiscard]] int getQuadrant() const;
  void setQuadrant(int Quadrant);

 private:
  std::unique_ptr<ASGE::Sprite> mongol;

  bool alive = true;
  float health = 100;
  float damage = 12.5;

  int action = 0;

 private:
  int sector = 0;
  int quadrant = 0;
};
