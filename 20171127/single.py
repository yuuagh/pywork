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
                                resultDic['CDS'] = resultDic['CDS'] + mulResult.group()

    #预防cds是文件最后一块
    if len(resultDic) > 0:
        allResult.append(resultDic)
        resultDic = {}

    print '匹配到CDS段 NUM = ' + str(allNum) + ', 容器值 NUM = ' + str(len(allResult))

    f.close()

    return allResult

if __name__ == '__main__':
    lineMethod()
