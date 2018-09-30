//
// Created by CaiNot on 2018/9/28 21:35.
//

#ifndef THREADCARS_HEAD_H
#define THREADCARS_HEAD_H

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

#define W 0
#define S 1
#define E 2
#define N 3

using namespace std;

mutex my_mutex;

class Vehicle;
class Route;

namespace cainot {
    int area[4] = {4, 4, 4, 4};
    queue<Vehicle> vehicles[4];

    void work();
    void ready(Route route);
}

class Vehicle {
public:
    int nowPos;
    const int start;

    Vehicle();

    Vehicle(int s, int e);

    inline queue<int> getArea();

    bool move();

private:
    void setArea();

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

    void setRandom();

    bool isEnd();

    bool canMoveVehicle();

    void moveVehicle();
};

#endif //THREADCARS_HEAD_H
