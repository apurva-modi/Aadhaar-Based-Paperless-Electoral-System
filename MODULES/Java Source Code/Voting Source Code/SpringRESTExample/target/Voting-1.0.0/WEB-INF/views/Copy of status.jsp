<!DOCTYPE HTML>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page session="false" %>
<html><head>
<style>
.floating-box {
    float: left;
    width: 150px;
    height: 75px;
    margin-left:250px; 
}

</style>
<title>Web Based Pump Controller</title>
<meta name="description" content="">
<meta name="keywords" content="">
<meta name="author" content="">
<meta name="generator" content="Aurora Web Editor">
<script>
function createRequest() {
	  var result = null;
	  if (window.XMLHttpRequest) {
	    // FireFox, Safari, etc.
	    result = new XMLHttpRequest();
	    if (typeof xmlhttp.overrideMimeType != 'undefined') {
	      result.overrideMimeType('text/xml'); // Or anything else
	    }
	  }
	  else if (window.ActiveXObject) {
	    // MSIE
	    result = new ActiveXObject("Microsoft.XMLHTTP");
	  } 
	  else {
	    // No known mechanism -- consider aborting the application
	  }
	  return result;
	}

function getTank1(){
	alert("getTank1");
	var req = new XMLHttpRequest(); // defined above
	alert("req---"+req);
	req.open("GET", "http://localhost:8080/tutorial/getTankInfo", true);
	req.send();
	// Create the callback:
	req.onreadystatechange = function() {
	  if (req.readyState != 4) return; // Not there yet
	  if (req.status != 200) {
	    // Handle request failure here...
	    return;
	  }
	  // Request successful, read the response
	  var resp = req.responseText;
	  alert("resp==="+resp);
	  // ... and use it as needed by your app.
	}
	
	req.open("GET", "http://localhost:8080/tutorial/tankInfo/tank1on", true);
	req.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	req.send("");
}

</script>

</head>
<body onload="getTank1()">
<div><img src="cmrit.png"></div>
<div style="
    margin-top: -80px;
"><h1 style="align:center;margin-top: -153px;margin-left: 554px;font-size: 44px;color: teal;">Web Based Pump Controller</h1>
</div>
<div class="floating-box">
Tank1
<img id="Tank1Image" src="${pageContext.request.contextPath}/images/water1.gif" alt="water percentage" style="
    height: 168px;
    margin-left: 55px;
    margin-top: 40px;
"></div>
<div class="floating-box">
Tank2
<img id="Tank2Image" src="${pageContext.request.contextPath}/images/water1.gif" alt="water percentage" style="
    height: 168px;
    margin-left: 55px;
    margin-top: 40px;
"></div>

<div style="
    margin-left: 267px;
    width:400px;
">
Motor On Tank1:
<input type="button" name="ON" value="Motor-1 On" style="border-radius: 39px;color:whitesmoke;background-color;green;background-color: green;width: 80px;height: 38px;">&nbsp;:&nbsp;:&nbsp;
<label style="
    font-size: 21px;
">Motor Off:</label>&nbsp;&nbsp;<input type="button" name="OFF" value="Motor-1 Off" style="margin-radius:10px;color:whitesmoke;background-color;red;border-radius: 39px;color: whitesmoke;background-color: red;width: 80px;height: 38px;">
</form>
</div>

<div style="
    margin-top: 121px;
    margin-left: 207px;
">
<form action="#" method="GET">
<label style="
    font-size: 21px;
">Motor On Tank2:</label>&nbsp;&nbsp;<input type="submit" name="ON" value="Motor-2 On" style="border-radius: 39px;color:whitesmoke;background-color;green;background-color: green;width: 80px;height: 38px;">&nbsp;:&nbsp;:&nbsp;
<label style="
    font-size: 21px;
">Motor Off:</label>&nbsp;&nbsp;<input type="submit" name="OFF" value="Motor-2 Off" style="margin-radius:10px;color:whitesmoke;background-color;red;border-radius: 39px;color: whitesmoke;background-color: red;width: 80px;height: 38px;">
</form>
</div>

<div style="
    width: 472px;
    margin-left: 569px;
    font-weight: bold;
    font-size: 36px;
    color: green;
    margin-top: 48px;
"><marquee>Hi welcome to our site develop by   REYAZ , MANU , AISHWARYA,ANUSHA</marquee>
</div>
<center>
</center>

</body></html>