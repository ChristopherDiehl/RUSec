package com.ransomware;

import org.springframework.data.mongodb.repository.MongoRepository;

public interface InfectedRepository extends MongoRepository<Infected, String> {
	public Infected findById(String id);
}
