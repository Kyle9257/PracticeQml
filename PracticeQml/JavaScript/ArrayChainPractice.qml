import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

/*
 * 数组链式调用与实战练习
 * 重点: filter/map/reduce/sort 的组合使用
 */

Item {
    id: root
    width: 700
    height: 900

    // ==================== 模拟真实数据 ====================
    
    // 商品数据
    property var products: [
        { id: 1, name: "iPhone 15", category: "手机", price: 5999, stock: 50, rating: 4.8 },
        { id: 2, name: "MacBook Pro", category: "电脑", price: 12999, stock: 20, rating: 4.9 },
        { id: 3, name: "AirPods Pro", category: "配件", price: 1899, stock: 100, rating: 4.7 },
        { id: 4, name: "iPad Air", category: "平板", price: 4799, stock: 35, rating: 4.6 },
        { id: 5, name: "Apple Watch", category: "配件", price: 2999, stock: 60, rating: 4.5 },
        { id: 6, name: "小米14", category: "手机", price: 3999, stock: 80, rating: 4.7 },
        { id: 7, name: "ThinkPad X1", category: "电脑", price: 8999, stock: 15, rating: 4.6 },
        { id: 8, name: "华为MatePad", category: "平板", price: 2999, stock: 45, rating: 4.4 }
    ]

    // 订单数据
    property var orders: [
        { orderId: "ORD001", userId: 1, productId: 1, quantity: 2, status: "completed", date: "2024-01-15" },
        { orderId: "ORD002", userId: 2, productId: 3, quantity: 1, status: "pending", date: "2024-01-16" },
        { orderId: "ORD003", userId: 1, productId: 5, quantity: 1, status: "completed", date: "2024-01-17" },
        { orderId: "ORD004", userId: 3, productId: 2, quantity: 1, status: "shipped", date: "2024-01-18" },
        { orderId: "ORD005", userId: 2, productId: 4, quantity: 3, status: "completed", date: "2024-01-19" }
    ]

    // 用户数据
    property var users: [
        { id: 1, name: "张三", level: "VIP", points: 5000 },
        { id: 2, name: "李四", level: "普通", points: 1200 },
        { id: 3, name: "王五", level: "VIP", points: 8000 }
    ]

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Text {
            text: "🛒 数组链式调用实战 - 电商数据处理"
            font.pixelSize: 22
            font.bold: true
        }

        // 结果展示区
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            color: "#fafafa"
            border.color: "#e0e0e0"
            radius: 8

            ScrollView {
                anchors.fill: parent
                anchors.margins: 10
                
                TextEdit {
                    id: outputArea
                    width: parent.width
                    wrapMode: TextEdit.WordWrap
                    selectByMouse: true
                    readOnly: true
                    text: "点击下方按钮执行不同练习..."
                }
            }
        }

        // 按钮区
        GridLayout {
            Layout.fillWidth: true
            columns: 3
            rowSpacing: 8
            columnSpacing: 8

            Button { text: "1. 筛选手机"; onClicked: exercise1() }
            Button { text: "2. 价格排序"; onClicked: exercise2() }
            Button { text: "3. 分类统计"; onClicked: exercise3() }
            Button { text: "4. 库存预警"; onClicked: exercise4() }
            Button { text: "5. 高评分商品"; onClicked: exercise5() }
            Button { text: "6. 订单关联"; onClicked: exercise6() }
            Button { text: "7. 用户消费"; onClicked: exercise7() }
            Button { text: "8. 综合查询"; onClicked: exercise8() }
            Button { text: "🏆 运行全部"; onClicked: runAll(); Layout.columnSpan: 3 }
        }

        // 代码展示区
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#263238"
            radius: 8

            Flickable {
                anchors.fill: parent
                anchors.margins: 10
                contentHeight: codeArea.implicitHeight
                clip: true

                TextEdit {
                    id: codeArea
                    width: parent.width
                    color: "#eceff1"
                    font.family: "Consolas, monospace"
                    wrapMode: TextEdit.WordWrap
                    selectByMouse: true
                    readOnly: true
                    text: "// 选择一个练习查看对应代码"
                }
            }
        }
    }

    // ==================== 练习函数 ====================

    function exercise1() {
        // 筛选手机类别商品
        let result = products.filter(p => p.category === "手机")
        
        outputArea.text = "📱 筛选手机类别商品:\n" + 
            result.map(p => `${p.name} - ¥${p.price}`).join("\n")
        
        codeArea.text = `// 练习1: 筛选手机类别
let result = products.filter(p => p.category === "手机")

// filter: 过滤数组，返回满足条件的元素
// p => p.category === "手机" 是箭头函数写法

// 结果:
${JSON.stringify(result, null, 2)}`
    }

    function exercise2() {
        // 按价格降序排序，取前3名
        let result = [...products]
            .sort((a, b) => b.price - a.price)
            .slice(0, 3)
        
        outputArea.text = "💰 价格最高的3件商品:\n" +
            result.map((p, i) => `${i+1}. ${p.name} - ¥${p.price}`).join("\n")
        
        codeArea.text = `// 练习2: 价格排序
let result = [...products]  // 复制数组避免修改原数组
    .sort((a, b) => b.price - a.price)  // 降序排序
    .slice(0, 3)  // 取前3个

// sort: 原地排序，会修改原数组
// 使用展开运算符[...]创建副本
// b.price - a.price 实现降序

// 结果:
${JSON.stringify(result.map(p => ({name: p.name, price: p.price})), null, 2)}`
    }

    function exercise3() {
        // 按类别统计库存和总价值
        let result = products.reduce((acc, p) => {
            if (!acc[p.category]) {
                acc[p.category] = { count: 0, stock: 0, value: 0 }
            }
            acc[p.category].count++
            acc[p.category].stock += p.stock
            acc[p.category].value += p.price * p.stock
            return acc
        }, {})
        
        let output = "📊 分类统计:\n"
        for (let cat in result) {
            output += `\n【${cat}】\n`
            output += `  商品数: ${result[cat].count}\n`
            output += `  库存: ${result[cat].stock}\n`
            output += `  总价值: ¥${result[cat].value.toLocaleString()}\n`
        }
        outputArea.text = output
        
        codeArea.text = `// 练习3: 分类统计
let result = products.reduce((acc, p) => {
    if (!acc[p.category]) {
        acc[p.category] = { count: 0, stock: 0, value: 0 }
    }
    acc[p.category].count++      // 商品数量+1
    acc[p[p.category].stock += p.stock  // 累加库存
    acc[p.category].value += p.price * p.stock  // 累加价值
    return acc  // 必须返回累加器
}, {})  // 初始值为空对象

// reduce: 将数组归约为单个值
// 这里用对象作为累加器，实现分组统计`
    }

    function exercise4() {
        // 库存预警：库存<30的商品，按紧急程度排序
        let result = products
            .filter(p => p.stock < 30)
            .sort((a, b) => a.stock - b.stock)
            .map(p => ({
                name: p.name,
                stock: p.stock,
                urgency: p.stock < 20 ? "🔴 紧急" : "🟡 注意"
            }))
        
        outputArea.text = "⚠️ 库存预警商品:\n" +
            result.map(p => `${p.urgency} ${p.name} - 库存: ${p.stock}`).join("\n")
        
        codeArea.text = `// 练习4: 库存预警
let result = products
    .filter(p => p.stock < 30)  // 步骤1: 筛选低库存
    .sort((a, b) => a.stock - b.stock)  // 步骤2: 按库存升序
    .map(p => ({  // 步骤3: 转换格式
        name: p.name,
        stock: p.stock,
        urgency: p.stock < 20 ? "🔴紧急" : "🟡注意"
    }))

// 链式调用: 多个数组方法连续调用
// 每个方法返回新数组，下一个方法继续处理
// 数据流: filter -> sort -> map`
    }

    function exercise5() {
        // 高评分(>=4.7)且价格<5000的商品
        let result = products
            .filter(p => p.rating >= 4.7 && p.price < 5000)
            .sort((a, b) => b.rating - a.rating)
        
        outputArea.text = "⭐ 高性价比商品(评分≥4.7, 价格<5000):\n" +
            result.map(p => `${p.name} - ¥${p.price} ⭐${p.rating}`).join("\n")
        
        codeArea.text = `// 练习5: 多条件筛选
let result = products
    .filter(p => p.rating >= 4.7 && p.price < 5000)
    .sort((a, b) => b.rating - a.rating)

// 组合条件使用 && (与) 或 || (或)
// p.rating >= 4.7 && p.price < 5000
// 表示同时满足两个条件`
    }

    function exercise6() {
        // 订单关联：找出已完成订单的商品详情
        let result = orders
            .filter(o => o.status === "completed")
            .map(o => {
                let product = products.find(p => p.id === o.productId)
                return {
                    orderId: o.orderId,
                    product: product.name,
                    quantity: o.quantity,
                    total: product.price * o.quantity
                }
            })
        
        outputArea.text = "📦 已完成订单详情:\n" +
            result.map(o => `${o.orderId}: ${o.product} x${o.quantity} = ¥${o.total}`).join("\n")
        
        codeArea.text = `// 练习6: 数组关联查询
let result = orders
    .filter(o => o.status === "completed")
    .map(o => {
        let product = products.find(p => p.id === o.productId)
        return {
            orderId: o.orderId,
            product: product.name,
            total: product.price * o.quantity
        }
    })

// find: 返回第一个满足条件的元素
// 类似于数据库的JOIN操作
// 通过productId关联orders和products`
    }

    function exercise7() {
        // 计算每个用户的消费总额
        let result = users.map(u => {
            let userOrders = orders.filter(o => o.userId === u.id)
            let totalSpent = userOrders.reduce((sum, o) => {
                let product = products.find(p => p.id === o.productId)
                return sum + product.price * o.quantity
            }, 0)
            return {
                name: u.name,
                level: u.level,
                orders: userOrders.length,
                totalSpent: totalSpent
            }
        }).sort((a, b) => b.totalSpent - a.totalSpent)
        
        outputArea.text = "👤 用户消费统计:\n" +
            result.map(u => `${u.name}(${u.level}): ${u.orders}单, ¥${u.totalSpent.toLocaleString()}`).join("\n")
        
        codeArea.text = `// 练习7: 用户消费统计
let result = users.map(u => {
    let userOrders = orders.filter(o => o.userId === u.id)
    let totalSpent = userOrders.reduce((sum, o) => {
        let product = products.find(p => p.id === o.productId)
        return sum + product.price * o.quantity
    }, 0)
    return { name: u.name, totalSpent }
}).sort((a, b) => b.totalSpent - a.totalSpent)

// 嵌套使用: map + filter + reduce + find
// 复杂业务逻辑的典型模式`
    }

    function exercise8() {
        // 综合查询：VIP用户购买的高评分商品
        let vipUsers = users.filter(u => u.level === "VIP").map(u => u.id)
        
        let result = orders
            .filter(o => vipUsers.includes(o.userId))
            .map(o => {
                let product = products.find(p => p.id === o.productId)
                let user = users.find(u => u.id === o.userId)
                return {
                    user: user.name,
                    product: product.name,
                    rating: product.rating,
                    price: product.price
                }
            })
            .filter(item => item.rating >= 4.7)
        
        outputArea.text = "🏆 VIP用户购买的高评分商品:\n" +
            result.map(r => `${r.user}购买了${r.product} ⭐${r.rating}`).join("\n")
        
        codeArea.text = `// 练习8: 综合查询
// 步骤1: 获取VIP用户ID列表
let vipUsers = users
    .filter(u => u.level === "VIP")
    .map(u => u.id)

// 步骤2: 查询VIP用户的订单
let result = orders
    .filter(o => vipUsers.includes(o.userId))
    .map(o => {
        let product = products.find(p => p.id === o.productId)
        let user = users.find(u => u.id === o.userId)
        return { user: user.name, product: product.name, rating: product.rating }
    })
    .filter(item => item.rating >= 4.7)

// includes: 检查数组是否包含某值
// 多表关联 + 多条件筛选的完整示例`
    }

    function runAll() {
        console.log("\n========== 运行所有练习 ==========\n")
        exercise1()
        exercise2()
        exercise3()
        exercise4()
        exercise5()
        exercise6()
        exercise7()
        exercise8()
        console.log("========== 练习完成 ==========\n")
    }

    Component.onCompleted: {
        console.log("=== 数组链式调用实战组件加载完成 ===")
    }
}
