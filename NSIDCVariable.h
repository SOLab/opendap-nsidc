#ifndef E_NSIDCVar_h
#define E_NSIDCVar_h 1

#include <string>

using std::string;

class NSIDCVariable
{
public:
    NSIDCVariable();
    NSIDCVariable(string short_name, string long_name, double scale_factor, string units);
    string _short_name ;
    string _long_name ;
    double _scale_factor ;
    string _units ;
};

#endif // E_NSIDCVar_h
