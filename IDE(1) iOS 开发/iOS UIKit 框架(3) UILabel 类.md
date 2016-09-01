# UILabel 类

UILabel 类继承自 UIView

UILabel 默认是透明的

# UILabel 属性

| 属性 | 含义 |
| - | - |
| text | 文本内容 |
| textColor | 文本颜色 |
| textAlignment | 文本布局 |
| alpha | 透明度，整个 Label，而非只是本文或控件 |
| font | 字体及字号(斜体对中文无效) |
| shadowColor | 文本阴影颜色 |
| shadowOffset | 文本阴影偏移位置 |
| lineBreakMode | 断行模式 |
| numberOfLines | 行数(设置为0或-1表示不限制行数) |

# 示例

```
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    UILabel *myLabel = [[UILabel alloc]init];
    myLabel.frame = CGRectMake(20, 40, 300, 300);
    myLabel.backgroundColor = [UIColor yellowColor];
    myLabel.text = @"Label1 Label2 Label3 Label4 Label5 Label6 Label7 Label8 Label9 Label10 Label11 Label12";
    myLabel.alpha = 0.8;
    
    myLabel.font = [UIFont systemFontOfSize:25];
    myLabel.font = [UIFont boldSystemFontOfSize:25];
    myLabel.font = [UIFont italicSystemFontOfSize:25];
    myLabel.font = [UIFont fontWithName:@"Geeza Pro" size:25];
    
    myLabel.shadowColor = [UIColor grayColor];
    myLabel.shadowOffset = CGSizeMake(-5, 20);
    
    myLabel.lineBreakMode = NSLineBreakByWordWrapping;
    
    myLabel.numberOfLines = 10;
    myLabel.numberOfLines = -1;
    
    myLabel.textAlignment = NSTextAlignmentCenter;
    
    myLabel.textColor = [UIColor clearColor];
    myLabel.textColor = [UIColor redColor];
    myLabel.textColor = [UIColor colorWithRed:0.43 green:0.80 blue:0.96 alpha:1.00];
    // 依据字符串计算 label 大小
    CGSize size = [myLabel.text sizeWithFont:myLabel.font constrainedToSize:CGSizeMake(200, 1000) lineBreakMode:NSLineBreakByCharWrapping];
    myLabel.frame = CGRectMake(myLabel.frame.origin.x, myLabel.frame.origin.y, size.width, size.height);
    [self.view addSubview:myLabel];
    for (NSString *fontname in [UIFont familyNames])
    {
        NSLog(@"fontname = %@", fontname);
    }
}
```

# 参考

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)
