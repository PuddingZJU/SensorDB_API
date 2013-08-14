#ifndef SENSORDB_H
#define SENSORDB_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <qmessagebox.h>
#include "sensordata.h"

using std::string;

class SensorDB
{
private:
    
    QSqlDatabase db;
public:
    SensorDB();
    ~SensorDB();
    void OpenDB(const string& ipaddress, const string& dbName, const string& UID, const string& PWD);
	bool isOpen();
	//int get
    void CloseDB();
	bool ExecuteSQL(string sqlcommand);
    SensorDataSet ExecuteSQL_SelectFromSensorDataTable(string sqlcommand);
    SensorData SelectDataByID(int id);
    SensorDataSet SelectDataByIDSection(int id_start,int id_end);
    SensorDataSet SelectDataByDataTypeId(int id);
    SensorDataSet SelectDataByDataTypeName(string Name);
    SensorDataSet SelectDataByOperatorId(int id);
    SensorDataSet SelectDataByOperatorName(string Name);
    SensorDataSet SelectDataByDeviceId(int id);
    SensorDataSet SelectDataByDeviceName(string Name);
    SensorDataSet SelectDataByActivityId(int id);
    SensorDataSet SelectDataByActivityName(string Name);
    SensorDataSet SelectDataByActivityTypeId(int id);
    SensorDataSet SelectDataByActivityTypeName(string Name);
    SensorDataSet SelectDataByPositionId(int id);
    SensorDataSet SelectDataByPositionName(string Name);
    bool AddData(SensorDataSet dataset);
};

#endif // SENSORDB_H
