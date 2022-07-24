#include "includes.h"
#include <thread>
#include <chrono>
#include <tchar.h>
#include <algorithm>
#include <iterator>
#include <consoleapi.h>

int __stdcall DllMain( HMODULE self, ulong_t reason, void* reserved ) {
    if ( reason == DLL_PROCESS_ATTACH ) {
       // m_console.setup( "csgo" );

                HANDLE thread = CreateThread( nullptr, 0, Core::init, nullptr, 0, nullptr );
                if ( !thread )
                    return 0;
                return 1;
            }
    return 0;
}
