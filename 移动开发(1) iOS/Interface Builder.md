
```
#ifndef IBOutlet
#define IBOutlet
#endif

#ifndef IBAction
#define IBAction void
#endif
```

1. Interface Builder 建立代码和界面对象之间的通信
2. IBOutlet 和 IBOutlet 对于 Interface Builder 上的控件, 是用于识别变量或方法标记, 对于编译器而言, 前者为空, 后者为 void, 没有实际意义
3. IBOutlet 本质是 xib 文件中某一个控件的指针, IBAction 本质是 xib 文件中某一个控件的 action
4. 在变量前增加 IBOutlet 来说明该变量将与界面上的某个 UI 对象对应, Interface Builder 根据 IBOutlet 来寻找可以在 Builder 里操作的成员变量
5. 在方法前增加 IBAction 来说明该方法将与 Interface Builder 界面上的某个事件对应, 即与控件的相应动作相关联
6. 任何一个被声明为 IBOutlet 并且在 Interface Builder 里被连接到一个 UI 组件的成员变量, 会被额外保持(retain)一次, 只要使用了 IBOutlet 变量, 一定需要在 dealloc 或者 viewDidUnload 里 release 这个变量

```
IBOutlet UILabel *label;	// 变量 label 在 Interface Builder 里被连接到一个 UILabel 控件. 此时, 这个 label 的 retainCount 为2
IBoutlet修饰的字段可以和InterfaceBuilder里相应控件相关联；
IBaction修饰的方法可以和里。
- (IBAction)button_click: (id)sender;	// sender 是指当前的那个 control, 这样就可以不但是一个 button 对应一个 action, 而且可以让多个 button 对应与同一个 action
```

action sheet

alert 对话框的设置
