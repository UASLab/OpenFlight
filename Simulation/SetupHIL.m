%% setup.m
% UAV Hardware-in-the-Loop Simulation setup
% 
% University of Minnesota
% Aerospace Engineering and Mechanics
% Copyright 2011 Regents of the University of Minnesota.
% All rights reserved.
%
% IMPORTANT: Run first the Simulink model, then the flight computer. This
% is needed to avoid delays due to data in the serial buffer. 
%


% warning off Simulink:Engine:SaveWithParameterizedLinks_Warning
% warning off Simulink:Commands:LoadMdlParameterizedLink 
% warning off Simulink:ID:DuplicateSID

%% Load airframe configuration and trim condition
% To change these, use the functions "UAV_config.m" and "trim_UAV.m"
load UAV_modelconfig
load UAV_trimcondition


%% Sensor reconfiguration configuration
AC.Sensors.NoiseOn = 1 ; 


%% Env. reconfiguration

Env.Winds.GustOn = 0; 

%% Simulation sample time
SampleTime = 0.01; % sec


%% Open model, build target, and connect.
UAV_HIL;
rtwbuild UAV_HIL;
