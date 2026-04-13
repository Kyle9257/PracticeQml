#ifndef STLPRACTICE_H
#define STLPRACTICE_H

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

/**
 * @brief STL 容器与算法练习类
 *
 * 每个 demo 方法对应一组 STL 用法示例，
 * 通过 Qt 信号将结果输出到 QML 端。
 *
 * 学习顺序建议：
 *   容器顺序：vector → list → deque → set/map → unordered → stack/queue
 *   算法顺序：遍历 → 查找 → 排序 → 变换 → 数值
 */
class STLPractice : public QObject
{
    Q_OBJECT

public:
    explicit STLPractice(QObject *parent = nullptr);

    // ========== 容器 ==========
    // 序列容器
    Q_INVOKABLE void demoVector();     // std::vector
    Q_INVOKABLE void demoList();       // std::list（双向链表）
    Q_INVOKABLE void demoDeque();      // std::deque（双端队列）

    // 关联容器
    Q_INVOKABLE void demoSet();        // std::set / multiset
    Q_INVOKABLE void demoMap();        // std::map / multimap
    Q_INVOKABLE void demoUnorderedSet(); // std::unordered_set
    Q_INVOKABLE void demoUnorderedMap(); // std::unordered_map

    // 容器适配器
    Q_INVOKABLE void demoStack();      // std::stack
    Q_INVOKABLE void demoQueue();      // std::queue
    Q_INVOKABLE void demoPriorityQueue(); // std::priority_queue

    // ========== 迭代器 ==========
    Q_INVOKABLE void demoIterator();   // 迭代器基础用法
    Q_INVOKABLE void demoReverseIterator(); // 反向迭代器
    Q_INVOKABLE void demoIteratorAdaptor(); // insert_iterator / stream_iterator

    // ========== 算法 ==========
    Q_INVOKABLE void demoAlgoForEach();    // for_each + lambda
    Q_INVOKABLE void demoAlgoFind();        // find / find_if / find_if_not
    Q_INVOKABLE void demoAlgoCount();       // count / count_if
    Q_INVOKABLE void demoAlgoSort();        // sort / stable_sort / partial_sort
    Q_INVOKABLE void demoAlgoBinarySearch(); // binary_search / lower_bound / upper_bound
    Q_INVOKABLE void demoAlgoMergeSet();    // merge / set_union / set_intersection
    Q_INVOKABLE void demoAlgoTransform();   // transform
    Q_INVOKABLE void demoAlgoRemoveErase(); // remove / erase idiom（重要）
    Q_INVOKABLE void demoAlgoNumeric();      // accumulate / iota
    Q_INVOKABLE void demoAlgoMinMax();       // min / max / minmax
    Q_INVOKABLE void demoAlgoHeap();         // make_heap / sort_heap / priority_queue
    Q_INVOKABLE void demoAlgoPermutation();  // next_permutation / prev_permutation
    Q_INVOKABLE void demoAlgoAllOf();        // all_of / any_of / none_of（C++11）

    // ========== 函数对象 ==========
    Q_INVOKABLE void demoFunctionObject();   // 函数对象（仿函数）
    Q_INVOKABLE void demoBind();             // std::bind 占位符
    Q_INVOKABLE void demoMemFn();            // std::mem_fn（C++11）

    // ========== 工具 ==========
    Q_INVOKABLE void demoTuple();            // std::tuple（C++11）
    Q_INVOKABLE void demoPair();             // std::pair
    Q_INVOKABLE void demoOptional();         // std::optional（C++17，如编译器支持）
    Q_INVOKABLE void demoVariant();          // std::variant（C++17，如编译器支持）

    // ========== 实用工具 ==========
    Q_INVOKABLE QVariantMap containerInfo(const QString &containerName);
    Q_INVOKABLE QVariantList listAllTopics();

signals:
    void output(const QString &msg);

    // 容器信号
    void sigVector(const QString &msg);
    void sigList(const QString &msg);
    void sigDeque(const QString &msg);
    void sigSet(const QString &msg);
    void sigMap(const QString &msg);
    void sigUnorderedSet(const QString &msg);
    void sigUnorderedMap(const QString &msg);
    void sigStack(const QString &msg);
    void sigQueue(const QString &msg);
    void sigPriorityQueue(const QString &msg);

    // 迭代器信号
    void sigIterator(const QString &msg);
    void sigReverseIterator(const QString &msg);
    void sigIteratorAdaptor(const QString &msg);

    // 算法信号
    void sigForEach(const QString &msg);
    void sigFind(const QString &msg);
    void sigCount(const QString &msg);
    void sigSort(const QString &msg);
    void sigBinarySearch(const QString &msg);
    void sigMergeSet(const QString &msg);
    void sigTransform(const QString &msg);
    void sigRemoveErase(const QString &msg);
    void sigNumeric(const QString &msg);
    void sigMinMax(const QString &msg);
    void sigHeap(const QString &msg);
    void sigPermutation(const QString &msg);
    void sigAllOf(const QString &msg);

    // 函数对象
    void sigFunctionObject(const QString &msg);
    void sigBind(const QString &msg);
    void sigMemFn(const QString &msg);

    // 工具
    void sigTuple(const QString &msg);
    void sigPair(const QString &msg);
    void sigOptional(const QString &msg);
    void sigVariant(const QString &msg);

private:
    void log(const QString &tag, const QString &msg);

    // 通用容器打印辅助（模板成员函数）
    template<typename Container>
    QString containerToString(const Container &c);

    template<typename It>
    QString rangeToString(It first, It last);
};

#endif // STLPRACTICE_H
