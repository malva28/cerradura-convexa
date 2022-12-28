#include <chrono>
#include <iostream>
#include <fstream>

/*
 * Simple class to set up a clock.
 *
 * Thanks to: https://stackoverflow.com/questions/67686251/how-to-measure-execution-time-of-code-in-deviceopenclgpu
 */
class Clock {
private:
    typedef std::chrono::high_resolution_clock clock;
    std::chrono::time_point<clock> t;
public:
    Clock() { start(); }
    void start() { t = clock::now(); }
    double stop() const { return std::chrono::duration_cast<std::chrono::duration<double>>(clock::now()-t).count(); }
};

