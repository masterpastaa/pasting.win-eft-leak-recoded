#include "Main.h"

HRESULT DirectXInit(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = Width;
	p_Params.BackBufferHeight = Height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImFontConfig font_config;
	font_config.OversampleH = 1;
	font_config.OversampleV = 1;
	font_config.PixelSnapH = true;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF,
		0x0400, 0x044F,
		0,
	};

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 13.f);

	menu::SkeetFont = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(icon_compressed_data, icon_compressed_size, 15.f, &font_config, ranges);

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);

	ImGui::StyleColorsClassic();
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 0.0f;
	style->FramePadding = ImVec2(2, 2);
	style->FrameRounding = 0.0f;
	style->ItemSpacing = ImVec2(8, 8); 
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 10.0f;
	style->GrabRounding = 0.0f;
	style->TabRounding = 0.f;
	style->ChildRounding = 0.f;

	style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImColor(150, 0, 0, 255);
	style->Colors[ImGuiCol_SliderGrab] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_SliderGrabActive] = ImColor(60, 60, 60, 255);
	style->Colors[ImGuiCol_Button] = ImColor(40, 40, 40, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImColor(50, 50, 50, 255);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

	style->WindowTitleAlign.x = 0.50f;
	style->FrameRounding = 2.0f;

	p_Object->Release();
	return S_OK;
}
void SetupWindow()
{
	WNDCLASSEX wClass =
	{
		sizeof(WNDCLASSEX),
		0,
		WinProc,
		0,
		0,
		nullptr,
		LoadIcon(nullptr, IDI_APPLICATION),
		LoadCursor(nullptr, IDC_ARROW),
		nullptr,
		nullptr,
		TEXT("Test1"),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wClass))
		exit(1);

	GameWnd = FindWindowW(NULL, TEXT("EscapeFromTarkov"));

	//printf("GameWnd Found! : %p\n", GameWnd);

	if (GameWnd)
	{
		GetClientRect(GameWnd, &GameRect);
		POINT xy;
		ClientToScreen(GameWnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right;
		Height = GameRect.bottom;
	}
	else exit(2);

	MyWnd = CreateWindowExA(NULL, "Test1", "Test1", WS_POPUP | WS_VISIBLE, GameRect.left, GameRect.top, Width, Height, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(MyWnd, &Margin);
	SetWindowLong(MyWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	ShowWindow(MyWnd, SW_SHOW);
	UpdateWindow(MyWnd);

	//printf("Hwnd created : %p\n", MyWnd);
}

void background()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.09f, 0.09f, 0.40f / 1.f * 2.f));
	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove;
	ImGui::Begin("##background", nullptr, flags);
	ImGui::End();
	ImGui::PopStyleColor();
}
bool draw_abigsquare()
{
	static int MenuTab = 0;
	static int VisualTab = 0;
	float
		TextSpaceLine = 90.f,
		SpaceLineOne = 120.f,
		SpaceLineTwo = 280.f,
		SpaceLineThr = 420.f;
	ImGuiStyle* style = &ImGui::GetStyle();
	//aimbot::selected_weapon = GetLocalSelectedWeapon();

	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin(("Rust"), NULL, flags);
	{
		ImGui::SetWindowSize(ImVec2(590, 315), ImGuiCond_Once);
		{
			ImGui::BeginChild(("##Tabs"), ImVec2(-1, 30.0f));
			{
				style->ItemSpacing = ImVec2(1, 1);
				ImGui::PushFont(menu::SkeetFont);
				{
					if (ImGui::Button((("! Aimbot")), ImVec2(185, 20)))
					{
						MenuTab = 0;
					}ImGui::SameLine();
					if (ImGui::Button((("$ Visuals")), ImVec2(185, 20)))
					{
						MenuTab = 1;
					}ImGui::SameLine();
					if (ImGui::Button((("% Misc")), ImVec2(185, 20)))
					{
						MenuTab = 2;
					}ImGui::SameLine();
				} ImGui::PopFont();

			} ImGui::EndChild();

			style->ItemSpacing = ImVec2(8, 8);

			if (MenuTab == 0)
			{
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Text(("Aimbot:"));
				ImGui::SetCursorPos(ImVec2(10, 70));
				ImGui::BeginChild(("##Aimbot"), ImVec2(130.f, 200.f), true);
				{
					ImGui::Checkbox(("Aimbot"), &aimbot::aimbot);
					ImGui::Checkbox(("Smooth"), &aimbot::smooth);
					ImGui::Checkbox(("Show FOV"), &aimbot::fovcircle);
					ImGui::Checkbox(("RCS"), &aimbot::rcs);
					ImGui::Checkbox(("Force Auto"), &aimbot::forceauto);
					ImGui::Checkbox(("Prediction"), &aimbot::prediction);
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(150, 50));
				ImGui::Text(("Settings:"));
				ImGui::SetCursorPos(ImVec2(150, 70));
				ImGui::BeginChild(("##Aimbot2"), ImVec2(-1.f, 200.f), true);
				{
					ImGui::PushItemWidth(200.f);
					ImGui::Text(("Select Weapon: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::Combo(("##selectwep"), &aimbot::selected_weapon, weaponsMode, IM_ARRAYSIZE(weaponsMode));
					ImGui::PopItemWidth();

					ImGui::PushItemWidth(270.f);
					ImGui::Text(("FOV: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloat2("##fovkrai", &aimbot::aimfov, 1.f, 50.f, "%.2f");

					ImGui::Text(("Smooth: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloat2(("##smoothkrai"), &aimbot::aimspeed, 1.f, 25.f, "%.2f");

					ImGui::PopItemWidth();

					ImGui::Text(("Aim Key: ")); ImGui::SameLine(SpaceLineOne);
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

					ImGui::PushItemWidth(200.f);
					ImGui::Text(("Hitbox: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::Combo(("##BONES"), &aimbot::hitbox, Hitbox, IM_ARRAYSIZE(Hitbox));
					ImGui::PopItemWidth();
				}
				ImGui::EndChild();
			}
			else if (MenuTab == 1)
			{

				if (ImGui::Button((("Players")), ImVec2(185, 20)))
				{
					VisualTab = 0;
				}ImGui::SameLine();
				if (ImGui::Button((("Items")), ImVec2(185, 20)))
				{
					VisualTab = 1;
				}

				if (VisualTab == 1)
				{
					ImGui::SetCursorPos(ImVec2(10, 80));
					ImGui::Text(("Ore and Others ESP:"));
					ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::BeginChild(("##ORES"), ImVec2(190.f, 175.f), true);
					{
						ImGui::Checkbox(("Show Ore"), &visuals::show_ore);
						ImGui::Checkbox(("Metal"), &visuals::ore_metal);
						ImGui::Checkbox(("Stone"), &visuals::ore_stone);
						ImGui::Checkbox(("Sulfur"), &visuals::ore_sulfur);
						ImGui::Checkbox(("Dropped Items"), &visuals::show_droppeditems);
						ImGui::Checkbox(("Scientist NPC"), &visuals::show_scientists);
					}
					ImGui::EndChild();

					ImGui::SetCursorPos(ImVec2(210, 80));
					ImGui::Text(("Collectables:"));
					ImGui::SetCursorPos(ImVec2(210, 100));
					ImGui::BeginChild(("##COLLECT"), ImVec2(190.f, 175.f), true);
					{
						ImGui::Checkbox(("Show Collectables"), &visuals::show_collectable);
						ImGui::Checkbox(("Vegetables"), &visuals::coll_vegetables);
						ImGui::Checkbox(("Wood"), &visuals::coll_wood);
						ImGui::Checkbox(("Metal"), &visuals::coll_metal);
						ImGui::Checkbox(("Stone"), &visuals::coll_stone);
						ImGui::Checkbox(("Sulfur"), &visuals::coll_sulfur);
					}
					ImGui::EndChild();

					ImGui::SetCursorPos(ImVec2(410, 80));
					ImGui::Text(("Crates:"));
					ImGui::SetCursorPos(ImVec2(410, 100));
					ImGui::BeginChild(("##CRATES"), ImVec2(-1.f, 175.f), true);
					{
						ImGui::Checkbox(("Show Crates"), &visuals::show_crates);
						ImGui::Checkbox(("Military"), &visuals::crate_military);
						ImGui::Checkbox(("Normal"), &visuals::crate_normal);
						ImGui::Checkbox(("Elite"), &visuals::crate_elite);
						ImGui::Checkbox(("Tools"), &visuals::crate_tools);
						ImGui::Checkbox(("Barrel"), &visuals::crate_barrel);
					}
					ImGui::EndChild();
				}

				if (VisualTab == 0)
				{
					ImGui::SetCursorPos(ImVec2(10, 80));
					ImGui::Text(("Player ESP:"));
					ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::BeginChild(("##Players1"), ImVec2(240.f, 175.f), true);
					{
						ImGui::Checkbox(("Show Box"), &visuals::box);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(("Show Skeleton"), &visuals::skel);

						ImGui::Checkbox(("Show Name"), &visuals::name);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(("Show Head"), &visuals::show_head);

						ImGui::Checkbox(("Show Health"), &visuals::health);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(("Show Lines"), &visuals::lines);

						ImGui::Checkbox(("Show Item"), &visuals::wepnhands);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(("Show Sleeping"), &visuals::sleeping_player);

						ImGui::Checkbox(("Crosshair"), &visuals::crosshair);
						ImGui::SameLine(120.f);
						ImGui::Checkbox(("Rainbow"), &menu::rainbow_colors);
					}
					ImGui::EndChild();
					ImGui::SetCursorPos(ImVec2(260, 80));
					ImGui::Text(("Styles:"));
					ImGui::SetCursorPos(ImVec2(260, 100));
					ImGui::BeginChild(("##Players22"), ImVec2(-1, 175.f), true);
					{
						ImGui::PushItemWidth(170.f);
						ImGui::Text(("Box Style")); ImGui::SameLine(100.f);
						ImGui::Combo(("##BOXSTYLES"), &visuals::boxMode, boxStyle, IM_ARRAYSIZE(boxStyle));
						ImGui::Text("Health Style"); ImGui::SameLine(100.f);
						ImGui::Combo(("##HEALTHSTYLE"), &visuals::healthMode, healthMode, IM_ARRAYSIZE(healthMode));
						ImGui::Text("Lines Style"); 	ImGui::SameLine(100.f);
						ImGui::Combo(("##LINESSTYLE"), &visuals::lineMode, linesMode, IM_ARRAYSIZE(linesMode));

						ImGui::Text(("Font Size: ")); ImGui::SameLine(TextSpaceLine);
						ImGui::SliderInt(("##FontSize"), &menu::font_size, 10.f, 15.f);
						ImGui::Text(("Box Thick: ")); ImGui::SameLine(TextSpaceLine);
						ImGui::SliderInt(("##BoxThick"), &menu::box_thick, 1.f, 3.f);
						ImGui::Text(("Crosshair Size:")); ImGui::SameLine(SpaceLineOne);
						ImGui::SliderFloat2(("##cross"), &menu::crosshair_size, 1.f, 100.f, "%.2f");
						ImGui::PopItemWidth();

					}ImGui::EndChild();
				}
			}

			else if (MenuTab == 2)
			{
				ImGui::SetCursorPos(ImVec2(10, 50));
				ImGui::Text(("Risky Features:"));
				ImGui::SetCursorPos(ImVec2(10, 70));
				ImGui::BeginChild(("##Misc1"), ImVec2(240.f, 200.f), true);
				{
					ImGui::Checkbox(("No Recoil"), &misc::norecoil);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(("No Spread"), &misc::nospread);

					ImGui::Checkbox(("No Sway"), &misc::nosway);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(("Fix EOKA"), &misc::notimeeoka);

					ImGui::Checkbox(("Spider Man"), &misc::peter_parker);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(("Admin Flag"), &misc::admin_flag);

					ImGui::Checkbox(("Players List"), &menu::player_list);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(("Outline"), &visuals::outline);

					ImGui::Checkbox(("Overlay FPS"), &menu::overlay_fps);
					ImGui::SameLine(120.f);
					ImGui::Checkbox(("Watermarker"), &menu::watermark);

					ImGui::Checkbox(("Lock at 60 fps (CPU Save)"), &menu::limit60);

					/*if (ImGui::Button(("Save Current Pos 1"), ImVec2(100, 25)))
					{
						visuals::SavePosition1 = visuals::CurrentPosition;
						Save_Settings(("C:\\Rust-Default.ini"));
					}*/
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(260, 50));
				ImGui::Text(("Colors:"));
				ImGui::SetCursorPos(ImVec2(260, 70));

				ImGui::BeginChild(("##Misc2"), ImVec2(-1.f, 200.f), true);
				{
					ImGui::PushItemWidth(170.f);
					ImGui::Text(("Crosshair: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##cross"), colors::crosscol);

					ImGui::Text(("ESP: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##esp"), colors::espcol);

					ImGui::Text(("Skeleton: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##skels"), colors::skelcol);

					ImGui::Text(("Crates: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##CRATESCOL"), colors::cratecol);

					ImGui::Text(("Collectables: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##COLLCOL"), colors::collcol);

					ImGui::Text(("Ore: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##ORECOL"), colors::orecol);

					ImGui::Text(("Scientist: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##SCICOL"), colors::scientistcol);

					ImGui::Text(("Items: ")); ImGui::SameLine(SpaceLineOne); ImGui::ColorEdit3(("##ITEMSCOL"), colors::itemscol);


					ImGui::Text(("Collect Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderInt(("##rainc2olors"), &visuals::MaxCollectableDistance, 0, 2000);

					ImGui::Text(("Crate Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderInt(("##raincolor1s"), &visuals::MaxCrateDistance, 0, 2000);

					ImGui::Text(("Ore Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderInt(("##raincolawor1s"), &visuals::MaxOreDistance, 0, 2000);

					ImGui::Text(("Scientist Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderInt(("##rainco213lawor121s"), &visuals::MaxScientistDistance, 0, 2000);

					ImGui::Text(("Skeleton Distance:")); ImGui::SameLine(SpaceLineOne); ImGui::SliderInt(("##rai2131wor1s"), &visuals::MaxSkeletonDrawDistance, 0, 300);


					ImGui::Text(("Rainbow Speed: ")); ImGui::SameLine(SpaceLineOne);
					ImGui::SliderFloat2(("##raincolors"), &rainbow_speed, 0.1f, 1.0f, "%.2f");
					ImGui::PopItemWidth();

					ImGui::PushItemWidth(120.f);
					ImGui::Text(("AirStruck Key: ")); ImGui::SameLine(120.f);
					HotkeyButton(hotkeys::airstuckey, ChangeKey2, keystatus);
					ImGui::PopItemWidth();
				}
				ImGui::EndChild();
			}

			//ImGui::SetCursorPos(ImVec2(100, 42));
			ImGui::BeginChild(("##Setts"), ImVec2(-1, 30.f));
			{

				ImGui::PushItemWidth(100.f);
				ImGui::Text(("Config: ")); ImGui::SameLine(60.f); ImGui::Combo(("##settsas"), &menu::settsMode, settsName, IM_ARRAYSIZE(settsName));

				ImGui::SameLine(170.f);

				if (ImGui::Button((("Save")), ImVec2(100, 20)))
				{
					if (menu::settsMode == 0)
						Save_Settings(("C:\\Rust-Default.ini"));
					if (menu::settsMode == 1)
						Save_Settings(("C:\\Rust-Setts1.ini"));
					if (menu::settsMode == 2)
						Save_Settings(("C:\\Rust-Setts2.ini"));
				}

				ImGui::SameLine(280.f);
				if (ImGui::Button((("Load")), ImVec2(100, 20)))
				{
					if (menu::settsMode == 0)
						Load_Settings(("C:\\Rust-Default.ini"));
					if (menu::settsMode == 1)
						Load_Settings(("C:\\Rust-Setts1.ini"));
					if (menu::settsMode == 2)
						Load_Settings(("C:\\Rust-Setts2.ini"));
				}
				ImGui::PopItemWidth();
			}ImGui::EndChild();
		}
		ImGui::End();
	}
	return true;
}
void render() {

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	shortcurts();

//	ESP();

	RGBA crosscolor = { colors::crosscol[0] * 255, colors::crosscol[1] * 255, colors::crosscol[2] * 255, 255 };

	if (menu::rainbow_colors)
		crosscolor = Col.rainbow();

	if (aimbot::fovcircle) {
		DrawCircle(Width / 2, Height / 2, aimbot::aimfov * 8, &crosscolor, 100);
	}

	if (menu::menu_key)
	{
		background();
		draw_abigsquare();
		ImGui::GetIO().MouseDrawCursor = 1;
	}
	else {
		ImGui::GetIO().MouseDrawCursor = 0;
	}

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}
	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&p_Params);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

WPARAM MainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();

	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanuoD3D();
	DestroyWindow(MyWnd);

	return Message.wParam;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		CleanuoD3D();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (p_Device != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			p_Params.BackBufferWidth = LOWORD(lParam);
			p_Params.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = p_Device->Reset(&p_Params);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
void CleanuoD3D()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL)
	{
		p_Object->Release();
	}
}
int isTopwin()
{
	HWND hWnd = GetForegroundWindow();
	if (hWnd == GameWnd)
		return TopWindowGame;
	if (hWnd == MyWnd)
		return TopWindowMvoe;

	return 0;
}
void SetWindowToTarget()
{
	while (true)
	{
		GameWnd = FindWindowW(TEXT("UnityWndClass"), NULL);
		if (GameWnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(GameWnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(MyWnd, GameRect.left, GameRect.top, Width, Height, true);
		}
	}
}

uintptr_t milliseconds_now() {
	static LARGE_INTEGER s_frequency;
	static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
	if (s_use_qpc) {
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return (1000LL * now.QuadPart) / s_frequency.QuadPart;
	}
	else {
		return GetTickCount();
	}
}
void LoadProtectedFunctions() {

	uintptr_t t = milliseconds_now();
	BYTE xorkey = 0x0;
	for (DWORD i = 0; i < 8; i++) {
		xorkey = ((BYTE*)&t)[i];
		if (xorkey > 0x3 && xorkey < 0xf0) {
			break;
		}
	}
	if (xorkey <= 0x3 || xorkey >= 0xf0) {
		xorkey = 0x56;
	}

	addFunc({ GetAowProcId, (uintptr_t)milliseconds_now - (uintptr_t)GetAowProcId - 0x3, xorkey, false });

	addFunc({ GetBaseAddress, (uintptr_t)GetBaseAddress - (uintptr_t)GetBaseAddress - 0x3, xorkey, false });
	//addFunc({ read, (uintptr_t)read - (uintptr_t)read - 0x3, xorkey, false });

	for (size_t i = 0; i < funcCount; i++) {
		if (functions[i].address != LoadProtectedFunctions)
			Protect(functions[i].address);
	}
	Unprotect(_ReturnAddress());
}

bool verify_game() {

	Unprotect(kernel_control_function);
	m_driver_control = kernel_control_function();
	Protect(kernel_control_function);

	if (!m_driver_control)
		return false;

	Unprotect(GetAowProcId);
	m_pid = GetAowProcId();
	Protect(GetAowProcId);

	printf(("[+] GamePid : %d[+] \n"), m_pid);

	if (!m_pid)
		return false;

	Unprotect(GetCurrentProcessId);
	usermode_pid = GetCurrentProcessId();
	Protect(GetCurrentProcessId);

	printf(("[+] UserMode Pid : %d[+] \n"), usermode_pid);

	Unprotect(GetBaseAddress);
	m_base = GetBaseAddress();
	Protect(GetBaseAddress);
	printf("[+] BaseAddress : %llx[+] \n", m_base);

	Unprotect(UnityPlayer);
	m_unityplayer = UnityPlayer("UnityPlayer.dll");
	Protect(UnityPlayer);
	printf("[+] UnityPlayer : %llx[+] \n", m_unityplayer);

	static const auto game_obj_mgr_addr = find_signature(m_unityplayer, "\x48\x89\x05\x00\x00\x00\x00\x48\x83\xc4\x38\xc3\x48\xc7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x48\x83\xc4\x38\xc3\xcc\xcc\xcc\xcc\xcc\x48", "xxx????xxxxxxxx????????xxxxxxxxxxx");

	game_object_manager = read<uint64_t>(m_unityplayer + game_obj_mgr_addr);

	return true;
}
int main() {

	printf("Protecting\n");
	LoadProtectedFunctions();
	Protect(LoadProtectedFunctions);

	while (true) {

		SetupWindow();
		DirectXInit(MyWnd);

		verify_game();

	/*	HANDLE hdl = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(cache), nullptr, NULL, nullptr);
		CloseHandle(hdl);*/

		MainLoop();
	}
}