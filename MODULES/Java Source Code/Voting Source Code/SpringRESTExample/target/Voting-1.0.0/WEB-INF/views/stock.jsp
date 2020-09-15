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
<h3>Shopping Cart Application Stock Details</h3>

	<br>
	<br>
<%
	//UserBean user = new UserBean();
	MySQLAccess mySQLAccess = new MySQLAccess();
	List<Stock> trsList = mySQLAccess.getAllStocks();
%>
<table align="center" class="table table-bordered" style="width: 1000px">
	<tr>
		<th>Id</th>
		<th>Product Name</th>
		<th>Message</th>
		<th>Stock Quantity</th>
	</tr>
	<tr>
		<%
			/*while(itr.hasNext())
			 {
			 System.out.println(user.getId());*/
			for (Stock stock : trsList) {
		%>
		<td><%=stock.getId()%></td>
		<td><%=stock.getPrdName()%></td>
		<td><%=stock.getAlertMsg()%></td>
		<td><%=stock.getStock_quantity()%></td>
	</tr>
	<%
		}
		//}
	%>
</table>
</body>
</html>