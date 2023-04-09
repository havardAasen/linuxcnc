add_library(trajectoryplanner
        tc.c
        tcq.c
        tp.c
        spherical_arc.c
        blendmath.c
)
target_include_directories(trajectoryplanner PUBLIC .)
get_uspace_config(trajectoryplanner)
