              

clear all
clc
close all

% You can customize and fix initial directory paths
TrainDatabasePath = uigetdir('F:\facerecognition_guicode\TrainDatabase', 'Select training database path' );
TestDatabasePath = uigetdir('F:\facerecognition_guicode\TestDatabase', 'Select test database path');

prompt = {'Enter test image name (a number between 1 to 10):'};
dg_title = 'Input of PCA-Based Face Recognition System';
num_lines= 1;
def = {'1'};

TestImage  = inputdlg(prompt,dg_title,num_lines,def);
TestImage = strcat(TestDatabasePath,'\',char(TestImage),'.jpg');
im = imread(TestImage);
% PSF = fspecial('gaussian',7,10);
% Blurred = imfilter(im,PSF,'symmetric','conv');
%figure;imshow(Blurred);title('Blurred Image');
%im=Blurred;
T = CreateDatabase(TrainDatabasePath);
[m, A, Eigenfaces] = EigenfaceCore(T);
OutputName = Recognition(TestImage, m, A, Eigenfaces);

SelectedImage = strcat(TrainDatabasePath,'\',OutputName);
SelectedImage = imread(SelectedImage);

imshow(im)
title('Test Image');
figure,imshow(SelectedImage);
title('Equivalent Image');

str = strcat('Matched image is :  ',OutputName);
disp(str)
