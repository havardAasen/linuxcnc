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
MODULE_INFO(linuxcnc, "component:limit1:Limit the output signal to fall between min and max");
MODULE_INFO(linuxcnc, "pin:in:float:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:out:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:min_:float:0:in::-1e20:None");
MODULE_INFO(linuxcnc, "pin:max_:float:0:in::1e20:None");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "author:Jeff Epler");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_float_t *in_p;
    hal_float_t *out_p;
    hal_float_t *min__p;
    hal_float_t *max__p;
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
    r = hal_pin_float_newf(HAL_IN, &(inst->in_p), comp_id,
        "%s.in", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->out_p), comp_id,
        "%s.out", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->min__p), comp_id,
        "%s.min", prefix);
    if(r != 0) return r;
    *(inst->min__p) = -1e20;
    r = hal_pin_float_newf(HAL_IN, &(inst->max__p), comp_id,
        "%s.max", prefix);
    if(r != 0) return r;
    *(inst->max__p) = 1e20;
    rtapi_snprintf(buf, sizeof(buf), "%s", prefix);
    r = hal_export_funct(buf, (void(*)(void *inst, long))_, inst, 1, 0, comp_id);
    if(r != 0) return r;
    if(__comp_last_inst) __comp_last_inst->_next = inst;
    __comp_last_inst = inst;
    if(!__comp_first_inst) __comp_first_inst = inst;
    return 0;
}
static int default_count=1, count=0;
RTAPI_MP_INT(count, "number of limit1");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of limit1");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("limit1");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "limit1.%d", i);
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
#undef in
#undef in_ptr
#define in_ptr (__comp_inst->in_p)
#define in (0+*__comp_inst->in_p)
#undef out
#undef out_ptr
#define out_ptr (__comp_inst->out_p)
#define out (*__comp_inst->out_p)
#undef min_
#undef min__ptr
#define min__ptr (__comp_inst->min__p)
#define min_ (0+*__comp_inst->min__p)
#undef max_
#undef max__ptr
#define max__ptr (__comp_inst->max__p)
#define max_ (0+*__comp_inst->max__p)


#line 10 "/home/end/projects/linuxcnc/src/hal/components/limit1.comp"
FUNCTION(_) {
    double tmp = in;
    if(tmp < min_) tmp = min_;
    if(tmp > max_) tmp = max_;
    out = tmp;
}

static int __comp_get_data_size(void) { return 0; }
