package com.ransomware;
import org.springframework.data.annotation.Id;

public class Infected {
	@Id
	private String Id;
	private String key;
	private String iv;
	private String ip;
	
	public void setKey(String key) {
		this.key = key;
	}
	public String getKey() {
		return this.key;
	}
	public void setIv(String iv) {
		this.iv = iv;
	}
	public String getIv() {
		return this.iv;
	}
	public void setIp(String ip) {
		this.ip = ip;
	}
	public String getIp() {
		return this.ip;
	}
}
