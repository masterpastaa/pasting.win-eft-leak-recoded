#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace std;

uint64_t game_object_manager;

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
DWORD ScreenCenterX = NULL;
DWORD ScreenCenterY = NULL;

void SaveCPU(int ms)
{
	return std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
std::uintptr_t find_signature(const std::uintptr_t base_address, const char* sig, const char* mask)
{
	const auto buffer = std::make_unique<std::array<std::uint8_t, 0x100000>>();
	auto data = buffer.get()->data();
	std::uintptr_t result = 0;

	for (std::uintptr_t i = 0u; i < (2u << 25u); ++i)
	{
		readwtf(base_address + i * 0x100000, data, 0x100000);

		if (!data)
			return 0;

		for (std::uintptr_t j = 0; j < 0x100000u; ++j)
		{
			if ([](std::uint8_t const* data, std::uint8_t const* sig, char const* mask)
				{
					for (; *mask; ++mask, ++data, ++sig)
					{
						if (*mask == 'x' && *data != *sig) return false;
					}
					return (*mask) == 0;
				}(data + j, (std::uint8_t*)sig, mask))
			{
				result = base_address + i * 0x100000 + j;

				std::uint32_t rel = 0;

				readwtf(result + 3, &rel, sizeof(std::uint32_t));

				if (!rel)
					return 0;

				return result - base_address + rel + 7;
			}
		}
	}
}

uint64_t gameWorld = 0x0;
uint64_t fpsCamera = 0x0;
std::vector<uint64_t> EFTPlayerList;
std::vector<uint64_t> ExtractPlayerList;
uint64_t temp;
uint64_t local_player = 0;
uint64_t matrix_list_base = 0;
uint64_t dependency_index_table_base = 0;

struct BaseObject
{
	uint64_t previousObjectLink; //0x0000
	uint64_t nextObjectLink; //0x0008
	uint64_t object; //0x0010
};
uint64_t GetObjectFromList(uint64_t listPtr, uint64_t lastObjectPtr, const char* objectName)
{
	char name[256];
	uint64_t classNamePtr = 0x0;

	BaseObject activeObject = read<BaseObject>(listPtr);
	BaseObject lastObject = read<BaseObject>(lastObjectPtr);

	if (activeObject.object != 0x0)
	{
		while (activeObject.object != 0 && activeObject.object != lastObject.object)
		{
			classNamePtr = read<uint64_t>(activeObject.object + 0x60);
			readwtf(classNamePtr + 0x0, &name, sizeof(name));
			if (strcmp(name, objectName) == 0)
			{
				return activeObject.object;
			}

			activeObject = read<BaseObject>(activeObject.nextObjectLink);
		}
	}
	if (lastObject.object != 0x0)
	{
		classNamePtr = read<uint64_t>(lastObject.object + 0x60);
		readwtf(classNamePtr + 0x0, &name, 256);
		if (strcmp(name, objectName) == 0)
		{
			return lastObject.object;
		}
	}

	return uint64_t();
}
uint64_t getbone_matrix(uint64_t instance)
{
	static std::vector<uint64_t> temp{ 0xA8 , 0x28, 0x28, 0x10 };

	return ReadChain(instance, temp);
}
uint64_t get_camera_entity() {
	uint64_t temp = fpsCamera;
	if (!(temp =  read<uint64_t>(temp + 0x30)) || !(temp = read<uint64_t>(temp + 0x18)))
		return 0;
	//printf("camera entity: 0x%p \n", temp);
	return temp;
}
glm::mat4x4 get_view_matrix() {

	return read<glm::mat4x4>(get_camera_entity() + 0xD8);
}
bool world_to_screen(glm::vec3 world, glm::vec2* screen)
{
	const auto matrix = glm::transpose(get_view_matrix());

	const auto pos_vec = glm::vec3{ matrix[3][0], matrix[3][1], matrix[3][2] };

	const auto z = glm::dot(pos_vec, world) + matrix[3][3];

	if (z < 0.098f)
		return false;

	const auto x = glm::dot(glm::vec3{ matrix[0][0], matrix[0][1], matrix[0][2] }, world) + matrix[0][3];
	const auto y = glm::dot(glm::vec3{ matrix[1][0], matrix[1][1], matrix[1][2] }, world) + matrix[1][3];

	static const auto screen_center_x = Width * 0.5f;
	static const auto screen_center_y = Height * 0.5f;

	if (screen)
	{
		*screen =
		{
			screen_center_x * (1.f + x / z),
			screen_center_y * (1.f - y / z)
		};
	}

	return true;
}

glm::vec3 get_transform_position(int64_t pMatrix, uint32_t index) 
{
	readwtf(pMatrix + 0x18, &matrix_list_base, sizeof(matrix_list_base));
	readwtf(pMatrix + 0x20, &dependency_index_table_base, sizeof(dependency_index_table_base));

	static auto get_dependency_index = [](uint64_t base, int32_t index) {
		//driver::read_memory(base + index * 4, uint64_t(&index), sizeof(index));
		index = read<uint32_t>(base + index * 4);
		return index;
	};

	static auto get_matrix_blob = [](uint64_t base, uint64_t offs, float* blob, uint32_t size) {
		readwtf(base + offs, blob, size);
	};

	int32_t index_relation = get_dependency_index(dependency_index_table_base, index);

	glm::vec3 ret_value;
	{
		float* base_matrix3x4 = (float*)malloc(64),
			* matrix3x4_buffer0 = (float*)((uint64_t)base_matrix3x4 + 16),
			* matrix3x4_buffer1 = (float*)((uint64_t)base_matrix3x4 + 32),
			* matrix3x4_buffer2 = (float*)((uint64_t)base_matrix3x4 + 48);

		get_matrix_blob(matrix_list_base, index * 48, base_matrix3x4, 16);

		__m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
		__m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
		__m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };

		while (index_relation >= 0) {
			uint32_t matrix_relation_index = 6 * index_relation;

			// paziuret kur tik 3 nureadina, ten translationas, kur 4 = quatas ir yra rotationas.
			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index, matrix3x4_buffer2, 16);
			__m128 v_0 = *(__m128*)matrix3x4_buffer2;

			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 32, matrix3x4_buffer0, 16);
			__m128 v_1 = *(__m128*)matrix3x4_buffer0;

			get_matrix_blob(matrix_list_base, 8 * matrix_relation_index + 16, matrix3x4_buffer1, 16);
			__m128i v9 = *(__m128i*)matrix3x4_buffer1;

			__m128* v3 = (__m128*)base_matrix3x4; // r10@1
			__m128 v10; // xmm9@2
			__m128 v11; // xmm3@2
			__m128 v12; // xmm8@2
			__m128 v13; // xmm4@2
			__m128 v14; // xmm2@2
			__m128 v15; // xmm5@2
			__m128 v16; // xmm6@2
			__m128 v17; // xmm7@2

			v10 = _mm_mul_ps(v_1, *v3);
			v11 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 0));
			v12 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 85));
			v13 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -114));
			v14 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -37));
			v15 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, -86));
			v16 = _mm_castsi128_ps(_mm_shuffle_epi32(v9, 113));

			v17 = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1350), v13),
								_mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1360), v14)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1360), v14),
								_mm_mul_ps(_mm_mul_ps(v11, (__m128)xmmword_1410D1340), v16)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v12, (__m128)xmmword_1410D1340), v16),
								_mm_mul_ps(_mm_mul_ps(v15, (__m128)xmmword_1410D1350), v13)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
						v10)),
				v_0);

			*v3 = v17;

			index_relation = get_dependency_index(dependency_index_table_base, index_relation);
		}
		ret_value = *(glm::vec3*)base_matrix3x4;
		delete[] base_matrix3x4;
	}
	return ret_value;
}
glm::vec3 get_transform_position(uint64_t transform) {
	auto transform_internal = read<uint64_t>(transform + 0x10);
	if (!transform_internal)
		return glm::vec3();

	auto matrices = read<uint64_t>(transform_internal + 0x38);
	auto index = read<uint32_t>(transform_internal + 0x40);
	if (!matrices || index < 0)
		return glm::vec3();

	return get_transform_position(matrices, index);
}
glm::vec3 get_bone_position(uint64_t entity, uint32_t index) {
	const auto bone_transform = read<uint64_t>(getbone_matrix(entity) + 0x20 + index * 8);
	if (!bone_transform)
		return glm::vec3();
	return get_transform_position(bone_transform);
}
glm::vec3 get_obj_pos(uint64_t entity)
{
	uint64_t bone_matrix = getbone_matrix(entity);

	uint64_t bone = ReadChain(bone_matrix, { 0x20, 0x10, 0x38 });
	return read<glm::vec3>(bone + 0xB0);
}
bool open_extract(uint64_t extract)
{
	if (!extract)
		return false;

	int32_t status = read<int32_t>(extract + 0xA8); /* NotOpen = 1// Imcpmpleterequirement = 2 // Countdown = 3 // Open = 4 // Pending = 5 // Awaot ,amial Activation = 6*/

	if (status == 4)
		return true;


	return false;
}
std::wstring get_player_name(std::uint64_t entity)
{
	uint64_t GetProfile = read<uint64_t>(entity + 0x440);
	uint64_t playerinfo = read<uint64_t>(GetProfile + 0x28);
	const auto player_name_ptr = read<uintptr_t>(playerinfo + 0x10);

	return read_unicode(player_name_ptr + 0x14, sizeof(player_name_ptr + 0x10));
}

