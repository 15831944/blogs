# Push 消息推送机制

# ARC 内存管理机制

# main.storyboard

1. main.storyboard 是一个可视化开发工具
2. 在项目设置的 Deployment Info 中指定 main interface 为 main 则表示应用从 main.storyboard 启动, 若要自定义启动窗口，应取消勾选

# main 函数

1. 对于命令行应用，程序总是从 main 函数执行，main.m 文件在项目文件夹中
2. 对于图形界面应用，main.m 文件转移到 Supporting Files 文件夹下，直接调用用户界面的 main 函数

`UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));`
