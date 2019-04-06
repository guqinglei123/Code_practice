# 如何设计一款基于ROS的移动机器人？——李金榜经验谈 | ExBot易科机器人实验室

_[](http://blog.exbot.net/ "返回首页")_

  * [BOOKS](http://books.exbot.net/)
  * [WIKI](http://wiki.exbot.net/)
  * [星火计划](http://blog.exbot.net/spark/)
  * [链接](http://blog.exbot.net/link)
  * [关于我](http://blog.exbot.net/about)

[
![noteattachment1][06e1fec4a87eca3142d54d09844c629f]](http://shang.qq.com/wpa/qunwpa?idkey=baf316ad163a102df7e8cebec205c58c65b9d134242f314720f3b317ccb9989a)
[
![noteattachment2][06e1fec4a87eca3142d54d09844c629f]](http://shang.qq.com/wpa/qunwpa?idkey=5c53f0a788dcb09da034ee3338847aa6d0a1303bb8f572b154263273d2db4a82)
[
![noteattachment3][06e1fec4a87eca3142d54d09844c629f]](http://shang.qq.com/wpa/qunwpa?idkey=f2caf05ecbf22a024f7598a0e2f6bfd22e6796375da793a5b5ca3e4de7b6b4fa)

[__](http://blog.exbot.net/archives/2713#sidr)

[

# ExBot易科机器人实验室

](http://blog.exbot.net/ "ExBot易科机器人实验室")

[__](http://blog.exbot.net/archives/2713#)

[__](http://blog.exbot.net/archives/2713#login)

[

# ExBot易科机器人实验室

](http://blog.exbot.net/ "ExBot易科机器人实验室")

[搜索](http://blog.exbot.net/archives/2713#)

[登录](http://blog.exbot.net/archives/2713#login)

  * [__“星火计划”北京、上海站公开课圆满结束，可加入QQ群接收开课通知！](http://blog.exbot.net/archives/bulletin/%E6%98%9F%E7%81%AB%E8%AE%A1%E5%88%92%E6%AD%A6%E6%B1%89%E7%AB%99%E5%85%AC%E5%BC%80%E8%AF%BE "查看“星火计划”武汉站公开课")

  * [__“星火计划”北京、上海站公开课圆满结束，可加入QQ群接收开课通知！](http://blog.exbot.net/archives/bulletin/%E6%98%9F%E7%81%AB%E8%AE%A1%E5%88%92%E6%AD%A6%E6%B1%89%E7%AB%99%E5%85%AC%E5%BC%80%E8%AF%BE "查看“星火计划”武汉站公开课")

  * [机器人](http://blog.exbot.net/robot)
  * [ROS](http://blog.exbot.net/ros)
  * [机器学习](http://blog.exbot.net/ml)
  * [点滴记录](http://blog.exbot.net/note)

  * 

现在位置： [首页](http://blog.exbot.net/ "返回首页") >
[robotics](http://blog.exbot.net/archives/category/robotics) >
[ROS](http://blog.exbot.net/archives/category/ros) > 正文

A-A+

# 如何设计一款基于ROS的移动机器人？——李金榜经验谈

__2016年07月28日 __[robotics](http://blog.exbot.net/archives/category/robotics),
[ROS](http://blog.exbot.net/archives/category/ros) __[评论 4
条](http://blog.exbot.net/archives/2713#comments) __阅读 3,183 次

    
    
    编者按：本文是EAI科技创始人兼CEO李金榜在硬创公开课的文字稿，感谢作者和雷锋网授权转载。



最近几年各种移动机器人开始涌现出来，不论是轮式的还是履带式的，如何让移动机器人移动都是最核心的工作。要让机器人实现环境感知、机械臂控制、导航规划等一系列功能，就需要操作系统的支持，而ROS就是最重要的软件平台之一，它在科研领域已经有广泛的应用。

不过有关ROS的书籍并不多，国内可供的学习社区就更少了。本期硬创公开课就带大家了解一下如何利用ROS来设计移动机器人。

![noteattachment4][a0e56356a4e13582d28431bfdf08d13e]

分享嘉宾李金榜：EAI科技创始人兼CEO，毕业于北京理工大学，硕士学位。
曾在网易、雪球、腾讯技术部有多年linux底层技术研发经验。2015年联合创立EAI科技，负责SLAM算法研发及相关定位导航软件产品开发。EAI科技，专注机器人移动，提供消费级高性能激光雷达、slam算法和机器人移动平台。

## **移动机器人的三个部分**

# ** **

所谓的智能移动， 是指机器人能根据周围的环境变化，自主地规划路线、避障，到达目标地。

机器人是模拟人的各种行为，想象一下，人走动需要哪些器官的配合？  首先用眼睛观察周围环境，然后用脑去分析如何走才能到达目标地，接着用腿走过去，
周而复始，直到到达目标地址为至。机器人如果要实现智能移动，也需要眼、脑和腿这三部分的紧密配合。

### **腿** ** **

“腿”是机器人移动的基础。机器人的“腿”不局限于类人或类动物的腿，也可以是轮子、履带等，能让机器人移动起来的部件，都可以笼统地称为“腿”。



类人的腿式优点是：既可以在复杂路况（比如爬楼梯）下移动、也可以更形象地模仿人的动作（比如跳舞），缺点是：结构和控制单元比较复杂、造价高、移动慢等。

所以大部分移动的机器人都是轮式机器人，其优势在于轮子设计简单、成本低、移动快。而轮式的也分为多种：
两轮平衡车、三轮、四轮和多轮等等。目前最经济实用的是两个主动轮+一个万向轮。

### **眼睛**



[
![noteattachment5][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/roboeye.png)

机器人的眼睛其实就是一个传感器。它的作用是观察周围的环境，适合做机器人眼睛的有激光雷达、视觉（深度相机、单双相机）、辅助（超声波测距、红外测距)等。

### **“脑”**

机器人的大脑就负责接收“眼睛”传输的数据，实时计算出路线，指挥腿去移动。

其实就是要把看到的东西转换为数据语言。针对如何描述数据，如何实现处理逻辑等一系列问题。 ROS系统给我们提供一个很好的开发框架。



# ** [
![noteattachment6][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/robobrain.png)**

## **ROS简介**

# ** **

ROS是建立在linux之上的操作系统。它的前身是斯坦福人工智能实验室为了支持斯坦福智能机器人而建立项目，主要可以提供一些标准操作系统服务，例如硬件抽象，底层设备控制，常用功能实现，进程间消息以及数据包管理。

ROS是基于一种图状架构，从而不同节点的进程能接受、发布、聚合各种信息（例如传感，控制，状态，规划等等）。目前ROS主要支持Ubuntu操作系统。

有人问ROS能否装到虚拟机里，一般来说是可以的，但是我们建议装个双系统，用Ubuntu专门跑ROS。

[
![noteattachment7][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/rosintro.png)

实际上，ROS可以分成两层，低层是上面描述的操作系统层，高层则是广大用户群贡献的实现不同功能的各种软件包，例如定位绘图，行动规划，感知，模拟等等。ROS（低层）使用BSD许可证，所有是开源软件，并能免费用于研究和商业用途，而高层的用户提供的包则使用很多种不同的许可证。

## **用ROS实现机器人的移动**

# ** **

对于二维空间，使用线速度 + 角速度可以实现轮式机器的随意移动。

> 线些速度：描述机器人前后移动的速度大小

>

> 角速度：描述机器人转动的角速度大小

所以控制机器人移动主要是要把线速度角速度转换为左右轮的速度大小，然后，通过轮子直径和轮间距，可以把线速度和角速度转化为左轮和右轮的速度大小。

这里有一个关键问题就是编码器的选择和pid的调速。

**编码器的选择：**
一般编码器和轮子是在一个轴上，目前来说，速度在0.7m/s以下的话，编码器选600键到1200键之间都ok。不过需要注意的是，编码器最好用双线的，A、B两线输出，A向和B向输出相差90度，这样可以防抖动。防抖动就是可以在之后里程计算时可以更准确。

左轮和右轮的速度大小的控制，通过轮子编码器反馈，通过PID实时调整电机的PMW来实现。实时计算出小车的里程计(odom)，得到小车移动位置的变化。

计算车的位置变化是通过编码器来计算的，如果轮子打滑等情况，那么计算的变化和实际的变化可能不同。要解决这个问题，其实是看哪个问题更严重。要走5米只走了4.9米重要，还是要走180度只走了179度重要。

其实角度的不精确对小车的影响更大。一般来说，小车的直线距离精确度可以控制在厘米范围内，在角度方面可以控制精准度在1%~2%。因为角度是比较重要的参数，所以很多人就用陀螺仪来进行矫正。

所以有时候大家问小车精度有多高？其实现在这样已经精度比较高了，难免打滑等问题，不可能做到百分之百的精准。

小车在距离和角度方面做到现在这样对于自建地图导航已经是可以接受的，要提高更高的精度可能就要其他设备辅助，比如激光雷达来进行辅助，激光雷达可以进行二次检测进行纠正。

激光雷达数据的存储格式，它首先会有一个大小范围，如果超出范围是无效的。还有就是有几个采样点，这样就可以激光雷达可以告诉你隔多少度有一个采样点。  
[
![noteattachment8][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/laserscan.png)

另外最后那个Intensities是告诉大家数据的准确率，因为激光雷达也是取最高点的数据，是有一定的准确率的。上面的ppt其实就是用激光雷达扫了一个墙的形状。

激光雷达扫出一个静态形状其实没有意义，雷达建图的意义其实在于建立房间的地图。

## **如何绘制地图？**

**第一步是收集眼睛数据：  **

针对激光雷达，ROS在sensor_msgs 包中定义了专用了数据结构来存储激光消息的相关信息，成为LaserScan。

它指定了激光的有效范围、扫描点采样的角度及每个角度的测量值。激光雷达360度实时扫描，能实时测出障碍物的距离、形状和实时变化。

**第二步就是把眼睛看到的数据转化为地图：**

[
![noteattachment9][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/scanmap.png)



ROS的gmapping把激光雷达的/scan数据转换为栅格map数据，其中黑色代表障碍物、白色代表空白区域，可以顺利通行、灰色
：未知领域。随着机器人的移动，激光雷达可以在多个不同方位观测同一个位置是否有障碍物，如果存在障碍物的阈值超过设置值是，就标定此处是存在障碍物；否则标定不存在障碍物。
把障碍物、空白区域和未知领域的尺寸用不同灰度表示出来，就是栅格地图。便于下一步定位和导航。

有时候会出现很直的墙，机器人却无法直着行走，这时的问题可能就是机器人的轮子出现打滑等其他问题，而走歪了，这时绘制出的地图也可能是歪的。这种情况可以通过加一个陀螺仪来避免这个情况。因为激光雷达的特性，有时候遇到黑色或镜面会导致测距不准。

目前的解决方法就是不用激光雷达，或者用激光雷达和超声波进行辅助处理。

ROS的地图是分多层的，我可以在不同高度放多台激光雷达来一起叠加，共同绘制一张地图。地图绘制结束之后，就可以进行定位和导航等工作。

## **如何定位和导航？**

**定位：** 其实是概率性的定位，而不是100%的精度。根据激光雷达扫描周围障碍物的形状，与地图的形状做匹配，判断机器人所在位置的概率。

机器人的定位是否成功，与地图特征有很大关系，如果区域特征明显，那么机器人就很容易判断自己的位置。如果出现难以定位的问题，可能需要人给指定初始位置，或者加led来进行位置识别，或者其他的定位设备来协助定位。

目前的视觉通过色彩或者光的技术越来越多。

**导航：** 全局路径规划+局部调整（动态避障）

导航其实就是全局定位，首先根据现有地图进行规划，但是在运行过程中会进行局部的路线规划。但是总体还是根据全局路径来走。

导航中工作量还很大，比如扫地机的路径规划和服务机器人的路径规划是不一样的，扫地机器人可能要全覆盖的有墙角的地图，而服务机器人主要围绕指定的路径或者最短路径来进行规划，这部分是ROS工作量最大的一块。

路径规划根据不同应用场景变化比较大，但是ROS提供基础的路径规划的开发包，在这个基础上我们会做自己的路径规划。

## **机器人描述和坐标系变换**

[
![noteattachment10][3d94c35dfbe9100e01dbcc8f878183e1]](http://blog.exbot.net/wp-
content/uploads/2016/07/urdf.png)

在导航时，哪些区域可以通过，取决于机器人形状等信息，ROS通过URDF（UnifiedRobot Description Format)
就是描述机器人硬件尺寸布局，比如轮子的位置、底盘大小、激光雷达安装位置，这些都会影响到坐标系的转换。

坐标系遵循的前提是每个帧只能有一个父帧，再往上进行一些眼神或者关联。

激光雷达的安装位置直接影响/scan输出数据。所以激光雷达和机器人的相对位置是需要做坐标变换，才能把激光雷达的数据转化为机器人视角的数据。

ROS的坐标系，最终归结为三个标准框架，可以简化许多常见的机器人问题：

> 1）全局准确，但局部不连续的帧（’map”）

>

> 2）全局不准确，但局部光滑框架（’odom”）

>

> 3）机器人自身框架（’base_link”）

多种传感器(像激光雷达、深度摄像头和陀螺仪加速度计等)都可以计算base_link和odom的坐标关系，但由于“每个帧只能有一个父帧”，所以只能有一个节点(比如
robot_pose_ekf 融合多传感器)发布base_link和odom的坐标关系。

Base link自身的坐标系，因为不同元件装在机器人上不同位置，都要对应到base link的坐标系中，因为所有的传感器都是要通过机器人的视角来“看”。

有些朋友问我，激光雷达在建地图的时候，小车移动后地图就乱了，这是因为小车的底盘坐标系和激光雷达的坐标系没有标定准确。

## **map和odom之间的关联**

因为小车移动需要一个局部联系，比如小车在向前走，不停的累加，这是里程计的作用，map起到全局的、不连续的作用，经过激光雷达和map对应。

如果要学习ROS的话，坐标系的变化是重要的点。坐标系的变换还有一个点，就是每个帧都只有一个父帧，有时候两个坐标都和它有关联的话，就是A和B关联，B再和C关联，而不是B/C都和A关联。

三个坐标帧的父子关系如下：

> map –> odom –> base_link

其实， map和odom都应该和base_link关联，但为了遵守“每个帧只能有一个父帧”的原则，根据map和base_link 以及
odom->base_link的关系，计算出map与odom的坐标关系并发布。

odom->base_link的坐标关系是由里程计节点计算并发布的。

map ->
base_link的坐标关系是由定位节点计算出来，但并不发布，而是利用接收odom->base_link的坐标关系，计算出map->odom的坐标关系，然后发布。

只有里程计的时候，没有激光雷达，也可以跑，但是要先根据预设地图进行简单避障。

# **精彩问答**

# ** **

Q：还有ROS的实时性有什么改进进展吗 ？

A：实时改进要看ROS2.0的设计，其实ROS2.0的进展网上有公开。但是实际上他的进展离实际应用还有一定距离，至少今年下半年还达不到稳定，不过可以去研究下他的代码，他对内存管理，线程管理，在实时性上有了很大改善。

Q：vSLAM对内存和CPU要求颇高。实际工程中，李老师使用的是什么硬件配置？可以做多大的地图呢？

A：确实如此，目前来说我们还是使用激光雷达和传感器辅助来进行，这个和地图大小没有太大关系，主要是与地形障碍物复杂程度有关。



**本文出处：程弢 @硬创公开课**

__喜欢 _10_ __[评论 4](http://blog.exbot.net/archives/2713#comments)
[__分享](http://blog.exbot.net/archives/2713#share "分享")

标签：[ros](http://blog.exbot.net/archives/tag/ros-2)[机器人](http://blog.exbot.net/archives/tag/%E6%9C%BA%E5%99%A8%E4%BA%BA)

![noteattachment11][0a943a488d56234f90abea73ec25c2d5]

  * **版权声明：** 本站原创文章，由[poyoten](http://blog.exbot.net/archives/author/poyoten "由poyoten发布")发表在[robotics](http://blog.exbot.net/archives/category/robotics), [ROS](http://blog.exbot.net/archives/category/ros)分类下，于2016年08月01日最后更新
  * **转载请注明：**[如何设计一款基于ROS的移动机器人？——李金榜经验谈 | ExBot易科机器人实验室](http://blog.exbot.net/archives/2713 "本文固定链接 http://blog.exbot.net/archives/2713")[ +复制链接](http://blog.exbot.net/archives/2713#)

【上篇】[ROS教程：视觉传感器使用漫谈](http://blog.exbot.net/archives/2669)  
【下篇】[如何使用Qt插件在Qt中进行ROS开发](http://blog.exbot.net/archives/2744)

##  4 条留言  访客：4 条  博主：0 条

  1. ![noteattachment12][3d94c35dfbe9100e01dbcc8f878183e1] **[QQ183072655](http://www.183072655.diouna.com/)** [](http://blog.exbot.net/archives/2713#comment-330052) 2016年08月11日 下午 4:29   -49楼   [回复](http://blog.exbot.net/archives/2713?replytocom=330052#respond)

博客不错，嘎嘎！

  2. ![noteattachment12][3d94c35dfbe9100e01dbcc8f878183e1] **zhangrelay** [](http://blog.exbot.net/archives/2713#comment-330012) 2016年07月28日 上午 8:56   -48楼   [回复](http://blog.exbot.net/archives/2713?replytocom=330012#respond)

图片无法正常显示啊

    * ![noteattachment12][3d94c35dfbe9100e01dbcc8f878183e1] **[poyoten](http://blog.exbot.net/)** [](http://blog.exbot.net/archives/2713#comment-330013) 2016年07月28日 上午 9:35   地下1层   [回复](http://blog.exbot.net/archives/2713?replytocom=330013#respond)

解决了。本来图片数据直接嵌入到文章中的，可能因为大小端存储的问题，有的不能正常显示，现在所以图片存储在本站。

      * ![noteattachment12][3d94c35dfbe9100e01dbcc8f878183e1] **zhangrelay** [](http://blog.exbot.net/archives/2713#comment-330020) 2016年07月28日 下午 10:47   地下2层   [回复](http://blog.exbot.net/archives/2713?replytocom=330020#respond)

赞

### 给我留言

昵称（必填）

邮箱（必填）

网址

__[__](http://blog.exbot.net/archives/2713 "插入表情")
![noteattachment16][d22775b2e32645907141f788c36d4e9d]
![noteattachment17][17cbe5cbade2b4ec3d85be4ac9409add]
![noteattachment18][1a273db3c34f6afb3fed75417ca5e7b6]
![noteattachment19][63bf101bd3d4f7564d3cf31822218d2e]
![noteattachment20][5ce371458c1a2148595f5f3daf7b5fc8]
![noteattachment21][b2984729c3b6cdc07508b88b5c0a4d1e]
![noteattachment22][1c6d8b101c821641f983175221346112]
![noteattachment23][c7597052fe2b16db307d6bd14e7b8c6b]
![noteattachment24][299972b5cdd1f1e0690dd95e4038bd87]
![noteattachment25][a6c65fa6ff738ef6c46a4e80a65f7aa0]
![noteattachment26][7fefa473594650055a36b9e3062c9a91]
![noteattachment27][96467eb5ae18dfa22ea1c0fa3e74380e]
![noteattachment28][d4f04dc65a387ca9b8c0f22ca8c0ec8c]
![noteattachment29][d7be08b669651a63080cfe7b9004d330]
![noteattachment30][62abd50ca92eb2381a7c60e351f64c46]
![noteattachment31][afc8bbc65fcbd2b82a3e2c1ab41a216a]
![noteattachment32][d01a4f87055ac0fce8a66739d80434ba]
![noteattachment33][bdb3226d2568b8c1edf8f453b1e872e6]
![noteattachment34][bfcab5090b1280bbe495dbead4d2281f]
![noteattachment35][8a95dbfaa99809b0150687ae0cb45aed]
![noteattachment36][453e7a3f8bbb417008f06d576c41d060]
![noteattachment37][fde9e44a8aae0e89bd527792b4779aca]

###

__

本站推荐

  * [ ![noteattachment38][4ca660ddc564ad7e8c13714fa1052793] ](http://blog.exbot.net/archives/1696 "TOP原创 | Lily无人机深度解析")

[TOP原创 | Lily无人机深度解析](http://blog.exbot.net/archives/1696 "TOP原创 |
Lily无人机深度解析")

__阅读 6,404 次

  * [ ![noteattachment39][87a403393bc9b08a2cd0ef40418d1c8d] ](http://blog.exbot.net/archives/2515 "SLAM第一篇：基础知识")

[SLAM第一篇：基础知识](http://blog.exbot.net/archives/2515 "SLAM第一篇：基础知识")

__阅读 11,193 次

  * [ ![noteattachment40][0c36b29c2053eb267d4f89bb4fc523d2] ](http://blog.exbot.net/archives/2966 "机器人程序设计——之如何正确入门ROS | 硬创公开课（附视频/PPT）")

[机器人程序设计——之如何正确入门ROS | 硬创公开课（附视频/PPT）](http://blog.exbot.net/archives/2966
"机器人程序设计——之如何正确入门ROS | 硬创公开课（附视频/PPT）")

__阅读 8,824 次

###

__

热门文章

  * 1[机器学习漫游指南 最完整的入门书...](http://blog.exbot.net/archives/2988)
  * 2[如何做好自动驾驶智能车控制决策系...](http://blog.exbot.net/archives/2982)

###

__

分类目录

  * [Machine Learning](http://blog.exbot.net/archives/category/machine-learning "关于机器学习的一切")
  * [note](http://blog.exbot.net/archives/category/note "只言片语")
  * [Other](http://blog.exbot.net/archives/category/other "杂项")
  * [QuadRotor](http://blog.exbot.net/archives/category/quadrotor)
  * [Resource](http://blog.exbot.net/archives/category/resource "分享来源于网络的稀少资源")
  * [robotics](http://blog.exbot.net/archives/category/robotics "关于机器人的一切")
  * [ROS](http://blog.exbot.net/archives/category/ros "关于ROS机器人操作系统的一切")
  * [星火计划](http://blog.exbot.net/archives/category/spark)
  * [机器人未来](http://blog.exbot.net/archives/category/%E6%9C%BA%E5%99%A8%E4%BA%BA%E6%9C%AA%E6%9D%A5)

###

__

相关文章

  * [__如何做好自动驾驶智能车控制决策系统开发？ | 硬创公开课](http://blog.exbot.net/archives/2982)
  * [__机器人工程师之路——从大一到研究生，YY硕经验谈](http://blog.exbot.net/archives/2790)
  * [__IEEE spectrum-201510-top精选机器人文章](http://blog.exbot.net/archives/2302)
  * [__新书速递《机器人与未来》](http://blog.exbot.net/archives/2284)
  * [__机器人系统常用仿真软件介绍和效果](http://blog.exbot.net/archives/2279)

###

__

近期评论

  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **大炮** 时效，无法下载 ](http://blog.exbot.net/archives/2323#comment-330231 "发表在 > 飞控漫谈第1讲")
  * [ ![noteattachment42][19ce036c7f16eef8649710cc7b904279] **云飞机器人实验室** 支持刘老师！ ](http://blog.exbot.net/archives/2966#comment-330224 "发表在 > 机器人程序设计——之如何正确入门ROS | 硬创公开课（附视频/PPT）")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **kamisama** catkin包没创建好，重做一遍就好了 ](http://blog.exbot.net/archives/1316#comment-330221 "发表在 > 机器人操作系统ROS Indigo 入门学习（6）——理解ROS Nodes")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **kamisama** 小海龟出不来怎么回事，roscore运行正常. 输入rosrun turtlesim turtlesim_node 提示 [rosrun] Couldn 't find executable named turtlesim_node below /opt/ros/indigo/share/turtlesim 环境： ubuntu14.04 indigo ](http://blog.exbot.net/archives/1316#comment-330220 "发表在 > 机器人操作系统ROS Indigo 入门学习（6）——理解ROS Nodes")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **zhangrelay** 😛 非常赞！！！ ](http://blog.exbot.net/archives/2966#comment-330217 "发表在 > 机器人程序设计——之如何正确入门ROS | 硬创公开课（附视频/PPT）")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **CrystalHong** hello,楼主，能不能发一份2012Reinforcement Learning State-Of-the-Art电子版给我啊？3Q 邮箱：fuhong2015@126.com ](http://blog.exbot.net/archives/223#comment-330210 "发表在 > 关于强化学习\(Reinforcement Learning\)学习过程中的几点想法")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **Julian** 您好，百度网盘的连接失效了，帮忙更新下好吗？很喜欢您的东西，拜读一下 ](http://blog.exbot.net/archives/2594#comment-330208 "发表在 > ROS与Matlab系列：一个简单的运动控制")
  * [ ![noteattachment48][c9a9b5eddaaeb11d01e51648c37468db] **tony** fatal: Not a git repository (or any of the parent directories): .git make: *** 没有规则可以创建目标“clean”。 停止。 setup.sh: 行 42: /opt/qt57/bin/qmake: 没有那个文件或目录 make: *** 没有指明目标并且找不到 makefile。 停止。 正克隆到  'ros_qtc_plugin'... remote: Counting objects: 718, done. error: RPC failed; result=56, HTTP code = 200 fatal: The remote end hung up unexpectedly fatal: protocol error: bad pack header setup.sh: 第 56 行: cd: /home/tony/qtc_plugins/ros_qtc_plugin: 没有那个文件或目录 setup.sh: 第 57 行: cd: /home/tony/qtc_plugins/ros_qtc_plugin: 没有那个文件或目录 setup.sh: 第 58 行: cd: /home/tony/qtc_plugins/ros_qtc_plugin: 没有那个文件或目录 make: *** 没有规则可以创建目标“clean”。 停止。 setup.sh: 行 62: /opt/qt57/bin/qmake: 没有那个文件或目录 make: *** 没有指明目标并且找不到 makefile。 停止。 ](http://blog.exbot.net/archives/2744#comment-330207 "发表在 > 如何使用Qt插件在Qt中进行ROS开发")
  * [ ![noteattachment48][c9a9b5eddaaeb11d01e51648c37468db] **doublehao** 想咨询一下，如果我想要在rviz中导入自己的模型的话，应该是怎么样的步骤？？谢谢啦 ](http://blog.exbot.net/archives/899#comment-330203 "发表在 > 10分钟上手玩ROS仿真机器人")
  * [ ![noteattachment41][09a8ef3a708b80ba08581ffc702f4fa5] **walleva** 安装exbot 提供的镜像发现 图形界面的密码进得去，但是tty 字符界面进不去。怎么回事 ](http://blog.exbot.net/archives/762#comment-330202 "发表在 > 10分钟安装ROS（Windows + 虚拟机）")

Copyright © ExBot易科机器人实验室 保留所有权利.    Theme   [Robin](http://zmingcx.com/
"主题：知更鸟") modified by poyoten [ ](http://blog.exbot.net/archives/%3C/span)

[ ](http://blog.exbot.net/archives/%3C/span)

# 用户登录

记住登录信息

  * [__](http://blog.exbot.net/archives/2713 "返回顶部")
  * [__](http://blog.exbot.net/archives/2713#share "分享")
  * [__](http://blog.exbot.net/archives/2713 "查看评论")
  * [__](http://blog.exbot.net/archives/2713 "转到底部")

#### 分享到：

[](http://blog.exbot.net/archives/2713# "分享到QQ空间")
[](http://blog.exbot.net/archives/2713# "分享到新浪微博")
[](http://blog.exbot.net/archives/2713# "分享到腾讯微博")
[](http://blog.exbot.net/archives/2713# "分享到人人网")
[](http://blog.exbot.net/archives/2713# "分享到微信")
[](http://blog.exbot.net/archives/2713#)


---
### ATTACHMENTS
[06e1fec4a87eca3142d54d09844c629f]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.png
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.png](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.png)
[09a8ef3a708b80ba08581ffc702f4fa5]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.jpg)
[0a943a488d56234f90abea73ec25c2d5]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.jpg)
[0c36b29c2053eb267d4f89bb4fc523d2]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.jpg)
[17cbe5cbade2b4ec3d85be4ac9409add]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.gif)
[19ce036c7f16eef8649710cc7b904279]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.jpg)
[1a273db3c34f6afb3fed75417ca5e7b6]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.gif)
[1c6d8b101c821641f983175221346112]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.gif)
[299972b5cdd1f1e0690dd95e4038bd87]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-4.gif)
[3d94c35dfbe9100e01dbcc8f878183e1]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.a
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.a](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室.a)
[453e7a3f8bbb417008f06d576c41d060]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.gif)
[4ca660ddc564ad7e8c13714fa1052793]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.png
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.png](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-2.png)
[5ce371458c1a2148595f5f3daf7b5fc8]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.gif)
[62abd50ca92eb2381a7c60e351f64c46]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-7.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-7.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-7.gif)
[63bf101bd3d4f7564d3cf31822218d2e]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-8.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-8.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-8.gif)
[7fefa473594650055a36b9e3062c9a91]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-9.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-9.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-9.gif)
[87a403393bc9b08a2cd0ef40418d1c8d]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-5.jpg)
[8a95dbfaa99809b0150687ae0cb45aed]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-10.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-10.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-10.gif)
[96467eb5ae18dfa22ea1c0fa3e74380e]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-11.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-11.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-11.gif)
[a0e56356a4e13582d28431bfdf08d13e]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.png
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.png](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-3.png)
[a6c65fa6ff738ef6c46a4e80a65f7aa0]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-12.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-12.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-12.gif)
[afc8bbc65fcbd2b82a3e2c1ab41a216a]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-13.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-13.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-13.gif)
[b2984729c3b6cdc07508b88b5c0a4d1e]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-14.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-14.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-14.gif)
[bdb3226d2568b8c1edf8f453b1e872e6]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-15.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-15.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-15.gif)
[bfcab5090b1280bbe495dbead4d2281f]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-16.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-16.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-16.gif)
[c7597052fe2b16db307d6bd14e7b8c6b]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-17.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-17.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-17.gif)
[c9a9b5eddaaeb11d01e51648c37468db]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.jpg
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.jpg](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-6.jpg)
[d01a4f87055ac0fce8a66739d80434ba]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-18.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-18.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-18.gif)
[d22775b2e32645907141f788c36d4e9d]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-19.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-19.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-19.gif)
[d4f04dc65a387ca9b8c0f22ca8c0ec8c]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-20.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-20.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-20.gif)
[d7be08b669651a63080cfe7b9004d330]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-21.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-21.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-21.gif)
[fde9e44a8aae0e89bd527792b4779aca]: media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-22.gif
[如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-22.gif](media/如何设计一款基于ROS的移动机器人？——李金榜经验谈__ExBot易科机器人实验室-22.gif)

---
### TAGS
{AI*MR概述}

---
### NOTE ATTRIBUTES
>Created Date: 2017-02-18 17:56:43  
>Last Evernote Update Date: 2019-04-06 02:07:15  
>source: web.clip  
>source-url: http://blog.exbot.net/archives/2713  
>source-application: evernote.win32  