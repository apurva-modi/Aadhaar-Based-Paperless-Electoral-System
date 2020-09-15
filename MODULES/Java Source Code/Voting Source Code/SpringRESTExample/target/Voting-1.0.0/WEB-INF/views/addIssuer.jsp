<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="f" %>
<%@ page session="false" %>
<html>
	<head>
		<title>${message}</title>
	</head>
	<body>
	    <h1>${message}</h1>
		<f:form method="POST" action="addIssuer">
		<table>
			<tbody>
				<tr>
				  <td>Ticker:</td>
				  <td><f:input path="ticker" size="10" maxlength="10"></f:input></td>
				</tr>
				<tr>
				  <td>Issuer Name:</td>
				  <td><f:input path="issuerName" size="30"></f:input></td>
				</tr>
				<tr>
				  <td>Issuer Type:</td>
				  <td><f:input path="issuerType" size="6"></f:input></td>
				</tr>
				<tr>
				  <td>Country:</td>
				  <td><f:input path="country" size="20"></f:input></td>
				</tr>
				<tr>
        			<td colspan="2"><input type="submit" value="Add Issuer"></td>
    			</tr>
			</tbody>
		</table>
		</f:form>	
	</body>
</html>