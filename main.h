#pragma once

#include "head.h"
#include "./system/signal/signal.h"
#include "./system/sys_call.h"
#include "view/manager/ViewManager.h"

bool main_process_can_run = true;

void registerAllSignalHandler();

void onInterrupt(int sig);
void onTerminate(int sig);
