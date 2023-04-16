add_library(libnml_rcs
        rcs_print.cc
        rcs_exit.cc
        )

target_include_directories(libnml_rcs PUBLIC .)

target_link_libraries(libnml_rcs PRIVATE ulapi libnml_linklist libnml_os_intf)
set_property(TARGET libnml_rcs PROPERTY POSITION_INDEPENDENT_CODE ON)
get_uspace_config(libnml_rcs)