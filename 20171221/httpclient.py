import re
import os
import shutil
import msvcrt
import traceback
import urllib2

boundary = '----------%s' % "WebKitFormBou3123ndaryEm5WNw6hGiQUBpng"
data = []
data.append('--%s' % boundary)

data.append('Content-Disposition: form-data; name="%s"\r\n' % 'user')
data.append('100000')
data.append('--%s' % boundary)

data.append('Content-Disposition: form-data; name="%s"\r\n' % 'type')
data.append('1')
data.append('--%s' % boundary)

fr=open(r'C:/Users/Administrator/AppData/Local/yudingcpp/100000.png','rb')

data.append('Content-Disposition: form-data; name="%s"; filename="100000.png"' % 'image')
data.append('Content-Type: %s\r\n' % 'image/png')

data.append(fr.read())
fr.close()

data.append('--%s--\r\n' % boundary)
#http_url='http://114.55.250.143:8080/gmfservelt/upServlet?param=user=100000;type=1 -F "image=@100000.png"'
http_url='http://114.55.250.143:8080/'

http_body='\r\n'.join(data)
try:
    #buld http request
    req=urllib2.Request(http_url, data=http_body)
    #header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    #req.add_header('User-Agent','Mozilla/5.0')
    #req.add_header('Referer','http://remotserver.com/')
    #post data to server
    resp = urllib2.urlopen(req, timeout=5)
    #get response
    qrcont=resp.read()
    print qrcont
    
    
except Exception,e:
    print 'http error'