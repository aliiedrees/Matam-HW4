#pragma once
#include <functional>
#include <map>
#include <memory> // Fixed incomplete include
#include <string>
#include "Event.h"
#include <stdexcept>
#include <istream>

class EventFactory {
private:
    // Map specific strings (e.g., "LoginEvent") to a lambda that creates that object
    std::map<std::string, std::function<std::unique_ptr<Event>()>> eventMap;
public:
    static std::vector<std::unique_ptr<Event>> eventsQueue;
    ~EventFactory() = default;
    EventFactory();
    void loadEvents(std::istream& eventsStream);
    std::unique_ptr<Event> createEvent(std::string eventName);
    std::unique_ptr<Pack> createPack(std::istream& eventsStream);
};