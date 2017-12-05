# -*- coding:utf-8 -*-
# @author yuding
# 2017-11-27
import re
import os
import shutil
import msvcrt
import traceback

'''
CDS             complement(join(89788..89816,90357..90588,68175..68291))
                     /trans_splicing
                     /protein_id="BAV38085.1"
                     /gene="rps12"
                     /transl_table=11
                     /note="Zoma_g44"
                     /codon_start=1
                     /product="ribosomal protein S12"
'''

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
    choose                  = False #是否是 cds内容块
    resultDic               = {} #单个cds字典内容
    allResult               = [] #所有的cds的内容
    needTranstionMulLine    = False #transtion需要换行标记
    needNoteMulLine         = False #note需要换行标记
    needProductMulLine      = False #product需要换行标记
    allNum                  = 0

    for line in lines:
        content = re.match(r'\s+CDS\s+(\S+)\n', line, re.S | re.I)

        if content:
            #匹配到'CDS'这样的一行
            choose                  = True
            needTranstionMulLine    = False
            needNoteMulLine         = False
            needProductMulLine      = False
            contentGroup            = content.groups()
            resultDic['CDS']        = contentGroup[0]
            allNum                  = allNum + 1
        else:
            #判断'CDS'下的内容
            if choose:
                #'\s*/(.+)=(.+)\n 匹配 /xx=xx
                #\s*/(.+)\n       匹配 /xx
                inResult    = re.match(r'\s*/(.+)\n', line, re.S | re.I)        # /xx 
                if inResult:
                    inResult2 = re.match(r'\s*/(.+)=(.+)\n', line, re.S | re.I) # /xx=yy
                    if inResult2:
                        inResult = inResult2
                    else:
                        inGroup = inResult.groups()
                        resultDic[inGroup[0]] = -1
                        continue

                #符合 inResult的格式
                if inResult:
                    inGroup = inResult.groups()
                    #translation 有多个换行 需要特殊处理
                    if inGroup[0] == 'translation':
                        needTranstionMulLine        = False
                        oneResult                   = re.match(r'\s*/translation=(".+")', line, re.S | re.I)
                        resultDic['translation']    = ''
                        if oneResult:
                            oneResultGroups             = oneResult.groups()
                            resultDic['translation']    = oneResultGroups[0]
                            needTranstionMulLine = False
                        else:
                            #多行字符
                            needTranstionMulLine        = True
                            mulResult                   = re.match(r'\s*/translation=(".+)\n', line, re.S | re.I)
                            mulResultGroups             = mulResult.groups()
                            resultDic['translation']    = mulResultGroups[0].strip() # strip 去除头尾空格
                    elif inGroup[0] == 'note':
                        needNoteMulLine             = False
                        oneResult                   = re.match(r'\s*/note=(".+")', line, re.S | re.I)
                        resultDic['note']           = ''
                        if oneResult:
                            oneResultGroups             = oneResult.groups()
                            resultDic['note']           = oneResultGroups[0]
                            needNoteMulLine             = False
                        else:
                            #多行字符
                            needNoteMulLine             = True
                            mulResult                   = re.match(r'\s*/note=(".+)\n', line, re.S | re.I)
                            mulResultGroups             = mulResult.groups()
                            resultDic['note']           = mulResultGroups[0].strip() # strip 去除头尾空格
                    elif inGroup[0] == 'product':
                        needProductMulLine             = False
                        oneResult                   = re.match(r'\s*/product=(".+")', line, re.S | re.I)
                        resultDic['product']           = ''
                        if oneResult:
                            oneResultGroups             = oneResult.groups()
                            resultDic['product']           = oneResultGroups[0]
                            needProductMulLine             = False
                        else:
                            #多行字符
                            needProductMulLine             = True
                            mulResult                   = re.match(r'\s*/product=(".+)\n', line, re.S | re.I)
                            mulResultGroups             = mulResult.groups()
                            resultDic['product']           = mulResultGroups[0].strip() # strip 去除头尾空格
                    else:
                        resultDic[inGroup[0]]           = inGroup[1]

                else:
                    final = re.match(r'ORIGIN', line, re.S | re.I) #ORINGIN是最后结束的标志
                    if final:
                        choose       = False
                        if len(resultDic) > 0:
                            allResult.append(resultDic)
                            resultDic = {}
                            break #跳出循环

                    newTag = re.match(r'\s{5}\S+\s+\S+\n', line, re.S | re.I) #代表有新的标记出现 非cds 
                    #如果出现新标记代表cds块处理结束
                    if newTag:
                       choose       = False
                       allResult.append(resultDic)
                       resultDic    = {}
                    else: #没有新标记，表示还是处理当前块的内容，目前只判断 translation 和cds 有换行的可能性， 如果以后有新的/xx子项需要换行， 需要修改程序
                        mulResult = re.match(r'\s{21}(.+)\n', line, re.S | re.I)
                        if needTranstionMulLine: #/translation 有换行
                            if mulResult:
                                resultDic['translation'] = resultDic['translation'] + mulResult.group().strip()
                        elif needNoteMulLine: #/note 有换行
                            if mulResult:
                                resultDic['note'] = resultDic['note'] + mulResult.group().strip()
                        elif needProductMulLine: #/product 有换行
                            if mulResult:
                                resultDic['product'] = resultDic['product'] + mulResult.group().strip()
                        else: #此行代表cds有换行
                            if mulResult:
                                resultDic['CDS'] = resultDic['CDS'] + mulResult.group().strip()

    #预防cds是文件最后一块
    if len(resultDic) > 0:
        allResult.append(resultDic)
        resultDic = {}

    print '匹配到CDS段 NUM = ' + str(allNum) + ', 容器值 NUM = ' + str(len(allResult))

    f.close()

    return allResult

