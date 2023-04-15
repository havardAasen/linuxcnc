add_library(pythonplugin SHARED python_plugin.cc)
target_link_libraries(pythonplugin
        Python3::Module
        Boost::${BOOSTPYTHON}
        libnml_inifile
        )
set_property(TARGET pythonplugin PROPERTY POSITION_INDEPENDENT_CODE ON)

