//
// Created by CaiNot on 2018/9/28 21:36.
//

#include "data.h"

void cainot::work(Route *route[4]) { // 对领域中的车辆进行移动，每次调用都移动一个单位
    /**
     * 线程任务，把路口的车依次清掉一台
     **/
    bool isEnd = true;
    for (int i = 0; i < 4; i++) {
        isEnd = isEnd && route[i]->isEnd();
    }

    while (!isEnd) {
        int vehiclesInOneArea = 0;
        for (int i = 0; i < 4; i++) {
            vehiclesInOneArea = area[i];// area
            for (int j = 0; j < vehiclesInOneArea; j++) {
                /**
                 *  我只需要把应该要离开该路口的车给删掉就好。
                 **/
                Vehicle *v = vehicles[i].front();

                lock_guard<mutex> lockGuard(my_mutex);
                if (v->nowPos == i) {
                    vehicles[i].pop();
                    area[i]--;

                    cout << v->getID() << " from " << v->start << " end at " << v->end << " now at " << i;

                    v->nowPos = (v->nowPos + 1) % 4;
                    if (v->nowPos == v->end) {
                        cout << "\tleave " << ++leaveCars << endl;
                        delete v;
                    } else cout << endl;
                } else {
                    vehicles[i].push(v);// 放到尾部
                    vehicles[i].pop();
                }
            }
        }
        isEnd = true;
        for (int i = 0; i < 4; i++) {
            isEnd = isEnd && (!area[i]) && route[i]->isEnd();
        }
        cout << endl;
    }
}

void cainot::ready(Route *route) {
    while (!route->isEnd()) {
        while (1) {
            lock_guard<mutex> lockGuard(my_mutex);
            if (!route->canMoveVehicle())
                break;
            route->moveVehicle();
        }
    }
}

Vehicle::Vehicle(int s) : start(s), end(rand() % 4) {
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


void Vehicle::setArea() {
    int endPos = this->end;

    if (this->start >= endPos)
        endPos = 4 + this->end;
    for (int i = this->start; i < endPos; i++) {
        this->area.push(i % 4);
    }
}

int Vehicle::setID(int n) {
    this->id = n;
    return this->id;
}

int Vehicle::getID() {
    return this->id;
}


bool Route::canMoveVehicle() { // 设计对象是对等待队列中的第一个做检查
    if (this->vehicles.empty()) {
        return false;
    }
    Vehicle *v = vehicles.front();
    int oneArea = 0;
    queue<int> vArea = v->getArea();
    int count = 0;
    while (!vArea.empty()) {
        oneArea = vArea.front(); // 这不是第一个领域啊。。。！！！这就是第一个！这是队列啊！！！
        count++;
        if (count == 2) { // 两种情况，当第一个领域未被占领，第二个领域有他的同僚时。
            queue<Vehicle *> vQ = cainot::vehicles[oneArea];
            while (!vQ.empty()) {
                if (vQ.front()->start == v->start) {
                    return true;
                }
                vQ.pop();
            }
        }
        if (cainot::area[oneArea] >= 4) { // 当该领域被占领时
            return false;
        }
        vArea.pop();
    }
    return true;
}

void Route::moveVehicle() { // 设计对象是对等待队列中的第一个移动
    Vehicle *v = this->vehicles.front();

    int oneArea = 0;
    queue<int> vArea = v->getArea();
    v->nowPos = v->start;

    while (!vArea.empty()) {
        oneArea = vArea.front();
        vArea.pop();
        cainot::area[oneArea]++;
        cainot::vehicles[oneArea].push(v);
    }

    this->vehicles.pop(); // 每个线程对应不同的this->vehicles。
}

bool Route::isEnd() {
    return this->vehicles.empty();
}

void Route::addVehiclesRandom(int n) {
    Vehicle *v = 0;
    default_random_engine e;
    for (int i = 0; i < n; i++) {
        v = new Vehicle(this->direction, e() % 4);
        v->setID(vehicleNum++);
        this->vehicles.push(v);
        cout << "car " << v->getID() << " end in " << v->end << endl;
    }
    cout << "添加完成，成功添加了" << n << "辆车于方向" << this->direction << endl;
}
