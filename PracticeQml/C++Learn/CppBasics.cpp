#include "CppBasics.h"
#include <iostream>       // 用于 cout 输出（调试用）
#include <QDebug>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <initializer_list>
#include <type_traits>

using namespace std;

// ==================== 构造函数 ====================
CppBasics::CppBasics(QObject *parent)
    : QObject(parent)
{
}

// ==================== 私有辅助 ====================
void CppBasics::log(const QString &category, const QString &msg)
{
    QString line = QString("[%1] %2").arg(category).arg(msg);
    emit output(line);
    qDebug().noquote() << line;
}

// ==================== 基础类型 ====================
void CppBasics::demoBasicTypes()
{
    // 整型
    int    i = 42;
    long   l = 2147483647L;
    // 浮点
    float  f = 3.14f;
    double d = 3.14159265358979;
    // 字符 / 布尔
    char   c = 'A';
    bool   b = true;
    // 无符号
    unsigned int ui = 0;

    // sizeof 验证
    log("BasicTypes",
        QString("sizeof: int=%1, long=%2, float=%3, double=%4, char=%5, bool=%6, void*=%7")
        .arg(sizeof(int)).arg(sizeof(long))
        .arg(sizeof(float)).arg(sizeof(double))
        .arg(sizeof(char)).arg(sizeof(bool))
        .arg(sizeof(void*)));

    log("BasicTypes",
        QString("values -> int:%1, float:%2, double:%3, char:'%4', bool:%5")
        .arg(i).arg(f).arg(d).arg(c).arg(b));
}

void CppBasics::demoVariable()
{
    // 不同初始化方式
    int a = 10;       // copy-initialization
    int b(20);        // direct-initialization
    int c{30};        // brace-initialization（C++11 推荐）
    int d = {40};     // copy-list-initialization

    // 未初始化变量值未定义
    int e;

    log("Variable",
        QString("a=%1, b=%2, c=%3, d=%4, e(uninit)=%5 ( UB!)")
        .arg(a).arg(b).arg(c).arg(d).arg(e));

    // 类型推导
    auto f = 3.14;    // double
    auto g = 100;     // int
    log("Variable", QString("auto f=%1 (double), auto g=%2 (int)").arg(f).arg(g));
}

void CppBasics::demoConst()
{
    const int   ci = 100;        // const（编译期常量，不可修改）
    constexpr int ce = 200;      // constexpr（编译期常量，C++11）

    // ci = 99;  // 编译错误：cannot assign to variable 'ci'
    // ce = 99;  // 编译错误：cannot assign to variable 'ce'

    int arr[ci];   // const 可用于数组维度（C++11 起）
    log("Const", QString("const int ci=%1, constexpr int ce=%2, int arr[ci] size=%3")
        .arg(ci).arg(ce).arg(sizeof(arr)/sizeof(int)));
}

// ==================== 控制流 ====================
void CppBasics::demoIfElse()
{
    int score = 85;
    QString result;
    if (score >= 90) {
        result = "A";
    } else if (score >= 80) {
        result = "B";
    } else if (score >= 60) {
        result = "C";
    } else {
        result = "D";
    }
    log("IfElse", QString("score=%1 => %2").arg(score).arg(result));

    // 三目运算符
    int x = 10, y = 20;
    int max = (x > y) ? x : y;
    log("IfElse", QString("ternary: max(%1,%2)=%3").arg(x).arg(y).arg(max));
}

void CppBasics::demoSwitch()
{
    int day = 3;
    QString name;
    switch (day) {
    case 1: name = "Monday";    break;
    case 2: name = "Tuesday";   break;
    case 3: name = "Wednesday"; break;
    case 4: name = "Thursday";  break;
    case 5: name = "Friday";    break;
    case 6: name = "Saturday";  break;
    case 7: name = "Sunday";    break;
    default: name = "Invalid";  break;
    }
    log("Switch", QString("day=%1 => %2").arg(day).arg(name));

    // switch 穿透（不写 break）
    int f = 1;
    QString out;
    switch (f) {
    case 1: out += "1 ";  // 穿透到 case 2
    case 2: out += "2 ";  // 穿透到 case 3
    case 3: out += "3 ";  break;
    default: out += "X ";
    }
    log("Switch", QString("fall-through: %1").arg(out.trimmed()));
}

