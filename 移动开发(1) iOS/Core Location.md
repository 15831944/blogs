# 位置服务

1. Core Locaton: 确定设备的物理位置
2. Map Kit: 创建实时交互的地图来显示设备的任意位置

# 定位技术

1. GPS: A-GPS(Assisted GPS), 使用网络资源来改进 GPS 性能
2. 蜂窝基站ID定位(cell ID Location): 根据设备所属范围内的蜂窝基站位置计算设备的当前位置, 基站覆盖范围广导致误差较大, 需要无线电连接
3. WPS(Wi-Fi Positioning Service, Wi-Fi 定位服务): 使用附近 Wi-Fi 接入点的 MAC 地址, 

# 位置管理器

1. CLLocationManager 类, 位置管理器(location manager)
2. CLLocationManagerDelegate 协议, 位置管理器的委托
3. 精度
4. 距离筛选器
5. 定位服务权限: NSLocationWhenInUseUsageDescription, NSLocationAlwaysUsageDescription, 在属性列表中添加描述
6. 轮询: 

```
CLLocationManager *locationManager = [[CLLocationManager alloc] init];
locationManager.delegate = self;
locationManager.desiredAccuracy = kCLLocationAccuracyBest;
locationManager.distanceFilter = kCLDistanceFilterNone;
[locationManager startUpdatingLocation];
[locationManager stopUpdatingLocation];
```

# 位置管理器委托

1. CLLocation 类, 6个属性, distanceFromLocation 方法

1. 定位服务权限变化
2. 确定当前位置 didUpdateLocation
3. 检测到位置更改
4. 位置管理器遇到错误

# Significant Locaton Update 服务

# 磁力计

# Geocoding 服务
