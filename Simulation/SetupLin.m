%% setup.m
% UAV Linear Simulation setup
%
% This script will setup the linear simulation (UAV_Lin.mdl) and call
% trim and linearization routines. Select the desired aircraft in the
% nonlinear simulation (../NL_Sim/setup.m).
%
%
% Calls: ../NL_Sim/setup.m
%        trim_UAV.m
%        linearize_UAV.m
%       
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%

%% Obtain UAV trim condition matrices and linear model. 
% To update trim targets, edit this m-file.
run setup_NL.m 

%% Simulation sample time
SampleTime = 0.02; %sec


%% Integer Time delay in flight software loop
IntegerTimeDelay = 2; % .04sec


%% Set controller variants
% Each variant corresponds to a different Simulink model that will be
% referenced in the "UAV_Lin/Control Software/Control Software" block.
baseline_control_var = Simulink.Variant('controller_mode == 1');
heading_control_var = Simulink.Variant('controller_mode == 2');
student_control_var = Simulink.Variant('controller_mode == 3');
lqr_control_var = Simulink.Variant('controller_mode == 4');


%% Set controller mode
% Use this variable to quickly change what controller is used in the
% simulation.
%
% 1 = baseline controller (Simulink)
% 2 = Heading controller (Simulink)
% 3 = Student controller (Simulink)     
% 4 = LQR controller (Simulink)
controller_mode = 1;

% Load controller parameters or compile flight code
switch controller_mode
    case 1 %Basleine controller in Simulink
        baseline_gains;   % Declare baseline controller gains
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];
        
    case 2 %Heading controller in Simulink
        baseline_gains;  % heading controller lays on top of the baseline controller        
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];
        
        heading_gains;  % Specify waypoint gains
        phi_sat = 45;   % phi cotnroller output saturation
        theta_sat = 20; % altitude controller output saturation
        
    case 3 %Student controller in Simulink
        % Specify gains here
        
    case 4 % LQR controller in Simulink
        % Parameters defined here are identical to those in lqr_control.c
        K_pitch = [-0.240144526553189,  0.079132432193614, 0.287138908852059];
        K_roll = [-0.6679,   0.0243,   0.0251,   0.3631;...
            -0.1355,   0.0004,   0.0284,   0.0710];
end


%% Open UAV_Lin model
UAV_Lin
