set(EMCSH_SOURCES
        emcsh.cc
        shcom.cc
        )

set(EMCRSH_SOURCES
        emcrsh.cc
        shcom.cc
        )

set(EMCSCHED_SOURCES
        schedrmt.cc
        emcsched.cc
        shcom.cc
        )

set(EMCLCD_SOURCES
        emclcd.cc
        shcom.cc
        sockets.c
        )
set(HALUI_SOURCES
        halui.cc
        )

add_library(linuxcnc SHARED ${EMCSH_SOURCES})
target_include_directories(linuxcnc
        PRIVATE
        ${TCL_INCLUDE_PATH}
        ${TCL_LIBRARY}
        ${TK_LIBRARY}
        X11::Xinerama
        Python3::Python
        pythonplugin
        nml
        nmlintf
        emc_inifile)
get_uspace_config(linuxcnc)

add_executable(linuxcncrsh ${EMCRSH_SOURCES})
target_link_libraries(linuxcncrsh
        PRIVATE
        nml
        nmlintf
        emc_inifile
        halsh
        ulapi)
get_uspace_config(linuxcncrsh)

add_executable(schedrmt ${EMCSCHED_SOURCES})
target_link_libraries(schedrmt
        PRIVATE
        nml
        nmlintf
        emc_inifile
        halsh
        ulapi)
get_uspace_config(schedrmt)

add_executable(linuxcnclcd ${EMCLCD_SOURCES})
target_link_libraries(linuxcnclcd
        PRIVATE
        nml
        nmlintf
        emc_inifile
        halsh
        ulapi)
get_uspace_config(linuxcnclcd)

add_executable(halui ${HALUI_SOURCES})
target_link_libraries(halui
        PRIVATE
        nml
        nmlintf
        emc_inifile
        halsh
        ulapi
        hal
        tooldata)
get_uspace_config(halui)

add_subdirectory(axis)