void CppBasics::demoLoop()
{
    // for 循环
    QString out1;
    for (int i = 0; i < 5; ++i) {
        out1 += QString::number(i) + " ";
    }
    log("Loop", QString("for:    %1").arg(out1.trimmed()));

    // while 循环
    int w = 0;
    QString out2;
    while (w < 5) {
        out2 += QString::number(w++) + " ";
    }
    log("Loop", QString("while:  %1").arg(out2.trimmed()));

    // do-while（至少执行一次）
    int d = 0;
    QString out3;
    do {
        out3 += QString::number(d++) + " ";
    } while (d < 5);
    log("Loop", QString("do-while: %1").arg(out3.trimmed()));

    // break / continue
    QString out4;
    for (int i = 0; i < 10; ++i) {
        if (i == 3) continue;   // 跳过 3
        if (i == 7) break;     // 遇到 7 停止
        out4 += QString::number(i) + " ";
    }
    log("Loop", QString("break/continue: %1").arg(out4.trimmed()));
}

void CppBasics::demoRangeBasedFor()
{
    // C++11 范围 for（原始数组）
    int arr[] = {10, 20, 30, 40};
    QString out1;
    for (int v : arr) {
        out1 += QString::number(v) + " ";
    }
    log("RangeFor", QString("int[]:  %1").arg(out1.trimmed()));

    // 范围 for（std::vector）
    vector<int> vec = {1, 2, 3};
    QString out2;
    for (const int &v : vec) {  // const ref 避免拷贝
        out2 += QString::number(v) + " ";
    }
    log("RangeFor", QString("vector: %1").arg(out2.trimmed()));
}

// ==================== 函数 ====================
void CppBasics::demoFunction()
{
    // 普通函数调用
    auto add = [](int a, int b) -> int { return a + b; };
    auto mul = [](int a, int b) { return a * b; };  // 编译器可推导返回类型

    log("Function", QString("add(3,4)=%1, mul(5,6)=%2").arg(add(3,4)).arg(mul(5,6)));

    // 函数内部定义函数（C++11 lambda 等价演示）
    auto apply2 = [](int v, auto f) { return f(f(v)); };
    log("Function", QString("apply2(2, [x](int a){return a+1;})=%1").arg(apply2(2, [](int a){ return a+1; })));
}

void CppBasics::demoDefaultParam()
{
    auto greet = [](const QString &name = "World") {
        return QString("Hello, %1!").arg(name);
    };

    log("DefaultParam", greet());                          // 使用默认参数
    log("DefaultParam", greet("C++"));                     // 传入参数覆盖默认值
    log("DefaultParam", greet(QString()));                  // 显式传空字符串（不触发默认）
}

void CppBasics::demoInline()
{
    // inline 关键字建议编译器内联，减少函数调用开销
    auto square = [](int x) -> int { return x * x; };
    // 注意：inline 主要用于非 lambda 的普通函数，
    // lambda 编译器自动内联，这里演示含义
    log("Inline", QString("inline lambda square(7)=%1 (likely inlined by compiler)").arg(square(7)));
}

void CppBasics::demoLambda()
{
    // 完整语法：[capture](params) -> ret { body }
    int x = 10;

    // 1. 值捕获
    auto f1 = [x](int y) { return x + y; };

    // 2. 引用捕获
    int z = 100;
    auto f2 = [&z](int y) { z += y; return z; };

    // 3. mutable（修改值捕获的副本）
    auto f3 = [x](int y) mutable { x += y; return x; };

    // 4. auto 推导参数（C++14）
    auto f4 = [](auto a, auto b) { return a + b; };

    log("Lambda", QString("value capture: f1(5)=%1 (x=10 unchanged)").arg(f1(5)));
    log("Lambda", QString("ref capture:   f2(5)=%1, z is now %2").arg(f2(5)).arg(z));
    log("Lambda", QString("mutable:       f3(5)=%1 (x inside lambda=15, outside x still=10)").arg(f3(5)));
    log("Lambda", QString("generic(C++14): f4(2,3.5)=%1, f4(string,string)=%2")
        .arg(f4(2, 3.5)).arg(f4(QString("a"), QString("b")).toString()));
}

// ==================== 类 ====================
void CppBasics::demoClass()
{
    // 匿名对象/结构演示
    struct Point {
        int x;
        int y;
        void describe() {
            log("Class", QString("Point(%1,%2)").arg(x).arg(y));
        }
    };

    Point p{3, 4};
    p.describe();

    // 嵌套类
    class Outer {
    public:
        class Inner {
        public:
            int value = 99;
        };
        Inner inner;
    };
    Outer o;
    log("Class", QString("nested class: Outer::Inner::value=%1").arg(o.inner.value));
}

