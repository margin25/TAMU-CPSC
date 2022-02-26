#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

#define INFO(X) cout << "[INFO] (" << __FUNCTION__ << ":" << __LINE__ << ") " << #X << " = " << X << endl;

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width];

  bool fail = false;

  for (int i = 0; i < width; ++i)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];

    if (image[i] == nullptr)
    { // failed to allocate
      fail = true;
    }
  }

  if (fail)
  { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i = 0; i < width; ++i)
    {
      delete[] image[i]; // deleting nullptr is not a problem
    }
    delete[] image; // dlete array of pointers
    return nullptr;
  }

  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i]; // delete each individual array placed on the heap
  }
  delete[] image;
  image = nullptr;
}

int *createSeam(int length)
{
  // TODO(student): create a seam

  /*
  This function will return a pointer to an array of ints allocated on the heap.
  The array must be initialized so that all elements have a value of zero in them.
  The parameter indicates how many elements must be in the returned array. 
  You can also think of this as the size of the array
  */

  int *c = new int[length];
  for (int i = 0; i < length; i++)
  {
    c[i] = 0;
  }

  INFO(length);
  return c;
}

void deleteSeam(int *seam)
{
  delete[] seam; // delete [] vs delete , so delete deletes only the first index while delete[] deletes the whole seam array which is
  //MUCH MORE MEMORY EFFICIENT!

  INFO(seam);
}

