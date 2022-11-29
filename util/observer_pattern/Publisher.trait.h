#pragma once

#include "../../head.h"

#include "Subscriber.trait.h"

#ifdef constructor
#undef constructor
#endif

#define constructor Publisher


class Publisher
{
  public:
    virtual void notifySubsriber(const NotificationDict&) = 0;

    virtual void addSubscriber(Subscriber* s)
    {
        let index = indexOfFirst(
            *this->subscribers,
            (function<bool(Subscriber*)>)(lambda_ref(Subscriber * subscriber) { return size_t(subscriber) == size_t(s); })
        );

        // Add only if not exist.
        if (index < 0)
        {
            this->subscribers->push_back(s);
        }
    }

    virtual void removeSubscriber(Subscriber* s)
    {
        let index = indexOfFirst(
            *this->subscribers,
            (function<bool(Subscriber*)>)(lambda_ref(Subscriber * subscriber) { return size_t(subscriber) == size_t(s); })
        );

        // If exist
        if (index >= 0)
        {
            std::swap(this->subscribers->at(index), this->subscribers->at(len(*this->subscribers) - 1));
            this->subscribers->pop_back();
        }
    }

  protected:
    SubscriberArray* subscribers = new SubscriberArray();
};