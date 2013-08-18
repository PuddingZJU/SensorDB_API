#coding=utf-8
'''
将ctypes对dll函数调用包装为python类，使其与cpp版的数据库接口风格一致
'''
import os, sys, ctypes

# =============================wrapper class
class SensorDB:
	def __init__(self, libPath=None):
		self.__lib=ctypes.cdll.LoadLibrary('./SensorDB_API.dll' if libPath is None else libPath)
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

