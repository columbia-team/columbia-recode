#include "new_config.h"
#include "../includes.h"

void CConfig::Setup( )
{
	//aimbot
	SetupValue( g_menu.main.aimbot.enable.get( ), false, "aimbot_enable" );//
	SetupValue( g_menu.main.aimbot.silent.get( ), false, "silent" );//
	SetupValue( g_menu.main.aimbot.selection.get( ), 0, "selection" );//
	SetupValue( g_menu.main.aimbot.scale.get( ), 50, "sclae" );//
	SetupValue( g_menu.main.aimbot.body_scale.get( ), 60, "bsclae" );//
	SetupValue( g_menu.main.aimbot.minimal_damage.get( ), 0, "min_dmaage" );//
	SetupValue( g_menu.main.aimbot.penetrate.get( ), false, "autowall" );//
	SetupValue( g_menu.main.aimbot.penetrate_minimal_damage.get( ), 0, "pmin_dmaage" );//
	SetupValue( g_menu.main.aimbot.knifebot.get( ), false, "kbot" );//
	SetupValue( g_menu.main.aimbot.zeusbot.get( ), false, "zbot" );//
	SetupValue( g_menu.main.aimbot.debugaim.get( ), false, "debugaim" );//
	SetupValue( g_menu.main.aimbot.zoom.get( ), 0, "zoom_mode" );//
	SetupValue( g_menu.main.aimbot.norecoil.get( ), false, "norecoil" );//
	SetupValue( g_menu.main.aimbot.hitchance.get( ), false, "hitchance" );//
	SetupValue( g_menu.main.aimbot.hitchance_amount.get( ), 60, "hitchance_ammount" );//
	SetupValue( g_menu.main.aimbot.ignor_limbs.get( ), false, "ignor_limbs" );//
	SetupValue( g_menu.main.aimbot.lagfix.get( ), false, "lagfix" );//
	SetupValue( g_menu.main.aimbot.correct.get( ), false, "correct" );//
	SetupValue( g_menu.main.aimbot.baim1_cond.get( ), false, "baim1_cond" );//
	SetupValue( g_menu.main.aimbot.only_baim_cond.get( ), false, "only_baim_cond" );//
	SetupValue( g_menu.main.aimbot.head_condition.get( ), false, "head_condition" );//

	//antiaim
	SetupValue( g_menu.main.antiaim.enable.get( ), false, "antiaimenable" );
	SetupValue( g_menu.main.antiaim.mode.get( ), 0, "antiaimmode" );
	SetupValue( g_menu.main.antiaim.pitch_stand.get( ), 0, "ptchstnd" );
	SetupValue( g_menu.main.antiaim.yaw_stand.get( ), 0, "yawstdn" );

	SetupValue( g_menu.main.antiaim.jitter_range_stand.get( ), 0, "jitter_range_stand" );
	SetupValue( g_menu.main.antiaim.rot_range_stand.get( ), 0, "rot_range_stand" );
	SetupValue( g_menu.main.antiaim.rot_speed_stand.get( ), 0, "rot_speed_stand" );
	SetupValue( g_menu.main.antiaim.rand_update_stand.get( ), 0, "rand_update_stand" );
	SetupValue( g_menu.main.antiaim.dir_time_stand.get( ), 0, "dir_time_stand" );
	SetupValue( g_menu.main.antiaim.dir_custom_stand.get( ), 0, "dir_custom_stand" );
	SetupValue( g_menu.main.antiaim.dir_lock.get( ), 0, "dir_lock" );
	SetupValue( g_menu.main.antiaim.body_fake_stand_fakewalk.get( ), 0, "body_fake_stand_fakewalk" );
	SetupValue( g_menu.main.antiaim.base_angle_stand.get( ), 0, "base_angle_stand" );
	SetupValue( g_menu.main.antiaim.body_fake_stand.get( ), 0, "body_fake_stand" );
	SetupValue( g_menu.main.antiaim.body_fake_stand_custom.get( ), 0, "body_fake_stand_custom" );

	SetupValue( g_menu.main.antiaim.pitch_walk.get( ), 0, "pitch_walk" );
	SetupValue( g_menu.main.antiaim.yaw_walk.get( ), 0, "yaw_walk" );
	SetupValue( g_menu.main.antiaim.jitter_range_walk.get( ), 0, "jitter_range_walk" );
	SetupValue( g_menu.main.antiaim.rot_range_walk.get( ), 0, "rot_range_walk" );

	SetupValue( g_menu.main.antiaim.rot_speed_walk.get( ), 0, "rot_speed_walk" );
	SetupValue( g_menu.main.antiaim.rand_update_walk.get( ), 0, "rand_update_walk" );
	SetupValue( g_menu.main.antiaim.dir_walk.get( ), 0, "dir_walk" );
	SetupValue( g_menu.main.antiaim.dir_time_walk.get( ), 0, "dir_time_walk" );
	SetupValue( g_menu.main.antiaim.dir_custom_walk.get( ), 0, "dir_custom_walk" );
	SetupValue( g_menu.main.antiaim.base_angle_walk.get( ), 0, "base_angle_walk" );

	SetupValue( g_menu.main.antiaim.pitch_air.get( ), 0, "pitch_air" );
	SetupValue( g_menu.main.antiaim.yaw_air.get( ), 0, "yaw_air" );
	SetupValue( g_menu.main.antiaim.jitter_range_air.get( ), 0, "jitter_range_air" );
	SetupValue( g_menu.main.antiaim.rot_range_air.get( ), 0, "rot_range_air" );
	SetupValue( g_menu.main.antiaim.rot_speed_air.get( ), 0, "rot_speed_air" );
	SetupValue( g_menu.main.antiaim.rand_update_air.get( ), 0, "rand_update_air" );
	SetupValue( g_menu.main.antiaim.dir_air.get( ), 0, "dir_air" );
	SetupValue( g_menu.main.antiaim.dir_time_air.get( ), 0, "dir_time_air" );
	SetupValue( g_menu.main.antiaim.dir_custom_air.get( ), 0, "dir_custom_air" );
	SetupValue( g_menu.main.antiaim.base_angle_air.get( ), 0, "base_angle_air" );
	SetupValue( g_menu.main.antiaim.body_fake_air.get( ), 0, "body_fake_air" );

	SetupValue( g_menu.main.antiaim.fake_yaw.get( ), 0, "fake_yaw" );
	SetupValue( g_menu.main.antiaim.fake_relative.get( ), 0, "fake_relative" );
	SetupValue( g_menu.main.antiaim.fake_jitter_range.get( ), 0, "fake_jitter_range" );

	SetupValue( g_menu.main.antiaim.lag_enable.get( ), false, "lag_enable" );
	SetupValue( g_menu.main.antiaim.lag_mode.get( ), 0, "lag_mode" );
	SetupValue( g_menu.main.antiaim.lag_limit.get( ), 0, "lag_limit" );
	SetupValue( g_menu.main.antiaim.lag_land.get( ), false, "lag_land" );

	SetupValue( g_menu.main.antiaim.manul_antiaim.get( ), false, "manul_antiaim" );
	SetupValue( g_menu.main.antiaim.draw_angles.get( ), false, "draw_angles" );
	SetupValue( g_menu.main.antiaim.draw_angles_chams.get( ), false, "draw_angles_chams" );

	SetupValue( g_menu.main.antiaim.draw_angles_chams_blend.get( ), 0, "draw_angles_chams_blend" );
	SetupValue( g_menu.main.antiaim.left.get( ), 0, "left" );
	SetupValue( g_menu.main.antiaim.right.get( ), 0, "right" );
	SetupValue( g_menu.main.antiaim.backward.get( ), 0, "backward" );

	//visuals
	SetupValue( g_menu.main.players.box_enemy.get( ), false, "box_enemy" );
	SetupValue( g_menu.main.players.dormant.get( ), false, "dormant" );
	SetupValue( g_menu.main.players.name_enemy.get( ), false, "name_enemy" );
	SetupValue( g_menu.main.players.glow.get( ), false, "glow" );
	SetupValue( g_menu.main.players.health_enemy.get( ), false, "health_enemy" );
	SetupValue( g_menu.main.players.weapon_enemy.get( ), false, "weapon_enemy" );
	SetupValue( g_menu.main.players.glow_blend.get( ), 0, "glow_blend" );
	SetupValue( g_menu.main.players.weapon_mode.get( ), 0, "weapon_mode" );
	SetupValue( g_menu.main.players.skeleton_enemy.get( ), false, "skeleton_enemy" );
	SetupValue( g_menu.main.players.ammo.get( ), false, "ammo" );
	SetupValue( g_menu.main.players.offscreen.get( ), false, "offscreen" );
	SetupValue( g_menu.main.players.lby_update.get( ), false, "lby_update" );
	
	/*
	* to do
	* setup value chams
	* setup valaue colors
	*/

	//visals2
	SetupValue( g_menu.main.visuals.distance.get( ), false, "distance" );
	SetupValue( g_menu.main.visuals.items.get( ), false, "items" );
	SetupValue( g_menu.main.visuals.ammo.get( ), false, "ammo" );
	SetupValue( g_menu.main.visuals.proj.get( ), false, "proj" );
	SetupValue( g_menu.main.visuals.disableteam.get( ), false, "disableteam" );
	SetupValue( g_menu.main.visuals.transparent_props.get( ), false, "transparent_props" );
	SetupValue( g_menu.main.visuals.enemy_radar.get( ), false, "enemy_radar" );
	SetupValue( g_menu.main.visuals.FogOverride.get( ), false, "FogOverride" );
	SetupValue( g_menu.main.visuals.novisrecoil.get( ), false, "novisrecoil" );
	SetupValue( g_menu.main.visuals.nosmoke.get( ), false, "nosmoke" );
	SetupValue( g_menu.main.visuals.nofog.get( ), false, "nofog" );
	SetupValue( g_menu.main.visuals.noflash.get( ), false, "noflash" );
	SetupValue( g_menu.main.visuals.noscope.get( ), false, "noscope" );
	SetupValue( g_menu.main.visuals.fov.get( ), false, "fov" );
	SetupValue( g_menu.main.visuals.fov_scoped.get( ), false, "fov_scoped" );
	SetupValue( g_menu.main.visuals.viewmodel_fov.get( ), false, "viewmodel_fov" );
	SetupValue( g_menu.main.visuals.spectators.get( ), false, "spectators" );
	SetupValue( g_menu.main.visuals.force_xhair.get( ), false, "force_xhair" );
	SetupValue( g_menu.main.visuals.spread_xhair.get( ), false, "spread_xhair" );
	SetupValue( g_menu.main.visuals.pen_crosshair.get( ), false, "pen_crosshair" );
	SetupValue( g_menu.main.visuals.pen_damage.get( ), false, "pen_damage" );
	SetupValue( g_menu.main.visuals.keybinds.get( ), false, "keybinds" );
	SetupValue( g_menu.main.visuals.tracers.get( ), false, "tracers" );
	SetupValue( g_menu.main.visuals.impact_beams.get( ), false, "impact_beams" );

	SetupValue( g_menu.main.visuals.night_darkness.get( ), 0, "night_darkness" );
	SetupValue( g_menu.main.visuals.transparent_props_amount.get( ), 0, "transparent_props_amount" );
	SetupValue( g_menu.main.visuals.FogStart.get( ), 0, "FogStart" );
	SetupValue( g_menu.main.visuals.FogEnd.get( ), 0, "FogEnd" );
	SetupValue( g_menu.main.visuals.Fogdensity.get( ), 0, "Fogdensity" );
	SetupValue( g_menu.main.visuals.fov_amt.get( ), 90, "fov_amt" );
	SetupValue( g_menu.main.visuals.viewmodel_fov_amt.get( ), 65, "viewmodel_fov_amt" );
	SetupValue( g_menu.main.visuals.spread_xhair_blend.get( ), 0, "spread_xhair_blend" );
	SetupValue( g_menu.main.visuals.impact_beams_time.get( ), 0, "impact_beams_time" );
	SetupValue( g_menu.main.visuals.thirdperson_distance.get( ), 0, "thirdperson_distance" );
	SetupValue( g_menu.main.visuals.thirdperson.get( ), 0, "thirdperson" );
	SetupValue( g_menu.main.visuals.world.get( ), 0, "world" );
	SetupValue( g_menu.main.visuals.chamstype.get( ), 0, "chamstype" );

	//,isc
	SetupValue( g_menu.main.movement.bhop.get( ), false, "bhop" );
	SetupValue( g_menu.main.movement.airduck.get( ), false, "airduck" );
	SetupValue( g_menu.main.movement.autostrafe.get( ), false, "autostrafe" );
	SetupValue( g_menu.main.movement.cstrafe.get( ), 0, "cstrafe" );
	SetupValue( g_menu.main.movement.astrafe.get( ), 0, "astrafe" );
	SetupValue( g_menu.main.movement.zstrafe.get( ), 0, "zstrafe" );
	SetupValue( g_menu.main.movement.z_dist.get( ), 0, "z_dist" );
	SetupValue( g_menu.main.movement.fakewalk.get( ), 0, "fakewalk" );
	SetupValue( g_menu.main.movement.cripwalk.get( ), 0, "cripwalk" );
	SetupValue( g_menu.main.movement.autopeek.get( ), 0, "autopeek" );
	SetupValue( g_menu.main.movement.autostop.get( ), 0, "autostop" );
	SetupValue( g_menu.main.movement.autostop_always_on.get( ), false, "autostop_always_on" );
}
void CConfig::SetupValue( int& value, int def, std::string name )
{
	value = def;
	ints.push_back( new ConfigValue< int >( name, &value ) );
}

