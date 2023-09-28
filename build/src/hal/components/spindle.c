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

#include "hal/components/spindle.h"
#ifdef MODULE_INFO
MODULE_INFO(linuxcnc, "component:spindle:Control a spindle with different acceleration and deceleration and optional gear change scaling");
MODULE_INFO(linuxcnc, "descr:This component will control a spindle with adjustable acceleration and deceleration.\n\n NOTE: This component is unfortunately named and creates pins with names very much like those created by the motion component.\n In nearly every case this is not the documentation page that you are looking for.\n See http://linuxcnc.org/docs/html/man/man9/motion.9.html instead.\n\nIt is designed for use with non-servo spindle drives that have separate fwd/reverse inputs, such as DC drives and inverters.\nIf a spindle encoder is available it is used to tailor the acceleration and deceleration to the spindle load.\nIf not the spindle speed is simulated. The component allows for gearboxes with up to 16 gears.\nEach gear has individual control of speeds, acceleration, driver gain and direction.");
MODULE_INFO(linuxcnc, "see_also:\\fBmotion\\fR(9)");
MODULE_INFO(linuxcnc, "pin:select-gear:u32:0:in:Select a gear. Must be in the range 0 -> number of available gears -1. If you use this, do not use the select.x input pins.:None:None");
MODULE_INFO(linuxcnc, "pin:commanded-speed:float:0:in:Commanded spindle speed (in RPM):None:None");
MODULE_INFO(linuxcnc, "pin:actual-speed:float:0:in:Actual spindle speed from a spindle encoder (in RPS).\nIf you do not have a spindle encoder set the simulate_encoder parameter to 1.:None:None");
MODULE_INFO(linuxcnc, "pin:simulate-encoder:bit:0:in:If you do not have an encoder, set this to 1.:None:None");
MODULE_INFO(linuxcnc, "pin:enable:bit:0:in:If FALSE, the spindle is stopped at the gear's maximum deceleration.:None:None");
MODULE_INFO(linuxcnc, "pin:spindle-lpf:float:0:in:Smooth the spindle-rpm-abs output when at speed, 0 = disabled.\nSuitable values are probably between 1 and 20 depending on how stable your spindle is.:None:None");
MODULE_INFO(linuxcnc, "pin:spindle-rpm:float:0:out:Current spindle speed in RPM.+ve = forward, -ve = reverse.\nUses the encoder input if available. If not, uses a simulated encoder speed.:None:None");
MODULE_INFO(linuxcnc, "pin:spindle-rpm-abs:float:0:out:Absolute spindle speed in RPM. Useful for spindle speed displays.:None:None");
MODULE_INFO(linuxcnc, "pin:output:float:0:out:Scaled output:None:None");
MODULE_INFO(linuxcnc, "pin:current-gear:u32:0:out:Currently selected gear.:None:None");
MODULE_INFO(linuxcnc, "pin:at-speed:bit:0:out:TRUE when the spindle is at speed:None:None");
MODULE_INFO(linuxcnc, "pin:forward:bit:0:out:TRUE for forward rotation:None:None");
MODULE_INFO(linuxcnc, "pin:reverse:bit:0:out:TRUE for reverse rotation. Both forward and reverse are false when the spindle is stopped.:None:None");
MODULE_INFO(linuxcnc, "pin:brake:bit:0:out:TRUE when decelerating:None:None");
MODULE_INFO(linuxcnc, "pin:zero-speed:bit:0:out:TRUE when the spindle is stationary:None:None");
MODULE_INFO(linuxcnc, "pin:limited:bit:0:out:TRUE when the commanded spindle speed is >max or <min.:None:None");
MODULE_INFO(linuxcnc, "notes:\n.TP\n.B The following pins are created depending the 'numgears=' parameter.\nOne of each pin is created for each gear. If no gears are specified then one gear will be created.\nFor instance if you have gears=2 on your command line, you will have two scale pins:\n \\fBspindle.\\fP\\fIN\\fB.scale.0\\fP\n \\fBspindle.\\fP\\fIN\\fB.scale.1\\fP\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.scale.\\fPx float in\nScale the output. For multiple gears you would use a different scale for each gear.\nIf you need to reverse the output for some gears, use a negative scale.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.min.\\fPx float in\nSet the minimum speed allowed (in RPM).\nThe limit output will be TRUE while the commanded speed is between 0 RPM and the min speed.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.max.\\fPx float in\nSet the maximum speed allowed (in RPM).\nThe limit output will be TRUE while the commanded speed is above this value.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.accel.\\fPx float in\nSet the maximum acceleration.\nIf you do not have a spindle encoder this is in RPM/second.\nIf you do have an encoder the output is the actual speed plus this value.\nThis way the acceleration can be dependent on the spindle load.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.decel.\\fPx float in\nSet the minimum deceleration. If you do not have a spindle encoder this is in RPM/second.\nIf you do have an encoder the output is the actual speed minus this value.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.speed-tolerance.\\fPx float in\nTolerance for 'at-speed' signal (in RPM).\nActual spindle speeds within this amount of the commanded speed will cause the at-speed signal to go TRUE.\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.zero-tolerance.\\fPx float in\nTolerance for 'zero-speed' signal (in RPM).\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.offset.\\fPx float in\nThe output command is offset by this amount (in RPM).\n\n.TP\n\\fBspindle.\\fP\\fIN\\fB.select.\\fPx bit in\nSelects this gear. If no select inputs are active, gear 0 is selected.\nIf multiple select inputs are active then the highest is selected.\n");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "author:Les Newell");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    hal_u32_t *select_gear_p;
    hal_float_t *commanded_speed_p;
    hal_float_t *actual_speed_p;
    hal_bit_t *simulate_encoder_p;
    hal_bit_t *enable_p;
    hal_float_t *spindle_lpf_p;
    hal_float_t *spindle_rpm_p;
    hal_float_t *spindle_rpm_abs_p;
    hal_float_t *output_p;
    hal_u32_t *current_gear_p;
    hal_bit_t *at_speed_p;
    hal_bit_t *forward_p;
    hal_bit_t *reverse_p;
    hal_bit_t *brake_p;
    hal_bit_t *zero_speed_p;
    hal_bit_t *limited_p;
    float ngears_p;

    gear_t gears_p[16];

};
struct __comp_state *__comp_first_inst=0, *__comp_last_inst=0;

