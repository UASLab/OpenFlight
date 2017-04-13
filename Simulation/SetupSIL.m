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


%% Set aircraft type
% 1 = UltraStick25e, standard outfit
aircraft_type = 1 ;

% Configure simulation specifically for this airfame
switch aircraft_type
    case 1 % UltraStick25e, standard outfit
        % Configure variant for model refenence        
        aircraft_config_var = Simulink.Variant('aircraft_type == 1');

        % Setup aircraft specific buses
        AircraftSpecificBuses_UltraStick25e ;
end


%% Load airframe configuration and trim condition
% To change these, use the functions "UAV_config.m" and "trim_UAV.m"
load UAV_modelconfig
load UAV_trimcondition


%% Simulation sample time
SampleTime = 0.02; % sec
MPCSampleTime = 0.02; % sec

%% Setup simulation buses
GeneralBuses ;


%% Set controller mode
% Use this variable to quickly change what controller is used in the
% simulation.
%
% 1 = baseline controller (C implementation)
% 2 = baseline controller (Simulink)
controller_mode = 2 ;


% Load controller parameters or compile flight code
switch controller_mode
    case 1 % Baseline controller in C
        % Compile Flight Software:
        control_code_path = '../../FlightCode/control/baseline_control.c';
        
        
        controller_type = 'C Code' ;
    case 2 % Baseline controller in Simulink.
        baseline_gains;   % Declare baseline controller gains
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];

        controller_type = 'Simulink' ;
        baseline_control_var = Simulink.Variant('controller_mode == 2');
end


%% Advanced Users: Include guidance, system ID, or fault injection codes.
% Set the path to the .c code in the following variables.
%
%%%%% GUIDANCE LAW %%%%%
% Point to the desired guidance code here. Use '-DSIMULINK_GUIDANCE' to
% input the reference commands from the simulink diagram.
% GUIDANCE = '../../Software/FlightCode/guidance/straight_level.c';
% GUIDANCE = '../../Software/FlightCode/guidance/doublet_phi_theta.c';
 GUIDANCE = '-DSIMULINK_GUIDANCE';

%%%%%% SYSTEM ID SELECTION %%%%%
% Point to the desired system ID code here
% SYSTEM_ID = '../../Software/FlightCode/system_id/chirp_sysid.c';
 SYSTEM_ID = '../../FlightCode/system_id/systemid_none.c';

%%%%%% SURFACE FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
% SURFACE_FAULT = '../../Software/FlightCode/faults/fault_onesurf.c';
% SURFACE_FAULT = '../../Software/FlightCode/faults/fault_onesurf_SingleStep.c';
 SURFACE_FAULT = '../../FlightCode/faults/surffault_none.c';


%%%%%% SENS0R FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
 SENSOR_FAULT = '../../FlightCode/faults/sensfault_none.c';

% Compile control software
if exist('control_code_path','var')
    eval(['mex -I../../FlightCode/ control_SIL.c  ' control_code_path...
                       ' ' GUIDANCE ' ' SYSTEM_ID ' ' SURFACE_FAULT ' ' SENSOR_FAULT ...
                       ' ../../FlightCode/faults/fault_functions.c ' ...
                       ' ../../FlightCode/system_id/systemid_functions.c ']);
end



%% Open sim diagram
UAV_SIL

% Set up controller wrapper
blockpath = 'UAV_SIL/Flight Computer/Interrupt Service Routine/Controller Type' ;
switch controller_type
    case 'C Code'
        set_param(blockpath,'BlockChoice','C Code');
    case 'Simulink'
        set_param(blockpath,'BlockChoice','Simulink');
end

