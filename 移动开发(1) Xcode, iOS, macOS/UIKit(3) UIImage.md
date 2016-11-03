# UIImage

图片的加载

1. 每次都重新加载，耗费加载时间，适合大图片
2. 加载到内存，耗费内存资源，适合频繁使用的小图片

```
UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];
UIImage *image2 = [UIImage imageNamed:@"101"];
```
