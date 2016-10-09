# 1. UIImage

UIImage 是图片对象

## 图片的加载

每次都重新加载，耗费加载时间，适合大图片

`UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];`

加载到内存，耗费内存资源，适合频繁使用的小图片

`UIImage *image2 = [UIImage imageNamed:@"101"];`

# 2. UIImageView

UIImageView 是图片的载体

图片需要载体才能显示在屏幕上

载体可以是 UIImageView，可以是 Button 等

载体控制屏幕上显示的图片的大小，默认的内容模式是拉伸

| 内容模式 | 含义 |
| - | - |
| UIViewContentModeScaleToFill | 拉伸(默认) |
| UIViewContentModeCenter | 居中 |
| UIViewContentModeScaleAspectFit | 按短边填充 |
| UIViewContentModeScaleAspectFill | 按长边填充 |

# 3. 序列图

将图片对象存入数组，进行动画播放

# 4. 示例

```
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // 工程路径
    NSString *projectPath = [[NSBundle mainBundle] resourcePath];
    // 图片路径
    NSString *imagePath = [NSString stringWithFormat:@"%@/101.png", projectPath];
    // 加载图片(每次都重新加载)
    UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];
    // 加载图片(加载到内存)
    UIImage *image2 = [UIImage imageNamed:@"101"];
    // 图片的载体 ImageView
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image2];
    imageView.backgroundColor = [UIColor redColor];
    
    imageView.contentMode = UIViewContentModeCenter;            // 居中
    imageView.contentMode = UIViewContentModeScaleAspectFit;    // 按短边填充
    imageView.contentMode = UIViewContentModeScaleAspectFill;   // 按长边填充
    imageView.contentMode = UIViewContentModeScaleToFill;       // 拉伸(默认)
    
    imageView.frame = CGRectMake(10, 100, image2.size.width / 3, image2.size.height / 3);
    [self.view addSubview:imageView];
    
    // 序列图
    NSMutableArray *imageArray = [[NSMutableArray alloc] init];
    // 获取每张图片并存入数组
    for (int i = 0; i < 10; i++)
    {
        UIImage *image = [UIImage imageNamed:[NSString stringWithFormat:@"%d.png", i]];
        [imageArray addObject:image];
    }
    // 初始化载体
    UIImageView *imageArrayView = [[UIImageView alloc] init];
    imageArrayView.frame = CGRectMake(10, 10, 100, 100);
    [self.view addSubview:imageArrayView];
    // 指定动画图片数组
    imageArrayView.animationImages = imageArray;
    // 播放周期
    imageArrayView.animationDuration = 2;
    // 播放次数
    imageArrayView.animationRepeatCount = 3;
    // 开始播放
    [imageArrayView startAnimating];
    // 停止播放
    [imageArrayView stopAnimating];
}
```

# 参考

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)
