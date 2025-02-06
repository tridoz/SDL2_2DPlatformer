//
// Created by trida on 1/13/25.
//

#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <chrono>
#include <thread>


#include <chrono>

class FPSCounter {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    int frameCount;              // Contatore dei frame
    double fps;                  // Valore attuale degli FPS
    TimePoint lastUpdateTime;    // Tempo dell'ultimo aggiornamento
    const int updateInterval;    // Intervallo di aggiornamento in millisecondi

public:
    // Costruttore con intervallo di aggiornamento personalizzabile
    FPSCounter(int interval = 1000)
        : frameCount(0), fps(0.0), updateInterval(interval),
          lastUpdateTime(Clock::now()) {}

    // Metodo per aggiornare il contatore e calcolare gli FPS
    void update() {
        frameCount++;
        TimePoint currentTime = Clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastUpdateTime
        );

        if (elapsed.count() >= updateInterval) {
            // Calcola gli FPS
            fps = frameCount / (elapsed.count() / 1000.0);

            // Reset del contatore e tempo di riferimento
            frameCount = 0;
            lastUpdateTime = currentTime;
        }
    }

    // Metodo per ottenere l'ultimo valore calcolato degli FPS
    double getFPS() const {
        return fps;
    }
};




#endif //FPSCOUNTER_H