void CppBasics::demoAccess()
{
    // public / private / protected 演示（用 struct/class 差异说明）
    // struct 默认 public，class 默认 private
    struct PubStruct {
        int x;           // 默认 public
    };
    class PrivClass {
        int x;           // 默认 private
    public:
        void setX(int v) { x = v; }
        int getX() const { return x; }
    };

    PubStruct s;
    s.x = 10;           // ✅ OK，struct 默认 public
    log("Access", QString("struct member (public by default): %1").arg(s.x));

    PrivClass c;
    c.setX(20);
    log("Access", QString("class member (private by default), accessed via getter: %1").arg(c.getX()));
}

void CppBasics::demoConstructor()
{
    class Demo {
    public:
        int value;
        QString name;
        // 默认构造函数
        Demo() : value(0), name("unnamed") {
            log("Constructor", "ctor: Demo()");
        }
        // 参数构造函数
        Demo(int v, const QString &n) : value(v), name(n) {
            log("Constructor", QString("ctor: Demo(%1, \"%2\")").arg(v).arg(n));
        }
        // 析构函数
        ~Demo() {
            log("Constructor", QString("dtor: ~Demo() on \"%1\"").arg(name));
        }
    };

    Demo a;              // 调用默认构造
    Demo b(42, "hello"); // 调用参数构造
    log("Constructor", QString("a.value=%1, b.value=%2").arg(a.value).arg(b.value));
    // 离开作用域时 a, b 自动析构
}

// ==================== 拷贝构造与移动 ====================
void CppBasics::demoCopy()
{
    class Buffer {
    public:
        vector<int> data;
        Buffer(size_t n) : data(n, 0) {
            log("Copy", QString("Buffer ctor: size=%1").arg(n));
        }
        Buffer(const Buffer &other) : data(other.data) {
            log("Copy", QString("copy ctor (deep copy): new vector, size=%1").arg(data.size()));
        }
        Buffer(Buffer &&other) noexcept : data(std::move(other.data)) {
            log("Copy", QString("move ctor: steal resources, no allocation"));
        }
        Buffer &operator=(const Buffer &) {
            log("Copy", "copy assignment");
            return *this;
        }
        Buffer &operator=(Buffer &&) noexcept {
            log("Copy", "move assignment");
            return *this;
        }
    };

    Buffer b1(1000);
    Buffer b2 = b1;        // 拷贝构造（深拷贝）
    Buffer b3 = std::move(b1); // 移动构造（b1 资源转移到 b3）

    log("Copy", QString("after move: b1.data.size=%1, b3.data.size=%2")
        .arg(b1.data.size()).arg(b3.data.size()));
}

// ==================== 运算符重载 ====================
void CppBasics::demoOperator()
{
    class Vec2 {
    public:
        int x, y;
        Vec2(int _x=0, int _y=0) : x(_x), y(_y) {}
        // 加法重载
        Vec2 operator+(const Vec2 &other) const {
            return Vec2(x + other.x, y + other.y);
        }
        // 下标重载
        int operator[](int i) const {
            return i == 0 ? x : y;
        }
        // 输出重载友元（通过 lambda 模拟，无实际流输出）
        QString toString() const {
            return QString("Vec2(%1,%2)").arg(x).arg(y);
        }
    };

    Vec2 a(1, 2);
    Vec2 b(3, 4);
    Vec2 c = a + b;
    log("Operator", QString("Vec2 a=%1, b=%2, a+b=%3").arg(a.toString()).arg(b.toString()).arg(c.toString()));
    log("Operator", QString("a[0]=%1, a[1]=%2").arg(a[0]).arg(a[1]));
}

// ==================== 继承 ====================
void CppBasics::demoInherit()
{
    class Animal {
    public:
        QString name;
        Animal(const QString &n) : name(n) {}
        void speak() {
            log("Inherit", QString("[%1] says: ...").arg(name));
        }
    };

    class Dog : public Animal {
    public:
        Dog(const QString &n) : Animal(n) {}
        void speak() {  // 重写（隐藏父类方法）
            log("Inherit", QString("[%1] says: Wang!").arg(name));
        }
    };

    Animal *a = new Animal("Generic");
    Dog    *d = new Dog("Buddy");
    Animal *ad = d;  // 父类指针指向子类对象（向上转型）

    a->speak();
    d->speak();
    ad->speak();     // 调用的是 Animal::speak（无虚函数时为静态绑定）
    delete a;
    delete d;
}

