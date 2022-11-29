#pragma once

#include "../../head.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Subscriber

using NotificationDict = std::map<string, string>;

class Subscriber;

using SubscriberArray = vector<Subscriber*>;

class Subscriber
{
  public:
    virtual void updateFromNotification(NotificationDict info) = 0;
};