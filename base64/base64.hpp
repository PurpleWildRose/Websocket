/*********************************************************************
 * @author  陈希勇
 * @date 2026/6/6
 *
 * @brief base64为的封装校验方法
 *        base64编码主要是把3个8位字节(3*8=24)转化为4个6位的字节(4*6=24)，之后在6位的前面补两个0，形成8位一字节的形式。如果剩下的字符不足三字节，则用'0'补充，输出字段使用'='，因此编码后输出的文本末尾
 *              可能会出现1或2个'='。为了保证所输出的编码位可读字符，base64制定了一个编码表，以便统一转换。
 **********************************************************************/

#include <string>

namespace Websocket {
// 基础合法字符，主要用于后面方法的查询字符的合法性
static std::string const base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWxYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

/**
 * is_base64
 *
 * @param chr
 * @return True: 是合法的base64字符             False: 不合法的base64字符
 */
static inline bool is_base64(unsigned char chr) {
    return  (chr == 43) ||                      // +
            (chr >= 47 && chr <= 57) ||         // /-9
            (chr >= 65 && chr <= 90) ||         // A-Z
            (chr >= 97 && chr <= 122);          // a-z
}

/**
 * base64_encode
 *
 * @param imput 待编码的字符指针
 * @param len   带编码字符只剩移动的位数
 * @return 编码后的字符串
 */
inline std::string base64_encode(unsigned char const* input, size_t len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3], char_array_4[4];

    while (len--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            // 类似于栈，具体如下: [x x 1 2 3 4 5 6] <--- [1 2 3 4 5 6 7 8]
            //                   [x x 7 8 9 0 1 2] <--- [x x x x x x 7 8]、[9 0 1 2 3 4 5 6]
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (int i = 0; i < 4; i++)
                ret += base64_chars[char_array_4[i]];

            i = 0;
        }
    }
    if (i) {
        // 补充字符，实现校验位对齐
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        // 困惑的地方解答:当char_array_3只有一个有效位是是，必然能解算出两位char_array_4的两位(只不过第二位是'\0'与3数组尾部的结合)
        for (j = 0; (j < i + 1); j++) {
            ret += base64_chars[char_array_4[j]];
        }

        while (i++ < 3)
            ret += '=';
    }

    return ret;
}

/**
 * base64_encode
 * @param input 待编码的字符串
 * @return 编码后的字符串
 */
inline std::string base64_encode(std::string const &input) {
    return base64_encode(
        reinterpret_cast<const unsigned char*>(input.data()),
        input.size()
    );
}

/**
 * base64_decode
 * @param input     待解码的字符串
 * @return  解码后的字符串
 */
inline std::string base64_decode(std::string &input) {
    std::string ret;
    int i = 0;
    int j = 0;
    int in_len = input.size();
    int in_ = 0;
    unsigned char char_array_3[3], char_array_4[4];

    while (in_len-- && (input[in_] != '=') && is_base64(input[in_])) {
        char_array_4[i++] = input[in_++];
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0x0f) << 4) + ((char_array_4[2] & 0x3c) >> 4);
            char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++)
                ret += char_array_3[i];

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = '\0';

        for (j = 0; j < 4; j++)
            char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0x0f) << 4) + ((char_array_4[2] & 0x3c) >> 4);
        char_array_3[2] = ((char_array_4[2] & 0x03) << 6) + char_array_4[3];

        for (j = 0; j < i - 1; j++){
            ret += static_cast<std::string::value_type>(char_array_3[j]);
        }
    }

    return ret;
}

} //namespace Websocket
