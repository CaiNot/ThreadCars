//
// Created by CaiNot on 2018/9/28 21:36.
//

#include "data.h"

void cainot::work(Route *route[4]) { // �������еĳ��������ƶ���ÿ�ε��ö��ƶ�һ����λ
    bool isEnd = true;
    for (int i = 0; i < 4; i++) {
        isEnd = isEnd && route[i]->isEnd();
    }
    while (!isEnd) {
        int vehiclesInOneArea = 0;
        for (int i = 0; i < 4; i++) {
            vehiclesInOneArea = area[i];// area
            for (int j = 0; j < 4 - vehiclesInOneArea; j++) {

                Vehicle *v = vehicles[i].front();


                cout << v->nowPos << "->";
                if (v->move()) {
                    cout << "����->";
                } else {
                    cout << "leave at ";
                }
                lock_guard<mutex> lockGuard(my_mutex);// �޸ı���ʱ����������

                vehicles[i].pop();

                cout << v->nowPos << "," << endl;


            }
        }
        isEnd = true;
        for (int i = 0; i < 4; i++) {
            isEnd = isEnd && route[i]->isEnd();
//            cout << i << route[i]->isEnd();
        }
//        cout << "isEnd" << isEnd << endl;
    }
    cout << "what a !!" << endl;
}

void cainot::ready(Route *route) {
    while (!route->isEnd()) {
        while (route->canMoveVehicle()) {
            route->moveVehicle();
        }
    }
    cout << route->getDirection() << "end" << endl;
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

bool Vehicle::move() {
    if (nowPos == -1) { // ԭ���ڵȴ�����
        nowPos = this->start;
    } else {
//        cout << nowPos << endl;
        lock_guard<mutex> lockGuard(my_mutex);// �޸ı���ʱ����������

        if (nowPos > 4) {
            cout << "Error" << this->start << endl;
            exit(-2);
        }
        cainot::area[nowPos]++; // ԭ�����ٱ�ռ��
//        cainot::vehicles[nowPos].pop();
        if (this->area.empty()) {
            cout << "Error" << this->start << endl;
//            cout  << endl;
            exit(-1);
        }
        this->area.pop(); // �Ѿ��߹��˵������ȥ����
        nowPos++; // ��ǰ�ƶ�һ����λ
    }
    return nowPos < end; // ����ѵ����յ㣬��������ƶ�һ����OK�ˣ�ȡ==��Ϊ�˷�������д
}

void Vehicle::setArea() {
    int endPos = this->end;

    if (this->start >= endPos)
        endPos = 4 + this->end;
    for (int i = this->start; i < endPos; i++) {
        this->area.push(i % 4);
    }
}

bool Route::canMoveVehicle() { // ��ƶ����ǶԵȴ������еĵ�һ�������
    if (vehicles.empty()) {
        return false;
    }
    Vehicle *v = vehicles.front();
//    cout << v.start << "����" << endl;
    int oneArea = 0;
    queue<int> vArea = v->getArea();
    int count = 0;
    while (!vArea.empty()) {
        oneArea = vArea.front();
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
        if (cainot::area[oneArea] <= 0) { // ��������ռ��ʱ
            return false;
        }

        vArea.pop();
    }
    return true;
}

void Route::moveVehicle() { // ��ƶ����ǶԵȴ������еĵ�һ���ƶ�
    Vehicle *v = vehicles.front();
//    lock_guard<mutex> lockGuard(my_mutex);// �޸ı���ʱ����������
    cout << v->start << "����" << endl;
    v->move();

    int oneArea = 0;
    queue<int> vArea = v->getArea();

    while (!vArea.empty()) {
        oneArea = vArea.front();
        vArea.pop();

        lock_guard<mutex> lockGuard(my_mutex);// �޸ı���ʱ����������
        cainot::area[oneArea]--;
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
        this->vehicles.push(v);
        cout << "car end in " << v->getArea().back() << endl;
    }
    cout << "�����ɣ��ɹ������" << n << "�����ڷ���" << this->direction << endl;

}
