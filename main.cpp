#include "./base64/base64.hpp"
#include <iostream>

using namespace Websocket;
int main() {
    std::string dencode = "12345678";
    std::string ret = Websocket::base64_encode(dencode);

    std::cout << ret << std::endl;
    return 0;
}
