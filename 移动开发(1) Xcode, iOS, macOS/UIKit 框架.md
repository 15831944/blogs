# UIKit 框架

| Class                           | Subclass |
| ------------------------------- | -------- |
| UIAcceleration                  |          |
| UIAccelerometer                 |          |
| UIAccessibilityElement          |          |
| UIBarItem                       | UIBarButtonItem, UITabBarItem |
| UIBezierPath                    |          |
| ** UIColor **                   |          |
| UIDevice                        |          |
| UIDocumentInteractionController |          |
| UIEvent                         |          |
| UIFont                          |          |
| UIGestureRecognizer             | 见下      |
| ** UIImage **                   |          |
| UILocalizedIndexedCollation     |          |
| UILocalNotification             |          |
| UIMenuController                |          |
| UIMenuItem                      |          |
| UINavigationItem                |          |
| UINib                           |          |
| UIPasteboard                    |          |
| UIPopoverController             |          |
| UIPrintFormatter                | 见下      |
| UIPrintInfo                     |          |
| UIPrintInteractionController    |          |
| UIPrintPageRenderer             |          |
| UIPrintPager                    |          |
| ** UIResponder **               | UIApplication, ** UIView **, ** UIViewController ** |
| ** UIScreen **                  |          |
| UIScreenMode                    |          |
| UISearchDisplayController       |          |
| UITextChecker                   |          |
| UITextInputStringTokenizer      |          |
| UITextPosition                  |          |
| UITextRange                     |          |
| UITouch                         |          |

UIGestureRecognizer 的子类有:

1. UILongPressGestureRecognizer
2. UIPanGestureRecognizer
3. UIPinchGestureRecognizer
4. UIRotationGestureRecognizer
5. UISwipeGestureRecognizer
6. UITapGestureRecognizer

UIPrintFormatter 的子类有:

1. UISimpleTextPrintFormatter
2. UIMarkupTextPrintFormatter
3. UIViewPrintFormatter

# UIView

| Class                   | Subclass |
| ----------------------- | -------- |
| ** UIWindow **          |          |
| UILabel                 |          |
| UIPickerView            |          |
| UIProgressView          |          |
| UIActivityIndicatorView |          |
| UIImageView             |          |
| UITabBar                |          |
| UIToolBar               |          |
| UINavigationBar         |          |
| UITableViewCell         |          |
| UIActionSheet           |          |
| UIAlertView             |          |
| UIScrollView            | UITableView, UITextView |
| UISearchBar             |          |
| UIWebView               |          |
| UIControl               | UIButton, UIDatePicker, UIPageControl, UISegmentedControl, UITextField, UISlider, UISwitch |

# 参考

教程

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)

博客

1. [OC学习之UIKit的类层次结构图](http://blog.csdn.net/heyddo/article/details/9631919)
2. [IOS UIKIT框架类之窗口和视图架构介绍！](http://blog.csdn.net/qq_31082775/article/details/50424454)
3. [UIWindow 与 UIView 深层解析](http://blog.csdn.net/gf771115/article/details/7761904)
