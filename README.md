# Wiki_Cpp_VariadicMacro
C++における可変引数マクロのテクニック  

1.マクロ記述内における可変長パラメータパック`__VA_ARGS__`の展開有無  
https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160  

  - @MSVC 従来型のプリプロセッサ(/Zc:preprocessor-)  
      - 可変長パラメータパックは展開されない.  
      - マクロ記述内部では`__VA_ARGS__`がシングルトークンとして扱われるので、  
      - 展開が必要な場合は, 展開用マクロを追加して強制的に展開動作を行わせる.  
      - `#define EXPAND_ARGS(...) \__VA_ARGS__` // この記述を展開したいマクロ記述内で使用する.  
      - `#define LOG(fmt, ...) std::printf(fmt, EXPAND_ARGS(__VA_ARGS__));`  
        
  - @MSVC 標準準拠モードのプリプロセッサ(/Zc:preprocessor)  
      - GNU系の標準プリプロセッサの動作に習って`__VA_ARGS__`は展開される.  
      - `#define LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__);`  
        
  - @GNU `__VA_ARGS__`は自動で展開される.  
          
  
2. マクロ記述内の `, __VA_ARGS__`における`,`の取扱い  
https://tyfkda.github.io/blog/2015/03/04/var-args.html  
https://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick#11172679  
https://docs.microsoft.com/ja-jp/cpp/preprocessor/variadic-macros?view=msvc-160  
    
  - @GNU `, ##__VA_ARGS__`とすることで、GNU拡張によって`__VA_ARGS__`が空の場合, 直前のカンマ`,`は削除される.  
    - `#define LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__);`  
    - ただし, コンパイラオプションの--pedantic-errorを設定した場合、GNU拡張が禁止されるので注意すること.  
    
  - @MSVC 従来型のプリプロセッサ(/Zc:preprocessor-)  
    - `, __VA_ARGS__`において`__VA_ARGS__`が空の場合、コンパイラが気を利かせて直前の`,`を消してくれる.
    - `#define EXPAND_ARGS(...) __VA_ARGS__`
    - `define LOG(fmt, ...) std::printf(fmt, EXPAND_ARGS(__VA_ARGS__));`
 
  - @MSVC 標準準拠モードのプリプロセッサ(/Zc:preprocessor)  
    - GNUと同じく`##`によって直前の`,`を消すように指示する. 自動で消してくれないので注意.  
    - `#define LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__);`
  
  
3. C++20以降の`, __VA_ARGS__`のカンマ`,`の取扱いについて  
https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160  

  - GNU&MSVC(Visual Studio 2019 ver16.5: `_MSC_VER >= 1925`)の両方において, `__VA_OPT__(,)`で制御できる.
  - `#define LOG(fmt, ...) std::printf(fmt __VA_OPT__(,) __VA_ARGS__);`
  
  
  
4. MSVCにおけるマクロ記述内のマクロ展開  
https://docs.microsoft.com/ja-jp/cpp/preprocessor/preprocessor-experimental-overview?view=msvc-160  

  - 従来型プリプロセッサ(/Zc:preprocessor-)では、マクロ記述内のマクロは自動的に展開される
    ```cpp:traditional_macro.cpp 
    #define CAT(a, b) a##b
    #define ECHO(...) __VA_ARGS__
    #define IMPL1(prefix, value) do_thing_one(prefix, value)
    #define IMPL2(prefix, value) do_thing_two(prefix, value)
    #define DO_THING_FIXED(a, b) CAT(IMPL, a) ECHO(("Hello", b))
    
    int main(int, char**)
    {
      DO_THING_FIXED(1, "world"); // IMPL1 ("Hello", "world") -(マクロ記述内のマクロが自動展開される)-> do_thing_one("Hello", "world")
      
      return 0;
    }
    ```
  - 新型プリプロセッサ(標準準拠モード)(/Zc:preprocessor)では、自動的にマクロ展開されないので、展開用のマクロを一つ追加して、間に噛ませる
    ```cpp:new_macro.cpp
    #define CAT(a, b) a##b
    #define ECHO(...) __VA_ARGS__
    #define IMPL1(prefix, value) do_thing_one(prefix, value)
    #define IMPL2(prefix, value) do_thing_two(prefix, value)
    #define CALL(macro_name, args) macro_name args // 展開用に間に噛ませるマクロ
    #define DO_THING_FIXED(a, b) CALL(CAT(IMPL, a), ECHO(("Hello", b)))
    
    int main(int, char**)
    {
      DO_THING_FIXED(1, "world"); // CALL(IMPL1, ("Hello", "world")) -( IMPL1 ("Hello", "world") )-> do_thing_one("Hello", "world")
      
      return 0;
    }
    ```
 
5.可変長引数マクロの数を数える方法   
執筆中  
