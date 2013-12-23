#ifndef SPRITE_CONSTANTS_H_
#define SPRITE_CONSTANTS_H_

#include <string>

namespace sprite {
const int kTileSize = 32;

const std::string kFilePath("char.bmp");

const int kCharX  = 0 * kTileSize;
const int kWalkX  = 0 * kTileSize;
const int kStandX = 0 * kTileSize;
const int kJumpX  = 1 * kTileSize;
const int kFallX  = 2 * kTileSize;
const int kDownX  = 6 * kTileSize; 
const int kBackX  = 7 * kTileSize; 

const int kUpOffsetX = 3 * kTileSize;

const int kLeftY  = 0 * kTileSize;
const int kRightY = 1 * kTileSize;
}

#endif  // SPRITE_CONSTANTS_H_
