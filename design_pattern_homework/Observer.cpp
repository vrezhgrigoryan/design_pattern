#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class Observer;

template <typename T>
class Observable {
    std::vector<Observer<T> *> observers;

public:
    void subscribe(Observer<T> *observer) { observers.push_back(observer); }
    void unsubscribe(Observer<T> *observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
            observers.erase(it);
    }
    void notify(T &source, const std::string &fieldName, const std::string &newValue) {
        for (auto observer : observers) {
            observer->fieldChanged(source, fieldName, newValue);
        }
    }
};

// Publisher - Concrete Observable
class WeatherStation : public Observable<WeatherStation> {
    float temperature;
    float humidity;

public:
    WeatherStation(float temp, float hum) : temperature(temp), humidity(hum) {}

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }

    void setTemperature(float temp) {
        if (this->temperature == temp)
            return;
        temperature = temp;
        notify(*this, "Temperature", std::to_string(temp));
    }

    void setHumidity(float hum) {
        if (this->humidity == hum)
            return;
        humidity = hum;
        notify(*this, "Humidity", std::to_string(hum));
    }
};

// Observer
template <typename T>
class Observer {
public:
    virtual void fieldChanged(T &source, const std::string &fieldName, const std::string &newValue) = 0;
};

// Concrete Observer 1: Phone Display
class PhoneDisplay : public Observer<WeatherStation> {
public:
    void fieldChanged(WeatherStation &station, const std::string &fieldName, const std::string &newValue) override {
        if (fieldName == "Temperature") {
            std::cout << "Phone Display: Temperature updated to " << newValue << "°C." << std::endl;
        } else if (fieldName == "Humidity") {
            std::cout << "Phone Display: Humidity updated to " << newValue << "%." << std::endl;
        }
    }
};

// Concrete Observer 2: Window Display
class WindowDisplay : public Observer<WeatherStation> {
public:
    void fieldChanged(WeatherStation &station, const std::string &fieldName, const std::string &newValue) override {
        if (fieldName == "Temperature") {
            std::cout << "Window Display: Temperature is now " << newValue << "°C." << std::endl;
        } else if (fieldName == "Humidity") {
            std::cout << "Window Display: Humidity is now " << newValue << "%." << std::endl;
        }
    }
};

int main() {
    WeatherStation station(25.0f, 60.0f);

    PhoneDisplay phone;
    WindowDisplay window;

    station.subscribe(&phone);
    station.subscribe(&window);

    std::cout << "Initial Weather Conditions:" << std::endl;
    station.setTemperature(26.0f);
    station.setHumidity(55.0f);

    std::cout << "\nUnsubscribing Phone Display..." << std::endl;
    station.unsubscribe(&phone);

    station.setTemperature(27.5f);
    station.setHumidity(50.0f);

    return 0;
}