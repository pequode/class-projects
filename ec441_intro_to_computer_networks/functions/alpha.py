#alpha.py: wait for greeting, say Hello
# import socket as s
# b = s.socket(s.AF_INET, s.SOCK_DGRAM)
# print("hahah")
# b.bind( ("10.0.0.1",9001))
# print("fc shit")
# msg,ca = b.recvfrom(100)
# print(msg)
# b.sendto(b"Hello",("10.0.0.2",9002))
import socket as s
b = s.socket(s.AF_INET, s.SOCK_DGRAM)
b.bind( ("10.0.0.1",9001))
for i in range(10):
	msg,ca = b.recvfrom(100)
	print(msg)
	b.sendto(b"Hello",("10.0.0.2",9002))
