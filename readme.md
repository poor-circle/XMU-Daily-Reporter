# XMU-Daily-Reporter

## Description 简介

这是一个厦门大学每日健康打卡系统的自动汇报程序，它可以通过smtp邮件服务通知你打卡的结果。程序支持每日定时打卡（默认在早上六点到八点随机选择一个时间开始打卡）。
你可以让本网站每天给你自动打卡，或者选择在自己的linux或windows设备上打卡。    

## Quick Start 快速开始

如果你没有自己的服务器，我们推荐使用Github Action来打卡。

### 使用Github Action打卡

1. 注册一个github账户。

2. 点击右上角的Starred按钮，收藏本程序

![image](https://user-images.githubusercontent.com/51276909/156751454-4c7b1d17-bca7-4084-8d0e-fdbf3ea590c8.png)

3. 再点击右上角的Fork按钮

![image](https://user-images.githubusercontent.com/51276909/156751558-243c0417-db3e-4a46-a5a2-2c10afa36a7f.png)

这会克隆一个你自己的打卡程序，并跳转到你自己的仓库。

3. 点击Settings:

![image](https://user-images.githubusercontent.com/51276909/156022067-de25036b-99e7-4011-85e2-f66510a4301c.png)

4. 选择Secret下的action

![image](https://user-images.githubusercontent.com/51276909/156022503-4eb5f6ff-ddc3-4af4-bfa7-8fc8e0a18a27.png)


5. 点击New repository secret，添加你的个人登录信息。

![image](https://user-images.githubusercontent.com/51276909/156101931-ea607179-8bec-49ed-871b-f04c965e2b86.png)


6. 填入以下内容。

![image](https://user-images.githubusercontent.com/51276909/156102027-3766e951-8d9a-4b0d-bfc2-df1321d6ce59.png)


value的内容可以从这里复制，记得把配置改成你自己的学号，密码，以及邮箱地址和密码。

```jsonc
{
    "xmu": {
        "ID": "21620192203361",
        "password": "123456" 
    },
    "mail": {
        "address": "114514114514@qq.com",
        "smtp_password": "123456"
    },
}
```

如果你不需要程序发送邮件提醒你打卡结果，则可以删掉邮箱有关的配置，如下所示：

```jsonc
{
    "xmu": {
        "ID": "23320779999999",
        "password": "123456"
    }
}
```


我们推荐使用QQ邮箱，因为它会在微信/QQ中弹出通知，符合国情。当然你也可以使用你自己喜欢的邮箱。这是[QQ邮箱设置SMTP服务的教程](https://jingyan.baidu.com/article/6079ad0eb14aaa28fe86db5a.html) 。注意，你获取的SMTP授权码就是需要填入的密码。


7. 点击Add secret保存配置。

![image](https://user-images.githubusercontent.com/51276909/156102191-e5b24a05-7935-46bf-bc75-b09f3e82d059.png)

8. 激活定时打卡

回到主页，点击左上角的Actions：

![image](https://user-images.githubusercontent.com/51276909/156023756-2b7da67f-35f2-4050-9a79-87991e8b689d.png)

点击绿色按钮激活脚本功能

![image](https://user-images.githubusercontent.com/51276909/156103209-1bdb465e-3de6-4ff7-8c11-ecf182cf110a.png)

点击Enbale workflow激活定时打卡功能

![image](https://user-images.githubusercontent.com/51276909/156103315-13d053d0-02e6-4929-a215-9db9ed41ee57.png)

现在，程序会自动在每天上午六点钟到八点钟，随机选择一个时间开始打卡。
      

9. 除了定时打卡，你也可以用这个网站手动打卡。我们建议您现在手动打一次卡，验证一下配置是否正确。

![image](https://user-images.githubusercontent.com/51276909/156913850-d598b8b0-1023-4223-b9f7-e7964d069eb0.png)

点击绿色的Run workflow按钮来触发手动打卡。

刷新页面，可以看到打卡正在进行中：

![image](https://user-images.githubusercontent.com/51276909/156023994-204c03ed-4067-45b5-a4a1-b35409d0bba1.png)

变为绿色则打卡完成。

点击可查看详情：

![image](https://user-images.githubusercontent.com/51276909/156100629-951f7ee5-db38-48e6-bfa6-bfd6100062cc.png)

10. 打卡成功后，如果你有设置邮件地址，那么程序会向你的邮箱发送邮件。
          
以下是邮件的示例（含成功和失败两种情况）    

![succeed](https://user-images.githubusercontent.com/51276909/156104359-b2c6310c-23de-472e-894e-495b84d3db45.png)
   
![failed](https://user-images.githubusercontent.com/51276909/156104386-237671ae-4178-4261-a400-e28137c6e11a.png)

11. 如果要修改定时打卡时间，请打开文件： [.github/workflows/main.yml](.github/workflows/main.yml)

![image](https://user-images.githubusercontent.com/51276909/156103631-71d74364-5fa2-4207-b085-2de299ac680a.png)

这里的 0 22 * * * 代表在UTC+0的时区的22点打卡。由于中国是UTC+8时区，因此默认是早上六点开始执行任务。

12. 如果要修改随机打卡的时间段，请打开文件： [bin/github_action/sleep.sh](bin/github_action/sleep.sh)

当任务被定时触发（而不是手动触发）时，这个脚本会随机睡眠1-7200秒，如果要修改随机打卡的时段，只需要将7200修改为合适的值。

13. 更新程序

如果程序有更新，你可以点此升级

![image](https://user-images.githubusercontent.com/51276909/156751156-a1c9eb3f-1472-44fa-8cf7-12122ac8a8c3.png)


### 使用自己的设备打卡

请从github的release界面下载程序。   

[下载地址](https://github.com/poor-circle/XMU-Daily-Reporter/releases)     
记得选择合适的系统版本。目前我们只提供```x86-windows```/```x64-windows```/```x64-linux```这三个版本。  
解压文件，在```report_setting.json```中编辑程序的设置。如果程序找不到它，会自动生成一个默认的配置文件。 
有些人会将在windows上将其设置为开机自启动，也有些人会在linux服务器上设置每日的定时任务来实现真正的全自动打卡。这取决于你的设备情况。    
       
## security and duty 安全和责任说明

你不应该使用这个程序撒谎。本程序汇报的内容是可以通过```setting.json```中的```form_data```一项来修改的，本程序只不过默认你身体健康而已。如果你发烧或者移动到其他城市，请及时手动更新表单。      
       
github上的个人信息会被加密存储。如果你选择用自己的设备打卡，则你的个人信息将会明文保存在你的本地计算机，请小心照看它防止泄露。        

我们使用HTTPS和SSL证书以及额外的AES-128算法来加密传输你的信息，这和官方网站使用的加密方法是一致的。我们不会将你的个人信息发送给别人，你可以阅读源代码来确认这一点。           

## 完整的配置文件解释

以下是配置文件中高级选项的解释。

除了你的学号和xmu登录密码，其他都是可选项。

```jsonc
{
    "form_data": "blablaaaaaaaaa" ,  //每次打卡时post的表单信息，如果你生病了记得改
    "mail": {
        "address": "1000000@qq.com", //填入你的邮箱地址，如果不想发送通知邮件，填入一个空字符串("")即可。 
        "reporter_name": "HAL-9000", //汇报机器人的名字，会在通知邮件中显示。
        "smtp_password": "123456"    //你的邮箱的smtp服务的密码
    },
    "report_retry": {
        "counts": 20,                 //打卡失败时重试的次数
        "duration": 10               //打卡失败时每次重试间隔的秒数
    },
    "user_agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",  //浏览器信息
    //学生个人信息
    "xmu": {
        "ID": "23320779999999",      //你的学号
        "password": "123456"         //你的密码
    }
}
```

## compile 编译
  
我们使用cmake来组织工程，使用[vcpkg包管理器](https://github.com/microsoft/vcpkg/blob/master/README_zh_CN.md)来安装第三方库，你的c++编译器需要支持C++17标准。     

以下是编译的步骤：

0. 装C++编译环境（Windows上安装Visual Studio，Linux上安装gcc/clang）  
1. 安装vcpkg        
2. 用vcpkg安装第三方库          
3. 使用IDE，或者直接使用cmake编译本项目

许多IDE都支持CMAKE工程，如Visual Studio，CLION，安装好cmake插件的Visual Studio Code。

你需要在vcpkg中安装这些库：
1. [spdlog](https://github.com/gabime/spdlog)
2. [mailio](https://github.com/karastojko/mailio)
3. [nlohmann-json](https://github.com/nlohmann/json)
4. [cpp-httplib](https://github.com/yhirose/cpp-httplib)

