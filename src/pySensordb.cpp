#include <boost\test\minimal.hpp>
#include <sensordb.h>
#include <fstream>
#include <sstream>

using std::clog;
using std::endl;
using std::string;
using std::ifstream;
using namespace boost::minimal_test;


class MyClass {
public:
	int testInt(int x){
		return x*2;
	}

	string testString(){
		return "in testString()";
	}

	bool testBool(bool b){
		return !b;
	}
};

extern "C" {
	__declspec(dllexport) void* myclassCreate(){
		return new(std::nothrow) MyClass;
	}
	__declspec(dllexport) int myclassTestInt(MyClass* self, int x){
		return self->testInt(x);
	}
	__declspec(dllexport) const char* myclassTestString(MyClass* self){
		int len=sizeof(char)*(self->testString().length()+1);
		char* res=(char*)malloc(len);
		memset(res, 0, len);
		strcpy(res, self->testString().c_str());
		return res;
	}
	__declspec(dllexport) bool myclassTestBool(MyClass* self, bool b){
		//return self->testBool(b);
		return b;
	}

	//==============================SensorDB======================
	__declspec(dllexport) SensorDB* sensordbCreate(void){
		return new(std::nothrow) SensorDB;
	}
	__declspec(dllexport) void sensordbOpenDB(SensorDB* self, const char* ipaddress, const char* dbName, const char* UID, const char* PWD){
		printf("in sensordbOpenDB: %s, %s, %s, %s\n", ipaddress, dbName, UID, PWD);
		return self->OpenDB(ipaddress, dbName, UID, PWD);
	}
	//__declspec(dllexport) void printString(const char* str){
	//	printf("in printString: %s\n", str);
	//}
	__declspec(dllexport) bool sensordbIsOpen(SensorDB* self){
		bool isOpen=self->isOpen();
		printf("in sensordbIsOpen: %d\n", isOpen);
		return isOpen;
		//return b;
	}

	__declspec(dllexport) void sensordbCloseDB(SensorDB* self){
		return self->CloseDB();
	}
	__declspec(dllexport) bool sensordbExecuteSQL(SensorDB* self, const char* sqlcommand){
		bool succ=self->ExecuteSQL(sqlcommand);
		return succ;
	}

	__declspec(dllexport) SensorDataSet* sensordbExecuteSQL_SelectFromSensorDataTable(SensorDB* self, string sqlcommand){
		return new SensorDataSet(self->ExecuteSQL_SelectFromSensorDataTable(sqlcommand));
	}
	__declspec(dllexport) SensorData* sensordbSelectDataByID(SensorDB* self, int id){
		return new SensorData(self->SelectDataByID(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByIDSection(SensorDB* self, int id_start,int id_end){
		return new SensorDataSet(self->SelectDataByIDSection(id_start, id_end));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByDataTypeId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByDataTypeId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByDataTypeName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByDataTypeName(Name));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByOperatorId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByOperatorId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByOperatorName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByOperatorName(Name));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByDeviceId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByDeviceId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByDeviceName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByDeviceName(Name));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByActivityId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByActivityId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByActivityName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByActivityName(Name));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByActivityTypeId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByActivityTypeId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByActivityTypeName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByActivityTypeName(Name));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByPositionId(SensorDB* self, int id){
		return new SensorDataSet(self->SelectDataByPositionId(id));
	}
	__declspec(dllexport) SensorDataSet* sensordbSelectDataByPositionName(SensorDB* self, const char* Name){
		return new SensorDataSet(self->SelectDataByPositionName(Name));
	}
	__declspec(dllexport) bool sensordbAddData(SensorDB* self, SensorDataSet* dataset){
		bool succ=self->AddData(*dataset);
		return succ;
	}

	//=============sensordb_api_test.cpp 抄来的==========
	__declspec(dllexport) SensorDataSet* LoadData(const char* filepath){
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
		return new SensorDataSet(sds);
	}//LoadData

	__declspec(dllexport) bool compare(SensorDataSet *orign,SensorDataSet *cursds){
#ifdef _DEBUG
#endif
		printf("in compare()~~~~~\n");
		if((*orign).Count() == (*cursds).Count()){
			for (int i = 0; i < (*orign).Count(); i++)
			{
				if((*orign).GetSensorData(i) != (*cursds).GetSensorData(i)){
					return false;
				}
			}
		}
		else{
			return false;
		}
		return true;
	}//compare


}//extern "C"


//====================C interface test=================

int test_main( int argc, char* argv[] ){
	SensorDB* db=sensordbCreate();
	sensordbOpenDB(db, "10.12.34.98", "CAPGSensorDB_Test", "capgadmin", "capg11207");
	if(!sensordbIsOpen(db)){
		BOOST_FAIL("数据库连接错误：数据库没有打开！");
	}
	sensordbExecuteSQL(db, "Truncate Table SensorDataTable");
	BOOST_REQUIRE(sensordbAddData(db, LoadData("all.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByActivityId(db, 8),LoadData("activity.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByActivityName(db, "摔倒后爬起"),LoadData("activity.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByDataTypeId(db, 1),LoadData("datatype.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByDataTypeName(db, "huawei"),LoadData("datatype.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByDeviceId(db, 3),LoadData("device.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByDeviceName(db, "I9300"),LoadData("device.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByOperatorId(db, 1),LoadData("operator.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByOperatorName(db, "李嘉俊"),LoadData("operator.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByPositionId(db, 3),LoadData("position.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByPositionName(db, "裤子侧口袋（左）"),LoadData("position.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByActivityTypeId(db, 4),LoadData("activitytype.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByActivityTypeName(db, "摔倒"),LoadData("activitytype.txt")));
	BOOST_CHECK(compare(sensordbSelectDataByIDSection(db, 25,112),LoadData("25-112.txt")));
	//sensordbExecuteSQL(db, "Truncate Table SensorDataTable");
	sensordbCloseDB(db);

	getchar();
	return 0;
}//test_main


