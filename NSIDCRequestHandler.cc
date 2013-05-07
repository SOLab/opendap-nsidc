// NSIDCRequestHandler.cc

#include "config.h"

#include "NSIDCRequestHandler.h"
#include "NSIDCDAS.h"
#include "NSIDCDDS.h"

#include <BESResponseHandler.h>
#include <BESResponseNames.h>
#include "NSIDCResponseNames.h"
#include <BESVersionInfo.h>
#include <BESTextInfo.h>
#include "BESDataDDSResponse.h"
#include "BESDDSResponse.h"
#include "BESDASResponse.h"
#include <BESConstraintFuncs.h>
#include <BESServiceRegistry.h>
#include <BESUtil.h>
#include <BESDapNames.h>
#include <BESDapError.h>
#include <Ancillary.h>
#include <BESDataNames.h>
#include <BESDebug.h>
#include <BESNotFoundError.h>
#include <BESInternalFatalError.h>

NSIDCRequestHandler::NSIDCRequestHandler( const string &name )
    : BESRequestHandler( name )
{
    add_handler( DAS_RESPONSE, NSIDCRequestHandler::binary_ssmi_nsidc_build_das ) ;
    add_handler( DDS_RESPONSE, NSIDCRequestHandler::binary_ssmi_nsidc_build_dds ) ;
    add_handler( DATA_RESPONSE, NSIDCRequestHandler::binary_ssmi_nsidc_build_data ) ;
    add_handler( VERS_RESPONSE, NSIDCRequestHandler::binary_ssmi_nsidc_build_vers ) ;
    add_handler( HELP_RESPONSE, NSIDCRequestHandler::binary_ssmi_nsidc_build_help ) ;
}

NSIDCRequestHandler::~NSIDCRequestHandler()
{
}

bool
NSIDCRequestHandler::binary_ssmi_nsidc_build_das( BESDataHandlerInterface &dhi )
{

    bool ret = true ;
    BESResponseObject *response =
    dhi.response_handler->get_response_object();
    BESDASResponse *bdas = dynamic_cast < BESDASResponse * >(response);
    DAS *das = bdas->get_das();

    try
    {
        string accessed = dhi.container->access() ;
        read_attributes( *das, accessed ) ;
        Ancillary::read_ancillary_das( *das, accessed ) ;
        return ret;
    }
    catch(InternalErr &e)
    {
        throw BESDapError( e.get_error_message(), true,
                           e.get_error_code(), __FILE__, __LINE__ ) ;
    }
    catch(Error &e)
    {
        throw BESDapError( e.get_error_message(), false,
                           e.get_error_code(), __FILE__, __LINE__);
    }
    catch(...)
    {
        throw BESDapError( "Caught unknown error build NSIDC DAS response", true,
                           unknown_error, __FILE__, __LINE__);
    }

    return ret ;
}

bool
NSIDCRequestHandler::binary_ssmi_nsidc_build_dds( BESDataHandlerInterface &dhi )
{
    bool ret = true ;
    BESResponseObject *response =
    dhi.response_handler->get_response_object();
    BESDDSResponse *bdds = dynamic_cast < BESDDSResponse * >(response);
    DDS *dds = bdds->get_dds();

    BaseTypeFactory *factory = new BaseTypeFactory ;
    dds->set_factory( factory ) ;

    try
    {
        string accessed = dhi.container->access() ;
        dds->filename( accessed ) ;
        read_descriptors( *dds, accessed ) ;
        Ancillary::read_ancillary_dds( *dds, accessed ) ;

        DAS das;
        read_attributes(das, accessed);
        Ancillary::read_ancillary_das( das, accessed ) ;
        dds->transfer_attributes( &das ) ;

        BESDEBUG( "NSIDC", "dds = " << endl << *dds << endl ) ;
        dhi.data[POST_CONSTRAINT] = dhi.container->get_constraint();

        return ret;
    }
    catch(InternalErr &e)
    {
        throw BESDapError( e.get_error_message(), true,
                           e.get_error_code(), __FILE__, __LINE__);
    }
    catch(Error &e)
    {
        throw BESDapError( e.get_error_message(), false,
                           e.get_error_code(), __FILE__, __LINE__);
    }
    catch(...)
    {
        throw BESDapError( "Caught unknown error build Ssmi DDS response", true,
                           unknown_error, __FILE__, __LINE__);
    }

    return ret ;
}

