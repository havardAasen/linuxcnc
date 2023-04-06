add_library(emcmodule SHARED extensions/emcmodule.cc)
target_link_libraries(emcmodule
        PRIVATE
        Python3::Python
        nmlintf
        nml
        ulapi
        emc_inifile
        tooldata
        ${EPOXY_LIBRARIES})
get_uspace_config(emcmodule)

set_target_properties(emcmodule PROPERTIES POSITION_INDEPENDENT_CODE ON
                                           PREFIX ""
                                           LIBRARY_OUTPUT_NAME linuxcnc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(_togl SHARED extensions/_toglmodule.c)
target_include_directories(_togl
        PRIVATE
        ${TCL_INCLUDE_PATH}
        Python3::Python
        ${TCL_LIBRARY}
        ${TK_LIBRARY}
        X11::Xmu)

set_target_properties(_togl PROPERTIES PREFIX "")