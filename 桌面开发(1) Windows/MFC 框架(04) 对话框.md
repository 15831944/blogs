# 对话框 Dialog

1. 对话框和菜单一样, 都可以是资源
2. 使用 CDialog 的派生类操作对话框资源, IDD 数据成员的值是对话框资源的ID号

1. 模态(modal)对话框: 令其父窗口无效，直到对话框结束, 才能继续执行程序的其他任务，使用 CDialog::DoModal, CDialog::EndDialog 函数创建和删除
2. 非模态(modeless)对话框: 父窗口与对话框共同运行, CDialog::Create

1. 对话框模板(dialog templete)
2. 对话框函数(dialog procedure)

窗口

1. 前台窗口
2. 后台窗口

窗口的Z次序

1. 窗口的Z次序(Z-order)表明重叠窗口堆中窗口的(向屏幕外延伸的Z轴的)位置, Windows 系统管理3个独立的Z次序.

1. 顶层窗口: 任何时候只有一个活动的顶层窗口(被激活)
2. 兄弟窗口: 共享同一个父窗口的多个子窗口,
3. 最顶层窗口: 覆盖所有其他窗口, 不管是活动窗口或是前台窗口, 设置为 WS_EX_TOPMOST 风格

# 属性表单和向导 Property Sheet, Wizard

1. 属性页 Property Page: 编辑->添加资源->新建

# 控件 Control

1. 组框 Group Box
1. 单选按钮 Radio Button, 第一个单选框的 group 属性设为真则直达下一个真之前的单选框为一组
1. 列表框 List Box
1. 复选框 Check Box
1. 组合框 Combo Box, 编辑框和列表框的组合, 默认会按名称排序
