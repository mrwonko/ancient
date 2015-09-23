// #############################################################
// Runs on: PLATFORM_WIN32, PLATFORM_LINUX, PLATFORM_APPLE
// A simple way to implement a Singleton class.
// #############################################################

#ifndef GXSINGLETON_H_
#define GXSINGLETON_H_

#include "assert.h"

#if  COMPILER ==  COMPILER_MSVC
// Turn of some nagging warnings caused by this implementation
#   pragma warning (disable : 4311)
#   pragma warning (disable : 4312)
#endif

namespace GX {
    //! Template class for creating single-instance global classes.
    template <typename T> class Singleton
    {
    protected:

        static T* ms_Singleton;

    public:
        Singleton( void )
        {
            assert( !ms_Singleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200
            int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
            ms_Singleton = (T*)((int)this + offset);
#else
	    ms_Singleton = static_cast< T* >( this );
#endif
        }
        ~Singleton( void )
            {  assert( ms_Singleton );  ms_Singleton = 0;  }
        static T& getSingleton( void )
		{	assert( ms_Singleton );  return ( *ms_Singleton ); }
        static T* getSingletonPtr( void )
		{ return ms_Singleton; }
    };
}
#endif
