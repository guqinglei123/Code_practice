# George Hotz：请收下我的智驾系统代码（附论文）

##  George Hotz：请收下我的智驾系统代码（附论文）

原创 _2016-08-06_
_小猴机器人_[新智元](http://mp.weixin.qq.com/s?__biz=MzI3MTA0MTk1MA==&mid=2651985655&idx=2&sn=b3b175e04b3484930735c91e5a8bea8d&mpshare=1&scene=1&srcid=0116htvYNIchQSBvojfek55L##)

  

1 新智元原创   ** **

 **作者：小猴机器人**

 **  
**

 **【新智元导读】** 我知道以GeoHot的脾气，最终 comma.ai
全套AI模型的代码肯定会被他开源，但我没想到会这么快，而且我也没想到这么完备，几乎毫无保留，多达80G的驾驶数据，模型以及论文全部开放，黑客精神在这位老兄身上的到了淋漓尽致的体现。本文结合GeoHot此次发表的论文和代码，讲解此前为Bloomberg演示时所采用的深度学习框架。代码采用Python语言编写，涉及tensorflow，anaconda，cv2等多个常用深度学习常用开发框架，是不可多得的学习材料。

  

 ** ******

  

##

桀骜不逊的自动驾驶破局者  

  

[ 智驾深谈的第一期，就是关于这位老兄George
Hotz，江湖人称GeoHot，“声名狼藉的”iPhone和PlayStation破解者，做过多家IT帝国的被告。](http://mp.weixin.qq.com/s?__biz=MzI3MTA0MTk1MA==&mid=2651982826&idx=1&sn=0bb613aa8b1eed41b8fb6943abbf4cee&scene=21#wechat_redirect)几个月前研究上了自动驾驶技术，紧接着就公然挑战Tesla、Google和Mobileye，自嘲是个“智痴（I'm
an
Idiot.）”，而其他家的水平，只能算是智障。Musk发邮件邀请他去Tesla，被他拒了，声称自己年底就要出不到一万人民币的产品，而且效果绝对秒杀。四月初拿到了310万美元融资，并在拉斯维加斯正常车流中，GeoHot演示了目前的技术进展，完成度颇高，只用了一个前置摄像头，以及一个草草贴在前保险杠上的毫米波雷达。

  

##  ****

深度学习端到端：开源概况  

  

此前我提过，目前的自动驾驶技术可以划分为两类，一种是感知-决策-
控制然后不断闭环，每个模块用不同的方法力争最好，很多情况下需要专家提供基于经验的规则。另一种则是GeoHot正在采用的办法，叫做End-to-
End，端到端方法，指以摄像头的原始图像作为输入，直接输出车辆的速度和方向，中间用某种数学模型来拟合逼近最优驾驶策略，目前常用的就是深度学习模型。

  

本次GeoHot开源的东西非常丰富，包括下面几个内容：

  

  * 七小时十五分的高速公路图像数据

  * 两种使用该数据的机器学习实验方法

  * 一篇利用深度学习RNN网络进行自动驾驶的论文 **（在新智元公众平台回复0806下载）**

  * 整套试验代码包括tensorflow，anaconda，keras等常用工具的用法

  

这些材料，足够读者复现GeoHot为Bloomberg演示的效果，比起此前Mobileye或者Nvidia光发布论文前进了一大步。



##  ****

深度学习端到端：数据准备  

                         
  

驾驶数据是本次开源的重要组成部分，不但包括前视摄像头裁剪的数据，共计7.25小时，分为11个视频，160*320大小，并且还包括了GeoHot那辆讴歌采集的转向、制动、速度以及惯导数据，以及图像输入和控制输出的同步时间戳数据。本次发布的论文主要聚焦在通过图像输入来学习控制转向和速度，GeoHot将图像缩小为80*160并将像素值归一化。

  

##  ****

深度学习端到端：模型介绍  

  

  

目前深度学习用于自动驾驶可以大概分为两类，一类是收集驾驶数据，离线训练模型，不断逼近人类驾驶员；另一类是在模拟器中，利用Q函数，不断自我决策和试错来提高驾驶技术。由于真正图片的复杂以及输出命令的连续性，使得现实世界中能够得到好结果比较困难，所以我们目前见到的很多都是在模拟器中尝试。

  

  

本次GeoHot开源的是第一种方法，且是在真实道路上经过实测的。其基本原理是，将摄像头获得的图像数据，利用Autoencoder编码（如上图锁匙，期间还用到最近很火的GAN），然后用一个RNN深度网络来从人类驾驶数据中学习，最终预测下一步操作。

  

##  ****

深度学习端到端：代码概要  

  

  

从代码结构上来看，大概可以分为数据、模型和训练框架三部分，其中模型部分包括了autoencoder和RNN，训练框架则以server.py文件作为入口。

  

结语  

  

我非常惊讶于GeoHot做出这次开源的决定，看过论文和代码之后，相信复现他们演示结果并不是一件很难的事情，算是让大部分想要尝试深度智驾模型而又无从下手的人得到了福利。那么开源是否会对整个智驾产业带来影响呢？如果你觉得GeoHot还不够强的话，Google未来开源了会不会有影响呢？谁也很难说智驾不会像智能手机一样，成为下一个兵家必争之地。

  

* * *

  

  

  

 **新智元Top10智能汽车创客大赛招募！**

  

新智元于7月11日启动2016年【新智元100】人工智能创业公司评选，在人工智能概念诞生60周年之际，寻找中国最具竞争力的人工智能创业企业。

  

智能驾驶技术是汽车行业的重点发展方向之一，同时也是人工智能相关产业创新落地的重要赛道之一。为此新智元联合北京中汽四方共同举办“新智元Top10智能汽车创客大赛”，共同招募智能汽车相关优质创业公司，并联合组织人工智能技术专家、传统汽车行业技术专家、关注智能汽车领域的知名风投机构，共同评审并筛选出Top
10进入决赛，在2016年10月16日“国际智能网联汽车发展合作论坛”期间，进行路演、颁奖及展览活动。

 **  
**

 **如何参加【新智元Top10智能汽车创客大赛】评选**

  

点击文章下方阅读原文，在线填写报名表。该报名表为参加评选必填资料。

  

如有更多介绍资料（例如BP等），可发送至xzy100@aiera.com.cn，邮件标题请注明公司名称。如有任何咨询问题，可联系微信号Kunlin1201。

  

  

  

 **评选活动时间表**

  

创业企业报名期：即日起至2016年8月31日

专家评委评审期：2016年9月

入围企业公布期：2016年10月18日

  

  

 **微信号：AI_era100**

  

长按二维码关注新智元100，发现中国最具竞争力人工智能初创企业

  

 **点击阅读原文，填写【新智元100】报名表**

[阅读原文](http://mp.weixin.qq.com/s?__biz=MzI3MTA0MTk1MA==&mid=2651985655&idx=2&sn=b3b175e04b3484930735c91e5a8bea8d&mpshare=1&scene=1&srcid=0116htvYNIchQSBvojfek55L##)


---
### ATTACHMENTS
[04963f167306cf589b2f88b83028ac82]: media/0.jpg
[0.jpg](media/0.jpg)
>hash: 04963f167306cf589b2f88b83028ac82  
>file-name: 0.jpg  

[591cd06bc2f940b400e420fd109eb4ac]: media/0-2.jpg
[0-2.jpg](media/0-2.jpg)
>hash: 591cd06bc2f940b400e420fd109eb4ac  
>file-name: 0.jpg  

[5998c4d98f7cc28a5edcff8ea119a644]: media/0-3.jpg
[0-3.jpg](media/0-3.jpg)
>hash: 5998c4d98f7cc28a5edcff8ea119a644  
>file-name: 0.jpg  

[a120aadd6e2f532d4d3259bd707db6e0]: media/0-4.jpg
[0-4.jpg](media/0-4.jpg)
>hash: a120aadd6e2f532d4d3259bd707db6e0  
>file-name: 0.jpg  

[add266127edec14a00f46f25f2727693]: media/0-5.jpg
[0-5.jpg](media/0-5.jpg)
>hash: add266127edec14a00f46f25f2727693  
>file-name: 0.jpg  

[cff8b16daf56e4678cc5132f1550fa0a]: media/0.png
[0.png](media/0.png)
>hash: cff8b16daf56e4678cc5132f1550fa0a  
>file-name: 0.png  

[e09b91727e42b1fae60ae42680bd78eb]: media/0-6.jpg
[0-6.jpg](media/0-6.jpg)
>hash: e09b91727e42b1fae60ae42680bd78eb  
>file-name: 0.jpg  

[e580ef43575c3b930fe193a0d77b95e2]: media/0-7.jpg
[0-7.jpg](media/0-7.jpg)
>hash: e580ef43575c3b930fe193a0d77b95e2  
>file-name: 0.jpg  

[ebaea32ba8313d99ca9fedea39026c1b]: media/0.gif
[0.gif](media/0.gif)
>hash: ebaea32ba8313d99ca9fedea39026c1b  
>file-name: 0.gif  

[fedf5ece467bf9049d376a91ad38eb57]: media/0-8.jpg
[0-8.jpg](media/0-8.jpg)
>hash: fedf5ece467bf9049d376a91ad38eb57  
>file-name: 0.jpg  


---
### TAGS
{微信}  {AI*AG概述}

---
### NOTE ATTRIBUTES
>Created Date: 2018-01-15 16:56:42  
>Last Evernote Update Date: 2018-01-17 17:36:21  
>source: desktop.win  
>source-url: http://mp.weixin.qq.com/s?__biz=MzI3MTA0MTk1MA==  
>source-url: &  
>source-url: mid=2651985655  
>source-url: &  
>source-url: idx=2  
>source-url: &  
>source-url: sn=b3b175e04b3484930735c91e5a8bea8d  
>source-url: &  
>source-url: mpshare=1  
>source-url: &  
>source-url: scene=1  
>source-url: &  
>source-url: srcid=0116htvYNIchQSBvojfek55L#rd  
>source-application: 微信  