#ifndef E_NSIDCVar_h
#define E_NSIDCVar_h 1

#include <string>
#include <vector>

using std::string;
using std::vector;

class NSIDCVariable
{
public:
    NSIDCVariable();

    string _short_name ;
    string _long_name ;
    double _scale_factor ;
    string _units ;
};

#endif // E_NSIDCVar_h
