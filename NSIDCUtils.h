#ifndef E_NSIDCUtils_h
#define E_NSIDCUtils_h 1
#include <string>

using std::string;

bool is_north(const string &filename);
int get_columns_number(const string &filename);
int get_rows_number(const string &filename);
char *readBytesFromFile(string filename, size_t bytesLength);
string escape(string value);

#endif // E_NSIDCUtils_h
