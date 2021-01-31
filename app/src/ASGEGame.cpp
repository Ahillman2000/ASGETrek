#include "ASGEGame.hpp"
#include <array>
#include <Engine/Logger.hpp>

/*
 * TODO
 *  - sprites rendering on top of each other - occupancy
 *  - update so that number of mongols is determined by command level
*/

/// Initialises the game.
/// Setup your game and initialise the core components.
/// @param settings
ASGETrek::ASGETrek(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &ASGETrek::keyHandler, this);
  inputs->use_threads = true;
  //toggleFPS();
  init();
}

/// Destroys the game.
ASGETrek::~ASGETrek()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
}

void ASGETrek::init()
{
  renderer->setClearColour(ASGE::COLOURS::BLACK);

  initRandomNumbers();
  initSector();
  initQuadrant();
  initSprites();
  initText();
}

void ASGETrek::initRandomNumbers()
{
  std::uniform_int_distribution<int> random_grid(0,63);

  lexington.setCurrentSectPosition(random_grid(rd));
  lexington.setCurrentQuadPosition(random_grid(rd));

  // todo - cmd lvl
  for (size_t i = 0; i < NUMBER_OF_MONGOLS; ++i)
  {
    int mongol_sector = random_grid(rd);
    //int mongol_quadrant = random_grid(rd);
    mongols[i].setSector(mongol_sector);
    sector[static_cast<size_t>(mongol_sector)].setOccupied(true);
  }
  for (size_t i = 0; i < NUMBER_OF_STARS; ++i)
  {
    int star_sector = random_grid(rd);
    stars[i].setSector(star_sector);
    sector[static_cast<size_t>(star_sector)].setOccupied(true);
  }
  for (size_t i = 0; i < NUMBER_OF_BASES; ++i)
  {
    int base_sector = random_grid(rd);
    starBases[i].setSector(base_sector);
    sector[static_cast<size_t>(base_sector)].setOccupied(true);
  }
}