float get_player_health(uint64_t entity)
{
	uint64_t m_pHealthController = read<uint64_t>(entity + 0x470);
	uint64_t m_pHealthBody = read<uint64_t>(m_pHealthController + 0x20);
	uint64_t m_pBodyController = read<uint64_t>(m_pHealthBody + 0x18);

	for (int i = 0; i <= 7; i++) {
		
		auto body_part = read<uintptr_t>(m_pBodyController + 0x30 + (i * 0x18));
		auto health_container = read<uintptr_t>(body_part + 0x10);
		auto health = read<float>(health_container + 0x10);
		auto health_max = read<float>(health_container + 0x14);

		health = read<float>(health_container + 0x10);
		float hp = 0.f;
		hp += health;
		health = hp / health_max * 100;

		return health;
	}
}

uint64_t get_player_side(uint64_t entity) {

	uint64_t GetProfile = read<uint64_t>(entity + 0x440);
	uint64_t playerinfo = read<uint64_t>(GetProfile + 0x28);

	return read<uint64_t>(playerinfo + 0x50);
}
uint64_t get_registration_date(uint64_t entity) {

	uint64_t GetProfile = read<uint64_t>(entity + 0x440);
	uint64_t playerinfo = read<uint64_t>(GetProfile + 0x28);

	return read<uint64_t>(playerinfo + 0x54);
}
enum EPlayerSide : int {
	Usec = 1,
	Bear,
	Savage = 4
};
bool is_player(uint64_t entity) {
	return get_player_side(entity) == Usec || Bear && get_registration_date(entity) != 0;
}
bool is_scav(uint64_t entity) {
	return get_registration_date(entity) == 0;
}