bool loadImage(string filename, Pixel **image, int width, int height)
{
  // TODO(student): load an image

  INFO(filename);
  INFO(image);
  INFO(width);
  INFO(height);
  // declare/define and open input file stream
  std::ifstream ifs(filename);
  // check if input stream opened successfully
  if (!ifs.is_open())
  {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  // get type from preamble
  char type[3];
  ifs >> type; // should be P3
  if (((toupper(type[0]) != 'P') && (type[1] != '3')) || ((toupper(type[0]) != 'p') && (type[1] != '3')))
  { // check that type is correct
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  // get width (w) and height (h) from preamble
  int w = 0, h = 0;
  ifs >> w;
  if (ifs.fail())
  {
    {
      if (ifs.eof())
      {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      else
      {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
    }
  }
  ifs >> h;
  if (ifs.fail())
  {
    {
      if (ifs.eof())
      {
        cout << "Error: not enough color values" << endl;
        return false;
      }
      else
      {
        cout << "Error: read non-integer value" << endl;
        return false;
      }
    }
  }

  if (w != width)
  { // check that width matches what was passed into the function
    cout << "Error: input width (" << width << ")"
         << " does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (h <= 0)
  {
    cout << "Error: target width must be greater than 0. You entered " << h << endl;
  }
  if (h != height)
  { // check that height matches what was passed into the function
    cout << "Error: input height (" << height << ")"
         << " does not match value in file (" << h << ")" << endl;
    return false;
  }

  // get maximum value from preamble
  int colorMax = 0;
  ifs >> colorMax;
  if (colorMax != 255)
  {
    cout << "Error: file is not using RGB color values." << endl;
    return false;
  }

  // TODO(student): get RGB pixel values
  int red = 0;   //initalize variable that will hold red color value
  int green = 0; //initalize variable that will hold green color value
  int blue = 0;  //initalize variable that will hold blue color value
  int extra = 0;
  for (int row = 0; row < height; row++) //column major order
  {
    for (int column = 0; column < width; column++)
    {
      //ifs.clear();
      //ifs.ignore();
      ifs >> red; // value for red inputted into filestream
      if (ifs.fail())
      {
        if (ifs.eof())
        {
          cout << "Error: not enough color values" << endl;
          return false;
        }
        else
        {
          cout << "Error: read non-integer value" << endl;
          return false;
        }
      }
      //ifs.clear();
      //ifs.ignore();
      ifs >> green; // value for green inputted into filestream
      if (ifs.fail())
      {
        if (ifs.eof())
        {
          cout << "Error: not enough color values" << endl;
          return false;
        }
        else
        {
          cout << "Error: read non-integer value" << endl;
          return false;
        }
      }
      //ifs.clear();
      //ifs.ignore();
      ifs >> blue; // value for blue inputted into filestream

      if (ifs.fail())
      {
        if (ifs.eof())
        {
          cout << "Error: not enough color values" << endl;
          return false;
        }
        else
        {
          cout << "Error: read non-integer value" << endl;
          return false;
        }
      }
      if (red < 0 || red > 255) // outputs error message if red is outside of RGB bounds
      {
        cout << "Error: invalid color value " << red << endl;
        return false;
      }
      if (green < 0 || green > 255) // outputs error message if green is outside of RGB bounds
      {
        cout << "Error: invalid color value " << green << endl;
        return false;
      }
      if (blue < 0 || blue > 255) // outputs error message if blue is outside of RGB bounds
      {
        cout << "Error: invalid color value " << blue << endl;
        return false;
      }
      image[column][row].r = red;   //inputs  value for red at current index in the  2d image array
      image[column][row].g = green; //inputs  value for green at current index in the  2d image array
      image[column][row].b = blue;  //inputs  value for blue at current index in the  2d image array
    }
  }
  ifs >> extra;
  if (!ifs.fail() && (extra < 255 && extra > 0))
  {
    cout << "Error: too many color values" << endl;
    return false;
  }
  return true;
}

bool outputImage(string filename, Pixel **image, int width, int height)
{
  cout << "Outputting image..." << endl;
  // TODO(student): declare/define and open output file stream
  ofstream ofs;       //declaring filestream
  ofs.open(filename); //opening filestream
  // TODO(student): check if output stream opened successfully
  if (!ofs.is_open())
  {
    cout << "Error: failed to open output file" << filename << endl;
    return (false);
  }
  // TODO(student): output preamble
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << "255" << endl;

  // TODO(student): output pixels
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      ofs << image[column][row].r << " " << image[column][row].g << " " << image[column][row].b << " ";
    }
    ofs << endl;
  }
  INFO(filename);
  INFO(image);
  INFO(width);
  INFO(height);
  return true;
}

int energy(Pixel **image, int column, int row, int width, int height)
{
  // TODO(student): compute the energy of a pixel
  /* int pixel_energy;
  int r_x = 0;
  int g_x = 0;
  int b_x = 0;
  int r_y = 0;
  int g_y = 0;
  int b_y = 0;
  int x_gradient = 0;
  int y_gradient = 0;
  //Non-Border
  if ((row > 0 && column > 0) && (row < height - 1 && column < width - 1))
  {
    r_x = image[column + 1][row].r - image[column - 1][row].r;
    g_x = image[column + 1][row].g - image[column - 1][row].g;
    b_x = image[column + 1][row].b - image[column - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][row + 1].r - image[column][row - 1].r;
    g_y = image[column][row + 1].g - image[column][row - 1].g;
    b_y = image[column][row + 1].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }

  //Border (top-middle)

  else if ((row == 0 && column != 0))
  {
    r_x = image[column + 1][row].r - image[column - 1][row].r;
    g_x = image[column + 1][row].g - image[column - 1][row].g;
    b_x = image[column + 1][row].b - image[column - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][height - 1].r - image[column][row + 1].r;
    g_y = image[column][height - 1].g - image[column][row + 1].g;
    b_y = image[column][height - 1].b - image[column][row + 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }

  //Border (top-left)
  else if ((row == 0 && column == 0))
  {
    r_x = image[column + 1][row].r - image[width - 1][row].r;
    g_x = image[column + 1][row].g - image[width - 1][row].g;
    b_x = image[column + 1][row].b - image[width - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][row + 1].r - image[column][height - 1].r;
    g_y = image[column][row + 1].g - image[column][height - 1].g;
    b_y = image[column][row + 1].b - image[column][height - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (top-right)
  else if ((row == 0) && (column == width - 1))
  {
    r_x = image[0][0].r - image[column - 2][0].r;
    g_x = image[0][0].g - image[column - 2][0].g;
    b_x = image[0][0].b - image[column - 2][0].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][row + 1].r - image[column][height - 1].r;
    g_y = image[column][row + 1].g - image[column][height - 1].g;
    b_y = image[column][row + 1].b - image[column][height - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (left)
  else if ((row != 0 && column == 0))
  {
    r_x = image[column + 1][row].r - image[width - 1][row].r;
    g_x = image[column + 1][row].g - image[width - 1][row].g;
    b_x = image[column + 1][row].b - image[width - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][row + 1].r - image[column][row - 1].r;
    g_y = image[column][row + 1].g - image[column][row - 1].g;
    b_y = image[column][row + 1].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (right)
  else if ((row != 0 && column == width - 1))
  {
    r_x = image[0][row].r - image[column - 1][row].r;
    g_x = image[0][row].g - image[column - 1][row].g;
    b_x = image[0][row].b - image[column - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][row + 1].r - image[column][row - 1].r;
    g_y = image[column][row + 1].g - image[column][row - 1].g;
    b_y = image[column][row + 1].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (bottom-left-corner)
  else if (row == width - 1 && column == 0)
  {
    r_x = image[column + 1][height - 1].r - image[width - 1][height - 1].r;
    g_x = image[column + 1][height - 1].g - image[width - 1][height - 1].g;
    b_x = image[column + 1][height - 1].b - image[width - 1][height - 1].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[0][0].r - image[column][row - 1].r;
    g_y = image[0][0].g - image[column][row - 1].g;
    b_y = image[0][0].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (bottom-middle)
  else if (row == height - 1 && column != 0 && column != width - 1)
  {
    r_x = image[column + 1][row].r - image[column - 1][row].r;
    g_x = image[column + 1][row].g - image[column - 1][row].g;
    b_x = image[column + 1][row].b - image[column - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][0].r - image[column][row - 1].r;
    g_y = image[column][0].g - image[column][row - 1].g;
    b_y = image[column][0].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }
  //Border (bottom-right-corner)
  else if (row == height - 1 && column == width - 1)
  {
    r_x = image[0][row].r - image[column - 1][row].r;
    g_x = image[0][row].g - image[column - 1][row].g;
    b_x = image[0][row].b - image[column - 1][row].b;
    x_gradient = pow(r_x, 2) + pow(g_x, 2) + pow(b_x, 2);
    r_y = image[column][0].r - image[column][row - 1].r;
    g_y = image[column][0].g - image[column][row - 1].g;
    b_y = image[column][0].b - image[column][row - 1].b;
    y_gradient = pow(r_y, 2) + pow(g_y, 2) + pow(b_y, 2);
    pixel_energy = x_gradient + y_gradient;
  }

  INFO(image);
  INFO(column);
  INFO(row);
  INFO(width);
  INFO(height);
  return pixel_energy; */
  int leftX = 0;
  int rightX = 0;
  int topY = 0;
  int bottomY = 0;
  if (column - 1 < 0)
  {
    leftX = width - 1;
  }
  else
  {
    leftX = column - 1;
  }

  if (column + 1 > width - 1)
  {
    rightX = 0;
  }
  else
  {
    rightX = column + 1;
  }

  if (row - 1 < 0)
  {
    topY = height - 1;
  }

  else
  {
    topY = row - 1;
  }

  if (row + 1 > height - 1)
  {
    bottomY = 0;
  }
  else
  {
    bottomY = row + 1;
  }
  Pixel leftPixel = image[leftX][row];
  Pixel rightPixel = image[rightX][row];
  Pixel topPixel = image[column][topY];
  Pixel bottomPixel = image[column][bottomY];
  int x_grad = (pow((rightPixel.r - leftPixel.r), 2) + pow((rightPixel.g - leftPixel.g), 2) + pow((rightPixel.b - leftPixel.b), 2));
  int y_grad = (pow((bottomPixel.r - topPixel.r), 2) + pow((bottomPixel.g - topPixel.g), 2) + pow((bottomPixel.b - topPixel.b), 2));
  int energy = x_grad + y_grad;
  return (energy);
}

int loadVerticalSeam(Pixel **image, int start_col, int width, int height, int *seam)
{

  // TODO(student): load a vertical seam
  /* GOAL : This function will traverse through an image starting at the first row of the given column (start_col). See “Loading a vertical seam” below for how the traversal works. See “Seam Representation” below for how seams are represented.
  The function returns the total energy of the seam*/
  //The first parameter is a 2d array of Pixels (structs) that hold a color value
  //The second parameter is the column to start the seam.
  //The third parameter is the width of the array (i.e. the number of columns) needed for traversing the array
  //The fourth parameter is the height of the array (i.e. the number of rows) needed for traversing the array.
  //The fifth parameter is an array to be loaded with column values for each row.

  /*
  Pseudocode GIVEN
  Set seam for the first row to the starting column
  Initialize total energy to the energy for pixel (start_col, 0)
  For each subsequent row
  Calculate the energy of each possible next column
  Set the seam for current row to the column with the minimal energy
  Add the minimal energy to the total energy
  Return total energy
  */

  seam[0] = start_col;
  int left = 0;
  int right = 0;
  int middle = 0;
  int total_energy = energy(image, start_col, 0, width, height); //Initialize total energy to the energy for pixel (start_col, 0)
  for (int x = 1; x < height; x++)
  {
    // || Finding Energies ||
    if (width == 1) //n x 1
    {
      middle = energy(image, start_col, x, width, height);
      right = middle + left;
      left = middle + right;
    }
    else if (start_col == width - 1) //edge case on right hand side
    {
      middle = energy(image, start_col, x, width, height);
      left = middle + right; // oo
      right = energy(image, start_col - 1, x, width, height);
    }
    else if (start_col == 0) // edge case on left hand side
    {
      middle = energy(image, start_col, x, width, height);
      right = middle + left; //oo
      left = energy(image, start_col + 1, x, width, height);
    }
    else //middle cases
    {
      left = energy(image, start_col + 1, x, width, height);
      right = energy(image, start_col - 1, x, width, height);
      middle = energy(image, start_col, x, width, height);
    }

    // || Calculating Minimal Energy +Energy TieBreakers + Adding to total Energy accordingly + changing seam path ||
    if (left > right && middle > right) // minimal energy is right
    {
      start_col = start_col - 1;
      seam[x] = start_col;
      total_energy = total_energy + right;
    }
    else if (right > left && middle > left) // minimal energy is  left
    {
      start_col = start_col + 1;
      seam[x] = start_col;
      total_energy = total_energy + left;
    }
    else if (right > middle && left > middle) // minimal energy is middle
    {
      seam[x] = start_col;
      total_energy = total_energy + middle;
    }
    else if ((left < right && middle == left) || (right < left && middle == right)) // middle and left have same energy and they are both smaller than right OR // middle and right have same energy and they are both smaller than left
    {

      seam[x] = start_col;
      total_energy = total_energy + middle;
    }
    else if (left == right && right < middle) // left and right have same energy and middle is greater than them.
    {
      start_col = start_col + 1;
      seam[x] = start_col;
      total_energy = total_energy + left;
    }
    else if ((middle == left) & (middle == right)) // all three energies are tied in being minimal energy
    {
      seam[x] = start_col;                // path stays in same column
      total_energy = total_energy + left; // in that case add whichever (left,right,or middle) bc they all have the same minimal energy
    }
  }
  return (total_energy);
  INFO(image);
  INFO(start_col);
  INFO(width);
  INFO(height);
  INFO(seam);
}

int loadHorizontalSeam(Pixel **image, int start_row, int width, int height, int *seam)
{
  // TODO(student): load a horizontal seam
  seam[0] = start_row;
  int left = 0;
  int right = 0;
  int middle = 0;
  int total_energy = energy(image, 0, start_row, width, height); //Initialize total energy to the energy for pixel (start_col, 0)
  for (int x = 1; x < width; x++)
  {
    if (height == 1) //1 x n
    {
      middle = energy(image, x, start_row, width, height);
      right = middle + left;
      left = middle + right;
    }
    else if (start_row == height - 1) // bottom cases
    {
      middle = energy(image, x, start_row, width, height);
      left = energy(image, x, start_row - 1, width, height);
      right = left + middle;
    }
    else if (start_row == 0) // top cases
    {
      right = energy(image, x, start_row + 1, width, height);
      middle = energy(image, x, start_row, width, height);
      left = middle + right;
    }
    else // middle cases
    {
      right = energy(image, x, start_row + 1, width, height);
      middle = energy(image, x, start_row, width, height);
      left = energy(image, x, start_row - 1, width, height);
    }

    if (left < right && left == middle)
    {
      seam[x] = start_row;
      total_energy = total_energy + middle;
    }
    else if (middle < left && middle == right)
    {
      seam[x] = start_row;
      total_energy = total_energy + middle;
    }
    else if (right < middle && right == left)
    {
      start_row = start_row - 1;
      seam[x] = start_row;
      total_energy = total_energy + right;
    }
    else if (middle == right && left == middle)
    {
      total_energy = total_energy + middle;
      seam[x] = start_row;
    }
    else if (right < left && right < middle)
    {
      total_energy = total_energy + right;
      start_row = start_row + 1;
      seam[x] = start_row;
    }
    else if (left < middle && left < right)
    {
      total_energy = total_energy + left;
      start_row = start_row - 1;
      seam[x] = start_row;
    }
    else if (middle < right && middle < left)
    {
      total_energy += middle;
      seam[x] = start_row;
    }
  }
  return total_energy;
  // IGNORE
  INFO(image);
  INFO(start_row);
  INFO(width);
  INFO(height);
  INFO(seam);
  // IGNORE
}

int *findMinVerticalSeam(Pixel **image, int width, int height)
{
  int *min_Seam = new int[height];
  int *normal_seam = new int[height];
  int min_Energy = loadVerticalSeam(image, 0, width, height, normal_seam);
  int energy_now = -1;
  for (int i = 0; i < height; i++)
  {
    min_Seam[i] = normal_seam[i];
  }

  for (int i = 1; i < width; i++)
  {
    energy_now = loadVerticalSeam(image, i, width, height, normal_seam);

    if (energy_now < min_Energy)
    {
      min_Energy = energy_now;

      for (int i = 0; i < height; i++)
      {
        min_Seam[i] = normal_seam[i];
      }
    }
  }
  delete[] normal_seam;
  normal_seam = nullptr;
  return min_Seam;
}

int *findMinHorizontalSeam(Pixel **image, int width, int height)
{
  int *min_Seam = new int[width];
  int *normal_seam = new int[width];
  int min_Energy = loadHorizontalSeam(image, 0, width, height, normal_seam);
  int energy_now = -1;
  for (int i = 0; i < width; i++)
  {
    min_Seam[i] = normal_seam[i];
  }
  for (int i = 1; i < height; i++)
  {
    energy_now = loadHorizontalSeam(image, i, width, height, normal_seam);
    if (energy_now < min_Energy)
    {
      min_Energy = energy_now;
      for (int i = 0; i < width; i++)
      {
        min_Seam[i] = normal_seam[i];
      }
    }
  }
  delete[] normal_seam;
  normal_seam = nullptr;
  return min_Seam;
}

void removeVerticalSeam(Pixel **image, int width, int height, int *verticalSeam)
{
  Pixel temp;
  for (int i = 0; i < height; i++)
  {
    temp = image[verticalSeam[i]][i];
    for (int j = verticalSeam[i]; j < width - 1; j++)
    {
      image[j][i] = image[j + 1][i];
    }
    image[width - 1][i] = temp;
  }
}

void removeHorizontalSeam(Pixel **image, int width, int height, int *horizontalSeam)
{
  Pixel temp;
  for (int i = 0; i < width; i++)
  {
    temp = image[i][horizontalSeam[i]];

    for (int j = horizontalSeam[i]; j < height - 1; j++)
    {
      image[i][j] = image[i][j + 1];
    }
    image[i][height - 1] = temp;
  }
}