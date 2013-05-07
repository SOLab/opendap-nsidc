// NSIDCRequestHandler.h

#ifndef I_NSIDCRequestHandler_H
#define I_NSIDCRequestHandler_H

#include "BESRequestHandler.h"

class NSIDCRequestHandler : public BESRequestHandler {
public:
			NSIDCRequestHandler( const string &name ) ;
    virtual		~NSIDCRequestHandler( void ) ;

    virtual void	dump( ostream &strm ) const ;

    static bool		binary_ssmi_nsidc_build_das( BESDataHandlerInterface &dhi ) ;
    static bool		binary_ssmi_nsidc_build_dds( BESDataHandlerInterface &dhi ) ;
    static bool		binary_ssmi_nsidc_build_data( BESDataHandlerInterface &dhi ) ;
    static bool		binary_ssmi_nsidc_build_vers( BESDataHandlerInterface &dhi ) ;
    static bool		binary_ssmi_nsidc_build_help( BESDataHandlerInterface &dhi ) ;
};

#endif // NSIDCRequestHandler.h

