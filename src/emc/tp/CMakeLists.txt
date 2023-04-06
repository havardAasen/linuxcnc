add_library(trajectoryplanner
        tc.c
        tcq.c
        tp.c
        spherical_arc.c
        blendmath.c
)
get_uspace_config(trajectoryplanner)
