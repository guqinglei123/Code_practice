import os
import urllib.request
 
 
print("downloading with urllib")
 
url0 = "https://www.evernote.com/shard/s542/res/89928ce1-da0d-40f9-a44a-4686f7a71b2d.png"
LocalPath = os.path.join('E:/','89928ce1-da0d-40f9-a44a-4686f7a71b2d.png')
urllib.request.urlretrieve(url0,LocalPath)
    #第一个参数url:需要下载的网络资源的URL地址
    #第二个参数LocalPath:文件下载到本地后的路径
# for item in range(1, 15):
#     file = "lecture" + str(item) + ".pdf"
#     url = url0 + file
#     print("downloading with " + file)
#     LocalPath = os.path.join('E:/',file)
#     #os.path.join将多个路径组合后返回
#     urllib.request.urlretrieve(url,LocalPath)

 