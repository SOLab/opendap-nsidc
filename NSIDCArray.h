#ifndef _NSIDC_Array_h
#define _NSIDC_Array_h

// STL includes
#include <string>
#include <vector>

// DODS includes
#include <Array.h>

using namespace libdap;

class NSIDCArray : public Array
{
public:
    NSIDCArray( const string & n, const string &d, BaseType * v ) ;
    virtual ~NSIDCArray() ;
    virtual BaseType *ptr_duplicate() ;
    virtual bool read() ;
    bool getSlabConstraint(vector < int >&start_array,
                            vector < int >&stop_array,
                            vector < int >&stride_array ) ;
    float *readGridCoordinatesFromFile(char* filename);
};

#endif // _NSIDC_Array_h
