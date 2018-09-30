//
// Created by CaiNot on 2018/9/28 21:36.
//
#include "data.h"

void cainot::work() { // 对领域中的车辆进行移动，每次调用都移动一个单位
    int vehiclesInOneArea = 0;
    for (int i = 0; i < 4; i++) {
        vehiclesInOneArea = area[i];
        for (int j = 0; j < vehiclesInOneArea; j++) {
            Vehicle v = vehicles[i].front();
            cout << v.nowPos << "->";
            v.move();
            cout << v.nowPos << "," << endl;
            /**
             * 把v放到最后面去。
             */

            lock_guard<mutex> lockGuard(my_mutex);// 修改变量时对其锁定。

            vehicles[i].pop();
            vehicles[i].push(v);
        }
    }
}

void cainot::ready(Route route) {
    while (!route.isEnd()) {
        while (route.canMoveVehicle()) {
            route.moveVehicle();
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

        lock_guard<mutex> lockGuard(my_mutex);// 修改变量时对其锁定。

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
    int count = 0;
    while (!vArea.empty()) {
        oneArea = vArea.front();
        count++;
        if (count == 2) { // 两种情况，当第一个领域未被占领，第二个领域有他的同僚时。
            queue<Vehicle> vQ = cainot::vehicles[oneArea];
            while (!vQ.empty()) {
                if (vQ.front().start == v.start) {
                    return true;
                }
                vQ.pop();
            }
        }
        if (cainot::area[oneArea] <= 0) { // 当该领域被占领时
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
        vArea.pop();

        lock_guard<mutex> lockGuard(my_mutex);// 修改变量时对其锁定。
        cainot::area[oneArea]--;
        cainot::vehicles[oneArea].push(v);
    }
    v.move();

    this->vehicles.pop(); // 每个线程对应不同的this->vehicles。
}

bool Route::isEnd() {
    return this->vehicles.empty();
}

void Route::setRandom() {

}
