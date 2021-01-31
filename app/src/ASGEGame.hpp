//
// Created by huxy on 23/02/2020.
//

#pragma once

#include "gamelib/Lexington.hpp"
#include "gamelib/Mongol.hpp"
#include "gamelib/Quadrant.hpp"
#include "gamelib/Sector.hpp"
#include "gamelib/Star.hpp"
#include "gamelib/StarBase.hpp"
#include "gamelib/Torpedo.hpp"

#include <Engine/FileIO.h>
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <fstream>
#include <gamelib/game_component.hpp>
#include <iostream>
#include <random>
#include <vector>

class ASGETrek : public ASGE::OGLGame
{
 public:
  explicit ASGETrek(const ASGE::GameSettings& settings);
  ~ASGETrek() override;

  ASGETrek(const ASGETrek&) = delete;
  ASGETrek& operator=(const ASGETrek&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void briefingUserInput();

  void playerActionInput();
  void repair();

  void update(const ASGE::GameTime& us) override;
  void userCommandSelection();
  void briefingStateRenderables();
  void playStateRenderables();
  void renderSprites();
  void renderPlayerActionText();

  void render() override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  void alignInput(ASGE::Text* text, ASGE::Text* input);
  void alignBriefingText();

  void init();
  void initText();
  void initSprites();
  // void initMongols();
  void initSector();
  void initQuadrant();
  void initRandomNumbers();
  void setStatBarWidth();

  /* void setOccupiedSectors();
  void occupiedSectors(); */

  // void playerMovement(int sect_x, int sect_y, int quad_x, int quad_y);
  void playerMovement(int sect, int quad);
  void checkShieldStatus();

  enum class AttackType
  {
    LASER,
    TORPEDO,
  };

  void fireLaser();
  void fireTorpedo(int numberToFire);
  void mongolTakeDamage(AttackType attackType);
  void mongolAction();
  void adjacentQuads(int central_pos);
  void quadrantAppearance();

 private:
  ASGE::GameSettings game_settings;

  std::vector<std::unique_ptr<GameComponent>> game_components;
  int key_callback_id = -1; /**< Key Input Callback ID. */

  std::random_device rd;

  enum class BriefingState
  {
    NAME,
    BRIEFING_REQUIREMENT,
    BRIEFING,
    RESTORE_SAVE,
    COMMAND_LEVEL,
    SELF_DESTRUCT_PASSWORD,
  };

  enum class GameState
  {
    BRIEFING_STATE,
    PLAY_STATE,
    HANDBOOK_STATE,
    WIN_STATE,
    LOSE_STATE,
  };

  enum class PlayerAction
  {
    NONE,
    MOVE,
    WARP,
    // REPAIR,
    LASER,
    TORPEDO,
    SHUP,
    SHDN,
    SELF,
    // DOCK
    // ORBIT,
    // LAND,
    // USE
  };

  enum class SelfDestructState
  {
    NONE,
    CONFIRMATION,
    INITIATE,
  };

  BriefingState briefingState         = BriefingState::NAME;
  GameState gameState                 = GameState::BRIEFING_STATE;
  PlayerAction playerAction           = PlayerAction::NONE;
  SelfDestructState selfDestructState = SelfDestructState::NONE;

  static const int GRID_SIZE  = 64;
  static const int GRID_WIDTH = 8;
  std::array<Sector, GRID_SIZE> sector;
  std::array<Quadrant, GRID_SIZE> quadrant;

  static const int MAX_NUMBER_OF_TORPEDOES = 9;
  std::array<Torpedo, MAX_NUMBER_OF_TORPEDOES> torpedoes;
  int starting_torpedo            = 0;
  int number_of_torpedoes_to_fire = 0;

  static const int NUMBER_OF_BARS = 4;
  std::array<std::unique_ptr<ASGE::Sprite>, NUMBER_OF_BARS> bars{ nullptr };
  std::array<ASGE::Text, NUMBER_OF_BARS> bar_text{};

  Lexington lexington;

  // 8 16 32 64
  static const int NUMBER_OF_MONGOLS = 64;
  size_t number_of_mongols           = 8;
  std::array<Mongol, NUMBER_OF_MONGOLS> mongols;

  static const int NUMBER_OF_STARS = 64;
  std::array<Star, NUMBER_OF_STARS> stars;

  static const int NUMBER_OF_BASES = 64;
  std::array<StarBase, NUMBER_OF_BASES> starBases;

  int mongol_count    = NUMBER_OF_MONGOLS;
  float recharge_rate = 0.05F;

  std::array<int, 8> adjacent_quads = { -1,-1,-1,-1,-1,-1,-1,-1 };

  std::string raw_user_input;

  ASGE::Text user_input{};
  ASGE::Text warp_factor_text{};
  ASGE::Text mongol_count_text{};
  ASGE::Text sector_location_text{};
  ASGE::Text quadrant_location_text{};

  // store in array
  std::string briefing_requirement_input;
  std::string saved_game_input;
  std::string name_input;
  std::string command_level_input;
  std::string password_input;

  std::string play_state_input;

  // store as an array
  float briefing_text_offset = 30;
  ASGE::Text welcome_text{};
  ASGE::Text briefing_requirement_text{};
  ASGE::Text briefing_text{};
  ASGE::Text savedGame_text{};
  ASGE::Text name_text{};
  ASGE::Text command_level_text{};
  ASGE::Text self_destruct_password_text{};

  ASGE::Text command_text{};
  float command_text_offset = 25;
  ASGE::Text move_text{};
  ASGE::Text warp_text{};
  ASGE::Text laser_text{};
  ASGE::Text torpedo_text{};
  ASGE::Text self_destruct_confirmation_text{};
  ASGE::Text initiate_self_destruct_text{};
  ASGE::Text handbook_text{};

  ASGE::Text win_text{};
  ASGE::Text lose_text{};
  
  std::array<ASGE::Text, 8> sector_coords_x{};
  std::array<ASGE::Text, 8> sector_coords_y{};
  std::array<ASGE::Text, 8> quadrant_coords_x{};
  std::array<ASGE::Text, 8> quadrant_coords_y{};

  int string_length = 0;

  int first_pos  = 0;
  int second_pos = 0;
  int third_pos  = 0;
  int fourth_pos = 0;

  // float star_date = 3500.0;

  void dock();
  void move();
  void warp();
  void laser();
  void torpedo();
};
