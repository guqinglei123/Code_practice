# 无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？ - 知乎

[](https://www.zhihu.com/)

[首页](https://www.zhihu.com/)[发现](https://www.zhihu.com/explore)[话题](https://www.zhihu.com/topic)

登录加入知乎

# 无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？

关注问题

写回答

[机器人](https://www.zhihu.com/topic/19551273)

[无人驾驶车](https://www.zhihu.com/topic/19653871)

[Google 无人驾驶汽车](https://www.zhihu.com/topic/19704867)

[同时定位和地图构建（SLAM）](https://www.zhihu.com/topic/20033502)

# 无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？

SLAM传统上还是面向室内等缺少GPS信号的应用，例如室内移动机器人导航，而在无人驾驶汽车上，它的意义和作用是什么，已经有高精度的地图和城市GPS信号…显示全部

关注者

 **478**

被浏览

 **12,504**

关注问题

写回答

​

添加评论

​

分享

​

邀请回答

​

[查看全部 8 个回答](https://www.zhihu.com/question/67473027)

[
![noteattachment1][5f227dcb1845d09a13c07a1e822d73be]](https://www.zhihu.com/people/yan-
qin-rui)

[颜沁睿](https://www.zhihu.com/people/yan-qin-rui)

天天上班打游戏

45 人赞同了该回答

谢邀，有很多留言邮件问过我这个问题，很抱歉我都没有回复，因为这个问题暂时还没有明确答案，作为身在自动驾驶研发一线的成员，只能分享一下想法大家一起探讨。

答题先扣题，这里的slam假设是视觉slam了，因为激光slam精度较高，在自动驾驶中应用已经比较多了这点没什么疑问。无人汽车也不可能随时收到GPS信号，GPS信号不是直接可用，因此SLAM有用。SLAM不是感知技术，主要还是用于定位。

  

\--------------------------------------我是分割线-------------------------------------------------

之后可以展开来说一下，

以视觉技术为核心的自动驾驶技术其实已经有现成的模板: 欧盟的v-charge项目  
[https://cvg.ethz.ch/research/v-charge/](https://link.zhihu.com/?target=https://cvg.ethz.ch/research/v-charge/)  
这个项目的主要目标就是实现低成本可量产的大型停车场自主泊车解决方案，相机的配置为前视双目相机和环视四路鱼眼相机，另外辅以四面超声波雷达用作基本避障。这种传感器的配置优势很明显，成本极低（对比激光雷达，高精IMU，室内UWB），方便车规级量产，对当前车辆结构设计改动很小，易于推广。

![noteattachment2][937f0fd4c0b6a61eb2598fa1ccd440cb]

v-charge DEMO用车，大众GOLF. 来源：https://www.ethz.ch/en/news-and-events/eth-
news/news/2014/04/driverless-parking-for-tomorrows-vehicles.html

slam可以有定位和建图两方面应用，目前看来在自动驾驶中主要的需求还是定位。相对而言定位的成本是远高于建图的，因为定位系统必须每台车都装备，而建图则不需要。当然为了保证地图的及时更新，建图车也是多多益善，但这个话题可以分开讨论。

如果把视觉slam划分为定位技术的话，则稀疏，稠密，半稠密地图的讨论都没有什么意义了，因为建立的地图纯粹是用来帮助相对定位的。因此只要保存足够大的局部地图，支持一定规模的local
ba即可。

  

![noteattachment3][cabf987bd9454502e44cc74c56ac7a41]

v-charge中，车辆实时建立避障地图

前面几个答案中，似乎把高精地图和slam建立的点云地图都算成了“地图”，我觉得还是有必要澄清一下，这两个地图表达形式是完全不同的。点云地图需要相当复杂的后处理，包括人工标注，才能成为高精地图。目前为止，市面上还没有基于视觉的全自动高精地图生成方案，国内外有不少企业正在努力地做这件事情，希望能早日实现。

回过头来说视觉slam，对于定位技术而言，最重要的指标是精度。由于vo是一种相对定位的方式，很少会产生定位跳变，累积误差的影响会比较大。所以最重要的指标就是位姿偏移了千分之几，即每走一百米，误差多少厘米？

这个指标直接决定了视觉slam在自动驾驶中的应用场景，它表示了在绝对定位技术（gps, uwb,
重定位等）技术缺失的情况下，自动驾驶汽车可以工作的时间与范围。

结合自动驾驶的场景，可以推出vslam的应用点主要是:  
1\. gps缺失场景下的长时间定位，如室内，楼房中。  
2\. 补偿行驶过程中gps信号不稳定造成的定位跳跃，如山洞，高楼群，野外山区等。

vslam的精度及鲁棒性越高，适用的场景越宽广。如果vslam能在任何场景无限长定位保持高精度，那其他定位技术就可以歇菜了，当然目前看来这个可能性很小，因此需要尝试结合imu，编码器等设备融合。至于最终的技术形态，目前还没有定论。

在无人驾驶汽车上，目前比较显著的瓶颈还在计算方面，数据收发，障碍物感知，融合定位，路径规划，每个模块都需要占据相当的计算资源。而SLAM本身就是对计算力消耗极大的一个模块（无论视觉还是激光），如果加上高频率的IMU进行融合优化，则计算力更加捉襟见肘。因此是否值得为视觉SLAM分配原本就那么有限的计算资源，如何识别场景对SLAM模块进行激活都是需要仔细衡量的。

  

值得一提的是，在v-
charge项目中，主要还是基于传统的特征点定位，深度图避障等方法，在特定场景下能够完成自动泊车任务。但是对于一个工业级产品而言，其鲁棒性仍然十分存疑，因此至今尚未能够看到相关产品面世。而近几年来深度学习大大提升了视觉算法的基本感知能力，如稳定实时的物体检测，语义分割技术。它们一方面可以使得自动驾驶汽车对于定位精度的需求从厘米级降低到亚米级，另一方面有望进一步提升视觉SLAM的精度及鲁棒性。这样可以使高精地图的绘制成本及定位系统的实现成本大大降低。

目前我们组正在相关的领域进行基于多种方案的研发，持续招人中（实习正式均可），希望加入的同学欢迎发送简历到qinrui.yan@hobot.cc。

[发布于 2017-11-06](https://www.zhihu.com/question/67473027/answer/255525224)

45

​

13 条评论

​

分享

​

收藏​

感谢收起

#### 更多回答

[
![noteattachment4][904ead2cca22062e339fba0f2c809058]](https://www.zhihu.com/people/spark-20-22)

[Spark](https://www.zhihu.com/people/spark-20-22)

我说的白是(255,255,255)

18 人赞同了该回答

抛砖引玉回答一个。

这也算是SLAM问题“终极二问”的其中一问了： **Do autonomous robots really need SLAM?**

另外一个是： **Is SLAM sloved?** [1]

  

题主的第一个问题， **无人驾驶技术与SLAM的契合点在哪里？**

回答这个问题，首先要明确SLAM的使命。最初，SLAM的提出就是为了解决 **未知环境下** 移动机器人的定位和建图的问题。

所以，笼统的说，SLAM对于无人驾驶的意义就是如何帮助车辆感知周围环境，更好的完成导航、避障、路径规划等高级任务。

题主提到现在已经有高精度的地图，暂且不去考虑这个地图的形式、存储规模和如何用它的问题。首先，这个构建好的地图真的能帮助无人驾驶完成避障或者路径规划等的类似任务吗？至少环境是动态的，道路哪里有一辆车，什么时候会出现一个行人，这些都是不确定的。所以从实时感知周围环境这个角度来讲，提前构建好的地图是不能解决这个问题的。

另外，GPS的定位方式是被动的、依赖信号源的，这一点使得其在一些特殊场景下是不可靠的，比如城市环境中GPS信号被遮挡，野外环境信号很弱，还有无人作战车辆作战中信号被干扰以及被监测等。所以像视觉SLAM这种主动的并且无源的工作方式在上述场景中是有优势的。

从硬件角度讲，目前主流的视觉SLAM方案，在构建低成本，小型化，易于搭载的硬件平台方面也是有优势的。

  

  

  

对于第二个问题， **有什么理由能够让SLAM成为无人驾驶的关键技术？**

我个人不是很赞同这个逻辑。SLAM作为一个很庞杂的系统，其本身也有很多关键环节和实际应用中会遇到的难题，作为一种应用场景越来越广泛的技术（如自动机器人，无人机，无人驾驶，AR），它可能永远不会成为无人驾驶的关键技术，与其思考这个问题，不如关注SLAM本身，即围绕
**定位和建图**
这两个基本任务，来想想里程计是不是可以估计的更准确，环境地图信息是不是可以建立得更丰富（比如有用的语义信息），场景识别/闭环检测是不是能保证更高的准确率和召回率，是不是可以借助其他传感器完善SLAM系统，接下来在想想
**SLAM能帮助无人驾驶做些什么？** 只有技术越来越完善和成熟，才能被应用到更多的实际场景中。

  

另外，我目前在研究结合深度学习如何解决视觉SLAM场景识别问题，如果各位对这方面有兴趣或者做过相关的工作，欢迎交流！

  

[1] Cadena, Cesar, et al. "Past, present, and future of simultaneous
localization and mapping: Toward the robust-perception age." _IEEE
Transactions on Robotics_ 32.6 (2016): 1309-1332.

展开阅读全文

18

​

11 条评论

​

分享

​

收藏​

感谢

[
![noteattachment5][2dd5b8eed51b2724487aa80a4b24d9cb]](https://www.zhihu.com/people/mr-
husky-56)

[Pickles Husky](https://www.zhihu.com/people/mr-husky-56)

主人是只猫

16 人赞同了该回答

谢邀，从phd学生的视角简单说一下，只了解一点皮毛，工业界大佬们请拍～

首先题主说的基本上是对的，目前自动驾驶中大家依赖的定位技术主流是高精度预制地图+localization（激光、视觉、GPS以及各种融合），需要vehicle具备online
mapping能力的时间并不多，也就是说目前自动驾驶汽车在绝大多数运行时间内并没有运行SLAM。

那我们就可以说在自动驾驶中SLAM技术没有用武之地么？我个人不这样认为。原因以下几点：

1、高精度预制地图从何而来？由于目前车载GPS+惯导的精度尚无法支持大尺度上的高精度定位来直接建图（RTK-
GPS的主要问题是城市、隧道环境丢星，还有基站的问题），所以以目前的技术，城市及更大尺度的高精度建图还是要部分依赖SLAM技术。而且这里面有很多值得研究的问题，比如超大规模least
square优化、多机器人建图与子图合并、不同时间尺度上建图的合并（比如冬天的图与夏天图的合并、白天与夜间图的合并，如果是视觉建图这个问题非常难），所以说这里面有很多的SLAM问题可以研究。

2、localization问题，某种程度上来说定位和重定位都是SLAM的子问题，使用的很多技术都是相通的，研究透SLAM的researcher在预制地图上做定位也会得心应手。

3、预制地图+定位无法覆盖的情况，目前没有哪个厂家试图做到全世界范围高精度、高更新频率建图，总有没有地图覆盖、地图更新不及时，以及off-
road的情况，所以所有的厂家都要求车辆具有一定的SLAM能力以应对没有地图，或者预制地图不能使用的未知的情况。

[编辑于 2017-11-02](https://www.zhihu.com/question/67473027/answer/253306600)

16

​

8 条评论

​

分享

​

收藏​

感谢

[查看全部 8 个回答](https://www.zhihu.com/question/67473027)

[
![noteattachment6][7caef4dd36377ef2fb2a1ea9bcb370f7]下载知乎客户端与世界分享知识、经验和见解](http://zhi.hu/BDXoI)

关于作者

[
![noteattachment7][5173e8e82d869b6741458ee64a8cedf0]](https://www.zhihu.com/people/yan-
qin-rui)

[颜沁睿](https://www.zhihu.com/people/yan-qin-rui)

天天上班打游戏

[回答 **44**](https://www.zhihu.com/people/yan-qin-rui/answers)[ 文章
**1**](https://www.zhihu.com/people/yan-qin-rui/posts)[ 关注者
**1,502**](https://www.zhihu.com/people/yan-qin-rui/followers)

​

关注他

发私信

被收藏 37 次

[机器学习](https://www.zhihu.com/collection/182337140 "机器学习")

知乎用户 创建

4 人关注

[slam](https://www.zhihu.com/collection/133668595 "slam")

[喵家小帅](https://www.zhihu.com/people/hu-rui-49-66) 创建

4 人关注

[CV](https://www.zhihu.com/collection/42043971 "CV")

[HLin](https://www.zhihu.com/people/shen-hai-hu-xi-hua) 创建

2 人关注

[无人机SLAM](https://www.zhihu.com/collection/189205578 "无人机SLAM")

[刘智](https://www.zhihu.com/people/liu-zhi-54-73) 创建

1 人关注

[自动驾驶](https://www.zhihu.com/collection/168049479 "自动驾驶")

[范伟](https://www.zhihu.com/people/fan-wei-93-95) 创建

1 人关注

相关问题

[研究自动驾驶技术的算法需要哪些知识？](https://www.zhihu.com/question/46575222) 11 个回答

[无人驾驶，个人如何研究？](https://www.zhihu.com/question/20210846) 19 个回答

[无人驾驶车的传感器如何进行布置？需要有哪些考虑？](https://www.zhihu.com/question/54857225) 5 个回答

[无人驾驶汽车比无人机控制程序要更复杂吗？](https://www.zhihu.com/question/23894597) 3 个回答

[无人驾驶中激光雷达感知周围环境的原理是什么？](https://www.zhihu.com/question/54137057) 8 个回答

相关推荐

[ ![noteattachment8][363e81ef5e4178221bb323d9b97c1269]9折|陈丹青荐: 国家宝藏80讲共 80
节课试听](https://www.zhihu.com/remix/albums/921064464932048896)[
![noteattachment9][e02c2894ff6542421756d5ba7a73dae7]文学是否是抵御 AI 的最后一个阵地？ 5722
人参与](https://www.zhihu.com/lives/848676201412308992)[
![noteattachment10][4b162289a2343ba070e932a90054aab1]智能化未来：无人驾驶技术将如何改变我们的生活504
人读过​阅读](https://www.zhihu.com/publications/book/119556442)

[刘看山](https://liukanshan.zhihu.com/)[知乎指南](https://www.zhihu.com/question/19581624)[知乎协议](https://www.zhihu.com/terms)[应用](https://www.zhihu.com/app)[工作](https://www.zhihu.com/careers)  
[侵权举报](https://zhuanlan.zhihu.com/p/28561671)[网上有害信息举报专区](http://www.12377.cn/)  
违法和不良信息举报：010-82716601  
[儿童色情信息举报专区](https://www.zhihu.com/jubao)  
[联系我们](https://www.zhihu.com/contact) © 2018 知乎


---
### ATTACHMENTS
[2dd5b8eed51b2724487aa80a4b24d9cb]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.jpg)
[363e81ef5e4178221bb323d9b97c1269]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-2.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-2.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-2.jpg)
[4b162289a2343ba070e932a90054aab1]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-3.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-3.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-3.jpg)
[5173e8e82d869b6741458ee64a8cedf0]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-4.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-4.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-4.jpg)
[5f227dcb1845d09a13c07a1e822d73be]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-5.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-5.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-5.jpg)
[7caef4dd36377ef2fb2a1ea9bcb370f7]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.png
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.png](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎.png)
[904ead2cca22062e339fba0f2c809058]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-6.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-6.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-6.jpg)
[937f0fd4c0b6a61eb2598fa1ccd440cb]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-7.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-7.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-7.jpg)
[cabf987bd9454502e44cc74c56ac7a41]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-8.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-8.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-8.jpg)
[e02c2894ff6542421756d5ba7a73dae7]: media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-9.jpg
[无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-9.jpg](media/无人驾驶技术与SLAM的契合点在哪里，有什么理由能够让SLAM成为无人驾驶的关键技术？_-_知乎-9.jpg)

---
### TAGS
{AI*AG概述}

---
### NOTE ATTRIBUTES
>Created Date: 2018-01-08 16:07:31  
>Last Evernote Update Date: 2019-04-06 02:07:09  
>source: web.clip  
>source-url: https://www.zhihu.com/question/67473027/answer/255525224?utm_source=com.evernote  
>source-url: &  
>source-url: utm_medium=social  
>source-application: ios.clipper.evernote  