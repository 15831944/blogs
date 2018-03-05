# Kinetis Design Studio

1. 包含 Eclipse, GNU Compiler Collection (GCC), GNU Debugger (GDB)
2. 支持 SEGGER J-Link/J-Trace, P&E USB Multilink Universal and CMSIS-DAP debug adapters
3. 使用 newlib-nano C runtime library.

1. build
2. debug

# Processor Expert

Processor Expert software enables your design with its knowledge base and helps create powerful applications with a few mouse clicks

doxygen		文档生成器
perspective	透视图
peripheral	外围

# Project

文件夹

1. \.settings:
2. Documentation:
3. Generated_Code: 其中的源文件和头文件均由 Processor Expert 生成, 不应手动修改
4. Project_Settings
5. SDK:
6. Sources
7. Static_Code

XML 文件

1. .project
2. .cproject
3. .cwGeneratedFileSetLog
4. ProcessorExpert.pe
5. ProjectInfo.xml
6. g_c
7. g_x

```
.\Generated_Code\PE_low_level_init.h
.\Static_Code\System\PE_low_level_init.c
.\SDK\platform\osa\src\fsl_os_abstraction_free_rtos.c
```

Components Library

打印输出需配置
Components -> clockMan1:fsl_clock_manager -> Clock configurations -> System clock -> LPUART1 clock selection -> MCGIRCLK clock
Components -> DbgCs1:fsl_debug_console -> Pins
