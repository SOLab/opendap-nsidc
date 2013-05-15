#ifndef E_NSIDCDAS_h
#define E_NSIDCDAS_h 1

#include <string>
#include <DAS.h>

using namespace libdap;

void read_attributes(DAS &das, const string &filename) ;
void set_global_attributes( DAS &das );
void set_file_headers( DAS &das, const string &filename );
void set_ice_variable( DAS &das );
void set_lat_variable( DAS &das );
void set_lon_variable( DAS &das );

#endif // E_NSIDCDAS_h
