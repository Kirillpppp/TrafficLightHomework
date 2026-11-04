#include <chrono>
#include <iostream>
#include <thread>

#include "TrafficLight.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    // Поддержка русского текста и ANSI-цветов в консоли Windows.
    SetConsoleOutputCP(CP_UTF8);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (console != INVALID_HANDLE_VALUE && GetConsoleMode(console, &mode))
    {
        SetConsoleMode(console, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif

    // Тестовый адрес: перекрёсток Сибуя, Токио, Япония.
    Address address{
        "Япония",
        "Токио",
        "Перекрёсток Сибуя (Shibuya Crossing)",
        35.659500,
        139.700500
    };

    TrafficLight trafficLight(address);
    using namespace std::chrono_literals;

    // Печатаем информацию каждые 23 секунды.
    while (true)
    {
        trafficLight.GetInfo();
        std::cout << "Следующее обновление через 23 секунды. "
                     "Для остановки нажмите Ctrl+C.\n";
        std::this_thread::sleep_for(23000ms);
    }
}
