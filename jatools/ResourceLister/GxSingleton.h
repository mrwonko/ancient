// #############################################################
// Runs on: PLATFORM_WIN32, PLATFORM_LINUX, PLATFORM_APPLE
// A simple and generic way to implement a Singleton class.
// #############################################################

#ifndef GXSINGLETON_H
#define GXSINGLETON_H

// Includes and forwarddeclarations
// #############################################################
// -- C Standard Library
#include <assert.h>

namespace GX {
    template <typename T>
	class Singleton
    {
    protected:
        static T* ms_Singleton;

    public:
        Singleton(void)
        {
            assert(!ms_Singleton);
#if defined(_MSC_VER) && _MSC_VER < 1200
            int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
            ms_Singleton = (T*)((int)this + offset);
#else
			ms_Singleton = static_cast< T* >(this);
#endif
        }
        ~Singleton(void)
        {
			// assert (ms_Singleton);
			ms_Singleton = 0;
		}
        static T& GetSingleton(void)
		{
			assert( ms_Singleton );
			return ( *ms_Singleton );
		}
        static T* GetSingletonPtr(void)
		{
			return ms_Singleton;
		}
    };
}
#endif
