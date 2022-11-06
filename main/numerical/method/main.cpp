//#include <iostream>

#include "../menu/menu.h"
#include "../menu/font.h"

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE); //SW_SHOW

    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"_", NULL };
   // wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Numerical methods", WS_OVERLAPPEDWINDOW ^ WS_CAPTION, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup ImPlot
    ImPlot::CreateContext();

 
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Setup fonts
    auto config = ImFontConfig();
    config.FontDataOwnedByAtlas = false;
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font, sizeof(font), 14.0f, &config);

    // Our state
    bool show_demo_window = false;
    bool implot_demo = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
         if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 1.1 Show ImPlot Demo
         if (implot_demo)
             ImPlot::ShowDemoWindow(&implot_demo);

        //2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;


            float width = 0.0f, height = 0.0f;
            RECT rect;
            if (GetWindowRect(hwnd, &rect)) {
                width = rect.right - rect.left;
                height = rect.bottom - rect.top;
            }

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(300, height));
            ImGui::SetNextWindowBgAlpha(0.8f);
            ImGui::Begin("_tabs", nullptr, ImGuiWindowFlags_NoDecoration); {
                ImGui::BeginGroup(); {
                    ImGui::SetCursorPosY(120); ImGui::SetCursorPosX(30);
                    ImGui::Text("test-1-default");
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    ImGui::TextColored(ImVec4(158 / 255.f, 157 / 255.f, 161 / 255.f, 255), "test-text-colored");
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    ImGui::Button("test button", ImVec2(200, 40));
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    char buf[255]{};
                    ImGui::InputText("input text", buf, sizeof(buf));
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    float float_var = 0;
                    ImGui::SliderFloat("slider-float (1-10)", &float_var, 1, 10);
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    bool test = false;
                    ImGui::Checkbox("test cb", &test);
                    ImGui::SameLine();
                    ImGui::Checkbox("test cb-2", &test);
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    ImGui::Checkbox("test cb-3", &test);
                    ImGui::SameLine();
                    ImGui::Checkbox("test cb-4", &test);
                    ImGui::SetCursorPosX(30); ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                    ImGui::ColorPicker3("color picker", (float*)&clear_color);
                   
                }
                ImGui::EndGroup();
            }
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(300, 0));
            ImGui::SetNextWindowSize(ImVec2(width-310, height));
            ImGui::SetNextWindowBgAlpha(1.0f);

            ImGui::Begin("_", nullptr, ImGuiWindowFlags_NoDecoration); { 
                ImGui::Text("This is some useful text.");  
                
#ifdef _DEBUG
                ImGui::Checkbox("Demo Window", &show_demo_window);
                ImGui::Checkbox("Demo Plot Window", &implot_demo);
                ImGui::Checkbox("Another Window", &show_another_window);
#endif // DEBUG

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

                float samples[100];
                for (int n = 0; n < 100; n++)
                    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
                ImGui::PlotLines("Samples", samples, 100);

                ImGui::BeginTable("table1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
                {
                    bool display_headers = true;
                    if (display_headers)
                    {
                        ImGui::TableSetupColumn("One");
                        ImGui::TableSetupColumn("Two");
                       // ImGui::TableSetupColumn("Three");
                        ImGui::TableHeadersRow();
                    }

                    for (int row = 0; row < 5; row++)
                    {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 2; column++)
                        {
                            ImGui::TableSetColumnIndex(column);
                            char buf[32];
                            sprintf_s(buf, "Hello %d,%d", column, row);
                            ImGui::TextUnformatted(buf);
                        }
                    }
                    ImGui::EndTable();
                }
            }
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}