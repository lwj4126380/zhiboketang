#pragma once

#include "MixStreamHelper.h"
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <QString>
#include "SxbServerHelper.h"
#include "../utils/cconstants.h"




class MixStreamHelper
{
	
public:
	/**
	@brief ����һ���������󣬻����������https://www.qcloud.com/document/product/267/8832
	@param [in] streams ��Ҫ�������Ĭ�ϵ�һ��Ϊ����
	@param [in] sig ��Ѷ��ֱ���������̨�����õ�API��Ȩkey
	@param [in] roomId �����
	@param [in] data �Զ�������
	*/
	MixStreamHelper(std::vector<std::pair<std::string, bool>> streams, const QString sig, int roomId, void *data);
	void doRequest();
	
private:
	QString genSign(QString key, QString time);
	QString genContent(std::vector<std::pair<std::string, bool>> ids);
	static void OnNetworkReply(int errCode, const QByteArray& bytes, void* pCusData);
	std::string genStreamCode(std::string id, bool aux, int roomId, std::string code);
	int getTemplate();

private:
	std::vector<std::pair<std::string, bool>> streams_;
	unsigned bigIndex_;
	int _roomId;
	QString	  m_url;
	QString	  m_content;
	SxbRecFun m_receiver;
	void*	  m_pCusdata;
	static std::string outCode;
	 
	
};

