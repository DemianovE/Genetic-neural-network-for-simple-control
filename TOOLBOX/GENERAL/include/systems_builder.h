#ifndef SYSTEM_BUILDER_H
#define SYSTEM_BUILDER_H

#include "pid_controller.h"

void selectSystem(float (**func_ptr)(float*), struct PID *pid);

#endif