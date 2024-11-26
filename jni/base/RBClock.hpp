//
//  RBClock.hpp
//
//  The OpenGL Tutorial
//  This code was written as part of a tutorial at https://medium.com/@rogerboesch/
//
//  Created by Roger Boesch on 07/30/2018.
//
//  DISCLAIMER:
//  The intention of this tutorial is not to always write the best possible code but
//  to show different ways to create a game or app that even can be published.
//  I will also refactor a lot during the tutorial and improve things step by step
//  or even show completely different approaches.
//
//  Feel free to use the code in the way you want :)
//

#pragma once

#include <string>
#include <chrono>

class RBClock {
public:
    RBClock();

    void Reset();
    float Delta();
    float Duration();
    static long Current();

private:
    bool m_firstTime = false;
    std::chrono::high_resolution_clock::time_point m_timestamp;
};