function [AC] = ParamDef_UltraStick25e()
% function [AC] = ParamDef_UltraStick25e()
% Ultra Stick 25e configuration file. Sets aircraft parameters.
% Called from: SimConfig.m
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. All rights reserved.
%


% The Simulation uses aircraft coordinates in the Body (B) frame only. However, it is often
% useful to specify vehicle setup in a seperate frame, whose origin does not move with the CG
% location.
% S (Structural) - Origin at the center of the firewall [+Aft, +Right Wing, +Up]
% B (Body)       - Origin at the CG                     [+Fwd, +Right Wing, +Down]
% SB (Structural, Body Oriented) - Origin at the center of the firewall [+Fwd, +Right Wing, +Down]
% Aero (Aeodynamic) - Origin at the Aerodynamic Center, aligned with flow [+Downstream, +Right Wing, +Up]
% Prop (Propulsion) - Origin at the Prop Center, aligned with thrustline [+Fwd (Thrust), +Right Wing, +Down]


% Constants
in2m = 0.0254;

AC.Geometry.T_S2SB = [-1, 0, 0; 0, 1, 0; 0, 0, -1];


%%
AC.aircraft = 'UltraStick25e';


%% Load Mass Properties
% AC.MassP.type = 'avl';
AC.MassP.type = 'flight'; AC.MassP.model = 'Thor';

AC.MassP = ParamDef_UltraStick25e_MassP(AC.MassP, AC.Geometry.T_S2SB);


%% Load Aerodynamics
% AC.Aero.type = 'avl_v1';
AC.Aero.type = 'flight';

AC.Aero = ParamDef_UltraStick25e_Aero(AC.Aero, AC.Geometry.T_S2SB);


%% PROPULSION
AC.Prop.propType = 'apc_12x6e';
AC.Prop = ParamDef_UltraStick25e_Prop(AC.Prop, AC.Geometry.T_S2SB);


%% Configure Actuators and Initial Conditions
d2r = pi/180; % Degrees to Radians conversion

% Select Effector Variant Type
AC.Sim.Effectors = 1;

%Elevator
AC.Actuator.elevator.BW = 8;    % [Hz]
AC.Actuator.elevator.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.elevator.PosLim = 25*d2r;  % [rad]
AC.Actuator.elevator.NegLim = -25*d2r; %[rad]

%Ailerons
AC.Actuator.l_aileron.BW = 8;    % [Hz]
AC.Actuator.l_aileron.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.l_aileron.PosLim = 25*d2r;  % [rad]
AC.Actuator.l_aileron.NegLim = -25*d2r; %[rad]

AC.Actuator.r_aileron.BW = 8;    % [Hz]
AC.Actuator.r_aileron.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.r_aileron.PosLim = 25*d2r;  % [rad]
AC.Actuator.r_aileron.NegLim = -25*d2r; %[rad]

%Rudder
AC.Actuator.rudder.BW = 8;    % [Hz]
AC.Actuator.rudder.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.rudder.PosLim = 25*d2r;  % [rad]
AC.Actuator.rudder.NegLim = -25*d2r; %[rad]

%Flaps
AC.Actuator.l_flap.BW = 8;    % [Hz]
AC.Actuator.l_flap.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.l_flap.PosLim = 25*d2r;  % [rad]
AC.Actuator.l_flap.NegLim = -25*d2r; %[rad]

AC.Actuator.r_flap.BW = 8;    % [Hz]
AC.Actuator.r_flap.RateLim = 150*d2r;   % [rad/s]
AC.Actuator.r_flap.PosLim = 25*d2r;  % [rad]
AC.Actuator.r_flap.NegLim = -25*d2r; %[rad]

%% Configure Sensor Error Models

% Model Variants
AC.Sensors.VarImuSel = 1;
AC.Sensors.VarGPSSel = 1;
AC.Sensors.VarAirDataSel = 1;


