#include <iostream>
#include <vector>
#include <thread>
#include <queue>

#define W 0
#define S 1
#define E 2
#define N 3

using namespace std;

void output(int i) {
    cout << i << "hello" << endl;
}


class Vehicle {
public:
    Vehicle(int s, int e) : start(s), end(e) {
        this->setArea();
    }

    inline queue<int> getArea() {
        return this->area;
    }

private:
    void setArea() {
        int endPos = this->end;
        if (this->start == this->end) {
            endPos = 4;
        }
        for (int i = this->start; i < endPos; i++) {
            this->area.push(i);
        }
    }

    const int start;
    const int end;
    queue<int> area;
};

namespace cainot {
    int area[4] = {4, 4, 4, 4};
    queue<Vehicle> vehicles[4];
}

class Route {
    const int direction;
public:
    queue<Vehicle> vehicles;

    Route(int d) : direction(d) {}

    inline int getDirection() {
        return direction;
    }

    bool moveVehicle(Vehicle v) {
//        if (vehicles.empty()) {
//            return false;
//        }
//        Vehicle v = vehicles.front();
        int oneArea = 0;
        queue<int> vArea = v.getArea();
        while (!vArea.empty()) {
            oneArea = vArea.front();
            if (cainot::area[oneArea] <= 0) {
                return false;
            }
        }
    }


};

int main() {

    for (uint8_t i = 0; i < 4; i++) {
        thread t(output, i);
        //t.join(); 使用join表示子线程结束之后再运行主线程
        t.detach();
    }


    getchar();
    /**
     * 如果main结束了，子线程也会结束，所以，强行不结束。
    **/
    return 0;
}