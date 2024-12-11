#include <iostream>
#include <string>

// Subsystem 1: Light Control
class LightControl {
public:
    void turnOnLights() { std::cout << "Lights are ON.\n"; }
    void turnOffLights() { std::cout << "Lights are OFF.\n"; }
};

// Subsystem 2: Fan Control
class FanControl {
public:
    void turnOnFan() { std::cout << "Fan is ON.\n"; }
    void turnOffFan() { std::cout << "Fan is OFF.\n"; }
};

// Subsystem 3: Security System
class SecuritySystem {
public:
    void armSystem() { std::cout << "Security system ARMED.\n"; }
    void disarmSystem() { std::cout << "Security system DISARMED.\n"; }
};

// Facade: Home Automation
class HomeAutomationFacade {
    LightControl* lights;
    FanControl* fan;
    SecuritySystem* security;

public:
    HomeAutomationFacade() {
        lights = new LightControl();
        fan = new FanControl();
        security = new SecuritySystem();
    }

    ~HomeAutomationFacade() {
        delete lights;
        delete fan;
        delete security;
    }

    void leaveHome() {
        std::cout << "Leaving home...\n";
        lights->turnOffLights();
        fan->turnOffFan();
        security->armSystem();
    }

    void arriveHome() {
        std::cout << "Arriving home...\n";
        lights->turnOnLights();
        fan->turnOnFan();
        security->disarmSystem();
    }
};

int main() {
    HomeAutomationFacade* home = new HomeAutomationFacade();

    home->arriveHome();
    std::cout << std::endl;
    home->leaveHome();

    delete home;
    return 0;
}