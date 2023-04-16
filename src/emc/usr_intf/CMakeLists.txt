add_library(linuxcnc SHARED
        emcsh.cc
        shcom.cc
        )
target_include_directories(linuxcnc
        PRIVATE
        ${TCL_INCLUDE_PATH})
target_link_libraries(linuxcnc
        PRIVATE
        ${TCL_LIBRARY}
        ${TK_LIBRARY}
        X11::Xinerama
        Python3::Python
        pythonplugin
        nml
        emc_nmlintf
        libnml_rcs
        libnml_posemath
        )
get_uspace_config(linuxcnc)

add_executable(linuxcncrsh
        emcrsh.cc
        shcom.cc)
target_link_libraries(linuxcncrsh
        PRIVATE
        nml
        emc_nmlintf
        halsh
        libnml_rcs
        libnml_posemath
        ulapi)
get_uspace_config(linuxcncrsh)

add_executable(schedrmt
        schedrmt.cc
        emcsched.cc
        shcom.cc)

target_link_libraries(schedrmt
        PRIVATE
        nml
        emc_nmlintf
        halsh
        ulapi
        libnml_posemath)
get_uspace_config(schedrmt)

add_executable(linuxcnclcd
        emclcd.cc
        shcom.cc
        sockets.c
        )
target_link_libraries(linuxcnclcd
        PRIVATE
        nml
        emc_nmlintf
        halsh
        ulapi)
get_uspace_config(linuxcnclcd)

add_executable(halui
        halui.cc
        )
target_link_libraries(halui
        PRIVATE
        nml
        emc_nmlintf
        libnml_posemath
        halsh
        ulapi
        hal
        emc_tooldata)
get_uspace_config(halui)

add_subdirectory(axis)
