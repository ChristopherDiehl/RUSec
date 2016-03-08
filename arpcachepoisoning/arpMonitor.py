from scapy.all import *
def arp_monitor_callback(pkt):
	if ARP in pkt and pkt[ARP].op in(1,2):
		return pkt.sprintf("%ARP.hwsrc% %ARP.psrc%")

#calls function arp_monitor_callback
pkt = sniff(prn=arp_monitor_callback, filter="arp",count=2)
