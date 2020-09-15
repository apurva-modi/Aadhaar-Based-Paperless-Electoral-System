clc
clear all

close all

i=imread('H:\D\133.jpg');

figure,imshow(i)

d=imnoise(i,'salt & pepper');

figure,imshow(d)

s=fspecial('disk',30);

q=imfilter(d,s,'replicate');

figure,imshow(q)