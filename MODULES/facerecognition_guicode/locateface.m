% clear all
% clc
%Detect objects using Viola-Jones Algorithm

function [handles k] = locateface(hObject, handles)
%To detect Face
FDetect = vision.CascadeObjectDetector;
imgIn = handles.webcam_image;
I=rgb2gray(imgIn);
% %Read the input image
% I = imread('13.jpg');

%Returns Bounding Box values based on number of objects
BB = step(FDetect,I);
% imgCrop = imcrop(imgIn,BB);
% imgCrop = imresize(imgCrop, [200 200]);
% handles.imgCrop = imgCrop;
% imwrite(imgCrop, 'imgCrop.bmp');
% figure,
% imshow(I); hold on

k=size(BB,1);
imgCrop1=zeros(200,200,k);
% imgCrop1(:,:,k)=[];
for i = 1:size(BB,1)
    rectangle('Position',BB(i,:),'LineWidth',5,'LineStyle','-','EdgeColor','r');
    
imgCrop = imcrop(imgIn,BB(i,:));
imgCrop1(:,:,i) = imresize(rgb2gray(imgCrop), [200 200]);
handles.imgCrop = imgCrop1;
end

% hold off;
