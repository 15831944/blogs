# 6. NSData 类

NSData 类用于包装数据，以便在网络数据通信时进行读写

NSData 类的数据为二进制形式，这种形式屏蔽了数据之间的差异，便于进行读取

文本，音频，图像都可以使用 NSData 进行处理

## 1. NSString 对象和 NSData 数据之间的转换

`NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];`

`NSData *dat = [str dataUsingEncoding:NSUTF8StringEncoding];`

## 2. UIImage 对象和 NSData 数据之间的转换

`UIImage *image = [UIImage imageWithData:data];`

`NSData *data = UIImagePNGRepresentation(image);`

注意 `UIImagePNGRepresentation` 是普通的 C 函数

# 9. 参考

[iOS基础教程-文件操作](http://www.imooc.com/learn/655)
