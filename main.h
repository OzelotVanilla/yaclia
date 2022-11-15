#pragma once

#include "head.h"
#include "./system/signal/UnixSignal.h"
#include "./system/sys_call.h"
#include "view/container/ConsoleConfig.h"
#include "view/container/Screen.h"
#include "view/manager/ViewManager.h"


void registerAllSignalHandler();

void onInterrupt(int sig);