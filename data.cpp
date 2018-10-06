//
// Created by CaiNot on 2018/9/28 21:36.
//

#include "data.h"

void cainot::work(Route *route[4]) { // �������еĳ��������ƶ���ÿ�ε��ö��ƶ�һ����λ
    /**
     * �߳����񣬰�·�ڵĳ��������һ̨
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
                 *  ��ֻ��Ҫ��Ӧ��Ҫ�뿪��·�ڵĳ���ɾ���ͺá�
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
                    vehicles[i].push(v);// �ŵ�β��
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


bool Route::canMoveVehicle() { // ��ƶ����ǶԵȴ������еĵ�һ�������
    if (this->vehicles.empty()) {
        return false;
    }
    Vehicle *v = vehicles.front();
    int oneArea = 0;
    queue<int> vArea = v->getArea();
    int count = 0;
    while (!vArea.empty()) {
        oneArea = vArea.front(); // �ⲻ�ǵ�һ�����򰡡���������������ǵ�һ�������Ƕ��а�������
        count++;
        if (count == 2) { // �������������һ������δ��ռ�죬�ڶ�������������ͬ��ʱ��
            queue<Vehicle *> vQ = cainot::vehicles[oneArea];
            while (!vQ.empty()) {
                if (vQ.front()->start == v->start) {
                    return true;
                }
                vQ.pop();
            }
        }
        if (cainot::area[oneArea] >= 4) { // ��������ռ��ʱ
            return false;
        }
        vArea.pop();
    }
    return true;
}

void Route::moveVehicle() { // ��ƶ����ǶԵȴ������еĵ�һ���ƶ�
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

    this->vehicles.pop(); // ÿ���̶߳�Ӧ��ͬ��this->vehicles��
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
    cout << "�����ɣ��ɹ������" << n << "�����ڷ���" << this->direction << endl;
}
