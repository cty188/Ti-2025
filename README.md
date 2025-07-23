# STM32H723VGT6 RGB LED 控制项目

## 项目简介
这是一个基于STM32H723VGT6微控制器的RGB LED控制项目，使用FreeRTOS实时操作系统。项目演示了如何控制RGB LED实现7种不同颜色的循环显示。

## 硬件平台
- **微控制器**: STM32H723VGT6
- **开发板**: H7_nano
- **外设**: RGB LED (红、绿、蓝三色LED)

## 功能特性
- RGB LED颜色循环显示
- 支持7种颜色组合：
  - 红色 (R)
  - 绿色 (G) 
  - 蓝色 (B)
  - 黄色 (RG)
  - 青色 (GB)
  - 紫色 (RB)
  - 白色 (RGB)
- 每秒切换一次颜色
- 基于FreeRTOS的多任务架构

## 开发环境
- **IDE**: Keil MDK-ARM
- **HAL库**: STM32H7xx HAL Driver
- **RTOS**: FreeRTOS
- **配置工具**: STM32CubeMX (STM32H723VGT6.ioc)

## 项目结构
```
├── Core/                    # 核心源码
│   ├── Inc/                # 头文件
│   └── Src/                # 源文件
├── Components/             # 自定义组件
│   └── BSP/               # 板级支持包
├── Drivers/               # STM32 HAL驱动
├── MDK-ARM/               # Keil项目文件
├── Middlewares/           # 中间件(FreeRTOS)
└── STM32H723VGT6.ioc     # CubeMX配置文件
```

## 编译和烧录
1. 使用Keil MDK-ARM打开 `MDK-ARM/STM32H723VGT6.uvprojx`
2. 编译项目
3. 连接ST-Link调试器
4. 下载程序到目标板

## 主要代码说明
项目的主循环在 `main.c` 中实现，通过switch语句控制RGB LED的不同颜色组合：
- 使用BSP_GPIO模块控制LED引脚
- 1秒延时实现颜色切换
- 7种颜色循环显示

## 作者
项目开发者：cty188

## 许可证
本项目基于STMicroelectronics的HAL库开发，请参考相关许可证条款。