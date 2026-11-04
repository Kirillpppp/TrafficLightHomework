#include "TrafficLight.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace
{
    // Учебная модель работы светофора (не реальное расписание перекрёстка):
    // 00-05 — жёлтый; 06-30 — зелёный; 31-35 — жёлтый; 36-59 — красный.
    TrafficLightsState GetStateForSecond(int seconds)
    {
        if (seconds >= 0 && seconds <= 5)
        {
            return TrafficLightsState::YELLOW;
        }
        if (seconds >= 6 && seconds <= 30)
        {
            return TrafficLightsState::GREEN;
        }
        if (seconds >= 31 && seconds <= 35)
        {
            return TrafficLightsState::YELLOW;
        }
        return TrafficLightsState::RED;
    }

    // Рисует лампу нужным цветом, неактивные лампы — серым.
    void PrintLamp(TrafficLightsState lamp, TrafficLightsState current,
                   const char* color, const char* name)
    {
        const char* lampColor = (lamp == current) ? color : "\033[90m";
        std::cout << "  " << lampColor << "(O)\033[0m " << name;
        if (lamp == current)
        {
            std::cout << " <-- горит";
        }
        std::cout << '\n';
    }
}

TrafficLight::TrafficLight(const Address& address) : address(address)
{
}

TrafficLightsState TrafficLight::GetCurrentState() const
{
    // Фиксируем текущее время.
    auto now = std::chrono::system_clock::now();
    // Приводим к секундам с начала эпохи.
    auto now_sec = std::chrono::floor<std::chrono::seconds>(now).time_since_epoch();
    // Получаем секунды текущей минуты (0-59).
    int seconds = static_cast<int>((now_sec % 60).count());

    return GetStateForSecond(seconds);
}

void TrafficLight::GetInfo() const
{
    TrafficLightsState state = GetCurrentState();

    // Местное время компьютера, чтобы было видно момент обновления.
    std::time_t currentTime = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    std::cout << "\n========== СВЕТОФОР ==========\n";
    std::cout << "Страна: " << address.country << '\n';
    std::cout << "Город: " << address.city << '\n';
    std::cout << "Улица: " << address.street << '\n';
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Координаты: " << address.latitude << ", " << address.longitude << '\n';
    std::cout << "Время: " << std::put_time(&localTime, "%H:%M:%S") << '\n';

    std::cout << "Текущий цвет: ";
    switch (state)
    {
    case TrafficLightsState::RED:
        std::cout << "КРАСНЫЙ\n";
        break;
    case TrafficLightsState::YELLOW:
        std::cout << "ЖЁЛТЫЙ\n";
        break;
    case TrafficLightsState::GREEN:
        std::cout << "ЗЕЛЁНЫЙ\n";
        break;
    }

    std::cout << '\n';
    PrintLamp(TrafficLightsState::RED, state, "\033[31m", "Красный");
    PrintLamp(TrafficLightsState::YELLOW, state, "\033[33m", "Жёлтый");
    PrintLamp(TrafficLightsState::GREEN, state, "\033[32m", "Зелёный");
    std::cout << "==============================\n";
}
