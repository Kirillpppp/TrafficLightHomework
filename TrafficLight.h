#pragma once

#include <string>

// Адрес, по которому установлен светофор.
struct Address
{
    std::string country;
    std::string city;
    std::string street;
    double latitude;
    double longitude;
};

/// <summary>
/// Состояния цветов светофора
/// </summary>
enum TrafficLightsState
{
    RED, YELLOW, GREEN
};

class TrafficLight
{
private:
    Address address;

public:
    // Конструктор получает адрес светофора.
    explicit TrafficLight(const Address& address);

    // Определяет состояние светофора по секундам текущей минуты.
    TrafficLightsState GetCurrentState() const;

    // Печатает адрес и текущее состояние светофора.
    void GetInfo() const;
};
