#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    try {
        // 尝试打开文件
        ifstream in("test.txt");

        // 如果文件打开失败，抛出异常
        if (!in.is_open()) {
            throw runtime_error("文件打开失败");
        }

        // 读取文件内容
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }

        in.close();
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}