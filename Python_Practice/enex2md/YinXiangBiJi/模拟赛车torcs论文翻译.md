# 模拟赛车torcs论文翻译

  

# 模拟赛车torcs论文翻译

2017-07-26 22:24 [机器人](http://www.sohu.com/tag/60035)
_/_[游戏](http://www.sohu.com/tag/49789) _/_[客户端](http://www.sohu.com/tag/59754)

摘要：本手册介绍了模拟赛车锦标赛的比赛软件，在进化计算领域和计算智能与游戏领域的大型会议上举办的国际比赛。
它提供了架构的概述、安装软件的说明以及运行包中提供的简单驱动程序、传感器和执行器的描述。

1.介绍：

本手册介绍了模拟赛车锦标赛的比赛软件，在进化计算领域和计算智能与游戏领域的大型会议上举办的国际比赛。

比赛的目标是为赛车设计一个控制器，用于首次单独在未知轨道比赛中同其他赛车比赛。
控制器通过多个传感器来感知赛车环境，这些传感器描述了汽车状态（燃料水平，发动机转速，当前档位等），汽车周围环境的相关特征（例如轨道极限，靠近障碍物
的位置）和当前游戏状态（圈时，圈数等）。 控制器可以执行典型的驾驶动作（离合器，换档，加速，断开，转向轮等）。
锦标赛的描述，包括规则和条例，可以在http://cig.sourceforge.net/找到。

冠军平台建立在开放赛车模拟器（TORCS）之上，这是一款先进的开源赛车模拟器，提供完整的3D可视化，先进的物理引擎和准确的汽车动力学考虑牵引力，
空气动力学，油耗等。

在本手册的其余部分中，我们概述了架构，安装软件的说明以及运行软件包中提供的简单驱动程序，传感器和执行器的说明。

2竞赛软件的架构

开放赛车模拟器（TORCS）作为一个独立应用程序，其中机器人被编译为单独的模块，当发生比赛时被加载到主内存中。这种结构有三个主要的缺点。首先，由于机器人执行被阻止，比赛不是实时的，如果机器人需要很长时间来决定要做什么，它会阻止所有其他人。第二，由于机器人和模拟引擎之间没有分离，机器人可以完全访问定义轨道和比赛当前状态的所有数据结构。因此，每个机器人可以使用不同的信息来实现其驾驶策略。此外，机器人可以分析比赛的完整状态（例如，轨道结构，对手位置，速度等）来规划他们的行动。因此，计算智能方法之间的公平比较是困难的，因为不同的方法可能会访问不同的信息。最后，TORCS将编程语言的选择限制为C
/ C ++，因为机器人必须被编译为使用C ++编写的主TORCS应用程序的可加载模块。

比赛软件在三个方面扩展了原始的TORCS体系结构。 首先，它将TORCS构建为客户端 -
服务器应用程序：机器人作为外部进程运行，通过UDP连接连接到比赛服务器。
第二，它实时增加：每个游戏tic（大致对应于20ms的模拟时间），服务器将当前感觉输入发送到每个机器人，然后等待10ms（实时）从机器人接收动作。
如果没有动作到达，则继续进行模拟，并使用上一次执行的动作。
最后，竞赛软件在驱动程序代码和竞赛服务器之间建立物理上的分离，构建抽象层，传感器和执行器模型，（i）给出了用于机器人的编程语言的完全自由选择，（ii）限制只能访问设计师定义的信息。

比赛软件的架构如图1所示。游戏引擎与原始的TORCS相同，主要修改在于新的server-bot，称作scr-server，它可以管理游戏与client-
bot之间的UDP连接。 比赛涉及每个客户端的server-bot; 每个服务器机器人在比赛服务器的单独端口上侦听。一开始，每个client-
bot将其自身识别为相应的server-bot建立连接。 然后，随着比赛开始，每个server-
bot将当前的感官信息发送给其客户端，并等待10秒（实时）的动作。 每个游戏tic，对应于20ms的模拟时间，服务器更新比赛的状态，发送回客户端。
客户端可以通过向服务器发送特殊操作来请求比赛重新启动。

3安装比赛服务器

为了向TORCS提供一个非常易于访问的界面，我们开发了两个模块，以客户端/服务器架构运行TORCS。
服务器是通过提供一种名为scr服务器的特定机器人驱动程序开发的，该服务器不是具有自己的智能，而是将游戏状态发送到客户端模块并等待回复，即由控制器执行的动作。
所以要开始比赛，我们首先需要安装TORCS和这个包中提供的比赛服务器包。

3.1Linux版本

从SourceForge下载一体化TORCS
1.3.4源代码包（http://sourceforge.net/projects/torcs/），或者直接点这里（http://prdownloads.sourceforge.net/torcs/torcs-1.3.4.tar.bz2?download），为了编译服务器，你需要：

硬件加速OpenGL（通常由您的Linux发行版提供）

GLUT 3.7或FreeGlut（优于GLUT用于全屏幕支持）

PLIB 1.8.5 version

OpenAL

libpng和zlib（通常由您的Linux发行版提供）

FreeALUT

用tar xfvj torcs-1.3.4.tar.bz2命令解压torcs-1.3.4.tar.bz2，自动创建torcs-1.3.4文件夹

从CIG项目页面http://sourceforge.net/projects/cig/下载包含TORCS源补丁的软件包scr-linux-
patch.tgz，或者从这里直接下载（https://sourceforge.net/projects/cig/files/SCR20Championship/Server%20Linux/）。在您的基本TORCS目录（您解压缩torcs-1.3.4.tar.bz2的位置）中解压scr-
linux-patch.tgz安装包。这将创建一个名为scr-patch的新目录。进入scr-patch目录并用sh
do_patch.sh运行do_patch.sh脚本（运行do_unpatch.sh来恢复修改）。进入父目录（就是你解压torcs-1.3.4.tar.bz2的地方）并执行

$ ./configure

$ make

$ make install

$ make datainstall

此时，您可以通过执行命令“torcs”来检查竞赛软件是否已正确安装，接着在主窗口选择：

Race -> Quick Race->Con gure Race->Accept

如果一切安装正确，您应该在右侧的“Not Selected Player”列表中找到十个scr server bot的实例。

有关安装过程的更多信息，请参见此处（http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=3#linux-
src-all）。 有关更多信息，请访问http://www.berniw.org/（TORCS->Installation --from left
bar）

3.2 Windows 版本

有可能从Windows编译TORCS，但可能相当具有挑战性。 因此，我们提供Windows的竞争软件的二进制分发。
在这种情况下，安装竞赛软件首先从https://sourceforge.net/projects/torcs/files/torcs-
win32-bin/下载TORCS 1.3.4 Windows安装程序，然后进行安装。
然后，从CIG项目页面http://sourceforge.net/projects/cig/下载文件scr-win-patch.zip，或从这里直接下载。
将包解压到TORCS主目录中。 在拆包过程中，您将被要求覆盖一些现有的文件，对所有的文件进行回答。
此时，您应该能够从安装目录或从开始菜单启动wtorcs.exe来检查竞赛软件是否正确安装; 然后，从TORCS主窗口中选择，

Race -> Quick Race->Con gure Race->Accept

如果一切安装正确，您应该在右侧的“未选择的播放器”列表中找到十个scr_server bot实例。

3.3 Mac OsX

比赛的C ++客户端是可以从源代码编译的独立控制台应用程序。
该软件包可以从CIG项目页面http://sourceforge.net/projects/cig/下载，也可以从这里直接下载（https://sourceforge.net/projects/cig/files/SCR%20Championship/Client%20C%2B%2B/）。

4C++客户端

比赛的C ++客户端是可以从源代码编译的独立控制台应用程序。
该软件包可以从CIG项目页面http://sourceforge.net/projects/cig/下载，也可以从这里直接下载（https://sourceforge.net/projects/cig/files/SCR%20Championship/Client%20C%2B%2B/）。

4.1编译为Linux

解压客户端软件包scr-client-cpp.tgz创建目录scr-client-cpp。 然后在打开客户端的目录中打开一个终端，然后键入make进行编译。
编译过程应该没有任何错误或警告结束，您现在应该有一个名为client的可执行文件。 要启动客户端，请键入

$ ./client host:<ip> port:<p> id:<client-id> maxEpisodes:<me>

maxSteps:<ms> track:<trackname> stage:<s>

其中<ip>是运行TORCS竞赛服务器的机器的IP地址（默认为localhost）;
<p>是服务器机器人正在侦听的端口，典型值在3001到3010之间（默认值 是3001）; <client-id>是您的机器人ID（默认为SCR）;
<me>是要执行的学习回合的最大数量（默认值为1）; <ms>是每回合中最大控制步数。 （默认值为0，即无限制步数）;
<trackname>是机器人比赛轨迹的名称1（默认值未知）;
<s>是一个整数，表示机器人参与的竞争的当前阶段：0是热身，1是合格，2是比赛，3是未知（默认是未知）。 所有参数都是可选的（如果没有指定，则使用默认值）

4.2编译Windows

解压客户端软件包scr-client-cpp.tgz创建目录scr-client-cpp。 该包提供了DevC
++项目文件（http://www.bloodshed.net/devcpp.html），但可以使用任何C ++开发工具/ IDE。
要在Windows上编译客户端，请按照同一个文件中提供的说明取消对client.cpp的第二行的注释。
该软件包还包含使用该系统库所需的系统库WS2_32.lib，它需要
WinSock功能。客户端应该编译没有任何错误或警告，生成client.exe可执行文件。 要启动客户端打开MS-DOS控制台并键入：

client.exe host:<ip> port:<p> id:<client-id> maxEpisodes:<me>

maxSteps:<ms> track:<trackname> stage:<s>

其中<ip>是运行TORCS竞赛服务器的机器的IP地址（默认为localhost）;
<p>是服务器机器人侦听的端口，典型值在3001到3010之间（默认值为3001）; <client-id>是您的机器人ID（默认为SCR）; <me>是
要执行的最大学习情节数（默认值为1）; <ms>是每集中最大控制步数。 （默认值为0，即无限制步数）;
<trackname>是机器人将竞争的轨道的名称2（默认值未知）;
<s>是一个整数，表示机器人参与的竞争的当前阶段：0是热身，1是合格，2是比赛，3是未知（默认是未知）。 所有参数都是可选的（如果未指定，则使用默认值）。

4.3自定义您自己的驱动程序

要编写自己的驱动程序，必须扩展客户端源码中提供的BaseDriver类，并且必须实现这些方法：

void init(float *angles) ,
该方法在比赛开始前调用，可用于定义轨道传感器的自定义配置（参见表2）：所有19个范围的传感器的所需角度（wrt car axis）必须设置在
参数angles

string drive(string sensors),传感器表示驾驶员感觉到的当前游戏状态;
该方法返回一个表示所采取行动的字符串（有关传感器和执行器的详细信息，请参见第6节)

void onShutdown(), 在比赛结束时调用的方法，在驱动程序模块卸载之前;

void onRestart(), 该方法在赛车重启时根据驱动程序请求（此功能应用于释放分配的内存，关闭打开的文件，保存到磁盘等）

此外，类属性stage和trackName分别包含比赛的当前阶段（预热，限定，比赛或未知）和当前曲目的名称（舞台和曲目名称必须使用相应的命令指定
客户端的线路选项）。 该信息可用于保存有关当前轨道的有用信息，并在竞争的不同阶段采用不同的策略。

作为示例，文件SimpleDriver.cpp实现了一个非常简单的驱动程序，默认情况下使用它构建客户端可执行文件。
因此，构建客户端可执行文件来运行自己的驱动程序：

on Windows,
取消注释client.cpp的前两行，并将__DRIVER_CLASS__和__DRIVER_INCLUDE__定义设置为已实现的驱动程序类的名称和同一驱动程序类的头文件。

on Linux , 在Makefile中将DRIVER_CLASS和DRIVER_INCLUDE设置为已实现的驱动程序类的名称和同一驱动程序类的头文件。

5 java客户端

Java客户端与C ++版本类似。 它是一个独立的控制台应用程序，可以从源代码编译。
该软件包可以从CIG项目页面http://sourceforge.net/projects/cig/下载，也可以从这里直接下载（https://sourceforge.net/projects/cig/files/SCR%20Championship/Client%20Java/）。

5.1 运行java客户端

首先，解压包scr-client-java.tgz来创建目录scr-client-java来保存源代码。 要编译客户端，请转到目录src并键入，

$ javac -d ../classes scr/*.java

要使用简单的控制器启动Java客户端，请转到目录classes并键入，

$ java scr.Client scr.SimpleDriver host:<ip> port:<p> id:<client-id>

maxEpisodes:<me> maxSteps:<ms> verbose:<v> track:<trackname> stage:<s>

其中scr.SimpleDriver是以软件提供的控制器的实现为例（可以用自定义实现替换）;其中<ip>是运行TORCS竞赛服务器的机器的IP地址（默认为localhost）;
<p>是服务器机器人侦听的端口，典型值在3001到3010之间（默认值为3001）; <client-id>是您的机器人ID（默认为SCR）;
<me>是要执行的学习剧集的最大数量（默认值为1）; <ms>是每集中最大控制步数。 （默认值为0，即无限制步数）;
<v>控制详细程度级别，可以打开或关闭（默认值为off）; <trackname>是机器人比赛轨迹的名称3（默认值未知）;
<s>是一个整数，表示机器人参与的竞争的当前阶段：0是热身，1是合格，2是比赛，3是未知（默认是未知）。所有参数都是可选的（如果没有指定，则使用默认值）。

5.2定制自己的驱动程序

Java客户机类似于C ++客户端。 要编写自己的驱动程序，必须通过提供以下方法来实现Controller接口：

public float [] initAngles（）。
该方法在比赛开始之前被调用，并且可以用于定义轨道传感器的定制配置（参见表2）：该方法返回每个19个所需角度（w.r.t car axis）的向量
的19个测距仪。

public Action control(SensorModel
sensors)。公共动作控制（SensorModel传感器），其中传感器表示驾驶员感觉到的当前游戏状态; 该方法返回所采取的行动（见第6节）;

public void shutdown()。在比赛结束时调用的方法，在驱动程序模块之前卸载

public void reset（）。在驱动程序请求重新启动比赛时调用的方法（此功能应用于释放分配的内存，关闭打开文件，保存到磁盘等）。

此外，class属性stage和trackName分别包含比赛的当前阶段（预热，限定，比赛或未知）以及当前曲目的名称（舞台和曲目名称必须使用相应的命令指定）
客户端的线路选项）。 该信息可用于保存有关当前轨道的有用信息，并在竞争的不同阶段采用不同的策略。
作为示例，文件SimpleDriver.java实现了一个非常简单的驱动程序

6传感器和执行器

比赛软件在游戏引擎和驱动程序之间建立了物理上的分离。因此，为了开发机器人，不需要任何有关TORCS引擎或内部数据结构的知识。
驾驶员的看法和可用的动作由竞赛设计师定义的传感器和执行器层定义。
在这场比赛中，司机投入包括一些有关汽车状态（当前档位，燃料等级）的数据，比赛状态（当前圈数，跑步距离等）和汽车周围环境（轨道边界，障碍物等）。
行动允许典型的驾驶行为。

6.1传感器

机器人通过多个传感器读数感知赛车环境，这些传感器读数提供关于周围游戏环境（例如，轨道，对手，速度等）的信息以及比赛的当前状态（例如，当前圈数
和比赛中的位置等）。 表1和表2报告了可用传感器的完整列表以及说明。
请注意，对手传感器（表1）提供的读数没有考虑到轨道的边缘，即，即使路径穿过轨道的边缘，也会计算“随着乌鸦飞行”的车辆之间的距离。

6.2执行机构

机器人通过相当典型的一组致动器（即方向盘，加油踏板，制动踏板和变速箱）来控制游戏中的汽车。 此外，还可以使用元动作来请求重新启动服务器。
表3详细列出了可用的行动及其表示。

7运行竞争服务器

安装TORCS和提供的服务器机器人（Windows或Linux版本）后，您可以开始开发自己的机器人，扩

展其中一个提供的客户端模块。
当您想要运行自己的机器人时，您必须启动TORCS并开始比赛，那么您必须使用自己编程的机器人启动客户端扩展，因此您的驱动程序bot将开始在比赛中运行。
在TORCS中有几种竞赛模式可用，但客户端 – 服务器模块仅支持两种模式：

1）.一次允许单个机器人竞赛的练习模式；

2）.快速竞赛模式，允许多个机器人竞争

但是，在与TORCS开赛之前，您需要确定以下事项：

1）您必须选择要在其上运行比赛的赛道

2）您需要添加一个scr_server x bot来比赛参与者，最终还是要作为对手的其他机器人

3）你必须确定比赛将持续多少圈或多少公里

4）您可能需要选择所需的显示模式

在TORCS中，所有上述选项都存储在一组XML配置文件中（每种种族模式一种）。 在Linux配置文件被创建之前，游戏第一次启动，并位于$ HOME /
.torcs / config / raceman /，其中$ HOME是您的主目录。 在Windows下，配置文件位于安装TORCS的目录下的
config raceman 目录中

7.1通过GUI配置TORCS赛

配置竞赛选项的最简单方法是使用TORCS GUI。 每个比赛模式都可以完全配置，从TORCS的主菜单中选择：

Race->Quick Race [or Practice]->Configure Race

一旦您更改了特定比赛模式的配置，所有更改将由TORCS自动存储相应的配置文件。

选择轨道。 在第一个屏幕中，您可以选择游戏中可用的任何轨迹，然后单击接受以移动到下一个屏幕。

选择机器人。 第二个屏幕允许选择将参加比赛的机器人。
请注意，在实践模式中，只允许一个机器人，因此为了添加机器人，您首先要取消选择当前选择的机器人（如果有的话）。
首先，您必须确保一个竞争机器人scr_server x位于所选驱动程序的列表中（在屏幕的左侧）。
然后，在快速竞速模式下，您可以从右侧的列表中添加其他驱动程序（代表随游戏提供的所有bot驱动程序）。
当添加机器人时，请注意他们使用的汽车型号：TORCS中有几种类型的汽车具有不同的功能，您可能需要确保只有具有相同汽车的驾驶员才能对抗。
请注意，scr_server使用car1-trb1，而使用同一辆车的其他机器是：

tita 3

berniw 3

olethros 3

lliaw 3

inferno 3

bt 3

当您选择了所有将在比赛中的驱动程序时，您可以单击接受并移动到下一个屏幕

设置比赛长度和显示模式。 在最终的配置屏幕中，您可以将比赛长度设置为要覆盖的距离（公里）或完成的圈数。 最后，您可以选择两种显示模式选项：正常或仅结果。
正常模式允许您从一个机器人驱动程序的角度或作为外部观众观看比赛。
在这种显示模式下，时间速度可以加快到正常速度的四倍，也就是说在15秒内可以看到1分钟的比赛。
在结果唯一模式下，您不会看到比赛，而只能在圈速（实践模式）或比赛的最终结果（快速比赛模式）中看到。
然而，这种模式可以让你运行模拟更快：时间速度可以加快20倍（甚至更多），即1分钟的比赛可以在3秒内模拟.

7.2通过配置文件配置TORCS

上述所有比赛设置都可以配置为直接编辑配置文件。 在TORCS中，每个种族都是自己的XML配置文件。 实践的设置存储在practice.xml中，而Quick
Race的设置位于quickrace.xml中。

选择轨道。 要选择轨道，请在XML le中找到 Tracks“部分，其中将包含以下部分:

<section name="1">

<attstr name="name" val="TRACK-NAME"/>

<attstr name="category" val="TRACK-CAT"/>

</section>

您应该（i）将TRACK-ROAD替换为所需轨道类别（即道路，椭圆形或泥土）; （ii）将TRACK-NAME替换为所需轨道的名称（例如，aalborg）。
有关TORCS中安装的轨道的完整列表，您可以看到安装TORCS的三个主要目录（track / road /，tracks / oval /和tracks /
dirt /）下组织的所有目录的列表。 在Windows下，您可以在主torcs目录中找到它们，在Linux下，可以在/ usr / local /
share / games / torcs /或不同的地方找到track目录，具体取决于您的分布

选择bots要选择机器人，您应该修改XML文件中的 Drivers“部分，特别是在本节中，您应该可以找到以下元素的列表：

<section name="N">

<attnum name="idx" val="IDX"/>

<attstr name="module" val="NAME"/>

</section>

其中N表示您正在编辑将在比赛中的第N个机器人。 IDX是您要添加的机器人实例的索引：对于游戏提供的一些机器人，有几个实例（例如，bt机器人有几个实例：bt
1，bt 2，...）; 当机器人只有一个实例IDX应该设置为1）。 应该使用您要添加的bot名称替换NAME，而不使用实例的索引（例如，添加bt 7
bot，您应该以NAME简单地使用bt和7作为IDX）。 可以在与之前介绍的磁带目录相同的位置的驱动程序/目录中找到可用的驱动程序列表。

设置比赛长度和显示模式。 要更改比赛长度和显示模式，您必须修改“快速比赛”或“练习”部分（具体取决于您要设置的比赛类型）。 特别是你应该改变以下几行:

...

<attnum name="distance" unit="km" val="DIST"/>

...

<attnum name="laps" val="LAPS"/>

...

<attstr name="display mode" val="MODE"/>

…

其中DIST应该是公里所需的种族长度，如果使用圈数作为种族长度，则为0。 因此，LAPS应该是所需的圈数，如果距离用作种族长度，则应为0。
最后MODE只是正常或结果

7.3开始比赛！

一旦你正确设定TORCS，你就可以运行自己的机器人了。 从主菜单中选择：

Race->Quick Race [or Practice]->Configure Race

您应该看到TORCS屏幕应该停止报告行:

Initializing Driver scr_server 1...

操作系统终端应该在端口3001上报告等待请求。这意味着服务器bot_server正在等待您的客户端开始比赛。
比赛开始后，可以通过按ESC键从用户中断，然后从菜单中选择中止比赛。 如果用户已经中断了比赛的距离/圈数限制，比赛结束将被通知给客户。
请注意，在游戏菜单中选择“退出游戏”选项，而不是“中止竞赛”选项，比赛结束将不会被正确通知给客户，从而阻止他们执行干净的关机

7.4以文本模式运行TORCS

没有图形可以运行TORCS，即没有任何GUI来启动比赛。
当您计划以批处理模式运行实验（或一系列实验），并且不需要使用GUI设置实验时，此运行模式可能很有用。 使用
-r“命令行选项，可以指定比赛配置文件a以文本模式运行TORCS，如下所示：

C:> wtorcs.exe -r race_config.xml (on Windows)

$ torcs -r race_config.xml (on linux)

TORCS将自动运行由race_config.xml文件定义的比赛，可以使用GUI进行配置或直接编辑它（如上一节所述）。

7.5禁用燃油，伤害和车速限制

要在TORCS中执行很长的实验，有必要禁用一些可以停止或改变模拟的功能。
应禁用燃料消耗和损坏的原因有两个：一是评估过程中增加噪音，因为燃油或损坏量不同的两个人性能不同; 第二，如果燃油很低或者汽车从比赛中脱离的伤害太高。
如果需要很多时间才能完成一圈，laptime限制从一场比赛中移除一辆汽车。 如果使用特定的参数配置，汽车性能非常差，可能会发生这种情况。

要禁用这些功能，可以使用这些命令行参数运行修补版本的TORCS：

C:> wtorcs.exe -nofuel -nodamage -nolaptime (on Windows)

$ torcs -nofuel -nodamage -nolaptime (on Linux)

当然，每个这个论点都可以单独使用或与其他参数组合使用。

7.6时间限制

在开发你的司机时，请记住，比赛是实时的。 因此，服务器在客户端有超时时间答案：您的驱动程序应该执行一个操作（即返回操作字符串）10ms以便与服务器保持同步。
如果您的机器人速度较慢，您可能会放弃与服务器的同步，因此您需要知道如何避免这种情况发生。 也可以通过以下命令行选项指定自定义超时：

C:> wtorcs.exe -t <timeout> (on Windows)

$ torcs -t <timeout> (on Linux)

其中timeout是所需的超时（以纳秒为单位）。

7.7噪音传感器

默认情况下，传感器模型中的测距仪不会嘈杂。 然而，在竞争中，将使用噪声测距仪（根据表1和表2中的规格）。 要启用有噪声的测距仪，可以使用以下命令行选项：

C:> wtorcs.exe -noisy (on Windows)

$ torcs -noisy (on Linux)

8更多信息和支持

有关锦标赛和比赛软件的更多信息，请访问http://cig.sourceforge.net/。

要报告错误，问题或只是为了帮助，发送电子邮件至scr@geccocompetitions.com。

以下网站还提供了其他信息：

开车赛车模拟器主页http://www.torcs.org

http://www.berniw.org/，Bernhard Wymann的页面，其中包含有关TORCS的大量信息[
__返回搜狐，查看更多](http://www.sohu.com/?strategyid=00001 "点击进入搜狐首页")

声明：本文由入驻搜狐号的作者撰写，除搜狐官方账号外，观点仅代表作者本人，不代表搜狐立场。

阅读 ( _92_ )

[不感兴趣](http://www.sohu.com/a/160344970_680233#)
[__投诉](https://passport.zhan.sohu.com/passport/sohu/login-
jumpto?callback=https://yonghufankui.kuaizhan.com/clubpc/topics/WhOlhDSItmL75kIf#!/comments/0)

  


---
### ATTACHMENTS
[bce19d97d7ebe176b3a2732293948688]: media/36763151895847d69c4238805cc03b53_th.pn.jpg
[36763151895847d69c4238805cc03b53_th.pn.jpg](media/36763151895847d69c4238805cc03b53_th.pn.jpg)
>hash: bce19d97d7ebe176b3a2732293948688  
>source-url: http://img.mp.sohu.com/upload/20170727/36763151895847d69c4238805cc03b53_th.png  
>file-name: 36763151895847d69c4238805cc03b53_th.png.jpg  

---
### NOTE ATTRIBUTES
>Created Date: 2018-03-07 15:19:09  
>Last Evernote Update Date: 2019-04-06 02:07:17  
>author: 刘倪  
>source: web.clip  
>source-url: http://www.sohu.com/www.sohu.com/a/160344970_680233  
>source-application: evernote.win32  