void ASGETrek::initText()
{
  welcome_text
    .setFont(renderer->getDefaultFont())
    .setString("Welcome aboard Captain!")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, 100 });

  name_text
    .setFont(renderer->getDefaultFont())
    .setString("Please enter your name: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, welcome_text.getPosition().y + 75 });

  briefing_requirement_text
    .setFont(renderer->getDefaultFont())
    .setString("Will you require a briefing <Y/N>?")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, name_text.getPosition().y + 75 });

  briefing_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ static_cast<float>(game_settings.window_width * 0.1),
                              static_cast<float>(game_settings.window_height * 0.25)});

  savedGame_text
    .setFont(renderer->getDefaultFont())
    .setString("Restore a saved game <Y/N>?")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, briefing_requirement_text.getPosition().y + briefing_text_offset });

  command_level_text
    .setFont(renderer->getDefaultFont())
    .setString("For verification, enter your command level (1-4): ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, savedGame_text.getPosition().y + briefing_text_offset });

  self_destruct_password_text
    .setFont(renderer->getDefaultFont())
    .setString("LT. Commander, please enter your "
                                        "self-destruct password: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ 100, command_level_text.getPosition().y + briefing_text_offset });

  user_input
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE);

  command_text
    .setFont(renderer->getDefaultFont())
    .setString("Command: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({50, static_cast<float>(game_settings.window_height)/ 2});

  move_text
    .setFont(renderer->getDefaultFont())
    .setString("Move: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, command_text.getPosition().y + command_text_offset});

  warp_text
    .setFont(renderer->getDefaultFont())
    .setString("Warp speed 1-8: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, command_text.getPosition().y + command_text_offset});

  laser_text
    .setFont(renderer->getDefaultFont())
    .setString("Amount to fire: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, command_text.getPosition().y + command_text_offset});

  torpedo_text
    .setFont(renderer->getDefaultFont())
    .setString("Number to fire: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, command_text.getPosition().y + command_text_offset});

  self_destruct_confirmation_text
    .setFont(renderer->getDefaultFont())
    .setString("Captain, this is a desperate measure."
               "\nAre you sure you want to do this <Y/N>? ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, command_text.getPosition().y + command_text_offset});

  initiate_self_destruct_text
    .setFont(renderer->getDefaultFont())
    .setString("Please enter your Self Destruct password: ")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({75, self_destruct_confirmation_text.getPosition().y+self_destruct_confirmation_text.getHeight() + 50});

  handbook_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ static_cast<float>(game_settings.window_width * 0.1),
                              static_cast<float>(game_settings.window_height * 0.1)});

  win_text
    .setFont(renderer->getDefaultFont())
    .setString("YOU WIN")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({static_cast<float>(game_settings.window_width) / 2.0F,
                  static_cast<float>(game_settings.window_height) / 2.0F});

  lose_text
    .setFont(renderer->getDefaultFont())
    .setString("YOU LOSE")
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({static_cast<float>(game_settings.window_width) / 2.0F,
                  static_cast<float>(game_settings.window_height) / 2.0F});

  for (size_t i = 0; i < 8; ++i)
  {
    sector_coords_x[i]
      .setFont(renderer->getDefaultFont())
      .setColour(ASGE::COLOURS::WHITE)
      .setPosition({ sector[i].getSprite()->xPos() + 10, sector[0].getSprite()->yPos()})
      .setZOrder(1)
      .setString(std::to_string(i + 1));

    sector_coords_y[i]
      .setFont(renderer->getDefaultFont())
      .setColour(ASGE::COLOURS::WHITE)
      .setPosition({ sector[0].getSprite()->xPos() - 10, sector[i * 8].getSprite()->yPos() + 23})
      .setZOrder(1)
      .setString(std::to_string(i + 1));

    quadrant_coords_x[i]
      .setFont(renderer->getDefaultFont())
      .setColour(ASGE::COLOURS::WHITE)
      .setPosition({ quadrant[i].getQuadrant()->getPosition().x + quadrant[i].getQuadrant()->getWidth()/2, quadrant[0].getQuadrant()->getPosition().y - 25})
      .setZOrder(1)
      .setString(std::to_string(i + 1));

    quadrant_coords_y[i]
      .setFont(renderer->getDefaultFont())
      .setColour(ASGE::COLOURS::WHITE)
      .setPosition({ quadrant[0].getQuadrant()->getPosition().x - 25, quadrant[i * 8].getQuadrant()->getPosition().y + quadrant[i * 8].getQuadrant()->getHeight()/2})
      .setZOrder(1)
      .setString(std::to_string(i + 1));
  }

  for (size_t i = 0; i < 4; ++i)
  {
    bar_text[i]
      .setFont(renderer->getDefaultFont())
      .setColour(ASGE::COLOURS::WHITE)
      .setZOrder(1)
      .setPositionX(bars[0]->xPos());
  }
  bar_text[0].setString("Health");
  bar_text[0].setPositionY(bars[0]->yPos() - bar_text[0].getHeight());

  bar_text[1].setString("Shields");
  bar_text[1].setPositionY(bars[1]->yPos() - bar_text[1].getHeight());

  bar_text[2].setString("Laser efficiency");
  bar_text[2].setPositionY(bars[2]->yPos() - bar_text[2].getHeight());

  bar_text[3].setString("Laser Temperature");
  bar_text[3].setPositionY(bars[3]->yPos() - bar_text[3].getHeight());

  warp_factor_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({ static_cast<float>(game_settings.window_width) / 2.0F, 50});

  mongol_count_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({static_cast<float>(game_settings.window_width) / 2.0F, 75});

  sector_location_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({static_cast<float>(game_settings.window_width) / 2.0F, 250});

  quadrant_location_text
    .setFont(renderer->getDefaultFont())
    .setColour(ASGE::COLOURS::WHITE)
    .setPosition({static_cast<float>(game_settings.window_width) / 2.0F, 275});
}

void ASGETrek::alignInput(ASGE::Text* text, ASGE::Text* input)
{
  input->setPosition({ text->getPosition().x + text->getWidth() + 10,
                       text->getPosition().y + text->getHeight() });
}

void ASGETrek::initSector()
{
  float grid_x_pos = 0;
  float grid_y_pos = 0;

  for (size_t i = 0; i < GRID_SIZE; ++i)
  {
    sector[i].initialiseSprite(renderer.get(), "/data/grid_coord.png");
    sector[i].getSprite()->xPos(grid_x_pos + 25);
    sector[i].getSprite()->yPos(grid_y_pos + 25);

    grid_x_pos += sector[i].getSprite()->width() * 1.1F;

    if (grid_x_pos >= sector[i].getSprite()->width() * 1.1F * GRID_WIDTH)
    {
      grid_x_pos = 0;
      grid_y_pos += sector[i].getSprite()->height() * 1.1F;
    }
  }
}

void ASGETrek::initQuadrant()
{
  float grid_x_pos = 0;
  float grid_y_pos = 0;

  for (size_t i = 0; i < GRID_SIZE; ++i)
  {
    quadrant[i].initialiseText(renderer.get(), ". . .", ASGE::COLOURS::WHITE, { 625 + grid_x_pos, 50 + grid_y_pos});

    grid_x_pos += 80;

    if (grid_x_pos >= 80 * GRID_WIDTH)
    {
      grid_x_pos = 0;
      grid_y_pos += 40;
    }
  }
}

void ASGETrek::initSprites()
{
  lexington.initialiseSprite(renderer.get(), "/data/lexington_white.png");
  lexington.getSprite()->setGlobalZOrder(1);

  lexington.getSprite()->xPos(sector[static_cast<size_t>(lexington.getCurrentSectPosition())].getSprite()->xPos());
  lexington.getSprite()->yPos(sector[static_cast<size_t>(lexington.getCurrentSectPosition())].getSprite()->yPos());

  quadrant[static_cast<size_t>(lexington.getCurrentQuadPosition())].setDiscovered(true);

  // todo - cmd lvl
  for (size_t i = 0; i < NUMBER_OF_MONGOLS; ++i)
  {
    mongols[i].initialiseSprite(renderer.get(), "/data/mongol.png");
    mongols[i].getSprite()->setGlobalZOrder(1);
    mongols[i].setQuadrant(static_cast<int>(i));
    quadrant[i].setNumberOfMongolsInQuad(quadrant[i].getNumberOfMongolsInQuad() + 1);

    mongols[i].getSprite()->xPos(sector[static_cast<size_t>(mongols[i].getSector())].getSprite()->xPos());
    mongols[i].getSprite()->yPos(sector[static_cast<size_t>(mongols[i].getSector())].getSprite()->yPos());
  }

  for (size_t i = 0; i < NUMBER_OF_STARS; ++i)
  {
    stars[i].initialiseSprite(renderer.get(), "/data/star.png");
    stars[i].getSprite()->setGlobalZOrder(1);
    stars[i].setQuadrant(static_cast<int>(i));
    quadrant[i].setNumberOfStarsInQuad(quadrant[i].getNumberOfStarsInQuad() + 1);
    stars[i].getSprite()->xPos(sector[static_cast<size_t>(stars[i].getSector())].getSprite()->xPos());
    stars[i].getSprite()->yPos(sector[static_cast<size_t>(stars[i].getSector())].getSprite()->yPos());
  }
  for (size_t i = 0; i < NUMBER_OF_BASES; ++i)
  {
    starBases[i].initialiseSprite(renderer.get(), "/data/starBase.png");
    starBases[i].getSprite()->setGlobalZOrder(1);
    starBases[i].setQuadrant(static_cast<int>(i));
    quadrant[i].setNumberOfStarBasesInQuad(quadrant[i].getNumberOfStarBasesInQuad() + 1);
    starBases[i].getSprite()->xPos(sector[static_cast<size_t>(starBases[i].getSector())].getSprite()->xPos());
    starBases[i].getSprite()->yPos(sector[static_cast<size_t>(starBases[i].getSector())].getSprite()->yPos());
  }

  for (size_t i = 0; i < MAX_NUMBER_OF_TORPEDOES; ++i)
  {
    torpedoes[i].initialiseSprite(renderer.get(), "/data/torpedo.png", 1);

    if (i <= 2)
    {
      torpedoes[i].getSprite()->xPos(static_cast<float>(400 + 10 * i));
      torpedoes[i].getSprite()->yPos(100);
    }
    else if (i <= 5)
    {
      torpedoes[i].getSprite()->xPos(static_cast<float>(400 + 10 * (i - 3)));
      torpedoes[i].getSprite()->yPos(115);
    }
    else
    {
      torpedoes[i].getSprite()->xPos(static_cast<float>(400 + 10 * (i - 6)));
      torpedoes[i].getSprite()->yPos(130);
    }
  }

  for (size_t i = 0; i < 4; ++i)
  {
    bars[i] = renderer->createUniqueSprite();
    bars[i]->setGlobalZOrder(1);
    bars[i]->xPos(50);
    bars[i]->yPos(static_cast<float>(500 + (i * 50)));
  }
  bars[0]->loadTexture("/data/health_bar.png");
  bars[1]->loadTexture("/data/shield_bar.png");
  bars[2]->loadTexture("/data/laser_efficiency.png");
  bars[3]->loadTexture("/data/laser_temp.png");
}

/// Processes key inputs.
/// This function is added as a callback to handle the game's
/// keyboard input. For this game, calls to this function
/// are not thread safe, so you may alter the game's state
/// but your code needs to designed to prevent data-races.
/// @param data
/// @see KeyEvent
void ASGETrek::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }

  // PLAYER IN MENU
  if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_PRESSED &&
    gameState == GameState::BRIEFING_STATE)
  {
    briefingUserInput();
  }

  // PLAYER IN GAME
  if (gameState == GameState::PLAY_STATE)
  {
    if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      play_state_input = raw_user_input;
      raw_user_input.clear();
      playerActionInput();
    }
  }

  if (gameState == GameState::HANDBOOK_STATE)
  {
    if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_PRESSED)
    {
      gameState = GameState::PLAY_STATE;
    }
  }

  if (key->action == ASGE::KEYS::KEY_PRESSED)
  {
    raw_user_input += static_cast<char>(key->key);
  }

  if (key->key == ASGE::KEYS::KEY_BACKSPACE && !raw_user_input.empty())
  {
    raw_user_input.pop_back();
  }
}

