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
<h3>Demonitization Application</h3>

	<br>
	<br>
<%
	//UserBean user = new UserBean();
	MySQLAccess mySQLAccess = new MySQLAccess();
	List<Transaction> trsList = mySQLAccess.getAllTransactions();
%>
<table align="center" class="table table-bordered" style="width: 1000px">
	<tr>
		<th>Id</th>
		<th>Account No</th>
		<th>Transaction Date</th>
		<th>Credit</th>
		<th>Debit</th>
		<th>Transaction Type</th>
		<th>Balance</th>
	</tr>
	<tr>
		<%
			/*while(itr.hasNext())
			 {
			 System.out.println(user.getId());*/
			for (Transaction transaction : trsList) {
		%>
		<td><%=transaction.getId()%></td>
		<td><%=transaction.getuAccountNo()%></td>
		<td><%=transaction.gettDate()%></td>
		<td><%=transaction.gettCredit()%></td>
		<td><%=transaction.gettDebit()%></td>
		<td><%=transaction.gettTransaction_Type()%></td>
		<td><%=transaction.getuBalance()%></td>		
	</tr>
	<%
		}
		//}
	%>
</table>
</body>
</html>