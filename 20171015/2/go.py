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

    pattern     = r'>.+?gene = .+?,.+?\n.+?\n'
    p           = re.compile(pattern, re.S|re.I)
    result      = p.findall(str)
    dic         = {}
    for unit in result:
        localPattern    = r'gene = (.+?),'
        localP          = re.compile(localPattern, re.S|re.I)
        localResult     = localP.findall(unit)

        if dic.has_key(unit):
            dic[localResult[0]].append(unit)
        else:
            dic[localResult[0]] = []
            dic[localResult[0]].append(unit)

    return dic

def getAllData2(dirname, fname, name):
    result  = getTargetData(fname)
    # make dir
    dirname = dirname + '\\' + name
    mkdir(dirname)
    shutil.rmtree(dirname)
    mkdir(dirname)

    for key in result:
        okey    = re.sub(r'/', '_', key)
        fl      = open(dirname + '\\' + okey + '.fasta', 'wb')
        print('gene = ' + key)
        length  = len(result[key])
        fl.write('gene = ' + key + ', length = ' + str(length) + '\n')
        for content in result[key]:
            fl.write(content)    
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