void ASGETrek::briefingUserInput()
{
  if (briefingState == BriefingState::NAME)
  {
    name_input = raw_user_input;
    briefingState = BriefingState::BRIEFING_REQUIREMENT;
    raw_user_input.clear();

    for (size_t i = 1; i < name_input.length(); ++i)
    {
      name_input[i] = static_cast<char>(std::tolower(name_input[i]));
    }

    briefing_text.setString("Welcome to mission briefing Captain " + name_input + "\n\n"

      "As you know, you have been assigned command of the U.S.S Lexington, the "
      "newest ship in the fleet.\n"
      "Under your command are 387 enlisted crewmen and 43 officers, bring them home "
      "safe.\n"
      "Your mission is to protect the galaxy from the dreaded Mongol Empire.\n\n"

      "If you should have any queries during your mission relating to commands, "
      "type 'HANDBOOK'\n"
      "into the command console to bring up the captain's handbook, which provides "
      "the guideline\n"
      "commands for you to issue and what they do.\n\n"

      "Good luck Captain and don't forget the prime directive.\n\n"

      "press ENTER to continue");

    for (size_t i = 1; i < name_input.length(); ++i)
    {
      name_input[i] = static_cast<char>(std::toupper(name_input[i]));
    }

    handbook_text.setString(
      "CAPTAIN " + name_input + "'S HANDBOOK\n\n"

      " MOVE quad_x, quad_y, sector_x, sector_y: To move to a specified quadrant "
      "and sector\n\n"
      " MOVE sector_x, sector_y: To move to a specified sector within a quadrant\n\n"
      " WARP: Set warp speed between 1-8\n\n"
      " REPAIR: Repairs the ship and restores health\n\n"
      " LASER:  Requires sector locations for firing, effectiveness influenced by "
      "distance from target\n\n"
      " TORPEDO: 3 torpedo tubes available. Requires the number of torpedoes to be "
      "fired and the sector locations\n"
      "          for each torpedo to be specified.\n\n"
      " SHUP: Raises shields\n\n"
      " SHDN: Lowers shields\n\n"
      " SELF: Activates the self-destruct protocol\n\n"
      " DOCK: When the sip is in a sector adjacent to a StarBase, the ship will "
      "resupply and repair.\n\n"
      //" ORBIT: Enters an orbit around an  adjacent planet, also scans the
      //planet\n\n" " LAND: Sends a landing party to a planet to look for items\n\n"
      //" USE: Use any items you have found during your mission\n\n"
      "Press ENTER to close handbook");
  }
  else if (briefingState == BriefingState::BRIEFING_REQUIREMENT)
  {
    briefing_requirement_input = raw_user_input;
    raw_user_input.clear();

    if (briefing_requirement_input.find('Y') != std::string::npos)
    {
      briefingState = BriefingState::BRIEFING;
      raw_user_input.clear();
    }
    else if (briefing_requirement_input.find('N') != std::string::npos)
    {
      briefingState = BriefingState::RESTORE_SAVE;
      raw_user_input.clear();
    }
  }
  else if (briefingState == BriefingState::BRIEFING)
  {
    briefingState = BriefingState::RESTORE_SAVE;
  }
  else if (briefingState == BriefingState::RESTORE_SAVE)
  {
    saved_game_input = raw_user_input;
    raw_user_input.clear();

    if (saved_game_input.find('Y') != std::string::npos || saved_game_input.find('N') != std::string::npos )
    {
      briefingState = BriefingState::COMMAND_LEVEL;
    }
  }
  else if (briefingState == BriefingState::COMMAND_LEVEL)
  {
    command_level_input = raw_user_input;
    raw_user_input.clear();

    if (command_level_input.find('1') != std::string::npos)
    {
      number_of_mongols = 8;
      briefingState = BriefingState::SELF_DESTRUCT_PASSWORD;
    }
    else if (command_level_input.find('2') != std::string::npos)
    {
      number_of_mongols = 16;
      briefingState = BriefingState::SELF_DESTRUCT_PASSWORD;
    }
    else if (command_level_input.find('3') != std::string::npos)
    {
      number_of_mongols = 32;
      briefingState = BriefingState::SELF_DESTRUCT_PASSWORD;
    }
    else if (command_level_input.find('4') != std::string::npos)
    {
      number_of_mongols = 64;
      briefingState = BriefingState::SELF_DESTRUCT_PASSWORD;
    }
    Logging::DEBUG(std::to_string(number_of_mongols) + " mongols");
    //initMongols();
  }
  else if (briefingState == BriefingState::SELF_DESTRUCT_PASSWORD)
  {
    password_input = raw_user_input;
    gameState = GameState::PLAY_STATE;
    raw_user_input.clear();
  }
}
void ASGETrek::playerActionInput()
{
  if (play_state_input.find("REPAIR") != std::string::npos)
  {
    repair();
    mongolAction();
  }

  // TODO - Only if player is adjacent to a star-base
  if (play_state_input.find("DOCK") != std::string::npos)
  {
    dock();
  }

  if (playerAction == PlayerAction::MOVE)
  {
    move();
  }
  if (playerAction == PlayerAction::WARP)
  {
    warp();
  }
  if (playerAction == PlayerAction::LASER)
  {
    laser();
  }

  if (playerAction == PlayerAction::TORPEDO)
  {
    torpedo();
  }

  if (selfDestructState == SelfDestructState::CONFIRMATION)
  {
    if (play_state_input.find('Y') != std::string::npos)
    {
      selfDestructState = SelfDestructState::INITIATE;
      alignInput(&initiate_self_destruct_text, &user_input);
      raw_user_input.clear();
    }
    else if (play_state_input.find('N') != std::string::npos)
    {
      playerAction = PlayerAction::NONE;
      selfDestructState = SelfDestructState::NONE;
      raw_user_input.clear();
    }
  }

  else if (selfDestructState == SelfDestructState::INITIATE)
  {
    if (play_state_input.find(password_input) != std::string::npos)
    {
      signalExit();
    }
    else
    {
      selfDestructState = SelfDestructState::NONE;
      playerAction = PlayerAction::NONE;
    }
  }
  /*if (mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].isAlive())
  {
    mongolAction();
  }*/
}
void ASGETrek::torpedo()
{
  if (play_state_input.find('1') != std::string::npos)
  {
    number_of_torpedoes_to_fire = 1;
  }
  else if (play_state_input.find('2') != std::string::npos)
  {
    number_of_torpedoes_to_fire = 2;
  }
  else if (play_state_input.find('3') != std::string::npos)
  {
    number_of_torpedoes_to_fire = 3;
  }
  else
  {
    number_of_torpedoes_to_fire = 0;
  }

  if (
    lexington.getRemainingTorpedoes() > 0 &&
    number_of_torpedoes_to_fire <= lexington.getRemainingTorpedoes())
  {
    fireTorpedo(number_of_torpedoes_to_fire);
    mongolAction();
    }
    playerAction = PlayerAction::NONE;
}
void ASGETrek::laser()
{
  lexington.setLaserDamage(0);

  if (play_state_input.length() == 2)
  {
    lexington.setLaserDamage(play_state_input[1] - 48);
  }
  else if (play_state_input.length() == 3)
  {
    lexington.setLaserDamage(
      (play_state_input[1] - 48) * 10 + (play_state_input[2] - 48));
  }
  else if (play_state_input.length() == 4)
  {
    lexington.setLaserDamage((play_state_input[1] - 48) * 100 + (play_state_input[2] - 48) * 10 + (play_state_input[3] - 48));
  }
    fireLaser();
}
void ASGETrek::warp()
{
  if (play_state_input[1] - 48 > 0 && play_state_input[1] - 48 < 9)
  {
    lexington.setWarpSpeed(static_cast<int>(play_state_input[1] - 48));
    mongolAction();
  }
}
void ASGETrek::move()
{
  string_length = static_cast<int>(play_state_input.length());

  if (string_length == 4)
  {
    first_pos  = static_cast<unsigned char>(play_state_input[1]);
    second_pos = static_cast<unsigned char>(play_state_input[3]);

    if (
      play_state_input[1] - 48 > 0 && play_state_input[1] - 48 < 9 &&
      play_state_input[3] - 48 > 0 && play_state_input[3] - 48 < 9)
    {
      int sector_destination   = (first_pos - 49) + ((second_pos - 49) * GRID_WIDTH);
      int quadrant_destination = lexington.getCurrentQuadPosition();

      playerMovement(sector_destination, quadrant_destination);
      mongolAction();
    }
  }
  else if (string_length == 8)
  {
    first_pos  = static_cast<unsigned char>(play_state_input[1]);
    second_pos = static_cast<unsigned char>(play_state_input[3]);
    third_pos  = static_cast<unsigned char>(play_state_input[5]);
    fourth_pos = static_cast<unsigned char>(play_state_input[7]);

    if (
      play_state_input[1] - 48 > 0 && play_state_input[1] - 48 < 9 &&
      play_state_input[3] - 48 > 0 && play_state_input[3] - 48 < 9 &&
      play_state_input[5] - 48 > 0 && play_state_input[5] - 48 < 9 &&
      play_state_input[7] - 48 > 0 && play_state_input[7] - 48 < 9)
    {
      int sector_destination = (first_pos - 49) + ((second_pos - 49) * GRID_WIDTH);
      int quadrant_destination = (third_pos - 49) + ((fourth_pos - 49) * GRID_WIDTH);

      playerMovement(sector_destination, quadrant_destination);
    }
  }
}
void ASGETrek::dock()
{
  for (size_t i = 0; i < MAX_NUMBER_OF_TORPEDOES; ++i)
  {
    torpedoes[i].setFired(false);
  }
  lexington.setRemainingTorpedoes(9);
  starting_torpedo = 0;
  lexington.setBaseHealth(100);
    // lexington.setShieldHealth(100);
}
void ASGETrek::repair()
{
  lexington.setBaseHealth(lexington.getBaseHealth() + 25);
}

