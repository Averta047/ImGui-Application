#include "CGui.h"
#include "CDirectX.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "addons/imgui_addons.h"

#include "../../resources/fonts/open_sans_regular.h"

CGui::CGui()
{
    m_hWnd              = 0;
    m_pDevice           = 0;
    m_pDeviceContext    = 0;
}

CGui::~CGui()
{
}

bool CGui::Initialize(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    if (!hwnd)
        return false;
    
    if (!device)
        return false;
    
    if (!device_context)
        return false;

    m_hWnd = hwnd;
    m_pDevice = device;
    m_pDeviceContext = device_context;
    
    bool result = true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.IniFilename = nullptr;               // Disable INI File  
    GImGui->NavDisableHighlight = true;     // Disable Highlighting

    if (!GImGui->NavDisableHighlight)
    {
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    }

    // Setup Dear ImGui default style
    ImGui::StyleColorsDark();

    // Custom Styles
    style.WindowRounding    = 8;
    style.ChildRounding     = 6;
    style.FrameRounding     = 4;
    style.GrabRounding      = 3;
    style.PopupRounding     = 6;
    style.TabRounding       = 4;
    style.ScrollbarRounding = 3;

    style.ButtonTextAlign   = { 0.5f, 0.5f };
    style.WindowTitleAlign  = { 0.5f, 0.5f };
    style.FramePadding      = { 8.0f, 8.0f };
    style.WindowPadding     = { 10.0f, 10.0f };
    style.ItemSpacing       = style.WindowPadding;
    style.ItemInnerSpacing  = { style.WindowPadding.x, 6 };

    style.WindowBorderSize  = 1;
    style.FrameBorderSize   = 1;

    style.ScrollbarSize     = 12.f;
    style.GrabMinSize       = style.FrameRounding;
    
    // Custom Colors
    style.Colors[ImGuiCol_WindowBg]             = ImAdd::HexToColorVec4(0x000000, 0.75f);

    // Setup Font
    io.Fonts->AddFontFromMemoryCompressedTTF(open_sans_regular_compressed_data, open_sans_regular_compressed_size, 16, nullptr, io.Fonts->GetGlyphRangesDefault());

    // Setup Platform/Renderer backends
    result &= ImGui_ImplWin32_Init(hwnd);
    result &= ImGui_ImplDX11_Init(device, device_context);

	return result;
}

void CGui::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CGui::Render(const char* title, POINTS size, bool* b_open)
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    {
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(size.x, size.y), ImGuiCond_Always);
        ImGui::Begin(title, b_open, ImGuiWindowFlags_NoDecoration);
        {
            ImGui::Text("Hello World !");
        }
        ImGui::End();
    }
    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool CGui::IsGuiMoving()
{
    return GImGui->MovingWindow;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CGui::MsgProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    return ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam);
}
