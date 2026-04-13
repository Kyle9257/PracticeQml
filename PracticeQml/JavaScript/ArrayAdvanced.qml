import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

/*
 * 数组高级操作练习
 * 涵盖: reduce, sort, some, every, flat, forEach高级用法
 */

Item {
    id: root
    width: 600
    height: 800

    // ==================== 测试数据 ====================
    
    // 简单数字数组
    property var numbers: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    
    // 对象数组 - 学生成绩
    property var students: [
        { name: "张三", age: 20, score: 85, subject: "数学" },
        { name: "李四", age: 22, score: 92, subject: "数学" },
        { name: "王五", age: 21, score: 78, subject: "英语" },
        { name: "赵六", age: 20, score: 88, subject: "英语" },
        { name: "钱七", age: 23, score: 95, subject: "数学" },
        { name: "孙八", age: 21, score: 67, subject: "物理" }
    ]
    
    // 嵌套数组
    property var nestedArray: [[1, 2, 3], [4, 5], [6, 7, 8, 9]]
    
    // 带空值的数组
    property var sparseArray: [1, null, 3, undefined, 5, "", 0]

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Text {
            text: "数组高级操作练习"
            font.pixelSize: 24
            font.bold: true
        }

        // ==================== reduce 练习 ====================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#e3f2fd"
            radius: 8

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "📌 reduce - 归约操作"
                    font.bold: true
                    color: "#1976d2"
                }
                Text {
                    id: reduceResult
                    text: "结果将显示在这里..."
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        // ==================== sort 练习 ====================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#f3e5f5"
            radius: 8

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "📌 sort - 排序操作"
                    font.bold: true
                    color: "#7b1fa2"
                }
                Text {
                    id: sortResult
                    text: "结果将显示在这里..."
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        // ==================== some/every 练习 ====================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#e8f5e9"
            radius: 8

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "📌 some/every - 条件检测"
                    font.bold: true
                    color: "#388e3c"
                }
                Text {
                    id: someEveryResult
                    text: "结果将显示在这里..."
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        // ==================== flat 练习 ====================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            color: "#fff3e0"
            radius: 8

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    text: "📌 flat/flatMap - 数组扁平化"
                    font.bold: true
                    color: "#f57c00"
                }
                Text {
                    id: flatResult
                    text: "结果将显示在这里..."
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        // ==================== 操作按钮 ====================
        RowLayout {
            Layout.topMargin: 10
            spacing: 10

            Button {
                text: "运行所有练习"
                onClicked: runAllExercises()
            }
            Button {
                text: "reduce详解"
                onClicked: reduceExercises()
            }
            Button {
                text: "sort详解"
                onClicked: sortExercises()
            }
            Button {
                text: "条件检测"
                onClicked: someEveryExercises()
            }
            Button {
                text: "扁平化"
                onClicked: flatExercises()
            }
        }
    }

    // ==================== 练习函数 ====================

    function runAllExercises() {
        reduceExercises()
        sortExercises()
        someEveryExercises()
        flatExercises()
    }

    function reduceExercises() {
        console.log("\n========== REDUCE 练习 ==========")
        let results = []

        // 1. 基础求和
        let sum = numbers.reduce((acc,cur)=>acc + cur,0)
        console.log("求和")
        results.push("求和",sum)

        //等价于.ES6引入的箭头函数写法
        let sum1 = numbers.reduce(function(acc, cur){
            return acc + cur;
        },0)

        // 2. 求最大值
        let max = numbers.reduce((acc,cur)=>cur > acc ? cur : acc, 0)
        console.log("最大值")
        results.push("最大值",max)

        // 3. 统计学生总成绩
        let totalScore = students.reduce((acc, s) => acc + s.score, 0)
        console.log("总成绩:", totalScore)
        results.push("总成绩: " + totalScore)

        // 4. 按学科分组
        let groupBySubject = students.reduce((acc, s) => {
            if (!acc[s.subject]) {
                acc[s.subject] = []
            }
            acc[s.subject].push(s.name)
            return acc
        }, {})
        console.log("按学科分组:", JSON.stringify(groupBySubject))
        results.push("分组: " + JSON.stringify(groupBySubject))

        // 5. 计算平均年龄
        let avgAge = students.reduce((acc, s, idx, arr) => {
            acc += s.age
            if (idx === arr.length - 1) {
                return acc / arr.length
            }
            return acc
        }, 0)
        console.log("平均年龄:", avgAge.toFixed(2))
        results.push("平均年龄: " + avgAge.toFixed(2))

        // 6. 数组去重
        let duplicates = [1, 2, 2, 3, 3, 3, 4, 5, 5]
        let unique = duplicates.reduce((acc, cur) => {
            if (!acc.includes(cur)) {
                acc.push(cur)
            }
            return acc
        }, [])
        console.log("去重结果:", unique)
        results.push("去重: " + unique)

        reduceResult.text = results.join("\n")
    }

    function sortExercises() {
        console.log("\n========== SORT 练习 ==========")
        let results = []

        // 1. 数字升序排序
        let ascSorted = [...numbers].sort((a, b) => a - b)
        console.log("升序:", ascSorted)
        results.push("升序: " + ascSorted.slice(0, 5) + "...")

        // 2. 数字降序排序
        let descSorted = [...numbers].sort((a, b) => b - a)
        console.log("降序:", descSorted)
        results.push("降序: " + descSorted.slice(0, 5) + "...")

        // 3. 按成绩排序学生
        let byScore = [...students].sort((a, b) => b.score - a.score)
        console.log("按成绩排序:", byScore.map(s => s.name + ":" + s.score))
        results.push("成绩排名: " + byScore.map(s => s.name).join(", "))

        // 4. 按年龄升序，年龄相同按成绩降序
        let complexSort = [...students].sort((a, b) => {
            if (a.age !== b.age) return a.age - b.age
            return b.score - a.score
        })
        console.log("复合排序:", complexSort.map(s => `${s.name}(年龄${s.age},成绩${s.score})`))
        results.push("复合排序: " + complexSort.map(s => s.name).join(", "))

        // 5. 字符串排序（中文）
        let names = ["张三", "李四", "王五", "赵六"]
        let nameSorted = names.sort((a, b) => a.localeCompare(b, "zh-CN"))
        console.log("中文排序:", nameSorted)
        results.push("中文排序: " + nameSorted.join(", "))

        // 6. 随机打乱数组
        let shuffled = [...numbers].sort(() => Math.random() - 0.5)
        console.log("随机打乱:", shuffled)
        results.push("随机打乱: " + shuffled.slice(0, 5) + "...")

        sortResult.text = results.join("\n")
    }

    function someEveryExercises() {
        console.log("\n========== SOME/EVERY 练习 ==========")
        let results = []

        // some: 是否存在满足条件的元素
        let hasHighScore = students.some(s => s.score >= 90)
        console.log("有90分以上学生:", hasHighScore)
        results.push("有90分以上: " + hasHighScore)

        let hasPhysics = students.some(s => s.subject === "物理")
        console.log("有物理学生:", hasPhysics)
        results.push("有物理学生: " + hasPhysics)

        // every: 是否所有元素都满足条件
        let allPassed = students.every(s => s.score >= 60)
        console.log("全部及格:", allPassed)
        results.push("全部及格: " + allPassed)

        let allAdults = students.every(s => s.age >= 18)
        console.log("全部成年:", allAdults)
        results.push("全部成年: " + allAdults)

        // 实际应用：验证表单
        let formData = [
            { field: "username", value: "admin", required: true },
            { field: "password", value: "123456", required: true },
            { field: "email", value: "", required: false }
        ]
        let allRequiredFilled = formData.every(f => !f.required || f.value !== "")
        console.log("必填项已填写:", allRequiredFilled)
        results.push("必填项已填: " + allRequiredFilled)

        // 检查数组中是否有空值
        let hasEmpty = sparseArray.some(v => v === null || v === undefined || v === "")
        console.log("有空值:", hasEmpty)
        results.push("有空值: " + hasEmpty)

        someEveryResult.text = results.join("\n")
    }

    // 手动实现 flat 函数（兼容 Qt 5.15）
    function flattenArray(arr, depth) {
        if (depth === undefined) depth = 1
        
        let result = []
        for (let i = 0; i < arr.length; i++) {
            if (Array.isArray(arr[i]) && depth > 0) {
                result = result.concat(flattenArray(arr[i], depth - 1))
            } else {
                result.push(arr[i])
            }
        }
        return result
    }

    // 手动实现 flatMap 函数（兼容 Qt 5.15）
    function flatMapArray(arr, mapper) {
        let result = []
        for (let i = 0; i < arr.length; i++) {
            let mapped = mapper(arr[i], i, arr)
            if (Array.isArray(mapped)) {
                result = result.concat(mapped)
            } else {
                result.push(mapped)
            }
        }
        return result
    }

    function flatExercises() {
        console.log("\n========== FLAT 练习 ==========")
        let results = []

        // 1. 基础扁平化
        let flattened = flattenArray(nestedArray, 1)
        console.log("扁平化1层:", flattened)
        results.push("flat(): " + flattened)

        // 2. 指定深度
        let deepNested = [[[1, 2], [3, 4]], [[5, 6]]]
        let flat2 = flattenArray(deepNested, 2)
        console.log("扁平化2层:", flat2)
        results.push("flat(2): " + flat2)

        // 3. 完全扁平化（使用足够大的深度）
        let veryDeep = [1, [2, [3, [4, [5]]]]]
        let flatAll = flattenArray(veryDeep, 10)  // Qt 5.15 不支持 Infinity
        console.log("完全扁平化:", flatAll)
        results.push("flat(深度10): " + flatAll)

        // 4. flatMap - 映射后扁平化
        let sentences = ["Hello World", "QML JavaScript"]
        let words = flatMapArray(sentences, function(s) { return s.split(" ") })
        console.log("分词结果:", words)
        results.push("flatMap分词: " + words)

        // 5. flatMap 实际应用 - 提取所有学生的课程
        let studentsWithCourses = [
            { name: "张三", courses: ["数学", "物理"] },
            { name: "李四", courses: ["英语", "化学"] },
            { name: "王五", courses: ["数学", "英语"] }
        ]
        let allCourses = flatMapArray(studentsWithCourses, function(s) { return s.courses })
        console.log("所有课程:", allCourses)
        results.push("所有课程: " + allCourses)

        // 6. 去除空值
        let cleaned = flattenArray([sparseArray], 1).filter(function(v) { 
            return v !== null && v !== undefined && v !== "" 
        })
        console.log("清理空值:", cleaned)
        results.push("清理空值: " + cleaned)

        flatResult.text = results.join("\n")
    }

    // ==================== 进阶练习函数 ====================

    function advancedExercises() {
        console.log("\n========== 进阶综合练习 ==========")
        console.log("查看 ArrayChainPractice.qml 获取更多链式调用练习")
    }

    function practiceNow() {
        console.log("===== 练习题 =====")
        
        // 练习1: 使用reduce实现count功能
        let arr = ['apple', 'banana', 'apple', 'orange', 'banana', 'apple']
        let fruitCount = arr.reduce((acc, fruit) => {
            acc[fruit] = (acc[fruit] || 0) + 1
            return acc
        }, {})
        console.log("水果统计:", JSON.stringify(fruitCount))
        
        // 练习2: 使用sort实现多条件排序
        let multiSort = [...students].sort((a, b) => {
            if (a.age !== b.age) return a.age - b.age
            return b.score - a.score
        })
        console.log("多条件排序:", multiSort.map(s => s.name))
        
        // 练习3: 使用some检测数组是否包含某对象
        let hasZhangSan = students.some(s => s.name === "张三")
        console.log("有张三:", hasZhangSan)
    }

    Component.onCompleted: {
        console.log("=== 数组高级操作练习组件加载完成 ===")
        console.log("点击按钮运行不同练习")
    }
}
