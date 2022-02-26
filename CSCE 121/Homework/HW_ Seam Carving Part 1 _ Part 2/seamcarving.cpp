#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cin;
using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

void testEnergies(Pixel **image, int width, int height)
{

  cout << "--- energies ---" << endl;
  cout << "Correct Energies:" << endl;
  cout << "57685 50893 91370 25418 33055 37246" << endl;
  cout << "15421 56334 22808 54796 11641 25496" << endl;
  cout << "12344 19236 52030 17708 44735 20663" << endl;
  cout << "17074 23678 30279 80663 37831 45595" << endl;
  cout << "32337 30796 4909  73334 40613 36556" << endl;
  cout << "Your Energies:" << endl;
  int e;
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {

      e = energy(image, x, y, width, height);
      cout << e << " ";
    }
    cout << endl;
  }
}

void testSeam(Pixel **image, int width, int height)
{

  int start_col = 1;
  int *seam = createSeam(height);
  int seamEnergy = loadVerticalSeam(image, start_col, width, height, seam);

  cout << "--- seam ---" << endl;
  cout << "Correct Seam: 126528" << endl;
  cout << "Your Seam:    " << seamEnergy << endl; // 126528
  cout << "Correct Seam: 1 0 0 0 1" << endl;
  cout << "Your Seam:    ";
  for (int y = 0; y < height; ++y)
  { // 1 0 0 0 1
    cout << seam[y] << " ";
  }
  cout << endl;
}

void test(Pixel **image, int width, int height)
{
  testEnergies(image, width, height);
  testSeam(image, width, height);
}

int main()
{
  cout << "Input filename: ";
  string filename;
  cin >> filename;

  // TODO(student): add error checking for width, height, targetWidth, and targetHeight
  cout << "Input width and height: " << endl;
  int width = 0;
  int height = 0;
  cin >> width;
  if (cin.fail())
  {
    cout << "Error: width is a non-integer value" << endl;
    return false;
  }
  cin >> height;
  if (cin.fail())
  {
    cout << "Error: height is a non-integer value" << endl;
    return false;
  }
  if (height <= 0)
  {
    cout << "Error: height must be greater than 0. You entered " << height << endl;
    return (false);
  }
  if (width <= 0)
  {
    cout << "Error: width must be greater than 0. You entered " << width << endl;
    return (false);
  }
  cout << "Input target width and height: " << endl;
  int targetWidth = 0;
  int targetHeight = 0;
  cin >> targetWidth;
  if (cin.fail())
  {
    cout << "Error: target width is a non-integer value" << endl;
    return false;
  }
  cin >> targetHeight;
  if (cin.fail())
  {
    cout << "Error: target height is a non-integer value" << endl;
    return false;
  }
  if (targetHeight <= 0)
  {
    cout << "Error: target height must be greater than 0. You entered " << targetHeight << endl;
    return false;
  }
  if (targetWidth <= 0)
  {
    cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl;
    return false;
  }
  if (targetWidth > width)
  {
    cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width << endl;
    return false;
  }
  if (targetHeight > height)
  {
    cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height << endl;
    return false;
  }

  // save originalWidth since width will change with carving
  int originalWidth = width;

  Pixel **image = createImage(width, height);
  if (image != nullptr)
  { // new returns nullptr if it fails to allocate array

    if (loadImage(filename, image, width, height))
    {
      // test(image1, width, height); // ADD THIS LINE
    }
    {

      // uncomment for part 2

      while ((width - targetWidth > 0) || (height - targetHeight > 0))
      {
        if (width - targetWidth > 0)
        {
          int *verticalSeam = findMinVerticalSeam(image, width, height);
          removeVerticalSeam(image, width, height, verticalSeam);
          deleteSeam(verticalSeam);
          width--;
        }

        // this is for the extra credit
        if (height - targetHeight > 0)
        {
          int *horizontalSeam = findMinHorizontalSeam(image, width, height);
          removeHorizontalSeam(image, width, height, horizontalSeam);
          deleteSeam(horizontalSeam);
          height--;
        }
      }

      ostringstream oss;
      oss << "carved" << width << "X" << height << "." << filename;
      outputImage(oss.str().c_str(), image, width, height);
    }
  }

  // call last to remove the memory from the heap
  deleteImage(image, originalWidth);
}