void ASGETrek::playerMovement(int sect, int quad)
{
  lexington.setCurrentSectPosition(sect);
  lexington.setCurrentQuadPosition(quad);

  lexington.getSprite()->xPos(sector[static_cast<size_t>(lexington.getCurrentSectPosition())].getSprite()->xPos());
  lexington.getSprite()->yPos(sector[static_cast<size_t>(lexington.getCurrentSectPosition())].getSprite()->yPos());
}

void ASGETrek::checkShieldStatus()
{
  if (lexington.getShieldStatus() == 0)
  {
    lexington.getSprite()->loadTexture("/data/lexington_white.png");
    playerAction = PlayerAction::NONE;
    lexington.setShieldHealth(0);
  }
  else if (lexington.getShieldStatus() == 1)
  {
    lexington.getSprite()->loadTexture("/data/lexington_yellow.png");
    playerAction = PlayerAction::NONE;
    lexington.setShieldHealth(100);
  }
}

void ASGETrek::fireLaser()
{
  if (lexington.getLaserDamage() <= static_cast<int>(lexington.getLaserEfficiency()))
  {
    mongolTakeDamage(AttackType::LASER);

    lexington.setLaserEfficiency(
      lexington.getLaserEfficiency() - static_cast<float>(lexington.getLaserDamage()));

    lexington.setLaserTemp(lexington.getLaserTemp() + static_cast<float>(lexington.getLaserDamage()));
    mongolAction();
  }
}