static void _(struct __comp_state *__comp_inst, long period);
static int __comp_get_data_size(void);
static int extra_setup(struct __comp_state *__comp_inst, char *prefix, long extra_arg);
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
    r = extra_setup(inst, prefix, extra_arg);
    if(r != 0) return r;
    r = hal_pin_u32_newf(HAL_IN, &(inst->select_gear_p), comp_id,
        "%s.select-gear", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->commanded_speed_p), comp_id,
        "%s.commanded-speed", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->actual_speed_p), comp_id,
        "%s.actual-speed", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_IN, &(inst->simulate_encoder_p), comp_id,
        "%s.simulate-encoder", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_IN, &(inst->enable_p), comp_id,
        "%s.enable", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IN, &(inst->spindle_lpf_p), comp_id,
        "%s.spindle-lpf", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->spindle_rpm_p), comp_id,
        "%s.spindle-rpm", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->spindle_rpm_abs_p), comp_id,
        "%s.spindle-rpm-abs", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->output_p), comp_id,
        "%s.output", prefix);
    if(r != 0) return r;
    r = hal_pin_u32_newf(HAL_OUT, &(inst->current_gear_p), comp_id,
        "%s.current-gear", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->at_speed_p), comp_id,
        "%s.at-speed", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->forward_p), comp_id,
        "%s.forward", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->reverse_p), comp_id,
        "%s.reverse", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->brake_p), comp_id,
        "%s.brake", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->zero_speed_p), comp_id,
        "%s.zero-speed", prefix);
    if(r != 0) return r;
    r = hal_pin_bit_newf(HAL_OUT, &(inst->limited_p), comp_id,
        "%s.limited", prefix);
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
RTAPI_MP_INT(count, "number of spindle");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of spindle");
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("spindle");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "spindle.%d", i);
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
#undef select_gear
#undef select_gear_ptr
#define select_gear_ptr (__comp_inst->select_gear_p)
#define select_gear (0+*__comp_inst->select_gear_p)
#undef commanded_speed
#undef commanded_speed_ptr
#define commanded_speed_ptr (__comp_inst->commanded_speed_p)
#define commanded_speed (0+*__comp_inst->commanded_speed_p)
#undef actual_speed
#undef actual_speed_ptr
#define actual_speed_ptr (__comp_inst->actual_speed_p)
#define actual_speed (0+*__comp_inst->actual_speed_p)
#undef simulate_encoder
#undef simulate_encoder_ptr
#define simulate_encoder_ptr (__comp_inst->simulate_encoder_p)
#define simulate_encoder (0+*__comp_inst->simulate_encoder_p)
#undef enable
#undef enable_ptr
#define enable_ptr (__comp_inst->enable_p)
#define enable (0+*__comp_inst->enable_p)
#undef spindle_lpf
#undef spindle_lpf_ptr
#define spindle_lpf_ptr (__comp_inst->spindle_lpf_p)
#define spindle_lpf (0+*__comp_inst->spindle_lpf_p)
#undef spindle_rpm
#undef spindle_rpm_ptr
#define spindle_rpm_ptr (__comp_inst->spindle_rpm_p)
#define spindle_rpm (*__comp_inst->spindle_rpm_p)
#undef spindle_rpm_abs
#undef spindle_rpm_abs_ptr
#define spindle_rpm_abs_ptr (__comp_inst->spindle_rpm_abs_p)
#define spindle_rpm_abs (*__comp_inst->spindle_rpm_abs_p)
#undef output
#undef output_ptr
#define output_ptr (__comp_inst->output_p)
#define output (*__comp_inst->output_p)
#undef current_gear
#undef current_gear_ptr
#define current_gear_ptr (__comp_inst->current_gear_p)
#define current_gear (*__comp_inst->current_gear_p)
#undef at_speed
#undef at_speed_ptr
#define at_speed_ptr (__comp_inst->at_speed_p)
#define at_speed (*__comp_inst->at_speed_p)
#undef forward
#undef forward_ptr
#define forward_ptr (__comp_inst->forward_p)
#define forward (*__comp_inst->forward_p)
#undef reverse
#undef reverse_ptr
#define reverse_ptr (__comp_inst->reverse_p)
#define reverse (*__comp_inst->reverse_p)
#undef brake
#undef brake_ptr
#define brake_ptr (__comp_inst->brake_p)
#define brake (*__comp_inst->brake_p)
#undef zero_speed
#undef zero_speed_ptr
#define zero_speed_ptr (__comp_inst->zero_speed_p)
#define zero_speed (*__comp_inst->zero_speed_p)
#undef limited
#undef limited_ptr
#define limited_ptr (__comp_inst->limited_p)
#define limited (*__comp_inst->limited_p)
#undef ngears
#define ngears (__comp_inst->ngears_p)
#undef gears
#define gears (__comp_inst->gears_p)


