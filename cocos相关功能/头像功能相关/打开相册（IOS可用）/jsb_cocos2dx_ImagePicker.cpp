#include "jsb_cocos2dx_ImagePicker.hpp"
#include "cocos2d_specifics.hpp"
#include "ImagePicker.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    JS::RootedObject global(cx, ScriptingCore::getInstance()->getGlobalObject());
    isNewValid = JS_GetProperty(cx, global, "initializing", &initializing) && initializing.toBoolean();
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_ImagePicker_class;
JSObject *jsb_ImagePicker_prototype;

bool js_cocos2dx_ImagePicker_ImagePicker_setAttr(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_setAttr : Invalid Native Object");
    if (argc == 3) {
        int arg0 = 0;
        double arg1 = 0;
        int arg2 = 0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= JS::ToNumber( cx, args.get(1), &arg1) && !isnan(arg1);
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_setAttr : Error processing arguments");
        cobj->setAttr(arg0, arg1, arg2);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_setAttr : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_getPlayerId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_getPlayerId : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getPlayerId();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_getPlayerId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_openCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_openCamera : Invalid Native Object");
    if (argc == 0) {
        cobj->openCamera();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_openCamera : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_openPhoto(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_openPhoto : Invalid Native Object");
    if (argc == 0) {
        cobj->openPhoto();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_openPhoto : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_setListener : Invalid Native Object");
    if (argc == 1) {
        std::function<void (std::basic_string<char>)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](std::basic_string<char> larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_setListener : Error processing arguments");
        cobj->setListener(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_setListener : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_getImageSize(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_getImageSize : Invalid Native Object");
    if (argc == 0) {
        int ret = cobj->getImageSize();
        jsval jsret = JSVAL_NULL;
        jsret = int32_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_getImageSize : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath : Error processing arguments");
        std::string ret = cobj->getFramworkResourceRealPath(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera : Invalid Native Object");
    if (argc == 1) {
        std::function<void (std::basic_string<char>)> arg0;
        do {
		    if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
		    {
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, args.thisv().toObjectOrNull(), args.get(0)));
		        auto lambda = [=](std::basic_string<char> larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg0 = lambda;
		    }
		    else
		    {
		        arg0 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera : Error processing arguments");
        cobj->callImagePickerWithPhotoAndCamera(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_getCompress(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_getCompress : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->getCompress();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_getCompress : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ImagePicker* cobj = (ImagePicker *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_ImagePicker_ImagePicker_removeListener : Invalid Native Object");
    if (argc == 0) {
        cobj->removeListener();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_removeListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_ImagePicker_ImagePicker_destoryInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        ImagePicker::destoryInstance();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_destoryInstance : wrong number of arguments");
    return false;
}

bool js_cocos2dx_ImagePicker_ImagePicker_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        ImagePicker* ret = ImagePicker::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
        if (ret) {
            js_proxy_t *jsProxy = js_get_or_create_proxy<ImagePicker>(cx, (ImagePicker*)ret);
            jsret = OBJECT_TO_JSVAL(jsProxy->obj);
        } else {
            jsret = JSVAL_NULL;
        }
    } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_ImagePicker_ImagePicker_getInstance : wrong number of arguments");
    return false;
}


void js_ImagePicker_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ImagePicker)", obj);
}
void js_register_cocos2dx_ImagePicker_ImagePicker(JSContext *cx, JS::HandleObject global) {
    jsb_ImagePicker_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ImagePicker_class->name = "ImagePicker";
    jsb_ImagePicker_class->addProperty = JS_PropertyStub;
    jsb_ImagePicker_class->delProperty = JS_DeletePropertyStub;
    jsb_ImagePicker_class->getProperty = JS_PropertyStub;
    jsb_ImagePicker_class->setProperty = JS_StrictPropertyStub;
    jsb_ImagePicker_class->enumerate = JS_EnumerateStub;
    jsb_ImagePicker_class->resolve = JS_ResolveStub;
    jsb_ImagePicker_class->convert = JS_ConvertStub;
    jsb_ImagePicker_class->finalize = js_ImagePicker_finalize;
    jsb_ImagePicker_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("setAttr", js_cocos2dx_ImagePicker_ImagePicker_setAttr, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPlayerId", js_cocos2dx_ImagePicker_ImagePicker_getPlayerId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("openCamera", js_cocos2dx_ImagePicker_ImagePicker_openCamera, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("openPhoto", js_cocos2dx_ImagePicker_ImagePicker_openPhoto, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setListener", js_cocos2dx_ImagePicker_ImagePicker_setListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getImageSize", js_cocos2dx_ImagePicker_ImagePicker_getImageSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getFramworkResourceRealPath", js_cocos2dx_ImagePicker_ImagePicker_getFramworkResourceRealPath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("callImagePickerWithPhotoAndCamera", js_cocos2dx_ImagePicker_ImagePicker_callImagePickerWithPhotoAndCamera, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCompress", js_cocos2dx_ImagePicker_ImagePicker_getCompress, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeListener", js_cocos2dx_ImagePicker_ImagePicker_removeListener, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("destoryInstance", js_cocos2dx_ImagePicker_ImagePicker_destoryInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_cocos2dx_ImagePicker_ImagePicker_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_ImagePicker_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_ImagePicker_class,
        dummy_constructor<ImagePicker>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ImagePicker", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<ImagePicker> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_ImagePicker_class;
        p->proto = jsb_ImagePicker_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_cocos2dx_ImagePicker(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "hh", &ns);

    js_register_cocos2dx_ImagePicker_ImagePicker(cx, ns);
}

