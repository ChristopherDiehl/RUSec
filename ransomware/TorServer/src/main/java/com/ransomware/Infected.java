package com.ransomware;
import org.springframework.data.annotation.Id;

public class Infected {
	@Id
	private String Id;
	private byte[] key;
	private byte[] iv;
	private String ip;
	
	public void setKey(byte [] key) {
		this.key = key;
	}
	public byte[] getKey() {
		return this.key;
	}
	public void setIv(byte[] iv) {
		this.iv = iv;
	}
	public byte[] getIv() {
		return this.iv;
	}
	public void setIp(String ip) {
		this.ip = ip;
	}
	public String getIp() {
		return this.ip;
	}
}
