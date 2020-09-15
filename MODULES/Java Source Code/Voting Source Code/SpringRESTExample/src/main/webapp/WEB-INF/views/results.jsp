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
<div class="table-responsive">
		<table align="center" class="table table-bordered" style="width: 300px">		
			<tr>
				<td>Total Vote Count :</td>
				<td><input type="text" value="4" editable="true"/></td>
			</tr>	
			<tr>
				<td>Total BJP Party Count </td>
				<td><input type="text" value="${BJP}" editable="true"/></td>
			</tr>
			<tr>
				<td>Total CONGRESS Party Count  </td>
				<td><input type="text" value="${CONGRESS}" editable="true"/></td>
			</tr>
			<tr>
				<td>Total JDS Party Count  </td>
				<td><input type="text" value="${JDS}" editable="true"/></td>
			</tr>
			<tr>
				<td>Total AAP Party Count  </td>
				<td><input type="text" value="${AAP}" editable="true"/></td>
			</tr>
			<tr>
				<td>Total NOTA Count  </td>
				<td><input type="text" value="${NOTA}" editable="true"/></td>
			</tr>
			<tr>
				<td>Winner Of the Polling </td>
				<td><input type="text" value="${winner}" editable="true"/></td>
			</tr>
			
		</table>
 	</div>
 	<form id="dischargeForm" method="post" action="resetVotings" >
 	<div class="table-responsive">
		<table align="center" class="table table-bordered" width="300px;">
			<tr>
				<td></td>
				<td><input class="btn btn-primary btn-sm" type="submit" value="Reset Voting System" /></td>
			</tr>
		</table>
		</div>
 	</form>
</body>
</html>