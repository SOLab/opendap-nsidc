#include "NSIDCUtils.h"

#include <sstream>
#include <string>
#include <algorithm>
#include <regex.h>

#include <AttrTable.h>
#include <BESDebug.h>
#include <BESDapError.h>
#include <BESNotFoundError.h>
#include <mime_util.h>
#include <stdlib.h>

using std::ostringstream;

using namespace libdap;

char *readBytesFromFile(string filename, int bytesLength)
{       
    FILE *pFile;
    pFile = fopen( filename.c_str(), "rb" );
    if (pFile == NULL)
    {
        string err = (string)"Unable to open file " + filename ;
        throw BESNotFoundError( err, __FILE__, __LINE__ ) ;
    }
    
    long fileLen;
    fseek (pFile, 0, SEEK_END);
    fileLen = ftell(pFile);
    rewind(pFile);
     
    int capacity = bytesLength == 0 ? sizeof(char)*fileLen : bytesLength;   
    //char *fileBuffer = (char*) malloc( capacity );
    char *fileBuffer = new char[capacity];

    if (!fileBuffer)
    {   
        throw BESDapError( "Unable to load file content into memory", true, 
                            unknown_error, __FILE__, __LINE__ ) ;
    }

    // read file contents into buffer
    fread(fileBuffer, 1, capacity, pFile);
    fclose(pFile);
    return fileBuffer;
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
