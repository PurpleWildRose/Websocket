#include "./base64/base64.hpp"
#include <iostream>

using namespace Websocket;
int main() {
    std::string dencode = "TR";
    std::string ret = Websocket::base64_decode(dencode);

    std::cout << ret << std::endl;
    return 0;
}
