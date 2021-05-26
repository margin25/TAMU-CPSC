#include <iostream>
#include <fstream>
#include <string>
#include "helper.h"
using std::cin, std::cout, std::endl, std::string, std::ifstream;

/**
 * Creates internal representation of dungeon map.
 * @param   fileName    File name of dungeon map representation.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   currX       Player's starting x-position on dungeon map.
 * @param   currY       Player's starting y-position on dungeon map.
 * @return  2D dynamic array representation of dungeon map with player's location.
 */
// STEP 1: Write code for createMap(...) function here.
int **createMap(const string fileName, int &width, int &height, int &currX, int &currY)
{
    // declare/define and open input file stream
    ifstream ifs(fileName);

    // check if input stream opened successfully
    if (!ifs.is_open())
    {
        cout << "ERROR: unable to open: " << fileName << endl;
        ifs.close();
        return (nullptr);
    }
    //Read the first first two lines and store them in their respective variables.
    ifs >> width;
    ifs >> height;
    ifs >> currX;
    ifs >> currY;
    int value;
    //Create a new map as a 2D dynamic int array based on the stored map dimensions.

    int **map = new int *[width]; //defining two dimensional array of ints
    for (int row = 0; row < height; row++)
    {
        map[row] = new int[height]; //iterating through array of ints, allocating memory
        //for each pointer in the array
    }
    //Read the remaining lines and store these values into the newly-created map.

    for (int row = 0; row < height; row++) //loading it with the values
    {
        for (int col = 0; col < width; col++)
        {
            ifs >> value;
            map[col][row] = value;
        }
    }

    //Store the player's starting location into the map with the stored starting position.
    map[currX][currY] = TILE_PLAYER;
    //Close the file reader and return the map.
    ifs.close();
    return (map);
}

/**
 * Updates player's position and movement status for next turn. 
 * @param   map         Dungeon map.
 * @param   width       Width of dungeon map.
 * @param   height      Height of dungeon map.
 * @param   direction   User's keyboard input for player's dungeon map direction.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.
 * @return  Player's movement status after updating player's position for next turn.
 */
// STEP 2: Write code for updateNextPosition(...) function here.

//Create the function signature (i.e., the function's return type, identifier, and parameter list)
//below this comment for creating the dungeon map.
int updateNextPosition(int **map, int width, int height, char direction, int &currX, int &currY, int &nextX, int &nextY)
{
    //Set the player's next position to the player's current position.
    nextY = currY;
    nextX = currX;

    //Calculate the player's position based on the user's keyboard input.
    //Refer to the user's keyboard input constants in helper.h.
    //If the position is out of bounds, then reset the player's next position to the player's current position.
    //Finally, return the player's movement status as staying.
    // If the position is located at a pillar, then reset the player's next position to the player's current position.
    //Finally, return the player's movement status as staying.
    if (direction == MOVE_UP)
    {
        nextY = currY - 1;
    }
    if (direction == MOVE_LEFT)
    {
        nextX = currX - 1;
    }
    if (direction == MOVE_RIGHT)
    {
        nextX = currX + 1;
    }
    if (direction == MOVE_DOWN)
    {
        nextY = currY + 1;
    }

    if ((nextY == height) || (nextX == width) || (map[nextX][nextY] == TILE_PILLAR) || (nextY < 0) || (nextX < 0))
    {
        nextY = currY;
        nextX = currX;
        return (STATUS_STAY);
    }
    if (map[nextX][nextY] == TILE_EXIT)
    {
        return (STATUS_ESCAPE);
    }
    if (width == 1 && height == 1)
    {
        return (STATUS_STAY);
    }

    return (STATUS_MOVE);
}

/**
 * Updates dungeon map representation with player's current position.
 * @param   currX       Player's current x-position on dungeon map.
 * @param   currY       Player's current y-position on dungeon map.
 * @param   nextX       Player's next x-position on dungeon map.
 * @param   nextY       Player's next y-position on dungeon map.  
 */
// STEP 3: Write code for updateMap(...) function here.
void updateMap(int **&map, int &currX, int &currY, int &nextX, int &nextY)
{

    //Go to the player's current position in the map and clear the tile as open.
    map[currX][currY] = TILE_OPEN;
    //Update the player's current position to the player's next position.
    currY = nextY;
    currX = nextX;
    //Go to the player's updated current position in the map and mark the tile as the player.
    map[currX][currY] = TILE_PLAYER;
}
int main()
{

    // declare variables
    int width, height, currX, currY, nextX, nextY;
    string fileName;

    // prompt user to enter dungeon file name
    cout << "Please enter dungeon map file: ";
    cin >> fileName;

    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    //create map, or quit if map load error
    int **map = createMap(fileName, width, height, currX, currY);
    if (map == nullptr)
    {
        cout << "This dungeon map does not exist. ";
        cout << "Returning you back to the real word, adventurer!" << endl;
        return 1;
    }

    // display greeting message
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Good day, adventurer! Your goal is to escape the dungeon!" << endl;
    cout << " --- SYMBOLS ---" << endl;
    cout << " o          : That is you, the adventurer!" << endl;
    cout << " x, -, |    : These are unpassable obstacles." << endl;
    cout << " !          : That is the door to escape the dungeon." << endl;
    cout << " --- CONTROLS ---" << endl;
    cout << " w, a, s, d : Keys for moving up, left, down, and right." << endl;
    cout << " q          : Key for abandoning your quest." << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << endl;

    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    // display map
    outputMap(map, width, height);

    // move player
    char input;
    int status;
    while (true)
    {
        // get user input
        cout << "Enter command (w,a,s,d: move, q: quit): ";
        cin >> input;

        // quit game if user inputs quit
        if (input == INPUT_QUIT)
        {
            cout << "Thank you for playing!" << endl;
            break;
        }

        // skip turn if user inputs
        if (input != MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT)
        {
            cout << "I did not understand your command, adventurer!" << endl;
            continue;
        }

        // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 2 ---
        // // move player, if possible, and get map status
        status = updateNextPosition(map, width, height, input, currX, currY, nextX, nextY);

        // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 3 ---
        // // update map
        if (status == STATUS_MOVE || status == STATUS_ESCAPE)
        {
            updateMap(map, currX, currY, nextX, nextY);
        }

        // // display map and status
        outputMap(map, width, height);
        outputStatus(status, currX, currY);

        // // quit game if user escapes
        if (status == STATUS_ESCAPE)
        {
            break;
        }
    }

    // --- UNCOMMENT THE FOLLOWING LINES AFTER COMPLETING STEP 1 ---
    // // delete map
    deleteMap(map, width);

    return 0;
}
