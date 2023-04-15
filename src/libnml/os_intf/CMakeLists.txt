add_library(libnml_os_intf
        _sem.c
        _shm.c
        _timer.c
        sem.cc
        shm.cc
        timer.cc
        )
target_link_libraries(libnml_os_intf PUBLIC ulapi libnml_rcs)
target_include_directories(libnml_os_intf PUBLIC .)
get_uspace_config(libnml_os_intf)
set_property(TARGET libnml_buffer PROPERTY POSITION_INDEPENDENT_CODE ON)