#beta.py: say Hello, wait for greeting
#import socket as s

# a=s.socket(s.AF_INET, s.SOCK_DGRAM)
# a.bind(("155.41.14.50",9002))
# a.sendto(b"Question?", ("128.197.128.9",9001))
# print("sent")
# msg,ca = a.recvfrom(1024)
# print(msg)
# a.sendto(msg, ("128.197.128.9",9001))
# print("sent2")
# msgs,caa = a.recvfrom(1024)
# print(msgs)

#beta.py: say Hello, wait for greeting
import socket as s
a=s.socket(s.AF_INET, s.SOCK_DGRAM)
a.bind( ("10.0.0.2",9002))
for i in range(10):
	a.sendto(b"Hello", ("10.0.0.1",9001))
	msg,ca = a.recvfrom(100)
	print(msg)
