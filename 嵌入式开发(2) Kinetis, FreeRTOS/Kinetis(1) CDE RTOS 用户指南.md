1. CDE 允许创建 RTOS 组件, 是硬件抽象层(HAL, 由 PE 定义)的必要组成部分
2. 在 HAL 架构中, RTOS 组件向 HAL 组件(逻辑设备驱动程序, LDDs)提供关于如何插入针对操作系统的调用到它的生成代码中的信息, 以促进 PE 到特定操作系统的整合

# RTOS component

1. RTOS 是 PE 组件, 能够向 LDD 提供关于如何创建 OS-specific 调用的信息
2. RTOS 组件并不试图实现方法或事件, 而是提供基础的属性和 API 来和 Freescale 的 HAL 架构相兼容

# LDD component

1. LDD 组件是 PE 组件, 是 Freescale 的 HAL 架构的一部分
2. LDD 组件实现了对特定设备的实际的硬件访问, 并能生成 OS-specific 的代码, 在没有 RTOS 组件的情况下, LDD 生成裸机设备驱动器的代码

PE 为特定的硬件生成设备驱动代码, 如果存在第二个相同类型设备的模块, 它为第二个设备生成另一组函数, 这个模块不适用于操作系统, 因为浪费了内存

1. shared LDD: 使用同一组函数, 即使系统中存在同类型的多个设备, 除了 Init() 函数
2. unique LDD: 为每个硬件模块生成一整套函数

# HAL

1. HAL 是一个软件层, 视图将操作系统从硬件独立出来, 主要提供两段代码: CPU 和平台初始化, 设备驱动程序, 均由 PE 引擎生成, 当 LDD 和它相应的 RTOS 组件在 PE 项目中整合的时候

1. LDD, Logical Device Driver Component
2. PDD, Physical Device Driver Component

# 在 PE 项目中使用 RTOS 组件

1. 一旦 RTOS 组件使用正确的值设置, 就可用于常规的 PE 项目, PE 项目应该使用该 RTOS 组件和一个或多个对应硬件架构的 LDD 组件
2. 项目还应该包含带有 HAL 适配层的确定的 RTOS 来讲所有的代码链接到一起
