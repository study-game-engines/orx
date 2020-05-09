/**
 * @file [name].cpp
 * @date [date]
 */

[+scroll #define __SCROLL_IMPL__
#include "[name].h"
#undef __SCROLL_IMPL__

#include "Object.h"]
[-scroll #include "orx.h"]
[+nuklear

#define orxNUKLEAR_IMPL
#include "orxNuklear.h"
#undef orxNUKLEAR_IMPL
]
[+imgui

#define orxIMGUI_IMPL
#include "orxImGui.h"
#undef orxIMGUI_IMPL]
[+archive

#define orxARCHIVE_IMPL
#include "orxArchive.h"
#undef orxARCHIVE_IMPL]

/** Update function, it has been registered to be called every tick of the core clock
 */
[+scroll void [name]::Update(const orxCLOCK_INFO &_rstInfo)]
[-scroll void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)]
{
    // Should quit?
    if(orxInput_IsActive("Quit"))
    {
        // Send close event
        orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
    }
}

/** Init function, it is called when all orx's modules have been initialized
 */
[+scroll orxSTATUS [name]::Init()]
[-scroll orxSTATUS orxFASTCALL Init()]
{
    // Display a small hint in console
    orxLOG("\n* This template project creates a simple scene"
    "\n* You can play with the config parameters in ../data/config/[name].ini"
    "\n* After changing them, relaunch the executable to see the changes.");

[+nuklear
    // Display additional Nuklear hint in console
    orxLOG("\n* This template has support for Nuklear.");

    // Initialize Dear ImGui
    orxNuklear_Init();
]
[+imgui
    // Display additional Dear ImGui hint in console
    orxLOG("\n* This template has support for Dear ImGui.");

    // Initialize Dear ImGui
    orxImGui_Init();
]
[+archive
    // Initialize archive (ZIP) resource type
    orxArchive_Init();
]
[+scroll
    // Create the scene
    CreateObject("Scene");]
[-scroll
    // Create the viewport
    orxViewport_CreateFromConfig("MainViewport");

    // Create the scene
    orxObject_CreateFromConfig("Scene");

    // Register the Update function to the core clock
    orxClock_Register(orxClock_Get(orxCLOCK_KZ_CORE), Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);]

    // Done!
    return orxSTATUS_SUCCESS;
}

/** Run function, it should not contain any game logic
 */
[+scroll orxSTATUS [name]::Run()]
[-scroll orxSTATUS orxFASTCALL Run()]
{
[+nuklear
    // Show a small Nuklear demo
    if(nk_begin(&sstNuklear.stContext, "Demo", nk_rect(50, 50, 200, 200), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static orxS32 Op = EASY;
        static orxS32 Property = 20;

        nk_layout_row_static(&sstNuklear.stContext, 30, 80, 1);
        if (nk_button_label(&sstNuklear.stContext, "button"))
        {
            orxLOG("Nuklear button pressed.");
        }
        nk_layout_row_dynamic(&sstNuklear.stContext, 30, 2);
        if(nk_option_label(&sstNuklear.stContext, "easy", Op == EASY))
        {
            Op = EASY;
        }
        if(nk_option_label(&sstNuklear.stContext, "hard", Op == HARD))
        {
            Op = HARD;
        }
        nk_layout_row_dynamic(&sstNuklear.stContext, 25, 1);
        nk_property_int(&sstNuklear.stContext, "Compression:", 0, &Property, 100, 10, 1);
    }
    nk_end(&sstNuklear.stContext);
]
[+imgui
    // Show Dear ImGui's demo and stats windows
    ImGui::ShowDemoWindow();
    ImGui::ShowMetricsWindow();
]
    // Return orxSTATUS_FAILURE to instruct orx to quit
    return orxSTATUS_SUCCESS;
}

/** Exit function, it is called before exiting from orx
 */
[+scroll void [name]::Exit()]
[-scroll void orxFASTCALL Exit()]
{
[+nuklear
    // Exits from Nuklear
    orxNuklear_Exit();
]
[+imgui
    // Exits from Dear ImGui
    orxImGui_Exit();
]
    // Let Orx clean all our mess automatically. :)
}

[+scroll
/** BindObjects function, ScrollObject-derived classes are bound to config sections here
 */
void [name]::BindObjects()
{
    // Bind the Object class to the Object config section
    ScrollBindObject<Object>("Object");
}
]
/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
[+scroll orxSTATUS [name]::Bootstrap() const]
[-scroll orxSTATUS orxFASTCALL Bootstrap()]
{
    // Add a config storage to find the initial config file
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
    return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
[+scroll
    // Execute our game
    [name]::GetInstance().Execute(argc, argv);]
[-scroll
    // Set the bootstrap function to provide at least one resource storage before loading any config files
    orxConfig_SetBootstrap(Bootstrap);

    // Execute our game
    orx_Execute(argc, argv, Init, Run, Exit);]

    // Done!
    return EXIT_SUCCESS;
}
