#ifndef TIMER_H
#define TIMER_H


#include "../core/object.h"

class Timer : public Object
{
protected:
    float timer_ = 0;
    float interval_ = 3.0f;
    bool time_out_ = false;

public:
    static Timer* addTimerChild(Object* parent, float interval = 3.0f);

    virtual void update(float dt) override;

    void start() { is_active_ = true; }
    void stop() { is_active_ = false; }
    bool timeOut();
    float getProgress() {return timer_ / interval_; }

    // getters and setters
    void setTimer(float timer) { timer_ = timer; }
    void setInterval(float interval) { interval_ = interval; }
    float getTimer() { return timer_; }
    float getInterval() { return interval_; }
};




#endif // TIMER_H