% Configure Sensors for specific simulation
assignin('base', 'VarImu_Pass', Simulink.Variant('VarImuSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarImu_Err', Simulink.Variant('VarImuSel == 1')); % Variant 1 - Error Model Only
assignin('base', 'VarImu_LocErr', Simulink.Variant('VarImuSel == 2')); % Variant 2 - Location + Error Model
assignin('base', 'VarImu_LocTransErr', Simulink.Variant('VarImuSel == 3')); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarImuSel',AC.Sensors.VarImuSel); % IMU

assignin('base', 'VarGps_Pass', Simulink.Variant('VarGpsSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarGps_Err', Simulink.Variant('VarGpsSel == 1')); % Variant 1 - Error Model Only
assignin('base', 'VarGps_LocErr', Simulink.Variant('VarGpsSel == 2')); % Variant 2 - Location + Error Model
assignin('base', 'VarGps_LocTransErr', Simulink.Variant('VarGpsSel == 3')); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarGpsSel', AC.Sensors.VarGPSSel); % GPS

assignin('base', 'VarAirData_Pass', Simulink.Variant('VarAirDataSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarAirData_Err', Simulink.Variant('VarAirDataSel == 1')); % Variant 1 - Error Model Only
assignin('base', 'VarAirData_LocErr', Simulink.Variant('VarAirDataSel == 2')); % Variant 2 - Location + Error Model
assignin('base', 'VarAirData_LocTransErr', Simulink.Variant('VarAirDataSel == 3')); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarAirDataSel', AC.Sensors.VarAirDataSel); % AirData


% IMU Sensor Model
AC.Sensors.IMU.rImu_S_m = [9.5; 0.0; 0.0] * in2m; % IMU sensor location
AC.Sensors.IMU.rImu_SB_m = AC.Geometry.T_S2SB * AC.Sensors.IMU.rImu_S_m;
AC.Sensors.IMU.sImu_B_rad = [0.0; 0.0; 0.0] * d2r; % IMU sensor orientation
AC.Sensors.IMU.T_B2IMU = eye(3); % FIXME - Used defined orientation

AC.Sensors.type.IMU = 'ADIS16405';
AC.Sensors.IMU = ParamDef_IMU(AC.Sensors.type.IMU, AC.Sensors.IMU); % IMU Error Model
AC.Sensors.IMU.errEnable = 1; % Enable the Error Model
AC.Sensors.IMU.timeSample_s = 1/50; % time Sample, used for Noise Generation only

% AirData Sensor Model
AC.Sensors.AirData.rAirData_S_m = [1.0; 14.0; 0.0] * in2m; % Pitot-Static location
AC.Sensors.AirData.rAirData_SB_m = AC.Geometry.T_S2SB * AC.Sensors.AirData.rAirData_S_m;
AC.Sensors.AirData.sAirData_SB_rad = [0.0; 0.0; 0.0] * d2r; % Pitot-Static orientation
AC.Sensors.AirData.T_B2AirData = eye(3); % FIXME - Used defined orientation

AC.Sensors.type.AirData.sys = 'pitot';
AC.Sensors.type.AirData.Ps = 'AMS5915-1200-B';
AC.Sensors.type.AirData.Pd = 'AMS5915-0020-D-B';
AC.Sensors.AirData = ParamDef_AirData(AC.Sensors.type.AirData, AC.Sensors.AirData);
AC.Sensors.AirData.errEnable = 1;
AC.Sensors.AirData.timeSample_s = 1/50; % time Sample, used for Noise Generation only

% GPS Sensor Model
AC.Sensors.GPS.rGPS_S_m = [12; 0.0; 0.5] * in2m; % GPS antenna location
AC.Sensors.GPS.rGPS_SB_m = AC.Geometry.T_S2SB * AC.Sensors.GPS.rGPS_S_m;

AC.Sensors.type.GPS = 'UBlox_M8N';
AC.Sensors.GPS = ParamDef_GPS(AC.Sensors.type.GPS, AC.Sensors.GPS);
AC.Sensors.GPS.errEnable = 1; % Enable the Error Model
AC.Sensors.GPS.timeSample_s = 1/50; % time Sample, used for Noise Generation only

