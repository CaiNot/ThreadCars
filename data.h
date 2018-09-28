//
// Created by CaiNot on 2018/9/28 21:35.
//

#ifndef THREADCARS_HEAD_H
#define THREADCARS_HEAD_H

#include <iostream>
#include <vector>
#include <thread>
#include <queue>

#define W 0
#define S 1
#define E 2
#define N 3

using namespace std;

class Vehicle;

namespace cainot {
    int area[4] = {4, 4, 4, 4};
    queue<Vehicle> vehicles[4];

    void work();
}

class Vehicle {
public:
    int nowPos;

    Vehicle();

    Vehicle(int s, int e);

    inline queue<int> getArea();

    bool move();

private:
    void setArea();

    const int start;
    const int end;

    queue<int> area;
};


class Route {
    const int direction;
public:
    queue<Vehicle> vehicles;

    Route(int d) : direction(d) {}

    inline int getDirection() {
        return direction;
    }

    bool canMoveVehicle();

    void moveVehicle();
};

#endif //THREADCARS_HEAD_H
