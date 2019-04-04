# LocalNote

[![Gitter](https://badges.gitter.im/littlecodersh/LocalNote.svg)](https://gitter.im/littlecodersh/LocalNote?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge) ![python](https://img.shields.io/badge/python-2.7-ff69b4.svg) [English Version](https://github.com/littlecodersh/LocalNote/blob/master/README_EN.md)

LocalNote让你能够像使用本地文件一样使用印象笔记。

支持流行的markdown格式的笔记，印象笔记中完美显示，上传重新下载笔记仍为`.md`格式。

支持印象笔记原笔记格式转化为markdown格式，轻松开始使用。

三平台支持，在linux平台也流畅的使用印象笔记。

# Screenshot

![](http://7xrip4.com1.z0.glb.clouddn.com/LocalNote/localnote.gif)

视频见[这里](http://v.youku.com/v_show/id_XMTU3Nzc5NzU1Ng==)

# Installation

```bash
pip install localnote
```

# Usage

## 常用命令

```bash
# 初始化印象笔记目录，请在空文件夹使用
localnote init
# 下载笔记
localnote pull
# 查看云端及本地笔记更改
localnote status
# 上传本地笔记
localnote push
# 将html转化为md格式
localnote convert 需要转换的文件.html
```

## 使用模式

你可以选择对整个印象笔记使用LocalNote，或者只有单一一个笔记本使用LocalNote

```bash
# 设定使用LocalNote的笔记本（全笔记本使用不设定即可）
localnote notebook
```

## 存储格式
* 根目录下每个文件夹对应一个笔记本
* 笔记本文件夹中每个文件（文件夹）对应一个笔记
* 笔记可以仅存在主文件也可以以文件夹的形式包含附件
* 笔记主文件必须是`.md`或者`.html`格式，文件名（不包括后缀）将会被用作笔记名

## 示例文件树

```
Root
    我的默认笔记本
        第一个笔记.html
        第二个笔记.html
    附件笔记本
        第三个笔记
            第三个笔记.md
            打包材料.zip
            打包笔记.txt
    空笔记本
```

# FAQ

Q: 第一次使用需要下载很久么？

A: 取决于你笔记中内容的多少，一般下载速度为200k/s。

Q: 本地如何预览markdown格式内容？

A: 建议添加浏览器插件，即可即时预览。例如Chrome的[Markdown Preview Plus](https://chrome.google.com/webstore/detail/markdown-preview-plus/febilkbfcbhebfnokafefeacimjdckgl)。

# Comments

如果有什么问题或者建议都可以在这个[Issue](https://github.com/littlecodersh/LocalNote/issues/1)和我讨论。

或者也可以在gitter上交流： [![Gitter](https://badges.gitter.im/littlecodersh/LocalNote.svg)](https://gitter.im/littlecodersh/LocalNote?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)



#guqinglei增加
1.安装需求：
    requests==2.9.1
    markdown==2.6.6
    evernote-sdk-python3==1.25.1（注意设定环境变量PYTHONPATH）
    chardet==2.3.0
    html2text==2016.4.2
    lxml==3.6.0
2.修改了程序中python 2和 python 3不兼容的部分，操作init/notebook/pulll/status确定没有问题。
3.将html文件写入二进制形式修改为utf-8形式
4.该文件一样的存在笔记资源下载不完全，无法链接资源等问题。