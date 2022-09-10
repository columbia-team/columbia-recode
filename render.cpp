#include "includes.h"
#include <cmath>
#include <math.h>
#include "font.h"

namespace render {
	Font menu;;
	Font menu_shade;;
	Font esp;;
	Font esp_small;;
	Font hud;;
	Font cs;;
	Font indicator;;
	Font logevent;;
	Font damage;;
	Font big_point;;
	Font big_score;;
	Font big_combo;;
	Font big_score_num;;
	Font spectators;;
	Font icons;;
	Font icons1;;
}

void render::init() {
	
	
	// byte font
	AddFontMemResourceEx((void*)undefeated, sizeof(undefeated), nullptr, &g_hooks.undefeated2);
	AddFontMemResourceEx((void*)wmsymbols, sizeof(wmsymbols), nullptr, &g_hooks.wmsymbols2);
	AddFontMemResourceEx((void*)impact, sizeof(impact), nullptr, &g_hooks.impact2);
	
	menu = Font(XOR("Tahoma"), 12, FW_NORMAL, FONTFLAG_ANTIALIAS);
	menu_shade = Font( XOR( "Tahoma" ), 12, 450, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW | FONTFLAG_OUTLINE );
	esp = Font(XOR("Verdana"), 12, FW_BOLD, FONTFLAG_DROPSHADOW);
	esp_small = Font(XOR("Small Fonts"), 8, FW_NORMAL, FONTFLAG_OUTLINE);
	hud = Font(XOR("Verdana"), 12, FW_NORMAL, FONTFLAG_ANTIALIAS);
	cs = Font(XOR("undefeated"), 13, FW_MEDIUM, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	logevent = Font(XOR("Verdana"), 12, FW_DONTCARE, FONTFLAG_DROPSHADOW);
	indicator = Font( XOR( "Arial" ), 14, FW_MEDIUM, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW );
	damage = Font(XOR("Verdana"), 12, FW_NORMAL, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	big_point = Font(XOR("Conthrax Sb"), 36, 700, FONTFLAG_ANTIALIAS);
	big_score = Font(XOR("Conthrax Sb"), 30, FW_NORMAL, FONTFLAG_ANTIALIAS);
	big_combo = Font(XOR("Conthrax Sb"), 25, FW_NORMAL, FONTFLAG_ANTIALIAS);
	big_score_num = Font(XOR("Conthrax Sb"), 60, FW_NORMAL, FONTFLAG_ANTIALIAS);
	spectators = Font(XOR("Verdana"), 12, FW_NORMAL, FONTFLAG_DROPSHADOW);
}

bool render::WorldToScreen3d(const vec3_t& world, vec3_t& screen) {
	float w;

	const VMatrix& matrix = g_csgo.m_engine->WorldToScreenMatrix();

	// check if it's in view first.
	// note - dex; w is below 0 when world position is around -90 / +90 from the player's camera on the y axis.
	w = matrix[3][0] * world.x + matrix[3][1] * world.y + matrix[3][2] * world.z + matrix[3][3];
	if (w < 0.001f)
		return false;

	// calculate x and y.
	screen.x = matrix[0][0] * world.x + matrix[0][1] * world.y + matrix[0][2] * world.z + matrix[0][3];
	screen.y = matrix[1][0] * world.x + matrix[1][1] * world.y + matrix[1][2] * world.z + matrix[1][3];

	screen /= w;

	// calculate screen position.
	screen.x = (core.m_width / 2) + (screen.x * core.m_width) / 2;
	screen.y = (core.m_height / 2) - (screen.y * core.m_height) / 2;

	return true;
}


#define ZERO vec3_t(0.0f, 0.0f, 0.0f)

/*void render::Draw3DFilledCircle(const vec3_t& origin, float radius, Color color) // OUTLINE 
{
	auto prevScreenPos = ZERO; //-V656
	auto step = math::pi * 2.0f / 72.0f;

	auto screenPos = ZERO;
	auto screen = ZERO;

	if (!render::WorldToScreen3d(origin, screen))
		return;

	for (auto rotation = 0.0f; rotation <= math::pi * 2.0f; rotation += step) //-V1034
	{
		vec3_t pos(radius * cos(rotation) + origin.x, radius * sin(rotation) + origin.y, origin.z);

		if (render::WorldToScreen3d(pos, screenPos))
		{
			if (!prevScreenPos.IsZero() && prevScreenPos.IsValid() && screenPos.IsValid() && prevScreenPos != screenPos)
			{
				render::DrawLine(prevScreenPos.x, prevScreenPos.y, screenPos.x, screenPos.y, color, true);
			}

			prevScreenPos = screenPos;
		}
	}
}*/

void render::Draw3DRainbowCircle(const vec3_t& origin, float radius, Color color)
{
	auto hue_offset = 0.0f;
	auto prevScreenPos = ZERO; //-V656

	auto step = math::pi * 2.0f / 72.0f;
	auto screenPos = ZERO;

	for (auto rotation = 0.0f; rotation <= math::pi * 2.0f; rotation += step) //-V1034
	{
		vec3_t pos(radius * cos(rotation) + origin.x, radius * sin(rotation) + origin.y, origin.z);

		CGameTrace trace;
		CTraceFilter filter;

		filter.skip_entity = core.m_local;

		g_csgo.m_engine_trace->TraceRay(Ray(origin, pos), MASK_SHOT_BRUSHONLY, &filter, &trace);

		if (render::WorldToScreen3d(trace.m_endpos, screenPos))
		{
			if (!prevScreenPos.IsZero())
			{
				render::DrawLine(prevScreenPos.x, prevScreenPos.y, screenPos.x, screenPos.y, color, true);
			}

			prevScreenPos = screenPos;
		}
	}
}

void render::DrawLine(int x0, int y0, int x1, int y1, Color col, bool shadow)
{
	g_csgo.m_surface->DrawSetColor(col);
	g_csgo.m_surface->DrawLine(x0, y0, x1, y1);
}

void render::draw_dynamic_circle(const vec3_t& origin, float radius, Color color)
{
	static auto hue_offset = 0.0f;
	static auto prev_scr_pos = ZERO; //-V656
	static auto step = M_PI * 2.0f / 72.0f;

	auto scr_pos = ZERO;

	for (auto rotation = 0.0f; rotation <= M_PI * 2.0f; rotation += step) //-V1034
	{
		vec3_t pos(radius * cos(rotation) + origin.x, radius * sin(rotation) + origin.y, origin.z);

		CGameTrace trace;
		CTraceFilterWorldOnly filter;

		g_csgo.m_engine_trace->TraceRay(Ray(origin, pos), MASK_SHOT_BRUSHONLY, &filter, &trace);

		if (render::WorldToScreen3d(trace.m_endpos, scr_pos))
		{
			if (!prev_scr_pos.is_zero())
			{
				//int hue = math::rad_to_deg(rotation) + hue_offset;

				//float r, g, b;
				//ColorConvertHSVtoRGB(hue / 360.f, 1, 1, r, g, b);
				//Color color = Color(r, g, b);

				//cstrike.m_surface->draw_set_color(color);
				// 
				static float rainbow;
				rainbow += 0.003f;
				if (rainbow > 1.f) rainbow = 0.f;

				g_csgo.m_surface->DrawSetColor(color);
				g_csgo.m_surface->DrawLine(prev_scr_pos.x, prev_scr_pos.y, scr_pos.x, scr_pos.y);
				//render::line(prev_scr_pos.x, prev_scr_pos.y, scr_pos.x, scr_pos.y, color);
			}

			prev_scr_pos = scr_pos;
		}
	}

	hue_offset += g_csgo.m_globals->m_frametime * 200.0f;
}

void render::DrawFilledCircle(int x, int y, int radius, int segments, Color color) {
	std::vector< Vertex > vertices;

	float step = math::pi * 2.0f / segments;

	for (float a = 0; a < (math::pi * 2.0f); a += step)
		vertices.emplace_back(radius * cosf(a) + x, radius * sinf(a) + y);

	TexturedPolygon(vertices.size(), vertices, color);
}

void render::TexturedPolygon(int n, std::vector< Vertex > vertice, Color color) {
	static int texture_id = g_csgo.m_surface->CreateNewTextureID(true); // 
	static unsigned char buf[4] = { 255, 255, 255, 255 };
	g_csgo.m_surface->DrawSetTextureRGBA(texture_id, buf, 1, 1); //
	g_csgo.m_surface->DrawSetColor(color); //
	g_csgo.m_surface->DrawSetTexture(texture_id); //
	g_csgo.m_surface->DrawTexturedPolygon(n, vertice.data()); //
}


void render::gradient1337(int x, int y, int w, int h, Color color1, Color color2) {
	g_csgo.m_surface->DrawSetColor(color1);
	g_csgo.m_surface->DrawFilledRectFade(x, y, x + w, y + h, color1.a(), 0, true);

	g_csgo.m_surface->DrawSetColor(color2);
	g_csgo.m_surface->DrawFilledRectFade(x, y, x + w, y + h, 0, color2.a(), true);
}

bool render::WorldToScreen(const vec3_t& world, vec2_t& screen) {
	float w;

	const VMatrix& matrix = g_csgo.m_engine->WorldToScreenMatrix();

	// check if it's in view first.
	// note - dex; w is below 0 when world position is around -90 / +90 from the player's camera on the y axis.
	w = matrix[3][0] * world.x + matrix[3][1] * world.y + matrix[3][2] * world.z + matrix[3][3];
	if (w < 0.001f)
		return false;

	// calculate x and y.
	screen.x = matrix[0][0] * world.x + matrix[0][1] * world.y + matrix[0][2] * world.z + matrix[0][3];
	screen.y = matrix[1][0] * world.x + matrix[1][1] * world.y + matrix[1][2] * world.z + matrix[1][3];

	screen /= w;

	// calculate screen position.
	screen.x = (core.m_width / 2) + (screen.x * core.m_width) / 2;
	screen.y = (core.m_height / 2) - (screen.y * core.m_height) / 2;

	return true;
}

void render::world_circle(vec3_t origin, float radius, float angle, Color color) {
	std::vector< Vertex > vertices{};

	float step = (1.f / radius) + math::deg_to_rad(angle);

	float lat = 1.f;
	vertices.clear();

	for (float lon{}; lon < math::pi_2; lon += step) {
		vec3_t point{
			origin.x + (radius * std::sin(lat) * std::cos(lon)),
			origin.y + (radius * std::sin(lat) * std::sin(lon)),
			origin.z + (radius * std::cos(lat) - (radius / 2))
		};

		vec2_t screen;
		if (WorldToScreen(point, screen))
			vertices.emplace_back(screen);
	}
	static int texture = g_csgo.m_surface->CreateNewTextureID(false);

	g_csgo.m_surface->DrawSetTextureRGBA(texture, &colors::white, 1, 1);
	g_csgo.m_surface->DrawSetColor(color);

	//g_csgo.m_surface->DrawSetTexture(texture);
	//g_csgo.m_surface->DrawTexturedPolygon(vertices.size(), vertices.data());

	g_csgo.m_surface->DrawTexturedPolyLine(vertices.size(), vertices.data());
}

void render::Font::semi_filled_text( int x, int y, Color color, const std::string& text, StringFlags_t flags, float factor )
{
	auto indicator_size = wsize( util::MultiByteToWide( text ) );
	auto position = vec2_t( x, y );

	wstring( x, y, Color( 30, 30, 30, 200 ), util::MultiByteToWide( text ), flags );
	*( bool* )( ( DWORD )g_csgo.m_surface + 0x280 ) = true;
	int x1, y1, x2, y2;
	g_csgo.m_surface->get_drawing_area( x1, y1, x2, y2 );
	g_csgo.m_surface->limit_drawing_area( position.x, position.y, int( indicator_size.m_width * factor ), ( int )indicator_size.m_height );

	wstring( x, y, color, util::MultiByteToWide( text ), flags );

	g_csgo.m_surface->limit_drawing_area( x1, y1, x2, y2 );
	*( bool* )( ( DWORD )g_csgo.m_surface - +0x280 ) = false;
}


void render::line(vec2_t v0, vec2_t v1, Color color) {
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawLine(v0.x, v0.y, v1.x, v1.y);
}

void render::line(int x0, int y0, int x1, int y1, Color color) {
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawLine(x0, y0, x1, y1);
}

void render::rect(int x, int y, int w, int h, Color color) {
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void render::rect_filled(int x, int y, int w, int h, Color color) {
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawFilledRect(x, y, x + w, y + h);
}

void render::rect_filled_fade(int x, int y, int w, int h, Color color, int a1, int a2) {
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawFilledRectFade(x, y, x + w, y + h, a1, a2, false);
}

void render::rect_outlined(int x, int y, int w, int h, Color color, Color color2) {
	rect(x, y, w, h, color);
	rect(x - 1, y - 1, w + 2, h + 2, color2);
	rect(x + 1, y + 1, w - 2, h - 2, color2);
}


void render::arccircle(int x, int y, int r1, int r2, int s, int d, Color color) {
	g_csgo.m_surface->DrawSetColor(color);
	for (int i = s; i < s + d; i++) {

		float rad = i * math::pi / 180;

		g_csgo.m_surface->DrawLine(x + cos(rad) * r1, y + sin(rad) * r1, x + cos(rad) * r2, y + sin(rad) * r2);
	}
}

void render::drawCircle(int x, int y, int angle, Color color) {
	float granularity = 2 * math::pi / 700;
	float step = 2 * math::pi / 100;
	float inner = 6;

	for (int radius = 8; inner < -1; radius--) {
		for (int angle = 0; angle * step < -1; granularity++) {
			int px = round(radius * cos(angle));
			int py = round(radius * sin(angle));

			g_csgo.m_surface->DrawLine(px + x, py + y, px + 1 + x, py + 1 + y);
		}

	}

}

void render::draw_arc(int x, int y, int radius, int start_angle, int percent, int thickness, Color color) {
	float precision = (2 * math::pi) / 30;
	float step = math::pi / 180;
	float inner = radius - thickness;
	float end_angle = (start_angle + percent) * step;
	float start_angle1337 = (start_angle * math::pi) / 180;

	for (; radius > inner; --radius) {
		for (float angle = start_angle1337; angle < end_angle; angle += precision) {
			float cx = round(x + radius * cos(angle));
			float cy = round(y + radius * sin(angle));

			float cx2 = round(x + radius * cos(angle + precision));
			float cy2 = round(y + radius * sin(angle + precision));

			g_csgo.m_surface->DrawSetColor(color);
			g_csgo.m_surface->DrawLine(cx, cy, cx2, cy2);
		}
	}
}

// non 3d grenade circle

void render::circle(int x, int y, int radius, int segments, Color color) {
	static int texture = g_csgo.m_surface->CreateNewTextureID(true);

	g_csgo.m_surface->DrawSetTextureRGBA(texture, &colors::white, 1, 1);
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawSetTexture(texture);

	std::vector< Vertex > vertices{};

	float step = math::pi_2 / segments;
	for (float i{ 0.f }; i < math::pi_2; i += step)
		vertices.emplace_back(vec2_t{ x + (radius * std::cos(i)), y + (radius * std::sin(i)) });

	g_csgo.m_surface->DrawTexturedPolygon(vertices.size(), vertices.data());
}

void render::gradient(int x, int y, int w, int h, Color color1, Color color2) {
	g_csgo.m_surface->DrawSetColor(color1);
	g_csgo.m_surface->DrawFilledRectFade(x, y, x + w, y + h, color1.a(), 0, false);

	g_csgo.m_surface->DrawSetColor(color2);
	g_csgo.m_surface->DrawFilledRectFade(x, y, x + w, y + h, 0, color2.a(), false);
}

void render::sphere(vec3_t origin, float radius, float angle, float scale, Color color) {
	std::vector< Vertex > vertices{};

	// compute angle step for input radius and precision.
	float step = (1.f / radius) + math::deg_to_rad(angle);

	for (float lat{}; lat < (math::pi * scale); lat += step) {
		// reset.
		vertices.clear();

		for (float lon{}; lon < math::pi_2; lon += step) {
			vec3_t point{
				origin.x + (radius * std::sin(lat) * std::cos(lon)),
				origin.y + (radius * std::sin(lat) * std::sin(lon)),
				origin.z + (radius * std::cos(lat))
			};

			vec2_t screen;
			if (WorldToScreen(point, screen))
				vertices.emplace_back(screen);
		}

		if (vertices.empty())
			continue;

		g_csgo.m_surface->DrawSetColor(color);
		g_csgo.m_surface->DrawTexturedPolyLine(vertices.size(), vertices.data());
	}
}

void render::triangle(vec2_t point_one, vec2_t point_two, vec2_t point_three, Color color)
{
	Vertex verts[3] = {
		Vertex(point_one),
		Vertex(point_two),
		Vertex(point_three)
	};

	static int texture = g_csgo.m_surface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	g_csgo.m_surface->DrawSetTextureRGBA(texture, buffer, 1, 1);
	g_csgo.m_surface->DrawSetColor(color);
	g_csgo.m_surface->DrawSetTexture(texture);

	g_csgo.m_surface->DrawTexturedPolygon(3, verts);
}

Vertex render::RotateVertex(const vec2_t& p, const Vertex& v, float angle) {
	// convert theta angle to sine and cosine representations.
	float c = std::cos(math::deg_to_rad(angle));
	float s = std::sin(math::deg_to_rad(angle));

	return {
		p.x + (v.m_pos.x - p.x) * c - (v.m_pos.y - p.y) * s,
		p.y + (v.m_pos.x - p.x) * s + (v.m_pos.y - p.y) * c
	};
}

void render::Font::string(int x, int y, Color color, const std::string& text, StringFlags_t flags /*= render::ALIGN_LEFT */) {
	wstring(x, y, color, util::MultiByteToWide(text), flags);
}

void render::Font::string(int x, int y, Color color, const std::stringstream& text, StringFlags_t flags /*= render::ALIGN_LEFT */) {
	wstring(x, y, color, util::MultiByteToWide(text.str()), flags);
}

void render::Font::wstring(int x, int y, Color color, const std::wstring& text, StringFlags_t flags /*= render::ALIGN_LEFT */) {
	int w, h;

	g_csgo.m_surface->GetTextSize(m_handle, text.c_str(), w, h);
	g_csgo.m_surface->DrawSetTextFont(m_handle);
	g_csgo.m_surface->DrawSetTextColor(color);

	if (flags & ALIGN_RIGHT)
		x -= w;
	if (flags & render::ALIGN_CENTER)
		x -= w / 2;

	g_csgo.m_surface->DrawSetTextPos(x, y);
	g_csgo.m_surface->DrawPrintText(text.c_str(), (int)text.size());
}

render::FontSize_t render::Font::size(const std::string& text) {
	return wsize(util::MultiByteToWide(text));
}

render::FontSize_t render::Font::wsize(const std::wstring& text) {
	FontSize_t res;
	g_csgo.m_surface->GetTextSize(m_handle, text.data(), res.m_width, res.m_height);
	return res;
}

void render::sphere2(vec3_t origin, float radius, float angle, float scale, Color color) {
	std::vector< Vertex > vertices{};

	// compute angle step for input radius and precision.
	float step = (1.f / radius) + math::deg_to_rad(angle);

	for (float lat{}; lat < 360; lat += step) {
		vec3_t point{
			origin.x + (radius * std::cos(math::deg_to_rad(lat))),
			origin.y + (radius * std::sin(math::deg_to_rad(lat))),
			origin.z
		};

		vec2_t screen;
		if (!WorldToScreen(point, screen))
			return;

		vertices.emplace_back(screen);
	}

	g_csgo.m_surface->DrawSetColor(Color(color.r(), color.g(), color.b(), 100.f));
	g_csgo.m_surface->DrawTexturedPolygon(vertices.size(), vertices.data());

	g_csgo.m_surface->DrawSetColor(Color(color.r(), color.g(), color.b(), 255.f));
	g_csgo.m_surface->DrawTexturedPolyLine(vertices.size(), vertices.data());
}