void DrawSkeleton(uint64_t instance)
{
	uint64_t bone_matrix = getbone_matrix(instance);

	glm::vec3 neckpos = get_transform_position(read<uint64_t>(bone_matrix + (0x20 + ((int)BoneList::HumanNeck * 8))));
	glm::vec3  pelvispos = get_transform_position(read<uint64_t>(bone_matrix + (0x20 + ((int)BoneList::HumanPelvis * 8))));
	glm::vec3  previous(0, 0, 0);

	glm::vec3 current;

	RGBA SkelColor = { colors::skelcol[0] * 255, colors::skelcol[1] * 255, colors::skelcol[2] * 255, 255 };

	if (menu::rainbow_colors)
		SkelColor = Col.rainbow();

	for (auto a : skeleton)
	{
		previous = glm::vec3(0, 0, 0);
		for (int bone : a)
		{
			current = bone == BoneList::HumanNeck ? neckpos : (bone == BoneList::HumanPelvis ? pelvispos : get_transform_position(read<uint64_t>(bone_matrix + (0x20 + ((int)bone * 8)))));
			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}

			glm::vec2 Out1;
			glm::vec2 Out2;

			if (world_to_screen(previous, &Out1) && world_to_screen(current, &Out2)) {
				DrawLine(Out1.x, Out1.y, Out2.x, Out2.y, &SkelColor, menu::box_thick);
			}
		}
	}
}

