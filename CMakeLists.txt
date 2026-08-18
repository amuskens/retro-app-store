cmake_minimum_required(VERSION 3.10)
project(Garden C)

add_application(Garden
    src/main.c
    src/app.c
    src/theme.c
    src/native.c
    src/catalog.c
    src/catalog_data.c
    src/catalog_load.c
    src/sidebar.c
    src/results_view.c
    src/toolbar.c
    src/dnr.c
    src/net.c
    src/ftp.c
    src/download.c
    src/progress_dlg.c
    src/prefs_dlg.c
    src/main.r
    CREATOR "GRDN"
)

set_target_properties(Garden PROPERTIES COMPILE_OPTIONS -ffunction-sections)
if(CMAKE_SYSTEM_NAME MATCHES Retro68)
    set_target_properties(Garden PROPERTIES LINK_FLAGS "-Wl,-gc-sections -Wl,--mac-single")
else()
    set_target_properties(Garden PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
endif()
