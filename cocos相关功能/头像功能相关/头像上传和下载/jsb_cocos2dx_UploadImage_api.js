/**
 * @module cocos2dx_UploadImage
 */
var hh = hh || {};

/**
 * @class UploadImage
 */
hh.UploadImage = {

/**
 * @method UploadPictures
 * @param {String} arg0
 * @param {int} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @param {function} arg4
 */
UploadPictures : function (
str, 
int, 
str, 
str, 
func 
)
{
},

/**
 * @method DownPictures
 * @param {String} arg0
 * @param {int} arg1
 * @param {String} arg2
 * @param {function} arg3
 */
DownPictures : function (
str, 
int, 
str, 
func 
)
{
},

/**
 * @method OnHttpRequestDownCompleted
 * @param {cc.network::HttpClient} arg0
 * @param {cc.network::HttpResponse} arg1
 */
OnHttpRequestDownCompleted : function (
httpclient, 
httpresponse 
)
{
},

/**
 * @method OnHttpRequestCompleted
 * @param {cc.network::HttpClient} arg0
 * @param {cc.network::HttpResponse} arg1
 */
OnHttpRequestCompleted : function (
httpclient, 
httpresponse 
)
{
},

/**
 * @method destoryInstance
 */
destoryInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {UploadImage}
 */
getInstance : function (
)
{
    return UploadImage;
},

};