typedef struct _TslEntity
{
	uint64_t pObjPointer;
	uint64_t Mesh;
}TslEntity;
vector<TslEntity> entityList;

//bool is_lootable_object(const std::string& object_name) {
//	static std::list<std::string> loot_object_list =
//	{
//		("cap"),
//		("Ammo_crate_Cap"),
//		("Grenade_box_Door"),
//		("Medical_Door"),
//		("POS"),
//		("Toolbox_Door"),
//		("card_file_box"),
//		("cover"),
//		("lootable"),
//		("scontainer"),
//		("suitcase_plastic_lootable_open"),
//		("weapon_box_cover")
//	};
//
//	for (auto& name : loot_object_list) {
//		if (object_name.find(name) != std::string::npos)
//			return true;
//	}
//
//	return false;
//}
//
//std::wstring get_active_weapon_name() {
//	const auto item = read<uint64_t>(get_hand_controller() + 0x50);
//	if (item != NULL) {
//		const auto item_template = read<uint64_t>(item + 0x38);
//		if (item_template != NULL) {
//			const auto weapon_name_ptr = read<uint64_t>(item_template + 0x58);
//			if (weapon_name_ptr != NULL) {
//				readwtf(weapon_name_ptr + 0x14, uint64_t(&weapon_name), sizeof(weapon_name));
//				if (weapon_name != NULL) {
//					return std::wstring(weapon_name);
//				}
//			}
//		}
//	}
//	return std::wstring();
//}

bool isaimbotting;
DWORD_PTR entityx;
float AimFOV = 15;

class CKey {
private:
	BYTE bPrevState[0x100];
public:
	CKey() {
		memset(bPrevState, 0, sizeof(bPrevState));
	}

	BOOL IsKeyPushing(BYTE vKey) {
		return GetAsyncKeyState(vKey) & 0x8000;
	}

	BOOL IsKeyPushed(BYTE vKey) {
		BOOL bReturn = FALSE;

		if (IsKeyPushing(vKey))
			bPrevState[vKey] = TRUE;
		else
		{
			if (bPrevState[vKey] == TRUE)
				bReturn = TRUE;
			bPrevState[vKey] = FALSE;
		}

		return bReturn;
	}
};
CKey Key;
double GetCrossDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
void Aimbot2(float x, float y)
{
	//std::printf("entityx2 %p.\n", entityx);
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = 2;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, TargetX, TargetY, NULL, NULL);

	return;
}
bool GetClosestPlayerToCrossHair(glm::vec2 Pos, float& max, float aimfov, DWORD_PTR entity)
{
	if (!Key.IsKeyPushing(VK_RBUTTON) || !isaimbotting)
	{
		if (entity)
		{
			float Dist = GetCrossDistance(Pos.x, Pos.y, Width / 2, Height / 2);

			if (Dist < max)
			{
				max = Dist;
				entityx = entity;
				AimFOV = aimfov;
			}
		}
	}
	return false;
}

