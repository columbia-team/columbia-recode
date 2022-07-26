#include "new_menu.h"
#include "m_window/window.hpp"
#include "m_checkbox/checkbox.hpp"
#include "new_config.h"
#include "m_slider/slider.hpp"
#include "m_combo/combo.hpp"
/* gui externals related */
Gui::Details Gui::m_Details;
Gui::Input Gui::m_Input;
Gui::Control Gui::m_Control;
Gui::ExternalRendering Gui::m_External;
Gui::Config Gui::m_Cfg;

/* gui func related */
bool Gui::Details::GetMenuState( ) {
	return m_Show;
}
void Gui::Details::SetMenuState( const bool m_State ) {
	m_Show = m_State;
}
vec2_t Gui::Input::GetMousePos( ) {
	return m_MousePos;
}
void Gui::Input::SetMousePos( const vec2_t m_Pos ) {
	m_MousePos = vec2_t{ m_Pos.x, m_Pos.y };
}
void Gui::Input::PollInput( ) {
	for ( size_t i{ 0 }; i < 256; i++ ) {
		Helpers.m_PrevKeyState[ i ] = Helpers.m_KeyState[ i ];
		Helpers.m_KeyState[ i ] = GetAsyncKeyState( i );
	}
}
bool Gui::Input::KeyPressed( const uintptr_t m_Key ) {
	return Helpers.m_KeyState[ m_Key ] && !Helpers.m_PrevKeyState[ m_Key ];
}
bool Gui::Input::MousePointer( const vec2_t m_Pos, const vec2_t m_Size ) {
	std::pair<bool, bool> m_ShouldReturn{
		GetMousePos( ).x > m_Pos.x && GetMousePos( ).y > m_Pos.y,
		GetMousePos( ).x < m_Pos.x + m_Size.x && GetMousePos( ).y < m_Pos.y + m_Size.y
	};

	return m_ShouldReturn.first && m_ShouldReturn.second;
}
void Gui::Input::SetMouseWheel( const float m_Wheel ) {
	m_MouseWheel = m_Wheel;
}
float Gui::Input::GetMouseWheel( ) {
	return m_MouseWheel;
}
int Gui::Control::GetIndex( ) {
	return m_Index;
}
void Gui::Control::SetIndex( const uintptr_t m_Last ) {
	m_Index = m_Last;
}
bool Gui::Control::IsPossible( ) {
	return Gui::m_Control.m_Opened
		[ Gui::m_Control.ControlType::COMBO ] == -1 &&
		Gui::m_Control.m_Opened
		[ Gui::m_Control.ControlType::MULTICOMBO ] == -1 &&
		Gui::m_Control.m_Opened
		[ Gui::m_Control.ControlType::BIND ] == -1;
}

