# 软件组件

## OSA

FreeRTOS

Interrupt Manager

DMA Controller

## OS Task

## Debug Console

LPUART0

# Clock Manager




# 硬件模块组件

## System Mode Controller (SMC)

## Low-Leakage Wakeup Unit (LLWU)

## Power Management Controller (PMC)

Power modes

Run
Wait
Stop

WFI(wait for interrupt)
WFE(wait for event)

## Low-Power Timer (LPTMR)

1. real-time interrupt 模式， 包含 2N prescaler
2. pulse accumulator 模式，包含 glitch filter

在装置中用于，半双工RF通信, 状态切换

lptimer0用于半双工通信状态切换
从5.0几ms改成4.9几ms

1s有4个时序，RTC触发一个，Lptimer触发3个

## System Integration Module (SIM)

COP Watchdog, computer operating properly

## Timer/PWM Module (TPM)

## Analog-to-Digital Converter (ADC)

chn4 太能能电压
chn23 电池电压

6000Hz

## Real Time Clock (RTC)





# 硬件接口组件

## General-Purpose Input/Output (GPIO)

GPIOB Pin1  Output PTB1

GPIOC Pin1  Input  PTC1
GPIOC Pin2  Input  PTC2  RTCPPS RTC INT 产生 8025T 中断?
GPIOC Pin11 Input  PTC11 GPSPPS Second pulse 产生 GPS 秒中断?

GPIOD Pin4  Output PTD4  flash_cs
GPIOD Pin6  Input  PTD6  SX1212 IRQ1
GPIOD Pin7  Input  PTD7  SX1212 IRQ0 产生数据发送接收成功中断?

GPIOE Pin0  Output PTE0  CS_CFG SX1212 CONFIG
GPIOE Pin22 Output PTE22 Abnormal_LED
GPIOE Pin23 Output PTE23 Normal_LED
GPIOE Pin24 Output PTE24 CHARGE_LED
GPIOE Pin25 Output PTE25 COMMUNICATION_LED

output pin 定义，其中4个 LED 是点灯

1. Abnormal_LED
2. Normal_LED
3. CS_CFG
4. COM_LED
5. CHARGE_LED
6. flash_cs

input pin 定义

1. PORTC, 外部 RTC GPS 秒脉冲
2. PORTD, 连接射频芯片, 每个数据窗数据接收成功时产生高电平

## Serial Peripheral Interface (SPI)

1. SPI0 master DMA mode

MISO PTE19 Input pin SX1212OUT
MOSI PTE18 Output pin SX1212IN
SCK  PTE17 Clock pin SX1212 SCK
SS   PTE16 Slave select pin 和 PTE0 组成与门进行 SX1212 DATA

2. SPI1 master DMA mode

MISO PTB17 N25Q064 DQ1
MOSI PTB16 N25Q064 DQ0
SCK  PTD5  N25Q064 C
SS   N.A.

Flash SPI1 CS 没有用 SPI1 的 SS, 而是用 PTC7 和 PTD4

SX1212 RF 射频芯片

## Inter-Integrated Circuit (I2C)

8025T RTC

## Low Power Universal asynchronous receiver/transmitter (LPUART)

LPUART0用于串口101

## UART

UART2
