# UITableView

1. 表视图只能有一列, 但行数没有限制, 不负责存储表中的数据, 只存储足够绘制当前可见行的数据
2. 表视图从遵循 UITableViewDelegate 协议的对象获取配置数据, 从遵循 UITableViewDataSource 协议的对象获得行数据
3. 表视图有分组表(grouped table), 无格式表(plain table)两种基本样式, 使用索引的无格式表称为索引表(indexed table), 数据源提供的信息用于使用右侧的索引在列表中进行导航, 
4. 数据源的分区(section): 分组表的一组, 索引表的没给索引都是分区
5. 表单元标识符: 不同类型的单元需要使用不同的表单元标识符

表视图单元样式

1. 图像
2. 文本标签
3. 详细文本标签

default: 文本标签在左, 图像在左, 没有详细文本标签
subtitle: 文本标签在左上, 详细文本标签在左下, 有图像
value1: 文本标签在左, 详细文本标签在右, 有图像
value2: 文本标签在详细文本标签左侧, 没有图像

定制表视图单元格式

1. 在创建单元时通过程序向 UITableViewCell 添加子视图
2. 从 nib 文件中加载单元
3. 从 storyboard 中加载单元

UITableView 的方法

```
// Returns a reusable table-view cell object for the specified reuse identifier and adds it to the table.
UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:HomeCellIdentifier forIndexPath:indexPath];
```

# UITableViewCell

1. UITableView 是由一系列 UITableViewCell 组成的列表, 每个 UITableViewCell 对象可以包含图像, 文本, 可选附加图标, 可以添加子视图, 放置更多数据, 可以在创建单元格时在程序中添加子视图或从 storyboard, nib 文件加载
2. identifier: 用于标识 cell 对象

作用

1. setting and managing cell content and background (including text, images, and custom views)
2. managing the cell selection and highlight state
3. managing accessory views
4. initiating the editing of the cell contents

UITableViewCell 的属性

1. textLabel, detailTextLabel, imageView: set the text and images of the cell
2. contentView: add subviews
3. backgroundView:
4. backgroundColor:

UITableViewCell 的方法

```
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
```

# 表视图委托和数据源

6. 遵循对应协议的控制器即成为该表视图的委托或数据源
2. 数据源提供了绘制表所需的所有数据
3. 委托用于配置表视图的外观并处理某些用户交互