/* drawing related */
void GradientHorizontalPrototype2( vec2_t a, vec2_t b, Color c_a, Color c_b )
{
	b += a;

	VerticeT verts[ 4 ] = {
		{a.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_a.r( ), c_a.g( ), c_a.b( ), c_a.a( ) )},
		{b.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_b.r( ), c_b.g( ), c_b.b( ), c_b.a( ) )},
		{a.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_a.r( ), c_a.g( ), c_a.b( ), c_a.a( ) )},
		{b.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_b.r( ), c_b.g( ), c_b.b( ), c_b.a( ) )}
	};

	DrawList.dev->SetTexture( 0, nullptr );
	DrawList.dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &verts, 20 );
}
void GradientVerticalPrototype2( vec2_t a, vec2_t b, Color c_a, Color c_b )
{
	b += a;

	VerticeT verts[ 4 ] = {
		{a.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_a.r( ), c_a.g( ), c_a.b( ), c_a.a( ) )},
		{b.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_a.r( ), c_a.g( ), c_a.b( ), c_a.a( ) )},
		{a.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_b.r( ), c_b.g( ), c_b.b( ), c_b.a( ) )},
		{b.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c_b.r( ), c_b.g( ), c_b.b( ), c_b.a( ) )}
	};

	DrawList.dev->SetTexture( 0, nullptr );
	DrawList.dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &verts, 20 );
}
void GradientVertical2( float x, float y, float w, float h, Color c_a, Color c_b )
{
	GradientVerticalPrototype2( { x, y }, { w, h }, c_a, c_b );
}
void Gui::ExternalRendering::GradientHorizontal2( float x, float y, float w, float h, Color c_a, Color c_b )
{
	GradientHorizontalPrototype2( { x, y }, { w, h }, c_a, c_b );
}
void FilledPrototype2( vec2_t a, vec2_t b, Color c )
{
	b += a;

	VerticeT verts[ 4 ] = {
		{a.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{b.x, a.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{a.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{b.x, b.y, 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )}
	};

	DrawList.dev->SetTexture( 0, nullptr );
	DrawList.dev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, &verts, 20 );
}
void Gui::ExternalRendering::FilledRect2( float x, float y, float w, float h, Color c )
{
	FilledPrototype2( { x, y }, { w, h }, c );
}
void RectPrototype2( vec2_t a, vec2_t b, Color c )
{
	b += a;

	b.x -= 1;
	b.y -= 1;

	VerticeT verts[ 5 ] = {
		{float( a.x ), float( a.y ), 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{float( b.x ), float( a.y ), 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{float( b.x ), float( b.y ), 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{float( a.x ), float( b.y ), 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )},
		{float( a.x ), float( a.y ), 0.01f, 0.01f, D3DCOLOR_RGBA( c.r( ), c.g( ), c.b( ), c.a( ) )}
	};

	DrawList.dev->SetTexture( 0, nullptr );
	DrawList.dev->DrawPrimitiveUP( D3DPT_LINESTRIP, 4, &verts, 20 );
}
void Rect2( float x, float y, float w, float h, Color c )
{
	RectPrototype2( { x, y }, { w + 1, h + 1 }, c );
}

/* install */
void Gui::ExternalRendering::Install( ) {
	for ( size_t i{ 0 }; i < RectDraw.size( ); i++ )
		DrawList.FilledRect( RectDraw[ i ].posX, RectDraw[ i ].posY, RectDraw[ i ].m_Width, RectDraw[ i ].m_Height, RectDraw[ i ].m_color_t );

	for ( size_t i{ 0 }; i < RectDraw2.size( ); i++ )
		FilledRect2( RectDraw2[ i ].posX, RectDraw2[ i ].posY, RectDraw2[ i ].m_Width, RectDraw2[ i ].m_Height, RectDraw2[ i ].m_color_t );

	for ( size_t i{ 0 }; i < GradientHDraw.size( ); i++ )
		DrawList.GradientHorizontal( GradientHDraw[ i ].posX, GradientHDraw[ i ].posY, GradientHDraw[ i ].m_Width, GradientHDraw[ i ].m_Height, GradientHDraw[ i ].m_color_t, GradientHDraw[ i ].m_color_tNext );

	for ( size_t i{ 0 }; i < GradientVDraw.size( ); i++ )
		DrawList.GradientVertical( GradientVDraw[ i ].posX, GradientVDraw[ i ].posY, GradientVDraw[ i ].m_Width, GradientVDraw[ i ].m_Height, GradientVDraw[ i ].m_color_t, GradientVDraw[ i ].m_color_t );

	for ( size_t i{ 0 }; i < GradientHDraw2.size( ); i++ )
		GradientHorizontal2( GradientHDraw2[ i ].posX, GradientHDraw2[ i ].posY, GradientHDraw2[ i ].m_Width, GradientHDraw2[ i ].m_Height, GradientHDraw2[ i ].m_color_t, GradientHDraw2[ i ].m_color_tNext );

	for ( size_t i{ 0 }; i < GradientVDraw2.size( ); i++ )
		GradientVertical2( GradientVDraw2[ i ].posX, GradientVDraw2[ i ].posY, GradientVDraw2[ i ].m_Width, GradientVDraw2[ i ].m_Height, GradientVDraw2[ i ].m_color_t, GradientVDraw2[ i ].m_color_t );

	for ( size_t i{ 0 }; i < OutlineDraw.size( ); i++ )
		DrawList.Rect( OutlineDraw[ i ].posX, OutlineDraw[ i ].posY, OutlineDraw[ i ].m_Width, OutlineDraw[ i ].m_Height, OutlineDraw[ i ].m_color_t );

	for ( size_t i{ 0 }; i < OutlineDraw2.size( ); i++ )
		Rect2( OutlineDraw2[ i ].posX, OutlineDraw2[ i ].posY, OutlineDraw2[ i ].m_Width, OutlineDraw2[ i ].m_Height, OutlineDraw2[ i ].m_color_t );

	for ( size_t i{ 0 }; i < TextDraw.size( ); i++ )
		DrawList.DrawString( { TextDraw[ i ].posX, TextDraw[ i ].posY }, TextDraw[ i ].m_Text, TextDraw[ i ].m_color_t, Fonts::Main, font_flags::drop_shadow );

	/* clear */
	RectDraw.clear( );
	OutlineDraw.clear( );
	GradientHDraw.clear( );
	GradientVDraw.clear( );
	TextDraw.clear( );

	/* clear */
	RectDraw2.clear( );
	OutlineDraw2.clear( );
	GradientHDraw2.clear( );
	GradientVDraw2.clear( );
}

std::vector<std::string> tabs = { "Ragebot", "Anti-Aim", "Visuals", "Settings", "Skins" };

std::vector < std::string> selection = { "distance", "crosshair", "damage", "health", "lag", "height" };
std::vector < std::string> mode = { "stand", "move", "air" };
std::vector < std::string> zoom_mode = { "off", "always", "hitchance fail" };


std::vector <std::string> ptch = { XOR( "off" ), XOR( "down" ), XOR( "up" ), XOR( "random" ), XOR( "ideal" ) };
std::vector <std::string> yaw = { XOR( "off" ), XOR( "direction" ), XOR("jitter"), XOR("rotate"), XOR("random")};
std::vector <std::string> drr = { XOR( "auto" ), XOR( "backwards" ), XOR( "left" ), XOR( "right" ), XOR( "custom" ) };
std::vector <std::string> baseangle = { XOR( "off" ), XOR( "static" ), XOR( "away crosshair" ), XOR( "away distance" ) };
std::vector <std::string> fakebody = { XOR( "off" ), XOR( "left" ), XOR( "right" ), XOR( "opposite" ), XOR( "z" ), XOR( "twist" ), XOR( "twist z" ), XOR( "fick random" ) };
std::vector <std::string> ptch_move = { XOR( "off" ), XOR( "direction" ), XOR( "jitter" ), XOR( "rotate" ), XOR( "random" ) };
std::vector <std::string> yaw_move = { XOR( "off" ), XOR( "down" ), XOR( "up" ), XOR( "random" ), XOR( "ideal" ) };

vec2_t window_position = vec2_t( 0, 0 );

void Gui::Details::Install( ) {
	/* pool */
	m_Input.PollInput( );

	/* menu open related */
	if ( m_Input.KeyPressed( VK_INSERT ) ) {
		SetMenuState( !GetMenuState( ) );
	}

	if ( !GetMenuState( ) )
		return;

	static bool save = false;
	static bool load = false;

	static bool CfgInitLoad = true;
	static bool CfgInitSave = true;

	m_Control.SetIndex( 0 );
	m_Control.m_Opened[ m_Control.ControlType::COMBO ] = -1;
	m_Control.m_Opened[ m_Control.ControlType::MULTICOMBO ] = -1;
	m_Control.m_Opened[ m_Control.ControlType::BIND ] = -1;

	std::string out = tfm::format( XorStr( "frenchook" ) );
	auto m_Window = new Window( out, &window_position, { 475, 355 }, tabs, &m_Index ); {
		auto rage_main = new Groupbox( "main", 0, 19, 45, 208, 125, 0 ); {
			m_Window->AddGroup( rage_main );
			rage_main->AddElement( new checkbox_new( "enable aimbot", &g_menu.main.aimbot.enable.get( ) ) );
			rage_main->AddElement( new checkbox_new( "silent", &g_menu.main.aimbot.silent.get( ) ) );
			rage_main->AddElement( new Combo( "target selection", &g_menu.main.aimbot.selection.get( ), selection ) );
			rage_main->AddElement( new checkbox_new( "knife bot", &g_menu.main.aimbot.knifebot.get( ) ) );
			rage_main->AddElement( new checkbox_new( "zeus bot", &g_menu.main.aimbot.zeusbot.get( ) ) );
			rage_main->AddElement( new checkbox_new( "aimbot debuggin", &g_menu.main.aimbot.debugaim.get( ) ) );
			
			rage_main->AddElement( new checkbox_new( "save", &save ) );
			if ( save ) {
				g_Config->Save( );
			}
			rage_main->AddElement( new checkbox_new( "load", &load ) );
			if ( load ) {
				g_Config->Load( );
			}
			rage_main->InitScroll( );
		} delete rage_main;
		auto rage_accuracy = new Groupbox( "accuracy", 1, 250, 45, 208, 270, 0 ); {
			m_Window->AddGroup( rage_accuracy );
			rage_accuracy->AddElement( new checkbox_new( "remove recoil", &g_menu.main.aimbot.norecoil.get( ) ) );
			rage_accuracy->AddElement( new checkbox_new( "fakelag fix", &g_menu.main.aimbot.lagfix.get( ) ) );
			rage_accuracy->AddElement( new checkbox_new( "ignore limbs", &g_menu.main.aimbot.ignor_limbs.get( ) ) );

			rage_accuracy->AddElement( new checkbox_new( "resolver", &g_menu.main.aimbot.correct.get( ) ) );
			rage_accuracy->AddElement( new checkbox_new( "baim conditions", &g_menu.main.aimbot.baim1_cond.get( ) ) );
			rage_accuracy->AddElement( new checkbox_new( "only baim conditions", &g_menu.main.aimbot.only_baim_cond.get( ) ) );
			rage_accuracy->AddElement( new checkbox_new( "only head when resolved", &g_menu.main.aimbot.head_condition.get( ) ) );

			rage_accuracy->AddElement( new slider_new( "point scale", &g_menu.main.aimbot.scale.get( ), 0, 100, "%" ) );
			rage_accuracy->AddElement( new slider_new( "body scale", &g_menu.main.aimbot.body_scale.get( ), 0, 100, "%" ) );

			rage_accuracy->AddElement( new Combo( "auto scope", &g_menu.main.aimbot.zoom.get( ), zoom_mode ) );
			rage_accuracy->InitScroll( );
		} delete rage_accuracy;
		auto rage_selection = new Groupbox( "config", 2, 19, 199, 208, 115, 0 ); {
			m_Window->AddGroup( rage_selection );
			rage_selection->AddElement( new checkbox_new( "hitchance", &g_menu.main.aimbot.hitchance.get( ) ) );
			if ( g_menu.main.aimbot.hitchance.get( ) ) {
				rage_selection->AddElement( new slider_new( "hitchance amount", &g_menu.main.aimbot.hitchance_amount.get( ), 0, 100, "%" ) );
			}
			rage_selection->AddElement( new slider_new( "minimal damage", &g_menu.main.aimbot.minimal_damage.get( ), 0, 100, "%" ) );
			rage_selection->AddElement( new checkbox_new( "penetration", &g_menu.main.aimbot.penetrate.get( ) ) );
			if ( g_menu.main.aimbot.penetrate.get( ) ) {
				rage_selection->AddElement( new slider_new( "penetrate damage", &g_menu.main.aimbot.penetrate_minimal_damage.get( ), 0, 100, "%" ) );
			}
			rage_selection->InitScroll( );
		} delete rage_selection;
		
		auto anti_aim_main = new Groupbox( "main", 0, 19, 45, 208, 125, 1 ); {
			m_Window->AddGroup( rage_main );
			anti_aim_main->AddElement( new Combo( "antiaim mode", &g_menu.main.antiaim.mode.get( ), mode ) );
			switch ( g_menu.main.antiaim.mode.get( ) ) {
				case 0: {

				} break;
				case 1: {

				} break;
				case 2: {

				} break;
			}
			anti_aim_main->InitScroll( );
		} delete anti_aim_main;
		auto anti_aim_fakilag = new Groupbox( "fakelag", 1, 250, 45, 208, 270, 1 ); {
			m_Window->AddGroup( rage_accuracy );
			
			anti_aim_fakilag->InitScroll( );
		} delete anti_aim_fakilag;
		auto anti_aim_main = new Groupbox( "other", 2, 19, 199, 208, 115, 1 ); {
			m_Window->AddGroup( rage_selection );
			
			anti_aim_main->InitScroll( );
		} delete anti_aim_main;


	} delete m_Window;
	m_External.Install( );
}