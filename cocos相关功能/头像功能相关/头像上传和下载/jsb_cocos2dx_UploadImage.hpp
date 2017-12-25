#include "base/ccConfig.h"
#ifndef __cocos2dx_UploadImage_h__
#define __cocos2dx_UploadImage_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_UploadImage_class;
extern JSObject *jsb_UploadImage_prototype;

bool js_cocos2dx_UploadImage_UploadImage_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_UploadImage_UploadImage_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_UploadImage_UploadImage(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_UploadImage(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_UploadImage_UploadImage_UploadPictures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_UploadImage_UploadImage_DownPictures(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_UploadImage_UploadImage_OnHttpRequestDownCompleted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_UploadImage_UploadImage_OnHttpRequestCompleted(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_UploadImage_UploadImage_destoryInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_UploadImage_UploadImage_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_UploadImage_h__
