# -*- coding:utf-8 -*-
# @author yuding
# 2017-11-27
import re
import os
import shutil
import msvcrt
import traceback

if __name__ == '__main__':
    f           = open('172cds1_1xiaoxie.fasta', 'r')
    names       = open('172name.txt', 'r')
    result      = open('result.txt', 'wb')
    fLines      = f.readlines()  #读取全部内容
    namesLines  = names.readlines()
    nameDic = {}

    for line in namesLines:
        content = re.match(r'(.+),(.+)', line, re.S | re.I)
        if content:
            groups = content.groups()
            nameDic[groups[1].strip()] = groups[0].strip()
    for line in fLines:
        content = re.match(r'>(.+)@(.+)', line, re.S | re.I)
        if content:
            groups = content.groups()
            name = groups[0]
            if nameDic.has_key(name):
                result.write('>' + nameDic[name] + '@' + groups[1])
            else:
                print '提醒： name = ' + name + ', 无法替换！'
        else:
            result.write(line)
    
    f.close()
    names.close()
    result.close()

    print('analysis finish')
    print("Press 'd' to exit...")
    while True:
        if ord(msvcrt.getch()) in [68, 100]:
            break





