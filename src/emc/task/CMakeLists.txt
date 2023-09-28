add_executable(linuxcncsvr
        emcsvr.cc
        )
target_link_libraries(linuxcncsvr
        PRIVATE
        hal
        nml
        emc_nmlintf
        emc_ini
        )
get_uspace_config(linuxcncsvr)


add_executable(milltask
        emctask.cc
        emccanon.cc
        emctaskmain.cc
        taskintf.cc
        taskclass.cc
        backtrace.cc
        )
target_link_libraries(milltask
        PRIVATE
        motion_task
        Boost::${BOOSTPYTHON}
        hal
        nml
        emc_nmlintf
        emc_ini
        Python3::Python
        pythonplugin
        rs274ngc
        emc_tooldata
        libnml_posemath
        )
get_uspace_config(milltask)

