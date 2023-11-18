//macos下清理屏幕功能的实现

#include <iostream>

void clearScreen() {
    // 使用 ANSI 转义序列清屏
    std::cout << "\033[2J\033[1;1H";
}


