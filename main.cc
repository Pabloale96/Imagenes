#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>

#include "cmdline.h"
#include "options.h"

using namespace std;


int main(int argc, char const *argv[])
{

  cmdline cmdl(options);
  cmdl.parse(argc, argv);

  std::cout << "hola mundo" << endl;


  return 0;
}
