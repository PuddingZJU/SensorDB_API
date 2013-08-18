#zhangxaochen:
pySensordb.cpp
	将 cpp 版数据库接口暴露为 C 接口

sensordb.py
	将ctypes对dll函数调用包装为python类，使其与cpp版的数据库接口风格一致

test_sensordb.py
	数据库接口使用测试：
	方法1：	ctypes 直接调用dll导出函数
	方法2：	使用SensorDB包装类

python下可用 nose 测试：
cmake 构建工程； 
SensorDB_API_shared 设为启动项；
生成 SensorDB_API.dll, 将其拷贝到 <xxx>\SensorDB_API\src ；
在当前路径下启动 cmd， 输入 nosetests， 如果顺利，看到类似输出：
”
	.
	-----------------------------------------------------------------
	Ran 2 tests in 16.567s
	OK
“