#include <boost\test\minimal.hpp>
#include <sensordb.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <qstring.h>
#include <qstringlist.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using namespace boost::minimal_test;
string db_address;
string db_name;
string db_uid;
string db_pwd;

void loaddbconnectconfig(){
	ifstream db_connect_in("dbconnect.config");
	db_connect_in>>db_address;
	db_connect_in>>db_name;
	db_connect_in>>db_uid;
	db_connect_in>>db_pwd;
	db_connect_in.close();
	BOOST_REQUIRE(db_address.size()!=0 && db_address.size()!=0 && db_address.size()!=0 && db_address.size()!=0 );

}

SensorDataSet LoadData(string filepath){
	ifstream in(filepath);
	string in_str="";
	SensorDataSet sds;
	while(std::getline(in,in_str)){
		if(!in_str.empty()){
			QString qstr = string2qstring(in_str);
			QStringList qlist = qstr.split('\t');
			ChannelList cl;
			int channelnum = qlist[7].toInt();
			for (int i = 0; i <channelnum; i++)
			{
				cl.push_back(Channel(qlist[10+i].toStdString()));
			}
			sds.PushBackSensorData(SensorData(cl,channelnum,qlist[0].toInt(),qlist[3].toInt(),qlist[2].toInt(),qlist[4].toInt(),qlist[1].toInt(),qlist[8].toInt(),qlist[9].toInt(),qlist[5].toDouble(),QDateTime::fromString(qlist[6],"yyyy-MM-dd hh:mm:ss")));
		}
	}
	in.close();
	return sds;
}

bool compare(SensorDataSet &orign,SensorDataSet &cursds){
	if(orign.Count() == cursds.Count()){
		for (int i = 0; i < orign.Count(); i++)
		{
			if(orign.GetSensorData(i) != cursds.GetSensorData(i)){
				return false;
			}
		}
	}
	else{
		return false;
	}
	return true;
}

int test_main(int argc,char* argv[]){
	loaddbconnectconfig();
	SensorDB db;
	db.OpenDB(db_address,db_name,db_uid,db_pwd);
	if(!db.isOpen()){
		BOOST_FAIL("数据库连接错误：数据库没有打开！");
	}
	db.ExecuteSQL("Truncate Table SensorDataTable");
	cout<<"Writing Data"<<endl;
	db.AddData(LoadData("all.txt"));
	cout<<"Test Start"<<endl;
	BOOST_CHECK(compare(db.SelectDataByActivityId(8),LoadData("activity.txt")));
	BOOST_CHECK(compare(db.SelectDataByActivityName("摔倒后爬起"),LoadData("activity.txt")));
	BOOST_CHECK(compare(db.SelectDataByDataTypeId(1),LoadData("datatype.txt")));
	BOOST_CHECK(compare(db.SelectDataByDataTypeName("huawei"),LoadData("datatype.txt")));
	BOOST_CHECK(compare(db.SelectDataByDeviceId(3),LoadData("device.txt")));
	BOOST_CHECK(compare(db.SelectDataByDeviceName("I9300"),LoadData("device.txt")));
	BOOST_CHECK(compare(db.SelectDataByOperatorId(1),LoadData("operator.txt")));
	BOOST_CHECK(compare(db.SelectDataByOperatorName("李嘉俊"),LoadData("operator.txt")));
	BOOST_CHECK(compare(db.SelectDataByPositionId(3),LoadData("position.txt")));
	BOOST_CHECK(compare(db.SelectDataByPositionName("裤子侧口袋（左）"),LoadData("position.txt")));
	BOOST_CHECK(compare(db.SelectDataByActivityTypeId(4),LoadData("activitytype.txt")));
	BOOST_CHECK(compare(db.SelectDataByActivityTypeName("摔倒"),LoadData("activitytype.txt")));
	BOOST_CHECK(compare(db.SelectDataByIDSection(25,112),LoadData("25-112.txt")));
	cout<<"Test Finish"<<endl;
	db.ExecuteSQL("Truncate Table SensorDataTable");
	return 0;
}

