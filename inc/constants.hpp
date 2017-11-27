#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// ============================================================================
// Global program settings
// ============================================================================

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 800;
const char WINDOW_TITLE[] = "PL2";

// ============================================================================
//  Debug drawing flags
// ============================================================================

// #define DEBUG_DRAW_SOI
#define DEBUG_DRAW_BLOB_WAYPOINT
#define DEBUG_DRAW_WALL_NORMAL
#define DEBUG_DRAW_BLOB_WALL_COLLISION
#define DEBUG_DRAW_PF_GRID

// ============================================================================
//  Pathfinding (PF) settings
// ============================================================================
const int PF_GRID_SIZE = 50;

#endif /* end of include guard: CONSTANTS_HPP */    