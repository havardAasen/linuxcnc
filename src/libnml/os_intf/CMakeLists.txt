add_library(libnml_os_intf
        _sem.c
        _shm.c
        _timer.c
        sem.cc
        shm.cc
        timer.cc
        )
set_property(TARGET libnml_buffer PROPERTY POSITION_INDEPENDENT_CODE ON)