# 获得目标字符串
def getTargetData(fname):
    # 先得到大致内容
    allResult = lineMethod(fname + '.gb')
    dic     = {}
    geneDic = {}
    translationDic = {}
    tag = 0
    try:
        for unit in allResult:
            cdsMatch                   = re.match(r'.*?([\d]+?\.\.[\d]+,[\d]+?\.\.[\d]+,?[\d]+?\.\.[\d]+|[\d]+?\.\.[\d]+,?[\d]+?\.\.[\d]+|[\d]+?\.\.[\d]+)', unit['CDS'], re.S|re.I)
            tag = tag + 1
            if cdsMatch:
                cdsGroups = cdsMatch.groups()

            if len(cdsGroups) == 0:
                print 'cds 不正确, value = ' + unit['CDS'] + ', 此条cds数据不统计'
                continue

            #value                       = re.split(',', cdsGroups[0])
            value                       = cdsGroups[0]
            proteinidGroups = []
            geneGroups      = []
            translationGroups = []
            if unit.has_key('protein_id'):
                proteinidMatch             = re.match(r'"(.+?)"', unit['protein_id'], re.S|re.I) #去掉双引号
                if proteinidMatch:
                    proteinidGroups = proteinidMatch.groups()
                else:
                    print 'protein_id 不正确， cds = ' + unit['CDS'] + ', 此条cds数据不统计'
                    continue
            #else:
            #    print unit['CDS'] + ', not protein_id'

            if unit.has_key('gene'):
                geneMatch                       = re.match(r'"(.+?)"', unit['gene'], re.S|re.I)
                if geneMatch:
                    geneGroups                  = geneMatch.groups()
                else:
                    print 'gene 不正确, protein_id ' + unit['protein_id'] + ', 此条cds数据不统计'
                    continue

            if unit.has_key('translation'):
                translationMatch = re.match(r'"(.+?)"', unit['translation'], re.S|re.I)
                if translationMatch:
                    translationGroups = translationMatch.groups()
                else:
                    print 'translation 不正确, protein_id ' + unit['protein_id'] + ', 此条cds数据不统计'
                    continue

            #else:
            #    print unit['CDS'] + ', not gene'
            if len(proteinidGroups) == 0:
                print 'protein_id len 为空， cds = ' + unit['CDS'] + ', 此条cds数据统计'
               proteinidGroups.append('none_' + str(tag))
            if len(geneGroups) == 0:
                print 'gene len 为空, cds = ' + unit['CDS'] + ', 此条cds数据不统计'
                continue
            if len(translationGroups) == 0:
                print 'translation len 为空, cds = ' + unit['CDS'] + ', 此条cds数据不统计'
                continue

            dic[proteinidGroups[0]]     = value
            geneDic[proteinidGroups[0]] = geneGroups[0]
            translationDic[proteinidGroups[0]] = translationGroups[0]
    except Exception, e:
        print "getTargetData, message = " + e.message
        raise Exception() #异常被抛出
    
    return (dic, geneDic, translationDic)

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
    (dic, geneDic, translationDic) = getTargetData(fname)
    content         = getContent(fname)
    fl              = open(dirname + '\\' + name + '.txt', 'wb')
    length          = len(content)

    for unit in dic:
        fl.write('>name = ' + name + ', protein_id = ' + unit + ', ' + 'gene = ' + geneDic[unit] + ', position = ' + dic[unit] + '\n')
        fl.write(translationDic[unit])
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


if __name__ == '__main__':
    getPackageData()
