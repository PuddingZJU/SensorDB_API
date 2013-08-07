#include "sensordata.h"
#include "qdebug.h"
string int2string(int x){
	string res = "";
	std::stringstream ss;
	ss<<x;
	ss>>res;
	return res;
}

string double2string(double x){
	string res = "";
	std::stringstream ss;
	ss<<x;
	ss>>res;
	return res;
}
QString string2qstring(const string& str)
{
	return QString(QString::fromLocal8Bit(str.c_str()));
}
Channel::Channel(string dat)
{
	QString _dat(QString::fromLocal8Bit(dat.c_str()));
	QStringList mlist = _dat.split('$');
	name = mlist[3].toStdString();
	QStringList vlist = mlist[0].split('#');
	QStringList tlist = mlist[1].split('#');
	QStringList flist = mlist[2].split('#');
	for (int i = 0; i < flist.size(); i++)
	{
		RawData t;
		t.frameid = flist[i].toInt();
		t.timestamp = tlist[i].toDouble();
		t.value = vlist[i].toDouble();
		data.push_back(t);
	}
}
bool Channel::operator==(const Channel &a)const{
	return this->name == a.name && this->data == a.data;
}
bool Channel::operator!=(const Channel &a)const{
	return !(*this==a);
}
string Channel::ToString(){
	string dat ="";
	dat += double2string(data[0].value);
	for (int j = 1; j < (int)data.size(); j++)
	{
		dat+="#";
		dat+=double2string(data[j].value);
	}
	dat+="$";
	dat += double2string(data[0].timestamp);
	for (int j = 1; j < (int)data.size(); j++)
	{
		dat+="#";
		dat+=double2string(data[j].timestamp);
	}
	dat+="$";
	dat += int2string(data[0].frameid);
	for (int j = 1; j < (int)data.size(); j++)
	{
		dat+="#";
		dat+=int2string(data[j].frameid);
	}
	dat+="$";
	dat+=name;
	return dat;
}

SensorData::SensorData()
{

}
bool SensorData::operator==(const SensorData &a)const{
	int res = 0 ;
	res += (this->channel == a.channel);
	res += (this->activitybeginframe_id == a.activitybeginframe_id);
	res += (this->activityendframe_id == a.activityendframe_id);
	res += (this->activity_id == a.activity_id);
	res += (this->createtime.toString("yyyy-MM-dd hh:mm:ss").toStdString() == a.createtime.toString("yyyy-MM-dd hh:mm:ss").toStdString());
	res += (this->datatype_id == a.datatype_id);
	res += (this->device_id == a.device_id);
	res += (this->operator_id == a.operator_id);
	res += (this->position_id == a.position_id);
	res += (this->samplerate == a.samplerate);
	res += (this->totalchannelnum == a.totalchannelnum);
	return res == 11;
}
bool SensorData::operator!=(const SensorData &a)const{
	return !(*this==a);
}
SensorData::SensorData(ChannelList channel,int totalchannelnum,int datatypeid,int operatorid,int deviceid,int positionid,int activityid,int activitybeginframeid, int activityendframeid, double samplerate,QDateTime createtime)
{
	this->channel = channel;
	this->totalchannelnum = totalchannelnum;
	datatype_id = datatypeid;
	this->samplerate = samplerate;
	operator_id = operatorid;
	device_id = deviceid;
	position_id = positionid;
	activity_id = activityid;
	activitybeginframe_id = activitybeginframeid;
	activityendframe_id = activityendframeid;
	this->createtime = createtime;
}

SensorData::~SensorData()
{

}

RawData SensorData::GetRawData(int channelid, int i)
{
	return this->channel[channelid].data[i];
}
Channel SensorData::GetChannel(int i){
	return channel[i];
}
int SensorData::GetTotalChannelNum()
{
	return totalchannelnum;
}

int SensorData::GetTotalFrame(int channelid){
	return channel[channelid].data.size();
}

int SensorData::GetDataTypeID()
{
	return datatype_id;
}

double SensorData::GetSampleRate()
{
	return samplerate;
}

QDateTime SensorData::GetCreateTime()
{
	return createtime;
}

int SensorData::GetOperatorID()
{
	return operator_id;
}

int SensorData::GetDeviceID()
{
	return device_id;
}

int SensorData::GetPositionID()
{
	return position_id;
}

int SensorData::GetActivityID()
{
	return activity_id;
}

int SensorData::GetActivityBeginFrameID()
{
	return activitybeginframe_id;
}

int SensorData::GetActivityEndFrameID()
{
	return activityendframe_id;
}

string SensorData::ConvertChannelToString(int channel_i){
	return channel[channel_i].ToString();
}

vector<string> SensorData::GetChannelStringlist(){
	vector<string> channelstr;
	for (int i = 0; i < totalchannelnum; i++)
	{
		channelstr.push_back(ConvertChannelToString(i));
	}
	return channelstr;
}

SensorDataSet::SensorDataSet()
{

}


SensorDataSet::SensorDataSet(vector<SensorData> dataSet)
{
	_dataset = dataSet;
}

SensorDataSet::~SensorDataSet()
{

}

SensorData SensorDataSet::GetSensorData(int i)
{
	return _dataset[i];
}

void SensorDataSet::PushBackSensorData(SensorData data)
{
	_dataset.push_back(data);
}

int SensorDataSet::Count()
{
	return _dataset.size();
}

