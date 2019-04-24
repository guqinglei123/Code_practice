# 使用Keras和DDPG玩赛车游戏（自动驾驶） - 简书

[
![noteattachment1][4c7bbafe27adc892f3046e6978459bac]](https://www.jianshu.com/)
[ __写文章](https://www.jianshu.com/writer#/) [
注册](https://www.jianshu.com/sign_up) [登录](https://www.jianshu.com/sign_in)

[__](https://www.jianshu.com/p/a3432c0e1ef2)

  * [ 首页 __](https://www.jianshu.com/)
  * [ 下载App __](https://www.jianshu.com/apps?utm_medium=desktop&utm_source=navbar-apps)
  * __

[ ×](https://www.jianshu.com/apps/download?utm_source=sbc)

# 使用Keras和DDPG玩赛车游戏（自动驾驶）

[
![96](https://upload.jianshu.io/users/upload_avatars/2422746/a597dc58020c.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/96/h/96)
](https://www.jianshu.com/u/66f24f2c0f36)

[treelake](https://www.jianshu.com/u/66f24f2c0f36)
[__关注](https://www.jianshu.com/p/a3432c0e1ef2)

2016.10.22 15:46* 字数 4381 阅读 10240评论 26喜欢 45

> [Using Keras and Deep Deterministic Policy Gradient to play
TORCS](https://link.jianshu.com/?t=https://yanpanlau.github.io/2016/10/11/Torcs-
Keras.html)——300行[python代码](https://link.jianshu.com/?t=https://github.com/yanpanlau/DDPG-
Keras-
Torcs)展示DDPG(基于Keras)——[视频](https://link.jianshu.com/?t=https://youtu.be/JqQd5Bqgedo)  
>  可以先看[新手向——使用Keras+卷积神经网络玩小鸟](https://www.jianshu.com/p/3ba69493f020)

![noteattachment2][d2a12a5c437fadcf2af5e3f03e86d24f]

### 为什么选择TORCS游戏

  * 《The Open Racing Car Simulator》（ **TORCS** ）是一款开源3D赛车模拟游戏
  * 看着AI学会开车是一件很酷的事
  * 可视化并考察神经网络的学习过程，而不是仅仅看最终结果
  * 容易看出神经网络陷入局部最优
  * 帮助理解自动驾驶中的机器学习技术

### 安装运行

  * 基于Ubuntu16.04，python3安装（Python2也可）
  * [OpenCV](https://link.jianshu.com/?t=http://opencv.org/downloads.html)安装参看[Installing OpenCV 3.0.0 on Ubuntu 14.04](https://link.jianshu.com/?t=http://rodrigoberriel.com/2014/10/installing-opencv-3-0-0-on-ubuntu-14-04/)，有些包的版本变新了，根据提示改一下名称再apt-get安装就行。国内环境可能还有些问题，参看[机器学习小鸟尝鲜 环境配置](https://www.jianshu.com/p/d8603d504b0c)中的OpenCV部分，没问题就不管。
  * 先安装一些包：

    
    
    sudo apt-get install xautomation
    sudo pip3 install numpy
    sudo pip3 install gym
    

  * 再下载[gym_torcs](https://link.jianshu.com/?t=https://github.com/ugo-nama-kun/gym_torcs)源码（建议迅雷+download zip，比较快），解压压缩包。
  * 然后将`gym_torcs/vtorcs-RL-color/src/modules/simu/simuv2/simu.cpp` 中第64行替换为`if (isnan((float)(car->ctrl->gear)) || isinf(((float)(car->ctrl->gear)))) car->ctrl->gear = 0;`，否则新的gcc会报错，Ubuntu14可能不用管。  

![noteattachment3][d9c5aca63d0968035d02c899184ac929]

代码修改

  * 然后`cd`进`gym_torcs`下`vtorcs-RL-color`目录，执行以下命令：

    
    
    sudo apt-get install libglib2.0-dev  libgl1-mesa-dev libglu1-mesa-dev  freeglut3-dev  libplib-dev  libopenal-dev libalut-dev libxi-dev libxmu-dev libxrender-dev  libxrandr-dev libpng12-dev 
    ./configure
    make
    sudo make install
    sudo make datainstall
    

  * 检查TORCS是否正确安装：打开一个终端，输入命令`torcs`，然后会出现图形界面，然后依次点击Race –> Practice –> New Race –> 会看到一个蓝屏输出信息“Initializing Driver scr_server1”。此时再打开一个终端，输入命令`python3 snakeoil3_gym.py`可以立刻看到一个演示，则安装成功。
  * 然后

    
    
    git clone https://github.com/yanpanlau/DDPG-Keras-Torcs.git #建议下载zip
    cd DDPG-Keras-Torcs
    cp *.* ../gym_torcs
    cd ../gym_torcs
    python3 ddpg.py 
    

作者使用的是python2，所以他将`snakeoil3_gym.py`文件做了一些修改。我用的是python3，还需要将`snakeoil3_gym.py`文件再改回来，应该是在上面cp命令中不要复制覆盖`snakeoil3_gym.py`文件就对了。如果覆盖了就将`snakeoil3_gym.py`文件中python2的一些语法改成python3的：如`print`要加个括号，`except`要改成`except
socket.error as emsg`，`unicode()`改成`str()`。这样就可以成功运行了。

### 背景

  * 在上一篇译文[新手向——使用Keras+卷积神经网络玩小鸟](https://www.jianshu.com/p/3ba69493f020)中，展示了如何使用深度Q学习神经网络来玩耍FlapyBird。但是，深Q网络的一个很大的局限性在于它的输出（是所有动作的Q值列表）是离散的，也就是对游戏的输入动作是离散的，而像在赛车游戏中的转向动作是一个连续的过程。一个显而易见的使DQN适应连续域的方法就是简单地将连续的动作空间离散化。但是马上我们就会遭遇‘维数灾难’问题。比如说，如果你将转盘从-90度到+90度的转动划分为5度一格，然后将将从0km到300km的加速度每5km一划分，你的输出组合将是36种转盘状态乘以60种速度状态等于2160种可能的组合。当你想让机器人进行一些更为专业化的操作时情况会更糟，比如脑外科手术这样需要精细的行为控制的操作，想要使用离散化来实现需要的操作精度就太naive了。
  * Google Deepmind 已经设计了一种新的算法来解决这种连续动作空间问题，它将3种技术结合在一起构成了[Deep Deterministic Policy Gradients (DDPG)](https://link.jianshu.com/?t=https://arxiv.org/abs/1509.02971)算法： 
    1. [Deterministic Policy-Gradient Algorithms](https://link.jianshu.com/?t=http://jmlr.org/proceedings/papers/v32/silver14.pdf) 确定性策略梯度算法（对于非机器学习研究者来说较难）
    2. [Actor-Critic Methods](https://link.jianshu.com/?t=https://webdocs.cs.ualberta.ca/~sutton/book/ebook/node66.html) 演员-评论家方法
    3. [Deep Q-Network](https://link.jianshu.com/?t=https://arxiv.org/abs/1312.5602) 深度Q学习神经网络

### 策略网络

  * 首先，我们将要定义一个策略网络来实现我们的AI-司机。这个网络将接收游戏的状态（例如，赛车的速度，赛车和赛道中轴之间的距离等）并且决定我们该做什么（方向盘向左打向右打，踩油门还是踩刹车）。它被叫做基于策略的强化学习，因为我们直接将策略参数化：

    
    
    \pi_\theta(s, a) = P [a | s, \theta]
    

![noteattachment4][b3973a3425c1a9b933f29a3ef62ff513]

  

这里，s是状态，a是行为/动作，θ是策略网络的模型参数，π是常见的表示策略的符号。我们可以设想策略是我们行为的代理人，即一个从状态到动作的映射函数。

### 确定性VS随机策略

  * 确定性策略： `a=μ(s)`  

![noteattachment5][4e8bdafe2b2f2db31bd8b407e11bd29c]

  * 随机策略： `π(a∣s)=P[a∣s]`  

![noteattachment6][360b9267d8795a621aacdc19b4d27cf5]

  
为什么在确定性策略之外我们还需要随机策略呢？理解一个确定性政策是容易的。我看到一个特定的状态输入，然后我采取特定的动作。但有时确定性策略不起作用，当你面对的第一个状态是个类似下面的白板时：  

![noteattachment7][8987364962b63b517eae2c0dc11915f8]

  
如果你还使用相同的确定性策略，你的网络将总是把棋子放在一个“特别”的位置，这是一个非常不好的行为，它会使你的对手能够预测你。在这种情况下，一个随机策略比确定性策略更合适。

### 策略目标函数

所以我们怎么找到`π_​θ​​(s,a)`呢？实际上，我们能够使用增强技术来解决它。例如，假设AI正在努力学习如何左转。在一开始，AI可能根本就不会转方向盘并撞上路边，获得一个负奖励（惩罚），所以神经网络将调整模型参数θ，避免下一次再撞上路边。多次尝试之后，它会发现，“啊哈，如果我把方向盘往更左打一点，我就不会这么早撞到路边了”。用数学语言来说，这就是策略目标函数。  
未来的总奖励函数定义为从离散的时间t开始的每一阶段的奖励之和：  
`R_t = r_t + r_{t+1} + r_{t+2} ... + r_n`  

![noteattachment8][96da9558c65012aab87c03e5f9288968]

  
上面的函数其实是马后炮函数，因为事情的总奖励在事情结束之前是不会确定的，说不定有转机呢（未来的动作数一般是很多的，也可能是不确定的），所谓俗语："不到最后一刻绝不罢休"和"盖棺定论"讲得就是这个道理，而且复杂的世界中，同样的决策它的结果也可能是不一样的，总有人运气好，也有人运气差，"一个人的命运，不光要看个人的奋斗，还要考虑历史的行程"，也就是说决策的结果可能还受一个不可掌控的未知参数影响。  
所以，作为一种提供给当前状态做判断的预期，我们构造一个相对简单的函数，既充分考虑又在一定程度上 **弱化**
未来的奖励（这个未来的奖励其实是基于经验得到，也就是训练的意义所在），得到未来的总折扣奖励（贴现奖励）函数：  
`R_t = r_t + \gamma r_{t+1} + \gamma^{2} r_{t+2} ... + \gamma^{n-t}
r_n`——`\gamma`即`γ`是折扣系数，一般取在(0,1)区间中  

![noteattachment9][e609f0e37c2f7209d0583676b956fdb7]

一个直观的策略目标函数将是总折扣奖励的期望：  
`L(\theta) = E[r_1 + \gamma r_2 + \gamma^{2} r_3 + ... |
\pi_\theta(s,a)]`，这里暂时取t为1，总奖励为R  

![noteattachment10][77a5570c2357d1f0043bc272423c6a8e]

  
`L(\theta) = E_{x\sim p(x|\theta)}[R]`  

![noteattachment11][844ec7d1ca011d9095d7262b52323818]

  
在这里，总奖励R的期望是在 由参数θ调整的某一概率分布`p(x∣θ)` 下计算的。

这时，又要用到我们的Q函数了，先回想一下上一篇译文的内容。  
由上文的未来总折扣奖励`R_t`可以看出它能表示为递归的形式：  
`R_t = r_t + \gamma * R_{t+1}`，将上文的`R_t`中的`t`代换为`t+1`代入此式即可验证  

![noteattachment12][b9efb406a75cd47682f3011ae929db39]

  
而我们的Q函数（在s状态下选择动作a的最大贴现奖励）是  
`Q(s_t, a_t) = max R_{t+1}`  

![noteattachment13][d7a01f658d3378be1ad6dbb60568abe3]

  
这里等式左边的`t`和右边的`t+1`可能看上去有些错位，因为它是按下面这个图走的，不用太纠结。  

![noteattachment14][13bcf77ec58f0ba53c4e3b32df0b8a2e]

  
但是接下来我们并没有和Q-learning采取同样的Q值更新策略，重点来了：  
我们采用了[SARSA](https://link.jianshu.com/?t=https://www.wikiwand.com/en/State-
Action-Reward-State-Action) —— State-Action-Reward-State-Action代表了状态-动作-奖励-状态-
动作。在SARSA中，我们开始于状态1，执行动作1，然后得到奖励1，于是我们到了状态2，在返回并更新在状态1下执行动作1的Q值之前，我们又执行了另一个动作（动作2）然后得到奖励2。相反，在Q-
learning中，我们开始于状态1，执行动作1，然后得到奖励1，接着就是查看在状态2中无论做出任一动作的最大可能奖励，并用这个值来更新状态1下执行动作1的Q值。所以不同的是未来奖励被发现的方式。在Q-
learning中它只是在状态2下最 **可能** 采取的最有利的动作的最大预期值，而在SARSA中它就是 **实际** 执行的动作的奖励值。  
这意味着SARSA考虑到了赛车（游戏代理）移动的控制策略（由控制策略我们连续地执行了两步），并集成到它的动作值的更新中，而Q-
learning只是假设一个最优策略被执行。 **不考虑所谓的最优而遵循一定的策略有时会是好事。**  
于是乎，在连续的情况下，我们使用了SARSA，Q值公式去掉了max，它还是递归的，只是去掉了
'武断'的max，而包含了控制策略，不过它并没有在这个Q值公式里表现出来，在更新公式的迭代中可以体现出来：  
`Q(s_t, a_t) = R_{t+1}`  

![noteattachment15][7e58a2fb3a6735a4b2dfa600c6c29e99]

  
Q值的更新公式从Q-learning的  

![noteattachment16][890d717a4be71caf5d27b091fb3e46c0]

Q-learning更新公式

  
变为  

![noteattachment17][4c6da938409883e5ae0b70b7b50b1052]

SARSA更新公式

所以，接着我们可以写出确定性策略`a=μ(s)`的梯度：  
`\frac{\partial L(\theta)}{\partial \theta} =
E_{x\sim~p(x|\theta)}[\frac{\partial Q}{\partial \theta}]`  

![noteattachment18][0dbf66c8f247ee714be4f84f2f7ba979]

  
然后应用高数中的链式法则：  

![noteattachment19][ee1a86455197fa36e45eb5226db9c08c]

  
它已经被证明（Silver el at. 2014）是策略梯度，即只要你按照上述的梯度公式来更新你的模型参数，你就会得到最大期望奖励。

> 补充

  * [Alberta](https://link.jianshu.com/?t=http://www.ualberta.ca/)大学课件[Sarsa](https://link.jianshu.com/?t=http://webdocs.cs.ualberta.ca/~sutton/book/ebook/node64.html) [Q-Learning](https://link.jianshu.com/?t=https://webdocs.cs.ualberta.ca/~sutton/book/ebook/node65.html)
  * 一篇不错的国人博客： [增强学习——时间差分学习(Q learning, Sarsa learning)](https://link.jianshu.com/?t=http://www.cnblogs.com/jinxulin/p/5116332.html)
  * 区别辨析，直观易懂：[Reinforcement Learning part 2: SARSA vs Q-learning](https://link.jianshu.com/?t=https://studywolf.wordpress.com/2013/07/01/reinforcement-learning-sarsa-vs-q-learning/)

### [演员-
评论家算法](https://link.jianshu.com/?t=https://webdocs.cs.ualberta.ca/~sutton/book/ebook/node66.html)

演员-评论家算法本质上是策略梯度算法和值函数方法的混合算法。策略函数被称为 **演员**
，而价值函数被称为评论家。本质上，演员在当前环境的给定状态s下产生动作a，而评论家产生一个信号来批评演员做出的动作。这在人类世界中是相当自然的，其中研究生（演员）做实际工作，导师（评论家）批评你的工作来让你下一次做得更好：）。在我们的TORCS例子中，我们使用了
**SARSA** 作为我们的 **评论家** 模型，并使用 **策略梯度算法** 作为我们的 **演员** 模型。它们的关系如图：  

![noteattachment20][60f7e061ae7dd6b43d74d127ba078725]

关系图

  
回到之前的公式，我们将Q做近似代换，其中w是神经网络的权重。所以我们得到深度策略性梯度公式(DDPG)：  
`\frac{\partial L(\theta)}{\partial \theta} = \frac{\partial
Q(s,a,w)}{\partial a}\frac{\partial a}{\partial \theta}`  

![noteattachment21][0f336cd24e9fc85c1e0e6c5ea48cbe58]

其中策略参数θ可以通过随机梯度上升来更新。  
此外，还有我们的损失函数，与SARSA的Q函数迭代更新公式一致：  
`Loss = [r + \gamma Q (s^{'},a^{'}) - Q(s,a)]^{2}`  

![noteattachment22][445b9e76de4db08cd82831ccb44ab276]

Q值用于估计当前演员策略的值。  
下图是演员-评论家模型的结构图：

  

![noteattachment23][aabea4097713ce9c254d8f38cdb7cde6]

演员-评论家结构图

## Keras代码说明

#### 演员网络

首先我们来看如何在Keras中构建演员网络。这里我们使用了2个隐藏层分别拥有300和600个隐藏单元。输出包括3个连续的动作。

  1. 转方向盘。是一个单元的输出层，使用`tanh`激活函数（输出-1意味着最大右转，+1表示最大左转）
  2. 加速。是一个单元的输出层，使用[`sigmoid`](https://link.jianshu.com/?t=https://www.wikiwand.com/en/Sigmoid_function)激活函数（输出0代表不加速，1表示全加速）。
  3. 刹车。是一个单元的输出层，也使用`sigmoid`激活函数（输出0表示不制动，1表示紧急制动）。

    
    
        def create_actor_network(self, state_size,action_dim):
            print("Now we build the model")
            S = Input(shape=[state_size])  
            h0 = Dense(HIDDEN1_UNITS, activation='relu')(S)
            h1 = Dense(HIDDEN2_UNITS, activation='relu')(h0)
            Steering = Dense(1,activation='tanh',init=lambda shape, name: normal(shape, scale=1e-4, name=name))(h1)   
            Acceleration = Dense(1,activation='sigmoid',init=lambda shape, name: normal(shape, scale=1e-4, name=name))(h1)   
            Brake = Dense(1,activation='sigmoid',init=lambda shape, name: normal(shape, scale=1e-4, name=name))(h1)   
            V = merge([Steering,Acceleration,Brake],mode='concat')          
            model = Model(input=S,output=V)
            print("We finished building the model")
            return model, model.trainable_weights, S
    

我们使用了一个Keras函数[Merge](https://link.jianshu.com/?t=https://keras.io/layers/core/)来合并三个输出层(concat参数是将待合并层输出沿着最后一个维度进行拼接)，为什么我们不使用如下的传统的定义方式呢：

    
    
    V = Dense(3,activation='tanh')(h1) 
    

使用3个不同的`Dense()`函数允许每个连续动作有不同的激活函数，例如，对加速使用`tanh`激活函数的话是没有意义的，`tanh`的输出是[-1,1]，而加速的范围是[0,1]。  
还要注意的是，在输出层我们使用了μ = 0，σ = 1e-4的正态分布初始化来确保策略的初期输出接近0。

#### 评论家网络

评论家网络的构造和上一篇的小鸟深Q网络非常相似。唯一的区别是我们使用了2个300和600隐藏单元的隐藏层。此外，评论家网络同时接受了状态和动作的输入。根据DDPG的论文，动作输入直到网络的第二个隐藏层才被使用。同样我们使用了`Merge`函数来合并动作和状态的隐藏层。

    
    
        def create_critic_network(self, state_size,action_dim):
            print("Now we build the model")
            S = Input(shape=[state_size])
            A = Input(shape=[action_dim],name='action2')    
            w1 = Dense(HIDDEN1_UNITS, activation='relu')(S)
            a1 = Dense(HIDDEN2_UNITS, activation='linear')(A)
            h1 = Dense(HIDDEN2_UNITS, activation='linear')(w1)
            h2 = merge([h1,a1],mode='sum')    
            h3 = Dense(HIDDEN2_UNITS, activation='relu')(h2)
            V = Dense(action_dim,activation='linear')(h3)  
            model = Model(input=[S,A],output=V)
            adam = Adam(lr=self.LEARNING_RATE)
            model.compile(loss='mse', optimizer=adam)
            print("We finished building the model")
            return model, A, S 
    

#### 目标网络

有一个众所周知的事实，在很多环境（包括TORCS）下，直接利用神经网络来实现Q值函数被证明是不稳定的。Deepmind团队提出了该问题的解决方法——使用一个目标网络，在那里我们分别创建了演员和评论家网络的副本，用来计算目标值。这些目标网络的权重通过
让它们自己慢慢跟踪学习过的网络 来更新：  
`\theta^{'} \leftarrow \tau \theta + (1 - \tau) \theta^{'}​​​​`  

![noteattachment24][b3687a9ec6df8a664ba9f339297dd1aa]

  
`\tau`即`τ` `<< 1`。这意味着目标值被限制为慢慢地改变，大大地提高了学习的稳定性。  
在Keras中实现目标网络时非常简单的：

    
    
        def target_train(self):
            actor_weights = self.model.get_weights()
            actor_target_weights = self.target_model.get_weights()
            for i in xrange(len(actor_weights)):
                actor_target_weights[i] = self.TAU * actor_weights[i] + (1 - self.TAU)* actor_target_weights[i]
            self.target_model.set_weights(actor_target_weights)
    

## 主要代码

在搭建完神经网络后，我们开始探索ddpg.py主代码文件。  
它主要做了三件事：

  1. 接收数组形式的传感器输入
  2. 传感器输入将被馈入我们的神经网络，然后网络会输出3个实数（转向，加速和制动的值）
  3. 网络将被训练很多次，通过DDPG（深度确定性策略梯度算法）来最大化未来预期回报。

#### 传感器输入

在TORCS中有18种不同类型的传感器输入，详细的说明在这篇文章中[Simulated Car Racing Championship :
Competition Software
Manual](https://link.jianshu.com/?t=https://arxiv.org/abs/1304.1672)。在试错后得到了有用的输入：

名称 | 范围 (单位) | 描述  
---|---|---  
ob.angle | [-π,+π] (rad) | 汽车方向和道路轴方向之间的夹角  
ob.track | (0, 200) (m) | 19个测距仪传感器组成的矢量，每个传感器返回200米范围内的车和道路边缘的距离  
ob.trackPos | (-oo, +oo) | 车和道路轴之间的距离，这个值用道路宽度归一化了：0表示车在中轴上，大于1或小于-1表示车已经跑出道路了  
ob.speedX | (-oo, +oo) (km/h) | 沿车纵向轴线的车速度(good velocity)  
ob.speedY | (-oo, +oo) (km/h) | 沿车横向轴线的车速度  
ob.speedZ | (-oo, +oo) (km/h) | 沿车的Z-轴线的车速度  
ob.wheelSpinVel | (0,+oo) (rad/s) | 4个传感器组成的矢量，表示车轮的旋转速度  
ob.rpm | (0,+oo) (rpm) | 汽车发动机的每分钟转速  
  
请注意，对于某些值我们归一化后再馈入神经网络，并且有些传感器输入并没有暴露在`gym_torcs`中。高级用户需要修改`gym_torcs.py`来改变参数。（查看函数`make_observaton()`）

#### 策略选择

现在我们可以使用上面的输入来馈入神经网络。代码很简单：

    
    
        for j in range(max_steps):
            a_t = actor.model.predict(s_t.reshape(1, s_t.shape[0]))
            ob, r_t, done, info = env.step(a_t[0])
    

然而，我们马上遇到两个问题。首先，我们如何确定奖励？其次，我们如何在连续的动作空间探索？

##### 奖励设计

在原始论文中，他们使用的奖励函数，等于投射到道路轴向的汽车速度，即`V​x*​​cos(θ)`，如图：  

![noteattachment25][06a97a8afef38f14fd705d76b4d3a9c6]

  
但是，我发现训练正如原始论文中说的那样并不是很稳定。有些时候可以学到合理的策略并成功完成任务，有些时候则不然，并不能习得明智的策略。  
我相信原因是，在原始的策略中，AI会尝试拼命踩油门油来获得最大的奖励，然后它会撞上路边，这轮非常迅速地结束。因此，神经网络陷入一个非常差的局部最小中。新提出的奖励函数如下：  
`R_t = V_x cos(\theta) - V_y sin(\theta) - V_x \mid trackPos \mid`  

![noteattachment26][7f417169d4ba521d50ad2a677110ffb1]

  
简单说来，我们想要最大化轴向速度（第一项），最小化横向速度（第二项），并且我们惩罚AI如果它持续非常偏离道路的中心（第三项）。  
这个新的奖励函数大幅提高了稳定性，降低了TORCS学习时间。

#### 探索算法的设计

另一个问题是在连续空间中如何设计一个正确的探索算法。在上一篇文章中，我们使用了ε贪婪策略，即在某些时间片，我们尝试一个随机的动作。但是这个方法在TORCS中并不有效，因为我们有3个动作（转向，加速，制动）。如果我只是从均匀分布的动作中随机选取，会产生一些无聊的组合（例如：制动的值大于加速的值，车子根本就不会动）。所以，我们使用奥恩斯坦
- 乌伦贝克（Ornstein-Uhlenbeck）过程添加噪声来做探索。

##### Ornstein-Uhlenbeck处理

简单说来，它就是具有均值回归特性的随机过程。  
`dx_t = \theta (\mu - x_t)dt + \sigma dW_t`  

![noteattachment27][440afdd85678bb26fcca166d0693bc8b]

  
这里，θ反应变量回归均值有多快。μ代表平衡或均值。σ是该过程的波动程度。有趣的事，奥恩斯坦 -
乌伦贝克过程是一种很常见的方法，用来随机模拟利率，外汇和大宗商品价格。（也是金融定量面试的常见问题）。下表展示了在代码中使用的建议值。

Action | θ | μ | σ  
---|---|---|---  
steering | 0.6 | 0.0 | 0.30  
acceleration | 1.0 | [0.3-0.6] | 0.10  
brake | 1.0 | -0.1 | 0.05  
  
基本上，最重要的参数是加速度μ，你想要让汽车有一定的初始速度，而不要陷入局部最小（此时汽车一直踩刹车，不再踩油门）。你可以随意更改参数来实验AI在不同组合下的行为。奥恩斯坦的
- 乌伦贝克过程的代码保存在`OU.py`中。  
AI如果使用合理的探索策略和修订的奖励函数，它能在一个简单的赛道上在200回合左右学习到一个合理的策略。

#### 经验回放

类似于深Q小鸟，我们也使用了经验回放来保存所有的阶段(s, a, r,
s')在一个回放存储器中。当训练神经网络时，从其中随机小批量抽取阶段情景，而不是使用最近的，这将大大提高系统的稳定性。

    
    
            buff.add(s_t, a_t[0], r_t, s_t1, done)
            # 从存储回放器中随机小批量抽取N个变换阶段 (si, ai, ri, si+1)
            batch = buff.getBatch(BATCH_SIZE)
            states = np.asarray([e[0] for e in batch])
            actions = np.asarray([e[1] for e in batch])
            rewards = np.asarray([e[2] for e in batch])
            new_states = np.asarray([e[3] for e in batch])
            dones = np.asarray([e[4] for e in batch])
            y_t = np.asarray([e[1] for e in batch])
    
            target_q_values = critic.target_model.predict([new_states, actor.target_model.predict(new_states)])    #Still using tf
           
            for k in range(len(batch)):
                if dones[k]:
                    y_t[k] = rewards[k]
                else:
                    y_t[k] = rewards[k] + GAMMA*target_q_values[k]
    

请注意，当计算了`target_q_values`时我们使用的是目标网络的输出，而不是模型自身。使用缓变的目标网络将减少Q值估测的振荡，从而大幅提高学习的稳定性。

#### 训练

神经网络的实际训练非常简单，只包含了6行代码：

    
    
            loss += critic.model.train_on_batch([states,actions], y_t) 
            a_for_grad = actor.model.predict(states)
            grads = critic.gradients(states, a_for_grad)
            actor.train(states, grads)
            actor.target_train()
            critic.target_train()
    

首先，我们最小化损失函数来更新评论家。  
`L = \frac{1}{N} \displaystyle\sum_{i} (y_i - Q(s_i,a_i | \theta^{Q}))^{2}`  

![noteattachment28][e4156da699e6eda483edeca3fb316e55]

  
然后演员策略使用一定样本的策略梯度来更新  
`\nabla_\theta J = \frac{\partial Q^{\theta}(s,a)}{\partial a}\frac{\partial
a}{\partial \theta}`  

![noteattachment29][8d2b56c86713596bc6dcc14a9e8f49bd]

  
回想一下，a是确定性策略：`a=μ(s∣θ)`  
因此，它能被写作：  
`\nabla_\theta J = \frac{\partial Q^{\theta}(s,a)}{\partial a}\frac{\partial
\mu(s|\theta)}{\partial \theta}`  

![noteattachment30][bf899b4091375f6121a6b985a9c24ead]

  
最后两行代码更新了目标网络  
`\theta^{Q^{'}} \leftarrow \tau \theta^{Q} + (1 - \tau) \theta^{Q^{'}}
\theta^{\mu^{'}} \leftarrow \tau \theta^{\mu} + (1 - \tau) \theta^{\mu^{'}}`  

![noteattachment31][473b15496c4f1accb020362839b19e3a]

### 结果

为了测试策略，选择一个名为 **Aalborg** 的稍微困难的赛道，如下图：  

![noteattachment32][0d6f68f3775952ede8481a0fc0be338f]

Aalborg

  
神经网络被训练了2000个回合，并且令奥恩斯坦 -
乌伦贝克过程在100000帧中线性衰变。（即没有更多的开发在100000帧后被应用）。然后测试一个新的赛道（3倍长）来验证我们的神经网络。在其它赛道上测试是很重要的，这可以确认AI是否只是简单地记忆住了赛道（过拟合），而非学习到通用的策略。  

![noteattachment33][5467369c9c5766471b384c60a3976af2]

Alpine

  
测试结果视频，赛道：[Aalborg](https://link.jianshu.com/?t=https://youtu.be/4hoLGtnK_3U)
与 [Alpine](https://link.jianshu.com/?t=https://youtu.be/8CNck-hdys8)。  
结果还不错，但是还不理想，因为它还没太学会使用刹车。

### 学习如何刹车

事实证明，要求AI学会如何刹车比转弯和加速难多了。原因在于当刹车的时候车速降低，因此，奖励也会下降，AI根本就不会热心于踩刹车。另外，
如果允许AI在勘探阶段同时踩刹车和加速，AI会经常急刹，我们会陷入糟糕的局部最小解（汽车不动，不会受到任何奖励）。  
所以如何去解决这个问题呢？不要急刹车，而是试着感觉刹车。我们在TORCS中添加随机刹车的机制：在勘探阶段，10%的时间刹车（感觉刹车），90%的时间不刹车。因为只在10%的时间里刹车，汽车会有一定的速度，因此它不会陷入局部最小（汽车不动），而同时，它又能学习到如何去刹车。  
[“随机刹车”使得AI在直道上加速很快，在快拐弯时适当地刹车](https://link.jianshu.com/?t=https://youtu.be/JqQd5Bqgedo)。这样的行为更接近人类的做法。

### 总结和进一步的工作

我们成功地使用
Keras和DDPG来玩赛车游戏。尽管DDPG能学习到一个合理的策略，但和人学会开车的复杂机制还是有很大区别的，而且如果是开飞机这种有更多动作组合的问题，事情会复杂得多。  
不过，这个算法还是相当给力的，因为我们有了一个对于连续控制的无模型算法，这对于机器人是很有意义的。

### 杂项

  1. 要更换赛道，需要命令行输入 **sudo torcs** – > Race –> Practice –> Configure Race。
  2. 关闭声音，需要命令行输入 **sudo torcs** – > Options –> Sound –> Disable sound。
  3. `snakeoil3_gym.py`是与TORCS服务器沟通的脚本。

### 参考

[1] Lillicrap, et al. [Continuous control with Deep Reinforcement
Learning](https://link.jianshu.com/?t=https://arxiv.org/abs/1509.02971)  
[2]
[@karpathy](https://link.jianshu.com/?t=https://twitter.com/karpathy)的[Deep
Reinforcement Learning: Pong from
Pixels](https://link.jianshu.com/?t=http://karpathy.github.io/2016/05/31/rl/)——理解策略梯度

### 其它

  * [Deep Learning Episode 3: Supercomputer vs Pong](https://link.jianshu.com/?t=http://www.allinea.com/blog/201610/deep-learning-episode-3-supercomputer-vs-pong)

### 作者的致谢

I thank to Naoto Yoshida, the author of the
[gym_torcs](https://link.jianshu.com/?t=https://github.com/ugo-nama-
kun/gym_torcs) and his prompt reply on various TORCS setup issue. I also thank
to [@karpathy](https://link.jianshu.com/?t=https://twitter.com/karpathy) his
great post [Deep Reinforcement Learning: Pong from
Pixels](https://link.jianshu.com/?t=http://karpathy.github.io/2016/05/31/rl/)
which really helps me to understand policy gradient. I thank to
[@hardmaru](https://link.jianshu.com/?t=https://twitter.com/hardmaru) and
[@flyyufelix](https://link.jianshu.com/?t=https://twitter.com/flyyufelix) for
their comments and suggestions.

小礼物走一走，来简书关注我

赞赏支持

[ __ Python ](https://www.jianshu.com/nb/7231458)

© 著作权归作者所有

[举报文章](https://www.jianshu.com/p/a3432c0e1ef2)

[
![96](https://upload.jianshu.io/users/upload_avatars/2422746/a597dc58020c.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/96/h/96)
](https://www.jianshu.com/u/66f24f2c0f36)
[__关注](https://www.jianshu.com/p/a3432c0e1ef2) [
treelake](https://www.jianshu.com/u/66f24f2c0f36)

写了 118933 字，被 2591 人关注，获得了 2663 个喜欢

无名之辈

[喜欢](https://www.jianshu.com/p/a3432c0e1ef2)

[45](https://www.jianshu.com/p/a3432c0e1ef2)

[ __](https://www.jianshu.com/p/a3432c0e1ef2) __ [
__](http://cwb.assets.jianshu.io/notes/images/6399501/weibo/image_a13e6d82a829.jpg)
更多分享

[
![noteattachment34][10f08e404d3887d2d45a4bc8f1831403]](https://www.jianshu.com/apps/download?utm_source=nbc)

[
![noteattachment35][78d4d1f68984cd6d4379508dd94b4210]](https://www.jianshu.com/p/a3432c0e1ef2)

[登录](https://www.jianshu.com/sign_in?utm_source=desktop&utm_medium=not-signed-
in-comment-form) 后发表评论

26条评论 [只看作者](https://www.jianshu.com/p/a3432c0e1ef2)

[按喜欢排序](https://www.jianshu.com/p/a3432c0e1ef2)[按时间正序](https://www.jianshu.com/p/a3432c0e1ef2)[按时间倒序](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/2179338/1a122dbce3e1.jpeg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/d98cff8d7ecc)

[casaba](https://www.jianshu.com/u/d98cff8d7ecc)

2楼 · 2016.10.22 19:39

上一篇都千阅了啊，强，无敌

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[treelake](https://www.jianshu.com/u/66f24f2c0f36)：

[@casaba](https://www.jianshu.com/users/d98cff8d7ecc) 赞率才2%不到

2016.10.22 19:43 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[NANAphei](https://www.jianshu.com/u/cfc7a98f9357)：

赶紧点赞 并约稿，大神大神 约稿呗 ![noteattachment36][e6f06b33a6dd19ea5eff73b94456a9ac]

2016.10.25 10:10 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[__ 添加新评论](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/939125/7850819d357e.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/b9249fb85d5d)

[ripperhe](https://www.jianshu.com/u/b9249fb85d5d)

3楼 · 2016.10.22 23:48

不明觉厉😁 已关注

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/3364523/1363d823df2b.jpeg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/a136a2b26084)

[JiaxYau](https://www.jianshu.com/u/a136a2b26084)

4楼 · 2016.10.25 15:51

你好，请问你的公式是怎么输入的，简书好像不支持latex吧

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[treelake](https://www.jianshu.com/u/66f24f2c0f36)：

[@YauPH](https://www.jianshu.com/users/a136a2b26084)
那是图片，只是把latex公式也放上去了。。简书数学支持不行啊，还是用pelican或者hexo吧

2016.10.25 15:56 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[__ 添加新评论](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/2809025/da8c31f844c9.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/6e48be5a3b81)

[vansnowpea](https://www.jianshu.com/u/6e48be5a3b81)

5楼 · 2016.10.26 20:37

偶遇 大早赞 请保持

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://cdn2.jianshu.io/assets/default_avatar/2-9636b13945b9ccf345bc98d0d81074eb.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/e9d70cb564a5)

[健叔998](https://www.jianshu.com/u/e9d70cb564a5)

6楼 · 2016.12.10 16:19

辛苦啦，翻译的不错~

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/4106819/d96d2b321edf.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/30aaebe9e529)

[Lanerl](https://www.jianshu.com/u/30aaebe9e529)

7楼 · 2016.12.20 19:49

from keras.engine.training import collect_trainable_weights  
ImportError: cannot import name collect_trainable_weights  
请问这个error怎么解决？

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[机器学习小学生](https://www.jianshu.com/u/da6e88ab9089)：

[@Lanerl](https://www.jianshu.com/users/30aaebe9e529)
注释掉ddpg.py，ActorNetwork.py，CriticNetwork.py中import
collect_trainable_weights的句子。亲测可用不知是否正确。

2017.01.04 10:03 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[Lanerl](https://www.jianshu.com/u/30aaebe9e529)：

[@机器学习小学生](https://www.jianshu.com/users/da6e88ab9089) 我也是这么改的
能跑但是训练效果不好，跑一段就停车了。不知道怎么才能训练成视频中的结果
![noteattachment37][7e4b2365f2611866c041969f8f0a0aa3]

2017.01.05 20:10 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[我_afeb](https://www.jianshu.com/u/852496af4b98)：

我现在也遇到了这个问题，请问是怎么解决的？十分感谢！

2017.04.08 00:30 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[__ 添加新评论](https://www.jianshu.com/p/a3432c0e1ef2) 还有5条评论，
[展开查看](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/617746/e65f6a5c520e?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/a24acc5449c7)

[Nicholas_Jela](https://www.jianshu.com/u/a24acc5449c7)

8楼 · 2017.07.19 10:51

跑了下，根本无法训练，车丝毫不动

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[冰与火演义](https://www.jianshu.com/u/1c05488f2aac)：

是呀，ddpg是训练过程，太慢了

2017.11.02 10:59 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[__ 添加新评论](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://cdn2.jianshu.io/assets/default_avatar/4-3397163ecdb3855a0a4139c34a695885.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/4d7510854c69)

[Ping_v](https://www.jianshu.com/u/4d7510854c69)

9楼 · 2017.11.27 15:26

可能是keras版本不同的原因，照着做碰到几个import错误，做了如下处理：  
\- 注释掉ddpg.py中的from keras.engine.training import collect_trainable_weights  
\- 修改ActorNetwork.py，将from keras.initializations import normal,
identity中的initializtion改为initializers,注释掉from keras.engine.training import
collect_trainable_weights  
\- 修改CriticNetworks.py，keras.initializtion改为keras.initializers, 注释掉from
keras.engine.training import collect_trainable_weights  
  
最后这错解决不了了：  
  
root@ubuntu16:~/gym_torcs# python ddpg.py  
Using TensorFlow backend.  
Now we build the model  
/root/gym_torcs/ActorNetwork.py:52: UserWarning: Update your `Dense` call to
the Keras 2 API: `Dense(1, activation="tanh", kernel_initializer=<function
...)`  
Steering = Dense(1,activation='tanh',init=lambda shape, name: normal(shape,
scale=1e-4, name=name))(h1)  
Traceback (most recent call last):  
File "ddpg.py", line 162, in <module>  
playGame()  
File "ddpg.py", line 52, in playGame  
actor = ActorNetwork(sess, state_dim, action_dim, BATCH_SIZE, TAU, LRA)  
File "/root/gym_torcs/ActorNetwork.py", line 26, in __init__  
self.model , self.weights, self.state = self.create_actor_network(state_size,
action_size)  
File "/root/gym_torcs/ActorNetwork.py", line 52, in create_actor_network  
Steering = Dense(1,activation='tanh',init=lambda shape, name: normal(shape,
scale=1e-4, name=name))(h1)  
File "/root/miniconda3/lib/python3.5/site-packages/keras/engine/topology.py",
line 576, in __call__  
self.build(input_shapes[0])  
File "/root/miniconda3/lib/python3.5/site-packages/keras/layers/core.py", line
830, in build  
constraint=self.kernel_constraint)  
File "/root/miniconda3/lib/python3.5/site-
packages/keras/legacy/interfaces.py", line 87, in wrapper  
return func(*args, **kwargs)  
File "/root/miniconda3/lib/python3.5/site-packages/keras/engine/topology.py",
line 397, in add_weight  
weight = K.variable(initializer(shape),  
TypeError: <lambda>() missing 1 required positional argument: 'name'  
  
谁能给点建议么？

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[Ping_v](https://www.jianshu.com/u/4d7510854c69)：

keras 2.1.1  
tensorflow 1.2.1

2017.11.27 15:33 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[Ping_v](https://www.jianshu.com/u/4d7510854c69)：

keras1.2.2 问题解决了，initializations也不用改。我没有GPU卡，终端看到数据在跳，但是游戏屏幕不动。

2017.11.27 17:47 [__ 回复](https://www.jianshu.com/p/a3432c0e1ef2)

[__ 添加新评论](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/6234774/13eaca09-ee14-4a23-a7ce-f60d7358e47b?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/0e068300748e)

[好小气先生](https://www.jianshu.com/u/0e068300748e)

10楼 · 2018.01.01 15:56

原作者提供的github代码有问题么，还是我理解的不对？Line 110~124  
y_t = np.asarray([e[1] for e in batch])  
y_t是用来计算q值的 但e[1]赋的值却是actions 不应该是rewards么？  
[https://github.com/yanpanlau/DDPG-Keras-
Torcs/blob/master/ddpg.py](https://github.com/yanpanlau/DDPG-Keras-
Torcs/blob/master/ddpg.py)

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://cdn2.jianshu.io/assets/default_avatar/10-e691107df16746d4a9f3fe9496fd1848.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/a74885679d58)

[a_ta](https://www.jianshu.com/u/a74885679d58)

11楼 · 2018.01.04 15:54

楼主知道怎么使用GPU训练网络嘛？我跑代码都是默认使用的CPU

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://cdn2.jianshu.io/assets/default_avatar/10-e691107df16746d4a9f3fe9496fd1848.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/a74885679d58)

[a_ta](https://www.jianshu.com/u/a74885679d58)

12楼 · 2018.01.04 15:56

楼主知道怎么用GPU训练嘛？原作代码跑起来只用了CPU，训练好慢

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

[![](https://upload.jianshu.io/users/upload_avatars/4861523/c2174003-a923-4eab-
ac8b-6bdda9613846?imageMogr2/auto-
orient/strip%7CimageView2/1/w/114/h/114)](https://www.jianshu.com/u/f3428c112966)

[ligh_4e08](https://www.jianshu.com/u/f3428c112966)

13楼 · 2018.01.29 21:52

个人觉得sarsa那里有些问题，Q函数的更新并没有用到动作a_t+1

[赞](https://www.jianshu.com/p/a3432c0e1ef2) [__
回复](https://www.jianshu.com/p/a3432c0e1ef2)

  * __

被以下专题收入，发现更多相似内容

[![](https://upload.jianshu.io/collections/images/14/6249340_194140034135_2.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)@IT·互联网](https://www.jianshu.com/c/V2CqjW?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/1131/%E5%B0%8FQ%E6%88%AA%E5%9B%BE-20140815162604.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)十一维的风](https://www.jianshu.com/c/6ce195da33a0?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/47/%E9%A6%96%E9%A1%B5%E6%8A%95%E7%A8%BF.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)首页投稿](https://www.jianshu.com/c/bDHhpK?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/16/computer_guy.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)程序员](https://www.jianshu.com/c/NEt52a?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/52/%E4%BB%8A%E6%97%A5%E7%9C%8B%E7%82%B9.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)今日看点](https://www.jianshu.com/c/3sT4qY?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/2453/CollectionImage.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)生活不易
我用...](https://www.jianshu.com/c/8c01bfa7b98a?utm_source=desktop&utm_medium=notes-
included-
collection)[![](https://upload.jianshu.io/collections/images/270448/images.jpeg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/64/h/64)每天学点机器学习](https://www.jianshu.com/c/f453fd752759?utm_source=desktop&utm_medium=notes-
included-collection) [ 展开更多 __](https://www.jianshu.com/p/a3432c0e1ef2)

[
无标题文章](https://www.jianshu.com/p/b2745d285770?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

目录 [TOC] 引言
量化交易是指以先进的数学模型替代人为的主观判断，利用计算机技术从庞大的历史数据中海选能带来超额收益的多种“大概率”事件以制定策略，极大地减少了投资者情绪波动的影响，避免在市场极度狂热或悲观的情况下作出非理性的投资决策。
量化领域拥有比较成熟的理论或策...

[
![48](https://cdn2.jianshu.io/assets/default_avatar/4-3397163ecdb3855a0a4139c34a695885.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 雷达熊
](https://www.jianshu.com/u/58008efbb46a?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[高考3500](https://www.jianshu.com/p/0bda5d804ee3?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

A a (an) [ə, eɪ(ən)] art. 一（个、件……） abandon [əˈbændən] v.抛弃，舍弃，放弃 ability
[əˈbɪlɪtɪ] n. 能力；才能 able [ˈeɪb(ə)l] a. 能够；有能力的 abnormal [æbˈnɔːm...

[
![48](https://upload.jianshu.io/users/upload_avatars/1356642/033b85284743?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 0涂桃子
](https://www.jianshu.com/u/02eb49244585?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[ ![240](https://upload-
images.jianshu.io/upload_images/3232548-f037d57e01949127.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/300/h/240)
](https://www.jianshu.com/p/2bc6dab16cfe?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
[Batch
Normalization论文翻译——中英文对照](https://www.jianshu.com/p/2bc6dab16cfe?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

文章作者：Tyan博客：noahsnail.com | CSDN | 简书 声明：作者翻译论文仅为学习，如有侵权请联系作者删除博文，谢谢！ Batch
Normalization: Accelerating Deep Network Training by Reducing...

[
![48](https://upload.jianshu.io/users/upload_avatars/3232548/242eb25c-3001-4411-a856-74b33312fdff.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) SnailTyan
](https://www.jianshu.com/u/7731e83f3a4e?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[RLDM 强化学习教程-David
Silver](https://www.jianshu.com/p/782cd2518d0e?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

Neil Zhu，简书ID Not_GOD，University AI 创始人 & Chief Scientist，致力于推进世界人工智能化进程。制定并实施
UAI 中长期增长战略和目标，带领团队快速成长为人工智能领域最专业的力量。作为行业领导者，他和UAI一起在2014年...

[
![48](https://upload.jianshu.io/users/upload_avatars/42741/0e4e103b9892?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 朱小虎Neil
](https://www.jianshu.com/u/696dc6c6f01c?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[REINFORCE
算法](https://www.jianshu.com/p/518ce700e4ab?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

Neil Zhu，简书ID Not_GOD，University AI 创始人 & Chief Scientist，致力于推进世界人工智能化进程。制定并实施
UAI 中长期增长战略和目标，带领团队快速成长为人工智能领域最专业的力量。作为行业领导者，他和UAI一起在2014年...

[
![48](https://upload.jianshu.io/users/upload_avatars/42741/0e4e103b9892?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 朱小虎Neil
](https://www.jianshu.com/u/696dc6c6f01c?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[ ![240](https://upload-
images.jianshu.io/upload_images/2630088-f7ccb4bc7a667f23.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/300/h/240)
](https://www.jianshu.com/p/439bd7e875c8?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
[《写在人生边上》|写在边上的边上](https://www.jianshu.com/p/439bd7e875c8?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

“即使人生是一部大书，那么，下面的几篇散文只能算是写在人生边上的。这本书真大，一时不易看完，就是写过的边上也还留下好多空白。”
这是钱钟书《写在人生边上》这本书的最佳注释。 这一本小册子，是钱老所思所想的合集，他的思考和感悟都在里面，他对人生的嬉笑调侃也在里面，有一种超然的...

[
![48](https://upload.jianshu.io/users/upload_avatars/2630088/373068ec9cfd.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 老胡冷静
](https://www.jianshu.com/u/10edd1799164?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[ ![240](https://upload-
images.jianshu.io/upload_images/2355077-3ac22c629c161e80.png?imageMogr2/auto-
orient/strip%7CimageView2/1/w/300/h/240)
](https://www.jianshu.com/p/e51142d2b0fe?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
[Codiad 漏洞挖掘笔记 (0x03)
[开发者修复漏洞不完善导致再次远程代码执行]](https://www.jianshu.com/p/e51142d2b0fe?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

简介 : Codiad GitHub 引子 : 之前在 XMAN 选拔赛中发现了一 Codiad 的一个远程命令执行漏洞 参考之前的分析文章 :
http://www.jianshu.com/p/41ac7ac2a7af 报告给开发者之后开发者反应非常迅速 , 基本一两天立...

[
![48](https://upload.jianshu.io/users/upload_avatars/2355077/9774c6e7-4771-423d-bbda-d82966131b8d.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 王一航
](https://www.jianshu.com/u/bf30f18c872c?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[拥有几个商才能幸福？|
朱身勇](https://www.jianshu.com/p/a83cf304bb6a?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

作者：朱身勇 【一个人要几个商才能幸福？】
智商决定了你的学习创造能力，没有智商吃药也无用。情商决定了与人普通关系，没有人的关系就是孤家寡人，无人协作，可学习改善，吃药能改善是骗人的。挫商决定了你成功有多少，没有人随便成功，遇挫而弃则半途而废，也可学习，吃药是扯淡。爱商决定...

[
![48](https://upload.jianshu.io/users/upload_avatars/5872837/4749c12b-def1-4764-b9a1-4de653dde2ab.jpg?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 朱身勇婚姻管理导师
](https://www.jianshu.com/u/994ed993bd18?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[ ![240](https://upload-
images.jianshu.io/upload_images/691101-a30513dc6b63b084?imageMogr2/auto-
orient/strip%7CimageView2/1/w/300/h/240)
](https://www.jianshu.com/p/0e2ad5f6c75e?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)
[十一拼假！去南半球享受春天！](https://www.jianshu.com/p/0e2ad5f6c75e?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

距离十一长假仅剩不到两周的时间了。相信许多朋友早已计划好了利用调休把中秋和十一假期连在一起，组成长达12天的超长豪华假期！
那么长的假期去哪里玩呢，如果还没想好，不妨看一看瞧一瞧，小编已经整理好一组当季澳大利亚玩点。此时的澳洲正当春暖花开，有不少好玩的去处，快随小编去看看吧...

[
![48](https://upload.jianshu.io/users/upload_avatars/691101/86f1c663b5b6?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) 丸子地球
](https://www.jianshu.com/u/2a63ccf7dfe0?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)

[PyInstaller:
Python程序打包](https://www.jianshu.com/p/107d82399f2b?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation)

昨晚才学会打包 Python 程序, 使用场景可能为你写了个小程序, 然后你的朋友并没有安装 Python 解释器(很可能是并不想安装),
这个时候你只发给他脚本就没什么乱用了, 这个时候你可能想到用 C 写的程序可以编译成 exe, Python可不可以呢? Python...

[
![48](https://upload.jianshu.io/users/upload_avatars/1804106/c4724551bd43.JPG?imageMogr2/auto-
orient/strip%7CimageView2/1/w/48/h/48) note286
](https://www.jianshu.com/u/8b869344aa57?utm_campaign=maleskine&utm_content=user&utm_medium=seo_notes&utm_source=recommendation)


---
### ATTACHMENTS
[06a97a8afef38f14fd705d76b4d3a9c6]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书.png)
[0d6f68f3775952ede8481a0fc0be338f]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-2.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-2.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-2.png)
[0dbf66c8f247ee714be4f84f2f7ba979]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-3.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-3.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-3.png)
[0f336cd24e9fc85c1e0e6c5ea48cbe58]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-4.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-4.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-4.png)
[10f08e404d3887d2d45a4bc8f1831403]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-5.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-5.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-5.png)
[13bcf77ec58f0ba53c4e3b32df0b8a2e]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-6.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-6.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-6.png)
[360b9267d8795a621aacdc19b4d27cf5]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-7.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-7.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-7.png)
[440afdd85678bb26fcca166d0693bc8b]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-8.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-8.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-8.png)
[445b9e76de4db08cd82831ccb44ab276]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-9.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-9.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-9.png)
[473b15496c4f1accb020362839b19e3a]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-10.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-10.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-10.png)
[4c6da938409883e5ae0b70b7b50b1052]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-11.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-11.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-11.png)
[4c7bbafe27adc892f3046e6978459bac]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-12.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-12.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-12.png)
[4e8bdafe2b2f2db31bd8b407e11bd29c]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-13.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-13.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-13.png)
[5467369c9c5766471b384c60a3976af2]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-14.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-14.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-14.png)
[60f7e061ae7dd6b43d74d127ba078725]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-15.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-15.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-15.png)
[77a5570c2357d1f0043bc272423c6a8e]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-16.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-16.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-16.png)
[78d4d1f68984cd6d4379508dd94b4210]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-17.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-17.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-17.png)
[7e4b2365f2611866c041969f8f0a0aa3]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-18.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-18.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-18.png)
[7e58a2fb3a6735a4b2dfa600c6c29e99]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-19.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-19.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-19.png)
[7f417169d4ba521d50ad2a677110ffb1]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-20.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-20.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-20.png)
[844ec7d1ca011d9095d7262b52323818]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-21.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-21.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-21.png)
[890d717a4be71caf5d27b091fb3e46c0]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-22.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-22.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-22.png)
[8987364962b63b517eae2c0dc11915f8]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-23.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-23.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-23.png)
[8d2b56c86713596bc6dcc14a9e8f49bd]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-24.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-24.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-24.png)
[96da9558c65012aab87c03e5f9288968]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-25.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-25.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-25.png)
[aabea4097713ce9c254d8f38cdb7cde6]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-26.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-26.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-26.png)
[b3687a9ec6df8a664ba9f339297dd1aa]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-27.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-27.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-27.png)
[b3973a3425c1a9b933f29a3ef62ff513]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-28.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-28.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-28.png)
[b9efb406a75cd47682f3011ae929db39]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-29.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-29.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-29.png)
[bf899b4091375f6121a6b985a9c24ead]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-30.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-30.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-30.png)
[d2a12a5c437fadcf2af5e3f03e86d24f]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-31.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-31.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-31.png)
[d7a01f658d3378be1ad6dbb60568abe3]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-32.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-32.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-32.png)
[d9c5aca63d0968035d02c899184ac929]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-33.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-33.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-33.png)
[e4156da699e6eda483edeca3fb316e55]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-34.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-34.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-34.png)
[e609f0e37c2f7209d0583676b956fdb7]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-35.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-35.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-35.png)
[e6f06b33a6dd19ea5eff73b94456a9ac]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-36.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-36.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-36.png)
[ee1a86455197fa36e45eb5226db9c08c]: media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-37.png
[使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-37.png](media/使用Keras和DDPG玩赛车游戏（自动驾驶）_-_简书-37.png)
---
### NOTE ATTRIBUTES
>Created Date: 2018-03-11 16:13:52  
>Last Evernote Update Date: 2019-04-06 02:07:13  
>source: web.clip  
>source-url: https://www.jianshu.com/p/a3432c0e1ef2  
>source-application: ios.clipper.evernote  