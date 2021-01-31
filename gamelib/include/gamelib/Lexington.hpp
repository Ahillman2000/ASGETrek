//
// Created by alexa on 17/11/2020.
//

#ifndef ASGETREK_LEXICON_H
#define ASGETREK_LEXICON_H

#endif // ASGETREK_LEXICON_H

#include <array>
#include <memory>
#include <Engine/Sprite.h>
#include <Engine/OGLGame.h>

class Lexington
{
 public:
  Lexington() = default;
  ~Lexington() = default;

  bool initialiseSprite(ASGE::Renderer* renderer,const std::string &filename);
  std::unique_ptr<ASGE::Sprite>& getSprite();

  [[nodiscard]] int getCurrentSectPosition() const;
  void setCurrentSectPosition(int currentSectPosition);
  [[nodiscard]] int getCurrentQuadPosition() const;
  void setCurrentQuadPosition(int currentQuadPosition);

  [[nodiscard]] float getBaseHealth() const;
  void setBaseHealth(float baseHealth);
  [[nodiscard]] float getShieldHealth() const;
  void setShieldHealth(float shieldHealth);
  //[[nodiscard]] float getTotalHealth() const;
  //void setTotalHealth(float totalHealth);

  [[nodiscard]] float getLaserTemp() const;
  void setLaserTemp(float laserTemp);
  [[nodiscard]] float getLaserEfficiency() const;
  void setLaserEfficiency(float laserEfficiency);
  [[nodiscard]] int getRemainingTorpedoes() const;
  void setRemainingTorpedoes(int remainingTorpedoes);

  /*[[maybe_unused]] float getEnergyConverterHealth() const;
  [[maybe_unused]] void setEnergyConverterHealth(float energyConverterHealth);
  [[maybe_unused]] float getLifeSupportHealth() const;
  [[maybe_unused]] void setLifeSupportHealth(float lifeSupportHealth);
  [[maybe_unused]] float getWarpEngineHealth() const;
  [[maybe_unused]] void setWarpEngineHealth(float warpEngineHealth);
  [[maybe_unused]] float getImpulseEngineHealth() const;
  [[maybe_unused]] void setImpulseEngineHealth(float impulseEngineHealth);
  [[maybe_unused]] float getShortRangeScannerHealth() const;
  [[maybe_unused]] void setShortRangeScannerHealth(float shortRangeScannerHealth);
  [[maybe_unused]] float getLongRangeScannerHealth() const;
  [[maybe_unused]] void setLongRangeScannerHealth(float longRangeScannerHealth);
  [[maybe_unused]] float getComputerHealth() const;
  [[maybe_unused]] void setComputerHealth(float computerHealth);*/

  [[nodiscard]] int getWarpSpeed() const;
  void setWarpSpeed(int warpSpeed);
  [[nodiscard]] int getShieldStatus() const;
  void setShieldStatus(int shieldStatus);

  [[nodiscard]] int getLaserDamage() const;
  void setLaserDamage(int laserDamage);
  [[nodiscard]] float getTorpedoDamage() const;

 private:
  std::unique_ptr<ASGE::Sprite> lexicon;

  int current_sect_position = 0;
  int current_quad_position = 0;

  float base_health = 100;
  float shield_health = 100;
  //float total_health = base_health + shield_health;
  int shield_status = 0;

  float laser_efficiency = 100;
  float laser_temp = 0;
  int remaining_torpedoes = 9;
  int laser_damage = 25;
  const float TORPEDO_DAMAGE = 50;
  int warp_speed = 1;

  /*float energy_converter_health = 100;
  float life_support_health = 100;
  float warp_engine_health = 100;
  float impulse_engine_health = 100;
  float short_range_scanner_health = 100;
  float long_range_scanner_health = 100;
  float computer_health = 100;*/
};
