# tuya_RGB_Strip
This project is developed using Tuya SDK, which enables you to quickly develop branded apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.
# Information
## Schematic：
<div  align="center">   
<img src="http://github.com/CN-Antonio/tuya_RGB_Strip/tree/main/pic/SCH.PNG" width = "280" height = "175" >
</div>
<!-- ![SCH](http://github.com/CN-Antonio/tuya_RGB_Strip/tree/main/pic/SCH.PNG "Schematic") -->
## PCB：
<div  align="center">   
<img src="http://github.com/CN-Antonio/tuya_RGB_Strip/tree/main/pic/PCB.PNG" width = "280" height = "175" >
</div>
<!-- ![PCB](http://github.com/CN-Antonio/tuya_RGB_Strip/tree/main/pic/PCB.PNG "PCB") -->

# Example
ino 数据类型，直接烧录进UNO，连接模块

# RGB strip
1. Tuya三明治板
2. Arduino UNO
3. WS2812灯带

ps：群里的PCB实现SOC、MCU共用一块板
## 连接
1. 使用Arduino的PD0、PD1脚，连接模组
2. 模组的RX2、TX2用于给模组下载程序（MCU开发不用烧录，已是通用固件），RX1、TX1用于与MCU通讯

## PCB
1. 
2. SOC、MCU模式选择跳线帽
3. 
4. RST按着模组不启动，可以向MCU烧录固件
5. 配网按键
6. 烧录接口，没有授权码也烧录不了，留空
7. 通讯RX、TX注意交替排布