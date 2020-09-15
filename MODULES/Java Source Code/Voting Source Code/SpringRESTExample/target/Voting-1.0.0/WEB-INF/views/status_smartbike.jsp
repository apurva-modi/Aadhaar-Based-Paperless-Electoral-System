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
<h3>Smartbike Application</h3>

	<br>
	<br>
<%
	//UserBean user = new UserBean();
	MySQLAccess mySQLAccess = new MySQLAccess();
	List<Smartbike> trsList = mySQLAccess.getAllSmartBikeDetails();
%>
<table align="center" class="table table-bordered" style="width: 1000px">
	<tr>
		<th>Id</th>
		<th>User Name</th>
		<th>Date</th>
		<th>Detection Type</th>
	</tr>
	<tr>
		<%
			/*while(itr.hasNext())
			 {
			 System.out.println(user.getId());*/
			for (Smartbike smartbike : trsList) {
		%>
		<td><%=smartbike.getId()%></td>
		<td><%=smartbike.getName()%></td>
		<td><%=smartbike.getDate()%></td>
		<td><%=smartbike.getDetectionType()%></td>
	</tr>
	<%
		}
		//}
	%>
</table>
</body>
</html>