add_library(rs274ngc_modalstate
        modal_state.cc
        )
target_include_directories(rs274ngc_modalstate PUBLIC .)

add_library(rs274ngc SHARED
        interp_arc.cc
        interp_array.cc
        interp_base.cc
        interp_check.cc
        interp_convert.cc
        interp_queue.cc
        interp_cycles.cc
        interp_execute.cc
        interp_find.cc
        interp_internal.cc
        interp_inverse.cc
        interp_read.cc
        interp_write.cc
        interp_o_word.cc
        interp_g7x.cc
        nurbs_additional_functions.cc
        interp_namedparams.cc
        interp_python.cc
        interp_remap.cc
        interp_setup.cc
        canonmodule.cc
        pyparamclass.cc
        pyemctypes.cc
        pyinterp1.cc
        pyblock.cc
        pyarrays.cc
        interpmodule.cc
        rs274ngc_pre.cc
        interp_inspection.cc
        )
target_include_directories(rs274ngc PUBLIC .)
target_link_libraries(rs274ngc
        PRIVATE
        Python3::Module
        Boost::${BOOSTPYTHON}
        pythonplugin
        ulapi
        emc_nmlintf
        emc_tooldata
        )
get_uspace_config(rs274ngc)

add_library(gcode
        SHARED
        gcodemodule.cc)
target_include_directories(gcode
        PUBLIC
        Python3::Python)
target_link_libraries(gcode
        PRIVATE
        rs274ngc
        Python3::Python
        emc_inifile
        hal
        tooldata
        Boost::${BOOSTPYTHON}
        pythonplugin)
set_target_properties(gcode PROPERTIES PREFIX "")