// ==================== 虚函数与多态 ====================
void CppBasics::demoVirtual()
{
    class Base {
    public:
        virtual QString identify() const {
            return "Base";
        }
        virtual ~Base() = default;  // 虚析构（多态基类必须）
    };

    class Derived : public Base {
    public:
        QString identify() const override {
            return "Derived";
        }
    };

    Base *ptr = new Derived();
    log("Virtual", QString("Base* ptr = new Derived()"));
    log("Virtual", QString("ptr->identify() = \"%1\" (dynamic dispatch)")
        .arg(ptr->identify()));
    log("Virtual", QString("typeid(*ptr).name() = %1")
        .arg(typeid(*ptr).name()));

    // 类型转换
    Derived *d = dynamic_cast<Derived*>(ptr);
    log("Virtual", QString("dynamic_cast<Derived*>(ptr) = %1 (success)")
        .arg(d ? "valid" : "null"));
    delete ptr;
}

// ==================== override（C++11） ====================
void CppBasics::demoOverride()
{
    class A {
    public:
        virtual void foo(int) const {}
    };
    class B : public A {
    public:
        // void foo(int) const override {}   // ✅ 正确编译
        // void foo(double) const override {}  // ❌ 编译错误：签名不匹配，无 override
        void foo(int) const override {
            log("Override", "B::foo(int) called via override");
        }
    };

    B b;
    b.foo(1);
    log("Override", "override 保证重写父类方法；签名错误时编译失败，防止意外隐藏");
}

// ==================== 智能指针（C++11） ====================
void CppBasics::demoSmartPointer()
{
    // unique_ptr：独占所有权
    auto up = std::make_unique<int>(42);
    log("SmartPtr", QString("unique_ptr<int>: *up=%1, owns=%2")
        .arg(*up).arg(up != nullptr));

    // 移动转移所有权
    auto up2 = std::move(up);
    log("SmartPtr", QString("after move: up=null?%1, up2=%2")
        .arg(up==nullptr).arg(*up2));

    // shared_ptr：共享引用计数
    auto sp1 = std::make_shared<int>(100);
    auto sp2 = sp1;
    log("SmartPtr", QString("shared_ptr: *sp1=%1, use_count=%2")
        .arg(*sp1).arg(sp1.use_count()));

    // weak_ptr：避免循环引用
    std::weak_ptr<int> wp = sp1;
    log("SmartPtr", QString("weak_ptr expired? %1, locked=%2")
        .arg(wp.expired()).arg(wp.lock() != nullptr));
    sp1.reset();
    log("SmartPtr", QString("after sp1.reset: weak_ptr expired? %1").arg(wp.expired()));
}

// ==================== STL ====================
void CppBasics::demoVector()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    // C++11 initializer list
    vector<int> v2 = {1, 2, 3, 4, 5};

    QString out;
    for (int x : v) out += QString::number(x) + " ";
    log("Vector", QString("push_back: %1").arg(out.trimmed()));

    out.clear();
    for (auto &x : v2) out += QString::number(x) + " ";
    log("Vector", QString("initializer list: %1").arg(out.trimmed()));

    // 常用操作
    auto it = v.begin() + 1;
    v.insert(it, 15);
    v.erase(v.begin());
    v.pop_back();
    out.clear();
    for (int x : v) out += QString::number(x) + " ";
    log("Vector", QString("after insert/erase/pop: %1").arg(out.trimmed()));

    // emplace（C++11，原位构造，避免拷贝）
    vector<QString> sv;
    sv.emplace_back("hello");
    log("Vector", QString("emplace_back QString: \"%1\"").arg(sv[0]));
}

void CppBasics::demoMap()
{
    map<QString, int> m;
    m["apple"]   = 3;
    m["banana"]  = 5;
    m["orange"]  = 2;
    // C++11 initializer list
    map<QString, int> m2 = {{"dog", 1}, {"cat", 2}};

    QString out;
    for (const auto &kv : m) {
        out += QString("%1:%2 ").arg(kv.first).arg(kv.second);
    }
    log("Map", QString("map contents: %1").arg(out.trimmed()));

    // 查找
    auto it = m.find("banana");
    if (it != m.end()) {
        log("Map", QString("m[\"banana\"]=%1 (found)").arg(it->second));
    }

    // emplace（C++11）
    m.emplace("grape", 7);
    log("Map", QString("emplace grape: %1").arg(m["grape"]));

    // unordered_map（哈希表，O(1) 查找）
    unordered_map<QString, int> um = {{"x",1}, {"y",2}};
    log("Map", QString("unordered_map size=%1").arg(um.size()));
}

