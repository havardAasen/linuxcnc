add_executable(linuxcncsvr
        emcsvr.cc
        )
target_link_libraries(linuxcncsvr
        PRIVATE
        hal
        nml
        nmlintf
        inifile)
get_uspace_config(linuxcncsvr)


add_executable(milltask
        emctask.cc
        emccanon.cc
        emctaskmain.cc
        taskintf.cc
        taskmodule.cc
        taskclass.cc
        backtrace.cc
        )
target_link_libraries(milltask
        PRIVATE
        motion_task
        Boost::${BOOSTPYTHON}
        hal
        nml
        nmlintf
        inifile
        Python3::Python
        pythonplugin
        posemath
        rs274ngc
        tooldata
        )
get_uspace_config(milltask)

