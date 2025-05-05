#include "object.h"

void Object::handleEvents(SDL_Event &event)
{
    for (auto &child : children_)
    {
        if (child->getActive())
        {
            child->handleEvents(event);
        }
    }
}

void Object::update(float dt)
{
    for (auto &object : object_to_add_)
    {
        addChild(object);

    }
    object_to_add_.clear();

    for (auto it = children_.begin(); it != children_.end();)
    {
        auto child = *it;
        if (child->needRemove())
        {
            it = children_.erase(it);
            child->clean();
            delete child;
            child = nullptr;
        }
        else
        {
            if (child->getActive())
            {
                child->update(dt);
            }
            ++it;
        }
    }
}

void Object::render()
{
    for (auto &child : children_)
    {
        if (child->getActive())
        {
            child->render();
        }
    }
}

void Object::clean()
{
    for (auto &child : children_)
    {
        child->clean();
    }
    children_.clear();
}
