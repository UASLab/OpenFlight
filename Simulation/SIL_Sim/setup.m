%% setup.m
% UAV Software-in-the-Loop Simulation setup
%
% This script will setup the SIL simulation. Stored aircraft configuration
% and trim conditions are used.
%
% University of Minnesota
% Aerospace Engineering and Mechanics
% Copyright 2011 Regents of the University of Minnesota.
% All rights reserved.
%

%% Clean up
clear all
close all
bdclose all
clc

%% Add Libraries and controllers folder to MATLAB path
addpath ../Libraries
addpath ../Controllers
warning off Simulink:Engine:SaveWithParameterizedLinks_Warning
warning off Simulink:Commands:LoadMdlParameterizedLink 
warning off Simulink:ID:DuplicateSID

%% Load airframe configuration and trim condition
% To change these, use the functions "UAV_config.m" and "trim_UAV.m"
load UAV_modelconfig
load UAV_trimcondition

%% Simulation sample time
SampleTime = 0.02; % sec
%% Set controller variants
% Each variant corresponds to a different Simulink model that will be
% referenced in the "UAV_SIL/Control Software/Control Software" block.
flightcode_var = Simulink.Variant('controller_mode == 1 || controller_mode == 3 || controller_mode == 5 || controller_mode == 7 || controller_mode == 9');
baseline_control_var = Simulink.Variant('controller_mode == 2');
heading_control_var = Simulink.Variant('controller_mode == 4');
lqr_control_var = Simulink.Variant('controller_mode == 6');
student_control_var = Simulink.Variant('controller_mode == 8');

%% Set controller mode
% Use this variable to quickly change what controller is used in the
% simulation.
%
% 1 = baseline controller (C implementation)
% 2 = baseline controller (Simulink)
% 3 = Heading controller (C implementation)
% 4 = Heading controller (Simulink)
% 5 = LQR controller (C implementation)
% 6 = LQR controller (Simulink)
% 7 = Student controller (C implementation) 
% 8 = Student controller (Simulink)    
% 9 = Waypoint tracker (C implementation)
controller_mode = 2;

% Load controller parameters or compile flight code
switch controller_mode
    case 1 % Baseline controller in C
        % Compile Flight Software:
        control_code_path = '../../FlightCode/control/baseline_control.c';
        
    case 2 % Baseline controller in Simulink.
        baseline_gains;   % Declare baseline controller gains
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];

        
    case 3 % Heading controller in C
        % Compile Flight Software:
        control_code_path ='../../FlightCode/control/heading_tracker.c';
        
    case 4 % Heading controller in Simulink
        baseline_gains;  % heading controller lays on top of the baseline controller        
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];
        
        heading_gains;  % Specify heading gains
        phi_sat = 45;   % phi cotnroller output saturation
        theta_sat = 20; % altitude controller output saturation

        
    case 5 % LQR controller in C
        % Compile Flight Software:
        control_code_path ='../../FlightCode/control/lqr_control.c';
        
    case 6 % LQR controller in Simulink
        % Parameters defined here are identical to those in lqr_control.c
        K_pitch = [-0.240144526553189,  0.079132432193614, 0.287138908852059];
        K_roll = [-0.6679,   0.0243,   0.0251,   0.3631;...
            -0.1355,   0.0004,   0.0284,   0.0710];
        
    case 7 % Student controller in C 
        % Compile Flight Software:
        control_code_path ='../../FlightCode/control/student_control.c'; % Specify your control code file name here       
           
    case 8 % Student controller in Simulink        
        % Get control gains
        
    case 9 % Waypoint tracker in C
        % Compile Flight Software:
        control_code_path ='../../FlightCode/control/waypoint_tracker.c';
end

% Advanced Users: Include guidance, system ID, or fault injection codes.
% Set the path to the .c code in the following variables.
%
%%%%% GUIDANCE LAW %%%%%
% Point to the desired guidance code here. Use '-DSIMULINK_GUIDANCE' to
% input the reference commands from the simulink diagram.
% GUIDANCE = '../../FlightCode/guidance/straight_level.c';
% GUIDANCE = '../../FlightCode/guidance/doublet_phi_theta.c';
 GUIDANCE = '-DSIMULINK_GUIDANCE';

%%%%%% SYSTEM ID SELECTION %%%%%
% Point to the desired system ID code here
% SYSTEM_ID = '../../FlightCode/system_id/chirp_sysid.c';
 SYSTEM_ID = '../../FlightCode/system_id/systemid_none.c';

%%%%%% SURFACE FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
% SURFACE_FAULT = '../../FlightCode/faults/fault_onesurf.c';
% SURFACE_FAULT = '../../FlightCode/faults/fault_onesurf_SingleStep.c';
 SURFACE_FAULT = '../../FlightCode/faults/surffault_none.c';


%%%%%% SENS0R FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
 SENSOR_FAULT = '../../FlightCode/faults/sensfault_none.c';

% Compile control software
BASE_HZ = num2str(round(1/SampleTime))
if exist('control_code_path','var')
    eval(['mex -I../../FlightCode/ control_SIL.c  ' control_code_path...
                       ' ' GUIDANCE ' ' SYSTEM_ID ' ' SURFACE_FAULT ' ' SENSOR_FAULT ...
                       ' ../../FlightCode/faults/fault_functions.c ' ...
                       ' ../../FlightCode/system_id/systemid_functions.c ' ...
                       '-DSIL_SIM -DBASE_HZ=' BASE_HZ]);
end



%% Integer Time delay in flight software loop
IntegerTimeDelay = 2; % .04sec

%% Open sim diagram
UAV_SIL
