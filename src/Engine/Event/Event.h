#ifndef HYDROGEN_EVENT_H
#define HYDROGEN_EVENT_H

#include <queue>
#include <functional>
#include <utility>
#include "../Core/Base.h"

namespace Engine{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication,
        EventCategoryInput,
        EventCategoryKeyboard,
        EventCategoryMouse,
        EventCategoryMouseButton
    };

    class Event{
    protected:
        EventType type;
        EventCategory category;
    public:
        EventType getType(){return type;}
        EventCategory getCategory(){return category;}
        virtual ~Event() = default;
    public:
        virtual std::string ToString() const = 0;
    };

    class EventBus{
    public:
        EventBus(){};
        void setCallback(std::function<void(const Scope<Event>&)> _callback){callback = std::move(_callback);};
//        void AddEvent(const Event &event){eventBus.push(CreateScope<Event>(event));}
        void AddEvent(Scope<Event> event){eventBus.push(std::move(event));}
        void DispatchAll() {
            while (!eventBus.empty()) {
                callback(eventBus.front());
                eventBus.pop();
            }
        };
    private:
        std::function<void(const Scope<Event>&)> callback;
        std::queue<Scope<Event>> eventBus;
    };
}
#endif //HYDROGEN_EVENT_H
