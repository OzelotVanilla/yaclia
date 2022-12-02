#pragma once

#include "../../head.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Subscriber

using NotificationDict = std::map<string, string>;

inline bool dictCheckEqual(const NotificationDict& d, const string& key, const string& value)
{
    return d.contains(key) and (d.at(key) == value);
}

class Subscriber;

using SubscriberArray = vector<Subscriber*>;

class Subscriber
{
  public:
    virtual void updateFromNotification(const NotificationDict& info) = 0;
};