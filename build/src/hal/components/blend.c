/* Autogenerated by /home/end/projects/linuxcnc/build/bin/halcompile on Thu Sep 28 23:37:49 2023 -- do not edit */
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
MODULE_INFO(linuxcnc, "component:blend:Perform linear interpolation between two values");
MODULE_INFO(linuxcnc, "pin:in1:float:0:in:First input.  If select is equal to 1.0, the output is equal to in1:None:None");
MODULE_INFO(linuxcnc, "pin:in2:float:0:in:Second input.  If select is equal to 0.0, the output is equal to in2:None:None");
MODULE_INFO(linuxcnc, "pin:select:float:0:in:Select input.  For values between 0.0 and 1.0, the output changes linearly from in2 to in1:None:None");
MODULE_INFO(linuxcnc, "pin:out:float:0:out:Output value.:None:None");
MODULE_INFO(linuxcnc, "param:open:bit:0:rw:If true, select values outside the range 0.0 to 1.0 give values outside the range in2 to in1.  If false, outputs are clamped to the the range in2 to in1:None:None");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "author:Jeff Epler");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_float_t *in1_p;
    hal_float_t *in2_p;
    hal_float_t *select_p;
    hal_float_t *out_p;
    hal_bit_t open_p;
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
    r = hal_pin_float_newf(HAL_IN, &(inst->in1_p), comp_id,
        "%s.in1", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->in2_p), comp_id,
        "%s.in2", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->select_p), comp_id,
        "%s.select", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->out_p), comp_id,
        "%s.out", prefix);
    if(r != 0) return r;
    r = hal_param_bit_newf(HAL_RW, &(inst->open_p), comp_id,
        "%s.open", prefix);
    if(r != 0) return r;
    rtapi_snprintf(buf, sizeof(buf), "%s", prefix);
    r = hal_export_funct(buf, (void(*)(void *inst, long))_, inst, 1, 0, comp_id);
    if(r != 0) return r;
    if(__comp_last_inst) __comp_last_inst->_next = inst;
    __comp_last_inst = inst;
    if(!__comp_first_inst) __comp_first_inst = inst;
    return 0;
}
static int default_count=1, count=0;
RTAPI_MP_INT(count, "number of blend");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of blend");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("blend");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "blend.%d", i);
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
#undef in1
#undef in1_ptr
#define in1_ptr (__comp_inst->in1_p)
#define in1 (0+*__comp_inst->in1_p)
#undef in2
#undef in2_ptr
#define in2_ptr (__comp_inst->in2_p)
#define in2 (0+*__comp_inst->in2_p)
#undef select
#undef select_ptr
#define select_ptr (__comp_inst->select_p)
#define select (0+*__comp_inst->select_p)
#undef out
#undef out_ptr
#define out_ptr (__comp_inst->out_p)
#define out (*__comp_inst->out_p)
#undef open
#define open (__comp_inst->open_p)


#line 32 "/home/end/projects/linuxcnc/src/hal/components/blend.comp"

FUNCTION(_) {
    double select_ = select;
    if(!open) { if(select_ < 0) select_ = 0; if(select_ > 1) select_ = 1; }
    out = in1 * select_ + in2 * (1 - select_);
}

static int __comp_get_data_size(void) { return 0; }
