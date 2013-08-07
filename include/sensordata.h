#ifndef SENSORDATA_H
#define SENSORDATA_H
#undef min
#undef max
#include <vector>
#include <QDateTime>
#include <sstream>
#include <qstring.h>
#include <qstringlist.h>
using std::vector;
using std::string;

string int2string(int x);
string double2string(double x);
QString string2qstring(const string& str);
struct RawData{
	double value;
	double timestamp;
	int frameid;
	
	bool operator==(const RawData &a)const{
		return this->value == a.value && this->frameid == a.frameid && this->timestamp == a.timestamp;
	}
	bool operator!=(const RawData &a)const{
		return !(*this==a);
	}
};
class Channel
{
public:
	Channel(){};
	~Channel(){};
	Channel(string dat);
	string ToString();
	string name;
	vector<RawData> data;
	bool operator==(const Channel &a)const;
	bool operator!=(const Channel &a)const;
};
typedef vector<Channel> ChannelList;

class SensorData
{
private:
	ChannelList channel;
    int totalchannelnum;
    int datatype_id;
    int operator_id;
    int device_id;
    int position_id;
    int activity_id;
    int activitybeginframe_id;
    int activityendframe_id;
    double samplerate;
    QDateTime createtime;
public:
    SensorData();
    ~SensorData();
	SensorData(ChannelList channel,int totalchannelnum,int datatypeid,int operatorid,int deviceid,int positionid,int activityid,
         int activitybeginframeid, int activityendframeid, double samplerate,QDateTime createtime);
	bool operator==(const SensorData &a)const;
	bool operator!=(const SensorData &a)const;
  //  Data(string XMLString);
  //  Data(string XMLPath);
	RawData GetRawData(int channelid, int i);
	vector<string> GetChannelStringlist();
    int GetTotalChannelNum();
	Channel GetChannel(int i);
    int GetDataTypeID();
    int GetOperatorID();
    int GetDeviceID();
    int GetPositionID();
    int GetActivityID();
    int GetActivityBeginFrameID();
    int GetActivityEndFrameID();
    int GetTotalFrame(int channelid);
    QDateTime GetCreateTime();
    double GetSampleRate();
	string ConvertChannelToString(int channel_i);
    string toXMLString();
};

class SensorDataSet
{
private:
    vector<SensorData> _dataset;
public:
    SensorDataSet();
    ~SensorDataSet();
    SensorDataSet(vector<SensorData> sensordataSet);
    int Count();
    void PushBackSensorData(SensorData sensordata);
    SensorData GetSensorData(int i);
};
#endif // SENSORDATA_H