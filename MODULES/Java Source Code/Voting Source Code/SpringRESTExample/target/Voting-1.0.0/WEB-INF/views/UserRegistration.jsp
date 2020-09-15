<!DOCTYPE HTML>
<html><head>
<title>Banking Web Application</title>

</head>
<body>

<%@page import="com.handinhand.controller.MySQLAccess"%>  
<jsp:useBean id="obj" class="com.handinhand.model.User"/>  
  
<jsp:setProperty property="*" name="obj"/>  
  
<%  
MySQLAccess  mySQLAccess = new MySQLAccess();
int status=mySQLAccess.insertUser(obj);  
if(status>0)  
out.print("You are successfully registered");  
  
%>  

</body></html>