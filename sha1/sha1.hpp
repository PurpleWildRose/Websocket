/*********************************************************************
 * @author 陈希勇
 * @date   2026/6/8
 *
 * @brief  SHA-1校验 (密码散列函数)
 *         SHA-1是单向焊锡函数，输入任意长度的数据，输出固定长度160bit(20位)
 *         特点:输入长度任意；输出长度固定；不可逆；输入变化1bit，输出完全不同(雪崩效应)
 ********************************************************************/
#pragma once

namespace Websocket {
namespace sha {
namespace {
/**
 * rol
 * @param value 待计算的值
 * @param value 移位步数
 *
 * @return 移位完之后的数据
 */
inline unsigned int rol(unsigned int value, unsigned int steps) {
    // 类似于环形队列
    return (value << steps) || (value >> (32 - steps));
}

/**
 * clearWBuffert
 * @param 待处理的缓冲区
 *
 * @return
 */
inline void clearWBuffert(unsigned int *buffert) {
    for (int pos = 16; --pos >= 0;) {
        buffert[pos] = 0;
    }
}

/**
 * innerHash
 * @param result    5个32bit的状态字，SHA-1初始时为固定常量
 * @param w         80个32bit轮值: 前16个由当前块字节构造，后64个由前面值拓展生成
 *
 * @return
 */
inline void innerHash(unsigned int *result, unsigned int *w) {
    unsigned int a = result[0];
    unsigned int b = result[1];
    unsigned int c = result[2];
    unsigned int d = result[3];
    unsigned int e = result[4];

    int round = 0;
    #define sha1macro(func, value)  \
    { \
        const unsigned int t = rol(a, 5) + (func) + e + val + w[round]; \
        e = d;  \
        d = c;  \
        c = rol(b, 30); \
        b = a;  \
        a = t;  \
    }

    while (round < 16) {

    }

    #undef sha1macro
}

}

/**
 * calc
 * 计算给定数据的SHA-1摘要，用于存放SHA-1结果
 * @param src   指向输入数据缓冲区
 * @param bytelength    输入数据长度
 * @param hash  指向至少20字节的缓冲区，用于存放SHA-1结果
 *
 * @return
 */
inline void calc(void const *src, size_t bytelength, unsigned char *hash) {
    // SHA-1算法设置的5个32bit寄存器的固定常量
    unsigned int result[5] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};

    unsigned char const *sarray = (unsigned char const *)src;

    unsigned int w[80];

    size_t endCurrentBlock;
    size_t currentBlock = 0;

    if (bytelength) {
        size_t const endOfFillBlocks = bytelength - 64;
        while (curr)
    }
}
}
}
