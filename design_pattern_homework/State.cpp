#include <iostream>

class State {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void changeChannel(int chan) = 0;
    virtual void adjustVolume(int vol) = 0;
    virtual ~State() = default;
};

// Context
class TV {
    State *state;

public:
    TV() { setState(new OffState(this)); }
    void setState(State *st) { state = st; }
    void on() { state->on(); }
    void off() { state->off(); }
    void changeChannel(int chan) { state->changeChannel(chan); }
    void adjustVolume(int vol) { state->adjustVolume(vol); }
};

class OffState : public State {
    TV *tv;

public:
    OffState(TV *tv) : tv(tv) {}

    void on() override {
        std::cout << "Turning TV ON.\n";
        tv->setState(new OnState(tv));
    }

    void off() override {
        std::cout << "TV is already OFF.\n";
    }

    void changeChannel(int chan) override {
        std::cout << "Turn on the TV first to change channels.\n";
    }

    void adjustVolume(int vol) override {
        std::cout << "Turn on the TV first to adjust volume.\n";
    }
};

class OnState : public State {
    TV *tv;

public:
    OnState(TV *tv) : tv(tv) {}

    void on() override {
        std::cout << "TV is already ON.\n";
    }

    void off() override {
        std::cout << "Turning TV OFF.\n";
        tv->setState(new OffState(tv));
    }

    void changeChannel(int chan) override {
        std::cout << "Changing channel to " << chan << ".\n";
    }

    void adjustVolume(int vol) override {
        if (vol > 0) {
            std::cout << "Increasing volume by " << vol << ".\n";
        } else {
            std::cout << "Decreasing volume by " << -vol << ".\n";
        }
    }
};

int main() {
    TV my_tv;

    my_tv.on();
    my_tv.on();

    my_tv.changeChannel(11);
    my_tv.adjustVolume(6);
    my_tv.adjustVolume(-4);

    my_tv.off();
    my_tv.changeChannel(22);

    return 0;
}
