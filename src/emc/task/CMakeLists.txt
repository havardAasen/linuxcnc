add_executable(linuxcncsvr emcsvr.cc)
target_link_libraries(linuxcncsvr PRIVATE hal nml nmlintf inifile)
get_uspace_config(linuxcncsvr)

set(MILL_SOURCES
        ../motion/emcmotglb.c
        ../task/emctask.cc
        ../task/emccanon.cc
        ../task/emctaskmain.cc
        ../motion/usrmotintf.cc
        ../motion/emcmotutil.c
        ../task/taskintf.cc
        ../motion/dbuf.c
        ../motion/stashf.c
        ../task/taskmodule.cc
        ../task/taskclass.cc
        ../task/backtrace.cc)
add_executable(milltask ${MILL_SOURCES})
target_link_libraries(milltask
        PRIVATE
        Boost::${BOOSTPYTHON}
        hal
        nml
        nmlintf
        inifile
        Python3::Python
        pythonplugin
        posemath
        rs274ngc
        tooldata)
get_uspace_config(milltask)
