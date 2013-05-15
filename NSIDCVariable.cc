#include "NSIDCVariable.h"
#include <string>

using std::string;

NSIDCVariable::NSIDCVariable(string short_name, string long_name, double scale_factor, string units)
    : _short_name(short_name), 
      _long_name(long_name), 
      _scale_factor(scale_factor), 
      _units(units)
{

}

