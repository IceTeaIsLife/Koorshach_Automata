#include "pneumo.h"
#include "stdbool.h"
#include <limits.h>

#define TIMEOUT_DELTA(timeout)  ((timeout) * 1000)
#define DELAY_DELTA(delay)      ((delay) * 1000)
#define TIMEOUT_GE(engine) \
( (engine)->timeout > (engine)->timeouts[(engine)->state] )
#define DELAY_GE(engine) \
( (engine)->delay > (engine)->delays[(engine)->state] )
// проверка нахождения цилиндра в определенном положении
#define IS_IN_POS(engine, cylinder, position) ( (engine)->cylinders[cylinder].input_signal[position] )

//инициализация
bool engine_init(struct PneumoEngine *engine) {
    if (0 == engine)
        return false;
    engine->cylinders[CYLINDER_1].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_1].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_1].output = 0;

    engine->cylinders[CYLINDER_2].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_2].output = 0;

    engine->cylinders[CYLINDER_3].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_3].output = 0;

    engine->cylinders[CYLINDER_4].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_4].output = 0;

    engine->cylinders[CYLINDER_5].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_5].output = 0;

    engine->cylinders[CYLINDER_6].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_6].output = 0;

    engine->cylinders[CYLINDER_7].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_7].output = 0;

    engine->cylinders[CYLINDER_8].input[SIGNAL_UP] = 0;
    engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN] = 0;
    engine->cylinders[CYLINDER_8].output = 0;

    engine->state = STATE_INIT;
    engine->timeout = 0;
    engine->delay = 0;
    engine->timeouts[STATE_INIT] = INT_MAX;
    engine->delays[STATE_INIT] = INT_MAX;
    engine->timeouts[STATE_0] = TIMEOUT_DELTA(56);
    engine->delays[STATE_0] = DELAY_DELTA(78);
    engine->timeouts[STATE_1] = TIMEOUT_DELTA(56);
    engine->delays[STATE_1] = DELAY_DELTA(45);
    engine->timeouts[STATE_2] = TIMEOUT_DELTA(120);
    engine->delays[STATE_2] = DELAY_DELTA(45);
    engine->timeouts[STATE_3] = TIMEOUT_DELTA(56);
    engine->delays[STATE_3] = DELAY_DELTA(70);
    engine->timeouts[STATE_4] = TIMEOUT_DELTA(60);
    engine->delays[STATE_4] = DELAY_DELTA(60);
    engine->timeouts[STATE_5] = TIMEOUT_DELTA(60);
    engine->delays[STATE_5] = DELAY_DELTA(78);
    engine->timeouts[STATE_6] = TIMEOUT_DELTA(45);
    engine->delays[STATE_6] = DELAY_DELTA(33);
    engine->timeouts[STATE_7] = TIMEOUT_DELTA(56);
    engine->delays[STATE_7] = DELAY_DELTA(78);
    engine->timeouts[STATE_8] = TIMEOUT_DELTA(45);
    engine->delays[STATE_8] = DELAY_DELTA(33);
    engine->timeouts[STATE_9] = TIMEOUT_DELTA(45);
    engine->delays[STATE_9] = DELAY_DELTA(78);
    engine->timeouts[STATE_10] = TIMEOUT_DELTA(45);
    engine->delays[STATE_10] = DELAY_DELTA(33);
    engine->timeouts[STATE_11] = TIMEOUT_DELTA(60);
    engine->delays[STATE_11] = DELAY_DELTA(60);
    engine->timeouts[STATE_12] = TIMEOUT_DELTA(120);
    engine->delays[STATE_12] = DELAY_DELTA(70);
    engine->timeouts[STATE_13] = TIMEOUT_DELTA(45);
    engine->delays[STATE_13] = DELAY_DELTA(78);
    engine->timeouts[STATE_14] = TIMEOUT_DELTA(120);
    engine->delays[STATE_14] = DELAY_DELTA(45);
    engine->timeouts[STATE_15] = TIMEOUT_DELTA(56);
    engine->delays[STATE_15] = DELAY_DELTA(70);
    engine->timeouts[STATE_16] = TIMEOUT_DELTA(56);
    engine->delays[STATE_16] = DELAY_DELTA(70);
    engine->timeouts[STATE_17] = TIMEOUT_DELTA(56);
    engine->delays[STATE_17] = DELAY_DELTA(78);
}


