<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="form"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</head>
<body style="background-color: #9dc8e2" align="center">
<h3>Finger Print Authentication and Online Voting Application Cast Vote Details</h3>

	<br>
	<br>
<form:form method="post" commandName="vote" action="/Voting/Vote1">
 <div class="table-responsive">
		<table align="center" class="table table-bordered" style="width: 300px">		
			<tr>
				<td>Voter Id :</td>
				<td><form:input type="text" path="voterId" /></td>
			</tr>	
			<tr>
				<td>Party Name </td>
				<td>
					<form:select path="partName">
						<form:option value="BJP" label="BJP"/>
						<form:option value="CONGRESS" label="CONGRESS"/>
						<form:option value="JDS" label="JDS"/>
						<form:option value="AAP" label="AAP"/>
						<form:option value="NOTA" label="NOTA" />
					</form:select>
				</td>
			</tr>
			<tr>
				<td colspan="2"><input type="submit" value="Vote" /></td>
			</tr>
		</table>
 	</div>
	</form:form>	
</body>
</html>