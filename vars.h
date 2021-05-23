#pragma once

#define M_PI                       3.14159265358979323846f
#define URotationToRadians(URotation)        ((URotation)* (M_PI / 32768.0f))
#define URotationToDegree( URotation )        ( ( URotation ) * ( 360.0f / 65536.0f ) ) 
#define DegreeToURotation( Degree )            ( ( Degree ) * ( 65536.0f / 360.0f ) )
#define DegreeToRadian( Degree )            ( ( Degree ) * ( M_PI / 180.0f ) 
#define RadianToURotation( URotation )        ( ( URotation ) * ( 32768.0f / M_PI ) ) 
#define RadianToDegree( Radian )            ( ( Radian ) * ( 180.0f / M_PI ) )
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))

float rainbow_speed = 0.25f;
static int keystatus = 0;
static int realkey = 0;

uintptr_t resultant_entity;

namespace aimbot
{
	bool aimbot = false;
	bool ignore_team = false;
	bool rcs = true;
	bool forceauto = false;
	bool smooth = false;
	bool fovcircle = false;
	bool prediction = false;
	bool alonercs = false;

	int smoothscale = 1;
	float aimspeed = 1.f;
	float aimfov = 25;

	int selected_weapon = 0;

	int hitbox = 0;

	uint64_t resultant_entity;
}

namespace items
{
	bool enable_items = false;
	bool meds = false;
	bool armors = false;
	bool attach = false;
	bool rifles = false;
	bool snipers = false;
	bool weapons = false;
	bool ammo = false;
	bool clothing = false;
	bool others = false;
}

namespace visuals
{
	bool box = false;
	bool skel = false;
	bool car = false;
	bool health = false;
	bool zombies = false;
	bool animals = false;
	bool wepnhands = false;
	bool name = false;
	bool dbgname = false;
	bool crosshair = false;
	bool outline = false;
	bool lines = false;
	bool knocked = false;
	bool team = false;
	bool team_name = false;
	bool show_head = false;
	bool health_based = false;
	bool sleeping_player = false;

	bool show_ore = false;
	bool ore_stone = false;
	bool ore_metal = false;
	bool ore_sulfur = false;

	bool show_collectable = false;
	bool coll_vegetables = false;
	bool coll_wood = false;
	bool coll_stone = false;
	bool coll_metal = false;
	bool coll_sulfur = false;

	bool show_crates = false;
	bool crate_tools = false;
	bool crate_military = false;
	bool crate_normal = false;
	bool crate_barrel = false;
	bool crate_elite = false;

	bool show_droppeditems = false;
	bool show_scientists = false;

	int boxMode = 0;
	int nameMode = 0;
	int skelMode = 0;
	int animMode = 0;
	int itemMode = 0;
	int carMode = 0;
	int lineMode = 0;
	int healthMode = 0;

	int NumberofEntity = 0;
	int SpectatorCount = 0;

	int MaxDistance = 1000;
	int MaxCrateDistance = 100;
	int MaxCollectableDistance = 50;
	int MaxOreDistance = 100;
	int MaxScientistDistance = 200;
	int MaxSkeletonDrawDistance = 400;
	int MaxZombDistance = 300;
	int MaxAnimalDistance = 300;

	//glm::vec3 CurrentPosition = { 0, 0, 0 };
	//glm::vec3 SavePosition1 = { 0, 0, 0 };
}
namespace colors
{
	float chamscol[3] = { 1.0f , 0.0f , 0.0f };
	float espcol[3] = { 1.0f , 0.0f , 0.0f };
	float skelcol[3] = { 1.0f , 1.0f , 1.0f };
	float crosscol[3] = { 1.0f , 0.0f , 0.0f };

	float orecol[3] = { 1.0f , 0.0f , 0.0f };
	float collcol[3] = { 1.0f , 0.0f , 0.0f };
	float cratecol[3] = { 1.0f , 0.0f , 0.0f };
	float scientistcol[3] = { 1.0f , 0.0f , 0.0f };
	float itemscol[3] = { 1.0f , 0.0f , 0.0f };
}

namespace misc
{
	bool speedhack = false;
	bool superjump = false;
	bool removegrass = false;
	bool alwaysday = false;
	bool overlayfps = false;

