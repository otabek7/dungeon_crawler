// #include <iostream>
// #include <fstream>
// #include <string>
// #include "logic.h"

// using std::cout, std::endl, std::ifstream, std::string;

// /**
//  * TODO: Student implement this function
//  * Load representation of the dungeon level from file into the 2D map.
//  * Calls createMap to allocate the 2D array.
//  * @param   fileName    File name of dungeon level.
//  * @param   maxRow      Number of rows in the dungeon table (aka height).
//  * @param   maxCol      Number of columns in the dungeon table (aka width).
//  * @param   player      Player object by reference to set starting position.
//  * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
//  * @updates  maxRow, maxCol, player
//  */
// char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
// {
//     char character = '-';
//     ifstream in(fileName);
//     if (!in.is_open())
//     {
//         return nullptr;
//     }

//     in >> maxRow;
//     if (in.fail() || maxRow <= 0)
//     {
//         return nullptr;
//     }

//     in >> maxCol;
//     if (in.fail() || maxCol <= 0)
//     {
//         return nullptr;
//     }

//     if (maxCol > (INT32_MAX / ((double)maxRow)))
//     {
//         return nullptr;
//     }

//     in >> player.row;
//     if (in.fail() || player.row < 0 || player.row >= maxRow)
//     {
//         return nullptr;
//     }

//     in >> player.col;
//     if (in.fail() || player.col < 0 || player.col >= maxCol)
//     {
//         return nullptr;
//     }

//     char **level = new char *[maxRow];
//     for (int i = 0; i < maxRow; i++)
//     {
//         level[i] = new char[maxCol];
//     }


//     bool doorAndExit = false;
//     for (int row = 0; row < maxRow; ++row)
//     {
//         for (int col = 0; col < maxCol; ++col)
//         {
//             in >> character;
//             if (character != TILE_OPEN && character != TILE_PLAYER && character != TILE_TREASURE && character != TILE_AMULET && character != TILE_MONSTER && character != TILE_PILLAR && character != TILE_DOOR && character != TILE_EXIT)
//             {
//                 return nullptr;
//             }
//             if (character == TILE_DOOR || character == TILE_EXIT)
//             {
//                 doorAndExit = true;
//             }
//             if (in.eof())
//             {
//                 return nullptr;
//             }
//             level[row][col] = character;
//         }
//     }
//     if (!doorAndExit)
//     {
//         return nullptr;
//     }
//     in >> character;
//     if (!in.eof())
//     {
//         return nullptr;
//     }
//     level[player.row][player.col] = TILE_PLAYER;
//     return level;
// }

// /**
//  * TODO: Student implement this function
//  * Translate the character direction input by the user into row or column change.
//  * That is, updates the nextRow or nextCol according to the player's movement direction.
//  * @param   input       Character input by the user which translates to a direction.
//  * @param   nextRow     Player's next row on the dungeon map (up/down).
//  * @param   nextCol     Player's next column on dungeon map (left/right).
//  * @updates  nextRow, nextCol
//  */
// void getDirection(char input, int &nextRow, int &nextCol)
// {
//     if (input == 'w')
//     {
//         nextRow -= 1;
//     }
//     else if (input == 's')
//     {
//         nextRow += 1;
//     }
//     else if (input == 'a')
//     {
//         nextCol -= 1;
//     }
//     else if (input == 'd')
//     {
//         nextCol += 1;
//     }
// }

// /**
//  * TODO: [suggested] Student implement this function
//  * Allocate the 2D map array.
//  * Initialize each cell to TILE_OPEN.
//  * @param   maxRow      Number of rows in the dungeon table (aka height).
//  * @param   maxCol      Number of columns in the dungeon table (aka width).
//  * @return  2D map array for the dungeon level, holds char type.
//  */
// char **createMap(int maxRow, int maxCol)
// {
//     char **dungeon = new char *[maxRow];

//     for (int i = 0; i < maxRow; i++)
//     {
//         dungeon[i] = new char[maxCol];
//     }

//     for (int row = 0; row < maxRow; row++)
//     {
//         for (int col = 0; col < maxCol; col++)
//         {
//             dungeon[row][col] = TILE_OPEN;
//         }
//     }

//     return dungeon;
// }

