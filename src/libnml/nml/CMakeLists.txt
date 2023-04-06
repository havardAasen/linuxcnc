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
        hal
        libnml_buffer
        libnml_cms
        libnml_linklist
        libnml_os_intf
        ${TIRPC_LIBRARIES})
target_include_directories(nml PRIVATE ${TIRPC_INCLUDE_DIRS})
get_uspace_config(nml)

set_property(TARGET nml PROPERTY POSITION_INDEPENDENT_CODE ON)
