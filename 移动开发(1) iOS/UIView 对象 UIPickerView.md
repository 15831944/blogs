# 选取器

1. 选取器是带有可旋转刻度盘的控件, 可以配置为一个或多个刻度盘(或组件, component), 用于显示文本和图像

日期选取器(Date Picker): 本身维护着日期数据, 无须委托和数据源
选取器视图(Picker View): 选取器本身不保存任何数据, 而是向它的控制器(数据源和委托)请求数据, 使用关联检查器进行关联委托和数据源视图控制器

# 选取器委托和数据源

1. 每个组件可具有独立的数据列表
2. 日期选取器不需要配置委托和数据源
3. 选取器将一些工作分配给它的委托, 委托可以确定为选取器的每个滚轮的每一行绘制的内容, 选取器从委托获取数据
4. 数据源: 选取器通过数据源获知滚轮数量和每个滚轮中的行数, 在预先指定的时刻调用委托方法, 数据源是控制器的一部分, 而不是模型的一部分, 模型用于存储数据, 虽然作为数据源的控制器可以存储数据(例如硬编码的数组), 但实际用于从模型(例如属性列表, 文件, URL 载入, 动态组合或计算)中检索数据, 并传递给选取器, 遵循 IPickerViewDataSource 协议的方法必须实现, 在视图被激活时被执行
5. 委托: 委托和数据源可以是同一对象, 一般是包含选取器视图的视图控制器, UIViewController 的子类, 遵循 IPickerViewDelegate 协议, 方法至少实现一个, 在滚轮变化时被执行
6. 遵循对应协议的控制器即是该选取器的委托和数据源

```
func numberOfComponents(in pickerView: UIPickerView) -> Int {}
func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {}

func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {}
```
