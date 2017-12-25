#include "UploadImage.h"

UploadImage* UploadImage::s_instance = NULL;
UploadImage* UploadImage::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new UploadImage();
	}
	return s_instance;
}

//--------------------------------------------------
void UploadImage::destoryInstance()
{
	CC_SAFE_DELETE(s_instance);
}

UploadImage::UploadImage()
:m_callback(nullptr)
, m_eventName("")
, m_userId(0)
, m_downCallback(nullptr)
, m_downEventName("")
, m_downUserId(0)
{

}

void UploadImage::UploadPictures(std::string url, int userId, std::string imagePath, std::string eventName, const std::function<void(int)>& callback)
{
    //log("yd_ url address is %s", url.c_str());
	m_eventName = eventName;
	m_callback = callback;
	m_userId = userId;

	HttpClient* http = HttpClient::getInstance();
	HttpRequest* req = new HttpRequest();

	req->setRequestType(network::HttpRequest::Type::POST);
	req->setUrl(url.c_str());
	req->setResponseCallback(CC_CALLBACK_2(UploadImage::OnHttpRequestCompleted, this));

	std::string pathKey = FileUtils::getInstance()->fullPathForFilename(imagePath);
	CCLOG("yd_path = %s", pathKey.c_str());

	//auto sifile = PathFindFileName(pathKey);
	Data imgdata = FileUtils::getInstance()->getDataFromFile(pathKey);

	//拿到图片数据
	ssize_t buff = 0;
	unsigned char * pBuffer = FileUtils::getInstance()->getFileData(pathKey, "rb", &buff);
	const char* fileBinary = (const char*)pBuffer;
	CCLOG("yd_fileBinary %s = ", fileBinary);

	//得到图片 文件流大小
	std::string strBin = std::string(fileBinary, buff);

	char s[100];
	sprintf(s, "Content-Disposition: form-data; name=\"image\"; filename=\"%d.jpg\"\r\n", userId);
	std::string dispositionStr = s;

	//设置 http headers  参数 和  数据流
	std::string boundary = "----------------WebKitFormBou3123ndaryEm5WNw6hGiQUBpng";
	std::string bound = boundary;
	std::vector<std::string> headers;
	headers.push_back("Content-Type:multipart/form-data; boundary = " + bound);

	std::string str = "\r\n--" + boundary + "\r\n";
	str = str + dispositionStr;
	str = str + "Content-Type: image/jpeg\r\n\r\n";
	str = str + strBin;
	str = str + "\r\n--" + boundary + "--\r\n";

	// 设置设置Header
	req->setHeaders(headers);
	//设置 RequesData

	//log(str.c_str());

	req->setRequestData(str.data(), str.size());
	CCLOG("yd_str data = %s \n str .size = %d \n", str.data(), str.size());
	//发送
	http->send(req);
	//关闭
	req->release();
};

void UploadImage::OnHttpRequestCompleted(HttpClient* client, HttpResponse* response)
{
	if (!response->isSucceed())
	{
		CCLOG("yd_error");
		CCLOG("yd_error buffer: %s", response->getErrorBuffer());
		CCLOG("yd_error code: %d", (int)response->getResponseCode());
		m_callback(0);
		return;
	}

	const char * pTag = response->getHttpRequest()->getTag();

	if (m_callback != nullptr)
	{
		m_callback(1);
	}

	if (!m_eventName.empty())
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(m_eventName);
	}
	
};

// 下载
void UploadImage::DownPictures(std::string url, int userId, std::string eventName, const std::function<void(int)>& callback)
{
	m_downEventName = eventName;
	m_downCallback	= callback;
	m_downUserId	= userId;

	HttpClient* http = HttpClient::getInstance();
	HttpRequest* req = new HttpRequest();

	req->setRequestType(network::HttpRequest::Type::GET);
	req->setUrl(url.c_str());
	//req->setResponseCallback(CC_CALLBACK_2(UploadImage::OnHttpRequestCompleted, this));

	req->setResponseCallback([userId, callback, eventName](HttpClient* client, HttpResponse* response)
	{
		if (!response->isSucceed())
		{
			CCLOG("yd_error");
			CCLOG("yd_error down buffer: %s", response->getErrorBuffer());
			CCLOG("yd_error down code: %d", (int)response->getResponseCode());
			callback(0);
			return;
		}

		std::vector<char> *data = response->getResponseData();
		std::string res;
		res.insert(res.begin(), data->begin(), data->end());

		// dump data
		std::vector<char> *buffer = response->getResponseData();
		char * buf = (char *)malloc(buffer->size());
		std::copy(buffer->begin(), buffer->end(), buf);

		char s[100];
		sprintf(s, "%d.jpg", userId);
		std::string sFileName = s;

		std::string path = FileUtils::getInstance()->getWritablePath() + sFileName;
		CCLOG("yd_ download the path = %s", path.c_str());

		FILE *fp = fopen(path.c_str(), "wb+");
		fwrite(buf, 1, buffer->size(), fp);
		fclose(fp);

		if (callback != nullptr)
		{
			callback(1);
		}

		if (!eventName.empty())
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName);
		}
	});

	//发送
	http->send(req);
	//关闭
	req->release();

}

void UploadImage::OnHttpRequestDownCompleted(HttpClient* client, HttpResponse* response)
{

}


