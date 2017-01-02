# UITableView

UITableView 的方法

```
// Returns a reusable table-view cell object for the specified reuse identifier and adds it to the table.
UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:HomeCellIdentifier forIndexPath:indexPath];
```

# UITableViewCell

1. UITableView 是由一系列 UITableViewCell 组成的列表
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

# 参考

1. [UITableViewCell - UIKit | Apple Developer Documentation](https://developer.apple.com/reference/uikit/uitableviewcell)
1. [UITableView 系列之自定义 UITableViewCell](http://www.cnblogs.com/wzrong/p/3261130.html)
1. [趣味苹果开发](http://www.cnblogs.com/liufan9/tag/TableViewController/)
