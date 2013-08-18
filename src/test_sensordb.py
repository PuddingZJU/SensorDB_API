#coding=utf-8
'''
数据库接口使用测试：
方法1：	ctypes 直接调用dll导出函数
方法2：	使用SensorDB包装类
'''

import os, sys, ctypes
from ctypes import *
from sensordb import SensorDB

encoding='gbk'
l2=ctypes.cdll.LoadLibrary('SensorDB_API.dll')

def testCtypesCall():
	print("==================testCtypesCall===============")
	db=l2.sensordbCreate()
	l2.sensordbOpenDB(db, c_char_p(b'10.12.34.98'), b'CAPGSensorDB_Test', b'capgadmin', b'capg11207')
	isOpen=l2.sensordbIsOpen(db)
	assert c_bool(isOpen).value, u"数据库连接错误：数据库没有打开！"
	print ("DataBase Connected")

	assert l2.sensordbExecuteSQL(db, b"Truncate Table SensorDataTable");
	assert l2.sensordbAddData(db, l2.LoadData(b"all.txt"))
	assert l2.compare(l2.sensordbSelectDataByActivityId(db, 8), l2.LoadData(b"activity.txt"))
	assert l2.compare(l2.sensordbSelectDataByActivityName(db, u"摔倒后爬起".encode(encoding)),l2.LoadData(b"activity.txt"))
	assert l2.compare(l2.sensordbSelectDataByDataTypeId(db, 1),l2.LoadData(b"datatype.txt"))
	assert l2.compare(l2.sensordbSelectDataByDataTypeName(db, b"huawei"),l2.LoadData(b"datatype.txt"))
	assert l2.compare(l2.sensordbSelectDataByDeviceId(db, 3),l2.LoadData(b"device.txt"))
	assert l2.compare(l2.sensordbSelectDataByDeviceName(db, b"I9300"),l2.LoadData(b"device.txt"))
	assert l2.compare(l2.sensordbSelectDataByOperatorId(db, 1),l2.LoadData(b"operator.txt"))
	assert l2.compare(l2.sensordbSelectDataByOperatorName(db, u"李嘉俊".encode(encoding)),l2.LoadData(b"operator.txt"))
	assert l2.compare(l2.sensordbSelectDataByPositionId(db, 3),l2.LoadData(b"position.txt"))
	assert l2.compare(l2.sensordbSelectDataByPositionName(db, u"裤子侧口袋（左）".encode(encoding)),l2.LoadData(b"position.txt"))
	assert l2.compare(l2.sensordbSelectDataByActivityTypeId(db, 4),l2.LoadData(b"activitytype.txt"))
	assert l2.compare(l2.sensordbSelectDataByActivityTypeName(db, u"摔倒".encode(encoding)),l2.LoadData(b"activitytype.txt"))
	assert l2.compare(l2.sensordbSelectDataByIDSection(db, 25,112),l2.LoadData(b"25-112.txt"))
	assert l2.sensordbExecuteSQL(db, b"Truncate Table SensorDataTable")
	l2.sensordbCloseDB(db)

def testWrapperClass():
	print("==================testWrapperClass===============")
	db=SensorDB()
	db.openDB(b'10.12.34.98', b'CAPGSensorDB_Test', b'capgadmin', b'capg11207')
	assert db.isOpen(), u"数据库连接错误：数据库没有打开！"
	print ("DataBase Connected")

	assert db.executeSQL(b"Truncate Table SensorDataTable");
	assert db.addData(l2.LoadData(b"all.txt"))
	assert l2.compare(db.selectDataByActivityId(8), l2.LoadData(b"activity.txt"))
	assert l2.compare(db.selectDataByActivityName(u"摔倒后爬起".encode(encoding)),l2.LoadData(b"activity.txt"))
	assert l2.compare(db.selectDataByDataTypeId(1),l2.LoadData(b"datatype.txt"))
	assert l2.compare(db.selectDataByDataTypeName(b"huawei"),l2.LoadData(b"datatype.txt"))
	assert l2.compare(db.selectDataByDeviceId(3),l2.LoadData(b"device.txt"))
	assert l2.compare(db.selectDataByDeviceName(b"I9300"),l2.LoadData(b"device.txt"))
	assert l2.compare(db.selectDataByOperatorId(1),l2.LoadData(b"operator.txt"))
	assert l2.compare(db.selectDataByOperatorName(u"李嘉俊".encode(encoding)),l2.LoadData(b"operator.txt"))
	assert l2.compare(db.selectDataByPositionId(3),l2.LoadData(b"position.txt"))
	assert l2.compare(db.selectDataByPositionName(u"裤子侧口袋（左）".encode(encoding)),l2.LoadData(b"position.txt"))
	assert l2.compare(db.selectDataByActivityTypeId(4),l2.LoadData(b"activitytype.txt"))
	assert l2.compare(db.selectDataByActivityTypeName(u"摔倒".encode(encoding)),l2.LoadData(b"activitytype.txt"))
	assert l2.compare(db.selectDataByIDSection(25,112),l2.LoadData(b"25-112.txt"))
	assert db.executeSQL(b"Truncate Table SensorDataTable")
	db.closeDB()

if __name__=='__main__':
	testCtypesCall()
	testWrapperClass()
