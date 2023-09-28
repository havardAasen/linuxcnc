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
MODULE_INFO(linuxcnc, "component:lincurve:one-dimensional lookup table");
MODULE_INFO(linuxcnc, "descr:This component can be used to map any floating-point input to a\nfloating-point output. Typical uses would include linearisation of\nthermocouples, defining PID gains that vary with external factors or to\nsubstitute for any mathematical function where absolute accuracy is not\nrequired.\n\nThe component can be thought of as a 2-dimensional graph of points in (x,y)\nspace joined by straight lines. The input value is located on the x axis,\nfollowed up until it touches the line, and the output of the component is set\nto the corresponding y-value.\n\nThe (x,y) points are defined by the x-val-NN and y-val-NN parameters which need\nto be set in the HAL file using \"setp\" commands.\n\nThe maximum number if (x,y) points supported is 16.\n\nFor input values less than the x-val-00 breakpoint the y-val-00 is returned. \nFor x greater than the largest x-val-NN the yval corresponding to x-max is\nreturned (ie, no extrapolation is performed.)\n\nSample usage: loadrt lincurve count=3 personality=4,4,4 \nfor a set of three 4-element graphs.\n ");
MODULE_INFO(linuxcnc, "param:x-val-##:float:(16, 'personality'):rw:axis breakpoints:None:None");
MODULE_INFO(linuxcnc, "param:y-val-##:float:(16, 'personality'):rw:output values to be interpolated:None:None");
MODULE_INFO(linuxcnc, "pin:in_:float:0:in:The input value:None:None");
MODULE_INFO(linuxcnc, "pin:out_:float:0:out:The output value:None:None");
MODULE_INFO(linuxcnc, "pin:out-io:float:0:io:The output value, compatible with PID gains:None:None");
MODULE_INFO(linuxcnc, "author:Andy Pugh");
MODULE_INFO(linuxcnc, "license:GPL");
MODULE_INFO(linuxcnc, "funct:_:1:");
MODULE_LICENSE("GPL");
#endif // MODULE_INFO


struct __comp_state {
    struct __comp_state *_next;
    int _personality;
    hal_float_t *in__p;
    hal_float_t *out__p;
    hal_float_t *out_io_p;
    hal_float_t x_val_p[16];
    hal_float_t y_val_p[16];
    unsigned i_p;

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

static int export(char *prefix, long extra_arg, long personality) {
    char buf[HAL_NAME_LEN + 1];
    int r = 0;
    int j = 0;
    int sz = sizeof(struct __comp_state) + __comp_get_data_size();
    struct __comp_state *inst = hal_malloc(sz);
    memset(inst, 0, sz);
    inst->_personality = personality;
    r = extra_setup(inst, prefix, extra_arg);
    if(r != 0) return r;
    personality = inst->_personality;
    r = hal_pin_float_newf(HAL_IN, &(inst->in__p), comp_id,
        "%s.in", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_OUT, &(inst->out__p), comp_id,
        "%s.out", prefix);
    if(r != 0) return r;
    r = hal_pin_float_newf(HAL_IO, &(inst->out_io_p), comp_id,
        "%s.out-io", prefix);
    if(r != 0) return r;
    if((personality) > (16)) {
        rtapi_print_msg(RTAPI_MSG_ERR,"Parameter x-val-##: Requested size %d exceeds max size %d\n",(int)personality, (int)16);
        return -ENOSPC;
    }
    for(j=0; j < (personality); j++) {
        r = hal_param_float_newf(HAL_RW, &(inst->x_val_p[j]), comp_id,
            "%s.x-val-%02d", prefix, j);
        if(r != 0) return r;
    }
    if((personality) > (16)) {
        rtapi_print_msg(RTAPI_MSG_ERR,"Parameter y-val-##: Requested size %d exceeds max size %d\n",(int)personality, (int)16);
        return -ENOSPC;
    }
    for(j=0; j < (personality); j++) {
        r = hal_param_float_newf(HAL_RW, &(inst->y_val_p[j]), comp_id,
            "%s.y-val-%02d", prefix, j);
        if(r != 0) return r;
    }
    inst->i_p = 0.0;
    rtapi_snprintf(buf, sizeof(buf), "%s", prefix);
    r = hal_export_funct(buf, (void(*)(void *inst, long))_, inst, 1, 0, comp_id);
    if(r != 0) return r;
    if(__comp_last_inst) __comp_last_inst->_next = inst;
    __comp_last_inst = inst;
    if(!__comp_first_inst) __comp_first_inst = inst;
    return 0;
}
static int default_count=1, count=0;
RTAPI_MP_INT(count, "number of lincurve");
char *names = ""; // comma separated names
RTAPI_MP_STRING(names, "names of lincurve");
static int personality[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
RTAPI_MP_ARRAY_INT(personality, 64, "personality of each lincurve");

            static int p_value(char* cname, char *name, int idx) {
                int ans = personality[idx%64];
                if (idx >= 64) {
            

                    if (name==NULL) {
                        rtapi_print_msg(RTAPI_MSG_ERR,"%s: instance %d assigned personality=%d(=%#0x)\n",
                                        cname, idx, ans, ans);
                    } else {
                        rtapi_print_msg(RTAPI_MSG_ERR,"%s: name %s assigned personality=%d(=%#0x)\n",
                                        cname, name, ans, ans);
                    }
                }
                return ans;
            }
            
int rtapi_app_main(void) {
    int r = 0;
    int i;
    comp_id = hal_init("lincurve");
    if(comp_id < 0) return comp_id;
    if(count && names[0]) {
        rtapi_print_msg(RTAPI_MSG_ERR,"count= and names= are mutually exclusive\n");
        return -EINVAL;
    }
    if(!count && !names[0]) count = default_count;
    if(count) {
        for(i=0; i<count; i++) {
            char buf[HAL_NAME_LEN + 1];
            rtapi_snprintf(buf, sizeof(buf), "lincurve.%d", i);
            r = export(buf, i, p_value("lincurve", buf, i) );
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
                r = export(buf, idx, p_value("lincurve", buf, idx) );
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
#undef in_
#undef in__ptr
#define in__ptr (__comp_inst->in__p)
#define in_ (0+*__comp_inst->in__p)
#undef out_
#undef out__ptr
#define out__ptr (__comp_inst->out__p)
#define out_ (*__comp_inst->out__p)
#undef out_io
#undef out_io_ptr
#define out_io_ptr (__comp_inst->out_io_p)
#define out_io (*__comp_inst->out_io_p)
#undef x_val
#define x_val(i) (__comp_inst->x_val_p[i])
#undef y_val
#define y_val(i) (__comp_inst->y_val_p[i])
#undef i
#define i (__comp_inst->i_p)
#undef personality
#define personality (__comp_inst->_personality)


#line 43 "/home/end/projects/linuxcnc/src/hal/components/lincurve.comp"

FUNCTION(_){
    double f, x;
    x = in_;
    if (x >= x_val(personality-1)) {
        out_ = y_val(personality-1);
        out_io = out_;
        return;
    }
    if (x <= x_val(0)) {
        out_ = y_val(0);
        out_io = out_;
        return;
    }
    while (x > x_val(i+1)) { i++;}
    while (x < (x_val(i))) { i--;}
    
    f = (x - x_val(i))/(x_val(i+1)-x_val(i));
    out_ = y_val(i) + f * (y_val(i+1) - y_val(i));
    out_io = out_;
}

EXTRA_SETUP(){
	if (personality > 16) personality = 16;
	if (personality < 2) personality = 2;
	return 0;
}

static int __comp_get_data_size(void) { return 0; }
