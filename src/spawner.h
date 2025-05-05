#ifndef SPAWNER_H
#define SPAWNER_H

#include "core/object.h"

class Player;
class Spawner : public Object
{
protected:
    int num_ = 20;
    float timer_ = 0.0f;
    float interval_ = 3.0f;

    Player* target_ = nullptr;

public:

    virtual void update(float dt) override;

    // getters and setters
    int getNum() { return num_; }
    void setNum(int num) { num_ = num; }
    float getInterval() { return interval_; }
    void setInterval(float interval) { interval_ = interval; }
    Player* getTarget() { return target_; }
    void setTarget(Player* player) { target_ = player; }

    // constructor
};


#endif // SPAWNER_H