// /**
//  * TODO: Student implement this function
//  * Deallocates the 2D map array.
//  * @param   map         Dungeon map.
//  * @param   maxRow      Number of rows in the dungeon table (aka height).
//  * @return None
//  * @update map, maxRow
//  */
// // fix deleteMap - hidden test
// void deleteMap(char **&map, int &maxRow)
// {
//     for (int i = 0; i < maxRow; i++)
//     {
//         delete[] map[i];
//     }
//     delete[] map;
//     map = nullptr;
//     maxRow = 0;
// }

// /**
//  * TODO: Student implement this function
//  * Resize the 2D map by doubling both dimensions.
//  * Copy the current map contents to the right, diagonal down, and below.
//  * Do not duplicate the player, and remember to avoid memory leaks!
//  * You can use the STATUS constants defined in logic.h to help!
//  * @param   map         Dungeon map.
//  * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
//  * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
//  * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
//  * @update maxRow, maxCol
//  */

// // fix resizeMap - hidden test
// char **resizeMap(char **map, int &maxRow, int &maxCol)
// {
//     char **dungeon = createMap(maxRow * 2, maxCol * 2);
//     int rowMax = maxRow;
//     if (map == nullptr)
//     {
//         return nullptr;
//     }
//     if (maxCol > (INT32_MAX / ((double)maxRow)))
//     {
//         return nullptr;
//     }
//     // A
//     for (int row = 0; row < maxRow; row++)
//     {
//         for (int col = 0; col < maxCol; col++)
//         {
//             dungeon[row][col] = map[row][col];
//         }
//     }
//     // B
//     for (int row = 0; row < maxRow; row++)
//     {
//         for (int col = maxCol; col < maxCol * 2; col++)
//         {
//             if (map[row][col - maxCol] == TILE_PLAYER)
//             {
//                 dungeon[row][col] = TILE_OPEN;
//             }
//             else
//             {
//                 dungeon[row][col] = map[row][col - maxCol];
//             }
//         }
//     }
//     // C
//     for (int row = maxRow; row < maxRow * 2; row++)
//     {
//         for (int col = 0; col < maxCol; col++)
//         {
//             if (map[row - maxRow][col] == TILE_PLAYER)
//             {
//                 dungeon[row][col] = TILE_OPEN;
//             }
//             else
//             {
//                 dungeon[row][col] = map[row - maxRow][col];
//             }
//         }
//     }
//     // D
//     for (int row = maxRow; row < maxRow * 2; row++)
//     {
//         for (int col = maxCol; col < maxCol * 2; col++)
//         {
//             if (map[row - maxRow][col - maxCol] == TILE_PLAYER)
//             {
//                 dungeon[row][col] = TILE_OPEN;
//             }
//             else
//             {
//                 dungeon[row][col] = map[row - maxRow][col - maxCol];
//             }
//         }
//     }
//     deleteMap(map, maxRow);
//     maxRow = rowMax * 2;
//     maxCol *= 2;
//     return dungeon;
// }
// /**
//  * TODO: Student implement this function
//  * Checks if the player can move in the specified direction and performs the move if so.
//  * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
//  * Cannot move onto TILE_EXIT without at least one treasure.
//  * If TILE_TREASURE, increment treasure by 1.
//  * Remember to update the map tile that the player moves onto and return the appropriate status.
//  * You can use the STATUS constants defined in logic.h to help!
//  * @param   map         Dungeon map.
//  * @param   maxRow      Number of rows in the dungeon table (aka height).
//  * @param   maxCol      Number of columns in the dungeon table (aka width).
//  * @param   player      Player object to by reference to see current location.
//  * @param   nextRow     Player's next row on the dungeon map (up/down).
//  * @param   nextCol     Player's next column on dungeon map (left/right).
//  * @return  Player's movement status after updating player's position.
//  * @update map contents, player
//  */
// int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
// {
//     if (nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0 || map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR)
//     {
//         return STATUS_STAY;
//     }
//     else if (map[nextRow][nextCol] == TILE_TREASURE)
//     {
//         player.treasure += 1;
//         map[nextRow][nextCol] = TILE_PLAYER;
//         map[player.row][player.col] = TILE_OPEN;
//         player.row = nextRow;
//         player.col = nextCol;
//         return STATUS_TREASURE;
//     }
//     else if (map[nextRow][nextCol] == TILE_AMULET)
//     {
//         map[nextRow][nextCol] = TILE_PLAYER;
//         map[player.row][player.col] = TILE_OPEN;
//         player.row = nextRow;
//         player.col = nextCol;
//         return STATUS_AMULET;
//     }
//     else if (map[nextRow][nextCol] == TILE_DOOR)
//     {
//         map[nextRow][nextCol] = TILE_PLAYER;
//         map[player.row][player.col] = TILE_OPEN;
//         player.row = nextRow;
//         player.col = nextCol;
//         return STATUS_LEAVE;
//     }
//     else if (map[nextRow][nextCol] == TILE_EXIT)
//     {
//         if (player.treasure >= 1)
//         {
//             map[nextRow][nextCol] = TILE_PLAYER;
//             map[player.row][player.col] = TILE_OPEN;
//             player.row = nextRow;
//             player.col = nextCol;
//             return STATUS_ESCAPE;
//         }
//         else
//         {
//             return STATUS_STAY;
//         }
//     }
//     map[nextRow][nextCol] = TILE_PLAYER;
//     map[player.row][player.col] = TILE_OPEN;
//     player.row = nextRow;
//     player.col = nextCol;
//     return STATUS_MOVE;
// }

