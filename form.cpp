#include "includes.h"

void Form::draw( ) {
	m_open ? m_alpha = 255 : m_alpha = 0;

	// get gui color.
	Color color = g_gui.m_color;
	color.a( ) = m_alpha;

	Color tabs_color = colors::white;
	if ( m_open ) {
		tabs_color.a( ) = 10;
	}
	else if ( !m_open ) {
		tabs_color.a( ) = 0;
	}

	/* main window */ render::rect_filled( m_x, m_y, m_width, m_height, Color( 16, 16, 16, m_alpha ) );
	/* main outline */ render::rect( m_x + 1, m_y + 1, m_width - 2, m_height - 2, Color( 45, 45, 45, m_alpha ) );
	/* elements rect */ render::rect_filled( m_x + 5, m_y + 5, m_width - 10, m_height - 10, Color( 24, 24, 24, m_alpha ) );

	for ( int io = 0; io < m_width / 2 - 5; io++ )
		/* backround */ render::rect( m_x + 5 + ( io * 2 ), m_y + 26, 1, m_height - 33, Color( 20, 20, 20, m_alpha ) );

	/* up bar/name bar */ render::rect_filled( m_x + 5, m_y + 5, m_width - 10, 27, Color( 24, 24, 24, m_alpha ) );
	/* outlines */ render::rect( m_x + 5, m_y + 5, m_width - 10, m_height - 10, Color( 45, 45, 45, m_alpha ) );
	/* outlines */ render::rect( m_x + 6, m_y + 30, m_width - 12, 1, Color( 45, 45, 45, m_alpha ) );
	/* cheat name */ render::menu_shade.string( m_x + 17 + render::menu_shade.size( "colubmia" ).m_width, m_y + 11, color, "columbia", render::ALIGN_RIGHT );

	render::gradient1337( m_x + 155, m_y + 30, m_width - 160, 1.5, Color( 0, 0, 0, 0 ), color );

	// font size.
	size_t font_w = 8;

	// draw tabs if we have any.
	if ( !m_tabs.empty( ) ) {
		// tabs background and border.
		Rect tabs_area = GetTabsRect( );

		for ( size_t i{}; i < m_tabs.size( ); ++i ) {
			const auto& t = m_tabs[ i ];
			render::menu_shade.string( ( tabs_area.x + render::menu_shade.size( "colubmia" ).m_width + 20 ) + font_w, tabs_area.y + 11, t == m_active_tab ? color : tabs_color, t->m_title );
			render::rect_filled( ( tabs_area.x + render::menu_shade.size( "colubmia" ).m_width + 20 ) + font_w, tabs_area.y + 24, render::menu_shade.size( t->m_title ).m_width, 2, t == m_active_tab ? color : tabs_color );
			font_w += render::menu_shade.size( t->m_title ).m_width + 12;
		}

		// this tab has elements.
		if ( !m_active_tab->m_elements.empty( ) ) {
			// elements background and border.
			Rect el = GetElementsRect( );

			render::rect_filled( el.x + 3, el.y, el.w / 2 - 6, el.h, { 25, 25, 25, m_alpha } );
			render::rect_filled( el.x + 3 + el.w / 2, el.y, el.w / 2 - 6, el.h, { 25, 25, 25, m_alpha } );

			render::rect( el.x + 3, el.y, el.w / 2 - 6, el.h, { 45, 45, 45, m_alpha } );
			render::rect( el.x + 3 + el.w / 2, el.y, el.w / 2 - 6, el.h, { 45, 45, 45, m_alpha } );

			render::rect( el.x + 4, el.y + 1, el.w / 2 - 8, el.h - 2, { 0, 0, 0, m_alpha } );
			render::rect( el.x + 4 + el.w / 2, el.y + 1, el.w / 2 - 8, el.h - 2, { 0, 0, 0, m_alpha } );

			std::string date = XOR( __DATE__ );

			// iterate elements to display.
			for ( const auto& e : m_active_tab->m_elements ) {

				// draw the active element last.
				if ( !e || ( m_active_element && e == m_active_element ) )
					continue;

				if ( !e->m_show )
					continue;

				// this element we dont draw.
				if ( !( e->m_flags & ElementFlags::DRAW ) )
					continue;

				e->draw( );
			}

			// we still have to draw one last fucker.
			if ( m_active_element && m_active_element->m_show )
				m_active_element->draw( );
		}
	}
}