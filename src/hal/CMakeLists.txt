set(CMAKE_INCLUDE_CURRENT_DIR True)

add_library(hal SHARED hal_lib.c)
set_property(TARGET hal PROPERTY POSITION_INDEPENDENT_CODE ON)
get_uspace_config(hal)
target_include_directories(hal PUBLIC .)
target_link_libraries(hal
        PRIVATE
        ulapi)

set_target_properties(hal PROPERTIES POSITION_INDEPENDENT_CODE ON)


add_library(_hal SHARED halmodule.cc)
target_link_libraries(_hal PRIVATE hal)
target_include_directories(_hal PUBLIC Python3::Python)
target_link_libraries(_hal
        PRIVATE
        Threads::Threads
        Python3::Python
        rt
        ulapi
        )
set_target_properties(_hal PROPERTIES PREFIX "")
get_uspace_config(_hal)

add_executable(halcmd
        utils/halcmd.c
        utils/halcmd_commands.cc
        utils/halcmd_main.c
        utils/halcmd_completion.c
        )
target_include_directories(halcmd
        PUBLIC .
        PRIVATE
        ${TCL_INCLUDE_PATH}
        ${READLINE_INCLUDE}
        )
target_link_libraries(halcmd
        PRIVATE
        ${TCL_LIBRARY}
        ${READLINE_LIBRARIES}
        inifile
        hal
        rt
        ulapi)
get_uspace_config(halcmd)

set(HALSH_SOURCES
        utils/halcmd.c
        utils/halcmd_commands.cc
        utils/halsh.c
        )
add_library(halsh SHARED ${HALSH_SOURCES})
target_include_directories(halsh
        PRIVATE
        ${READLINE_INCLUDE}
        ${TCL_INCLUDE_PATH}
        )
target_link_libraries(halsh
        PRIVATE
        ${READLINE_LIBRARIES}
        ${TCL_LIBRARY}
        hal
        inifile
        ulapi)
get_uspace_config(halsh)

add_executable(halstreamer components/streamer_usr.c)
target_link_libraries(halstreamer PRIVATE hal ulapi)
get_uspace_config(halstreamer)

add_executable(halsampler components/sampler_usr.c)
target_link_libraries(halsampler PRIVATE hal ulapi)
get_uspace_config(halsampler)

add_executable(halrmt utils/halrmt.c)
target_link_libraries(halrmt
        PRIVATE
        hal
        ulapi
        inifile)
get_uspace_config(halrmt)

set(HALMETER_SOURCES
        utils/meter.c
        utils/miscgtk.c
        )
add_executable(halmeter ${HALMETER_SOURCES})
target_include_directories(halmeter
        PRIVATE
        ${GTK3_INCLUDE_DIRS}
        ${Intl_INCLUDE_DIRS}
        )
target_link_libraries(halmeter
        PRIVATE
        hal
        ${GTK3_LIBRARIES}
        ${Intl_LIBRARIES}
        ulapi
        )
get_uspace_config(halmeter)

add_executable(halscope
        utils/scope.c
        utils/scope_horiz.c
        utils/scope_vert.c
        utils/scope_trig.c
        utils/scope_disp.c
        utils/scope_files.c
        utils/miscgtk.c
        )
target_include_directories(halscope
        PRIVATE
        ${GTK3_INCLUDE_DIRS}
        ${Intl_INCLUDE_DIRS}
        )
target_link_libraries(halscope
        PRIVATE
        hal
        m
        ${GTK3_LIBRARIES}
        ${Intl_LIBRARIES}
        ulapi
        )
get_uspace_config(halscope)

if(USE_RTAI)
    add_executable(pci_write
            utils/pci_write.c
            utils/upci.c
            )

    add_executable(pci_read
            utils/pci_read.c
            utils/upci.c
            )
endif()

add_custom_command(OUTPUT halcompile
        COMMAND yapps2 ${CMAKE_CURRENT_SOURCE_DIR}/utils/halcompile.g ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/halcompile
        COMMAND chmod +x ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/halcompile
        DEPENDS utils/halcompile.g)
add_custom_target(halcompile_script ALL DEPENDS halcompile)
