# Kinetis Design Studio

1. ���� Eclipse, GNU Compiler Collection (GCC), GNU Debugger (GDB)
2. ֧�� SEGGER J-Link/J-Trace, P&E USB Multilink Universal and CMSIS-DAP debug adapters
3. ʹ�� newlib-nano C runtime library.

1. build
2. debug

# Processor Expert

Processor Expert software enables your design with its knowledge base and helps create powerful applications with a few mouse clicks

doxygen		�ĵ�������
perspective	͸��ͼ
peripheral	��Χ

# Project

�ļ���

1. \.settings:
2. Documentation:
3. Generated_Code: ���е�Դ�ļ���ͷ�ļ����� Processor Expert ����, ��Ӧ�ֶ��޸�
4. Project_Settings
5. SDK:
6. Sources
7. Static_Code

XML �ļ�

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

��ӡ���������
Components -> clockMan1:fsl_clock_manager -> Clock configurations -> System clock -> LPUART1 clock selection -> MCGIRCLK clock
Components -> DbgCs1:fsl_debug_console -> Pins
