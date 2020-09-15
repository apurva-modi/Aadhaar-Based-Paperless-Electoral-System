function recipient = matlabmail(recipient, message, subject, sender, psswd,attachments)
% MATLABMAIL Send an email from a predefined gmail account.
%
% MATLABMAIL( recipient, message, subject )
%
%   sends the character string stored in 'message' with subjectline 'subject'
%   to the address in 'recipient'.
%   This requires that the sending address is a GMAIL email account.
%
% MATLABMAIL( recipient, message, subject, sender, passwd ) 
%
%   avoids using the stored credentials.
%

%
% Example:

%matlabmail( 'nitheshksuvarna@gmail.com', 'Please find the attachment', 'Matlab Test Mail', 'info@anventec.com', 'password','C:\Users\ANUGRAHA\Desktop\anventec official.png') 

%
% See also SENDMAIL


mail = 'sender@gmail.com';
password = 'password';

setpref('Internet','E_mail',mail);
setpref('Internet','SMTP_Server','smtp.gmail.com');
setpref('Internet','SMTP_Username',mail);
setpref('Internet','SMTP_Password',password);
props=java.lang.System.getProperties;
pp=props.setProperty('mail.smtp.auth','true'); %#ok
pp=props.setProperty('mail.smtp.socketFactory.class','javax.net.ssl.SSLSocketFactory'); %#ok
pp=props.setProperty('mail.smtp.socketFactory.port','465'); %#ok

sendmail(recipient,subject,message,attachments)