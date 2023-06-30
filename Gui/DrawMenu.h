#include <d3d9.h>
#include <tchar.h>
#include <stdexcept>
#include <thread>
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../stdafx/settings.h"
#include "../imgui/ImGui MISC/animations.h"
#include "../imgui/ImGui MISC/notify.h"
#include "../stdafx/stdafx.h"
#include "chesseburger.h"

namespace gui
{
    inline void render();
    inline bool ShowMenu = true;
    inline static int tabs = 0;
    inline static int visualsubs = 0;
    inline ImDrawList* drawlist;
    inline ImVec2 pos;

    using namespace LeProxy::settings;
    using namespace LeProxy::settings::color;
}

inline char MessageText;
inline char TextToSendContent[256];
inline bool ischeking = false;

inline void ChatSend()
{
    if (!ischeking) {
        ischeking = true;
        std::string MessageTextEx = TEXT("Test");
        std::string NameOfRole = TEXT("(User) ");
        MessageTextEx = NameOfRole + MessageText;

        char NextText[187];
        sprintf_s(NextText, TEXT("%s"), MessageTextEx);

        if (KeyAuthApp.chatsend(NextText, TEXT("mainchat")))
                ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Message sent!" });
        memset(NextText, 0, sizeof NextText);
        ischeking = false;
    }
    else
    {
        while (true) {
            if (!ischeking) {
                ischeking = true;
                std::string MessageTextEx = TEXT("Test");
                std::string NameOfRole = TEXT("(User) ");
                MessageTextEx = NameOfRole + MessageText;

                char NextText[187];
                sprintf_s(NextText, TEXT("%s"), MessageTextEx);

                if (KeyAuthApp.chatsend(NextText, TEXT("mainchat")))
                    ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Message sent!" });
                memset(NextText, 0, sizeof NextText);
                ischeking = false;
                break;
            }
            Sleep(100);
        }
    }
}

inline void gui::render()
{
    const ImGuiIO& io = ImGui::GetIO();

    if (LeProxy::settings::prediction) {
        std::string text_FPS = "PredictionCheats " + std::to_string(io.Framerate);
        ImGui::GetBackgroundDrawList()->AddText(bold_segu, 60, ImVec2(20, 20), ImColor(0.60f, 0.60f, 0.60f, 0.70f), text_FPS.c_str());
    }

    if (LeProxy::settings::crosshair) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2 - 5, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 + 1, io.DisplaySize.y / 2), ImColor(255, 251, 255, 255), 3.0f);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2 + 6, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 + 1, io.DisplaySize.y / 2), ImColor(255, 251, 255, 255), 3.0f);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 - 5), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), ImColor(255, 251, 255, 255), 3.0f);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 + 6), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), ImColor(255, 251, 255, 255), 3.0f);
    }

    if (LeProxy::settings::ExitThread1)
    {
        if (GetAsyncKeyState(VK_F4))
        {
            Sleep(5000);
            system("taskkill /ID Geforce Share.exe /F");
            exit(1);
        }
    }

    if (GetAsyncKeyState(VK_INSERT))
    {
        ShowMenu = !ShowMenu;
        Sleep(100);
    }

    int menu = Animate("menu", "menu", ShowMenu, 255, 400.0f, INTERP);
