function varargout = realtimefacerecognition(varargin)
% REALTIMEFACERECOGNITION MATLAB code for realtimefacerecognition.fig
%      REALTIMEFACERECOGNITION, by itself, creates a new REALTIMEFACERECOGNITION or raises the existing
%      singleton*.
%
%      H = REALTIMEFACERECOGNITION returns the handle to a new REALTIMEFACERECOGNITION or the handle to
%      the existing singleton*.
%
%      REALTIMEFACERECOGNITION('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in REALTIMEFACERECOGNITION.M with the given input arguments.
%
%      REALTIMEFACERECOGNITION(  'Property','Value',...) creates a new REALTIMEFACERECOGNITION or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before realtimefacerecognition_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to realtimefacerecognition_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help realtimefacerecognition

% Last Modified by GUIDE v2.5 19-Feb-2018 12:05:18

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @realtimefacerecognition_OpeningFcn, ...
                   'gui_OutputFcn',  @realtimefacerecognition_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before realtimefacerecognition is made visible.
function realtimefacerecognition_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to realtimefacerecognition (see VARARGIN)

% Choose default command line output for realtimefacerecognition
handles.output = hObject;

axes(handles.axes1);
axis off;
axes(handles.axes2);
axis off;
axes(handles.axes3);
axis off;
axes(handles.axes4);
axis off;
axes(handles.axes5);
axis off;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes realtimefacerecognition wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = realtimefacerecognition_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
vidobj  = videoinput('winvideo', 1, 'YUY2_320x240');

vidRes = get(vidobj , 'VideoResolution');
nBands = get(vidobj , 'NumberOfBands');

% Display the video data in your GUI.
% axes(handles.axes1);
axes(handles.axes4);
hImage = image( zeros(vidRes(2), vidRes(1), nBands) );

preview(vidobj, hImage);

 handles.vidobj = vidobj;
% 
% % set(handles.pushbutton_CaptureFrame, 'Enable', 'on');
% % set(handles.pushbutton_StartVideo, 'Enable', 'off');
% % Update handles structure
 guidata(hObject, handles);

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.webcam_image = getsnapshot(handles.vidobj);

% url='http://192.168.1.31:8080/photo.jpg';
% 
% handles.webcam_image=imread(url);
% stoppreview(handles.vidobj);

axes(handles.axes2);
handles.webcam_image = ycbcr2rgb(handles.webcam_image);
imshow(handles.webcam_image);
guidata(hObject, handles);
% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global imgCrop
handles.imgCrop = [];
[handles] = locateface(hObject, handles);

% handles.imgCrop = crop_image(handles.webcam_image, 1);

imgCrop = handles.imgCrop;
if ~isempty(imgCrop)
    axes(handles.axes3);
    imshow(uint8(imgCrop));
    imgCrop=uint8(imgCrop);
    %save cropImg imgCrop;
imgCrop=uint8(imgCrop);
eyeloc=locateeye(imgCrop);
noseloc=locatenose(imgCrop);
eye1=[eyeloc(1)+10 eyeloc(4)/2];
eye2=[eyeloc(1)+eyeloc(3)-10 eyeloc(4)/2];
nose1=[noseloc(1)+noseloc(3)/2 noseloc(2)+noseloc(4)/2];
eye_diff=eu_dist(eye1,eye2);
nose_eye1_diff=eu_dist(eye1,nose1)
nose_eye2_diff=eu_dist(eye2,nose1)     
%     set(handles.pushbutton_Save, 'Enable', 'on');
%     set(handles.pushbutton_Enrolement, 'Enable', 'on');
end
guidata(hObject, handles);

% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global imgCrop
%TrainDatabasePath = uigetdir('D:\2016\Practie 2016\ERachith RV Face\delivered', 'Select training database path' );
TrainDatabasePath = '.\TrainDatabase';
prompt = {'Enter image name (a number between 1 to 10):'};
dg_title = 'Input of PCA-Based Face Recognition System';
num_lines= 1;
def = {'1'};

TrainImage  = inputdlg(prompt,dg_title,num_lines,def);
TrainImage = strcat(TrainDatabasePath,'\',char(TrainImage),'.jpg');
imwrite(imgCrop,TrainImage)
guidata(hObject, handles);
% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clc
clear all
close all

% --- Executes on button press in pushbutton6.
function pushbutton6_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
TrainDatabasePath ='.\TrainDatabase';

% 
% prompt = {'Enter test image name (a number between 1 to 10):'};
% dg_title = 'Input of PCA-Based Face Recognition System';
% num_lines= 1;
% def = {'1'};
% 
% TestImage  = inputdlg(prompt,dg_title,num_lines,def);
% TestImage = strcat(TestDatabasePath,'\',char(TestImage),'.jpg');
% im = imread(TestImage);
%%

vidobj  = videoinput('winvideo', 1, 'YUY2_320x240');

vidRes = get(vidobj , 'VideoResolution');
nBands = get(vidobj , 'NumberOfBands');
% axes(handles.axes1);
axes(handles.axes4);
hImage = image( zeros(vidRes(2), vidRes(1), nBands) );

% Display the video data in your GUI.

preview(vidobj, hImage);

 handles.vidobj = vidobj;
 pause(3);
handles.webcam_image = getsnapshot(handles.vidobj);

% url='http://192.168.1.31:8080/photo.jpg';
% handles.webcam_image=imread(url);

% stoppreview(handles.vidobj);

axes(handles.axes2);
handles.webcam_image = ycbcr2rgb(handles.webcam_image);
imshow(handles.webcam_image);

handles.imgCrop = [];
[handles k] = locateface(hObject, handles);
% handles.imgCrop = crop_image(handles.webcam_image, 1);

%imgCrop = handles.imgCrop;

% if ~isempty(imgCrop)
%     axes(handles.axes3);
%     imshow(imgCrop);
%   end  
    %save cropImg imgCrop;
    
%     set(handles.pushbutton_Save, 'Enable', 'on');
%     set(handles.pushbutton_Enrolement, 'Enable', 'on');

for i=1:k
%%

imgCrop = handles.imgCrop(:,:,i);
axes(handles.axes3);
    imshow(uint8(imgCrop));
imwrite(uint8(imgCrop),'test.jpg')
TestImage = 'test.jpg';
T = CreateDatabase(TrainDatabasePath);

[m, A, Eigenfaces] = EigenfaceCore(T);
[OutputName index] = Recognition(TestImage, m, A, Eigenfaces);
index;
SelectedImage = strcat(TrainDatabasePath,'\',OutputName);
SelectedImage = imread(SelectedImage);

% imshow(im)
% title('Test Image');

stop(vidobj);
% SelectedImage1 = strcat(TrainDatabasePath,'\',OutputName);
% SelectedImage1 = imread(SelectedImage1);

% str = strcat('Matched image is PCA :  ',OutputName);
% disp(str)

guidata(hObject, handles);
%%
imgCrop=uint8(imgCrop);
eyeloc=locateeye(imgCrop);
noseloc=locatenose(imgCrop);
eye1=[eyeloc(1)+10 eyeloc(4)/2];
eye2=[eyeloc(1)+eyeloc(3)-10 eyeloc(4)/2];
nose1=[noseloc(1)+noseloc(3)/2 noseloc(2)+noseloc(4)/2];
eye_diff=eu_dist(eye1,eye2);
nose_eye1_diff=eu_dist(eye1,nose1)
nose_eye2_diff=eu_dist(eye2,nose1)      
s=serial('COM4');

if index<6 && nose_eye1_diff<123&& nose_eye1_diff>118 && nose_eye2_diff<124 && nose_eye2_diff>119
    disp('Person 1 matched')
    axes(handles.axes1);
    imshow(SelectedImage);
    title('Equivalent Image using PCA');
    d='Person 1 matched';
    set(handles.text2,'string',d)
    fopen(s);
    fwrite(s,'A');
    fclose(s);  
elseif index>5 && index <11 && nose_eye1_diff<116&& nose_eye1_diff>109 && nose_eye2_diff<115 && nose_eye2_diff>108
    disp('Person 2 matched')
    axes(handles.axes1);
    imshow(SelectedImage);
    title('Equivalent Image using PCA');
    d='Person 2 matched';
    set(handles.text2,'string',d)
    fopen(s);
    fwrite(s,'B');
    fclose(s);
elseif index>10 && index <16 && nose_eye1_diff<119&& nose_eye1_diff>116 && nose_eye2_diff<125 && nose_eye2_diff>115
    disp('Person 3 matched')
    axes(handles.axes1);
    imshow(SelectedImage);
    title('Equivalent Image using PCA');
    d='Person 3 matched';
    set(handles.text2,'string',d)
    fopen(s);
    fwrite(s,'C');
    fclose(s);
elseif index>15 && index <21 && nose_eye1_diff<127&& nose_eye1_diff>121 && nose_eye2_diff<128 && nose_eye2_diff>120
    disp('Person 4 matched')
    axes(handles.axes1);
    imshow(SelectedImage);
    title('Equivalent Image using PCA');
    d='Person 4 matched';
    set(handles.text2,'string',d)
    fopen(s);
    fwrite(s,'D');
    fclose(s);
    elseif index>21 && index <26 && nose_eye1_diff<122&& nose_eye1_diff>118 && nose_eye2_diff<129 && nose_eye2_diff>123
    disp('Person 5 matched')
    axes(handles.axes1);
    imshow(SelectedImage);
    title('Equivalent Image using PCA');
    d='Person 5 matched';
    set(handles.text2,'string',d)
    fopen(s);
    fwrite(s,'e');
    fclose(s);
else
    disp('Not matched')
    d='NOT MATCHED';
    set(handles.text2,'string',d);
end
end
