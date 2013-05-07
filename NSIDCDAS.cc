#include "NSIDCDAS.h"
#include "NSIDCUtils.h"
#include "NSIDCVariable.h"

#include <BESNotFoundError.h>
#include <BESDebug.h>
#include <mime_util.h>

#include <sstream>
#include <sys/types.h>
#include <stdlib.h>

using std::ostringstream;

void
read_attributes(DAS &das, const string &filename)
{
    set_global_attributes(das);
    
    set_file_headers(das, filename);

    set_variable(das);
}

void
set_global_attributes( DAS &das )
{
    string table_name = "NSIDC_GLOBAL";
    AttrTable *attr_table_ptr = das.get_table( table_name ) ;

    if( !attr_table_ptr )
        attr_table_ptr =
                das.add_table( table_name, new AttrTable );

    attr_table_ptr->append_attr( "short_name", AttrType_to_String(Attr_string), "NSIDC_SSMI_NRT_SEAICE" ) ;
    attr_table_ptr->append_attr( "long_name", AttrType_to_String(Attr_string), "Near-Real-Time DMSP SSM/I-SSMIS Daily Polar Gridded Sea Ice Concentrations" ) ;
    attr_table_ptr->append_attr( "producer_agency", AttrType_to_String(Attr_string), "National Snow & Ice Data Center" ) ;
    attr_table_ptr->append_attr( "spatial_resolution", AttrType_to_String(Attr_string), "25 km" ) ;
    attr_table_ptr->append_attr( "platforms", AttrType_to_String(Attr_string), "Nimbus-7, DMSP-F8, -F11, -F13, -F17" ) ;
    attr_table_ptr->append_attr( "sensors", AttrType_to_String(Attr_string), "SMMR, SSM/I-SSMIS" ) ;
    attr_table_ptr->append_attr( "spatial_coverage", AttrType_to_String(Attr_string), "North and south polar regions" ) ;
    attr_table_ptr->append_attr( "parameters", AttrType_to_String(Attr_string), "Sea ice concentration" ) ;
    attr_table_ptr->append_attr( "temporal_coverage", AttrType_to_String(Attr_string), "Final data: 26 October 1978 - most current processing; Preliminary data: most recent 3 - 12 months of processed data" ) ;
    attr_table_ptr->append_attr( "temporal_resolution", AttrType_to_String(Attr_string), "SMMR: every other day;SSM/I-SSMIS: daily" ) ;
    attr_table_ptr->append_attr( "version", AttrType_to_String(Attr_string), "1.0" ) ;
}

void
set_file_headers( DAS &das, const string &filename )
{
    string table_name = "NSIDC_HEADERS";
    AttrTable *attr_table_ptr = das.get_table( table_name ) ;

    if( !attr_table_ptr )
        attr_table_ptr =
            das.add_table( table_name, new AttrTable );

    // read header bytes from file
    char *fileBuffer = readBytesFromFile(filename, 300);

    std::stringstream ss;
    for(int i=0;i<6;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "missing_data_integer_value", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=6;i<12;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "number_of_columns_in_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=12;i<18;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "number_of_rows_in_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=24;i<30;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "latitude_enclosed_by_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=30;i<36;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "greenwich_orientation_of_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=42;i<48;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "J-coordinate_of_the_grid_intersection_at_the_pole", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=48;i<54;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "I-coordinate_of_the_grid_intersection_at_the_pole", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=54;i<60;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "instrument_descriptor_(SMMR,SSM/I)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=60;i<66;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "two_descriptors_of_two_characters_each_that_describe_the_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=66;i<72;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Starting_Julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=72;i<78;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Starting_hour_of_grid_data_(if_available)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=78;i<84;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Starting_minute_of_grid_data_(if_available)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=84;i<90;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Ending_Julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=90;i<96;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Ending_hour_of_grid_data_(if_available)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=96;i<102;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Ending_minute_of_grid_data_(if_available)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=102;i<108;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Year_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=108;i<114;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=115;i<120;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Three-digit_channel_descriptor_(000_for_ice_concentrations)", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=120;i<126;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "Integer_scaling_factor", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=126;i<150;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "file_name", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=150;i<230;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "80-character_image_title", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=230;i<300;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "70-character_data_information", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    free( fileBuffer ) ;
}

void
set_variable( DAS &das )
{
    ostringstream ostream;

    NSIDCVariable variable = NSIDCVariable();

    AttrTable *attr_table_ptr = das.get_table( variable._short_name ) ;

    if( !attr_table_ptr )
        attr_table_ptr =
            das.add_table( variable._short_name, new AttrTable );

    attr_table_ptr->append_attr( "long_name", AttrType_to_String( Attr_string ),  variable._long_name ) ;

    ostream.str("");
    ostream << 0 ;
    attr_table_ptr->append_attr( "add_offset", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << variable._scale_factor ;
    attr_table_ptr->append_attr( "scale_factor", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << 251 ;
    attr_table_ptr->append_attr( "_arctic_pole_data_gap", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << 252 ;
    attr_table_ptr->append_attr( "_unused_value", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << 253 ;
    attr_table_ptr->append_attr( "_coastlines", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << 254 ;
    attr_table_ptr->append_attr( "_superimposed_land_mask", AttrType_to_String( Attr_byte ), ostream.str() ) ;

    ostream.str("");
    ostream << 255 ;
    attr_table_ptr->append_attr( "_missing_data", AttrType_to_String( Attr_byte ), ostream.str() ) ;


    attr_table_ptr->append_attr( "units", AttrType_to_String( Attr_string ), variable._units ) ;
}




