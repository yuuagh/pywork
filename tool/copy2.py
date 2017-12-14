#! /usr/bin/env python   
# -*- coding: utf-8 -*-   
import re
import os
import shutil
import msvcrt
import traceback

sourceDir = r"D:\project2\src"
targetDir = r"C:\Users\Administrator\AppData\Local\client\src" 
shutil.rmtree(targetDir);
shutil.copytree(sourceDir, targetDir)