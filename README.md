# TrafficMonitor 交通管理系统
这是一个C/S架构的交通管理系统，客户端负责采集图像，发送给服务端，服务端获取图像后对图像进行识别，得到车牌号，并保存到数据库中。

解决方案目录下有四个子目录
- `TMClient` 客户端项目目录
- `TMClientUnitTest` 客户端单元测试项目目录
- `TMServer` 服务端项目目录
- `TMServerClient` 服务端单元测试项目目录

## 开发人员必读

### 添加单元测试的方法
如果要对TMClient项目中的Uploader进行单元测试
1. 在TMClientUnitTest项目中添加一个测试文件`UploaderTest.cpp`
2. 在`UploaderTest.cpp`中编写测试，测试的模板参考`unittest1.cpp`
3. 在解决方案资源管理器中右键点击`TMClientUnitTest`项目，选择属性-链接器-输入-附加依赖项-添加一个`Uploader.obj`
4. 点击菜单栏上的测试-运行-运行所有测试
