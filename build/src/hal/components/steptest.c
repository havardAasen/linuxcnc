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
MODULE_INFO(linuxcnc, "component:steptest:Used by Stepconf to allow testing of acceleration and velocity values for an axis.");
MODULE_INFO(linuxcnc, "pin:jog-minus:bit:0:in:Drive TRUE to jog the axis in its minus direction:None:None");
MODULE_INFO(linuxcnc, "pin:jog-plus:bit:0:in:Drive TRUE to jog the axis in its positive direction:None:None");
MODULE_INFO(linuxcnc, "pin:run:bit:0:in:Drive TRUE to run the axis near its current position_fb with a trapezoidal velocity profile:None:None");
MODULE_INFO(linuxcnc, "pin:maxvel:float:0:in:Maximum velocity:None:None");
MODULE_INFO(linuxcnc, "pin:maxaccel:float:0:in:Permitted Acceleration:None:None");
MODULE_INFO(linuxcnc, "pin:amplitude:float:0:in:Approximate amplitude of positions to command during 'run':None:None");
MODULE_INFO(linuxcnc, "pin:dir:s32:0:in:Direction from central point to test: 0 = both, 1 = positive, 2 = negative:None:None");
MODULE_INFO(linuxcnc, "pin:position-cmd:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:position-fb:float:0:in::None:None");
MODULE_INFO(linuxcnc, "pin:running:bit:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:run-target:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:run-start:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:run-low:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:run-high:float:0:out::None:None");
MODULE_INFO(linuxcnc, "pin:pause:s32:0:in:pause time for each end of run in seconds:0:None");
MODULE_INFO(linuxcnc, "param:epsilon:float:0:rw::.001:None");
MODULE_INFO(linuxcnc, "param:elapsed:float:0:r:Current value of the internal timer:None:None");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "author:Jeff Epler");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_bit_t *jog_minus_p;
    hal_bit_t *jog_plus_p;
    hal_bit_t *run_p;
    hal_float_t *maxvel_p;
    hal_float_t *maxaccel_p;
    hal_float_t *amplitude_p;
    hal_s32_t *dir_p;
    hal_float_t *position_cmd_p;
    hal_float_t *position_fb_p;
    hal_bit_t *running_p;
    hal_float_t *run_target_p;
    hal_float_t *run_start_p;
    hal_float_t *run_low_p;
    hal_float_t *run_high_p;
    hal_s32_t *pause_p;
    hal_float_t epsilon_p;
    hal_float_t elapsed_p;
    double timer_p;

    int timer_on_p;

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
    r = hal_pin_bit_newf(HAL_IN, &(inst->jog_minus_p), comp_id,
        "%s.jog-minus", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_IN, &(inst->jog_plus_p), comp_id,
        "%s.jog-plus", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_IN, &(inst->run_p), comp_id,
        "%s.run", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->maxvel_p), comp_id,
        "%s.maxvel", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->maxaccel_p), comp_id,
        "%s.maxaccel", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->amplitude_p), comp_id,
        "%s.amplitude", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->dir_p), comp_id,
        "%s.dir", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->position_cmd_p), comp_id,
        "%s.position-cmd", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->position_fb_p), comp_id,
        "%s.position-fb", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->running_p), comp_id,
        "%s.running", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->run_target_p), comp_id,
        "%s.run-target", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->run_start_p), comp_id,
        "%s.run-start", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->run_low_p), comp_id,
        "%s.run-low", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->run_high_p), comp_id,
        "%s.run-high", prefix);
    if(r != 0) return r;
    r = hal_pin_s32_newf(HAL_IN, &(inst->pause_p), comp_id,
        "%s.pause", prefix);
    if(r != 0) return r;
    *(inst->pause_p) = 0;
    r = hal_param_float_newf(HAL_RW, &(inst->epsilon_p), comp_id,
        "%s.epsilon", prefix);
    inst->epsilon_p = .001;
    if(r != 0) return r;
    r = hal_param_float_newf(HAL_RO, &(inst->elapsed_p), comp_id,
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
RTAPI_MP_INT(count, "number of steptest");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of steptest");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("steptest");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "steptest.%d", i);
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
#undef jog_minus
#undef jog_minus_ptr
#define jog_minus_ptr (__comp_inst->jog_minus_p)
#define jog_minus (0+*__comp_inst->jog_minus_p)
#undef jog_plus
#undef jog_plus_ptr
#define jog_plus_ptr (__comp_inst->jog_plus_p)
#define jog_plus (0+*__comp_inst->jog_plus_p)
#undef run
#undef run_ptr
#define run_ptr (__comp_inst->run_p)
#define run (0+*__comp_inst->run_p)
#undef maxvel
#undef maxvel_ptr
#define maxvel_ptr (__comp_inst->maxvel_p)
#define maxvel (0+*__comp_inst->maxvel_p)
#undef maxaccel
#undef maxaccel_ptr
#define maxaccel_ptr (__comp_inst->maxaccel_p)
#define maxaccel (0+*__comp_inst->maxaccel_p)
#undef amplitude
#undef amplitude_ptr
#define amplitude_ptr (__comp_inst->amplitude_p)
#define amplitude (0+*__comp_inst->amplitude_p)
#undef dir
#undef dir_ptr
#define dir_ptr (__comp_inst->dir_p)
#define dir (0+*__comp_inst->dir_p)
#undef position_cmd
#undef position_cmd_ptr
#define position_cmd_ptr (__comp_inst->position_cmd_p)
#define position_cmd (*__comp_inst->position_cmd_p)
#undef position_fb
#undef position_fb_ptr
#define position_fb_ptr (__comp_inst->position_fb_p)
#define position_fb (0+*__comp_inst->position_fb_p)
#undef running
#undef running_ptr
#define running_ptr (__comp_inst->running_p)
#define running (*__comp_inst->running_p)
#undef run_target
#undef run_target_ptr
#define run_target_ptr (__comp_inst->run_target_p)
#define run_target (*__comp_inst->run_target_p)
#undef run_start
#undef run_start_ptr
#define run_start_ptr (__comp_inst->run_start_p)
#define run_start (*__comp_inst->run_start_p)
#undef run_low
#undef run_low_ptr
#define run_low_ptr (__comp_inst->run_low_p)
#define run_low (*__comp_inst->run_low_p)
#undef run_high
#undef run_high_ptr
#define run_high_ptr (__comp_inst->run_high_p)
#define run_high (*__comp_inst->run_high_p)
#undef pause
#undef pause_ptr
#define pause_ptr (__comp_inst->pause_p)
#define pause (0+*__comp_inst->pause_p)
#undef epsilon
#define epsilon (__comp_inst->epsilon_p)
#undef elapsed
#define elapsed (__comp_inst->elapsed_p)
#undef timer
#define timer (__comp_inst->timer_p)
#undef timer_on
#define timer_on (__comp_inst->timer_on_p)


FUNCTION(_) {
#line 26 "/home/end/projects/linuxcnc/src/hal/components/steptest.comp"
extern double fabs(double);

if (timer_on) {
    timer += fperiod;
}
elapsed = timer;
if(run) {
    if(!running) {
        running = 1;
        run_start = position_fb;

        if(dir == 2) run_high = run_start;
        else run_high = run_start + amplitude;

        if(dir == 1) run_low = run_start;
        else run_low = run_start - amplitude;

        position_cmd = run_low;
    }

    if(fabs(position_fb - position_cmd) < epsilon) {
        if ((position_cmd == run_low) || (position_cmd ==run_high)) {
            if (!timer_on) {
                timer = 0;
                timer_on = true;
            } else if (timer >= pause) {
                timer_on = false; 
                if(position_cmd == run_low) {
                    position_cmd = run_high;
                } else {
                    position_cmd = run_low;
                }
            }
        }
    }
} else if(running) {
    position_cmd = run_start;
    if(fabs(position_fb - run_start) < epsilon) {
        running = 0;
        timer_on = false;
    }
} else {
    if(jog_minus) {
        position_cmd = position_fb - 2 * maxvel * fperiod;
    } else if(jog_plus) {
        position_cmd = position_fb + 2 * maxvel * fperiod;
    } else {
        // Let the command track the feedback while the stepgen decelerates
        // to a halt, then keep the command constant there.
        if (fabs(position_fb - position_cmd) > (0.001 * maxvel * fperiod)) {
            position_cmd = position_fb;
        }
    }
}
}

static int __comp_get_data_size(void) { return 0; }
