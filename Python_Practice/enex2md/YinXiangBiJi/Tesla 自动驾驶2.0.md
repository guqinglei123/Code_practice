# Tesla 自动驾驶2.0

  

  

  

注意看那两块Tegra X1的芯片与主板链接方式——居然是NVM接口，再联想一下Tesla用的车载电脑：

好巧，主芯片Tegra 3模组也是NVM接口！

  

  

  

  

2\. 固件7.0 和 固件8.0的自动辅助驾驶拥有完全不同的性能。

  

  

  

刚刚Elon Musk公布了今天以后生产的Tesla Model S、X以及3将会具备自动驾驶2.0平台。

希望借用上一次的文章作为铺垫，来谈谈这次2.0增加了什么，又改变了什么。

感兴趣第一篇文章的：[Tesla自动驾驶的前世今生 - Ryan Woo的文章 -
知乎专栏](https://zhuanlan.zhihu.com/p/22413629)

先感受下自动驾驶2.0实际效果：

  

[ ![noteattachment1][32a49d5b6c565d5193860dfeaa97aa91] Full Self-Driving
Hardware - 腾讯视频
http://v.qq.com/x/page/q0338hv72j7.html](https://link.zhihu.com/?target=http%3A//v.qq.com/x/page/q0338hv72j7.html)

1.硬件部分：

Autopilot 1.0 ：

一个前置摄像头

12个超声波传感器

一个前置雷达

一个后置倒车摄像头（目前不参与自动辅助驾驶）

下面的图片中可以看见12个传感器按照前后排列，摄像头和雷达以大约40度向前。

处理芯片：NVIDIA Tegra 3/ Mobileye Q3

![noteattachment2][3a3bcbd101e76afcbee24b38d681fd7a]

Autopilot 2.0：

3个前置摄像头（不同视角 广角、长焦、中等）

2个侧边摄像头（一左一右）

3个后置摄像头

12个超声波传感器（传感距离增加一倍）

一个前置雷达(增强版)

一个后置倒车摄像头（目前不参与自动辅助驾驶）

处理芯片：NVIDIA PX2？（40x Autopilot 1.0 处理速度）

![noteattachment3][42c26c627c5f456ed3f6a1bbdca0dbe8]

其实我想说的是硬件这部分，Autopilot
2.0真没啥让人眼前一亮的东西，除了硬件规格升级，摄像头大增，这个配置基本是目前很多车的自动辅助驾驶标配，除了Tesla提到的可以提升40倍计算性能的芯片：

坊间早有传说，NVIDIA的黄仁勋和Elon Musk本来私交就甚好，否则Tesla 第一代Model
S选型时就不会看上当时无人问津的Tegra芯片，在关键时候拉了老黄一把，老黄也是Tesla簇拥，几个月前两人还出席了OpenAI的发布会，老黄也捐赠了当时最强大的DGX-1给协会：

![noteattachment4][024bbeb9093f09c492fefb19ea102b7a]

这事还上了两家的官方新闻：[https://blogs.nvidia.com/blog/2016/08/15/first-ai-supercomputer-
openai-elon-musk-deep-
learning/](https://link.zhihu.com/?target=https%3A//blogs.nvidia.com/blog/2016/08/15/first-
ai-supercomputer-openai-elon-musk-deep-learning/)

再考虑到之前Mobileye和Tesla闹分手，可以无端猜测一下NVIDIA在里面帮忙推了一把：

“别用以色列的陈旧东西了，换用我们家的Drive PX吧”

所以2014年你会看到这样一个奇葩东西：

NVIDIA当时发布的Drive PX1 上面居然有一个Mobileye Q3芯片！你说这是专门方便”某公司“测试对比吗？

![noteattachment5][535807a196984d6570f91b45db2117f5]

然后再看看现在的NVIDIA Drive PX2:

![noteattachment6][60780508e00b6cd2779e5edeb4b8d1a2]

![noteattachment7][5b469e41bb7b23cda388249d1ce12289]

![noteattachment8][3e5a4959eeb4b1175e0851e3f71be56d]

所以也许私底下NVIDIA和Tesla早就在计划更换Mobileye，只是刚好遇到那次车祸，正好以此为契机分手，转投NVIDIA。所以不出意外，这个40倍芯片就是Drive
PX2上面的Tegra X1:

![noteattachment9][77576f248831f38a883dbd6e96348aec]

2\. 软件部分

我想说虽然有很多人认为Tesla的实力在于其有多么先进的硬件技术，例如电池，例如电动马达设计和制造...其实Tesla真正的竞争实力是在软件部分，例如电池管理BMS：[Tesla
Motors 的电池管理系统 (BMS) 相比其他电动汽车有哪些优势？ - 特斯拉汽车 (Tesla
Motors)](https://www.zhihu.com/question/22183103) 或者说Tesla在硬件和软件上两手抓才是它最大的竞争力：

在第一篇文章中，我引用了不少媒体对2016-2017款 奔驰 E／S 自动辅助驾驶对比Tesla Model S自动辅助驾驶的测试：

引用自：[Tesla自动驾驶的前世今生 - Ryan Woo的文章 -
知乎专栏](https://zhuanlan.zhihu.com/p/22413629)

在上面autofil的测试中，测试者发现奔驰E的自动辅助驾驶有非常严重的漂移现象：

在过一个大弯的途中：

奔驰在自动辅助驾驶中越过了道路中央的黄线，并且跑到了逆行车道，我们不得不人工把车调回来，因为车完全没意识到自己已经逆向行驶。

Tesla始终保持在黄线内测，无需人工干预。

![noteattachment10][b35bf24fe729832b7645af7dec63303c]

小弯道：

奔驰在行驶中滑出了道路白线，并且完全没有修正企图。

Tesla很轻松就保持在道路中心。

![noteattachment11][3057f235bc5ddd0bc43dce2ad97f97e5]

下一个弯道中，奔驰继续滑出了黄线，而Tesla继续保持领先

![noteattachment12][853dd0a7b7387e1891e97f9037ce3fb7]

最后我们高速通过弯道：

我们放开让汽车自己控制，不出意外，奔驰继续滑出了黄线，奔向了逆行车道。

Tesla虽然有点擦线，但是它依然保持在道内并且减速后顺利通过了弯道，我们没有人工干预。

![noteattachment13][82a6dcb54d22a94d3c162e1727253622]

对比全程的结论：

Steering Wheel warning：车辆发出的掌握方向盘预警

Driver input：手工干预次数

![noteattachment14][bef0020c6b4236b1e3539441e96306a1]

thedrive的结论：

> 奔驰Drive Pilot：唯一值得一提的是这系统会想方设法保护你不要用它...
我能否信任它？一丢丢而已。我能否理解它？我完全无法理解奔驰怎么能把这样一个系统发布给公众。基本从头到尾都让人厌恶，它开起来就像一个喝醉酒的10岁小屁孩，跟一个14岁的醉酒小青年抢方向盘。在大多数情况中，它开得太危险。

>

>  
>

>

> Tesla的Autopilot：
我喜欢它，尝试几个小时后就能享受它带来的便捷：看着窗外的风景，调节调节驾驶参数。一旦掌握了要点，油门变得不再那么重要。它开起来就像是一个有着良好驾驶培训的少年非常想让你感到印象深刻，也确实开得越来越好。

>

>
如果在正确环境下使用，它确实比单纯人工开车感到安全。在目前ADAS市场上，是无需质疑的最佳系统。它达到了无人驾驶第二级水准，拥有部分第三级的潜力。但是由于预警信息还不完全到位，最好别期望能完全达到第三级。作为一个成年人去合理甄别这些提示信息，你会发现这是市场上最好的系统。

作为对比，这是奔驰的自动辅助驾驶系统传感器以及摄像头布局图：

![noteattachment15][d184ed5b9de46b1b2cbee021590c4fbc]

奔驰的传感器，摄像头硬件比Tesla Autopilot 1.0
多了一倍都不止，规格也更先进，为什么实际路测差了十万八千里？居然可以多次闯过黄线，逆向行驶还不自觉。拿测试人的评价来说benz这自动辅助驾驶根本就不能用，比小孩开得还差，上路就是危害交通安全。而且最悲剧的是如此不堪用的系统，居然还不能升级，只能一路烂到底。

如果拿一句话总结：软件太烂。

别以为把最好的硬件拼凑起来就是最好的整车自动驾驶，这里面需要软件工程师的调教、优化和路测，一个算法的优化可以提升百倍性能。这才是Tesla的核心竞争力所在，也是传统厂商靠着Mobileye脸色吃饭的落魄根源。

所以说到这里，其实这也是Tesla下的战书：既然Tesla只用了传统汽车几乎一样的硬件能搞出来Level
5的自动驾驶，Mobileye的追随者你们有能力也可以搞出来啊，上Lidar也行，只要你价格能卖出去。换句话说，现成品已经在这里，管你逆向工程还是“借鉴”，从Tesla和Elon一直以来的态度，他们非常欢迎同行竞争，共同推进自动驾驶。如果拿Touch
ID 举例，iPhone
5s之前没有一个指纹解决方案兼顾安全和便捷，如今一个手机不带指纹解锁才是另类，习惯了指纹解锁支付的你，还能回到过去手输密码的时代吗？自动驾驶的时代已经到来，不再是科幻。

一点题外话：做内饰，卖牛皮，捣鼓发动机底盘上面国人不一定是日德老牌车厂的对手，也没那么多人才积累，但是要说软件实力，AI，算法，控制...中国人才的数量和质量优势正在逐渐显现。所以国内不少公司打算在自动驾驶上弯道超车，别说还真有可能，看看有多少中国人占领了AI，深度学习的前沿阵地：[AI领域，中国人/华人有多牛？
- AI学人 - 知乎专栏](https://zhuanlan.zhihu.com/p/22995382)

Autopilot 1.0

2014年10月- 至今 （大版本 6.0，6.1，6.2，7.0，7.1，8.0...）

小版本几乎一周两次更新，几十种不同配置的车，能做到如此：

![noteattachment16][b6cd69766d0e598fb7b9da6d8f01ae0f]

这里尤其值得注意的是两点：

1\. Tesla的自动辅助驾驶功能是一步一步解锁的。

在第一篇文章已经有详细介绍，这里继续用这张图，Tesla虽然在所有车上面内置了自动辅助驾驶的硬件，但是真正把完整的自动辅助驾驶交给用户其实是一个不短的过程，而这其中促成这一切的关键是OTA空中更新——最初的Tesla只是拥有道路辅助警告，依靠每一辆Tesla都拥有免费的无线3G／4G
LTE网络，通过OTA来获取最新的软件和功能进一步扩展辅助驾驶的潜力，所以我们口中的Tesla
自动辅助驾驶其实是一整套套件的合集，Tesla每次开放一点，最后完整成一体才有了我们现在看到的自动辅助驾驶Autopilot。这其中每一次更新都经过了内部测试，封测，路测，验证以及更新到实际Tesla车队，再通过车队反馈数据进一步加强自动辅助驾驶：

![noteattachment17][b1ed4134658331ca2d051c15940fc094]

7.0时代的自动辅助驾驶是通过图像识别为主，雷达只是辅助的手段实现，其中图像识别部分便是以Mobileye的软件结合Tesla自己的软件。虽然在当时引起了业界轰动，但是也随之发生过两起自动辅助驾驶没能避免的致命车祸，又引起了非常巨大的争议。而一个月之前的8.0系统对整个技术进行了大换血：改成以雷达为主，图像识别为辅的方式。周边车辆的感知能力提升了6倍，前方障碍物识别也得到了极大更新，避免再次出现类似的道路中障碍物事故。

在8.0的系统面板上你可以看见前方2-3辆车：

![noteattachment18][e350845ac9c20876df0695a599977977]

Autopilot 2.0

2016年10月- 2017年底

所以这次Autopilot 2.0 发布，Tesla同样先普及硬件，再慢慢解锁软件的方式实现，非常类似于Autopilot 1.0 时代从6.0 -
7.0版本升级的方式，一步一步实现第五级全自动驾驶。至于能否实现？有了前面1.0的铺垫和经历作参考，个人觉得可能性还是蛮大的。而Model
3作为下一款明星车能够直接上第五级全自动驾驶，竞争力会大增。

自动驾驶的分级参照美国的标准，其中NHTSA是美国国家公路交通安全管理局，SAE是美国汽车工程师协会

![noteattachment19][35fcfbbc13fbfd7baaa8d3d223558178]

图片来源：[http://www.cheyun.com/content/10421](https://link.zhihu.com/?target=http%3A//www.cheyun.com/content/10421)

我们再来看看最终完成版的自动驾驶2.0实现了什么：

现在新的配置页面已经显示出来，自动驾驶功能被分成了两个选配包：

第一个包：增强辅助驾驶 $5000，交车后激活$6000

车辆会自动跟随车流，保持车道，自动变道而无需人工介入，从高速进出，自动泊车和召唤。这部分基本跟Autopilot 1.0
功能一摸一样，只是硬件的提升让性能更好而已。依然只是Leve 2- Leve3级别的自动辅助驾驶。

![noteattachment20][a8a2969e927a417ab60da7410694aab3]

第二个包：完全自动驾驶 $3000，交车后激活$4000

会激活全部8个摄像头（第一个包只激活4个），可以全自动驾驶，整个过程无需人工干预。而且途径超级充电站时会自动充电（有自动插接的充电桩）！

你只需要在地图上告诉车去哪，或者告诉车“回家”，它便会自动导航到目的地，无论什么路况，红绿灯或者紧急情况。当你到达目的地时，你只需要关上车门，你的车会自动寻找停车位，然后发送坐标到你手机上。

你可以共享你的自动驾驶汽车给亲朋好友，或者通过tesla的网络出租出去帮你赚钱。

![noteattachment21][b61dd5dbce64b3843c664884a4eecb6a]

这些都是明明白白写在配置上面的，只能说太科幻，一想到这些将会在2017年实现，不得不激动一把，尤其是价格上并没有爆表到不能接受，我想最终愿意尝鲜的用户会有不少。

更多详情: <https://zhuanlan.zhihu.com/p/23074176>


---
### ATTACHMENTS
[024bbeb9093f09c492fefb19ea102b7a]: media/Tesla_自动驾驶2.0
[Tesla_自动驾驶2.0](media/Tesla_自动驾驶2.0)
[3057f235bc5ddd0bc43dce2ad97f97e5]: media/Tesla_自动驾驶2-2.0
[Tesla_自动驾驶2-2.0](media/Tesla_自动驾驶2-2.0)
[32a49d5b6c565d5193860dfeaa97aa91]: media/Tesla_自动驾驶2-3.0
[Tesla_自动驾驶2-3.0](media/Tesla_自动驾驶2-3.0)
[35fcfbbc13fbfd7baaa8d3d223558178]: media/Tesla_自动驾驶2-4.0
[Tesla_自动驾驶2-4.0](media/Tesla_自动驾驶2-4.0)
[3a3bcbd101e76afcbee24b38d681fd7a]: media/Tesla_自动驾驶2-5.0
[Tesla_自动驾驶2-5.0](media/Tesla_自动驾驶2-5.0)
[3e5a4959eeb4b1175e0851e3f71be56d]: media/Tesla_自动驾驶2-6.0
[Tesla_自动驾驶2-6.0](media/Tesla_自动驾驶2-6.0)
[42c26c627c5f456ed3f6a1bbdca0dbe8]: media/Tesla_自动驾驶2-7.0
[Tesla_自动驾驶2-7.0](media/Tesla_自动驾驶2-7.0)
[535807a196984d6570f91b45db2117f5]: media/Tesla_自动驾驶2-8.0
[Tesla_自动驾驶2-8.0](media/Tesla_自动驾驶2-8.0)
[5b469e41bb7b23cda388249d1ce12289]: media/Tesla_自动驾驶2-9.0
[Tesla_自动驾驶2-9.0](media/Tesla_自动驾驶2-9.0)
[60780508e00b6cd2779e5edeb4b8d1a2]: media/Tesla_自动驾驶2-10.0
[Tesla_自动驾驶2-10.0](media/Tesla_自动驾驶2-10.0)
[77576f248831f38a883dbd6e96348aec]: media/Tesla_自动驾驶2-11.0
[Tesla_自动驾驶2-11.0](media/Tesla_自动驾驶2-11.0)
[82a6dcb54d22a94d3c162e1727253622]: media/Tesla_自动驾驶2-12.0
[Tesla_自动驾驶2-12.0](media/Tesla_自动驾驶2-12.0)
[853dd0a7b7387e1891e97f9037ce3fb7]: media/Tesla_自动驾驶2-13.0
[Tesla_自动驾驶2-13.0](media/Tesla_自动驾驶2-13.0)
[a8a2969e927a417ab60da7410694aab3]: media/Tesla_自动驾驶2-14.0
[Tesla_自动驾驶2-14.0](media/Tesla_自动驾驶2-14.0)
[b1ed4134658331ca2d051c15940fc094]: media/Tesla_自动驾驶2-15.0
[Tesla_自动驾驶2-15.0](media/Tesla_自动驾驶2-15.0)
[b35bf24fe729832b7645af7dec63303c]: media/Tesla_自动驾驶2-16.0
[Tesla_自动驾驶2-16.0](media/Tesla_自动驾驶2-16.0)
[b61dd5dbce64b3843c664884a4eecb6a]: media/Tesla_自动驾驶2-17.0
[Tesla_自动驾驶2-17.0](media/Tesla_自动驾驶2-17.0)
[b6cd69766d0e598fb7b9da6d8f01ae0f]: media/Tesla_自动驾驶2-18.0
[Tesla_自动驾驶2-18.0](media/Tesla_自动驾驶2-18.0)
[bef0020c6b4236b1e3539441e96306a1]: media/Tesla_自动驾驶2-19.0
[Tesla_自动驾驶2-19.0](media/Tesla_自动驾驶2-19.0)
[d184ed5b9de46b1b2cbee021590c4fbc]: media/Tesla_自动驾驶2-20.0
[Tesla_自动驾驶2-20.0](media/Tesla_自动驾驶2-20.0)
[e350845ac9c20876df0695a599977977]: media/Tesla_自动驾驶2-21.0
[Tesla_自动驾驶2-21.0](media/Tesla_自动驾驶2-21.0)

---
### TAGS
{AI*AG概述}

---
### NOTE ATTRIBUTES
>Created Date: 2018-01-08 16:14:45  
>Last Evernote Update Date: 2018-01-12 15:01:43  
>source: desktop.win  
>source-application: evernote.win32  