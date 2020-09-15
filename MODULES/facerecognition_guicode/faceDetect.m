function [handles] = faceDetect(hObject, handles)

sNameHaarDetector = 'haarcascade_frontalface.xml';

imgIn = handles.webcam_image;
imgIn=rgb2gray(imgIn);

rFaces = mexHaarDetect(imgIn, sNameHaarDetector);
imshow(imgIn); axis off, hold on;
rectangle('Position', rFaces(:,1), 'EdgeColor', 'r');
imgCrop = imcrop(imgIn, rFaces(:, 1)');
imgCrop = imresize(imgCrop, [200 200]);

handles.imgCrop = imgCrop;
imwrite(imgCrop, 'imgCrop.bmp');

save cropImg imgCrop;