bool
NSIDCRequestHandler::binary_ssmi_nsidc_build_data( BESDataHandlerInterface &dhi )
{
    BESResponseObject *response = dhi.response_handler->get_response_object();
    BESDataDDSResponse *bdds = dynamic_cast < BESDataDDSResponse * >(response);
    if (!bdds)
        throw BESInternalError("cast error", __FILE__, __LINE__);

    try
    {
        bdds->set_container(dhi.container->get_symbolic_name());
        DataDDS *dds = bdds->get_dds();
        BaseTypeFactory *factory = new BaseTypeFactory ;
        dds->set_factory(factory);

        string accessed = dhi.container->access();
        dds->filename( accessed );

        read_descriptors(*dds, accessed);
        Ancillary::read_ancillary_dds( *dds, accessed ) ;

        DAS *das = new DAS;
        BESDASResponse bdas(das);
        bdas.set_container(dhi.container->get_symbolic_name());
        read_attributes(*das, accessed);
        Ancillary::read_ancillary_das(*das, accessed ) ;

        dds->transfer_attributes(das) ;

        dhi.data[POST_CONSTRAINT] = dhi.container->get_constraint();

        bdds->set_constraint(dhi);
        bdds->clear_container();
    }
    catch(InternalErr &e)
    {
        throw BESDapError( e.get_error_message(), true,
                           e.get_error_code(), __FILE__, __LINE__);
    }
    catch(Error &e)
    {
        throw BESDapError( e.get_error_message(), false,
                           e.get_error_code(), __FILE__, __LINE__);
    }
    catch (std::exception &e) 
    {
        string s = string("C++ Exception: ") + e.what();
        BESInternalFatalError ex(s, __FILE__, __LINE__);
        throw ex;
    }
    catch(...)
    {
        throw BESDapError( "Caught unknown error build NSIDC DataDDS response", true,
                           unknown_error, __FILE__, __LINE__);
    }
    return true;
}

bool
NSIDCRequestHandler::binary_ssmi_nsidc_build_vers( BESDataHandlerInterface &dhi )
{
    std::cerr << "build vers" << std::endl;

    bool ret = true ;
    BESVersionInfo *info = dynamic_cast<BESVersionInfo *>(dhi.response_handler->get_response_object() ) ;
    info->add_module( PACKAGE_NAME, PACKAGE_VERSION ) ;
    return ret ;
}

bool
NSIDCRequestHandler::binary_ssmi_nsidc_build_help( BESDataHandlerInterface &dhi )
{
    std::cerr << "build help" << std::endl;

    bool ret = true ;
    BESInfo *info = dynamic_cast<BESInfo *>(dhi.response_handler->get_response_object());

    // This is an example. If you had a help file you could load it like
    // this and if your handler handled the following responses.
    map<string,string> attrs ;
    attrs["name"] = PACKAGE_NAME ;
    attrs["version"] = PACKAGE_VERSION ;
    list<string> services ;
    BESServiceRegistry::TheRegistry()->services_handled( NSIDC_NAME, services );
    if( services.size() > 0 )
    {
	string handles = BESUtil::implode( services, ',' ) ;
	attrs["handles"] = handles ;
    }
    info->begin_tag( "module", &attrs ) ;
    //info->add_data_from_file( "NSIDC.Help", "NSIDC Help" ) ;
    info->end_tag( "module" ) ;

    return ret ;
}

void
NSIDCRequestHandler::dump( ostream &strm ) const
{
    strm << BESIndent::LMarg << "NSIDCRequestHandler::dump - ("
			     << (void *)this << ")" << endl ;
    BESIndent::Indent() ;
    BESRequestHandler::dump( strm ) ;
    BESIndent::UnIndent() ;
}

