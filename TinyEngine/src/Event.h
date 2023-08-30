#pragma once
#include <sstream>
#include <string>

namespace TE
{
    enum class ETriggerEvent
    {
        None,
        Pressed,
        Released,
        Repeat
    };

    class Event
    {
    public:
        virtual std::string ToString() const = 0;
    };

    class InputEvent : public Event
    {
    public:
        InputEvent(int key, ETriggerEvent triggerEvent)
            : Key(key), TriggerEvent(triggerEvent) { }
    
        std::string ToString() const override
        {
            std::stringstream ss;
            std::string triggerEventStr = "";
            switch (TriggerEvent)
            {
            case ETriggerEvent::Pressed: triggerEventStr = "Pressed ";
                break;
            case ETriggerEvent::Released: triggerEventStr = "Released ";
                break;
            case ETriggerEvent::Repeat: triggerEventStr = "Repeat ";
                break;
            default: ;
            }
            ss << "InputEvent: " << triggerEventStr << Key;
            return ss.str();
        }

    private:
        int Key;
        ETriggerEvent TriggerEvent;
    };
 
}