void CppBasics::demoString()
{
    std::string s = "Hello, C++";
    // C++11 string literals
    auto s2 = u8"UTF-8 string"sv;

    // 常用操作
    log("String", QString("size=%1, empty=%2, front='%3', back='%4'")
        .arg(s.size()).arg(s.empty()).arg(s.front()).arg(s.back()));

    // 子串
    log("String", QString("substr(0,5)=\"%1\"").arg(QString::fromStdString(s.substr(0,5))));

    // 拼接（C++11）
    std::string s3 = s + " " + s2;
    log("String", QString("concatenated: \"%1\"")
        .arg(QString::fromStdString(s3)));

    // to_string / stoi（C++11）
    int    i = stoi("123");
    double d = stod("3.14");
    log("String", QString("stoi(\"123\")=%1, stod(\"3.14\")=%2").arg(i).arg(d));
    log("String", QString("to_string(99.5)=\"%1\"").arg(QString::fromStdString(to_string(99.5))));
}

void CppBasics::demoAlgorithm()
{
    vector<int> v = {5, 2, 8, 1, 9, 3};

    // sort
    sort(v.begin(), v.end());
    QString out;
    for (int x : v) out += QString::number(x) + " ";
    log("Algorithm", QString("sort: %1").arg(out.trimmed()));

    // reverse
    reverse(v.begin(), v.end());
    out.clear();
    for (int x : v) out += QString::number(x) + " ";
    log("Algorithm", QString("reverse: %1").arg(out.trimmed()));

    // find
    auto it = find(v.begin(), v.end(), 8);
    log("Algorithm", QString("find 8: %1").arg(it != v.end() ? "found" : "not found"));

    // count_if（C++11）
    int evens = count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
    log("Algorithm", QString("count_if even: %1").arg(evens));

    // accumulate（C++11）
    int sum = accumulate(v.begin(), v.end(), 0);
    log("Algorithm", QString("accumulate sum: %1").arg(sum));

    // lambda 作为回调
    vector<int> v2 = {1,2,3,4,5};
    transform(v2.begin(), v2.end(), v2.begin(), [](int x){ return x * x; });
    out.clear();
    for (int x : v2) out += QString::number(x) + " ";
    log("Algorithm", QString("transform square: %1").arg(out.trimmed()));
}

// ==================== 模板 ====================
void CppBasics::demoTemplate()
{
    // 函数模板
    auto max = [](auto a, auto b) {
        return a > b ? a : b;
    };
    log("Template", QString("max(3,7)=%1, max(3.14,2.71)=%2")
        .arg(max(3,7)).arg(max(3.14, 2.71)));

    // 类型萃取
    bool is_int    = std::is_same<int,    int>::value;
    bool is_double = std::is_same<int, double>::value;
    log("Template", QString("is_same<int,int>=%1, is_same<int,double>=%2")
        .arg(is_int).arg(is_double));

    // enable_if（C++11 条件编译）
    // auto f = std::enable_if_t<sizeof(int)>=4, int>(0); // 仅 sizeof(int)>=4 时可用
    log("Template", QString("sizeof(int)=%1 (enable_if_t: compiles OK)").arg(sizeof(int)));
}

// ==================== auto ====================
void CppBasics::demoAuto()
{
    auto a = 42;              // int
    auto b = 3.14;            // double
    auto c = 'X';             // char
    auto d = u"hello";        // const char16_t*
    auto e = std::vector<int>{1,2,3};
    auto f = std::make_pair(1, "one");
    auto lam = [](int x){ return x * 2; };

    log("Auto", QString("auto a=%1(type=int), b=%2(type=double), c='%3'(type=char)")
        .arg(a).arg(b).arg(c));
    log("Auto", QString("auto lam(10)=%1").arg(lam(10)));

    // auto & / auto &&（C++11）
    int    arr[] = {1,2,3};
    for (auto &v : arr) {
        // v 是引用，可修改原数组
    }
    log("Auto", QString("range-for auto& arr[0]=%1").arg(arr[0]));
}

