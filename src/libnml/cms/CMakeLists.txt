add_library(libnml_cms
        cms.cc
        cms_aup.cc
        cms_cfg.cc
        cms_in.cc
        cms_dup.cc
        cms_pm.cc
        cms_srv.cc
        cms_up.cc
        cms_xup.cc
        cmsdiag.cc
        tcp_opts.cc
        tcp_srv.cc
        )
set_property(TARGET libnml_cms PROPERTY POSITION_INDEPENDENT_CODE ON)
