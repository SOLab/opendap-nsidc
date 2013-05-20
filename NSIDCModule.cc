// NSIDCModule.cc

#include <iostream>

using std::endl ;

#include "NSIDCModule.h"
#include "BESRequestHandlerList.h"
#include "NSIDCRequestHandler.h"
#include "BESDebug.h"
#include "BESResponseHandlerList.h"
#include "BESResponseNames.h"
#include "NSIDCResponseNames.h"
#include "NSIDCGridCoordinates.h"

#include "BESContainerStorageList.h"
#include "BESContainerStorageCatalog.h"
#include "BESCatalogDirectory.h"
#include "BESCatalogList.h"
#include <BESDapService.h>


void
NSIDCModule::initialize( const string &modname )
{
    BESDEBUG( modname, "Initializing NSIDC Module "
		       << modname << endl ) ;

    BESDEBUG( modname, "    adding " << modname
		       << " request handler" << endl ) ;
    BESRequestHandlerList::TheList()->add_handler( modname, new NSIDCRequestHandler( modname ) ) ;

    BESDEBUG( modname, modname << " handles dap services" << endl ) ;
    BESDapService::handle_dap_service( modname ) ;

    BESDEBUG( modname, "    adding " << NSIDC_CATALOG << " catalog" << endl ) ;
    if( !BESCatalogList::TheCatalogList()->ref_catalog( NSIDC_CATALOG ) )
    {
        BESCatalogList::TheCatalogList()->
                add_catalog(new BESCatalogDirectory( NSIDC_CATALOG ) ) ;
    }
    else
    {
        BESDEBUG( modname, "    catalog already exists, skipping" << endl ) ;
    }

    BESDEBUG( modname, "    adding Catalog Container Storage" << endl ) ;
    if( !BESContainerStorageList::TheList()->ref_persistence( NSIDC_CATALOG ) )
    {
        BESContainerStorageList::TheList()->
                add_persistence( new BESContainerStorageCatalog( NSIDC_CATALOG ) ) ;
    }
    else
    {
        BESDEBUG( modname, "    storage already exists, skipping" << endl ) ;
    }

    // INIT_END
    BESDEBUG( modname, "    adding NSIDC debug context" << endl ) ;
    BESDebug::Register( modname ) ;

    BESDEBUG( modname, "Done Initializing NSIDC Module "
		       << modname << endl ) ;
}

void
NSIDCModule::terminate( const string &modname )
{
    BESDEBUG( modname, "Cleaning NSIDC module " << modname << endl ) ;

    BESDEBUG( modname, "    removing " << modname
		       << " request handler"
    << endl ) ;
    BESRequestHandler *rh = BESRequestHandlerList::TheList()->remove_handler( modname ) ;
    if( rh ) delete rh ;

    // If new commands are needed, then let's declare this once here. If
    // not, then you can remove this line.
    string cmd_name ;

    BESDEBUG( modname, "    removing lat/lon arrays " << endl ) ;
    if (latitudesNorth) delete latitudesNorth;
    if (longitudesNorth) delete longitudesNorth;
    if (latitudesSouth) delete latitudesSouth;
    if (longitudesSouth) delete longitudesSouth;

    // TERM_END
    BESDEBUG( modname, "Done Cleaning NSIDC module "
		       << modname << endl ) ;
}

extern "C"
{
    BESAbstractModule *maker()
    {
	return new NSIDCModule ;
    }
}

void
NSIDCModule::dump( ostream &strm ) const
{
    strm << BESIndent::LMarg << "NSIDCModule::dump - ("
			     << (void *)this << ")" << endl ;

}

