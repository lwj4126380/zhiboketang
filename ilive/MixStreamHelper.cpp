#include "MixStreamHelper.h"
#include <QString>
#include "json/json.h"

MixStreamHelper::MixStreamHelper(std::vector<std::pair<std::string, bool>> streams, const QString sig, int roomId, void *data)
{
	streams_ = streams;
	_roomId = roomId;
	QString urlBase = "http://fcgi.video.qcloud.com/common_access?";
	QString time = QString::number(QDateTime::currentMSecsSinceEpoch() / 1000 + 60*1000);	
	QString md5 = genSign(sig, time);
	m_url = urlBase + "appid=" + QString::number(SuixinboZhiboid) + "&interface=Mix_StreamV2&t=" + time + "&sign=" + md5;
	m_content = genContent(streams);
	m_pCusdata = data;
}

void MixStreamHelper::doRequest()
{
	NetworkHelper::post( m_url, m_content, OnNetworkReply, m_pCusdata );

}

QString MixStreamHelper::genSign(QString key, QString time)
{
	//�㷨MD5(key + t) 
	QString md5;
	QString str = key + time;
	QByteArray bb;
	bb = QCryptographicHash::hash ( str.toUtf8(), QCryptographicHash::Md5 );
	return md5.append(bb.toHex());
}

void MixStreamHelper::OnNetworkReply( int errCode, const QByteArray& bytes, void* pCusData )
{
	if (errCode == 0) 
	{
		QString str(bytes);
		Json::Reader reader;
		Json::Value value;
		if ( reader.parse( str.toStdString(), value ) )
		{
			int retCode = value["code"].asInt();
			if (retCode == 0)
			{
//				Live *pLive = (Live *)pCusData;
//				pLive->onMixStream(MixStreamHelper::outCode);
			}			
		}
	}
	
}



QString MixStreamHelper::genContent(std::vector<std::pair<std::string, bool>> ids)
{
	if (ids.size() <= 1) return nullptr;
	Json::Value req;
	req["timestamp"] = QDateTime::currentMSecsSinceEpoch() / 1000;
	req["eventId"] = QDateTime::currentMSecsSinceEpoch() / 1000;
	//gen interface
	Json::Value reqInterface;
	reqInterface["interfaceName"] = "Mix_StreamV2";	
	//gen para
	Json::Value para;	
	para["app_id"] = 1253488539;
	para["interface"] = "mix_streamv2.start_mix_stream_advanced";
	
    MixStreamHelper::outCode = genStreamCode(ids[0].first + "_0", false, _roomId, "29723");//29723����Ѷ���ṩ��bizid
	para["mix_stream_session_id"] = MixStreamHelper::outCode; 
	para["output_stream_id"] = MixStreamHelper::outCode;
	para["output_stream_type"] = 1;
	para["mix_stream_template_id"] = getTemplate();
	//gen stream list
	Json::Value streams;
    for (int i = 0; i < ids.size(); ++i)
	{
		
		Json::Value streamItem;
		streamItem["input_stream_id"] = genStreamCode(ids[i].first, ids[i].second, _roomId, "29723");
		//layout param ������ģ��
		Json::Value layout;
		layout["image_layer"] = i + 1;
		streamItem["layout_params"] = layout;
		streams[i] = streamItem;
	}
	para["input_stream_list"] = streams;
	reqInterface["para"] = para;
	req["interface"] = reqInterface;
	Json::FastWriter writer;
	std::string reqStr = writer.write(req);
	return QString::fromStdString(reqStr);	
	
}

std::string MixStreamHelper::genStreamCode(std::string id, bool aux, int roomId, std::string code)
{
	//ֱ����=BIZID_MD5(�����_�û���_��������)
	
	std::stringstream oss;
	oss << roomId << "_" << id << "_" << (aux? "aux" : "main");
	QString md5 = QCryptographicHash::hash ( oss.str().c_str(), QCryptographicHash::Md5 ).toHex();
	return code + "_" + md5.toStdString();
}

int MixStreamHelper::getTemplate()
{
	switch(streams_.size())
	{
	case 2:
		return 10;
	case 3:
		return 310;
	case 4:
		return 410;
	case 5:
		return 510;
	case 6:
		return 610;
	default:
		return 0;
	}
}

std::string MixStreamHelper::outCode = "";
