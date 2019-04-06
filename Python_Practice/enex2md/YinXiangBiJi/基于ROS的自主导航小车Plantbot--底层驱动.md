# 基于ROS的自主导航小车Plantbot--底层驱动

  * 小车平台

小车采用 **差分驱动** （differential
drive），底座包括两个由直流电机驱动的主动轮以及两个用于支撑的从动轮。三层支撑版由玻纤版设计定做，层间连接件为螺杆，配以螺母，方便调节高度。为了测量轮子转速，选用的直流电机带有正交编码器。考虑到成本，选用观测周围信息的传感器为国产廉价单线激光雷达，有效观测距离为6m，近距离里融合超声波传感器实现避障。

![noteattachment1][0cad922ace3de5d6866897445b701ecc]第二层板上放的是NUC（Next Unit of
Computing），可以视为一个没有显示器的小电脑，优点为体积小、质量轻，可以直接架设到小车平台上 。NUC
安装了Linux系统，在运行时跑ROS，直接处理包括激光雷达在内的传感器数据，负责控制命令接受、速度分解、PID调速以实现对小车的控制以及绘图、定位、导航的任务。同时SLAM的结果需要上位机来显示，NUC通过
**SSH** 与上位机实现通信。

平台的MCU为EK-TM4C123GXL Launchpad，这款单片机采用ARM
Cortex-M4的CPU，因此比Arduino等单片机具有更好地性能，同时其IDE（集成开发环境，Integrated Development
Environment）[energia](http://link.zhihu.com/?target=http%3A//energia.nu/)
的编程语言与Arduino
IDE的相同，并且两者的大部分代码可以兼容。但并非全部，在接MPU6050测量四元数的时候，数据不能持续正常输出。同时Launchpad的IO口输出电压为3.3V，而大部分电路模块引脚的接入电压是5V，因此需要增加3.3V到5V的电压转换模块，增加了电路的复杂性。

后期为了拓展功能，又接了四路红外模块，分别用于防跌和避障，以及蓝牙模块，用来接收由手机App发送来的控制信息，由Arduino作控制器。

  * 底层ROS框架设计

底层ROS的运行状态设计图如下所示：

![noteattachment2][8739a72fa055a3fe988fce95185ab0fb]

底层ROS的设计目标是：

1\.
能够通过编码器的数据（lwheel、rwheel），得到此刻小车两轮的转速（lwheel_vel、rwwheel_vel），矢量合成为小车的运动速度，
并通过旋转矩阵变换为里程计坐标系上的速度，积分迭代得到在x，y轴前进的距离（粗略位姿估计，还会根据激光雷达定位信息纠正odom坐标）；

2\. 能够根据控制命令（cmd_vel）的要求速度，分解为小车两轮的速度
（lwheel_vtarget、rwheel_vtarget），并能通过控制车轮转速达到目标速度 （PID控制实现）；

3\.
获取超声波、红外传感器数据，判读距离障碍物的距离，实现自动避障，并考虑到工厂安全监测，拓展了防火、防雾的功能，可在Arduino板外接火焰或烟雾传感器，当小车在工厂中执行任务时，测到火灾隐患，蜂鸣器自动报警，同时在发送消息（Warning）
，让小车停止任务，持续报警。

  * 控制器与ROS结点

底层设计的一个难点是如何将控制器作为一个节点，即传感器可以由控制器驱动、采集状态，但是如何将采集到的这些数据以message的形式传播到ROS框架中。对于串口连接，ROS提供了专门的功能包：[rosserial](http://link.zhihu.com/?target=http%3A//wiki.ros.org/rosserial/)，以及对于一些单片机的直接应用：[rosserial_arduino](http://link.zhihu.com/?target=http%3A//wiki.ros.org/rosserial_arduino/Tutorials)可以直接在Arduino
IDE中编程，成为结点；[rosserial_tivac](http://link.zhihu.com/?target=http%3A//wiki.ros.org/rosserial_tivac/Tutorials)可以直接用于Launchpad。其它可以作为ROS节点的传感器可以参照[Sensors
supported by
ROS](http://link.zhihu.com/?target=http%3A//wiki.ros.org/Sensors)。此外树莓派可以直接跑ROS，对于其它单片机如STM32，熟悉串口通信编程的话也可以自己写，比如[@夜猫](http://www.zhihu.com/people/a42ed016eb434e594e6ae8da2d475096)
提供的[学习stm32版的ROS小车](http://link.zhihu.com/?target=http%3A//www.ncnynl.com/category/ros-
car-b/)。

下节：基于ROS的自主导航小车Plantbot--自主导航  
\----------------------------------------------------------------------------------------------------------------------------------  

欢迎讨论、交流。

附[系统图](http://link.zhihu.com/?target=https%3A//www.processon.com/view/link/59046226e4b0be5dbd00b263)：

![noteattachment3][9c1e14c45877bcbf1c9d78218380d56c]  

项目由我和同学合作完成，绿色部分为我完成的任务。

更多详情: <https://zhuanlan.zhihu.com/p/26644994>


---
### ATTACHMENTS
[0cad922ace3de5d6866897445b701ecc]: media/基于ROS的自主导航小车Plantbot--底层驱动.png
[基于ROS的自主导航小车Plantbot--底层驱动.png](media/基于ROS的自主导航小车Plantbot--底层驱动.png)
[8739a72fa055a3fe988fce95185ab0fb]: media/基于ROS的自主导航小车Plantbot--底层驱动-2.png
[基于ROS的自主导航小车Plantbot--底层驱动-2.png](media/基于ROS的自主导航小车Plantbot--底层驱动-2.png)
[9c1e14c45877bcbf1c9d78218380d56c]: media/基于ROS的自主导航小车Plantbot--底层驱动-3.png
[基于ROS的自主导航小车Plantbot--底层驱动-3.png](media/基于ROS的自主导航小车Plantbot--底层驱动-3.png)

---
### TAGS
{AI*MR概述}

---
### NOTE ATTRIBUTES
>Created Date: 2017-05-02 09:36:09  
>Last Evernote Update Date: 2017-07-29 04:28:36  
>source: desktop.win  
>source-application: evernote.win32  