void ASGETrek::fireTorpedo(int numberToFire)
{
  for (int i = 0; i < numberToFire; ++i)
  {
    torpedoes[static_cast<size_t>(starting_torpedo)].setFired(true);
    starting_torpedo++;
    lexington.setRemainingTorpedoes(lexington.getRemainingTorpedoes() - 1);
  }

  mongolTakeDamage(AttackType::TORPEDO);
}

void ASGETrek::mongolTakeDamage(AttackType attackType)
{
  if (
    quadrant[static_cast<size_t>(lexington.getCurrentQuadPosition())]
        .getNumberOfMongolsInQuad() > 0 &&
    mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].isAlive())
  {
    if (attackType == AttackType::TORPEDO)
    {
      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].setHealth(
        mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getHealth() - lexington.getTorpedoDamage() *
                                   static_cast<float>(number_of_torpedoes_to_fire));
    }
    else
    {
      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].setHealth(
        mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getHealth() - static_cast<float>(lexington.getLaserDamage()));
    }

    if (mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getHealth() <= 0)
    {
      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].setAlive(
        false);
    }
    if (
      !mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].isAlive() &&
      mongol_count > 0)
    {
      mongol_count -= 1;
    }
  }

  if (
    !mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].isAlive() &&
    quadrant[static_cast<size_t>(lexington.getCurrentQuadPosition())]
        .getNumberOfMongolsInQuad() > 0)
  {
    quadrant[static_cast<size_t>(lexington.getCurrentQuadPosition())]
      .setNumberOfMongolsInQuad(
        quadrant[static_cast<size_t>(lexington.getCurrentQuadPosition())]
          .getNumberOfMongolsInQuad() -
        1);
  }
}

