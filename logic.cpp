
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
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{
    std::ifstream file(fileName);

    //series of check to check if the file failed to open and if the contens are bad
    if (!file.is_open())
    {
        return nullptr;
    }

    file >> maxRow;
    if (file.fail() || maxRow <= 0)
        return nullptr;

    file >> maxCol;
    if (file.fail() || maxCol <= 0 || (maxCol > (INT32_MAX / ((double)maxRow))))
        return nullptr;


    //checking for player row if good or bad
    file >> player.row;
    if (file.fail() || player.row < 0 || player.row >= maxRow)
        return nullptr;
    file >> player.col;
    if (file.fail() || player.col < 0 || player.col >= maxCol)
        return nullptr;

        // initializing a char array with maxRow set
    char **levelLoad = new char *[maxRow];

    // populating each row with a column
    for (int row = 0; row < maxRow; row++)
    {
        levelLoad[row] = new char[maxCol];
    }

    char character;

    bool trigger;
    trigger = false;

    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            //checking the character of each character in the file
            file >> character;
            //if one of these tiles are met, then return a nullptr automatically
            if (character != TILE_OPEN && character != TILE_PLAYER && character != TILE_TREASURE && character != TILE_AMULET && character != TILE_MONSTER && character != TILE_PILLAR && character != TILE_DOOR && character != TILE_EXIT)
                return nullptr;
            //else if it is a door or exit then trigger is true
            if (character == TILE_DOOR)
                trigger = true;
            if(character == TILE_EXIT)
                trigger = true;
            //if the file reaches the end then thats bad
            if (file.eof())
                return nullptr;
            
            levelLoad[row][col] = character;
        }
    }
    if (trigger == false)
        return nullptr;

    //checking if end of file didnt reach
    file >> character;
    if (!file.eof())
        return nullptr;


    //assigning with level load tile player
    levelLoad[player.row][player.col] = TILE_PLAYER;
    return levelLoad;
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
void getDirection(char input, int &nextRow, int &nextCol)
{
    //self explanatory
    if (input == MOVE_UP)
        nextRow -= 1; 
    if (input == MOVE_DOWN)
        nextRow += 1;
    if (input == MOVE_LEFT)
        nextCol -= 1;
    if (input == MOVE_RIGHT)
        nextCol += 1;
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char **createMap(int maxRow, int maxCol)
{

    // creating an array of char type with the maximum amount of rows TODO
    char **map = new char *[maxRow];

    // initializing each row with a column
    for (int i = 0; i < maxRow; i++)
    {
        map[i] = new char[maxCol];
    }

    // initializing each row and column with tile open
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            map[row][col] = TILE_OPEN;
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
void deleteMap(char **&map, int &maxRow)
{
    // deleting each index of map
    if(map != nullptr)
    {    

    for (int i = 0; i < maxRow; i++)
    {
        delete[] map[i];
    }

    delete[] map;
    maxRow = 0;
    map = nullptr;
    }
    else{
    maxRow = 0;    
    }
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
char **resizeMap(char **map, int &maxRow, int &maxCol)
{

    // initializing a char array with the rows doubled
    int doubledRow = maxRow * 2;
    int doubledCol = maxCol * 2;
    double dmaxRow = (double)maxRow;

    //resizing the created map with those parameters
    char **resizedMap = createMap(doubledRow, doubledCol);

    //checking for abnormalities
    if (map == nullptr || (maxCol > (INT32_MAX / (dmaxRow))))
        return nullptr;

    //resizing the row,col
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            resizedMap[row][col] = map[row][col];
        }
    }
    //checking if resized map has a tile player and resizing second sec
    for (int row = 0; row < maxRow; row++)
    {
        for (int col = maxCol; col < doubledCol; col++)
        {
            if (map[row][col - maxCol] == TILE_PLAYER)
                resizedMap[row][col] = TILE_OPEN;

            else
                resizedMap[row][col] = map[row][col - maxCol];
        }
    }

    //resizing the third section
    for (int row = maxRow; row < doubledRow; row++)
    {
        for (int col = 0; col < maxCol; col++)
        {
            if (map[row - maxRow][col] == TILE_PLAYER)
                resizedMap[row][col] = TILE_OPEN;

            else
                resizedMap[row][col] = map[row - maxRow][col];
        }
    }
    
    //checking if second resized map has a tile player and resizing fourth sec
    for (int row = maxRow; row < doubledRow; row++)
    {
        for (int col = maxCol; col < doubledCol; col++)
        {
            if (map[row - maxRow][col - maxCol] == TILE_PLAYER)
                resizedMap[row][col] = TILE_OPEN;

            else
                resizedMap[row][col] = map[row - maxRow][col - maxCol];
        }
    }

    //clearing
    deleteMap(map, maxRow);

    maxRow = doubledRow;
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
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{
    int status = STATUS_STAY;
    // int statusFlag = STATUS_MOVE;
    // bool monsterNext = (map[nextRow][nextCol] == TILE_MONSTER);
    // bool pillarNext = (map[nextRow][nextCol] == TILE_PILLAR);
    // bool treasureNext = (map[nextRow][nextCol] == TILE_TREASURE);
    // bool amuletNext = (map[nextRow][nextCol] == TILE_AMULET);
    // bool doorNext = (map[nextRow][nextCol] == TILE_DOOR);
    // bool exitNext = (map[nextRow][nextCol] == TILE_EXIT);
    if (nextRow >= maxRow || nextRow < 0 || nextCol >= maxCol || nextCol < 0 || map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR)
        return status;

        
    if (map[nextRow][nextCol] == TILE_DOOR)
    {
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;

        status = STATUS_LEAVE;
        return status;
    }

     if (map[nextRow][nextCol] == TILE_EXIT)
    {
        if (player.treasure >= 1)
        {
            map[nextRow][nextCol] = TILE_PLAYER;
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            status = STATUS_ESCAPE;
            return status;
        }
        else
            return status;
    }

    
    if (map[nextRow][nextCol] == TILE_AMULET)
    {
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        status = STATUS_AMULET;
        return status;
    }

    if (map[nextRow][nextCol] == TILE_TREASURE)
    {
        player.treasure += 1;
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        status = STATUS_TREASURE;
        return status;
    }
    
   

    map[player.row][player.col] = TILE_OPEN;
    map[nextRow][nextCol] = TILE_PLAYER;
    player.row = nextRow;
    player.col = nextCol;
    status = STATUS_MOVE;
    return status;
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
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{
    bool playerDead = false;
    int obsC = -1;

    // checking for the pillar or exit in the columns behind
    for (int i = 0; i < player.col; i++)
    {
        if (map[player.row][i] == TILE_PILLAR)
            obsC = i;

        if (map[player.row][i] == TILE_EXIT)
            obsC = i;
    }

    // checking for the monster or open in the columns behind

    for (int i = player.col - 1; i > -1; i--)
    {
        if (map[player.row][i] == TILE_MONSTER && i > obsC)
        {
            map[player.row][i + 1] = TILE_MONSTER;
            map[player.row][i] = TILE_OPEN;
        }
    }
    // checking for the pillar or exit in the columns ahead

    obsC = maxCol;
    for (int i = player.col + 1; i < maxCol; i++)
    {
        if (map[player.row][i] == TILE_PILLAR)
            obsC = i;
        if (map[player.row][i] == TILE_EXIT)
            obsC = i;
    }
    // checking for the monster in the columns ahead

    for (int j = player.col + 1; j < maxCol; j++)
    {
        if (map[player.row][j] == TILE_MONSTER && j < obsC)
        {
            map[player.row][j - 1] = TILE_MONSTER;
            map[player.row][j] = TILE_OPEN;
        }
    }

    int obs = -1;
    // checking for the pillar or exit in the rows behind

    for (int i = 0; i < player.row; i++)
    {
        if (map[i][player.col] == TILE_PILLAR)

            obs = i;
        if (map[i][player.col] == TILE_EXIT)
            obs = i;
    }
    // checking for the monster in the rows behind

    for (int row = player.row - 1; row > -1; row--)
    {
        if (map[row][player.col] == TILE_MONSTER && row > obs)
        {
            map[row + 1][player.col] = TILE_MONSTER;
            map[row][player.col] = TILE_OPEN;
        }
    }

    obs = maxRow;
    // checking for the pillar or exit in the rows forward

    for (int i = player.row + 1; i < maxRow; i++)
    {
        if (map[i][player.col] == TILE_EXIT)
            obs = i;
        if (map[i][player.col] == TILE_PILLAR)
            obs = i;
    }
    // checking for the monster in the rows forward

    for (int j = player.row + 1; j < maxRow; j++)
    {
        if (map[j][player.col] == TILE_MONSTER && j < obs)
        {
            map[j - 1][player.col] = TILE_MONSTER;
            map[j][player.col] = TILE_OPEN;
        }
    }

    //if there is a monster, the player is dead!
    if (map[player.row][player.col] == TILE_MONSTER)
    {
        playerDead = true;
        return playerDead;
    }
    //else he is not
    playerDead = false;
    return playerDead;
}