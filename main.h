#pragma once

#include "head.h"
#include "./system/signal/signal.h"
#include "./system/sys_call.h"
#include "view/manager/ViewManager.h"


void registerAllSignalHandler();

void onInterrupt(int sig);