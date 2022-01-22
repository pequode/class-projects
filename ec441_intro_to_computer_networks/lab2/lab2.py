#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import scipy
import numpy 
import pyshark
import scapy
import mininet
import nest_asyncio
nest_asyncio.apply()
a= pyshark.FileCapture('lab2_ec441_fall2020.pcapng')

sum1 = 0 
sum2 = 0 
sum3 = 0
sec = dir(a[0].frame_info)
ssc = a[0].frame_info.time_epoch
#print(ssc)
#print(sec)
listofIP = []
for pack in a:
  sum1 = sum1+1 
  testString = "ICMP"
  ipv6 = '6'
  srcip = pack.ip.src
  dstip = pack.ip.dst
  
  if srcip not in listofIP:
      listofIP.append(srcip)
  if dstip not in listofIP:
      listofIP.append(dstip)
  
  printVal = pack.ip.version
  sum2 = sum2+(testString==pack.highest_layer) 
  sum3 = sum3+(ipv6==pack.ip.version) 
  if (printVal==ipv6):
      print(printVal,sum3)
sum4 = len(listofIP)
print(listofIP)
print(sum1,sum2,sum3,sum4)
# EC441 Fall 2020
# Lab2: network detective / final exam prep

# The purpose of this lab is to prepare you for
# your take-home final exam, which will have a 
# similar format.


# This lab can be performed with 2 authors.

# Download the file  lab2_ec441_fall2020.pcapng
# from the following url
# 
# http://curl.bu.edu:44120/static/content/lab2_ec441_fall2020.pcapng
#
# and answer the following questions about the packets captured
#
#
# The answers should be written into the variables provided.

# When you are done, submit this file at
#   http://curl.bu.edu:44120/assignment/lab2


#
# This problem can be completed using any combination of
# wireshark, tshark, pyshark


# Directions: replace -1 with the correct value, like 42 or 0 or 3.14

# Q0. How many packets were captured?

packet_count = 5221#sum1#5221

# Q1. How many ICMP packets were captured?

icmp_packet_count = 58#sum2#58


# Q2. How many IPv6 packets were captured?

ipv6_packet_count =0# sum3 # 0

# Q3. How many unique IP addresses were captured

ip_unique_count = 6# sum4 # 6

# Q4. A problem solving chart was downloaded and the exchange was recorded.
# How many arrows lead to the "Oh No!" box.

ohno_arrows = 3 # if done directly if indirectly the number is 7  # done manually through wire shark 


# Q5. A file "large_word_list.txt" was retrieved from a website. What
# was the throughput for this request, measured in megabits/second?
# NOTE: throughput is defined as  DATA / TIME. For the time,
# use the time required from the HTTP GET  until the file was delivered, 
# and use the file size as the amount of data delivered (making sure
# to convert the units into Mb/s)
streamn = 1
b = pyshark.FileCapture(
    'lab2_ec441_fall2020.pcapng',
    display_filter='tcp.stream eq %d' % streamn) #from https://stackoverflow.com/questions/50000818/follow-tcp-stream-using-python-and-pyshark
leng = 0 # only when dest is user 

des = "10.0.0.6"
timestart = -123
endtime = 123
print(len(b))
count = 0
for pack in b:
    count = count+1
    if(pack.highest_layer =="HTTP" and timestart == -123):
        timestart =  pack.frame_info.time_epoch
    if (des ==pack.ip.dst):
        print(pack.ip.dst)
        leng = leng + int(pack.length)
    if(count ==736):
        endtime=pack.frame_info.time_epoch 
#endtime=b[count].frame_info.time_epoch 
timetaken =float(endtime)-float(timestart)
leninmb = 1044590/1000000#taken from wireshark 
through = leninmb/timetaken
print(through)
#pack.length
# pack.highest_layer =="HTTP"
# pack.frame_info.time_epoch
throughput = 0.6673737488989004