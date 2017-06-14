%% setup.m
% UAV Software-in-the-Loop Simulation setup
%
% This script will setup the SIL simulation. 
%
% University of Minnesota
% Aerospace Engineering and Mechanics
% Copyright 2017 Regents of the University of Minnesota.
% All rights reserved.
%


%% Set Aircraft Type
% 1 = UltraStick25e, standard outfit
aircraftType = 1 ;


%% Configure Simulation Fidelity
% 1 = Simplified Open-Source
% 2 = High-Fidelity, requires Aerospace Blockset
simulation_type = 1 ;


%% Set controller mode
% Use this variable to quickly change what controller is used in the
% simulation.
%
% 1 = baseline controller (C implementation)
% 2 = baseline controller (Simulink)
cntrlMode = 2 ;


%% Configure Simulation Specifically For This Airfame
switch aircraftType
    case 1 % UltraStick25e, standard outfit
        
        % Call base setup file
        SetupNL
end

% Simulation Fidelity Variants Definition
sim_fidelity_simple_var = Simulink.Variant('simulation_type == 1') ;
sim_fidelity_full_var   = Simulink.Variant('simulation_type == 2') ;



%% Setup Simulation Variant
% Configure Effectors for specific simulation
AC_TYPE_SIMPLE = Simulink.Variant('AC_TYPE == 1');
AC_TYPE_DETAILED = Simulink.Variant('AC_TYPE == 2');
switch AC.Sim.Effectors
    case 1
        AC_TYPE = 1;
    case 2
        AC_TYPE = 2;
end

% Configure Sensors for specific simulation
AC_IMU_TYPE1 = Simulink.Variant('AC_IMU == 1');
AC_IMU_TYPE2 = Simulink.Variant('AC_IMU == 2');
AC_GPS_TYPE1 = Simulink.Variant('AC_GPS == 1');
AC_GPS_TYPE2 = Simulink.Variant('AC_GPS == 2');
AC_GPS_TYPE3 = Simulink.Variant('AC_GPS == 3');
AC_PITOT_TYPE1 = Simulink.Variant('AC_PITOT == 1');
AC_PITOT_TYPE2 = Simulink.Variant('AC_PITOT == 2');
AC_AIRDATA_TYPE1 = Simulink.Variant('AC_AIRDATA == 1');
AC_AIRDATA_TYPE2 = Simulink.Variant('AC_AIRDATA == 2');
AC_AIRDATA_TYPE3 = Simulink.Variant('AC_AIRDATA == 3');
AC_AIRDATA_TYPE4 = Simulink.Variant('AC_AIRDATA == 4');

% IMU
switch AC.Sim.Sensor.IMU
    case 1
        AC_IMU = 1;
    case 2
        AC_IMU = 2;
end

% GPS
switch AC.Sim.Sensor.GPS
    case 1
        AC_GPS = 1;
    case 2
        AC_GPS = 2;
    case 3
        AC_GPS = 3;
end

% Pitot Static
switch AC.Sim.Sensor.Pitot
    case 1
        AC_PITOT = 1;
    case 2
        AC_PITOT = 2;
end

% Airdata Sensors
switch AC.Sim.Sensor.Airdata
    case 1
        AC_AIRDATA = 1;
    case 2
        AC_AIRDATA = 2;
    case 3
        AC_AIRDATA = 3;
    case 4
        AC_AIRDATA = 4;
end



%% Simulation sample time
SampleTime = 0.02; % sec
MPCSampleTime = 0.02; % sec



%% Load controller parameters or compile flight code
switch cntrlMode
    case 1 % Baseline controller in C
        % Compile Flight Software:
        cntrlPath = '../FlightCode/control/baseline_control.c';

        
        cntrlType = 'C Code' ;
        
    case 2 % Baseline controller in Simulink.
        CntrlBaselineSetup;   % Declare baseline controller gains
        pitch_gains = [kp_PT, ki_PT, kp_PD];
        roll_gains = [kp_RT, ki_RT, kp_RD];
        yaw_damper_num = [YDz_num]; % discrete transfer function yaw damper coefficients
        yaw_damper_den = [YDz_den];

        cntrlType = 'Simulink' ;
        cntrlBaselineVariant = Simulink.Variant('cntrlMode == 2');
        
        % Undefine any c code path
        clear cntrlPath ;
end




%% Advanced Users: Include guidance, system ID, or fault injection codes.
% Set the path to the .c code in the following variables.
%
%%%%% GUIDANCE LAW %%%%%
% Point to the desired guidance code here. Use '-DSIMULINK_GUIDANCE' to
% input the reference commands from the simulink diagram.
% GUIDANCE = '../Software/FlightCode/guidance/straight_level.c';
% GUIDANCE = '../Software/FlightCode/guidance/doublet_phi_theta.c';
 GUIDANCE = '-DSIMULINK_GUIDANCE';

%%%%%% SYSTEM ID SELECTION %%%%%
% Point to the desired system ID code here
% SYSTEM_ID = '../Software/FlightCode/system_id/chirp_sysid.c';
 SYSTEM_ID = '../FlightCode/system_id/systemid_none.c';

%%%%%% SURFACE FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
% SURFACE_FAULT = '../Software/FlightCode/faults/fault_onesurf.c';
% SURFACE_FAULT = '../Software/FlightCode/faults/fault_onesurf_SingleStep.c';
 SURFACE_FAULT = '../FlightCode/faults/surffault_none.c';


%%%%%% SENS0R FAULT MODE SELECTION %%%%%
% Point to the desired fault code here
 SENSOR_FAULT = '../FlightCode/faults/sensfault_none.c';

% Compile control software
if exist('cntrlPath','var')
    eval(['mex -I../FlightCode/ ' 'Controllers/ControlSIL.c  ' cntrlPath...
                       ' ' GUIDANCE ' ' SYSTEM_ID ' ' SURFACE_FAULT ' ' SENSOR_FAULT ...
                       ' ../FlightCode/faults/fault_functions.c ' ...
                       ' ../FlightCode/system_id/systemid_functions.c ']);
end



%% Open sim diagram
open_system('SimSIL')

% Set up controller wrapper
blockpath = 'SimSIL/Flight Computer/Interrupt Service Routine/Controller Type' ;
switch cntrlType
    case 'C Code'
        set_param(blockpath, 'BlockChoice', 'C Code');
    case 'Simulink'
        set_param(blockpath, 'BlockChoice', 'Simulink');
end

