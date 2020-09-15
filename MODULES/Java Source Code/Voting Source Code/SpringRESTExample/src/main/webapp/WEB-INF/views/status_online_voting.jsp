<%@page import="com.handinhand.model.User"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%@ page import="com.handinhand.controller.MySQLAccess"%>
<%@ page import="com.handinhand.model.*"%>
<%@ page import="java.util.*"%>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</head>
<body style="background-color: #9dc8e2" align="center">
<h3>Finger Print Authentication and Online Voting Application</h3>

	<br>
	<br>
	
<%
	//UserBean user = new UserBean();
	MySQLAccess mySQLAccess = new MySQLAccess();
	List<VoterUser> trsList = mySQLAccess.getAllVotingUser();
%>
<table align="center" class="table table-bordered" style="width: 1000px">
	<tr>
		<th></th>
		<th>Voter Id</th>
		<th>Date of Birth</th>
		<th>Voter Name</th>
		<th>Voter Address</th>
		<th>Status</th>
	</tr>
	<tr>
		<%  int count=0;
			for (VoterUser user1 : trsList) {
		%>
		<% if(user1.getVoterId() == 1){
		%>
		<td><img src="./images/omprakash.jpg" style="width:100px;height:100px;"/> 
		</td>
		<%
		} else if(user1.getVoterId() == 2){
		%>
		<td><img src="./images/aditya.jpg" style="width:100px;height:100px;" />
		 </td>
		<%
		} else if(user1.getVoterId() == 3){
		%>
		<td><img src="./images/apurva.jpg"  style="width:100px;height:100px;"/> 
		</td>
		<%
		} else if(user1.getVoterId() == 4){
		%>
		<td><img src="./images/kundan.jpg"  style="width:100px;height:100px;"/>
		 </td>
		<%
		} 
		%>
		<td><%=user1.getVoterId()%></td>
		<td><%=user1.getDob() %></td>
		<td><%=user1.getName()%></td>
		<td><%=user1.getAddress()%></td>
		
		<% if(user1.getStatus() == 1){
		%>
		<td><a href="/Voting/casteVote/?VoterId=<%=user1.getVoterId()%>" style="color:red;">Vote</a></td>
		<%
		} else if(user1.getStatus() == 2){
			count++;
		%>
		<td>Vote Casted Successfully </td>
		<%
		} else if(user1.getStatus() == 3){
		%>
		<td>Yet to Cast Vote </td>
		<%
		} 
		%>
	</tr>
	<%
		}
		//}
	%>
	<tr>
	<% if(count == 4){ %>
	<td ></td>
	<td ></td>
	<td ></td>
	<td ></td>
		<td > <a href="/Voting/getResults" style="color:red;">Show Results</a></td>
		<% } %>
	</tr>
	
</table>
</body>
</html>