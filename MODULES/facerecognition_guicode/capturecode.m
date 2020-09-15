
i=imaqhwinfo('winvideo');

v=videoinput('winvideo',1,'YUY2_320X240');
set(v,'returnedcolorspace','rgb')
preview(v)
pause(5)
x=getsnapshot(v);
figure,imshow(x)
imwrite(x,'person1.jpg');