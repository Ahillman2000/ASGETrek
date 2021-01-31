//
// Created by alexa on 17/11/2020.
//

#include "gamelib/Lexington.hpp"

bool Lexington::initialiseSprite(ASGE::Renderer* renderer,const std::string &filename)
{
  lexicon = renderer->createUniqueSprite();

  return lexicon->loadTexture(filename);
}

std::unique_ptr<ASGE::Sprite>& Lexington::getSprite()
{
  return lexicon;
}

int Lexington::getCurrentSectPosition() const
{
  return current_sect_position;
}
void Lexington::setCurrentSectPosition(int currentSectPosition)
{
  current_sect_position = currentSectPosition;
}
int Lexington::getCurrentQuadPosition() const
{
  return current_quad_position;
}
void Lexington::setCurrentQuadPosition(int currentQuadPosition)
{
  current_quad_position = currentQuadPosition;
}

float Lexington::getBaseHealth() const
{
  return base_health;
}
void Lexington::setBaseHealth(float baseHealth)
{
  base_health = baseHealth;
}
float Lexington::getShieldHealth() const
{
  return shield_health;
}
void Lexington::setShieldHealth(float shieldHealth)
{
  shield_health = shieldHealth;
}
/*float Lexington::getTotalHealth() const
{
  return total_health;
}
void Lexington::setTotalHealth(float totalHealth)
{
  total_health = totalHealth;
}*/

int Lexington::getWarpSpeed() const
{
  return warp_speed;
}
void Lexington::setWarpSpeed(int warpSpeed)
{
  warp_speed = warpSpeed;
}
int Lexington::getShieldStatus() const
{
  return shield_status;
}
void Lexington::setShieldStatus(int shieldStatus)
{
  shield_status = shieldStatus;
}

float Lexington::getLaserEfficiency() const
{
  return laser_efficiency;
}
void Lexington::setLaserEfficiency(float laserEfficiency)
{
  laser_efficiency = laserEfficiency;
}
int Lexington::getRemainingTorpedoes() const
{
  return remaining_torpedoes;
}
void Lexington::setRemainingTorpedoes(int remainingTorpedoes)
{
  remaining_torpedoes = remainingTorpedoes;
}

float Lexington::getLaserTemp() const
{
  return laser_temp;
}
void Lexington::setLaserTemp(float laserTemp)
{
  laser_temp = laserTemp;
}
float Lexington::getTorpedoDamage() const
{
  return TORPEDO_DAMAGE;
}
int Lexington::getLaserDamage() const
{
  return laser_damage;
}
void Lexington::setLaserDamage(int laserDamage)
{
  laser_damage = laserDamage;
}

/*float Lexington::getEnergyConverterHealth() const
{
  return energy_converter_health;
}
void Lexington::setEnergyConverterHealth(float energyConverterHealth)
{
  energy_converter_health = energyConverterHealth;
}
float Lexington::getLifeSupportHealth() const
{
  return life_support_health;
}
void Lexington::setLifeSupportHealth(float lifeSupportHealth)
{
  life_support_health = lifeSupportHealth;
}
float Lexington::getWarpEngineHealth() const
{
  return warp_engine_health;
}
void Lexington::setWarpEngineHealth(float warpEngineHealth)
{
  warp_engine_health = warpEngineHealth;
}
float Lexington::getImpulseEngineHealth() const
{
  return impulse_engine_health;
}
void Lexington::setImpulseEngineHealth(float impulseEngineHealth)
{
  impulse_engine_health = impulseEngineHealth;
}
float Lexington::getShortRangeScannerHealth() const
{
  return short_range_scanner_health;
}
void Lexington::setShortRangeScannerHealth(float shortRangeScannerHealth)
{
  short_range_scanner_health = shortRangeScannerHealth;
}
float Lexington::getLongRangeScannerHealth() const
{
  return long_range_scanner_health;
}
void Lexington::setLongRangeScannerHealth(float longRangeScannerHealth)
{
  long_range_scanner_health = longRangeScannerHealth;
}
float Lexington::getComputerHealth() const
{
  return computer_health;
}
void Lexington::setComputerHealth(float computerHealth)
{
  computer_health = computerHealth;
}*/