void ASGETrek::mongolAction()
{
  if (mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].isAlive())
  {
    std::uniform_int_distribution<int> random_grid(0,63);
    std::uniform_int_distribution<int> enemy_action(0,1);

    mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].setAction(enemy_action(rd));

    if (mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getAction() == 0)
    {
      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].setSector(random_grid(rd));

      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getSprite()->xPos(sector[static_cast<size_t>(random_grid(rd))].getSprite()->xPos());
      mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getSprite()->yPos(sector[static_cast<size_t>(random_grid(rd))].getSprite()->yPos());
    }
    else
    {
      lexington.setBaseHealth(lexington.getBaseHealth() - mongols[static_cast<size_t>(lexington.getCurrentQuadPosition())].getDamage());
    }
  }
}

void ASGETrek::setStatBarWidth()
{
  bars[0]->width(lexington.getBaseHealth() * 2);
  bars[1]->width(lexington.getShieldHealth() * 2);
  bars[2]->width(lexington.getLaserEfficiency() * 2);
  bars[3]->width(lexington.getLaserTemp() * 2);
}

void ASGETrek::adjacentQuads(int central_pos)
{
  /*
   * TODO - make array global
   * - reset array at start of func
   * - move quads out
   * - change so that it can work with the quads and to find if player is adjacent to base
  */

  adjacent_quads = {-1,-1,-1,-1,-1,-1,-1,-1};
  //int player_quad = current_quad_position;

   // top_left     = 0
   // top          = 1
   // top_right    = 2
   // left         = 3
   // right        = 4
   // bottom_left  = 5
   // bottom       = 6
   // bottom_right = 7

  // 0 = right, down, down right
  if (central_pos == 0)
  {
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
    adjacent_quads[7] = central_pos + GRID_WIDTH + 1;
  }
  // 7 = left, down, left down
  else if (central_pos == 7)
  {
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
    adjacent_quads[5] = central_pos + GRID_WIDTH - 1;
  }
  // 56 = right, up, right up
  else if (central_pos == 56)
  {
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[2] = central_pos - GRID_WIDTH + 1;
  }
  // 63 = left, up, left up
  else if (central_pos == 63)
  {
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[0] = central_pos - GRID_WIDTH - 1;
  }
  // 1,2,3,4,5,6 = left, right, left down, down, down right
  else if (central_pos == 1 || central_pos == 2 || central_pos == 3 || central_pos == 4 || central_pos == 5 || central_pos == 6)
  {
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[5] = central_pos + GRID_WIDTH - 1;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
    adjacent_quads[7] = central_pos + GRID_WIDTH + 1;
  }
  // 57,58,59,60,61,62 = left, right, up, left up, right up
  else if (central_pos == 57 || central_pos == 58 || central_pos == 59 || central_pos == 60 || central_pos == 61 || central_pos == 62)
  {
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[0] = central_pos - GRID_WIDTH - 1;
    adjacent_quads[2] = central_pos - GRID_WIDTH + 1;
  }
  // 8,16,24,32,40,48 = top, top right, right, bottom right, bottom
  else if (central_pos == 8 || central_pos == 16 || central_pos == 24 || central_pos == 32 || central_pos == 40 || central_pos == 48)
  {
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[2] = central_pos - GRID_WIDTH + 1;
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[7] = central_pos + GRID_WIDTH + 1;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
  }
  // 15,23,31,39,47,55 = top, top left, left, bottom left, bottom
  else if (central_pos == 15 || central_pos == 23 || central_pos == 31 || central_pos == 39 || central_pos == 47 || central_pos == 55)
  {
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[0] = central_pos - GRID_WIDTH - 1;
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[5] = central_pos + GRID_WIDTH - 1;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
  }
  else
  {
    adjacent_quads[3] = central_pos - 1;
    adjacent_quads[4] = central_pos + 1;
    adjacent_quads[1] = central_pos - GRID_WIDTH;
    adjacent_quads[6] = central_pos + GRID_WIDTH;
    adjacent_quads[0] = central_pos - GRID_WIDTH - 1;
    adjacent_quads[2] = central_pos - GRID_WIDTH + 1;
    adjacent_quads[5] = central_pos + GRID_WIDTH - 1;
    adjacent_quads[7] = central_pos + GRID_WIDTH + 1;
  }
}

