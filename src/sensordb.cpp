#include "sensordb.h"
#include <qapplication.h>
SensorDB::SensorDB()
{

}
SensorDB::~SensorDB()
{
    db.close();
}
void SensorDB::OpenDB(const string& ipaddress, const string& dbName, const string& UID, const string& PWD){
  db=QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName( "DRIVER={SQL Server};SERVER="+string2qstring(ipaddress)+";UID="+string2qstring(UID)+";PWD="+string2qstring(PWD)+";DATABASE="+string2qstring(dbName)+" ;");
	db.setHostName(string2qstring(ipaddress));
	//db.setDatabaseName(string2qstring(dbName));
	db.setUserName(string2qstring(UID));
	db.setPassword(string2qstring(PWD));
   // db.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3")
    if (!db.open())
    {
		qDebug()<<db.lastError().databaseText();
    }
}
void SensorDB::CloseDB()
{
    db.close();
}

bool SensorDB::ExecuteSQL(string sqlcommand){
	if(db.isOpen()){
        QSqlQuery query;
        QString sqlcmd = string2qstring(sqlcommand);
        if(query.exec(sqlcmd)){
			return true;
			//qDebug()<<"Success";
		}
		else{
			qDebug()<<db.lastError();
		}
	}
	else{
		qDebug()<<"DataBase is not opened";
	}
	return false;
}
bool SensorDB::isOpen(){
	return db.isOpen();
}
SensorDataSet SensorDB::ExecuteSQL_SelectFromSensorDataTable(std::string sqlcommand)
{
    SensorDataSet ds;
	ChannelList channelist;
    int channel_num;
    int datatype_id;
    int operator_id;
    int device_id;
    int position_id;
    int activity_id;
    int activitybeginframe_id;
    int activityendframe_id;
    double samplerate;
    QDateTime createtime;
    if(db.isOpen()){
        QSqlQuery query;
        QString sqlcmd = string2qstring(sqlcommand);
        if(query.exec(sqlcmd)){
                while(query.next()){
					datatype_id = query.value("DataTypeID").toInt();
                    activity_id = query.value("ActivityID").toInt();
                    device_id = query.value("DeviceID").toInt();
                    operator_id = query.value("OperatorID").toInt();
                    position_id = query.value("PositionID").toInt();
                    activitybeginframe_id = query.value("ActivityBeginFrameID").toInt();
                    activityendframe_id = query.value("ActivityEndFrameID").toInt();
                    samplerate = query.value("SampleRate").toDouble();
                    createtime = query.value("CreateTime").toDateTime();
					channel_num = query.value("TotalChannelNum").toInt();
					channelist.clear();
					for(int i=1;i<=channel_num;i++){
                        if(query.value(i).isNull()){
                            break;
                        }					
						string ch = "channel_"+int2string(i);						
						//qDebug() << query.value(string2qstring(ch.c_str())).toString();
						channelist.push_back(Channel(query.value(string2qstring(ch.c_str())).toString().toStdString()));
						//qDebug() << string2qstring((channelist[channelist.size()-1].ToString()));
					}
					ds.PushBackSensorData(SensorData(channelist,channel_num,datatype_id,operator_id,device_id,position_id,
                                         activity_id,activitybeginframe_id,activityendframe_id, samplerate,createtime));
                }
        }
        else{
            qDebug()<<query.lastError();
        }
    }
    else{
        qDebug()<<"DataBase is not opened";
    }
    return ds;
}



SensorData SensorDB::SelectDataByID(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where ID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd).GetSensorData(0);
}

SensorDataSet  SensorDB::SelectDataByIDSection(int id_start,int id_end)
{

    string sqlcmd = "select * from [dbo].[SensorDataTable] where ID between "+int2string(id_start)+" and "+int2string(id_end);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByDataTypeId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where DataTypeID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByDataTypeName(string Name)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where DataTypeID IN (select ID from [dbo].[DataTypeTable] where Name = '"+Name+"')";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByOperatorId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where OperatorID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByOperatorName(string Name)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where OperatorID IN (select ID from [dbo].[OperatorTable] where Name = '"+Name+"')";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByDeviceId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where DeviceID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByDeviceName(string Name)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where DeviceID IN  (select ID from [dbo].[DeviceTable] where Name = '"+Name+"')";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByActivityId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where ActivityID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByActivityName(string Name)
{
   string sqlcmd = "select * from [dbo].[SensorDataTable] where ActivityID IN (select ID from [dbo].[ActivityTable] where Name = '"+Name+"' )";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByActivityTypeId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where ActivityID IN (select ID from [dbo].[ActivityTable] where ActivityType = "+int2string(id)+" )";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByActivityTypeName(string Name)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where ActivityID IN (select ID from [dbo].[ActivityTable] where ActivityType IN (Select ID From [dbo].[ActivityTypeTable] Where Name = '"+Name+"' ) )";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByPositionId(int id)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where PositionID = "+int2string(id);
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

SensorDataSet  SensorDB::SelectDataByPositionName(string Name)
{
    string sqlcmd = "select * from [dbo].[SensorDataTable] where PositionID IN (select ID from [dbo].[PositionTable] where Name = '"+Name+"')";
    return ExecuteSQL_SelectFromSensorDataTable(sqlcmd);
}

bool SensorDB::AddData(SensorDataSet dataset)
{

    string channel_num="";
    string datatype_id="";
    string operator_id="";
    string device_id="";
    string position_id="";
    string activity_id="";
    string activitybeginframe_id="";
    string activityendframe_id="";
    string samplerate="";
    string createtime="";
	for (int i = 0; i < dataset.Count(); i++)
	{
		string cmd = "INSERT INTO [dbo].[SensorDataTable](DataTypeID,ActivityID,DeviceID,OperatorID,PositionID,SampleRate,CreateTime,TotalChannelNum,ActivityBeginFrameID,ActivityEndFrameID";
		for (int j = 1; j <= dataset.GetSensorData(i).GetTotalChannelNum(); j++)
		{
			cmd += (",channel_"+int2string(j));
		}
		cmd+=") VALUES (";
		channel_num = ",'"+int2string(dataset.GetSensorData(i).GetTotalChannelNum())+"'";
		datatype_id = "'"+int2string(dataset.GetSensorData(i).GetDataTypeID())+"'";
		operator_id = ",'"+int2string(dataset.GetSensorData(i).GetOperatorID())+"'";
		device_id = ",'"+int2string(dataset.GetSensorData(i).GetDeviceID())+"'";
		position_id = ",'"+int2string(dataset.GetSensorData(i).GetPositionID())+"'";
		activity_id = ",'"+int2string(dataset.GetSensorData(i).GetActivityID())+"'";
		activitybeginframe_id = ",'"+int2string(dataset.GetSensorData(i).GetActivityBeginFrameID())+"'";
		activityendframe_id = ",'"+int2string(dataset.GetSensorData(i).GetActivityEndFrameID())+"'";
		samplerate= ",'"+double2string(dataset.GetSensorData(i).GetSampleRate())+"'";
		createtime= ",'"+dataset.GetSensorData(i).GetCreateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString()+"'";
		cmd+=(datatype_id+activity_id+device_id+operator_id+position_id+samplerate+createtime+channel_num+activitybeginframe_id+activityendframe_id);
		for (int j = 1; j <= dataset.GetSensorData(i).GetTotalChannelNum(); j++)
		{
			cmd+=(",'"+dataset.GetSensorData(i).GetChannel(j-1).ToString()+"'");
		}
		cmd+=");";
		if(!ExecuteSQL(cmd)){
			return false;
		}
	}
	return true;
}
