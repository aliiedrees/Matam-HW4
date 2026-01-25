#include "EventFactory.h"

std::vector<std::unique_ptr<Event>> EventFactory::eventsQueue;

EventFactory::EventFactory() {
    eventMap["Snail"] = []() { return std::make_unique<Snail>(); };
    eventMap["Slime"] = [](){ return std::make_unique<Slime>();};
    eventMap["Balrog"] = []() { return std::make_unique<Balrog>(); };
    eventMap["Pack"] = []() { return std::make_unique<Pack>(); };
    eventMap["SolarEclipse"] = []() { return std::make_unique<SolarEclipse>(); };
    eventMap["PotionsMerchant"] = []() { return std::make_unique<PotionsMerchant>(); };
}

std::unique_ptr<Pack> EventFactory::createPack(std::istream& eventsStream) {
    int packSize;
    if (!(eventsStream >> packSize) || packSize <= 0) {
        throw std::runtime_error("Invalid Events File");
    }

    std::vector<std::unique_ptr<Encounter>> packMembers;
    for (int i = 0; i < packSize; i++) {
        std::string eventName;
        if (!(eventsStream >> eventName)) {
            throw std::runtime_error("Invalid Events File");
        }

        if (eventName == "Pack") { // pack includes pack
            auto nestedPack = EventFactory::createPack(eventsStream); 
            packMembers.push_back(std::move(nestedPack));
        } else {
            std::unique_ptr<Event> event = createEvent(eventName);
            Encounter* rawMonsterPtr = dynamic_cast<Encounter*>(event.get());
            
            if (rawMonsterPtr) {
            event.release(); 

            packMembers.push_back(std::unique_ptr<Encounter>(rawMonsterPtr));
        } else {
            throw std::runtime_error("Invalid Events File");
        }
        }
    }

    return Pack::createPack(std::move(packMembers), packSize);
}
std::unique_ptr<Event> EventFactory::createEvent(std::string eventName){
    auto p = eventMap.find(eventName);
    if (p == eventMap.end()) {
        throw std::runtime_error("Invalid Events File");
    }
    return p->second();
}
void EventFactory::loadEvents(std::istream& eventsStream) {
    if (!eventsStream) {
        throw std::runtime_error("Invalid Events File");
    }

    std::string eventName;
    while (eventsStream >> eventName) {
        if (eventName == "Pack") {
            auto pack = EventFactory::createPack(eventsStream);
            EventFactory::eventsQueue.push_back(std::move(pack));
        } else {
            auto event = createEvent(eventName);
            EventFactory::eventsQueue.push_back(std::move(event));
        }
    }
}