void ASGETrek::quadrantAppearance()
{
  for (size_t i = 0; i < 8; ++i)
  {
    if (adjacent_quads[i] > -1)
    {
      quadrant[static_cast<size_t>(adjacent_quads[i])].setAdjacent(true);
      quadrant[static_cast<size_t>(adjacent_quads[i])].setDiscovered(true);
    }
  }

  for (size_t i = 0; i < GRID_SIZE; ++i)
  {
    if (lexington.getCurrentQuadPosition() == static_cast<int>(i))
    {
      quadrant[i].setTextString(std::to_string(quadrant[i].getNumberOfMongolsInQuad()) + " " + std::to_string(quadrant[i].getNumberOfStarsInQuad()) + " " + std::to_string(quadrant[i].getNumberOfStarBasesInQuad()));
      quadrant[i].setTextColour(ASGE::COLOURS::RED);
      quadrant[i].setDiscovered(true);
    }
    else if (quadrant[i].isDiscovered())
    {
      quadrant[i].setTextString(std::to_string(quadrant[i].getNumberOfMongolsInQuad()) + " " + std::to_string(quadrant[i].getNumberOfStarsInQuad()) + " " + std::to_string(quadrant[i].getNumberOfStarBasesInQuad()));
      quadrant[i].setTextColour(ASGE::COLOURS::GREEN);
    }
    else
    {
      quadrant[i].setTextString(". . .");
      quadrant[static_cast<size_t>(i)].setTextColour(ASGE::COLOURS::GRAY);
    }
  }
}

/// Updates your game and all it's components.
/// @param us
void ASGETrek::update(const ASGE::GameTime& us)
{
  for (auto& gc : game_components)
  {
    gc->update(us.deltaInSecs());
  }

  if (lexington.getBaseHealth() > 100)
  {
    lexington.setBaseHealth(100);
  }

  if (lexington.getLaserTemp() >= 0)
  {
    lexington.setLaserTemp(lexington.getLaserTemp() - recharge_rate);
  }
  if (lexington.getLaserEfficiency() <= 100)
  {
    lexington.setLaserEfficiency(lexington.getLaserEfficiency() + recharge_rate);
  }
  if (lexington.getBaseHealth() <= lexington.getBaseHealth() - mongols[0].getDamage())
  {
    lexington.setBaseHealth(lexington.getBaseHealth() - 0.25F);
  }

  user_input.setString(raw_user_input);
  warp_factor_text.setString("Warp: " + std::to_string(lexington.getWarpSpeed()));
  mongol_count_text.setString("Mongols: " + std::to_string(mongol_count));
  sector_location_text.setString("Sector: " + std::to_string(lexington.getCurrentSectPosition()));
  quadrant_location_text.setString("Quadrant: " + std::to_string(lexington.getCurrentQuadPosition()));

  // text align for menu text
  if (gameState == GameState::BRIEFING_STATE)
  {
    alignBriefingText();
  }

  if (gameState == GameState::PLAY_STATE)
  {
    checkShieldStatus();
    setStatBarWidth();
    adjacentQuads(lexington.getCurrentQuadPosition());
    quadrantAppearance();

    if (playerAction == PlayerAction::NONE)
    {
      alignInput(&command_text, &user_input);
    }
    userCommandSelection();

    if (mongol_count <= 0)
    {
      gameState = GameState::WIN_STATE;
    }
    if (lexington.getBaseHealth() <= 0)
    {
      gameState = GameState::LOSE_STATE;
    }
  }
}

void ASGETrek::userCommandSelection()
{
  if (play_state_input.find("MOVE") != std::string::npos)
  {
    playerAction = PlayerAction::MOVE;
    alignInput(&move_text, &user_input);
  }
  if (play_state_input.find("WARP") != std::string::npos)
  {
    playerAction = PlayerAction::WARP;
    alignInput(&warp_text, &user_input);
  }
  if (play_state_input.find("LASER") != std::string::npos)
  {
    playerAction = PlayerAction::LASER;
    alignInput(&laser_text, &user_input);
  }
  if (play_state_input.find("TORPEDO") != std::string::npos)
  {
    playerAction = PlayerAction::TORPEDO;
    alignInput(&laser_text, &user_input);
  }
  if (play_state_input.find("SHUP") != std::string::npos)
  {
    playerAction = PlayerAction::SHUP;
    play_state_input.clear();
    lexington.setShieldStatus(1);
  }
  if (play_state_input.find("SHDN") != std::string::npos)
  {
    playerAction = PlayerAction::SHDN;
    play_state_input.clear();
    lexington.setShieldStatus(0);
  }
  if (play_state_input.find("SELF") != std::string::npos)
  {
    Logging::DEBUG("User has started self destruct process");
    playerAction = PlayerAction::SELF;
    alignInput(&self_destruct_confirmation_text, &user_input);
    selfDestructState = SelfDestructState::CONFIRMATION;
  }
  if (play_state_input.find("HANDBOOK") != std::string::npos)
  {
    play_state_input.clear();
    gameState = GameState::HANDBOOK_STATE;
  }
}
void ASGETrek::alignBriefingText()
{
  if (briefingState == BriefingState::BRIEFING_REQUIREMENT)
  {
    alignInput(&briefing_requirement_text, &user_input);
  }
  else if (briefingState == BriefingState::RESTORE_SAVE)
  {
    alignInput(&savedGame_text, &user_input);
  }
  else if (briefingState == BriefingState::NAME)
  {
    alignInput(&name_text, &user_input);
  }
  else if (briefingState == BriefingState::COMMAND_LEVEL)
  {
    alignInput(&command_level_text, &user_input);
  }
  else if (briefingState == BriefingState::SELF_DESTRUCT_PASSWORD)
  {
    alignInput(&self_destruct_password_text, &user_input);
  }
}

