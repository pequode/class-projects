#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Mar 30 22:10:30 2021

@author: whorehay
"""
#insent = "Almost heaven, West Virginia Blue Ridge Mountains, Shenandoah River Life is old there, older than the trees Younger than the mountains, growin' like a breeze"
#insent = "O say can you see by the dawn's early light What so proudly we hailed at the twilight's last gleaming Whose broad stripes and bright stars through the perilous fight O'er the ramparts we watched, were so gallantly streaming? And the rocket's red glare, the bombs bursting in air"
insent = "f you wanna run away with me, I know a galaxy And I can take you for a ride (for a ride) I had a premonition that we fell into a rhythm Where the music don't stop for life (for life)"
which  = 0 
Mixa=[]
Mixb=[]
Mixc=[]
ListOfWords = insent.split()
for i in ListOfWords:
    if which ==0:
        Mixa.append(i)
        which = 1
    elif which ==1:
         Mixb.append(i)
         which = 2
    elif which ==2:
        Mixc.append(i)
        which = 0
L = [Mixa, Mixb,Mixc]
print(L)
with open("ScramSent.txt", "w") as file1:
    for i in L:
        for j in i:
            file1.write(j+" ")
        file1.write("\n")