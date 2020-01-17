#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <limits>
#include <ctime>
#include <cstdint>

#include "cmdline.h"
#include "options.h"
#include "bmp.h"


using namespace std;


int main(int argc, char const *argv[])
{
  cmdline cmdl(options);
  cmdl.parse(argc, argv);

  bmp bmp(ifs);

  (ifs).close();
  (ofs).close();


  return 0;
}
