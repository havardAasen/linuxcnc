add_library(libnml_rcs
        rcs_print.cc
        rcs_exit.cc
        )

target_include_directories(libnml_rcs PUBLIC .)

target_link_libraries(libnml_rcs PRIVATE ulapi libnml_linklist libnml_os_intf)
get_uspace_config(libnml_rcs)