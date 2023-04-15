add_executable(motion-logger motion-logger.c)
target_link_libraries(motion-logger
        PRIVATE
        emc_nmlintf
        hal
        ulapi
        motion_task
        )
# TODO: this only needs ULAPI not RTAPI?
get_uspace_config(motion-logger)
