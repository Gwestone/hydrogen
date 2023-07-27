#ifndef HYDROGEN_KEYEVENT_H
#define HYDROGEN_KEYEVENT_H

#include <string>
#include <sstream>
#include "../Core/KeyCodes.h"
#include "Event.h"

namespace Engine{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }
        bool IsRepeated() const { return isRepeated; }
    protected:
        KeyEvent(const KeyCode keycode)
                : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
        bool isRepeated = false;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode keycode, bool _isRepeat = false)
                : KeyEvent(keycode){
            type = EventType::KeyPressed;
            category = EventCategory::EventCategoryKeyboard;
            isRepeated = _isRepeat;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << isRepeated << ")";
            return ss.str();
        }

        ~KeyPressedEvent() = default;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode keycode)
                : KeyEvent(keycode) {
            type = EventType::KeyReleased;
            category = EventCategory::EventCategoryKeyboard;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode keycode)
                : KeyEvent(keycode) {
            type = EventType::KeyTyped;
            category = EventCategory::EventCategoryKeyboard;
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

    };
}
#endif //HYDROGEN_KEYEVENT_H