	bool peter_parker = false;
	bool admin_flag = false;
	bool norecoil = false;
	bool nospread = false;
	bool nosway = false;
	bool notimeeoka = false;
	bool airstuck = false;

	float speedval = 2.0f;
	float settime = 0.f;
	float superheight = 1;
	int superscale = 2;
}

namespace menu
{
	bool rainbow_colors = false;
	bool menu_key = false;
	bool player_list = false;
	bool overlay_fps = true;
	bool debug = false;
	bool debug2 = false;
	bool watermark = true;
	bool limit60 = false;
	int font_size = 14;
	int box_thick = 1;
	float rainbow_speed = 0.25f;
	float crosshair_size = 1.f;
	static int settsMode = 0;
	ImFont* SkeetFont;
}

namespace hotkeys
{
	int aimkey;
	int airstuckey;
}

static const char* Hitbox[] =
{
	"Head",
	"Neck",
	"Pelvis"
};
static const char* boxStyle[] =
{
	"2D",
	"2D Filled",
	"2D Corner",
	"2D Corner Filled",
	"3D Box"
};
static const char* healthMode[] =
{
	"Left Bar",
	"Right Bar",
	"Numbers",
	"Lbar + Numbers",
	"Rbar + Numbers",
	"Bottom Bar"
};
static const char* linesMode[] =
{
	"Top",
	"Middle",
	"Bottom",
	"Aim Fov"
};
static const char* weaponsMode[] =
{
	"All",
	"Rifles",
	"Snipers",
	"Pistols",
	"Shotguns",
	"SMGs",
	"LMGs",
	"Bows"
};

static const char* keyNames[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static const char* settsName[] =
{
	"Default",
	"Config 1",
	"Config 2"
};

namespace local
{
	std::uint64_t local_player = 0;
	std::atomic<uint64_t> camera_instance{};
}

enum BoneList : int
{
	HumanBase = 0,
	HumanPelvis = 14,
	HumanLThigh1 = 15,
	HumanLThigh2 = 16,
	HumanLCalf = 17,
	HumanLFoot = 18,
	HumanLToe = 19,
	HumanRThigh1 = 20,
	HumanRThigh2 = 21,
	HumanRCalf = 22,
	HumanRFoot = 23,
	HumanRToe = 24,
	HumanSpine1 = 29,
	HumanSpine2 = 36,
	HumanSpine3 = 37,
	HumanLCollarbone = 89,
	HumanLUpperarm = 90,
	HumanLForearm1 = 91,
	HumanLForearm2 = 92,
	HumanLForearm3 = 93,
	HumanLPalm = 94,
	HumanRCollarbone = 110,
	HumanRUpperarm = 111,
	HumanRForearm1 = 112,
	HumanRForearm2 = 113,
	HumanRForearm3 = 114,
	HumanRPalm = 115,
	HumanNeck = 132,
	HumanHead = 133
};

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}
void ChangeKey2(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::airstuckey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press key to bind";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf(lpString, "%d", nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
	char lpString[1024];
	sprintf(lpString, "%f", nInteger);
	return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
}

float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
{
	char szData[32];

	GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

	return (float)atof(szData);
}

