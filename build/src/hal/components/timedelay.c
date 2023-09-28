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
MODULE_INFO(linuxcnc, "component:timedelay:The equivalent of a time-delay relay");
MODULE_INFO(linuxcnc, "pin:in:bit:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:out:bit:0:out:Follows the value of \\fBin\\fR after applying the delays\n\\fBon-delay\\fR and \\fBoff-delay\\fR.:None:None");
MODULE_INFO(linuxcnc, "pin:on-delay:float:0:in:The time, in seconds, for which \\fBin\\fR must be\n\\fBtrue\\fR before \\fBout\\fR becomes \\fBtrue\\fR:0.5:None");
MODULE_INFO(linuxcnc, "pin:off-delay:float:0:in:The time, in seconds, for which \\fBin\\fR must be\n\\fBfalse\\fR before \\fBout\\fR becomes \\fBfalse\\fR:0.5:None");
MODULE_INFO(linuxcnc, "pin:elapsed:float:0:out:Current value of the internal timer:None:None");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "author:Jeff Epler, based on works by Stephen Wille Padnos and John Kasunich");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_bit_t *in_p;
    hal_bit_t *out_p;
    hal_float_t *on_delay_p;
    hal_float_t *off_delay_p;
    hal_float_t *elapsed_p;
    double timer_p;

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
    r = hal_pin_bit_newf(HAL_IN, &(inst->in_p), comp_id,
        "%s.in", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->out_p), comp_id,
        "%s.out", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->on_delay_p), comp_id,
        "%s.on-delay", prefix);
    if(r != 0) return r;
    *(inst->on_delay_p) = 0.5;
    r = hal_pin_float_newf(HAL_IN, &(inst->off_delay_p), comp_id,
        "%s.off-delay", prefix);
    if(r != 0) return r;
    *(inst->off_delay_p) = 0.5;
    r = hal_pin_float_newf(HAL_OUT, &(inst->elapsed_p), comp_id,
        "%s.elapsed", prefix);
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
RTAPI_MP_INT(count, "number of timedelay");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of timedelay");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("timedelay");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "timedelay.%d", i);
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
#undef on_delay
#undef on_delay_ptr
#define on_delay_ptr (__comp_inst->on_delay_p)
#define on_delay (0+*__comp_inst->on_delay_p)
#undef off_delay
#undef off_delay_ptr
#define off_delay_ptr (__comp_inst->off_delay_p)
#define off_delay (0+*__comp_inst->off_delay_p)
#undef elapsed
#undef elapsed_ptr
#define elapsed_ptr (__comp_inst->elapsed_p)
#define elapsed (*__comp_inst->elapsed_p)
#undef timer
#define timer (__comp_inst->timer_p)


FUNCTION(_) {
#line 20 "/home/end/projects/linuxcnc/src/hal/components/timedelay.comp"
hal_bit_t in_ = in;
if(in_ != out) {
    timer += fperiod;
    elapsed = timer;
    if(in_) {
        if(timer >= on_delay) {
            out = 1;
            timer = 0.0;
        }
    } else {
        if(timer >= off_delay) {
            out = 0;
            timer = 0.0;
        }
    }
} else {
    timer = 0.0;
}
}

static int __comp_get_data_size(void) { return 0; }
