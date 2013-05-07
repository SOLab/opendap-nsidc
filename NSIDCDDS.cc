#include "NSIDCDDS.h"
#include "NSIDCVariable.h"
#include "NSIDCArray.h"

#include <Array.h>
#include <BaseType.h>
#include <Byte.h>
#include <UInt16.h>
#include <Int16.h>
#include <UInt32.h>
#include <Int32.h>
#include <Float32.h>
#include <Float64.h>
#include <Str.h>
#include <mime_util.h>

#include <BESNotFoundError.h>
#include <BESDebug.h>

#include <sys/types.h>
#include <sstream>
#include "NSIDCUtils.h"

void
read_descriptors( DDS &dds, const string &filename )
{
    dds.set_dataset_name( name_path( filename ) ) ;

    int columns = get_columns_number(filename);
    int rows = get_rows_number(filename);    

    NSIDCVariable variable = NSIDCVariable();
    BaseType *bt = 0;
    bt = dds.get_factory()->NewByte( variable._short_name ) ;
    NSIDCArray *ar = new NSIDCArray( variable._short_name, filename, bt);

    if (bt)
    {
        ar->add_var( bt ) ;

        ar->append_dim( columns, "lon" );
        ar->append_dim( rows, "lat" );

        dds.add_var( ar );
    }

    delete ar;
    delete bt;
}