/// Render your game and its scenes here.
void ASGETrek::render()
{
  if (gameState == GameState::BRIEFING_STATE)
  {
    briefingStateRenderables();
  }
  else if (gameState == GameState::PLAY_STATE)
  {
    playStateRenderables();
  }
  else if (gameState == GameState::HANDBOOK_STATE)
  {
    renderer->renderText(handbook_text);
  }
  else if (gameState == GameState::WIN_STATE)
  {
    renderer->renderText(win_text);
  }
  else if (gameState == GameState::LOSE_STATE)
  {
    renderer->renderText(lose_text);
  }
}

void ASGETrek::briefingStateRenderables()
{
  renderer->renderText(welcome_text);
  renderer->renderText(user_input);

  if (briefingState == BriefingState::NAME)
  {
    renderer->renderText(name_text);
  }

  else if (briefingState == BriefingState::BRIEFING_REQUIREMENT)
  {
    renderer->renderText(name_text);
    renderer->renderText(briefing_requirement_text);
  }

  if (briefingState == BriefingState::BRIEFING)
  {
    renderer->renderText(briefing_text);
  }

  if (briefingState == BriefingState::RESTORE_SAVE)
  {
    renderer->renderText(name_text);
    renderer->renderText(briefing_requirement_text);
    renderer->renderText(savedGame_text);
  }
  else if (briefingState == BriefingState::COMMAND_LEVEL)
  {
    renderer->renderText(name_text);
    renderer->renderText(briefing_requirement_text);
    renderer->renderText(savedGame_text);
    renderer->renderText(command_level_text);
  }
  else if (briefingState == BriefingState::SELF_DESTRUCT_PASSWORD)
  {
    renderer->renderText(name_text);
    renderer->renderText(briefing_requirement_text);
    renderer->renderText(savedGame_text);
    renderer->renderText(command_level_text);
    renderer->renderText(self_destruct_password_text);
  }
}

void ASGETrek::renderSprites()
{
  renderer->renderSprite(*lexington.getSprite());

  for (size_t i = 0; i < NUMBER_OF_MONGOLS; ++i)
  {
    if (
      mongols[i].isAlive() &&
      mongols[i].getQuadrant() == lexington.getCurrentQuadPosition())
    {
      renderer->renderSprite(*mongols[i].getSprite());
    }
  }
  for (size_t i = 0; i < NUMBER_OF_STARS; ++i)
  {
    if (stars[i].getQuadrant() == lexington.getCurrentQuadPosition())
    {
      renderer->renderSprite(*stars[i].getSprite());
    }
  }
  for (size_t i = 0; i < NUMBER_OF_BASES; ++i)
  {
    if (
      starBases[i].getQuadrant() == lexington.getCurrentQuadPosition())
    {
      renderer->renderSprite(*starBases[i].getSprite());
    }
  }
  for (size_t i = 0; i < MAX_NUMBER_OF_TORPEDOES; i++)
  {
    if (!torpedoes[i].isFired())
    {
      renderer->renderSprite(*torpedoes[i].getSprite());
    }
  }

  for (size_t i = 0; i < 4; ++i)
  {
    renderer->renderSprite(*bars[i]);
  }

  for (size_t i = 0; i < GRID_SIZE; ++i)
  {
    renderer->renderText(*quadrant[i].getQuadrant());
    renderer->renderSprite(*sector[i].getSprite());
  }
}

void ASGETrek::playStateRenderables()
{
  renderSprites();

  renderer->renderText(command_text);
  renderer->renderText(warp_factor_text);
  renderer->renderText(mongol_count_text);
  renderer->renderText(sector_location_text);
  renderer->renderText(quadrant_location_text);
  renderer->renderText(user_input);

  for (size_t i = 0; i < 4; ++i)
  {
    renderer->renderText(bar_text[i]);
  }

  for (size_t i = 0; i < 8; ++i)
  {
    renderer->renderText(sector_coords_x[i]);
    renderer->renderText(sector_coords_y[i]);
    renderer->renderText(quadrant_coords_x[i]);
    renderer->renderText(quadrant_coords_y[i]);
  }

  renderPlayerActionText();
}
void ASGETrek::renderPlayerActionText()
{
  if (playerAction == PlayerAction::MOVE)
  {
    renderer->renderText(move_text);
  }
  if (playerAction == PlayerAction::WARP)
  {
    renderer->renderText(warp_text);
  }
  if (playerAction == PlayerAction::LASER)
  {
    renderer->renderText(laser_text);
  }
  if (playerAction == PlayerAction::TORPEDO)
  {
    renderer->renderText(torpedo_text);
  }
  if (playerAction == PlayerAction::SELF)
  {
    renderer->renderText(self_destruct_confirmation_text);
  }
  if (selfDestructState == SelfDestructState::INITIATE)
  {
    renderer->renderText(initiate_self_destruct_text);
  }
}

/// Calls to fixedUpdate use the same fixed timesteps
/// irrespective of how much time is passed. This allows
/// calculations to resolve correctly and stop physics
/// simulations from imploding
///
/// https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
/// "Use variable timesteps for your game and fixed steps for physics"
/// @param us
void ASGETrek::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}
