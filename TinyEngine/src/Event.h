#pragma once
#include <sstream>
#include <string>

#define TE_BIND(FuncPtr) std::bind(FuncPtr, this, std::placeholders::_1)

namespace TE
{
    enum class EEventType
    {
        InputEvent, OtherEvent
    };
    
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
        virtual EEventType GetType() const = 0;
    };
    
    class OtherEvent : public Event
    {
    public:
        std::string ToString() const override { return std::string("OtherEvent"); }
        EEventType GetType() const override { return EEventType::OtherEvent; }
        static EEventType GetStaticType()  { return EEventType::OtherEvent; }
    };   

    class InputEvent : public Event
    {
    public:
        InputEvent(int key, ETriggerEvent triggerEvent)
            : Key(key), TriggerEvent(triggerEvent) { }

        
        EEventType GetType() const override { return EEventType::InputEvent; }
        static EEventType GetStaticType() { return EEventType::InputEvent; }
        
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

        int GetKey() const { return Key; }

    private:
        int Key;

    private:
        ETriggerEvent TriggerEvent;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : event(event)
        {}

        template<typename T, typename F>
        void Dispatch(const F& func)
        {
            if(event.GetType() == T::GetStaticType())
            {
                func(static_cast<T&>(event));
            }                
        }
    private:
        Event& event;
    };
}