bool engine_tick(struct PneumoEngine *engine) {
    bool ret = true;
    if (0 == engine)
        return false;
    switch (engine->state) {
        case STATE_INIT: {
            engine->state = STATE_0;
            engine->delay = 0;
            engine->timeout = 0;
            break;
        }
        case STATE_0: {
            engine->cylinders[CYLINDER_1].output = 0;
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 0;
            engine->cylinders[CYLINDER_7].output = 0;
            engine->cylinders[CYLINDER_8].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_1;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_1: {
            engine->cylinders[CYLINDER_1].output = 1;
            engine->cylinders[CYLINDER_2].output = 1;
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_5].output = 1;
            engine->cylinders[CYLINDER_6].output = 1;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 1;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_2;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_3;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_2: {
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_6].output = 0;
            if (engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_3;
                    engine->timeout = 0;
                    engine->delay = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_3: {
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_7].output = 0;
            if (engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_4;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_12;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_4: {
            engine->cylinders[CYLINDER_1].output = 0;
            engine->cylinders[CYLINDER_2].output = 1;
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 1;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_5;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_16;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_5: {
            engine->cylinders[CYLINDER_1].output = 1;
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_5].output = 1;
            engine->cylinders[CYLINDER_7].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_6;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_7;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_6: {
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_6].output = 0;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 1;
            if (engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_7;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_7: {
            engine->cylinders[CYLINDER_1].output = 0;
            engine->cylinders[CYLINDER_2].output = 1;
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 1;
            engine->cylinders[CYLINDER_7].output = 0;
            engine->cylinders[CYLINDER_8].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_8;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_14;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_8: {
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_5].output = 1;
            engine->cylinders[CYLINDER_6].output = 0;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 1;
            if (engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_9;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_9: {
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 1;
            if (engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_10;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_10: {
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_6].output = 0;
            if (engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_11;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_11: {
            engine->cylinders[CYLINDER_1].output = 1;
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_7].output = 0;
            engine->cylinders[CYLINDER_8].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_12;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_12: {
            engine->cylinders[CYLINDER_2].output = 1;
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_5].output = 1;
            engine->cylinders[CYLINDER_6].output = 1;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 1;
            if (engine->cylinders[CYLINDER_2].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_13;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_13: {
            engine->cylinders[CYLINDER_1].output = 0;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_6].output = 0;
            engine->cylinders[CYLINDER_7].output = 0;
            if (engine->cylinders[CYLINDER_1].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_14;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_14: {
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 1;
            if (engine->cylinders[CYLINDER_2].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_3].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_5].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_15;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_15: {
            engine->cylinders[CYLINDER_4].output = 1;
            engine->cylinders[CYLINDER_7].output = 1;
            engine->cylinders[CYLINDER_8].output = 0;
            if (engine->cylinders[CYLINDER_4].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_16;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_16: {
            engine->cylinders[CYLINDER_2].output = 1;
            engine->cylinders[CYLINDER_6].output = 0;
            if (engine->cylinders[CYLINDER_2].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_DOWN]) {
                engine->timeout = 0;
                if (DELAY_GE(engine)) {
                    engine->state = STATE_17;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_17: {
            engine->cylinders[CYLINDER_3].output = 1;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_6].output = 1;
            engine->cylinders[CYLINDER_7].output = 0;
            engine->cylinders[CYLINDER_8].output = 1;
            if (engine->cylinders[CYLINDER_3].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_4].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_6].input[SIGNAL_UP] &&
                engine->cylinders[CYLINDER_7].input[SIGNAL_DOWN] &&
                engine->cylinders[CYLINDER_8].input[SIGNAL_UP]) {
                if (DELAY_GE(engine)) {
                    engine->state = STATE_0;
                    engine->delay = 0;
                    engine->timeout = 0;
                }
            } else if (TIMEOUT_GE(engine)) {
                engine->state = STATE_ERROR;
                engine->delay = 0;
                engine->timeout = 0;
            } else {
                engine->delay = 0;
            }
            break;
        }
        case STATE_ERROR: {
            engine->cylinders[CYLINDER_1].output = 0;
            engine->cylinders[CYLINDER_2].output = 0;
            engine->cylinders[CYLINDER_3].output = 0;
            engine->cylinders[CYLINDER_4].output = 0;
            engine->cylinders[CYLINDER_5].output = 0;
            engine->cylinders[CYLINDER_6].output = 0;
            engine->cylinders[CYLINDER_7].output = 0;
            engine->cylinders[CYLINDER_8].output = 0;
            ret = false;
            break;
        }
    }
    engine->timeout++;
    engine->delay++;
    return ret;
}
