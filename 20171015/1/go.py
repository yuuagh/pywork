# -*- coding:utf-8 -*-
# @author yuding
# 2017-09-23

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

# 获得目标字符串
def getTargetData(fname):
    # 先得到大致内容
    nc          = open(fname + '.fasta')
    str         = nc.read()
    nc.close()

    pattern     = r'gene = (.+?),'
    p           = re.compile(pattern, re.S|re.I)
    result      = p.findall(str)
    result      = list(set(result))
    return result

# 获得替换的内容
def getContent(fname):
    tf          = open(fname + '.fasta')
    content     = tf.read()
    # 删除头部和换行符
    content     = re.sub(r'.+\.', '', content)
    content     = re.sub(r'\n', '', content)
    tf.close()
    return content

def getAllData2(dirname, fname, name):
    result  = getTargetData(fname)
    fl      = open(dirname + '\\' + name + '.txt', 'wb')
    length  = len(result)
    fl.write('gene:\n')
    fl.write('gene number : ' + str(length) + '\n')
    for unit in result:
        fl.write(unit + '\n')
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

def main():
    getPackageData()

if __name__ == '__main__':
    main()