// /**
//  * TODO: Student implement this function
//  * Update monster locations:
//  * We check up, down, left, right from the current player position.
//  * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
//  * If we see a monster before an obstacle, the monster moves one tile toward the player.
//  * We should update the map as the monster moves.
//  * At the end, we check if a monster has moved onto the player's tile.
//  * @param   map         Dungeon map.
//  * @param   maxRow      Number of rows in the dungeon table (aka height).
//  * @param   maxCol      Number of columns in the dungeon table (aka width).
//  * @param   player      Player object by reference for current location.
//  * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
//  * @update map contents
//  */
// bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
// {
//     int obstacleRow = -1;
//     // rows behind
//     for (int r = 0; r < player.row; r++)
//     {
//         if (map[r][player.col] == TILE_PILLAR || map[r][player.col] == TILE_EXIT)
//         {
//             obstacleRow = r;
//         }
//     }
//     for (int row = player.row - 1; row > -1; row--)
//     {
//         if (map[row][player.col] == TILE_MONSTER && row > obstacleRow)
//         {
//             map[row + 1][player.col] = TILE_MONSTER;
//             map[row][player.col] = TILE_OPEN;
//         }
//     }
//     // rows ahead
//     obstacleRow = maxRow;
//     for (int r = player.row + 1; r < maxRow; r++)
//     {
//         if (map[r][player.col] == TILE_PILLAR || map[r][player.col] == TILE_EXIT)
//         {
//             obstacleRow = r;
//         }
//     }
//     for (int row = player.row + 1; row < maxRow; row++)
//     {
//         if (map[row][player.col] == TILE_MONSTER && row < obstacleRow)
//         {
//             map[row - 1][player.col] = TILE_MONSTER;
//             map[row][player.col] = TILE_OPEN;
//         }
//     }
//     // columns behind
//     int obstacleCol = -1;
//     for (int c = 0; c < player.col; c++)
//     {
//         if (map[player.row][c] == TILE_PILLAR || map[player.row][c] == TILE_EXIT)
//         {
//             obstacleCol = c;
//         }
//     }
//     for (int col = player.col - 1; col > -1; col--)
//     {
//         if (map[player.row][col] == TILE_MONSTER && col > obstacleCol)
//         {
//             map[player.row][col + 1] = TILE_MONSTER;
//             map[player.row][col] = TILE_OPEN;
//         }
//     }
//     // columns ahead
//     obstacleCol = maxCol;
//     for (int c = player.col + 1; c < maxCol; c++)
//     {
//         if (map[player.row][c] == TILE_PILLAR || map[player.row][c] == TILE_EXIT)
//         {
//             obstacleCol = c;
//         }
//     }
//     for (int col = player.col + 1; col < maxCol; col++)
//     {
//         if (map[player.row][col] == TILE_MONSTER && col < obstacleCol)
//         {
//             map[player.row][col - 1] = TILE_MONSTER;
//             map[player.row][col] = TILE_OPEN;
//         }
//     }
//     // if monster is on same tile as player
//     if (map[player.row][player.col] == TILE_MONSTER)
//     {
//         return true;
//     }
//     return false;
// }
