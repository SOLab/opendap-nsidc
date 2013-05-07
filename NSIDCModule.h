// NSIDCModule.h

#ifndef I_NSIDCModule_H
#define I_NSIDCModule_H 1

#include "BESAbstractModule.h"

class NSIDCModule : public BESAbstractModule
{
public:
    				NSIDCModule() {}
    virtual		    	~NSIDCModule() {}
    virtual void		initialize( const string &modname ) ;
    virtual void		terminate( const string &modname ) ;

    virtual void		dump( ostream &strm ) const ;
} ;

#endif // I_NSIDCModule_H

