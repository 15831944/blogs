# Foundation.framework

1. Foundation 框架对于 macOS 和 iOS 两个平台均适用

<figure>
    <img src="images/Foundation.jpg" width="400"/>
</figure>

# 值对象 Value Objects

| Class                  | Subclass       | Subclass        |
| ---------------------- | -------------- | --------------- |
| NSAffineTransform      |                |                 |
| NSCalendar             |                |                 |
| NSCache                |                |                 |
| NSData                 | NSMutableData  | NSPurgeableData |
| NSDate                 | NSCalendarDate |                 |
| NSDateComponents       |                |                 |
| NSDecimalNumberHandler |                |                 |
| NSLocale               |                |                 |
| NSNull                 |                |                 |
| NSTimeZone             |                |                 |
| NSValue                | NSNumber       | NSDecimalNumber |
| NSValueTransformer     |                |                 |

# XML

| Class                                    | Subclass                                            |
| ---------------------------------------- | --------------------------------------------------- |
| NSXMLNode(OS X)                          | NSXMLDocument, NSXMLDTD, NSXMLDTDNode, NSXMLElement |
| NSXMLParser                              |                                                     |

# 字符串 Strings

| Class              | Subclass                           |
| ------------------ | ---------------------------------- |
| NSAttributedString | NSMutableAttributeString           |
| NSCharacterSet     | NSMutableCharacterSet              |
| NSString           | NSMutableString                    |
| NSFormatter        | NSDateFormatter, NSNumberFormatter |
| NSScanner          |                                    |
| NSSortDescriptor   |                                    |

# 集合 Collections

| Class                    | Subclass               | Subclass     |
| ------------------------ | ---------------------- | ------------ |
| NSArray                  | NSMutableArray         |              |
| NSDictionary             | NSMutableDictionary    |              |
| NSEnumerator             | NSDictionaryEnumerator |              |
| NSHashTable(OS X)        |                        |              |
| NSIndexPath              |                        |              |
| NSIndexSet               | NSMutableIndexSet      |              |
| NSMapTable(OS X)         |                        |              |
| NSPointerArray(OS X)     |                        |              |
| NSPointerFunctions(OS X) |                        |              |
| NSSet                    | NSMutableSet           | NSCountedSet |

# 谓词 Predicates

| Class              | Subclass                                   |
| ------------------ | ------------------------------------------ |
| NSExpression       |                                            |
| NSPredicate        | NSComparisonPredicate, NSCompoundPredicate |

# 操作系统服务 Operating-System Services

| Class                |
| -------------------- |
| NSError              |
| NSHost               |
| NSNetService         |
| NSNetServiceBrowser  |
| NSOrthography        |
| NSProcessinfo        |
| NSRunLoop            |
| NSSpellServer(OS X)  |
| NSTextCheckingResult |
| NSTimer              |
| NSUserDefaults       |

## 文件系统 File System

| Class                                    | Subclass                      |
| ---------------------------------------- | ----------------------------- |
| NSBundle                                 |                               |
| NSFileHandle                             |                               |
| NSFileManager                            |                               |
| NSMetadataItem(OS X)                     |                               |
| NSMetadataQuery(OS X)                    |                               |
| NSMetadataQueryAttributeValueTuple(OS X) |                               |
| NSMetadataQueryResultGroup(OS X)         |                               |
| NSStream                                 | NSInputStream, NSOutputStream |

## URL

| Class                       | Subclass            |
| --------------------------- | ------------------- |
| NSCachedURLResponse         |                     |
| NSHTTPCookie                |                     |
| NSHTTPCookieStorage         |                     |
| NSURL                       |                     |
| NSURLAuthorizationChallenge |                     |
| NSURLCache                  |                     |
| NSURLConnection             |                     |
| NSURLCredential             |                     |
| NSURLCredentialStorage      |                     |
| NSURLDownload               |                     |
| NSURLProtectionSpace        |                     |
| NSURLProtocol               |                     |
| NSURLRequest                | NSMutableURLRequest |
| NSURLResponse               | NSHTTPURLResponse   |

## 进程间通信 Interprocess Communication

1. 代表不同的系统端口, 套接字, 名字服务器，用于实现底层的IPC
2. NSPipe 代表一个BSD管道，即一种进程间的单向通讯通道

| Class                  | Subclass                                                               |
| ---------------------- | ---------------------------------------------------------------------- |
| NSPipe                 |                                                                        |
| NSPort                 | NSMachPort, NSMessagePort, NSSocketPort(OS X)                          |
| NSPortMessage(OS X)    |                                                                        |
| NSPortNameServer(OS X) | NSMachBootstrapServer, NSMessagePortNameServer, NSSocketPortNameServer |

## 线程和子任务 Locking/Threading

1. NSThread 类创建多线程的程序
2. 各种锁（lock）类则为彼此竞争的线程在访问进程资源时提供各种控制机制
3. 通过 NSTask，您的程序可以分出一个子进程来执行其它工作或进行进度监控

| Class             | Subclass                                |
| ----------------- | --------------------------------------- |
| NSConditionLock   |                                         |
| NSDistributedLock |                                         |
| NSLock            |                                         |
| NSOperation       | NSBlockOperation, NSInvocationOperation |
| NSOperationQueue  |                                         |
| NSRecursiveLock   |                                         |
| NSTask            |                                         |
| NSThread          |                                         |

# 消息 Notifications

| Class                | Subclass                        |
| -------------------- | ------------------------------- |
| NSNotification       | NSDistributedNotificationCenter |
| NSNotificationCenter |                                 |
| NSNotificationQueue  |                                 |

# 归档和序列化 archiving and Serialization

| Class                                    | Subclass                                                                  |
| ---------------------------------------- | ------------------------------------------------------------------------- |
| NSCoder                                  | NSArchiver, NSKeyedArchiver, NSKeyedUnarchiver, NSPortCoder, NSUnarchiver |
| NSPropertyListSerialization              |                                                                           |

# OC语言服务 Objective-C Language Services

| Class                                    | Subclass                 |
| ---------------------------------------- | ------------------------ |
| NSAssertionHander                        |                          |
| NSAutoreleasePool                        |                          |
| NSClassDescription                       | NSScriptClassDescription |
| NSException                              |                          |
| NSGarbageCollector(OS X)                 |                          |
| NSInvocation                             |                          |
| NSMethodSignature                        |                          |
| NSUndoManager                            |                          |

# 脚本 Scripting

| Class                      |
| -------------------------- |
| NSAppleEventDescriptor     |
| NSAppleEventManager        |
| NSAppleScript              |
| NSPositionalSpecifier      |
| NSScriptCoercionHandler    |
| NSScriptCommand            |
| NSScriptCommandDescription |
| NSScriptExecutionContext   |
| NSScriptObjectSpecifier    |
| NSScriptSuiteRegistry      |
| NSScriptWhoseTest          |

# 分布式对象 Distributed Objects

| Class                  |
| ---------------------- |
| NSConnection           |
| NSDistantObjectRequest |
| NSDistantObject        |
| NSProtocolChecker      |