#line 142 "/home/end/projects/linuxcnc/src/hal/components/spindle.comp"

int numgears[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
RTAPI_MP_ARRAY_INT(numgears, 16, "Number of gears");

int add_gear(int index, char *prefix, gear_t * g);

FUNCTION(_) {
    int ct;
    float cmdspeed;
    float curspeed;
    float diff;
    float tmp;
    bool limit = false;
    bool reversing;

    gear_t * thisgear = gears;
    if(select_gear != 0){
        current_gear = select_gear;
        if(current_gear > 15) current_gear = 15;
        thisgear = &gears[current_gear];
    }else{
        current_gear = 0;
        for(ct = ngears-1; ct >= 0; ct--){
            thisgear = &gears[ct];
            if(*(thisgear->select)){
                current_gear = ct;
                break;
            }
        }
    }
    if(!simulate_encoder){
        spindle_rpm = actual_speed * 60; /*RPS to RPM*/
    }
    curspeed = spindle_rpm;
    if(enable){
        cmdspeed = commanded_speed;
    }else{
        cmdspeed = 0;
    }

    if(curspeed >= 0){
        tmp = curspeed;
    }else{
        tmp = -curspeed;
    }
    zero_speed = (tmp <= *(thisgear->zero_tolerance));
    if(spindle_lpf >0 && at_speed){
        spindle_rpm_abs += (tmp - spindle_rpm_abs) * spindle_lpf * fperiod;
    }else{
        spindle_rpm_abs = tmp;
    }

    reversing = (cmdspeed > 0 && curspeed < 0) || (cmdspeed < 0 && curspeed > 0);

    diff = cmdspeed - curspeed;
    if(diff <0) diff = -diff;
    tmp = *(thisgear->speed_tolerance);
    at_speed = (tmp >0 && tmp >= diff) && !reversing;

    tmp = *(thisgear->min);
    if(tmp > 0){
        if(cmdspeed > 0){
            if(cmdspeed < tmp){
                cmdspeed = tmp;
                limit = true;
            }
        }else if(cmdspeed < 0){
            if(cmdspeed > -tmp){
                cmdspeed = -tmp;
                limit = true;
            }
        }
    }
    tmp = *(thisgear->max);
    if(tmp > 0){
        if(cmdspeed > 0 && cmdspeed > tmp){
            cmdspeed = tmp;
            limit = true;
        }
        if(cmdspeed < 0 && cmdspeed < -tmp){
            cmdspeed = -tmp;
            limit = true;
        }
    }

    diff = cmdspeed - curspeed;

    /* make sure we don't cross zero speed */
    if(curspeed > 0 && diff < -curspeed) diff = -curspeed;
    if(curspeed < 0 && diff > -curspeed) diff = -curspeed;

    tmp = *(thisgear->accel);
    if(tmp > 0 && !reversing){
        if(simulate_encoder) tmp *= fperiod;
        if(cmdspeed > 0 && diff > tmp){
                diff = tmp;
        }
        if(cmdspeed < 0 && diff < -tmp){
                diff = -tmp;
        }
    }

    tmp = *(thisgear->decel);
    if(tmp > 0){
        if(simulate_encoder) tmp *= fperiod;
        if(reversing){
            if(cmdspeed >= 0 && diff > tmp) diff = tmp;
            if(cmdspeed <= 0 && diff < -tmp) diff = -tmp;
        }else{
            if(cmdspeed >= 0 && diff < -tmp) diff = -tmp;
            if(cmdspeed <= 0 && diff > tmp) diff = tmp;
        }
    }

    if(at_speed){ /* stop hunting when at sped */
        curspeed = cmdspeed;
    }else{
        curspeed += diff;
    }

    if(simulate_encoder){
        spindle_rpm = curspeed;
    }

    if(cmdspeed !=0){
        forward = (curspeed >0);
        reverse = (curspeed <0);
    }else{ /* don't try to move once stopped */
        forward = (curspeed >0) && forward;
        reverse = (curspeed <0) && forward;
    }
    if(curspeed < 0) curspeed = -curspeed;
    output = (curspeed + (*(thisgear->offset))) * (*(thisgear->scale));
    limited = limit;
}

EXTRA_SETUP(){
    int ct;
    int r;
    ngears = numgears[extra_arg];
    if(ngears < 1 || ngears > 16){
        rtapi_print_msg(RTAPI_MSG_ERR,"Number of gears is out of range\n");
        return(-EINVAL);
    }
    for(ct = 0; ct < ngears; ct++){
        r = add_gear(ct, prefix,&gears[ct]);
        if(r != 0) return r;
    }
    if(ngears ==1){
        *(gears[0].select) = true;
    }
    return(0);
}

int add_gear(int index, char *prefix, gear_t * g)
{
    int r;
    r = hal_pin_float_newf(HAL_IN, &(g->scale), comp_id,
        "%s.scale.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->min), comp_id,
        "%s.min.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->max), comp_id,
        "%s.max.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->accel), comp_id,
        "%s.accel.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->decel), comp_id,
        "%s.decel.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->speed_tolerance), comp_id,
        "%s.speed-tolerance.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->zero_tolerance), comp_id,
        "%s.zero-tolerance.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_float_newf(HAL_IN, &(g->offset), comp_id,
        "%s.offset.%i", prefix,index);
    if(r != 0) return r;

    r = hal_pin_bit_newf(HAL_IN, &(g->select), comp_id,
        "%s.select.%i", prefix,index);
    if(r != 0) return r;
    *g->scale = 1;
    *g->min = 0;
    *g->max = 0;
    *g->accel = 0;
    *g->decel = 0;
    *g->speed_tolerance = 20;
    *g->zero_tolerance = 20;
    *g->offset = 0;
    *g->select = false;
    return(0);
}

static int __comp_get_data_size(void) { return 0; }
