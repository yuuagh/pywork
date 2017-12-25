#include "base/ccConfig.h"
#ifndef __cocos2dx_ImagePicker_h__
#define __cocos2dx_ImagePicker_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_ImagePicker_class;
extern JSObject *jsb_ImagePicker_prototype;

bool js_cocos2dx_ImagePicker_ImagePicker_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_cocos2dx_ImagePicker_ImagePicker_finalize(JSContext *cx, JSObject *obj);
void js_register_cocos2dx_ImagePicker_ImagePicker(JSContext *cx, JS::HandleObject global);
void register_all_cocos2dx_ImagePicker(JSContext* cx, JS::HandleObject obj);
bool js_cocos2dx_ImagePicker_ImagePicker_setAttr(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_getPlayerId(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_openCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_openPhoto(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_setListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_getImageSize(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_getCompress(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_removeListener(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_destoryInstance(JSContext *cx, uint32_t argc, jsval *vp);
bool js_cocos2dx_ImagePicker_ImagePicker_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __cocos2dx_ImagePicker_h__
