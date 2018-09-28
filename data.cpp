//
// Created by CaiNot on 2018/9/28 21:36.
//
#include "data.h"

void cainot::work() {
    int vehiclesInOneArea = 0;
    for (int i = 0; i < 4; i++) {
        vehiclesInOneArea = area[i];
        for (int j = 0; j < vehiclesInOneArea; j++) {
            Vehicle v = vehicles[i].front();
            v.move();
            vehicles[i].pop();
            vehicles[i].push(v);
        }
    }
}

Vehicle::Vehicle() : start(rand() % 4), end(rand() % 4) {
    this->setArea();
    this->nowPos = -1;
}

Vehicle::Vehicle(int s, int e) : start(s), end(e) {
    this->setArea();
    this->nowPos = -1;
}

inline queue<int> Vehicle::getArea() {
    return this->area;
}

bool Vehicle::move() {
    if (nowPos == -1) { // 原来在等待队列
        nowPos = this->start;
    } else {
        cainot::area[nowPos]++; // 原区域不再被占用
        cainot::vehicles[nowPos].pop();
        this->area.pop(); // 已经走过了的区域就去除掉
        nowPos++; // 向前移动一个单位
    }
    return nowPos <= end; // 如果已到达终点，则最后再移动一步就OK了，取==是为了方便代码编写
}

void Vehicle::setArea() {
    int endPos = this->end;

    if (this->start >= endPos)
        endPos = 4 + this->end;
    for (int i = this->start; i < endPos; i++) {
        this->area.push(i % 4);
    }
}

bool Route::canMoveVehicle() { // 设计对象是对等待队列中的第一个做检查
    if (vehicles.empty()) {
        return false;
    }
    Vehicle v = vehicles.front();
    int oneArea = 0;
    queue<int> vArea = v.getArea();
    while (!vArea.empty()) {
        oneArea = vArea.front();
        if (cainot::area[oneArea] <= 0) {
            return false;
        }
        vArea.pop();
    }
    return true;
}

void Route::moveVehicle() { // 设计对象是对等待队列中的第一个移动
    Vehicle v = vehicles.front();
    int oneArea = 0;
    queue<int> vArea = v.getArea();

    while (!vArea.empty()) {
        oneArea = vArea.front();

        cainot::area[oneArea]--;
        cainot::vehicles[oneArea].push(v);

        vArea.pop();
    }
    v.move();
    this->vehicles.pop();

}
