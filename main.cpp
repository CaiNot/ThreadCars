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

class Vehicle;

namespace cainot {
    int area[4] = {4, 4, 4, 4};
    queue<Vehicle> vehicles[4];
}

class Vehicle {
public:
    int nowPos;

    Vehicle(int s, int e) : start(s), end(e) {
        this->setArea();
        this->nowPos = -1;
    }


    inline queue<int> getArea() {
        return this->area;
    }

    bool move() {
        if (nowPos == -1) { // 原来在等待队列
            nowPos = this->start;
        } else {
            cainot::area[nowPos]++; // 原区域不再被占用
            cainot::vehicles[nowPos].pop();
            this->area.pop(); // 已经走过了区域就去除掉
            nowPos++; // 向前移动一个单位
        }
        return nowPos <= end; // 如果已到达终点，则最后再移动一步就OK了，取==是为了方便代码编写
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


class Route {
    const int direction;
public:
    queue<Vehicle> vehicles;

    Route(int d) : direction(d) {}

    inline int getDirection() {
        return direction;
    }

    bool canMoveVehicle() { // 设计对象是对等待队列中的第一个做检查
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

    void moveVehicle() { // 设计对象是对等待队列中的第一个移动
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