#ifndef KOORSHACH_AUTOMATA_PNEUMO_H
#define KOORSHACH_AUTOMATA_PNEUMO_H

#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

enum PneumoState {
    STATE_INIT = 0, STATE_0, STATE_1, STATE_2,
    STATE_3, STATE_4, STATE_5, STATE_6, STATE_7,
    STATE_8, STATE_9, STATE_10, STATE_11, STATE_12,
    STATE_13, STATE_14, STATE_15, STATE_16, STATE_17,
    STATE_ERROR
};

#define SIGNAL_UP 0
#define SIGNAL_DOWN 1

struct PneumoCylinder{
    int input[2];
    int output;
};
#define CYLINDER_1 0
#define CYLINDER_2 1
#define CYLINDER_3 2
#define CYLINDER_4 3
#define CYLINDER_5 4
#define CYLINDER_6 5
#define CYLINDER_7 6
#define CYLINDER_8 7
struct PneumoEngine {
    enum PneumoState state;
    float timeout;
    float delay;
    float timeouts[STATE_ERROR];
    float delays[STATE_ERROR];
    struct PneumoCylinder cylinders[8];
};

bool engine_init(struct PneumoEngine *engine);
bool engine_tick(struct PneumoEngine *engine);

#if defined(__cplusplus)
}
#endif

#endif
