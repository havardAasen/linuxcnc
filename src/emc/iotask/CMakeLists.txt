add_executable(io ioControl.cc)
target_link_libraries(io
        PRIVATE
        emc_tooldata
        emc_nmlintf
        hal
        ulapi)
get_uspace_config(io)

add_executable(iov2 ioControl_v2.cc)
target_link_libraries(iov2
        PRIVATE
        nml
        emc_nmlintf
        hal
        emc_tooldata
        ulapi
        inifile)
get_uspace_config(iov2)
