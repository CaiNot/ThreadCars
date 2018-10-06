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
#include <random>


using namespace std;

static mutex my_mutex;
static int vehicleNum = 0;
static vector<int> result;

class Vehicle;

class Route;

namespace cainot {
    static int area[4] = {0, 0, 0, 0};
    static queue<Vehicle *> vehicles[4];
    static int leaveCars=0;

    void work(Route *route[4]);

    void ready(Route *route);
}

class Vehicle {
public:
    int nowPos;
    const int start;
    const int end;

    Vehicle(int s);

    Vehicle(int s, int e);

    int setID(int n);

    int getID();

    inline queue<int> getArea();

    bool move();

    void showLast();

private:
    void setArea();

    int id;

    queue<int> area;
};


class Route {
    const int direction;
public:
    queue<Vehicle *> vehicles;

    Route(int d) : direction(d) {}

    inline int getDirection() {
        return direction;
    }

    void addVehiclesRandom(int n);

    bool isEnd();

    bool canMoveVehicle();

    void moveVehicle();
};

#endif //THREADCARS_HEAD_H
