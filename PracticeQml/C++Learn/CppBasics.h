#ifndef CPPBASICS_H
#define CPPBASICS_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QVariantList>

/**
 * @brief C++ 基础学习辅助类
 *
 * 本类通过 Qt 信号槽机制，将 C++ 基础概念以可视化方式呈现。
 * 每个示例方法对应一个信号，触发后在 QML 端观察输出结果。
 *
 * 用法：在 QML 中通过 Connections 连接 signals，
 *       或直接调用 demo 方法观察控制台输出。
 */
class CppBasics : public QObject
{
    Q_OBJECT

public:
    explicit CppBasics(QObject *parent = nullptr);

    // ---- 基础类型演示 ----
    Q_INVOKABLE void demoBasicTypes();    // 基本数据类型
    Q_INVOKABLE void demoVariable();      // 变量与初始化
    Q_INVOKABLE void demoConst();         // const 与 constexpr

    // ---- 控制流演示 ----
    Q_INVOKABLE void demoIfElse();        // if / else if / else
    Q_INVOKABLE void demoSwitch();        // switch
    Q_INVOKABLE void demoLoop();          // for / while / do-while
    Q_INVOKABLE void demoRangeBasedFor(); // 范围 for 循环（C++11）

    // ---- 函数演示 ----
    Q_INVOKABLE void demoFunction();              // 普通函数
    Q_INVOKABLE void demoDefaultParam();          // 默认参数
    Q_INVOKABLE void demoInline();                // 内联函数
    Q_INVOKABLE void demoLambda();                // Lambda 表达式（C++11）

    // ---- 类与对象演示 ----
    Q_INVOKABLE void demoClass();                 // 类与对象基础
    Q_INVOKABLE void demoAccess();                // 访问控制 public / private / protected
    Q_INVOKABLE void demoConstructor();           // 构造与析构
    Q_INVOKABLE void demoCopy();                  // 拷贝构造与移动构造
    Q_INVOKABLE void demoOperator();              // 运算符重载
    Q_INVOKABLE void demoInherit();                // 继承
    Q_INVOKABLE void demoVirtual();               // 虚函数与多态
    Q_INVOKABLE void demoOverride();              // override 说明符（C++11）
    Q_INVOKABLE void demoSmartPointer();           // 智能指针（C++11）

    // ---- STL 演示 ----
    Q_INVOKABLE void demoVector();        // std::vector
    Q_INVOKABLE void demoMap();           // std::map
    Q_INVOKABLE void demoString();         // std::string
    Q_INVOKABLE void demoAlgorithm();      // 常用算法（sort / find 等）

    // ---- 高级特性演示 ----
    Q_INVOKABLE void demoTemplate();               // 模板
    Q_INVOKABLE void demoAuto();                   // auto 关键字（C++11）
    Q_INVOKABLE void demoRangefor();               // 范围 for 循环
    Q_INVOKABLE void demoInitializerList();        // initializer_list（C++11）
    Q_INVOKABLE void demoNullptr();                // nullptr（C++11）
    Q_INVOKABLE void demoEnumClass();              // enum class（C++11）
    Q_INVOKABLE void demoStaticAssert();           // static_assert（C++11）

    // ---- 实用工具 ----
    Q_INVOKABLE QVariant readMemoryAddress();       // 读取自身 this 指针地址（辅助理解指针）
    Q_INVOKABLE QVariantList listAllTopics();      // 返回所有示例主题列表

signals:
    // 通用信号：输出信息（可连接至 QML 端 TextArea 或 ListView）
    void output(const QString &msg);
    // 基础类型
    void sigBasicTypes(const QString &msg);
    void sigVariable(const QString &msg);
    void sigConst(const QString &msg);
    // 控制流
    void sigIfElse(const QString &msg);
    void sigSwitch(const QString &msg);
    void sigLoop(const QString &msg);
    void sigRangeBasedFor(const QString &msg);
    // 函数
    void sigFunction(const QString &msg);
    void sigDefaultParam(const QString &msg);
    void sigInline(const QString &msg);
    void sigLambda(const QString &msg);
    // 类
    void sigClass(const QString &msg);
    void sigAccess(const QString &msg);
    void sigConstructor(const QString &msg);
    void sigCopy(const QString &msg);
    void sigOperator(const QString &msg);
    void sigInherit(const QString &msg);
    void sigVirtual(const QString &msg);
    void sigOverride(const QString &msg);
    void sigSmartPointer(const QString &msg);
    // STL
    void sigVector(const QString &msg);
    void sigMap(const QString &msg);
    void sigString(const QString &msg);
    void sigAlgorithm(const QString &msg);
    // 高级
    void sigTemplate(const QString &msg);
    void sigAuto(const QString &msg);
    void sigRangefor(const QString &msg);
    void sigInitializerList(const QString &msg);
    void sigNullptr(const QString &msg);
    void sigEnumClass(const QString &msg);
    void sigStaticAssert(const QString &msg);

private:
    // 辅助：统一 emit 输出信号
    void log(const QString &category, const QString &msg);
};

#endif // CPPBASICS_H
