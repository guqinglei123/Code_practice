# 如何评价百度Apollo 2.0开放的代码？ - 知乎

[](https://www.zhihu.com/)

[首页](https://www.zhihu.com/)[发现](https://www.zhihu.com/explore)[话题](https://www.zhihu.com/topic)

登录加入知乎

# 如何评价百度Apollo 2.0开放的代码？

关注问题

写回答

[互联网](https://www.zhihu.com/topic/19550517)

[百度](https://www.zhihu.com/topic/19551460)

[汽车](https://www.zhihu.com/topic/19551915)

[自动驾驶](https://www.zhihu.com/topic/19635352)

[百度无人驾驶车](https://www.zhihu.com/topic/20047063)

# 如何评价百度Apollo 2.0开放的代码？

百度在12月30日09:00左右开放了Apollo 2.0的代码，新开放的模块包括Security，Camera，Radar和Black
box。此次…显示全部

关注者

 **551**

被浏览

 **20,282**

关注问题

写回答

​

1 条评论

​

分享

​

邀请回答

​

[查看全部 5 个回答](https://www.zhihu.com/question/264834593)

[
![noteattachment1][2cb830116b11050f0ebc03517cdd06d8]](https://www.zhihu.com/people/xinhe-
sun)

[xinhe sun](https://www.zhihu.com/people/xinhe-sun)

126 人赞同了该回答

解析一下Apollo 2.0吧，边看文档边看代码同时记录整理，所以会比较慢，得分好几次才能写完～

先说 **运行环境** ：硬件及操作系统。

![noteattachment2][22ca147522dc298e127838496066b1f6]

## 硬件：

 **计算中心：** 就是整套系统大脑了，使用的是Neousys
Nuvo-6108GC，这是一款性能强大的X86解构工业控制计算机，强大到什么程度呢？支持至强E3和I7，支持GTX1080显卡，玩游戏的朋友都知道这款显卡，强大的性能我就不多说了，所以比较适合用来做自动驾驶。

 **CAN通讯卡** ，用来和汽车进行通讯以控制汽车的加速、制动、档位、方向等信号，使用的是ESD CAN-
PCIe/402-B4，CAN卡直接插在主机内。

 **GPS和IMU：** 定位系统和惯性制导，当然就是用来进行GPS定位和惯性定位，使用的是NovAtel SPAN-IGM-A1或者NovAtel
SPAN® ProPak6™ and NovAtel IMU-IGM-A1，通过串口连接主机。

 **激光雷达：** 扫描距离达到120米，水平360度扫描，垂直FOV26.9度，型号为Velodyne HDL-64E S3，通过以太网连接计算中心。

 **摄像头：** 用于视觉，Leopard Imaging LI-USB30-AR023ZWDR with USB 3.0 case，通过USB连接主机。

 **毫米波雷达：** 用于探测前方，安装在车辆前端，为大陆集团的ARS408-21，连接至CAN卡。

除去以上这些，还需要鼠标键盘显示器，当然就是平常用的那种。

## 软件：

 **操作系统：** Ubuntu Linux 推荐版本14.04，看到这个操作系统，我非常兴奋，因为我曾经在这个操作系统下Coding4年。

然后安装Apollo 内核和CAN卡、显卡驱动。

下图是Apollo运行图。

![noteattachment3][081ec4f701ea59855a7d9ba4b067b43d]

 **整个软件包含如下模块**

![noteattachment4][7d069e96eb1e29f55c754aa3aec9654a]

calibration：校准模块，使用前必须对系统进行校准和标定，包括激光雷达与摄像头、毫米波雷达与摄像头等。所谓校准就是要对齐激光雷达、摄像头以及毫米波雷达获得的信息，我们知道激光雷达可以获得详细的3D信息，但是不能获得颜色信息，摄像头可以获得颜色信息，但是无法获得深度等3D信息，毫米波雷达不能获得颜色信息，但是可以获得3D信息，三者获得的信息对齐后，就可以同时获得实际环境中的3D信息和颜色信息。下图就是对齐后的激光雷达和摄像头画面，下下图为对齐后的毫米波雷达和激光雷达画面。

![noteattachment5][8fb9dd8ec1ae8e07b93ca2343e37f99e]

![noteattachment6][5b88e51afa9ec38ebb18271fe6dd06e2]

canbus：管理CAN卡和CAN通讯，把接受到的信号传递给相应模块，同时将Control模块的命令下发到车辆。

common：其他模块之外的代码都在这里

control：主控制模块 ，基于车道规划和车辆当前状态，输出转向、加速和制动控制信号到CAN卡

data Data: 收集、存储、处理收集到的各种数据。

dreamview：这是一个Web应用，可以帮助用户随时掌握系统的输出数据，包括车道、位置、车身等情况。

drivers：此模块包含CAN卡、激光雷达、毫米波雷达、GPS以及摄像头等相关设备的驱动程序

e2e：end to end，端到端深度学习，这部分在代码中需要另外下载，学习的

数据主要来源于传感器的原始数据，包括图像、激光雷达、雷达等。end-to-end输入以图像为主。 输出是车辆的控制决策指令，如方向盘角度、加速、刹车。
连接输入输出的是深度神经网络，即通过神经网络直接生成车辆控制指令对车辆进行横向控制和纵向控制，中间没有人工参与的逻辑程序。横向控制，主要是指通过方向盘控制车身横向移动，即方向盘角度。纵向控制，是指通过油门和刹车控制车身纵向的移动，即加速、刹车等。横向模型的输出没有采用方向盘角度，而是使用要行驶的曲率（即拐弯半径的倒数）。

elo：百度的车辆自身定位部分，结构如下。

![noteattachment7][0c26553f20b4ee095f86a6e5409814f3]

这部分的代码也是另外下载。前向的摄像头会采集车道数据以实现更精确的定位，输出的位置信息包括车辆的x y z坐标，还有就是在百度高精度地图中的ID。

localization：车辆定位服务，包含两种定位方式，一种是GPS和IMU，另一种是多传感器融合。输出位置估算结构体。

map：地图

monitor：此模块用于监测硬件状态及整个系统的健康程度。

perception:此模块用于障碍物感知和红绿灯等交通信号的感知，主要依靠摄像头数据以及激光雷达和毫米波雷达的数据，当然还有高精度地图，输出3D的障碍物信息，包括方向、速度和障碍物类型，当然还有红绿灯等交通信号。模块可以将障碍物标注为机动车、非机动车、行人和其他，使用的是激光点云算法。

planning：根据车辆位置和车辆状态、地图、障碍物、导航信息等计算具体的车道。规划车道有两种方式，一种是提前把轨迹存入程序，然后根据车辆状态和位置提取轨迹另外一种是实时计算。

prediction：根据障碍物的位置、航向、速度、加速度计算障碍物的可能轨迹。

routing：路径规划，根据地图和起点终点位置计算出具体的导航信息。

third_party_perception：第三方感知

tools：工具

 **根据这些模块，可以大概看出整体流程了：**

首先，用户输入目的地， **routing** 模块就可以根据终点位置计算出具体的导航信息。激光雷达、毫米波雷达和摄像头拍摄到的数据配合高精度地图由
**percepting** 模块计算出3D的障碍物信息并识别交通标志及交通信号，这些数据进入 **perdiction**
模块，计算出障碍物的可能轨迹，如此就可以结合以上信息并根据车辆定位模块 **localizationg**
提供的车辆位置由planning模块得到车辆应该走的具体车道。

得到车道后车辆 **control** 模块结合车辆的当前状态计算加速、刹车和方向的操作信号，此信号进入CAN卡后输出到车内，如此实现了车辆的自动驾驶。

在整个流程中， **monitor** 模块会及时监测硬件及系统的健康状况，出现问题肯定就会中止驾驶过程。对于驾驶中的信息，用户可以通过web应用
**dreamview** 来查看，下图就是实际驾驶过程中的dreamview界面。

![noteattachment8][6b871b742fa5637d8f223d8ad9d0f794]

说说写到这里的一些小想法吧。

这套软件，很明显只是一个框架，而且开放的也是整套系统中的部分代码，并没有多少核心重要的东西在里面，也是非常初级的智能驾驶，顶多就是用来测试，我倾向于认为百度不过是渲染下气氛，更多的是传播上的考虑，如果你指望这些代码搞定一辆实用的无人驾驶车，几乎是不可能的。

对于百度来说，他很可能是做出一个姿态来吸引更多厂商的合作和尝试，当然不可谓不好，但是也并没多像大家想的那么美好。

对于厂商来说，如果使用了百度这一套，百度基本上就可以和这个入口捆绑在一起了，主机厂也和百度绑在一起了，无人驾驶可是未来出行的核心，各大互联网巨头肯定都要全力抢夺，百度走的够快啊！

以上还有一些需要细化补充的地方，有空继续写...

[编辑于 昨天 15:50](https://www.zhihu.com/question/264834593/answer/286118234)

126

​

14 条评论

​

分享

​

收藏​

感谢收起

#### 更多回答

[
![noteattachment9][218f0c47beacb12de8fbf61a5855a2c6]](https://www.zhihu.com/people/wang-
slam)

[王小迪SLAM](https://www.zhihu.com/people/wang-slam)

爱生活，爱Coding！挣扎在科研一线的PhD

谢邀。我比较关心其中的高精度地图，定位和障碍物检测模块。目前来看定位依赖RTK-
GPS，不能满足城区无人驾驶的要求，比较危险；障碍物检测模块可圈可点，但我对CNN在其中的作用表示怀疑：除了提供属性信息，CNN对障碍物的检测性能是否有真正意义上的提高？

[编辑于 2018-01-01](https://www.zhihu.com/question/264834593/answer/286825891)

0

​

5 条评论

​

分享

​

收藏​

感谢

[
![noteattachment10][612042811425957bef56f3ce665caeb0]](https://www.zhihu.com/people/yiiwood)

[机智子](https://www.zhihu.com/people/yiiwood)

自动驾驶机器学习

5 人赞同了该回答

虽然理解不一定全面，但还是答一下，免得有人被误导。  
1.perception里面加入了light的检测识别，采用两个分别为25mm和6mm的镜头，根据地图和定位reprojection获取prior区域再检测识别，为了避免遮挡光照等导致的不确定，加入了sequence
state滤波，根据个人经验，总体上效果会不错。  
2.localization加入msf，可以利用altitude和intensity信息进行定位，流程是先gnss/rtk初始化，然后采取monto
carlo定位方法，分别利用odomtry和measurement进行更新，输出定位信息及置信度，虽然没有提供核心代码，但绝对值得试用和对比。  
3.prediction模块加入了rnn做预测，预测未来是最难的，而且目标之间可能存在交互更增加了难度，传统方法做这个会遇到两个难题，一个是特征的选取及特征精度的影响，另一个就是目标交互引起的预测变化，rnn用这里对第一个问题提出了不错的方案，会有更好的适用性，能同时解决一二两个问题的我们也在开发。

未完待续

[编辑于 2018-01-01](https://www.zhihu.com/question/264834593/answer/286840015)

5

​

添加评论

​

分享

​

收藏​

感谢

[查看全部 5 个回答](https://www.zhihu.com/question/264834593)

[
![noteattachment11][7caef4dd36377ef2fb2a1ea9bcb370f7]下载知乎客户端与世界分享知识、经验和见解](http://zhi.hu/BDXoI)

关于作者

[
![noteattachment12][b3e5f2c2e2127efe3e2e29ff802a7c85]](https://www.zhihu.com/people/xinhe-
sun)

[xinhe sun](https://www.zhihu.com/people/xinhe-sun)

[回答 **227**](https://www.zhihu.com/people/xinhe-sun/answers)[ 文章
**85**](https://www.zhihu.com/people/xinhe-sun/posts)[ 关注者
**4,797**](https://www.zhihu.com/people/xinhe-sun/followers)

​

关注他

发私信

被收藏 70 次

[程序算法](https://www.zhihu.com/collection/21742031 "程序算法")

[口贝力](https://www.zhihu.com/people/wei-shou-xun) 创建

1,588 人关注

[关于ML, DL和NLP](https://www.zhihu.com/collection/63628972 "关于ML, DL和NLP")

[vanja](https://www.zhihu.com/people/foolooo) 创建

460 人关注

[dl](https://www.zhihu.com/collection/44492201 "dl")

[杨珣](https://www.zhihu.com/people/yang-lu-59-39) 创建

4 人关注

[认知计算](https://www.zhihu.com/collection/85570617 "认知计算")

[Swizard](https://www.zhihu.com/people/swizard) 创建

4 人关注

[乱七八糟](https://www.zhihu.com/collection/45556567 "乱七八糟")

[旅行的国王](https://www.zhihu.com/people/sun-peng-79-80) 创建

1 人关注

相关问题

[如何评价百度免费开放无人驾驶能力的 Apollo 计划?](https://www.zhihu.com/question/58778536) 98 个回答

[如何看待最近谷歌放弃研发自动驾驶辅助系统？](https://www.zhihu.com/question/68106366) 12 个回答

[国内从事 ADAS 和自动驾驶的相关（创业）公司有哪些？](https://www.zhihu.com/question/39375325) 34 个回答

[高精地图对自动驾驶来说有多重要？在自动驾驶上和一般的导航地图有什么区别？](https://www.zhihu.com/question/54379931)
29 个回答

[Google 自动驾驶/无人驾驶车用到哪些算法？](https://www.zhihu.com/question/24803906) 4 个回答

相关推荐

[ ![noteattachment13][035cd7ad99230ada781a4d43ac23c2f5]美国名校经济学思维课兰德尔·巴特利特共 24
节课试听](https://www.zhihu.com/remix/albums/921103406666493952)[
![noteattachment14][fcc3cdcbfde0ff2a6d6f67f4ee3aac4b]业余时间赚钱的6种策略foruok 16005
人参与](https://www.zhihu.com/lives/870704471959822336)[
![noteattachment15][4b162289a2343ba070e932a90054aab1]智能化未来：无人驾驶技术将如何改变我们的生活504
人读过​阅读](https://www.zhihu.com/publications/book/119556442)

[刘看山](https://liukanshan.zhihu.com/)[知乎指南](https://www.zhihu.com/question/19581624)[知乎协议](https://www.zhihu.com/terms)[应用](https://www.zhihu.com/app)[工作](https://www.zhihu.com/careers)  
[侵权举报](https://zhuanlan.zhihu.com/p/28561671)[网上有害信息举报专区](http://www.12377.cn/)  
违法和不良信息举报：010-82716601  
[儿童色情信息举报专区](https://www.zhihu.com/jubao)  
[联系我们](https://www.zhihu.com/contact) © 2018 知乎


---
### ATTACHMENTS
[035cd7ad99230ada781a4d43ac23c2f5]: media/如何评价百度Apollo_2.0开放的代码？_-_知乎
[如何评价百度Apollo_2.0开放的代码？_-_知乎](media/如何评价百度Apollo_2.0开放的代码？_-_知乎)
[081ec4f701ea59855a7d9ba4b067b43d]: media/如何评价百度Apollo_2-2.0开放的代码？_-_知乎
[如何评价百度Apollo_2-2.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-2.0开放的代码？_-_知乎)
[0c26553f20b4ee095f86a6e5409814f3]: media/如何评价百度Apollo_2-3.0开放的代码？_-_知乎
[如何评价百度Apollo_2-3.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-3.0开放的代码？_-_知乎)
[218f0c47beacb12de8fbf61a5855a2c6]: media/如何评价百度Apollo_2-4.0开放的代码？_-_知乎
[如何评价百度Apollo_2-4.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-4.0开放的代码？_-_知乎)
[22ca147522dc298e127838496066b1f6]: media/如何评价百度Apollo_2-5.0开放的代码？_-_知乎
[如何评价百度Apollo_2-5.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-5.0开放的代码？_-_知乎)
[2cb830116b11050f0ebc03517cdd06d8]: media/如何评价百度Apollo_2-6.0开放的代码？_-_知乎
[如何评价百度Apollo_2-6.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-6.0开放的代码？_-_知乎)
[4b162289a2343ba070e932a90054aab1]: media/如何评价百度Apollo_2-7.0开放的代码？_-_知乎
[如何评价百度Apollo_2-7.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-7.0开放的代码？_-_知乎)
[5b88e51afa9ec38ebb18271fe6dd06e2]: media/如何评价百度Apollo_2-8.0开放的代码？_-_知乎
[如何评价百度Apollo_2-8.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-8.0开放的代码？_-_知乎)
[612042811425957bef56f3ce665caeb0]: media/如何评价百度Apollo_2-9.0开放的代码？_-_知乎
[如何评价百度Apollo_2-9.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-9.0开放的代码？_-_知乎)
[6b871b742fa5637d8f223d8ad9d0f794]: media/如何评价百度Apollo_2-10.0开放的代码？_-_知乎
[如何评价百度Apollo_2-10.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-10.0开放的代码？_-_知乎)
[7caef4dd36377ef2fb2a1ea9bcb370f7]: media/如何评价百度Apollo_2-11.0开放的代码？_-_知乎
[如何评价百度Apollo_2-11.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-11.0开放的代码？_-_知乎)
[7d069e96eb1e29f55c754aa3aec9654a]: media/如何评价百度Apollo_2-12.0开放的代码？_-_知乎
[如何评价百度Apollo_2-12.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-12.0开放的代码？_-_知乎)
[8fb9dd8ec1ae8e07b93ca2343e37f99e]: media/如何评价百度Apollo_2-13.0开放的代码？_-_知乎
[如何评价百度Apollo_2-13.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-13.0开放的代码？_-_知乎)
[b3e5f2c2e2127efe3e2e29ff802a7c85]: media/如何评价百度Apollo_2-14.0开放的代码？_-_知乎
[如何评价百度Apollo_2-14.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-14.0开放的代码？_-_知乎)
[fcc3cdcbfde0ff2a6d6f67f4ee3aac4b]: media/如何评价百度Apollo_2-15.0开放的代码？_-_知乎
[如何评价百度Apollo_2-15.0开放的代码？_-_知乎](media/如何评价百度Apollo_2-15.0开放的代码？_-_知乎)

---
### TAGS
{AI*AG概述}

---
### NOTE ATTRIBUTES
>Created Date: 2018-01-08 16:10:42  
>Last Evernote Update Date: 2019-04-06 02:07:15  
>source: web.clip  
>source-url: https://www.zhihu.com/question/264834593/answer/286118234?utm_source=com.evernote  
>source-url: &  
>source-url: utm_medium=social  
>source-application: ios.clipper.evernote  