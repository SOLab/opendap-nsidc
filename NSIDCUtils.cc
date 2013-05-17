#include "NSIDCUtils.h"

#include <sstream>
#include <string>
#include <algorithm>
#include <regex.h>
#include <iostream>  
#include <fstream>
#include <AttrTable.h>
#include <BESDebug.h>
#include <BESDapError.h>
#include <BESNotFoundError.h>
#include <mime_util.h>
#include <stdlib.h>

using std::ostringstream;

using namespace libdap;

char* readBytesFromFile(string filename, size_t bytesLength)
{
    ifstream fl(filename.c_str());  
    fl.seekg( 0, ios::end );  
    size_t len = fl.tellg();
    if (bytesLength > 0)
        len = bytesLength;
    char *ret = new char[len];  
    fl.seekg(0, ios::beg);   
    fl.read(ret, len);  
    fl.close();  
    return ret;  
}

bool is_north(const string &filename)
{
    regex_t preg_north;
    const char *north_file_regex =  "^nt_[0-9]{6,8}_[0-9a-z]{3}_[0-9a-z]{3}_n.bin$";
    regcomp(&preg_north, north_file_regex, REG_EXTENDED | REG_NOSUB);
    return regexec(&preg_north, name_path(filename).c_str(), 0, NULL, 0) == 0;
}

int get_columns_number(const string &filename)
{
    int columns;
    if (is_north(filename)) {
        columns = 304;
    } else {
        columns = 316;
    }
    return columns;
}

int get_rows_number(const string &filename)
{
    int rows;
    if (is_north(filename)) {
        rows = 448;
    } else {
        rows = 332;
    }
    return rows;
}

string escape(string value)
{
    using std::replace;
    replace(value.begin(), value.end(), '/', '_');
    return value;
}