void Save_Settings(LPCSTR path)
{
	WritePrivateProfileInt(("Visuals"), ("m_playeresp"), visuals::box, path);
	WritePrivateProfileInt(("Visuals"), ("m_boxstyle"), visuals::boxMode, path);
	WritePrivateProfileInt(("Visuals"), ("m_health"), visuals::health, path);
	WritePrivateProfileInt(("Visuals"), ("m_healthstyle"), visuals::healthMode, path);
	WritePrivateProfileInt(("Visuals"), ("m_skeleton"), visuals::skel, path);
	WritePrivateProfileInt(("Visuals"), ("m_crosshair"), visuals::crosshair, path);
	WritePrivateProfileFloat(("Visuals"), ("m_crossize"), menu::crosshair_size, path);
	WritePrivateProfileInt(("Visuals"), ("m_playername"), visuals::name, path);
	WritePrivateProfileInt(("Visuals"), ("m_drawhead"), visuals::show_head, path);
	WritePrivateProfileInt(("Visuals"), ("m_outline"), visuals::outline, path);
	WritePrivateProfileInt(("Visuals"), ("m_snaplines"), visuals::lines, path);
	WritePrivateProfileInt(("Visuals"), ("m_linemode"), visuals::lineMode, path);
	WritePrivateProfileInt(("Visuals"), ("m_fontsize"), menu::font_size, path);
	WritePrivateProfileInt(("Visuals"), ("m_boxthick"), menu::box_thick, path);
	WritePrivateProfileInt(("Visuals"), ("m_itemhands"), visuals::wepnhands, path);
	WritePrivateProfileInt(("Visuals"), ("m_showsleeping"), visuals::sleeping_player, path);
	WritePrivateProfileInt(("Visuals"), ("m_playerlist"), menu::player_list, path);

	/*if (visuals::SavePosition1.x != 0 || visuals::SavePosition1.y != 0 || visuals::SavePosition1.z != 0) {
		WritePrivateProfileFloat(("Positions"), ("m_save_pos1.x"), visuals::SavePosition1.x, path);
		WritePrivateProfileFloat(("Positions"), ("m_save_pos1.y"), visuals::SavePosition1.y, path);
		WritePrivateProfileFloat(("Positions"), ("m_save_pos1.z"), visuals::SavePosition1.z, path);
	}*/

	WritePrivateProfileInt(("Aimbot"), ("m_aimbot"), aimbot::aimbot, path);
	WritePrivateProfileInt(("Aimbot"), ("m_smooth"), aimbot::smooth, path);
	WritePrivateProfileFloat(("Aimbot"), ("m_aimbotfov"), aimbot::aimfov, path);
	WritePrivateProfileFloat(("Aimbot"), ("m_aimbotsmooth"), aimbot::aimspeed, path);
	WritePrivateProfileInt(("Aimbot"), ("m_fovcircle"), aimbot::fovcircle, path);
	WritePrivateProfileInt(("Aimbot"), ("m_aimkey"), hotkeys::aimkey, path);
	WritePrivateProfileInt(("Aimbot"), ("m_hitbox"), aimbot::hitbox, path);
	WritePrivateProfileInt(("Aimbot"), ("m_rcs"), aimbot::rcs, path);
	WritePrivateProfileInt(("Aimbot"), ("m_forceauto"), aimbot::forceauto, path);
	WritePrivateProfileInt(("Aimbot"), ("m_prediction"), aimbot::prediction, path);

	WritePrivateProfileInt(("Misc"), ("m_playerlist"), menu::player_list, path);
	WritePrivateProfileInt(("Misc"), ("m_overlayfps"), menu::overlay_fps, path);
	WritePrivateProfileInt(("Misc"), ("m_watermarker"), menu::watermark, path);
	WritePrivateProfileInt(("Misc"), ("m_norecoil"), misc::norecoil, path);
	WritePrivateProfileInt(("Misc"), ("m_nospread"), misc::nospread, path);
	WritePrivateProfileInt(("Misc"), ("m_nosway"), misc::nosway, path);
	WritePrivateProfileInt(("Misc"), ("m_fixeoka"), misc::notimeeoka, path);
	WritePrivateProfileInt(("Misc"), ("m_spiderman"), misc::peter_parker, path);
	WritePrivateProfileInt(("Misc"), ("m_airstuckkey"), hotkeys::airstuckey, path);

	WritePrivateProfileInt(("ItemOre"), ("m_showore"), visuals::show_ore, path);
	WritePrivateProfileInt(("ItemOre"), ("m_ore_metal"), visuals::ore_metal, path);
	WritePrivateProfileInt(("ItemOre"), ("m_ore_stone"), visuals::ore_stone, path);
	WritePrivateProfileInt(("ItemOre"), ("m_ore_sulfur"), visuals::ore_sulfur, path);
	WritePrivateProfileInt(("ItemOre"), ("m_droppeditems"), visuals::show_droppeditems, path);
	WritePrivateProfileInt(("ItemOre"), ("m_scientists"), visuals::show_scientists, path);

	WritePrivateProfileInt(("ItemCollectable"), ("m_showcollectable"), visuals::show_collectable, path);
	WritePrivateProfileInt(("ItemCollectable"), ("m_coll_metal"), visuals::coll_metal, path);
	WritePrivateProfileInt(("ItemCollectable"), ("m_coll_sulfur"), visuals::coll_sulfur, path);
	WritePrivateProfileInt(("ItemCollectable"), ("m_coll_stone"), visuals::coll_stone, path);
	WritePrivateProfileInt(("ItemCollectable"), ("m_coll_vegetables"), visuals::coll_vegetables, path);
	WritePrivateProfileInt(("ItemCollectable"), ("m_coll_wood"), visuals::coll_wood, path);

	WritePrivateProfileInt(("ItemCrates"), ("m_showcrates"), visuals::show_crates, path);
	WritePrivateProfileInt(("ItemCrates"), ("m_crate_barrel"), visuals::crate_barrel, path);
	WritePrivateProfileInt(("ItemCrates"), ("m_crate_military"), visuals::crate_military, path);
	WritePrivateProfileInt(("ItemCrates"), ("m_crate_normal"), visuals::crate_normal, path);
	WritePrivateProfileInt(("ItemCrates"), ("m_crate_elite"), visuals::crate_elite, path);
	WritePrivateProfileInt(("ItemCrates"), ("m_crate_tools"), visuals::crate_tools, path);

	WritePrivateProfileFloat(("Colors"), ("m_espr"), colors::espcol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_espg"), colors::espcol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_espb"), colors::espcol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_skelr"), colors::skelcol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_skelg"), colors::skelcol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_skelb"), colors::skelcol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_crossr"), colors::crosscol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_crossg"), colors::crosscol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_crossb"), colors::crosscol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_crater"), colors::cratecol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_crateg"), colors::cratecol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_crateb"), colors::cratecol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_collr"), colors::collcol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_collg"), colors::collcol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_collb"), colors::collcol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_orer"), colors::orecol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_oreg"), colors::orecol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_oreb"), colors::orecol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_itemsr"), colors::itemscol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_itemsg"), colors::itemscol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_itemsb"), colors::itemscol[2], path);
	WritePrivateProfileFloat(("Colors"), ("m_scientistr"), colors::scientistcol[0], path);
	WritePrivateProfileFloat(("Colors"), ("m_scientistg"), colors::scientistcol[1], path);
	WritePrivateProfileFloat(("Colors"), ("m_scientistb"), colors::scientistcol[2], path);
	WritePrivateProfileInt(("Colors"), ("m_rainbow"), menu::rainbow_colors, path);
	WritePrivateProfileFloat(("Colors"), ("m_rainbowspeed"), menu::rainbow_speed, path);

	WritePrivateProfileInt(("Distance"), ("m_collactabledistance"), visuals::MaxCollectableDistance, path);
	WritePrivateProfileInt(("Distance"), ("m_collactabledistance"), visuals::MaxOreDistance, path);
	WritePrivateProfileInt(("Distance"), ("m_cratedistance"), visuals::MaxCrateDistance, path);
	WritePrivateProfileInt(("Distance"), ("m_scientistdistance"), visuals::MaxScientistDistance, path);
	WritePrivateProfileInt(("Distance"), ("m_esqueletoistance"), visuals::MaxSkeletonDrawDistance, path);
}

