package com.handinhand.controller;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import org.springframework.web.bind.annotation.PathVariable;

import com.handinhand.model.Parking;
import com.handinhand.model.ParkingSlot;
import com.handinhand.model.PrintData;
import com.handinhand.model.Product;
import com.handinhand.model.Shopping;
import com.handinhand.model.Smartbike;
import com.handinhand.model.Stock;
import com.handinhand.model.Transaction;
import com.handinhand.model.User;
import com.handinhand.model.VoterUser;

public class MySQLAccess {
	 private static Connection connect = null;
	 private static Connection connect1 = null;
	  private static Statement statement = null;
	  private static PreparedStatement preparedStatement = null;
	  private static ResultSet resultSet = null;
	  private static PreparedStatement preparedStatement1 = null;
	  private static ResultSet resultSet1 = null;

  public static Connection connectJDBCToAWSEC2() {

	    System.out.println("----MySQL JDBC Connection Testing -------");
	    Connection connection = null;
	    try {
	        Class.forName("com.mysql.jdbc.Driver");
	    } catch (ClassNotFoundException e) {
	        System.out.println("Where is your MySQL JDBC Driver?");
	        e.printStackTrace();
	        return connection;
	    }

	    System.out.println("MySQL JDBC Driver Registered!");


	    try {
	        connection = DriverManager.getConnection("jdbc:mysql://" + "localhost" + ":" + 3306 + "/" + "voting", "root", "password");
	        System.out.println("Connection Failed!:\n" + e.getMessage());
	    }

	    if (connection != null) {
	        System.out.println("SUCCESS!!!! You made it, take control     your database now!");
	    } else {
	        System.out.println("FAILURE! Failed to make connection!");
	    }
	    return connection;

	}



		 public  ArrayList<VoterUser>  getAllVotingUser(){
			 ArrayList<VoterUser> arrayList = new ArrayList<VoterUser>();
			  try {
				  connect = connectJDBCToAWSEC2();
				  preparedStatement = connect
					      .prepareStatement("SELECT * FROM users");
					 resultSet = preparedStatement.executeQuery();
				     while (resultSet.next()) {
				    	 VoterUser voterUser = new VoterUser();
				    	 if(resultSet.getInt("VoterId") == 1){
				    		 voterUser.setDob("01/01/1996");
				    	 }
				    	 else  if(resultSet.getInt("VoterId") == 2){
				    		 voterUser.setDob("20/02/1996");
				    	 }
				    	 else  if(resultSet.getInt("VoterId") == 3){
				    		 voterUser.setDob("10/03/1996");
				    	 }
				    	 else  if(resultSet.getInt("VoterId") == 4){
				    		 voterUser.setDob("29/04/1996");
				    	 }

				    	 voterUser.setVoterId(resultSet.getInt("VoterId"));
				    	 voterUser.setName(resultSet.getString("Name"));
				    	 voterUser.setAddress(resultSet.getString("Address"));
				    	 voterUser.setStatus(resultSet.getInt("Status"));
				    	 arrayList.add(voterUser);
				     }
				     resultSet.close();
				     preparedStatement.close();
				     connect.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
			  return arrayList;
			}

		 public  Map<String,Integer>  getResult(){
			 Map<String,Integer> map1 = new HashMap<>();
			  try {
				  connect = connectJDBCToAWSEC2();
				  preparedStatement = connect
					      .prepareStatement("SELECT * FROM candidate");
					 resultSet = preparedStatement.executeQuery();
				     while (resultSet.next()) {
				    	 int count = resultSet.getInt("CountVOTE");
				    	 String partyName = resultSet.getString("PartyName").trim();
				    	 map1.put(partyName, count);
				     }
				     resultSet.close();
				     preparedStatement.close();
				     connect.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
			  return map1;
			}

		 public int getStatus(int id) {
				int status=0;
				  try {
					  Connection connect = connectJDBCToAWSEC2();
					  PreparedStatement preparedStatement = connect
					      .prepareStatement("select * from users where VoterId = "+id);
					ResultSet resultSet = preparedStatement.executeQuery();

				     while (resultSet.next()) {
				    	 status = resultSet.getInt("Status");
				       }

				     resultSet.close();
				     preparedStatement.close();
				     connect.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}
			return status;
			}

		 public int updateVotingUser(VoterUser tr){

			 try {
				  connect1 = connectJDBCToAWSEC2();
				  String updateTableSQL = "UPDATE  users SET  Status = ? WHERE VoterId = ?";
			      PreparedStatement preparedStatement1 = connect1.prepareStatement(updateTableSQL);
			      preparedStatement1.setInt(1, tr.getStatus());
			      preparedStatement1.setInt(2, tr.getVoterId());
			      preparedStatement1.executeUpdate();

				  preparedStatement1.close();
			     connect1.close();

				 return 1;

			} catch (SQLException e) {
				e.printStackTrace();
			}
			return 0;
			}

		 public int updateAllVotingUser(){

			 try {
				  connect1 = connectJDBCToAWSEC2();
				  String updateTableSQL = "UPDATE  users SET  Status = 3";
			      PreparedStatement preparedStatement1 = connect1.prepareStatement(updateTableSQL);
			      preparedStatement1.executeUpdate();

				  preparedStatement1.close();
			     connect1.close();

				 return 1;

			} catch (SQLException e) {
				e.printStackTrace();
			}
			return 0;
			}

		 public int updateAllPartyCOunt(){

			 try {
				  connect1 = connectJDBCToAWSEC2();
				  String updateTableSQL = "UPDATE  candidate SET  CountVOTE = 0";
			      PreparedStatement preparedStatement1 = connect1.prepareStatement(updateTableSQL);
			      preparedStatement1.executeUpdate();

				  preparedStatement1.close();
			     connect1.close();

				 return 1;

			} catch (SQLException e) {
				e.printStackTrace();
			}
			return 0;
			}

		 public int updateCandidate(int vote,String partyName){

			 try {
				  connect1 = connectJDBCToAWSEC2();
				  String updateTableSQL = "UPDATE candidate SET  CountVOTE = ? WHERE PartyName = ?";
			      PreparedStatement preparedStatement1 = connect1.prepareStatement(updateTableSQL);
			      preparedStatement1.setInt(1, vote);
			      preparedStatement1.setString(2, partyName);
			      preparedStatement1.executeUpdate();

				  preparedStatement1.close();
			     connect1.close();

				 return 1;

			} catch (SQLException e) {
				e.printStackTrace();
			}
			return 0;
			}

		 public int getCandidateCount(String partyName){
				int count = 0;
			 try {
				 connect = connectJDBCToAWSEC2();
				  preparedStatement = connect
					      .prepareStatement("SELECT * FROM candidate WHERE PartyName = '"+partyName+"'");
					 resultSet = preparedStatement.executeQuery();
				     while (resultSet.next()) {
				    	 count =resultSet.getInt("CountVOTE");
				     }
				     resultSet.close();
				     preparedStatement.close();
				     connect.close();

			} catch (SQLException e) {
				e.printStackTrace();
			}
			return count;
			}

}
