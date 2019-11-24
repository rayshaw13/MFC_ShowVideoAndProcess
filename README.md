# MFC_ShowVideoAndProcess
无聊的程序，通过MFC和opencv调用显示本地视频和图片并进行处理

## 说明 
工程本身是自己写的一个小程序，通过MFC和opencv来读取本地两段视频和两个图片进行对比，没有多少技术含量，唯一学到的是线程的创建和关闭（通过原子锁）。 
自己想着就把这个项目逐步丰富一下，加入一些图像处理的操作，慢慢写吧。后续会另开一个工程来写QT和opencv的学习。 

## 功能历程 
视频功能：打开摄像头（显示无法打开），打开本地文件，通过第一个视频文件的地址寻找对应的处理后的视频文件，并一同在两个窗口播放。 
图片功能：打开本地图片，通过图片地址寻找对应的图片文件，一同显示。
