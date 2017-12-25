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
	// 获取选择器单例
	static UploadImage* getInstance();
	// 销毁
	static void destoryInstance();

public:

	// 上传
	void UploadPictures(std::string url, int userId, std::string imagePath, std::string eventName, const std::function<void(int)>& callback);
	void OnHttpRequestCompleted(HttpClient* client, HttpResponse* response);

	// 下载
	void DownPictures(std::string url, int userId, std::string eventName, const std::function<void(int)>& callback);
	void OnHttpRequestDownCompleted(HttpClient* client, HttpResponse* response);

protected:
	UploadImage();
protected:
	static UploadImage* s_instance;

	// 上传
	std::function<void(int)>	m_callback;
	std::string					m_eventName;
	int							m_userId;

	// 下载
	std::function<void(int)>		m_downCallback;
	std::string						m_downEventName;
	int								m_downUserId;

};

#endif