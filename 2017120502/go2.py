# -*- coding:utf-8 -*-
# @author yuding
# 2017-12-05
import re
import os
import shutil
import msvcrt
import traceback

if __name__ == '__main__':
    f           = open('62cds.fasta', 'r')
    fLines      = f.readlines()  #读取全部内容
    result      = open('newResult.fasta', 'wb')
    key         = ''
    value       = ''
    tag         = 0
    willWrite   = True
    for line in fLines:
        if tag == 2:
            tag = 0
            if willWrite:
                result.write(key)
                result.write(value)
            willWrite = True

        tag = tag + 1
        content = re.match(r'>(.+)@(.+)', line, re.S | re.I)
        if content:
            key = line
            #result.write(line)
        else:
            #总长度为3的倍数处理
            if len(line.strip()) % 3 != 0:
                willWrite = False
                print key.strip() + ', 没有处理！'
                continue
            else:
                #enumerate()函数，可以同时枚举字符串或者序列的索引和元素
                newStr = ''
                for id, value in enumerate(line):
                    #最后一个字符是换行符
                    if value == '\n':
                        newStr = newStr + '\n'
                        break

                    if (id + 1) % 3 != 0:
                        newStr = newStr + value
                value = newStr
                #result.write(newStr)

    f.close()
    result.close()
    print('analysis finish')
    print("Press 'd' to exit...")
    while True:
        if ord(msvcrt.getch()) in [68, 100]:
            break





