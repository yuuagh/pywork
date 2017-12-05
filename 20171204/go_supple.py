# -*- coding:utf-8 -*-
# @author yuding
# 2017-11-27
import re
import os
import shutil
import msvcrt
import traceback

def mkdir(path):
    # 去除首位空格
    path        = path.strip()
    # 去除尾部 \ 符号
    path        = path.rstrip("\\")
    isExists    = os.path.exists(path)
    if not isExists:
        os.makedirs(path)

def lineMethod(fileName):
    f                       = open(fileName, "r")
    lines                   = f.readlines()  #读取全部内容
    needMulLine             = False #多行行标记
    tagArray                = []
    contentArray            = []

    for line in lines:
        content = re.match(r'>.+?', line, re.S | re.I)
        if content:
            #匹配到 '>'这样的一行
            needMulLine          = False
            tagArray.append(line)
        else:

            if needMulLine == False:
                needMulLine = True
                contentArray.append(line.strip())
            else:
                contentArray[-1] = contentArray[-1] + line.strip()

    f.close()

    return (tagArray, contentArray)

# 获得替换的内容
def getContent(fname):
    tf          = open(fname + '.fasta')
    first       = tf.readline() #读取第一行，这一行不要
    content     = tf.read() #从第二行开始
    # 删除头部和换行符
    content     = re.sub(r'\n', '', content)
    tf.close()
    return content

def getAllData2(dirname, fname, name):
    (tagArray, contentArray)  = lineMethod(fname + '.fasta')
    fl              = open(dirname + '\\' + name + '.fasta', 'wb')
    lengthTag       = len(tagArray)
    lengthContent   = len(contentArray)
    if lengthTag != lengthContent:
        raise Exception("处理出错") #抛出异常
    
    for i in range(0, lengthTag):
        fl.write(tagArray[i])
        fl.write(contentArray[i])
        if i != lengthTag - 1: #最后一行不要回车
            fl.write('\n')

    fl.close()

def getPath():
    # 从当前文件路径中获取目录
    dname       = os.path.dirname(os.path.realpath(__file__))
    dname       = dname + '\\source'
    filelist    = os.listdir(dname)
    names       = []
    for filename in filelist:  
        rl = re.split(r'\.', filename)
        names.append(rl[0])
        
    names = list(set(names))
    return names

def getPackageData():
    curfile = os.path.dirname(os.path.realpath(__file__)) 
    names   = getPath()
    # make dir
    mkdir(curfile + '\\result')
    shutil.rmtree(curfile + '\\result')
    mkdir(curfile + '\\result')
    
    log     = open(curfile + '\\log.txt', 'wb')
    log.write('result path: ' + curfile + '\\result' + '\n')
    for name in names:
        try:
            getAllData2(curfile + '\\result', curfile + '\\source\\' + name, name)
            print('analysis id = ' + name + ',success')
            log.write('analysis id = ' + name + ',success' + '\n')
        except Exception, e:
            print('analysis id = ' + name + ',fail')
            log.write('analysis id = ' + name + ',fail')
            log.write('message: ' + e.message)
    log.close()
    print('analysis finish')
    print("Press 'd' to exit...")
    while True:
        if ord(msvcrt.getch()) in [68, 100]:
            break


if __name__ == '__main__':
    getPackageData()
