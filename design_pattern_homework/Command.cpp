#include <iostream>

class ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

class Receiver {
public:
    void turnOnLights() {
        std::cout << "Turning on the lights.\n";
    }

    void turnOffLights() {
        std::cout << "Turning off the lights.\n";
    }
};

class TurnOnLightsCommand : public ICommand {
    Receiver* receiver;

public:
    TurnOnLightsCommand(Receiver* recv) : receiver(recv) {}

    void execute() override {
        receiver->turnOnLights();
    }
};

class TurnOffLightsCommand : public ICommand {
    Receiver* receiver;

public:
    TurnOffLightsCommand(Receiver* recv) : receiver(recv) {}

    void execute() override {
        receiver->turnOffLights();
    }
};

class Invoker {
    ICommand* command = nullptr;

public:
    void setCommand(ICommand* cmd) {
        command = cmd;
    }

    void executeCommand() {
        if (command) {
            command->execute();
        } else {
            std::cout << "No command set.\n";
        }
    }
};

int main() {
    Receiver receiver;

    TurnOnLightsCommand turnOn(&receiver);
    TurnOffLightsCommand turnOff(&receiver);

    Invoker invoker;
    invoker.setCommand(&turnOn);
    invoker.executeCommand();
    invoker.setCommand(&turnOff);
    invoker.executeCommand();
    return 0;
}