void CConfig::SetupValue( float& value, float def, std::string name )
{
	value = def;
	floats.push_back( new ConfigValue< float >( name, &value ) );
}

void CConfig::SetupValue( bool& value, bool def, std::string name )
{
	value = def;
	bools.push_back( new ConfigValue< bool >( name, &value ) );
}

void CConfig::SetupValue( bool* value, bool def, int size, std::string name ) // for multiboxes
{
	for ( int c = 0; c < size; c++ )
	{
		value[ c ] = def;

		name += std::to_string( c );

		bools.push_back( new ConfigValue< bool >( name, &value[ c ] ) );
	}
}

static char name[ ] = "frenchook";

void CConfig::Save( )
{
	static TCHAR path[ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, path ) ) )
	{
		folder = std::string( path ) + "\\frenchook\\";
		file = std::string( path ) + "\\frenchook\\cfg.ini";
	}

	CreateDirectory( folder.c_str( ), NULL );

	for ( auto value : ints )
		WritePrivateProfileString( name, value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : floats )
		WritePrivateProfileString( name, value->name.c_str( ), std::to_string( *value->value ).c_str( ), file.c_str( ) );

	for ( auto value : bools )
		WritePrivateProfileString( name, value->name.c_str( ), *value->value ? "true" : "false", file.c_str( ) );
}

void CConfig::Load( )
{
	static TCHAR path[ MAX_PATH ];
	std::string folder, file;

	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, path ) ) )
	{
		folder = std::string( path ) + "\\frenchook\\";
		file = std::string( path ) + "\\frenchook\\cfg.ini";
	}

	CreateDirectory( folder.c_str( ), NULL );

	char value_l[ 32 ] = { '\0' };

	for ( auto value : ints )
	{
		GetPrivateProfileString( name, value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atoi( value_l );
	}

	for ( auto value : floats )
	{
		GetPrivateProfileString( name, value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = atof( value_l );
	}

	for ( auto value : bools )
	{
		GetPrivateProfileString( name, value->name.c_str( ), "", value_l, 32, file.c_str( ) );
		*value->value = !strcmp( value_l, "true" );
	}
}

CConfig* g_Config = new CConfig( );