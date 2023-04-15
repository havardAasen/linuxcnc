add_library(libnml_buffer
        locmem.cc
        memsem.cc
        phantom.cc
        physmem.cc
        recvn.c
        sendn.c
        shmem.cc
        tcpmem.cc)
target_include_directories(libnml_buffer PUBLIC .)
target_link_libraries(libnml_buffer PUBLIC libnml_cms libnml_linklist libnml_rcs libnml_os_intf ulapi)
set_property(TARGET libnml_buffer PROPERTY POSITION_INDEPENDENT_CODE ON)
get_uspace_config(libnml_buffer)