void Load_Settings(LPCSTR path)
{
	visuals::box = GetPrivateProfileIntA(("Visuals"), ("m_playeresp"), visuals::box, path);
	visuals::health = GetPrivateProfileIntA(("Visuals"), ("m_health"), visuals::health, path);
	visuals::healthMode = GetPrivateProfileIntA(("Visuals"), ("m_healthstyle"), visuals::healthMode, path);
	visuals::boxMode = GetPrivateProfileIntA(("Visuals"), ("m_boxstyle"), visuals::boxMode, path);
	visuals::crosshair = GetPrivateProfileIntA(("Visuals"), ("m_crosshair"), visuals::crosshair, path);
	visuals::skel = GetPrivateProfileIntA(("Visuals"), ("m_skeleton"), visuals::skel, path);
	menu::crosshair_size = GetPrivateProfileFloat(("Visuals"), ("m_crossize"), menu::crosshair_size, path);
	visuals::name = GetPrivateProfileIntA(("Visuals"), ("m_playername"), visuals::name, path);
	visuals::show_head = GetPrivateProfileIntA(("Visuals"), ("m_drawhead"), visuals::show_head, path);
	visuals::outline = GetPrivateProfileIntA(("Visuals"), ("m_outline"), visuals::outline, path);
	visuals::lines = GetPrivateProfileIntA(("Visuals"), ("m_snaplines"), visuals::lines, path);
	visuals::lineMode = GetPrivateProfileIntA(("Visuals"), ("m_linemode"), visuals::lineMode, path);
	menu::font_size = GetPrivateProfileIntA(("Visuals"), ("m_fontsize"), menu::font_size, path);
	menu::box_thick = GetPrivateProfileIntA(("Visuals"), ("m_boxthick"), menu::box_thick, path);
	visuals::wepnhands = GetPrivateProfileIntA(("Visuals"), ("m_itemhands"), visuals::wepnhands, path);
	visuals::sleeping_player = GetPrivateProfileIntA(("Visuals"), ("m_showsleeping"), visuals::sleeping_player, path);
	menu::player_list = GetPrivateProfileIntA(("Visuals"), ("m_playerlist"), menu::player_list, path);

	/*visuals::SavePosition1.x = GetPrivateProfileFloat(("Positions"), ("m_save_pos1.x"), visuals::SavePosition1.x, path);
	visuals::SavePosition1.y = GetPrivateProfileFloat(("Positions"), ("m_save_pos1.y"), visuals::SavePosition1.y, path);
	visuals::SavePosition1.z = GetPrivateProfileFloat(("Positions"), ("m_save_pos1.z"), visuals::SavePosition1.z, path);*/

	aimbot::aimbot = GetPrivateProfileIntA(("Aimbot"), ("m_aimbot"), aimbot::aimbot, path);
	aimbot::smooth = GetPrivateProfileIntA(("Aimbot"), ("m_smooth"), aimbot::smooth, path);
	aimbot::aimfov = GetPrivateProfileFloat(("Aimbot"), ("m_aimbotfov"), aimbot::aimfov, path);
	aimbot::aimspeed = GetPrivateProfileFloat(("Aimbot"), ("m_aimbotsmooth"), aimbot::aimspeed, path);
	aimbot::fovcircle = GetPrivateProfileIntA(("Aimbot"), ("m_fovcircle"), aimbot::fovcircle, path);
	hotkeys::aimkey = GetPrivateProfileIntA(("Aimbot"), ("m_aimkey"), hotkeys::aimkey, path);
	aimbot::hitbox = GetPrivateProfileIntA(("Aimbot"), ("m_hitbox"), aimbot::hitbox, path);
	aimbot::rcs = GetPrivateProfileIntA(("Aimbot"), ("m_rcs"), aimbot::rcs, path);
	aimbot::forceauto = GetPrivateProfileIntA(("Aimbot"), ("m_forceauto"), aimbot::forceauto, path);
	aimbot::prediction = GetPrivateProfileIntA(("Aimbot"), ("m_prediction"), aimbot::prediction, path);

	menu::player_list = GetPrivateProfileIntA(("Misc"), ("m_playerlist"), menu::player_list, path);
	misc::overlayfps = GetPrivateProfileIntA(("Misc"), ("m_overlayfps"), menu::overlay_fps, path);
	menu::watermark = GetPrivateProfileIntA(("Misc"), ("m_watermarker"), menu::watermark, path);
	misc::norecoil = GetPrivateProfileIntA(("Misc"), ("m_norecoil"), misc::norecoil, path);
	misc::nospread = GetPrivateProfileIntA(("Misc"), ("m_nospread"), misc::nospread, path);
	misc::nosway = GetPrivateProfileIntA(("Misc"), ("m_nosway"), misc::nosway, path);
	misc::notimeeoka = GetPrivateProfileIntA(("Misc"), ("m_fixeoka"), misc::notimeeoka, path);
	misc::peter_parker = GetPrivateProfileIntA(("Misc"), ("m_spiderman"), misc::peter_parker, path);
	hotkeys::airstuckey = GetPrivateProfileIntA(("Misc"), ("m_airstuckkey"), hotkeys::airstuckey, path);

	visuals::show_ore = GetPrivateProfileIntA(("ItemOre"), ("m_showore"), visuals::show_ore, path);
	visuals::ore_metal = GetPrivateProfileIntA(("ItemOre"), ("m_ore_metal"), visuals::ore_metal, path);
	visuals::ore_stone = GetPrivateProfileIntA(("ItemOre"), ("m_ore_stone"), visuals::ore_stone, path);
	visuals::ore_sulfur = GetPrivateProfileIntA(("ItemOre"), ("m_ore_sulfur"), visuals::ore_sulfur, path);
	visuals::show_droppeditems = GetPrivateProfileIntA(("ItemOre"), ("m_droppeditems"), visuals::show_droppeditems, path);
	visuals::show_scientists = GetPrivateProfileIntA(("ItemOre"), ("m_scientists"), visuals::show_scientists, path);

	visuals::show_collectable = GetPrivateProfileIntA(("ItemCollectable"), ("m_showcollectable"), visuals::show_collectable, path);
	visuals::coll_metal = GetPrivateProfileIntA(("ItemCollectable"), ("m_coll_metal"), visuals::coll_metal, path);
	visuals::coll_sulfur = GetPrivateProfileIntA(("ItemCollectable"), ("m_coll_sulfur"), visuals::coll_sulfur, path);
	visuals::coll_stone = GetPrivateProfileIntA(("ItemCollectable"), ("m_coll_stone"), visuals::coll_stone, path);
	visuals::coll_vegetables = GetPrivateProfileIntA(("ItemCollectable"), ("m_coll_vegetables"), visuals::coll_vegetables, path);
	visuals::coll_wood = GetPrivateProfileIntA(("ItemCollectable"), ("m_coll_wood"), visuals::coll_wood, path);

	visuals::show_crates = GetPrivateProfileIntA(("ItemCrates"), ("m_showcrates"), visuals::show_crates, path);
	visuals::crate_barrel = GetPrivateProfileIntA(("ItemCrates"), ("m_crate_barrel"), visuals::crate_barrel, path);
	visuals::crate_military = GetPrivateProfileIntA(("ItemCrates"), ("m_crate_military"), visuals::crate_military, path);
	visuals::crate_normal = GetPrivateProfileIntA(("ItemCrates"), ("m_crate_normal"), visuals::crate_normal, path);
	visuals::crate_elite = GetPrivateProfileIntA(("ItemCrates"), ("m_crate_elite"), visuals::crate_elite, path);
	visuals::crate_tools = GetPrivateProfileIntA(("ItemCrates"), ("m_crate_tools"), visuals::crate_tools, path);

	colors::espcol[0] = GetPrivateProfileFloat(("Colors"), ("m_espr"), colors::espcol[0], path);
	colors::espcol[1] = GetPrivateProfileFloat(("Colors"), ("m_espg"), colors::espcol[1], path);
	colors::espcol[2] = GetPrivateProfileFloat(("Colors"), ("m_espb"), colors::espcol[2], path);
	colors::skelcol[0] = GetPrivateProfileFloat(("Colors"), ("m_skelr"), colors::skelcol[0], path);
	colors::skelcol[1] = GetPrivateProfileFloat(("Colors"), ("m_skelg"), colors::skelcol[1], path);
	colors::skelcol[2] = GetPrivateProfileFloat(("Colors"), ("m_skelb"), colors::skelcol[2], path);
	colors::crosscol[0] = GetPrivateProfileFloat(("Colors"), ("m_crossr"), colors::crosscol[0], path);
	colors::crosscol[1] = GetPrivateProfileFloat(("Colors"), ("m_crossg"), colors::crosscol[1], path);
	colors::crosscol[2] = GetPrivateProfileFloat(("Colors"), ("m_crossb"), colors::crosscol[2], path);
	colors::cratecol[0] = GetPrivateProfileFloat(("Colors"), ("m_crater"), colors::cratecol[0], path);
	colors::cratecol[1] = GetPrivateProfileFloat(("Colors"), ("m_crateg"), colors::cratecol[1], path);
	colors::cratecol[2] = GetPrivateProfileFloat(("Colors"), ("m_crateb"), colors::cratecol[2], path);
	colors::collcol[0] = GetPrivateProfileFloat(("Colors"), ("m_collr"), colors::collcol[0], path);
	colors::collcol[1] = GetPrivateProfileFloat(("Colors"), ("m_collg"), colors::collcol[1], path);
	colors::collcol[2] = GetPrivateProfileFloat(("Colors"), ("m_collb"), colors::collcol[2], path);
	colors::orecol[0] = GetPrivateProfileFloat(("Colors"), ("m_orer"), colors::orecol[0], path);
	colors::orecol[1] = GetPrivateProfileFloat(("Colors"), ("m_oreg"), colors::orecol[1], path);
	colors::orecol[2] = GetPrivateProfileFloat(("Colors"), ("m_oreb"), colors::orecol[2], path);
	colors::itemscol[0] = GetPrivateProfileFloat(("Colors"), ("m_itemsr"), colors::itemscol[0], path);
	colors::itemscol[1] = GetPrivateProfileFloat(("Colors"), ("m_itemsg"), colors::itemscol[1], path);
	colors::itemscol[2] = GetPrivateProfileFloat(("Colors"), ("m_itemsb"), colors::itemscol[2], path);
	colors::scientistcol[0] = GetPrivateProfileFloat(("Colors"), ("m_scientistr"), colors::scientistcol[0], path);
	colors::scientistcol[1] = GetPrivateProfileFloat(("Colors"), ("m_scientistg"), colors::scientistcol[1], path);
	colors::scientistcol[2] = GetPrivateProfileFloat(("Colors"), ("m_scientistb"), colors::scientistcol[2], path);

	visuals::MaxCollectableDistance = GetPrivateProfileIntA(("Distance"), ("m_collactabledistance"), visuals::MaxCollectableDistance, path);
	visuals::MaxOreDistance = GetPrivateProfileIntA(("Distance"), ("m_collactabledistance"), visuals::MaxOreDistance, path);
	visuals::MaxCrateDistance = GetPrivateProfileIntA(("Distance"), ("m_cratedistance"), visuals::MaxCrateDistance, path);
	visuals::MaxScientistDistance = GetPrivateProfileIntA(("Distance"), ("m_scientistdistance"), visuals::MaxScientistDistance, path);
	visuals::MaxSkeletonDrawDistance = GetPrivateProfileIntA(("Distance"), ("m_esqueletoistance"), visuals::MaxSkeletonDrawDistance, path);

	menu::rainbow_colors = GetPrivateProfileIntA(("Colors"), ("m_rainbow"), menu::rainbow_colors, path);
	menu::rainbow_speed = GetPrivateProfileFloat(("Colors"), ("m_rainbowspeed"), menu::rainbow_speed, path);
};

