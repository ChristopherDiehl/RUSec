package com.ransomware;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RansomwareController {

	public RansomwareController(){}
	
	@RequestMapping("/sendDecrypt")
	public Infected sendDecrypt(String infectedId){
		return null;
	}
	
}
