# VariadicMacro
C++における可変引数マクロのテクニック</br>

1.
マクロ記述内で一旦可変長引数パラメータパックを展開する方法</br>
MSVCの場合、可変長引数パラメータパックがその他のマクロ記述内部でシングルトークンとして扱われるので、</br>
展開が必要な場合は、以下のマクロを定義して指定のマクロ記述内で使用する.</br>
`#define EXPAND_ARGS(...) __VA__ARGS__ // この記述を展開したいマクロ記述内で使用する`</br>
最新のMSVCの場合、アンパックされる.</br>
https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160</br>

2.
GCCとMSVCにおける\__VA__ARGS__の挙動の違い</br>
通常、可変長マクロ `#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)`を作ると、</br>
可変部分は1個以上値を渡さなければならない. したがって、`LOG("FOOBAR\n") // コンパイルエラー`</br>

GCCの場合、##\__VA_ARGS__を使えば、0個の場合でも受け取れる(GNU拡張).</br>
`#define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__) // OK`</br>
コンパイラオプションで--pedantic-errorを入れるとGNU拡張が禁止されるので注意</br>

MSVCの場合, ...が空の場合、コンパイラ`がprintf(fmt, __VA_ARGS__)`の`,`を気を利かせて消してくれる.</br>
https://tyfkda.github.io/blog/2015/03/04/var-args.html</br>
https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick#11172679</br>
https://docs.microsoft.com/ja-jp/cpp/preprocessor/variadic-macros?view=msvc-160</br>

<追記:2021/03/03> </br>
MSVCはVisual Studio 2019 から 可変長マクロの引数なし時の動作が変更になる. </br>
C++標準よりになったため、GCCと同様に`, ##__VA_ARGS__`で可変長引数パックが空のときに対応する. </br>
https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160</br>

※C++20からは、`__VA_OPT__(,)`によって可変長パラメータパックが空のときの仕様違いを回避することができる</br>
MSVCの場合、Visual Studio 2019 バージョン16.5以降で利用可能になる. </br>

※MSVCがGCC同様、標準C++に準拠したプリプロセッサ動作をさせるためには、</br>
/Zc:preprocessor オプションをコンパイラに伝える必要がある. </br>
https://docs.microsoft.com/ja-jp/cpp/build/reference/zc-preprocessor?view=msvc-160</br>


3.
可変長引数マクロの数を数える方法</br> 
