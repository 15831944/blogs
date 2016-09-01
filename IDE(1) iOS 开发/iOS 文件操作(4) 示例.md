# 8. 示例

```
- (NSString *)getHomePath{
    NSString *homePath = NSHomeDirectory();
    NSLog(@"%@", homePath);
    return homePath;
}

- (NSString *)getDocumentPath{
    // 指定要搜索路径名称 限定在沙盒内部搜索 是否展开代表用户主目录的波浪线符号
    NSArray *documentsPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentPath = [documentsPaths lastObject];
    NSLog(@"%@", documentPath);
    return documentPath;
}

- (NSString *)getLibraryPath{
    NSArray *librarysPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString *libraryPath = [librarysPaths firstObject];
    NSLog(@"%@", libraryPath);
    return libraryPath;
}

- (NSString *)getTmpPath{
    NSString *tmpPath = NSTemporaryDirectory();
    NSLog(@"%@", tmpPath);
    return tmpPath;
}

- (void) parsePath{
    NSString *path = @"/Users/wanghuiyong/Library/Developer/CoreSimulator/Devices/3729864D-9A5E-4168-AC0F-22A82CBF5B20/data/Containers/Data/Application/A1BC0179-8111-4D10-A0F1-04C878B2022B/tmp/hehe.jpg";
    NSArray *array = [path pathComponents];
    NSLog(@"%@", array);
    NSString *name = [path lastPathComponent];
    NSLog(@"lastCompoent %@", name);
    NSString *str = [path stringByDeletingLastPathComponent];
    NSLog(@"%@", str);
    NSString *add = [path stringByAppendingPathComponent:@"haha.png"];
    NSLog(@"%@", add);
}

- (void) dataTransform:(NSData *)data{
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSData *dat = [str dataUsingEncoding:NSUTF8StringEncoding];
    UIImage *image = [UIImage imageWithData:data];
    NSData *data2 = UIImagePNGRepresentation(image);
}

- (void) createFolder{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong"];
    NSFileManager *myManger = [NSFileManager defaultManager];
    BOOL rtn = [myManger createDirectoryAtPath:filePath withIntermediateDirectories:YES attributes:nil error:nil];
    if (rtn)
        NSLog(@"%@", filePath);
}

- (void) createFile{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileManager *myManger = [NSFileManager defaultManager];
    BOOL rtn = [myManger createFileAtPath:filePath contents:nil attributes:nil];
}

- (void) writeFile{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSString *content = @"content";
    BOOL rtn = [content writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
}

- (BOOL) fileExist:(NSString *)filePath{
    NSFileManager *myManger = [NSFileManager defaultManager];
    if ([myManger fileExistsAtPath:filePath])
        return YES;
    else
        return NO;
}

- (void) appendFile{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileHandle *myHandle = [NSFileHandle fileHandleForUpdatingAtPath:filePath];
    [myHandle seekToEndOfFile];
    NSString *str = @"append";
    NSData *dat = [str dataUsingEncoding:NSUTF8StringEncoding];
    [myHandle writeData:dat];
    [myHandle closeFile];
}

- (void) deleteFile{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingString:@"/wanghuiyong/note.txt"];
    NSFileManager * myManger = [NSFileManager defaultManager];
    if ([myManger fileExistsAtPath:filePath])
        [myManger removeItemAtPath:filePath error:nil];
}

- (void) writeImage{
    UIImage *myImage = [UIImage imageNamed:@"101"];
    NSData *myData = UIImagePNGRepresentation(myImage);
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingPathComponent:@"/wanghuiyong"];
    NSString *picName = [filePath stringByAppendingPathComponent:@"pic.png"];
    [myData writeToFile:picName atomically:YES];
}

- (UIImage *) readImage{
    NSString *homePath = NSHomeDirectory();
    NSString *filePath = [homePath stringByAppendingPathComponent:@"/wanghuiyong"];
    NSString *picName = [filePath stringByAppendingPathComponent:@"pic.png"];
    NSData *myData = [NSData dataWithContentsOfFile:@"picName"];
    UIImage *image = [UIImage imageWithData:myData];
    return image;
}
```
