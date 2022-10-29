#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Error: failed to open input file - " << fileName << endl;
        return nullptr;
    }

    file >> maxRow;
    if(file.fail() || file.eof())
        return nullptr;

    file >> maxCol;
    if(file.fail() || file.eof())
        return nullptr;

    //creating the map
    char** dungeonMap = createMap(maxRow,maxCol);
    if (dungeonMap == nullptr)
        return nullptr;
    //populating the associated row and column with the adventurer
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            file >> dungeonMap[row][col];
            if (row == player.row && col == player.col) {
                dungeonMap[col][row] = TILE_PLAYER;
            }
        }
    }

    return dungeonMap;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    
    if(input == MOVE_UP)
        nextRow--; //since row starts at index 0 from the top
    if(input == MOVE_DOWN)
        nextRow++;
    if(input == MOVE_LEFT)
        nextCol--;
    if(input == MOVE_RIGHT)
        nextCol++;

}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    //creating an array of char type with the maximum amount of rows
    char** map = new char* [maxRow];

    for (int row = 0; row < maxRow; row++)
    {
        //populating each row with a column
        map[row] = new char[maxCol];
        for (int column = 0; column < maxRow; column++)
        {
            //populating each row, column with TILE_OPEN
            map[row][column] = TILE_OPEN;
        }
        
    }
    
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {

    for (int i = 0; i < maxRow; i++)
    {
        delete[] map[i];
    }
    
    maxRow = 0;
    delete [] map;
    map = nullptr;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    //initializing a char array with the rows doubled
    int doubledRow = maxRow*2;
    int doubledCol = maxCol*2;

    char **resizedMap = new char*[doubledRow];

    for (int row = 0; row < doubledRow; row++)
    {
        //adding columns to each array row
        resizedMap[row] = new char[doubledCol];
        //populating each row/column with the original values 
        if(row < maxRow){
            for(int col = 0; col < maxCol; col++){
                resizedMap[row][col] = map[row][col];
            }
        }
    }

    //declaring the original char
    char original;

    for(int row = 0; row < maxRow; row++){
        for(int col = 0; col < maxCol; col++){
            original = map[row][col];
            //in the event that the char at the location is not the adventurer, set it equal to the original char
            if(map[row][col] != TILE_PLAYER){
                resizedMap[row+maxRow][col+maxCol] = original;
                resizedMap[row][col+maxCol] = original;
                resizedMap[row+maxRow][col] = original;
            }
            //if it is the adventurer, set the array at location above, left and right to tile open
            else
            {
                resizedMap[row+maxRow][col+maxCol] = TILE_OPEN;
                resizedMap[row][col+maxCol] = TILE_OPEN;
                resizedMap[row+maxRow][col] = TILE_OPEN;
            }
        }
    }

    //clear memory
    deleteMap(map, maxRow);
    //double the row and columns
    maxRow *= 2;
    maxCol *= 2;
    
    return resizedMap;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {

    //default status
    int statusFlag = STATUS_MOVE;
    bool monsterNext = (map[nextRow][nextCol] == TILE_MONSTER);
    bool pillarNext = (map[nextRow][nextCol] == TILE_PILLAR);
    bool treasureNext = (map[nextRow][nextCol] == TILE_TREASURE);
    bool amuletNext = (map[nextRow][nextCol] == TILE_AMULET);
    bool doorNext = (map[nextRow][nextCol] == TILE_DOOR);
    bool exitNext = (map[nextRow][nextCol] == TILE_EXIT);



    if(nextRow>= maxRow || nextCol >= maxCol || nextRow < 0 || nextCol < 0 || pillarNext || monsterNext){
        nextRow = player.row;
        nextCol = player.col;
        statusFlag = STATUS_STAY;
    }
    if(treasureNext){
        player.treasure += 1;
        statusFlag = STATUS_TREASURE;

    }
    if(amuletNext)
        statusFlag = STATUS_AMULET;
    if(doorNext)
        statusFlag = STATUS_LEAVE;
    if(exitNext){
        //if the player has no treasure, then stay
        if (player.treasure < 1)
        {
            nextRow = player.row;
            nextCol = player.col;
            statusFlag = STATUS_STAY;
        }

        //if player has treasure, escape
        else
            statusFlag = STATUS_ESCAPE;

    }

    //updating values to open and player
    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    //updating the column and rows
    player.col = nextCol;
    player.row = nextRow;
    //returning the status
    return statusFlag;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    return false;
}
