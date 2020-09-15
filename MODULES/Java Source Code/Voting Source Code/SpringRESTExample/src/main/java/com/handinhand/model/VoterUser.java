package com.handinhand.model;

public class VoterUser {

	int VoterId;
	String Name;
	String Address;
	int status;
	String dob;
	
	public VoterUser() {
		super();
	}

	public VoterUser(int voterId, String name, String address, int status) {
		super();
		VoterId = voterId;
		Name = name;
		Address = address;
		this.status = status;
	}

	public int getVoterId() {
		return VoterId;
	}

	public void setVoterId(int voterId) {
		VoterId = voterId;
	}

	public String getName() {
		return Name;
	}

	public void setName(String name) {
		Name = name;
	}

	public String getAddress() {
		return Address;
	}

	public void setAddress(String address) {
		Address = address;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}
	
	public String getDob() {
		return dob;
	}

	public void setDob(String dob) {
		this.dob = dob;
	}

	@Override
	public String toString() {
		return "VoterUser [VoterId=" + VoterId + ", Name=" + Name
				+ ", Address=" + Address + ", status=" + status + "]";
	}
}
