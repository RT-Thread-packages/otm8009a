# OTM80009A

## 简介

otm8009a 软件包提供了使用液晶显示的基本功能，并且本软件包已经对接到了 LCD 接口框架，通过 LCD 接口框架，开发者可以快速的将此液晶芯片驱动起来。
## 支持情况

| 包含设备           | 液晶芯片 |  
| ----------------     | -------- | 
| **通讯接口**      |          |      
| mipi 接口             | √        | 
      

## 使用说明

### 依赖

- RT-Thread 4.0.0+
- LCD 接口组件
- LCD 接口驱动：otm8009a 设备使用 LCD 接口设备进行数据通讯，需要系统 LCD 接口驱动支持；

### 获取软件包

使用 otm8009a 软件包需要在 RT-Thread 的包管理中选中它，具体路径如下：

```
RT-Thread online packages  --->
  peripheral libraries and drivers  --->
    lcd drivers  --->
      otm8009a: lcd ic otm8009a for rt-thread
              Version (latest)  --->
```
**Version**：软件包版本选择

### 使用软件包

otm8009a 软件包初始化函数如下所示：

```c
rt_hw_otm8009a_init(rt_uint16_t width, rt_uint16_t height, void *user_data)
```

该函数需要由用户调用，函数主要完成的功能有，

- 设备配置和初始化（根据传入的配置信息，配置接口设备）；
- 注册相应的 LCD 设备，完成 otm8009a 设备的注册；

#### 初始化示例

```.c
#define  LCD_WIDTH     800
#define  LCD_HEIGHT    480
#define  RST_PIN       119  

int rt_hw_otm8009a_port(void)
{ 
    rt_base_t rst_pin = RST_PIN;
	
    rt_hw_otm8009a_init(LCD_WIDTH, LCD_HEIGHT, &rst_pin);

    return 0;
}
INIT_ENV_EXPORT(rt_hw_otm8009a_port);
```

## 注意事项

暂无

## 联系人信息

维护人:

- [tyustli](https://github.com/tyustli) 

- 主页：<https://github.com/RT-Thread-packages/otm8009a>