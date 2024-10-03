#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers

// --- Interface for TicketBooking to follow the Interface Segregation Principle (ISP) ---
class ITicketBooking {
public:
    virtual void bookTicket(const std::string& participantName) = 0;
    virtual ~ITicketBooking() = default;
};

// --- Participant Class ---
class Participant {
    std::string name;
public:
    Participant(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

// --- Event Class (Abstraction for Event Handling) ---
class Event {
protected:
    std::string eventName;
    std::vector<std::shared_ptr<Participant>> participants;

public:
    Event(const std::string& name) : eventName(name) {}

    virtual void createEvent() = 0; // Pure virtual function
    virtual void manageEvent() = 0; // Pure virtual function

    void addParticipant(std::shared_ptr<Participant> participant) {
        participants.push_back(participant);
    }

    std::vector<std::shared_ptr<Participant>> getParticipants() const {
        return participants;
    }

    virtual ~Event() = default;
};

// --- Venue Class for Dependency Injection ---
class Venue {
    std::string location;
    int capacity;
public:
    Venue(const std::string& location, int capacity) : location(location), capacity(capacity) {}

    std::string getLocation() const {
        return location;
    }

    int getCapacity() const {
        return capacity;
    }
};

// --- Concrete Conference Event Class (Liskov Substitution Principle applied here) ---
class Conference : public Event, public ITicketBooking {
    std::shared_ptr<Venue> venue;
public:
    Conference(const std::string& name, std::shared_ptr<Venue> venue)
        : Event(name), venue(venue) {}

    void createEvent() override {
        std::cout << "Conference '" << eventName << "' created at " << venue->getLocation() << " with capacity " << venue->getCapacity() << ".\n";
    }

    void manageEvent() override {
        std::cout << "Managing Conference: " << eventName << "\n";
        std::cout << "Participants list:\n";
        for (const auto& participant : participants) {
            std::cout << "- " << participant->getName() << "\n";
        }
    }

    void bookTicket(const std::string& participantName) override {
        auto participant = std::make_shared<Participant>(participantName);
        addParticipant(participant);
        std::cout << "Ticket booked for " << participantName << " at Conference: " << eventName << "\n";
    }
};

// --- Concrete Party Event Class ---
class Party : public Event, public ITicketBooking {
    std::shared_ptr<Venue> venue;
public:
    Party(const std::string& name, std::shared_ptr<Venue> venue)
        : Event(name), venue(venue) {}

    void createEvent() override {
        std::cout << "Party '" << eventName << "' created at " << venue->getLocation() << " with capacity " << venue->getCapacity() << ".\n";
    }

    void manageEvent() override {
        std::cout << "Managing Party: " << eventName << "\n";
        std::cout << "Participants list:\n";
        for (const auto& participant : participants) {
            std::cout << "- " << participant->getName() << "\n";
        }
    }

    void bookTicket(const std::string& participantName) override {
        auto participant = std::make_shared<Participant>(participantName);
        addParticipant(participant);
        std::cout << "Ticket booked for " << participantName << " at Party: " << eventName << "\n";
    }
};

// --- Event Manager Class (Single Responsibility and Open/Closed Principle) ---
class EventManager {
    std::vector<std::shared_ptr<Event>> events;

public:
    void createEvent(std::shared_ptr<Event> event) {
        event->createEvent();
        events.push_back(event);
    }

    void manageEvents() {
        for (auto& event : events) {
            event->manageEvent();
        }
    }

    void bookTicket(std::shared_ptr<ITicketBooking> event, const std::string& participantName) {
        event->bookTicket(participantName);
    }
};

// --- Main function to demonstrate the Event Management System ---
int main() {
    // Creating a Venue
    auto conferenceVenue = std::make_shared<Venue>("Grand Hall", 200);
    auto partyVenue = std::make_shared<Venue>("Rooftop Lounge", 100);

    // Creating Events
    auto conference = std::make_shared<Conference>("Tech Conference 2024", conferenceVenue);
    auto party = std::make_shared<Party>("Annual Party", partyVenue);

    // Creating EventManager
    EventManager eventManager;

    // Adding events to manager
    eventManager.createEvent(conference);
    eventManager.createEvent(party);

    // Booking tickets
    eventManager.bookTicket(conference, "Alice Johnson");
    eventManager.bookTicket(party, "Bob Smith");

    // Managing all events
    eventManager.manageEvents();

    return 0;
}
