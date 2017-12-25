#ifndef _IMAGEPICKER_H_
#define _IMAGEPICKER_H_

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif	// CC_PLATFORM_ANDROID

/**
 * 图像选择器
 */
class ImagePicker
{
public:
    // 获取选择器单例
    static ImagePicker* getInstance();



    // 销毁
    static void destoryInstance();
public:
    // 显示本地相册与相机选择器
    void callImagePickerWithPhotoAndCamera(const std::function<void(std::string)>& callback);
    
    // 设置监听
    void setListener(const std::function<void(std::string)>& callback);
    
    // 移除监听
    void removeListener();
    
    // 打开相册
    void openPhoto();
    
    // 打开相机
    void openCamera();

	// 获取真实图片路径
	std::string getFramworkResourceRealPath(std::string fileName);

	// 设置属性 玩家id 压缩率 大小（字节）
	void setAttr(int playerId, float compress, int size);

    // 得到玩家id
    int getPlayerId();
    float getCompress();
    int getImageSize();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // 设置AppController
    void setViewController(void* viewController);
#endif // CC_PLATFORM_IOS

protected:
    // 初始化
    bool init();
    
    ImagePicker();
    
protected:
    int m_playerId;
    float m_compress;
    int m_size;
    std::function<void(std::string)> m_callback;
    static ImagePicker* s_instance;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void* m_viewController;
#endif // CC_PLATFORM_IOS
    
};

#endif // _IMAGEPICKER_H_