void AimAt(DWORD_PTR entity)
{
	glm::vec2 vHeadBoneOut;
	glm::vec3 vHeadBone = get_bone_position(entity, 133);

	if (world_to_screen(vHeadBone, &vHeadBoneOut)) {

		if (vHeadBoneOut.y != 0 || vHeadBoneOut.y != 0)
		{
			if ((GetCrossDistance(vHeadBoneOut.x, vHeadBoneOut.y, Width / 2, Height / 2) <= AimFOV * 8) || isaimbotting) {

				Aimbot2(vHeadBoneOut.x, vHeadBoneOut.y);

			}
		}
	}
}
void Aimbot()
{
	if (entityx != 0)
	{
		if (Key.IsKeyPushing(VK_RBUTTON))
		{

			AimAt(entityx);
		}
		else
		{
			isaimbotting = false;
		}
	}
}
void AIms(DWORD_PTR entity)
{
	float max = 100.f;

	glm::vec2 vHeadBoneOut;
	glm::vec3 vHeadBone = get_bone_position(entity, 133);
	if (world_to_screen(vHeadBone, &vHeadBoneOut)) {

		if (GetClosestPlayerToCrossHair(vHeadBoneOut, max, AimFOV, entity))
			entityx = entity;
	}

}

void cache()
{
	while (true)
	{
		vector<TslEntity> tmpList;

		auto active_objects = read<std::array<uint64_t, 2>>(game_object_manager + 0x10);

		//printf("ActiveObjects: 0x%X\n", active_objects);

		gameWorld = GetObjectFromList(active_objects[1], active_objects[0], "GameWorld");

		//printf("gameWorld: 0x%X\n", gameWorld);

		uint64_t localGameWorld = ReadChain(gameWorld, { 0x30, 0x18, 0x28 });

		//printf("localgameWorld: 0x%X\n", localGameWorld);

		auto tagged_objects = read<std::array<uint64_t, 2>>(game_object_manager + 0x0);

		//printf("tagged_objects: 0x%X\n", tagged_objects);

		fpsCamera = GetObjectFromList(tagged_objects[1], tagged_objects[0], "FPS Camera");

		//printf("fpsCamera: 0x%X\n", fpsCamera);

		uint64_t onlineusers = read<uint64_t>(localGameWorld + 0x80);

		//printf("onlineusers: 0x%X\n", onlineusers);

		uint64_t list_base = read<uint64_t>(onlineusers + 0x10);
		int player_count = read<int>(onlineusers + 0x18);

		//printf("this->playercount :%i\n", player_count);

		constexpr auto BUFFER_SIZE = 128;

		uint64_t player_buffer[BUFFER_SIZE];
		readwtf(list_base + 0x20, player_buffer, sizeof(uint64_t) * player_count);

		for (int i = 0; i < player_count; i++)
		{
			uint64_t instance = player_buffer[i];

			if (instance == 0x00)
			{
				continue;
			}

			uint64_t bone_matrix = getbone_matrix(instance);
			uint64_t bone = ReadChain(bone_matrix, { 0x20, 0x10, 0x38 });
			glm::vec3 location = read<glm::vec3>(bone + 0xB0);

			if (i == 0)
			{
				local::local_player = instance;
				continue;
			}

			float player_health = get_player_health(instance);
			const int player_distance = glm::distance(location, get_obj_pos(local::local_player));

			if (bone != 0x00) {

				TslEntity tslEntity{ };
				tslEntity.pObjPointer = instance;

				tslEntity.Mesh = bone;

				if (player_health <= 0) {
					continue;
				}
				/*if (player_distance > 400)
					continue;*/

				tmpList.push_back(tslEntity);
			}
		}
		entityList = tmpList;
		Sleep(100);
	}
}


