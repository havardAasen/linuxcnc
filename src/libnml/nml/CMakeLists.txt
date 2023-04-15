add_library(nml SHARED
        cmd_msg.cc
        nml_mod.cc
        nml_oi.cc
        nml_srv.cc
        nml.cc
        nmldiag.cc
        nmlmsg.cc
        stat_msg.cc
        )
target_link_libraries(nml
        PRIVATE
        libnml_linklist
        PUBLIC
        ulapi
        INTERFACE
        libnml_cms
        libnml_rcs
        libnml_os_intf
        libnml_inifile
        libnml_buffer
        )
target_include_directories(nml
        PUBLIC
        .
        ../cms/
        ../rcs/
        ../os_intf/
        ../buffer/
        ../inifile/
        )
get_uspace_config(nml)

set_property(TARGET nml PROPERTY POSITION_INDEPENDENT_CODE ON)
