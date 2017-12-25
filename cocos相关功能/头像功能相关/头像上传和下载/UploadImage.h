#ifndef __UPLOAD_IMAGE__
#define __UPLOAD_IMAGE__

#include "cocos2d.h"
#include "network/HttpClient.h"
using namespace cocos2d;
using namespace std;
using namespace cocos2d::network;

class UploadImage
{
public:
	// ��ȡѡ��������
	static UploadImage* getInstance();
	// ����
	static void destoryInstance();

public:

	// �ϴ�
	void UploadPictures(std::string url, int userId, std::string imagePath, std::string eventName, const std::function<void(int)>& callback);
	void OnHttpRequestCompleted(HttpClient* client, HttpResponse* response);

	// ����
	void DownPictures(std::string url, int userId, std::string eventName, const std::function<void(int)>& callback);
	void OnHttpRequestDownCompleted(HttpClient* client, HttpResponse* response);

protected:
	UploadImage();
protected:
	static UploadImage* s_instance;

	// �ϴ�
	std::function<void(int)>	m_callback;
	std::string					m_eventName;
	int							m_userId;

	// ����
	std::function<void(int)>		m_downCallback;
	std::string						m_downEventName;
	int								m_downUserId;

};

#endif