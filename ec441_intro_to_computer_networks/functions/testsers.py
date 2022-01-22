#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 21 03:05:27 2020

@author: whorehay
"""

number10sec =0
dope= True
while(dope):
    numToadd =0
    if (number10sec%360 ==0):
        print("fan running")
        numToadd = numToadd+60;
    if (number10sec%1440 ==0):
        print("water running")
        numToadd = numToadd+4;
    if (number10sec>8640):
        print("Reset")
        number10sec =0
        break
    number10sec = number10sec+numToadd
    number10sec = number10sec+1
print(8640/360)
print(1440/360)