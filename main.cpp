#include <iostream>
#include <fstream>
#include "bitmap.h"
#include "greyscale.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 1)
    {
        cout << "Error: Invalid number of arguments." << endl;
        return 0;
    }

    if (argc == 1)
    {
        cout << "Usage: bmp2gbdk.exe <filename>" << endl;
        return 0;
    }

    bitmap bmp(argv[1]);
    greyscale grey(bmp);
}