// ==================== initializer_list ====================
void CppBasics::demoInitializerList()
{
    // std::initializer_list（C++11）
    auto sum = [](std::initializer_list<int> il) {
        int s = 0;
        for (int x : il) s += x;
        return s;
    };
    log("InitList", QString("sum({1,2,3,4,5})=%1").arg(sum({1,2,3,4,5})));

    // vector 直接初始化
    vector<int> v{10, 20, 30};
    log("InitList", QString("vector<int>{10,20,30}.size=%1").arg(v.size()));

    // map 初始化
    map<QString, int> m = {{"one",1}, {"two",2}};
    log("InitList", QString("map initialized with %1 entries").arg(m.size()));
}

// ==================== nullptr ====================
void CppBasics::demoNullptr()
{
    int *p1 = nullptr;   // C++11，推荐
    int *p2 = NULL;     // C 风格宏，通常为 0
    // int *p3 = 0;       // 合法但语义不清晰

    log("Nullptr", QString("nullptr==nullptr=%1, nullptr==NULL=%2, sizeof(nullptr_t)=%3")
        .arg(p1==nullptr).arg(p1==p2).arg(sizeof(nullptr_t)));

    // 函数重载
    auto foo_int  = [](int)   { return "int"; };
    auto foo_ptr  = [](int*)  { return "pointer"; };
    log("Nullptr", QString("foo_int(nullptr)=%1 (NULL as int=0)") // NULL=0，选 int 重载
        .arg(foo_int(NULL)));
    log("Nullptr", QString("foo_ptr(nullptr)=%1 (nullptr_t -> pointer overload)")
        .arg(foo_ptr(nullptr)));
}

// ==================== enum class ====================
void CppBasics::demoEnumClass()
{
    // enum class（强类型枚举，C++11）
    enum class Color : int { Red = 1, Green, Blue };
    enum class Size   { Small, Medium, Large };

    Color c = Color::Green;
    Size  s = Size::Large;

    // 强类型：不能隐式转 int
    int ic = static_cast<int>(c);
    int is = static_cast<int>(s);
    log("EnumClass", QString("Color::Green cast to int=%1, Size::Large cast to int=%2")
        .arg(ic).arg(is));

    // enum class 不需要作用域前缀给变量名（避免命名冲突）
    int Red = 999;  // 与 Color::Red 不冲突
    log("EnumClass", QString("int Red=%1 (no conflict with Color::Red)").arg(Red));
}

// ==================== static_assert ====================
void CppBasics::demoStaticAssert()
{
    // static_assert 在编译期检查条件（C++11）
    static_assert(sizeof(int) >= 4,  "int must be at least 4 bytes");
    static_assert(sizeof(void*) >= 4, "pointers must be at least 4 bytes");

    // 编译期常量表达式验证
    constexpr int N = 10;
    static_assert(N > 0, "N must be positive");

    log("StaticAssert",
        QString("static_assert passed: sizeof(int)=%1, sizeof(void*)=%2")
        .arg(sizeof(int)).arg(sizeof(void*)));
    log("StaticAssert",
        "编译期断言通过：条件不满足时编译直接失败，用于跨平台/版本检查");
}

// ==================== 实用工具 ====================
QVariant CppBasics::readMemoryAddress()
{
    quint64 addr = reinterpret_cast<quint64>(this);
    log("Memory", QString("this pointer address: 0x%1")
        .arg(addr, 0, 16));
    return QVariant(QString("0x%1").arg(addr, 0, 16));
}

QVariantList CppBasics::listAllTopics()
{
    return {
        // 基础类型
        QStringLiteral("BasicTypes"), QStringLiteral("Variable"), QStringLiteral("Const"),
        // 控制流
        QStringLiteral("IfElse"), QStringLiteral("Switch"), QStringLiteral("Loop"), QStringLiteral("RangeBasedFor"),
        // 函数
        QStringLiteral("Function"), QStringLiteral("DefaultParam"), QStringLiteral("Inline"), QStringLiteral("Lambda"),
        // 类
        QStringLiteral("Class"), QStringLiteral("Access"), QStringLiteral("Constructor"),
        QStringLiteral("Copy"), QStringLiteral("Operator"), QStringLiteral("Inherit"),
        QStringLiteral("Virtual"), QStringLiteral("Override"), QStringLiteral("SmartPointer"),
        // STL
        QStringLiteral("Vector"), QStringLiteral("Map"), QStringLiteral("String"), QStringLiteral("Algorithm"),
        // 高级特性
        QStringLiteral("Template"), QStringLiteral("Auto"), QStringLiteral("InitializerList"),
        QStringLiteral("Nullptr"), QStringLiteral("EnumClass"), QStringLiteral("StaticAssert")
    };
}
