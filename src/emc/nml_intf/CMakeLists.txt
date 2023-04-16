add_library(emc_nmlintf STATIC
        #../rs274ngc/modal_state.cc
        emcglb.c
        emc.cc
        emcpose.c
        emcargs.cc
        emcpos.cc
        canon_position.cc
        interpl.cc
        )
target_link_libraries(emc_nmlintf
        PRIVATE
        emc_tooldata
        PUBLIC
        rs274ngc_modalstate
        nml
        libnml_posemath
        motion_component
        )
target_include_directories(emc_nmlintf PUBLIC .)
set_property(TARGET emc_nmlintf PROPERTY POSITION_INDEPENDENT_CODE ON)
get_uspace_config(emc_nmlintf)
#target_link_libraries(linuxcnc PRIVATE Python3::Module)
#target_link_libraries(linuxcnc PRIVATE pythonplugin)
#get_uspace_config(linuxcnc)
