#coding=utf-8
import os, sys, ctypes
from ctypes import *

encoding='gbk'
l2=ctypes.cdll.LoadLibrary('SensorDB_API.dll')

def testPyInterf():
	print("==================testPyInterf===============")
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

# =============================wrapper class
from ctypes import *
class SensorDB:
	def __init__(self, libPath=None):
		self.__lib=cdll.LoadLibrary('./SensorDB_API.dll' if libPath is None else libPath)
		self.__db=self.__lib.sensordbCreate()
	
	def openDB(self, ipAddress, dbName, uid, pwd):
		return bool(self.__lib.sensordbOpenDB(self.__db, ipAddress, dbName, uid, pwd))
	
	def isOpen(self):
		return bool(self.__lib.sensordbIsOpen(self.__db))
		
	def closeDB(self):
		return self.__lib.sensordbCloseDB(self.__db)
	
	def executeSQL(self, sqlStr):
		return self.__lib.sensordbExecuteSQL(self.__db, sqlStr)
	
	def selectDataByDataTypeId(self, id):
		return self.__lib.sensordbSelectDataByDataTypeId(self.__db, id)
	
	def selectDataByDataTypeName(self, name):
		return self.__lib.sensordbSelectDataByDataTypeName(self.__db, name)
	
	def selectDataByOperatorId(self, id):
		return self.__lib.sensordbSelectDataByOperatorId(self.__db, id)
		
	def selectDataByOperatorName(self, name):
		return self.__lib.sensordbSelectDataByOperatorName(self.__db, name)
		
	def selectDataByDeviceId(self, id):
		return self.__lib.sensordbSelectDataByDeviceId(self.__db, id)
		
	def selectDataByDeviceName(self, name):
		return self.__lib.sensordbSelectDataByDeviceName(self.__db, name)
		
	def selectDataByActivityId(self, id):
		return self.__lib.sensordbSelectDataByActivityId(self.__db, id)
		
	def selectDataByActivityName(self, name):
		return self.__lib.sensordbSelectDataByActivityName(self.__db, name)
		
	def selectDataByActivityTypeId(self, id):
		return self.__lib.sensordbSelectDataByActivityTypeId(self.__db, id)
		
	def selectDataByActivityTypeName(self, name):
		return self.__lib.sensordbSelectDataByActivityTypeName(self.__db, name)
		
	def selectDataByPositionId(self, id):
		return self.__lib.sensordbSelectDataByPositionId(self.__db, id)
		
	def selectDataByPositionName(self, name):
		return self.__lib.sensordbSelectDataByPositionName(self.__db, name)
	
	def selectDataByIDSection(self, start, end):
		return self.__lib.sensordbSelectDataByIDSection(self.__db, start, end)
		
	def addData(self, dataset):
		return self.__lib.sensordbAddData(self.__db, dataset)
		
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
	testPyInterf()
	testWrapperClass()