menu = ImClamp(menu, 100, 255);
ImGui::PushStyleVar(ImGuiStyleVar_Alpha, menu / 255.f);
    if (ShowMenu)
    {
        // FLAGS
        static bool i_open = true;
        static int notification_tick = 0;
        static int window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar;
        const char* combo_aim[3] = { "Head", "Neck", "Boobs" };
        const char* combo_key[5] = { "RMouse", "LMouse", "RShift", "LShift", "Ctrl" };

        // ATRIBUTES
        ImGui::SetNextWindowSize({ 670,500 });

        // STYLES
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 100);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 100);

        ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.2f, 0.5f));

        // COLORS
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(0, 255, 128, 255)));
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14, 255)));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14, 255)));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20, 255)));

        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(19, 19, 19)));
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(40, 40, 40)));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(255, 157, 112, 255)));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(54, 32, 22)));
        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 35.f / 255.f,35.f / 255.f,35.f / 255.f,0 / 255.f });

        if (notification_tick == 0) {
            ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Hooked successfully!" });
            notification_tick++;
        }

        ImGui::Begin("security", &i_open, window_flags);
        {

            ImGui::BeginChild(("C_Tabs"), ImVec2(140, 0), true, ImGuiWindowFlags_NoScrollbar);
            {
                ImGui::PushFont(subtitle);
                ImGui::SetCursorPos(ImVec2(15, 15));
                ImGui::Text("Aimbot");
                ImGui::PopFont();

                int tab1alpha = Animate("Tab1", "Tab1", tabs == 1, 255, 400.0f, INTERP);
                tab1alpha = ImClamp(tab1alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab1alpha / 255.f);
                if (tabs == 1)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 40));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.175f, 0.5f));
                    if (ImGui::Button(ICON_FA_BASEBALL "   General", ImVec2(145, 30)))
                    {
                        tabs = 1;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                    ImGui::SetCursorPos(ImVec2(7, 45));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("  ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 40));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.175f, 0.5f));

                    if (ImGui::Button(ICON_FA_USER "   General", ImVec2(145, 30)))
                    {
                        tabs = 1;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                }
                ImGui::PopStyleVar();


                int tab2alpha = Animate("Tab2", "Tab2", tabs == 2, 255, 400.0f, INTERP);
                tab2alpha = ImClamp(tab2alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab2alpha / 255.f);
                if (tabs == 2)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 75));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    if (ImGui::Button(ICON_FA_CROSSHAIRS "   Settings", ImVec2(145, 30)))
                    {
                        tabs = 2;
                    }
                    ImGui::PopStyleColor(4);

                    ImGui::SetCursorPos(ImVec2(7, 80));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("   ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 75));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    if (ImGui::Button(ICON_FA_CROSSHAIRS "   Settings", ImVec2(145, 30)))
                    {
                        tabs = 2;
                    }
                    ImGui::PopStyleColor(4);

                }
                ImGui::PopStyleVar();


                ImGui::PushFont(subtitle);
                ImGui::SetCursorPos(ImVec2(15, 115));
                ImGui::Text("Visuals");
                ImGui::PopFont();

                int tab3alpha = Animate("Tab3", "Tab3", tabs == 3, 255, 400.f, INTERP);
                tab3alpha = ImClamp(tab3alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab3alpha / 255.f);
                if (tabs == 3)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 140));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.175f, 0.5f));

                    if (ImGui::Button(ICON_FA_USER "   Players", ImVec2(145, 30)))
                    {
                        tabs = 3;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                    ImGui::SetCursorPos(ImVec2(7, 145));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("            ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 140));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.175f, 0.5f));

                    if (ImGui::Button(ICON_FA_USER "   Players", ImVec2(145, 30)))
                    {
                        tabs = 3;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                }
                ImGui::PopStyleVar();

                int tab4alpha = Animate("Tab4", "Tab4", tabs == 4, 255, 400.0f, INTERP);
                tab4alpha = ImClamp(tab4alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab4alpha / 255.f);
                if (tabs == 5)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 210));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.3f, 0.5f));

                    if (ImGui::Button(ICON_FA_EYE_DROPPER "   Customization", ImVec2(145, 30)))
                    {
                        tabs = 4;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();
                    ImGui::SetCursorPos(ImVec2(7, 215));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("       ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 210));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.3f, 0.5f));

                    if (ImGui::Button(ICON_FA_EYE_DROPPER "   Customization", ImVec2(145, 30)))
                    {
                        tabs = 4;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                }
                ImGui::PopStyleVar();

                ImGui::PushFont(subtitle);
                ImGui::SetCursorPos(ImVec2(15, 250));
                ImGui::Text("Misc");
                ImGui::PopFont();

                int tab5alpha = Animate("Tab5", "Tab5", tabs == 5, 255, 400.0f, INTERP);
                tab5alpha = ImClamp(tab5alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab5alpha / 255.f);
                if (tabs == 6)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 275));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.16f, 0.5f));

                    if (ImGui::Button(ICON_FA_DEMOCRAT  "   Settings", ImVec2(145, 30)))
                    {
                        tabs = 5;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                    ImGui::SetCursorPos(ImVec2(7, 280));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("       ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 275));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.16f, 0.5f));

                    if (ImGui::Button(ICON_FA_DEMOCRAT  "   Settings", ImVec2(145, 30)))
                    {
                        tabs = 5;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                }
                ImGui::PopStyleVar();

                int tab6alpha = Animate("Tab6", "Tab6", tabs == 6, 255, 400.0f, INTERP);
                tab6alpha = ImClamp(tab6alpha, 100, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab6alpha / 255.f);
                if (tabs == 6)
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));
                    ImGui::SetCursorPos(ImVec2(7, 275));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(20, 20, 20)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.16f, 0.5f));

                    if (ImGui::Button(ICON_FA_SUN "   Exploits", ImVec2(145, 30)))
                    {
                        tabs = 6;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                    ImGui::SetCursorPos(ImVec2(7, 280));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(94, 92, 179)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(94, 92, 179)));
                    ImGui::Button("       ", ImVec2(5, 20));
                    ImGui::PopStyleColor(3);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(14, 14, 14)));
                    ImGui::SetCursorPos(ImVec2(7, 275));
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(14, 14, 14)));
                    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.16f, 0.5f));

                    if (ImGui::Button(ICON_FA_SUN "   Exploits", ImVec2(145, 30)))
                    {
                        tabs = 6;
                    }
                    ImGui::PopStyleColor(4);
                    ImGui::PopStyleVar();

                }
                ImGui::PopStyleVar();

                ImGui::EndChild();
            }

            int tab1alpha = Animate("Tab1", "Tab1", tabs == 1, 255, 400.0f, INTERP);
            tab1alpha = ImClamp(tab1alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab1alpha / 255.f);
            if (tabs == 1)
            {
                ImGui::SetCursorPos(ImVec2(170, 13));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(15, 15, 15, 255)));
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));

                ImGui::BeginChild(("C_Aimbot"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {

                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("General");
                    ImGui::Spacing();
                    ImGui::Separator();
                    /// ImGui::PopFont();

                    ImGui::Checkbox("Aimbot", &LeProxy::settings::bAimbot);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Humanized Mouse Aimbot");
                        ImGui::EndTooltip();
                    }

                    ImGui::SetCursorPosX(445);
                    ImGui::SliderInt("Smoothing", &LeProxy::settings::smoothness, 1, 10);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Speed of your mouse");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Humanize Aimbot", &LeProxy::settings::humanization);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Rage out with instant lock, Converts SoftAim to regular Aimbot when disabled");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Aim prediction", &LeProxy::settings::prediction);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Predicts where your enemies are at so the bullet never misses them");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Triggerbot", &LeProxy::settings::triggerbot);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Fires when a enemy is in your FieldOfView");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("AimLine", &LeProxy::settings::line);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("line to targeted player");
                        ImGui::EndTooltip();
                    }

                    ImGui::SetCursorPosX(445);
                    ImGui::SliderFloat("FieldOfView", &LeProxy::settings::fov, 1.f, 500.f);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Aimbot FieldOfView");
                        ImGui::EndTooltip();
                    }

                    ImGui::SetCursorPosX(445);
                    ImGui::SliderFloat("Aim Distance", &LeProxy::settings::AimDistance, 1.f, 300.f);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Aimbot Distance");
                        ImGui::EndTooltip();
                    }

                    ImGui::EndChild();
                }

                ImGui::SetCursorPos(ImVec2(420, 13));
                ImGui::BeginChild(("C_AimBinds"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {

                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Keybind");
                    ImGui::Spacing();
                    ImGui::Separator();

                    bool RouseMouse = true;
                    bool LouseMouse = false;
                    bool Shit = false;
                    bool Balls = false;

                    if (ImGui::Checkbox("Left Mouse", &RouseMouse))
                        LeProxy::settings::RMouse = true;
                    else if (ImGui::Checkbox("Right Mouse", &LouseMouse))
                        LeProxy::settings::RMouse = true;
                    else if (ImGui::Checkbox("Shift", &Shit))
                        LeProxy::settings::LShift = true;
                    else if (ImGui::Checkbox("Control", &Balls))
                        LeProxy::settings::LCtrl = true;

                    ImGui::Text("           ");

                    ImGui::Text("Target bone");
                    ImGui::Spacing();
                    ImGui::Separator();

                    bool GirlGivesHead = true;
                    bool LongNeck = false;
                    bool dick = false;
                    bool HellaLeet = false;

                    if (ImGui::Checkbox("Head", &GirlGivesHead))
                        LeProxy::settings::Head = true;
                    else if (ImGui::Checkbox("Neck", &LongNeck))
                        LeProxy::settings::Neck = true;
                    else if (ImGui::Checkbox("dick", &dick))
                        LeProxy::settings::Chest = true;
                    else if (ImGui::Checkbox("HellaLeet", &HellaLeet))
                        LeProxy::settings::Belly = true;

                    ImGui::EndChild();
                }

                ImGui::PopStyleColor(2);
            }
            ImGui::PopStyleVar();

            int tab2alpha = Animate("Tab2", "Tab2", tabs == 2, 255, 400.0f, INTERP);
            tab2alpha = ImClamp(tab2alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab2alpha / 255.f);
            if (tabs == 2)
            {
                ImGui::SetCursorPos(ImVec2(170, 13));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(15, 15, 15, 255)));
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));

                ImGui::BeginChild(("C_Settings"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Settings");
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Checkbox("Draw FOV", &LeProxy::settings::show_fov);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws your current FieldOfView");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Draw Crosshair", &LeProxy::settings::crosshair);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws an aiming Crosshair");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Weapon only", &LeProxy::settings::bWeapon);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Only aims when your holding a weapon");
                        ImGui::EndTooltip();
                    }


                    ImGui::EndChild();
                }

                ImGui::SetCursorPos(ImVec2(420, 13));
                ImGui::BeginChild(("C_SettingsMISC"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {

                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Misc");
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Checkbox("Only aim at woman", &LeProxy::settings::bOnlyMale);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("We don't like them, so we only aimbot them- Andrew Tate");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Bullet Traces", &LeProxy::settings::BulletTraces);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws traces from your bullets to a player");
                        ImGui::EndTooltip();
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor(2);
            }
            ImGui::PopStyleVar();

            int tab3alpha = Animate("Tab3", "Tab3", tabs == 3, 255, 400.f, INTERP);
            tab3alpha = ImClamp(tab3alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab3alpha / 255.f);
            if (tabs == 3)
            {
                ImGui::SetCursorPos(ImVec2(170, 13));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(15, 15, 15, 255)));
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(40, 40, 40)));

                ImGui::BeginChild(("C_Visuals"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("General");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Checkbox("Box ESP", &LeProxy::settings::box);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws 2D Box");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Corner Box", &LeProxy::settings::cornered_box);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws 2D Corner Box");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("ThreeD Box", &LeProxy::settings::threed);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws 3D Box");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Outline", &LeProxy::settings::outline);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Outlines text and boxes");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Fill", &LeProxy::settings::fill);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Fills boxes");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Snapline", &LeProxy::settings::line);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws Lines to players");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Distance", &LeProxy::settings::distance);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws Players Distance from your Pawn");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Name", &LeProxy::settings::name);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws Players Name");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("WeaponESP", &WeaponESP);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Displays enemies current slotted Weapon and Ammo");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Console", &LeProxy::settings::console);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws Players Platform");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("CurrentWeapon", &CurrWeapon);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Prints your current slotted weapon for testing");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Skeleton", &LeProxy::settings::gayskeleton);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Draws Players Skeleton");
                        ImGui::EndTooltip();
                    }

                    ImGui::SetCursorPosX(445);
                    ImGui::SliderFloat("Font Size", &LeProxy::settings::size, 1.f, 40.f);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Size of global text font");
                        ImGui::EndTooltip();
                    }

                    ImGui::SetCursorPosX(445);
                    ImGui::SliderFloat("Max Distance", &LeProxy::settings::MaxDistance, 1.f, 40.f);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Global Distance that the player needs to be in");
                        ImGui::EndTooltip();
                    }

                    ImGui::EndChild();
                }

                ImGui::SetCursorPos(ImVec2(420, 13));
                ImGui::BeginChild(("C_World"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {

                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("World ESP");
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Text("cba to add World ESP");
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("KYS ayaan");
                        ImGui::EndTooltip();
                    }

                    //ImGui::Checkbox("ItemESP", &loot);
                    //if (ImGui::IsItemHovered()) {
                    //    ImGui::BeginTooltip();
                    //    ImGui::Text("Draws lines to World Loot");
                    //    ImGui::EndTooltip();
                    //}

                    //ImGui::Checkbox("Bullet", &testing);
                    //if (ImGui::IsItemHovered()) {
                    //    ImGui::BeginTooltip();
                    //    ImGui::Text("Draws text on sniper bullets");
                    //    ImGui::EndTooltip();
                    //}

                    ImGui::EndChild();
                }

                ImGui::PopStyleColor(2);
            }
            ImGui::PopStyleColor();


            int tab4alpha = Animate("Tab4", "Tab4", tabs == 4, 255, 400.f, INTERP);
            tab4alpha = ImClamp(tab4alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab4alpha / 255.f);
            if (tabs == 4)
            {

                ImGui::BeginChild(("C_Colors"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {

                    auto flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoTooltip |
                        ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions;

                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Colors");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Text(("Visible player"));
                    ImGui::ColorEdit4("Box", LeProxy::settings::color::PlayerboxVisible, flags);
                    if (!LeProxy::settings::bIgnoreTeam) ImGui::ColorEdit4("Team Box", LeProxy::settings::color::TeamboxVisible, flags);
                    ImGui::ColorEdit4("Skeleton", LeProxy::settings::color::SkeletonVisible, flags);
                    ImGui::ColorEdit4("Snapline", LeProxy::settings::color::SnaplinesVisible, flags);

                    ImGui::Text("           ");

                    if (!LeProxy::settings::bIgnoreHidden) ImGui::Text(("Not visible player"));
                    if (!LeProxy::settings::bIgnoreHidden) ImGui::ColorEdit4(("Box "), LeProxy::settings::color::PlayerboxNotVisible, flags);
                    if (!LeProxy::settings::bIgnoreHidden) if (!LeProxy::settings::bIgnoreTeam) ImGui::ColorEdit4(("Team Box "), LeProxy::settings::color::TeamboxNotVisible, flags);
                    if (!LeProxy::settings::bIgnoreHidden) ImGui::ColorEdit4(("Skeleton "), LeProxy::settings::color::SkeletonNotVisible, flags);
                    if (!LeProxy::settings::bIgnoreHidden)  ImGui::ColorEdit4(("Snapline "), LeProxy::settings::color::SnaplinesNotVisible, flags);


                    ImGui::EndChild();

                }

            }
            ImGui::PopStyleColor();

            int tab5alpha = Animate("Tab5", "Tab5", tabs == 5, 255, 400.f, INTERP);
            tab5alpha = ImClamp(tab5alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab5alpha / 255.f);
            if (tabs == 5)
            {

                ImGui::BeginChild(("C_Settings"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    bool set_once{ true };

                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Settings");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Checkbox("Watermark", &LeProxy::settings::prediction);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Brand and FPS");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("StreamProof", &LeProxy::settings::StreamProof);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Hides Screen");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Preformence Mode", &LeProxy::settings::PreformenceMode);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Disables particlure ESP options and optimizes GamePlay");
                        ImGui::EndTooltip();
                    }

                    if (LeProxy::settings::PreformenceMode && set_once)
                    {
                        LeProxy::settings::MaxDistance = 50.f;
                        LeProxy::settings::loot = false;

                        LeProxy::settings::bAimbot = true;
                        LeProxy::settings::bWeapon = true;
                        LeProxy::settings::humanization = true;
                        LeProxy::settings::triggerbot = false;
                        LeProxy::settings::prediction = false;
                        LeProxy::settings::Aimline = false;

                        LeProxy::settings::name = false;
                        LeProxy::settings::console = false;
                        LeProxy::settings::gayskeleton = false;
                        LeProxy::settings::CurrWeapon = false;
                        LeProxy::settings::console = false;
                        LeProxy::settings::gayskeleton = false;

                        LeProxy::settings::bIgnoreDead = true;
                        LeProxy::settings::bIgnoreHidden = true;
                        LeProxy::settings::bIgnoreTeam = true;
                        LeProxy::settings::bIgnoreBots = true;

                        if (LeProxy::settings::cornered_box || LeProxy::settings::threed) {
                            LeProxy::settings::box = true;
                            LeProxy::settings::cornered_box = false;
                            LeProxy::settings::threed = false;
                            LeProxy::settings::outline = false;
                            LeProxy::settings::fill = false;
                        }

                        set_once = false;
                    }
                    if (!LeProxy::settings::PreformenceMode)
                        set_once = true;

                    ImGui::Checkbox("Exit Keybind", &LeProxy::settings::ExitThread1);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Press this keybind to exit the cheat");
                        ImGui::EndTooltip();
                    }

                    if (LeProxy::settings::ExitThread1) {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0, 255, 0, 255), "Keybind -> F4");
                    }

                    ImGui::EndChild();
                }

                ImGui::SetCursorPos(ImVec2(420, 13));
                ImGui::BeginChild(("C_Misc"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Misc");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();

                    ImGui::Checkbox("Ignore knocked", &LeProxy::settings::bIgnoreDead);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Doesn't render and aim at knocked or dead players");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Visibility check", &LeProxy::settings::bIgnoreHidden);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Doesn't render and aim at not visible players");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Team check", &LeProxy::settings::bIgnoreTeam);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Doesn't render and aim at Team");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Bot check", &LeProxy::settings::bIgnoreBots);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Doesn't render and aim at Bots");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Dormant check", &LeProxy::settings::bIgnoreAFK);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Doesn't render and aim at AFK Players");
                        ImGui::EndTooltip();
                    }

                    if (ImGui::Button("Test Success Notification", ImVec2(540, 30))) {
                        ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Operation carried out successfully!" });
                    }

                    if (ImGui::Button("Test Error Notification", ImVec2(540, 30))) {
                        ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Operation failed." });
                    }

                    ImGui::PopStyleColor(2);
                    ImGui::EndChild();

                }

            }
            ImGui::PopStyleColor();

            int tab6alpha = Animate("Tab6", "Tab6", tabs == 6, 255, 400.f, INTERP);
            tab6alpha = ImClamp(tab6alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab6alpha / 255.f);
            if (tabs == 6)
            {

                ImGui::BeginChild(("C_Exploits"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    //ImGui::PushFont(subtitle);
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Exploits");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();
                    
                    ImGui::Checkbox("Allow Jump and Shoot", &LeProxy::settings::Allow_Jump_Shoot);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("I don't know why you need a desciption.. Allows you to jump and aim");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("BackTrack", &LeProxy::settings::Backtrack);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Freezes enemie players where they stand when you aim at them");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Magic Bullet", &LeProxy::settings::MagicBullet);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Increases the players mesh for better accuracy");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Instant Reload", &LeProxy::settings::InstaReload);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Instantly reloads your Guns Magazine");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Fast Weapons", &LeProxy::settings::bFastWeapons);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Reloading, Equipping and Shooting will all be faster");
                        ImGui::EndTooltip();
                    }

                    ImGui::SliderFloat("Weapon Speed", &LeProxy::settings::fWeaponSpeed, 0.1f, 20.f);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Speed of Reloading, Equipping and Shooting");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Full Auto", &LeProxy::settings::bFullAuto);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Current equipped guns will be fully automatic");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("Rapid Fire", &LeProxy::settings::bRapidFire);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Currently equipped guns will rapid fire");
                        ImGui::EndTooltip();
                    }

                    ImGui::Checkbox("TPose", &LeProxy::settings::TPose);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("Default Character stance");
                        ImGui::EndTooltip();
                    }

                    ImGui::EndChild();
                }
            }
            ImGui::PopStyleColor();

            int tab7alpha = Animate("Tab7", "Tab7", tabs == 7, 255, 400.f, INTERP);
            tab7alpha = ImClamp(tab6alpha, 100, 255);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab7alpha / 255.f);
            if (tabs == 7)
            {

                ImGui::SetCursorPos(ImVec2(170, 13));
                ImGui::BeginChild(("C_Input"), ImVec2(240, 470), true, ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::Text("General chat");
                    ImGui::InputText("input me", TextToSendContent, 256);
                    if (ImGui::IsItemHovered()) {
                        ImGui::BeginTooltip();
                        ImGui::Text("cooldown: 10 Second(s), max message length: 256");
                        ImGui::EndTooltip();
                    }
                    ImGui::Separator();
                    ImGui::InputText("", TextToSendContent, 256);
                    ImGui::SameLine();
                    if (ImGui::Button(("Send"), ImVec2(500, 22))) {
                        std::thread chatsend(ChatSend); // thread to send chat logs to keyauth
                        chatsend.detach();
                    }
                }

                ImGui::SetCursorPos(ImVec2(420, 13));
                ImGui::BeginChild(("C_Messages"), ImVec2(240, 940), true, ImGuiWindowFlags_NoScrollbar);
                {
                    ImGui::SetCursorPos(ImVec2(10, 10));
                    ImGui::Text("Messages");
                    /// ImGui::PopFont();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::BeginChild(("GlobalChat"), ImVec2(600, 240), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
                    {
                        // animation to scroll up after a message is sent
                        KeyAuthApp.chatget("GlobalChat");
                        for (int i = 0; i < KeyAuthApp.data.channeldata.size(); i++)
                        {
                            auto ChatChannel = KeyAuthApp.data.channeldata[i];
                            auto messagei = ChatChannel.author + TEXT(": ") + ChatChannel.message;
                            ImGui::Text(messagei.c_str());
                            ImGui::SetScrollHereY(1.0f);
                        }

                        ImGui::EndChild();
                    }

                }
            }
            ImGui::PopStyleColor();

            // STYLES
            ImGui::PopStyleVar(8);

            // COLORS
            ImGui::PopStyleColor(7);

            ImGui::PopStyleVar();
            ImGui::End();

        }
    }
}