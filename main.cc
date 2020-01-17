#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <limits>
#include <ctime>
#include <vector>
#include <cstdint>

#include "cmdline.h"
#include "options.h"
#include "bmp.h"


using namespace std;

int main(int argc, char const *argv[])
{
  cmdline cmdl(options);
  cmdl.parse(argc, argv);

  bmp bmp1(ifs);
  bmp bmp2(500,500,true);

  bmp2.copyData(bmp1);


  bmp2.write(ofs);

  (ifs).close();
  (ofs).close();


  return 0;
}
