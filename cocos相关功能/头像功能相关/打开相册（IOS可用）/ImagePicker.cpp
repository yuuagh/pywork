#include "ImagePicker.h"
//--------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import  "ImagePickerViewController.h"
#import  "RootViewController.h"
#endif
//--------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define JAVA_CLASS              "org/cocos2dx/cpp/ImagePicker"
#define JAVA_FUNC_OPEN_PHOTO    "openPhoto"
#define JAVA_FUNC_OPEN_CAMERA   "openCamera"
#endif
//--------------------------------------------------
USING_NS_CC;
//--------------------------------------------------
ImagePicker* ImagePicker::s_instance = NULL;
//--------------------------------------------------
ImagePicker* ImagePicker::getInstance()
{
    if (s_instance == NULL)
    {
        s_instance = new ImagePicker();
    }
    return s_instance;
}
//--------------------------------------------------
void ImagePicker::destoryInstance()
{
    CC_SAFE_DELETE(s_instance);
}
//--------------------------------------------------
ImagePicker::ImagePicker()
:m_callback(nullptr)
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("ImagePickerEvent", [=](EventCustom* eve)
    {
        std::string* path = (std::string*)eve->getUserData();
        if (path && m_callback != nullptr)
        {
            m_callback(*path);
        }
    });
}
//--------------------------------------------------
void ImagePicker::callImagePickerWithPhotoAndCamera(const std::function<void(std::string)>& callback)
{
    s_instance->init();
    setListener(callback);
}
//--------------------------------------------------
void ImagePicker::setListener(const std::function<void(std::string)>& callback)
{
    m_callback = callback;
}
//--------------------------------------------------
void ImagePicker::removeListener()
{
    m_callback = nullptr;
}
//--------------------------------------------------
void ImagePicker::openPhoto()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ImagePickerViewController* imagePickerViewController = [[ImagePickerViewController alloc] initWithNibName:nil bundle:nil];
    
    RootViewController* _viewController = (RootViewController*)m_viewController;
    [_viewController.view addSubview:imagePickerViewController.view];
    
    [imagePickerViewController localPhoto:m_playerId compressInfo : m_compress sizeInfo : m_size];
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, JAVA_CLASS, JAVA_FUNC_OPEN_PHOTO,"(IFI)V");
    if (ret)
    {
        info.env->CallStaticVoidMethod(info.classID, info.methodID, m_playerId, m_compress, m_size);
    }
#endif
}
//--------------------------------------------------
void ImagePicker::openCamera()
{
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ImagePickerViewController* imagePickerViewController = [[ImagePickerViewController alloc] initWithNibName:nil bundle:nil];
    
    RootViewController* _viewController = (RootViewController*)m_viewController;
    [_viewController.view addSubview:imagePickerViewController.view];
    
    [imagePickerViewController takePhoto];
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo info;
    bool ret = JniHelper::getStaticMethodInfo(info, JAVA_CLASS, JAVA_FUNC_OPEN_CAMERA,"()V");
    if (ret)
    {
        info.env->CallStaticVoidMethod(info.classID, info.methodID);
    }
#endif
*/
}
//--------------------------------------------------
bool ImagePicker::init()
{
    return true;
}

std::string ImagePicker::getFramworkResourceRealPath(std::string fileName)
{
	auto fileBasePath = "src/hallstatic/res/doudizhuDT/x3/" + fileName;
	auto storePath = FileUtils::getInstance()->getWritablePath();
	auto fileSelectPath = storePath + fileBasePath;
	if (FileUtils::getInstance()->isFileExist(fileSelectPath))
	{
		return fileSelectPath;
	}
	return fileBasePath;

}

// 设置玩家id
void ImagePicker::setAttr(int playerId, float compress, int size)
{
    m_playerId = playerId;
    m_compress = compress;
    m_size = size;
}

// 得到玩家id
int ImagePicker::getPlayerId()
{
    return m_playerId;
}

float ImagePicker::getCompress()
{
    return m_compress;
}

int ImagePicker::getImageSize()
{
    return m_size;
}

//--------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void  ImagePicker::setViewController(void* viewController)
{
    m_viewController = viewController;
}
#endif
//--------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
    void Java_org_cocos2dx_cpp_ImagePicker_onImageSaved(JNIEnv* env, jobject thiz, jstring path)
    {
        std::string strPath = JniHelper::jstring2string(path);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ImagePickerEvent", &strPath);
    }
}
#endif
//--------------------------------------------------
