//
// Created by bluejoe on 2018/6/8.
//

#ifndef POORREVERSI_TIME_H
#define POORREVERSI_TIME_H

#include<chrono>
#include<string>

namespace comjTimer {
    class timer {
        typedef std::chrono::steady_clock::time_point tp;
        typedef std::chrono::duration<double> dd;
        typedef std::chrono::steady_clock sc;
    private:
        tp _begin;
        dd _span;
    public:
        timer()
                : _begin(tp()), _span(dd(0)) {}

        void start() {
            _begin = sc::now();
        }

        double getTime() {
            tp _end = sc::now();
            _span = std::chrono::duration_cast<dd>(_end - _begin);
            return _span.count();
        }

        ~timer()
        = default;
    };

} // namespace

#endif //POORREVERSI_TIME_H