void shortcurts()
{
	if (GetAsyncKeyState(VK_INSERT))
	{
		if (menu::menu_key == false)
		{
			menu::menu_key = true;
		}
		else if (menu::menu_key == true)
		{
			menu::menu_key = false;
		}
		Sleep(200);
	}
}

int select_hitbox()
{
	int hitbox = 0;

	//if (aimbot::hitbox == 0)
	//	hitbox = BoneList::head; //head
	//else if (aimbot::hitbox == 1)
	//	hitbox = BoneList::neck; //neck
	//else if (aimbot::hitbox == 2)
	//	hitbox = BoneList::pelvis; //chest
	//else if (aimbot::hitbox == 3)
	//	hitbox = BoneList::penis;
	//else if (aimbot::hitbox == 4)
	//	hitbox = BoneList::pelvis;

	return hitbox;
}

#include <list>

std::list<int> upper_part = { BoneList::HumanNeck, BoneList::HumanHead };
std::list<int> right_arm = { BoneList::HumanNeck, BoneList::HumanRUpperarm, BoneList::HumanRForearm1, BoneList::HumanRPalm };
std::list<int> left_arm = { BoneList::HumanNeck, BoneList::HumanLUpperarm, BoneList::HumanLForearm1, BoneList::HumanLPalm };
std::list<int> spine = { BoneList::HumanNeck, BoneList::HumanSpine1, BoneList::HumanSpine2, BoneList::HumanPelvis };

std::list<int> lower_right = { BoneList::HumanPelvis, BoneList::HumanRThigh1, BoneList::HumanRCalf, BoneList::HumanRFoot };
std::list<int> lower_left = { BoneList::HumanPelvis, BoneList::HumanLThigh1, BoneList::HumanLCalf, BoneList::HumanLFoot };

std::list<std::list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

