#include <iostream>
#include <thread>

using namespace std;

void output(int i) {
    cout << i << "hello" << endl;
}

int main() {

    for (uint8_t i = 0; i < 4; i++) {
        thread t(output, i);
        t.detach();
    }

    getchar();
    /**
     * 如果main结束了，子线程也会结束，所以，强行不结束。
    **/
    return 0;
}