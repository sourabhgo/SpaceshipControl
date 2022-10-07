// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // planet texture
    if (!planetTexture.initialize(graphics,PLANET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

    // spaceship texture
    if (!shipTexture.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

    // nebula
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

    // planet
    if (!planet.initialize(graphics,0,0,0,&planetTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
    // place planet in center of screen
    planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
    planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

    // ship
    if (!ship.initialize(graphics,SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
    ship.setX(GAME_WIDTH/4);                    // start above and left of planet
    ship.setY(GAME_HEIGHT/4);
    ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames
    ship.setCurrentFrame(SHIP_START_FRAME);     // starting frame
    ship.setFrameDelay(SHIP_ANIMATION_DELAY);
    ship.setDegrees(45.0f);                     // angle of ship

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
    ship.update(frameTime);
    ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE); // rotate ship
    ship.setScale(ship.getScale() - frameTime * SCALE_RATE);    // make ship smaller
    ship.setX(ship.getX() + frameTime * SHIP_SPEED);    // move ship right
    if (ship.getX() > GAME_WIDTH)                       // if off screen right
    {
        ship.setX((float)-ship.getWidth());             // position off screen left
        ship.setScale(SHIP_SCALE);                      // set to starting size
    }
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    nebula.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
    ship.draw();                            // add the spaceship to the scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    shipTexture.onLostDevice();
    planetTexture.onLostDevice();
    nebulaTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    nebulaTexture.onResetDevice();
    planetTexture.onResetDevice();
    shipTexture.onResetDevice();

    Game::resetAll();
    return;
}
