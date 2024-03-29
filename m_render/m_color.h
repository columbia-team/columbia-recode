#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct color_t {
	color_t( ) : r( 255 ), g( 255 ), b( 255 ), a( 255 ) { } /* default white */
	color_t( int r, int g, int b, int a = 255 ) : r( r ), g( g ), b( b ), a( a ) { }
	~color_t( ) { }

	D3DCOLOR to_d3d( ) {
		return D3DCOLOR_RGBA( r, g, b, a );
	}

	int r, g, b, a;
};
