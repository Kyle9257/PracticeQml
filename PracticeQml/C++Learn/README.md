# C++Learn — C++ 基础学习辅助模块

## 文件说明

| 文件 | 说明 |
|------|------|
| `CppBasics.h` | 头文件：类声明、所有 demo 方法声明、Qt 信号声明 |
| `CppBasics.cpp` | 源文件：所有示例实现（详细注释） |
| `README.md` | 本文件 |

## 如何集成到项目

### 1. 修改 `.pro` 文件，添加源文件

```pro
SOURCES += \
    C++Learn/CppBasics.cpp \
    # 其他已有 .cpp...

HEADERS += \
    C++Learn/CppBasics.h \
    # 其他已有 .h...
```

### 2. 在 main.cpp 中注册到 QML

```cpp
#include "C++Learn/CppBasics.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    // ... 现有代码 ...

    // 在 load qrc 之前注册
    qmlRegisterType<CppBasics>("CppLearn", 1, 0, "CppBasics");

    engine.load(url);
    return app.exec();
}
```

### 3. 在 QML 中使用

```qml
import CppLearn 1.0

Item {
    CppBasics {
        id: cppLearn

        // 信号绑定：将输出打印到控制台或 TextArea
        onOutput: console.log(msg)

        // 列出所有可用的 demo 主题
        Component.onCompleted: {
            var topics = cppLearn.listAllTopics()
            topics.forEach(t => console.log(" - " + t))
        }

        // 调用示例
        MouseArea {
            anchors.fill: parent
            onClicked: {
                cppLearn.demoBasicTypes()
                cppLearn.demoVariable()
                cppLearn.demoLambda()
                cppLearn.demoSmartPointer()
            }
        }
    }
}
```

## 示例主题清单

### 基础类型
| 主题 | 内容 |
|------|------|
| `BasicTypes` | int / long / float / double / char / bool / sizeof |
| `Variable` | 变量声明、初始化方式（copy / direct / brace）、auto 推导 |
| `Const` | const / constexpr、编译期常量、数组维度 |

### 控制流
| 主题 | 内容 |
|------|------|
| `IfElse` | if / else if / else、三目运算符 |
| `Switch` | switch + break、case 穿透 |
| `Loop` | for / while / do-while、break / continue |
| `RangeBasedFor` | C++11 范围 for 循环 |

### 函数
| 主题 | 内容 |
|------|------|
| `Function` | 函数声明与调用、返回类型推导 |
| `DefaultParam` | 默认参数 |
| `Inline` | inline 关键字含义 |
| `Lambda` | 捕获方式（值 / 引用 / mutable）、generic lambda (C++14) |

### 类与对象
| 主题 | 内容 |
|------|------|
| `Class` | struct / class、嵌套类 |
| `Access` | public / private / protected |
| `Constructor` | 默认构造、参数构造、析构函数 |
| `Copy` | 拷贝构造 vs 移动构造、深拷贝 vs 浅拷贝 |
| `Operator` | 运算符重载示例（+ / []） |
| `Inherit` | 继承、向上转型、静态绑定 |
| `Virtual` | 虚函数、动态多态、dynamic_cast、typeid |
| `Override` | override 说明符，防止意外隐藏 |
| `SmartPointer` | unique_ptr / shared_ptr / weak_ptr |

### STL 容器与算法
| 主题 | 内容 |
|------|------|
| `Vector` | push_back / insert / erase / emplace / initializer_list |
| `Map` | map / unordered_map、find / emplace |
| `String` | std::string 子串 / 拼接 / stoi / to_string |
| `Algorithm` | sort / reverse / find / count_if / accumulate / transform |

### C++11/14 现代特性
| 主题 | 内容 |
|------|------|
| `Template` | 函数模板、类型萃取 std::is_same / enable_if |
| `Auto` | auto 推导规则、auto & / auto && |
| `InitializerList` | std::initializer_list |
| `Nullptr` | nullptr vs NULL vs 0 |
| `EnumClass` | 强类型枚举 |
| `StaticAssert` | 编译期断言 |

## 学习建议

1. **按顺序学**：基础类型 → 控制流 → 函数 → 类 → STL → 现代特性
2. **动手改**：每个 demo 改几个参数或逻辑，观察输出变化
3. **QML 联动**：结合 QML 可视化，理解 C++ 对象如何在 QML 端调用
4. **对比学习**：例如 `demoCopy` 中的深拷贝 vs 浅拷贝、 `demoInherit` 中有无 virtual 的区别

## 注意事项

- 所有 demo 方法均为 `Q_INVOKABLE`，可直接从 QML 调用
- 信号 `output` 会同时输出到 Qt 控制台（qDebug）和 QML 端，适合调试
- `demoCopy` / `demoInherit` / `demoVirtual` 中含有 `new` / `delete`，注意内存生命周期
