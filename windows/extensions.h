#pragma once
#ifndef _EXTENSIONS_H
#define _EXTENSIONS_H

#include <wchar.h>

/**
*
* Proxy structure 
*
**/
typedef struct ProxyData {

    int port_num;
    char *address;

} ProxyData;



ProxyData get_ie_proxy();


#endif // _EXTENSIONS_H