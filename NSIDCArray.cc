#include "NSIDCArray.h"
#include "NSIDCUtils.h"

#include <BESDapError.h>
#include <BESNotFoundError.h>

#include <BESDebug.h>

#include <stdlib.h>
#include <sys/types.h>

NSIDCArray::NSIDCArray( const string &n, const string &d, BaseType *v )
    : Array( n, d, v )
{

}

NSIDCArray::~NSIDCArray()
{

}

BaseType *NSIDCArray::ptr_duplicate()
{
    return new NSIDCArray( *this );
}

bool NSIDCArray::read()
{
    vector<int> start, stop, stride;
    bool is_slab = getSlabConstraint( start, stop, stride ) ;
    string filename = dataset();

    // read all bytes from file
    char *fileBuffer = readBytesFromFile(filename, 0);

    int columns = get_columns_number(filename);
    int rows = get_rows_number(filename);
    int headerSize = 300;

    if (start[0] >= columns || 
        stop[0] >= columns ||
        start[1] >= rows ||
	stop[1] >= rows) {
	    throw BESDapError( "Requested index is greater than grid dimension", true,
                               unknown_error, __FILE__, __LINE__ ) ;
	}
    
    // allocate memory for destination buffer
    int capacity = rows * columns; 
    char *buffer = (char*) malloc( capacity );

    int counter = 0;
    for (int i = start[0]; i <= stop[0]; i += stride[0]) {
        for (int j = start[1]; j <= stop[1]; j += stride[1]) {
	    int byteIndex = (columns * j + i) + headerSize;
	    buffer[counter++] = fileBuffer[byteIndex];
        }
    }

    val2buf( (void*) buffer ) ;

    free( buffer ) ;
    free( fileBuffer ) ;

    set_read_p( true ) ;
    return true ;

}

bool NSIDCArray::getSlabConstraint( vector<int>&start_array,
        vector<int>&stop_array, vector<int>&stride_array )
{
    int start = 0, stop = 0, stride = 0 ;

    start_array = vector<int> ( 0 ) ;
    stop_array = vector<int> ( 0 ) ;
    stride_array = vector<int> ( 0 ) ;

    for ( Array::Dim_iter p = dim_begin(); p != dim_end(); ++p ) {
        start = dimension_start( p, true ) ;
        stride = dimension_stride( p, true ) ;
        stop = dimension_stop( p, true ) ;
        if ( start == 0 && stop == 0 && stride == 0 )
            return false; // no slab constraint
        if ( start > stop )
            throw BESDapError( "start > stop", true,
                               unknown_error, __FILE__, __LINE__ ) ;

        start_array.push_back( start ) ;
        stop_array.push_back( stop ) ;
        stride_array.push_back( stride ) ;
        //std::cerr << "NSIDCArray::read: start = " << start << ", stop = " << stop << ", stride = " << stride << std::endl;
    }
    return true ;
}