void ESP() {

	auto entityListCopy = entityList;
	RGBA ESPColor = { colors::espcol[0] * 255, colors::espcol[1] * 255, colors::espcol[2] * 255, 255 };

	if (!entityListCopy.empty())
	{

		for (unsigned long i = 0; i < entityListCopy.size(); ++i)
		{
			TslEntity entity = entityListCopy[i];

			const auto player_name = get_player_name(entity.pObjPointer);
			const auto player_health = get_player_health(entity.pObjPointer);

			uint64_t bone_matrix = getbone_matrix(entity.pObjPointer);
			uint64_t bone = ReadChain(bone_matrix, { 0x20, 0x10, 0x38 });
			glm::vec3 location = read<glm::vec3>(bone + 0xB0);
			glm::vec3 BoxHead = get_bone_position(entity.pObjPointer, 133);
			const int player_distance = glm::distance(location, get_obj_pos(local::local_player));

			//printf("distance :%d\n", player_distance);

			if (bone != 0x00) {

				glm::vec2 player_screen{};
				glm::vec2 normal_head{};
				glm::vec2 head_screen{};

				if (!world_to_screen(location, &player_screen))
					continue;

				if (!world_to_screen(glm::vec3(BoxHead.x, BoxHead.y + 0.3, BoxHead.z), &head_screen))
					continue;

				if (!world_to_screen(BoxHead, &normal_head))
					continue;

				float BoxHeight = (float)(player_screen.y - normal_head.y);
				float BoxWidth = BoxHeight / 3.0f;


				AIms(entity.pObjPointer);

				if (is_player(entity.pObjPointer) && is_scav(entity.pObjPointer))
				{
					if (visuals::name)
					{
						char name[64];
						sprintf_s(name, "[%dm] - %S", player_distance, player_name.c_str());

						DrawString(menu::font_size, head_screen.x, head_screen.y - 5, &Col.white_, true, true, name);
					}
				}

				if (visuals::box)
				{
					if (visuals::boxMode == 0 || visuals::boxMode == 1)
					{
						if (visuals::outline)
						{
							DrawNormalBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawNormalBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawNormalBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						}
						DrawNormalBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &ESPColor);
					}
					if (visuals::boxMode == 2 || visuals::boxMode == 3)
					{
						if (visuals::outline)
						{
							DrawCornerBox(player_screen.x - BoxWidth / 2 + 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawCornerBox(player_screen.x - BoxWidth / 2 - 1, head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y + 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
							DrawCornerBox(player_screen.x - BoxWidth / 2, head_screen.y - 1, BoxWidth, BoxHeight, menu::box_thick, &Col.black);
						}
						DrawCornerBox(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, menu::box_thick, &ESPColor);
					}

					if (visuals::boxMode == 1 || visuals::boxMode == 3) menu::box_thick = 1,
						DrawFilledRect(player_screen.x - (BoxWidth / 2), head_screen.y, BoxWidth, BoxHeight, &Col.filled);
				}

				if (visuals::health)
				{
					if (visuals::healthMode == 0 || visuals::healthMode == 3)
						DrawLeftProgressBar(player_screen.x, head_screen.y, BoxWidth, BoxHeight, 1, player_health);
					if (visuals::healthMode == 1 || visuals::healthMode == 4)
						DrawRightProgressBar(player_screen.x, head_screen.y, BoxWidth, BoxHeight, 1, player_health);
					if (visuals::healthMode == 2 || visuals::healthMode == 3 || visuals::healthMode == 4)
					{
						char vida[100];
						sprintf(vida, "Health: %d ", player_health);
						DrawString(12, player_screen.x, player_screen.y + 5, &Col.white, true, true, vida);

					}
				}

				if (visuals::lines)
				{
					if (visuals::lineMode == 0)
						DrawLine((Width / 2), Height, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
					if (visuals::lineMode == 1)
						DrawLine((Width), Height / 2, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
					if (visuals::lineMode == 2)
						DrawLine((Width / 2), Height / 2, player_screen.x, player_screen.y, &ESPColor, menu::box_thick);
				}

				if (visuals::show_head)
					DrawCircle(normal_head.x, normal_head.y, BoxHeight / 25, &Col.white_, 15);

				if (visuals::skel) {
					if (player_distance <= visuals::MaxSkeletonDrawDistance) {

						glm::vec2 vHeadBoneOut, vHipOut, vNeckOut
							, vUpperArmLeftOut, vUpperArmRightOut, vLeftHandOut
							, vRightHandOut, vLeftHandOut1, vRightHandOut1
							, vRightThighOut, vLeftThighOut, vRightCalfOut
							, vLeftCalfOut, vLeftFootOut, vRightFootOut, PelvisOut;

						glm::vec3 vHeadBone = get_bone_position(entity.pObjPointer, 133);
						if (!world_to_screen(vHeadBone, &vHeadBoneOut))
							continue;

						glm::vec3 vHip = get_bone_position(entity.pObjPointer, 14);
						if (!world_to_screen(vHip, &vHipOut))
							continue;

						glm::vec3 vNeck = get_bone_position(entity.pObjPointer, 132);
						if (!world_to_screen(vNeck, &vNeckOut))
							continue;

						glm::vec3 vUpperArmLeft = get_bone_position(entity.pObjPointer, 90);
						if (!world_to_screen(vUpperArmLeft, &vUpperArmLeftOut))
							continue;

						glm::vec3 vUpperArmRight = get_bone_position(entity.pObjPointer, 111);
						if(!world_to_screen(vUpperArmRight, &vUpperArmRightOut))
							continue;

						glm::vec3 vLeftHand = get_bone_position(entity.pObjPointer, 91);
						if (!world_to_screen(vLeftHand, &vLeftHandOut))
							continue;

						glm::vec3 vRightHand = get_bone_position(entity.pObjPointer, 112);
						if (!world_to_screen(vRightHand, &vRightHandOut))
							continue;

						glm::vec3 vLeftHand1 = get_bone_position(entity.pObjPointer, 92);
						if (!world_to_screen(vLeftHand1, &vLeftHandOut1))
							continue;

						glm::vec3 vRightHand1 = get_bone_position(entity.pObjPointer, 113);
						if (!world_to_screen(vRightHand1, &vRightHandOut1))
							continue;

						glm::vec3 vRightThigh = get_bone_position(entity.pObjPointer, 20);
						if (!world_to_screen(vRightThigh, &vRightThighOut))
							continue;

						glm::vec3 vLeftThigh = get_bone_position(entity.pObjPointer, 15);
						if (!world_to_screen(vLeftThigh, &vLeftThighOut))
							continue;

						glm::vec3 vRightCalf = get_bone_position(entity.pObjPointer, 22);
						if (!world_to_screen(vRightCalf, &vRightCalfOut))
							continue;

						glm::vec3 vLeftCalf = get_bone_position(entity.pObjPointer, 17);
						if (!world_to_screen(vLeftCalf, &vLeftCalfOut))
							continue;

						glm::vec3 vLeftFoot = get_bone_position(entity.pObjPointer, 18);
						if (!world_to_screen(vLeftFoot, &vLeftFootOut))
							continue;

						glm::vec3 vRightFoot = get_bone_position(entity.pObjPointer, 23);
						if (!world_to_screen(vRightFoot, &vRightFootOut))
							continue;

						glm::vec3 Pelvis = get_bone_position(entity.pObjPointer, 14);
						if (!world_to_screen(Pelvis, &PelvisOut))
							continue;

						DrawLine(vNeckOut.x, vNeckOut.y, vHeadBoneOut.x, vHeadBoneOut.y, &Col.green, menu::box_thick);
						DrawLine(PelvisOut.x, PelvisOut.y, vNeckOut.x, vNeckOut.y, &Col.green, menu::box_thick);

						DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.green, menu::box_thick);
						DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.green, menu::box_thick);

						DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.green, menu::box_thick);
						DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.green, menu::box_thick);

						DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.green, menu::box_thick);
						DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.green, menu::box_thick);

						DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.green, menu::box_thick);
						DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.green, menu::box_thick);

						DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.green, menu::box_thick);
						DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.green, menu::box_thick);

						DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.green, menu::box_thick);
						DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.green, menu::box_thick);
					}
				}
			}
		}
		Aimbot();
	}
}