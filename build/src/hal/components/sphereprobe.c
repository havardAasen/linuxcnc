/* Autogenerated by /home/end/projects/linuxcnc/build/bin/halcompile on Thu Sep 28 23:37:50 2023 -- do not edit */
#include "rtapi.h"
#ifdef RTAPI
#include "rtapi_app.h"
#endif
#include "rtapi_string.h"
#include "rtapi_errno.h"
#include "hal.h"
#include "rtapi_math64.h"

static int comp_id;

#ifdef MODULE_INFO
MODULE_INFO(linuxcnc, "component:sphereprobe:Probe a pretend hemisphere");
MODULE_INFO(linuxcnc, "author:Jeff Epler");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "pin:px:s32:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:py:s32:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:pz:s32:0:in:\\fBrawcounts\\fR position from software encoder:None:None");
MODULE_INFO(linuxcnc, "pin:cx:s32:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:cy:s32:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:cz:s32:0:in:Center of sphere in counts:None:None");
MODULE_INFO(linuxcnc, "pin:r:s32:0:in:Radius of hemisphere in counts:None:None");
MODULE_INFO(linuxcnc, "pin:probe-out:bit:0:out::None:None");
MODULE_INFO(linuxcnc, "funct:_:0:update probe-out based on inputs");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_s32_t *px_p;
    hal_s32_t *py_p;
    hal_s32_t *pz_p;
    hal_s32_t *cx_p;
    hal_s32_t *cy_p;
    hal_s32_t *cz_p;
    hal_s32_t *r_p;
    hal_bit_t *probe_out_p;
};
struct __comp_state *__comp_first_inst=0, *__comp_last_inst=0;

static void _(struct __comp_state *__comp_inst, long period);
static int __comp_get_data_size(void);
#undef TRUE
#define TRUE (1)
#undef FALSE
#define FALSE (0)
#undef true
#define true (1)
#undef false
#define false (0)

static int export(char *prefix, long extra_arg) {
    char buf[HAL_NAME_LEN + 1];
    int r = 0;
    int sz = sizeof(struct __comp_state) + __comp_get_data_size();
    struct __comp_state *inst = hal_malloc(sz);
    memset(inst, 0, sz);
    r = hal_pin_s32_newf(HAL_IN, &(inst->px_p), comp_id,
        "%s.px", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->py_p), comp_id,
        "%s.py", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->pz_p), comp_id,
        "%s.pz", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->cx_p), comp_id,
        "%s.cx", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->cy_p), comp_id,
        "%s.cy", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->cz_p), comp_id,
        "%s.cz", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->r_p), comp_id,
        "%s.r", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->probe_out_p), comp_id,
        "%s.probe-out", prefix);
    if(r != 0) return r;
    rtapi_snprintf(buf, sizeof(buf), "%s", prefix);
    r = hal_export_funct(buf, (void(*)(void *inst, long))_, inst, 0, 0, comp_id);
    if(r != 0) return r;
    if(__comp_last_inst) __comp_last_inst->_next = inst;
    __comp_last_inst = inst;
    if(!__comp_first_inst) __comp_first_inst = inst;
    return 0;
}
static int default_count=1, count=0;
RTAPI_MP_INT(count, "number of sphereprobe");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of sphereprobe");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("sphereprobe");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "sphereprobe.%d", i);
            r = export(buf, i);
            if(r != 0) break;
       }
    } else {
        size_t i, j;
        int idx;
        char buf[HAL_NAME_LEN+1];
        const size_t length = strlen(names);
        for (i = j = idx = 0; i <= length; i++) {
            const char c = buf[j] = names[i];
            if ((c == ',') || (c == '\0')) {
                buf[j] = '\0';
                r = export(buf, idx);
                if(r != 0) {break;}
                idx++;
                j = 0;
            } else {
                if (++j == (sizeof(buf) / sizeof(buf[0]))) {
                    buf[j - 1] = '\0';
                    rtapi_print_msg(RTAPI_MSG_ERR,"names: \"%s\" too long\n", buf);
                    r = -EINVAL;
                    break;
                }
            }
        }
    }
    if(r) {
        hal_exit(comp_id);
    } else {
        hal_ready(comp_id);
    }
    return r;
}

void rtapi_app_exit(void) {
    hal_exit(comp_id);
}

#undef FUNCTION
#define FUNCTION(name) static void name(struct __comp_state *__comp_inst, long period)
#undef EXTRA_SETUP
#define EXTRA_SETUP() static int extra_setup(struct __comp_state *__comp_inst, char *prefix, long extra_arg)
#undef EXTRA_CLEANUP
#define EXTRA_CLEANUP() static void extra_cleanup(void)
#undef fperiod
#define fperiod (period * 1e-9)
#undef px
#undef px_ptr
#define px_ptr (__comp_inst->px_p)
#define px (0+*__comp_inst->px_p)
#undef py
#undef py_ptr
#define py_ptr (__comp_inst->py_p)
#define py (0+*__comp_inst->py_p)
#undef pz
#undef pz_ptr
#define pz_ptr (__comp_inst->pz_p)
#define pz (0+*__comp_inst->pz_p)
#undef cx
#undef cx_ptr
#define cx_ptr (__comp_inst->cx_p)
#define cx (0+*__comp_inst->cx_p)
#undef cy
#undef cy_ptr
#define cy_ptr (__comp_inst->cy_p)
#define cy (0+*__comp_inst->cy_p)
#undef cz
#undef cz_ptr
#define cz_ptr (__comp_inst->cz_p)
#define cz (0+*__comp_inst->cz_p)
#undef r
#undef r_ptr
#define r_ptr (__comp_inst->r_p)
#define r (0+*__comp_inst->r_p)
#undef probe_out
#undef probe_out_ptr
#define probe_out_ptr (__comp_inst->probe_out_p)
#define probe_out (*__comp_inst->probe_out_p)


#line 18 "/home/end/projects/linuxcnc/src/hal/components/sphereprobe.comp"
#undef abs
int abs(int x) { if(x < 0) return -x; else return x; }

FUNCTION(_) {
    rtapi_u64 dx = abs(px-cx), dy=abs(py-cy), dz=abs(pz-cz);
    rtapi_u64 d2 = dx*dx + dy*dy;
    rtapi_u64 r2 = (rtapi_s64)r*(rtapi_s64)r;
    if(d2 > r2) {
        probe_out = pz < cz;
    } else {
        d2 += dz*dz;
        probe_out = d2 <= r2;
    }
}

static int __comp_get_data_size(void) { return 0; }
