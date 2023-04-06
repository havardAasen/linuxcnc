add_library(libnml_buffer
        locmem.cc
        memsem.cc
        phantom.cc
        physmem.cc
        recvn.c
        sendn.c
        shmem.cc
        tcpmem.cc)
set_property(TARGET libnml_buffer PROPERTY POSITION_INDEPENDENT_CODE ON)
