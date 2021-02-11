#pragma once

// MSVCのマクロ記述内で可変長パラメータパックが
// シングルトークンとして扱われる仕様を回避する方法
// 以下マクロを指定のマクロ記述内部で使用する.
#define EXPAND_ARGS(...) __VA__ARGS__


////////////////////////////////////
// 可変長引数マクロの数を数える方法
////////////////////////////////////
// 数えられる最大数はマクロで定義しなければならない
// 今回は10個の可変長マクロ引数までを検出できる
// e.g MACRO_ARGS_NUM(int, string, char) -> 3
#define MACRO_ARGS_GET_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#ifdef MSVC
    #define MACRO_ARGS_NUM(...) MACRO_ARGS_GET_N(0, EXPAND_ARGS(__VA__ARGS__), 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else
    #define MACRO_ARGS_NUM(...) MACRO_ARGS_GET_N(0, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif


//////////////////////////////////
// マクロ引数から仮引数を作る方法
//////////////////////////////////
// e.g ARGDEFS(int, long&, char*) -> int a1, long& a2, char* a3

#define ARGDEFS_0()
#define ARGDEFS_1(A1) A1 a1
#define ARGDEFS_2(A1, A2) ARGDEFS_1(A1), A2 a2
#define ARGDEFS_3(A1, A2, A3) ARGDEFS_2(A1, A2), A3 a3
#define ARGDEFS_4(A1, A2, A3, A4) ARGDEFS_3(A1, A2, A3), A4, a4
#define ARGDEFS_5(A1, A2, A3, A4, A5) ARGDEFS_4(A1, A2, A3, A4) A5 a5
#define ARGDEFS_6(A1, A2, A3, A4, A5, A6) ARGDEFS_5(A1, A2, A3, A4, A5) A6 a6
#define ARGDEFS_7(A1, A2, A3, A4, A5, A6, A7) ARGDEFS_6(A1, A2, A3, A4, A5, A6) A7 a7
#define ARGDEFS_8(A1, A2, A3, A4, A5, A6, A7, A8) ARGDEFS_7(A1, A2, A3, A4, A5, A6, A7) A8 a8
#define ARGDEFS_9(A1, A2, A3, A4, A5, A6, A7, A8, A9) ARGDEFS_8(A1, A2, A3, A4, A5, A6, A7, A8) A9, a9

#ifdef MSVC

#else
    #define MACRO_ARGDEFS(...)                                    \
        MACRO_ARGS_GET_N(0, ##__VA_ARGS__,                        \
            ARGDEFS_9, ARGDEFS_8, ARGDEFS_7,                      \
            ARGDEFS_6, ARGDEFS_5, ARGDEFS_4,                      \
            ARGDEFS_3, ARGDEFS_2, ARGDEFS_1,                      \
            ARGDEFS_0)(__VA_ARGS__)
#endif







