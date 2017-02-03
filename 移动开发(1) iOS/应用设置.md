# Setting Bundle 设置捆绑包

1. 应用自带的一组文件, 用于设置应用, 设置应用可以根据属性列表自动创建界面
2. Root.plist 属性列表: 定义根级偏好设置视图, 可为子视图添加条目, 可显示易读形式, 也可以显示原始(raw)键值数据

# User Defaults 用户默认设置机制

1. NSUserDefaults 类是单例类, 用键值对方式来保存和读取偏好设置, 数据被持久保存在文件系统中

```

```

# 属性列表

1. 属性类表的本质是字典
2. 节点: 包括 Boolean, Data, Date, Number, String 节点类型
3. 节点集合: 包括 Dictionary(只能以字符串类型作为键), Array 节点类型
