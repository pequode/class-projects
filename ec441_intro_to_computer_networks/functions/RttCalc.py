#!/usr/bin/env python
# coding: utf-8

# In[2]:


RTT1=200
RTT2=210

Prob1=0.5
Prob2=0.5
alpha = 0.125

EstRTT = 205
DevRTT = 5
Timeout = EstRTT + 4*DevRTT
print(Timeout)
quit()

from pylab import *
import random
EstRTT=0
EstRTTs=[]
for i in range(10000):
	SampleRTT = random.sample([RTT1,RTT2],1)[0]
	EstRTT = (1-alpha)*EstRTT + alpha*SampleRTT
	EstRTTs.append(EstRTT)
plot(EstRTT)
draw()


# In[1]:


# Signal recived Attenuation*g(t)+gausianNosie()
#gt is the transmition function 
#Perror = q(squrt((2*qb)/N0))
#power per bit(PPB) = Energy per bit / symbol time(ST) 
#Perror = Q(squrt((2*PPB*ST)/N0))
#transrate(TR) = 1/ST
#Perror = Q(squrt((2*PPB/TR)/N0))

# signal x(t) = sum(Ak*g(t-kt))
#power dencity(f) = 1/ST * magnitude(G(F))**2

#channel decides how much signal you can get 
#power over data rate is in whats 
#if you want to use rate 
#bandwith is also proporional to R 
#means that the chanel cant be shared if the 
#data rate gets higher  
#g(t)is a forie trnasfor to G(f)


# In[ ]:





# In[ ]:





# In[ ]:




