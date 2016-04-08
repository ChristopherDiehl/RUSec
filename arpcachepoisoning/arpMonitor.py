from scapy import *
def arp_monitor(filename, count):
	pkts =sniff(filter="arp", count=count)
	wrpcap(filename,pkts)
	return 1;

#doesn't store anythng
def arp_monitor():
	sniff(prn=arp_monitor_callback,filter="arp",store=0)

def arp_monitor_callback( pkt):
	if ARP in pkt and pkt[ARP].op in(1,2):
		return pkt.sprintf("%ARP.hwsrc% %ARP.psrc%")

