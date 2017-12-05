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
    nc          = open(fname + '.gb')
    str         = nc.read()
    nc.close()

    # 去除干扰信息
    str         = re.sub(r'\.\.>', '..', str)

    # 取CDS到protein_id="xxxx"之间内容
    pattern     = r'CDS.*?protein_id=".*?".*?gene=".*?"'
    p           = re.compile(pattern, re.S|re.I)
    result      = p.findall(str)

    
    # 得到目标字符串 得到 "xxx..xxx protein_id里面内容"
    newpattern  = r'([\d]+?\.\.[\d]+,[\d]+?\.\.[\d]+,?[\d]+?\.\.[\d]+|[\d]+?\.\.[\d]+,?[\d]+?\.\.[\d]+|[\d]+?\.\.[\d]+).*protein_id="(.+?)".*gene="(.+?)"'
    p2 = re.compile(newpattern, re.S|re.I)
    # 数据存入字典中
    dic     = {}
    geneDic = {}
    for unit in result:
        result2         = p2.findall(unit)
        value           = re.split(',', result2[0][0])
        key             = result2[0][1]
        dic[key]        = value
        geneDic[key]    = result2[0][2]
    
    return (dic, geneDic)

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
    (dic, geneDic)  = getTargetData(fname)
    content         = getContent(fname)
    fl              = open(dirname + '\\' + name + '.txt', 'wb')
    length          = len(content)
    for unit in dic:
        pt = ''
        for k in dic[unit]:
            pt = pt + k + ','

        lh = len(pt)
        if lh > 0:
            pt = pt[0:lh - 1]

        fl.write('name = ' + name + ', protein_id = ' + unit + ', ' + 'gene = ' + geneDic[unit] + ', position = ' + pt + ":\n")

        for k in dic[unit]:
            # 字符串 content 是从0的下标开始
            value   = re.split(r'\.\.', k)
            bg      = int(value[0]) - 1 
            ed      = int(value[1]) - 1
            if bg > length - 1:
                bg = length - 1
                print 'begin beyond the max length'

            if ed > length - 1:
                print 'end beyond the max length' + ', length = ' + str(length) + ', ed = ' + str(ed)
                ed = length - 1

            final   = content[bg : ed]
            fl.write(final)

        fl.write("\n")

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
