add_library(libnml_rcs
        rcs_print.cc
        rcs_exit.cc
        )

target_include_directories(libnml_rcs PUBLIC .)

target_link_libraries(libnml_rcs PRIVATE libnml_linklist)