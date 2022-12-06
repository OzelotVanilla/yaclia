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
    virtual void notifySubsriber(const NotificationDict& info)
    {
        // forEach(
        //     *this->subscribers,
        //     (function<void(Subscriber*)>)(lambda_ref(Subscriber * s) { s->updateFromNotification(info); })
        // );

        for (size_t i = 0; i < len(*this->subscribers); i++)
        {
            this->subscribers->at(i)->updateFromNotification(info);
        }
    }

    virtual void addSubscriber(Subscriber* s)
    {
        let index = indexOfFirst(
            *this->subscribers,
            (function<bool(Subscriber*)>)(lambda_ref(Subscriber * subscriber) { return isize(subscriber) == isize(s); })
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
            (function<bool(Subscriber*)>)(lambda_ref(Subscriber * subscriber) { return isize(subscriber) == isize(s); })
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