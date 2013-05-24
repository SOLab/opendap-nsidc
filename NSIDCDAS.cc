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

    set_ice_variable(das);

    set_lat_variable(das);

    set_lon_variable(das);
}

void
set_global_attributes( DAS &das )
{
    string table_name = "NSIDC_GLOBAL";
    AttrTable *attr_table_ptr = das.get_table( table_name ) ;

    if( !attr_table_ptr )
        attr_table_ptr =
                das.add_table( table_name, new AttrTable );

    attr_table_ptr->append_attr( "CONVENTIONS", AttrType_to_String(Attr_string), "COARDS" ) ;
    attr_table_ptr->append_attr( "short_name", AttrType_to_String(Attr_string), "NSIDC_SSMI_NRT_SEAICE" ) ;
    attr_table_ptr->append_attr( "long_name", AttrType_to_String(Attr_string), "Near-Real-Time DMSP SSMI-SSMIS Daily Polar Gridded Sea Ice Concentrations" ) ;
    attr_table_ptr->append_attr( "producer_agency", AttrType_to_String(Attr_string), "National Snow & Ice Data Center" ) ;
    attr_table_ptr->append_attr( "spatial_resolution", AttrType_to_String(Attr_string), "25 km" ) ;
    attr_table_ptr->append_attr( "platforms", AttrType_to_String(Attr_string), "Nimbus_7, DMSP_F8, F11, F13, F17" ) ;
    attr_table_ptr->append_attr( "sensors", AttrType_to_String(Attr_string), "SMMR, SSMI-SSMIS" ) ;
    attr_table_ptr->append_attr( "spatial_coverage", AttrType_to_String(Attr_string), "North and south polar regions" ) ;
    attr_table_ptr->append_attr( "parameters", AttrType_to_String(Attr_string), "Sea ice concentration" ) ;
    attr_table_ptr->append_attr( "temporal_coverage", AttrType_to_String(Attr_string), "Final data: 26 October 1978 - most current processing; Preliminary data: most recent 3 - 12 months of processed data" ) ;
    attr_table_ptr->append_attr( "temporal_resolution", AttrType_to_String(Attr_string), "SMMR: every other day;SSMI-SSMIS: daily" ) ;
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
    for(int i=0;i<5;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "missing_data_integer_value", AttrType_to_String( Attr_string ), ss.str() ) ;
    ss.str("");

    for(int i=6;i<11;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "number_of_columns_in_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=12;i<17;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "number_of_rows_in_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=24;i<29;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "latitude_enclosed_by_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=30;i<35;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "greenwich_orientation_of_polar_stereographic_grid", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=42;i<47;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "j_coordinate_of_the_grid_intersection_at_the_pole", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=48;i<53;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "i_coordinate_of_the_grid_intersection_at_the_pole", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=54;i<59;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "instrument_descriptor", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=60;i<65;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "two_descriptors_of_two_characters_each_that_describe_the_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=66;i<71;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "starting_julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=72;i<77;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "starting_hour_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=78;i<83;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "starting_minute_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=84;i<89;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "ending_julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=90;i<95;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "ending_hour_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=96;i<101;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "ending_minute_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=102;i<107;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "year_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=108;i<113;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "julian_day_of_grid_data", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=115;i<119;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "three_digit_channel_descriptor", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=120;i<126;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "integer_scaling_factor", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=126;i<147;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "file_name", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    for(int i=150;i<229;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "80_character_image_title", AttrType_to_String( Attr_string ),  escape(ss.str()) ) ;
    ss.str("");

    for(int i=230;i<229;i++)
    {
        ss <<  fileBuffer[i];
    }
    attr_table_ptr->append_attr( "70_character_data_information", AttrType_to_String( Attr_string ),  ss.str() ) ;
    ss.str("");

    free( fileBuffer ) ;
}

void
set_ice_variable( DAS &das )
{
    ostringstream ostream;
    AttrTable *attr_table_ptr = das.get_table("sea_ice_concentration") ;

    if( !attr_table_ptr )
        attr_table_ptr =
            das.add_table("sea_ice_concentration", new AttrTable );

    attr_table_ptr->append_attr("long_name", AttrType_to_String( Attr_string ), "Sea Ice Concentration");
    attr_table_ptr->append_attr("description", AttrType_to_String( Attr_string ), "fractional coverage scaled by scale_factor");

    ostream.str("");
    ostream << 0 ;
    attr_table_ptr->append_attr( "add_offset", AttrType_to_String( Attr_byte ), ostream.str());

    ostream.str("");
    ostream << 250;
    attr_table_ptr->append_attr( "scale_factor", AttrType_to_String( Attr_byte ), ostream.str());

    attr_table_ptr->append_attr( "flag_values", AttrType_to_String( Attr_byte ), "251 252 253 254");

    attr_table_ptr->append_attr( "flag_meanings", AttrType_to_String( Attr_byte ), "arctic_pole_data_gap unused_value coastlines superimposed_land_mask" ) ;

    attr_table_ptr->append_attr( "missing_value", AttrType_to_String( Attr_byte ), "255");
    attr_table_ptr->append_attr( "units", AttrType_to_String( Attr_string ), "1");
    attr_table_ptr->append_attr( "coordinates", AttrType_to_String( Attr_string ), "latitude longitude");
}

void
set_lat_variable( DAS &das )
{
    AttrTable *attr_table_ptr = das.get_table( "latitude");

    if(!attr_table_ptr)
        attr_table_ptr =
            das.add_table("latitude", new AttrTable);

    attr_table_ptr->append_attr("long_name", AttrType_to_String( Attr_string ), "latitude");
    attr_table_ptr->append_attr("units", AttrType_to_String( Attr_string ), "degrees_north");
    attr_table_ptr->append_attr("standard_name", AttrType_to_String( Attr_string ), "latitude");
}

void
set_lon_variable( DAS &das )
{
    AttrTable *attr_table_ptr = das.get_table( "longitude" ) ;

    if( !attr_table_ptr )
        attr_table_ptr =
            das.add_table( "longitude", new AttrTable );

    attr_table_ptr->append_attr( "long_name", AttrType_to_String( Attr_string ), "longitude");
    attr_table_ptr->append_attr( "units", AttrType_to_String( Attr_string ),  "degrees_east" );
    attr_table_ptr->append_attr( "standard_name", AttrType_to_String( Attr_string ),  "longitude");
}



