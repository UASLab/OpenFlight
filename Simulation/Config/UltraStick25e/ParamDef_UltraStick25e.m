function [Sim, AC] = ParamDef_UltraStick25e(Sim, AC)
% Configures the Aircraft (UltraStick25e) for the Simulation.
%
%Usage:  [Sim, AC] = ParamDef_UltraStick25e(Sim, AC);
%
%Inputs:
% Sim      - Simulation Configuration Structure []
% AC       - Aircraft Configuration Structure []
%
%Outputs:
% Sim      - Simulation Configuration Structure
% AC       - Aircraft Configuration Structure
%
%Notes:
% 
% The Simulation uses aircraft coordinates in the Body (B) frame only. However, it is often
% useful to specify vehicle setup in a seperate frame, whose origin does not move with the CG
% location.
% S (Structural) - Origin at the center of the firewall [+Aft, +Right Wing, +Up]
% B (Body)       - Origin at the CG                     [+Fwd, +Right Wing, +Down]
% SB (Structural, Body Oriented) - Origin at the center of the firewall [+Fwd, +Right Wing, +Down]
% Aero (Aeodynamic) - Origin at the Aerodynamic Center, aligned with flow [+Downstream, +Right Wing, +Up]
% Prop (Propulsion) - Origin at the Prop Center, aligned with thrustline [+Fwd (Thrust), +Right Wing, +Down]
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.


%% Check I/O Arguments
narginchk(0, 2);
if nargin < 2, AC = [];
    if nargin < 1, Sim = []; end
end
 
nargoutchk(0, 2);

%% Default Values and Constants
if isempty(AC), AC = []; end
if isempty(Sim), Sim = []; end

% Constants
in2m = 0.0254;
d2r = pi/180;
rpm2rps = 2*pi / 60;

% Generic Transformation from S to SB frame
AC.Geometry.T_S2SB = [-1, 0, 0; 0, 1, 0; 0, 0, -1];


%% Load Mass Properties
% Define the specific Mass Properties
AC.MassP = ParamDef_UltraStick25e_MassP(Sim.MassP, AC.Geometry.T_S2SB);


%% Load Aerodynamics
% Define the specific the Aero Model
AC.Aero = ParamDef_UltraStick25e_Aero(Sim.Aero, AC.Geometry.T_S2SB);


%% Propulsion
% Define Propulsion System
Sim.Prop.motorType = 'Power25';
Sim.Prop.propType = 'APC_12X6e';
                
% Propulsion Model Parameters
[Sim.Prop, AC.Prop] = ParamDef_Prop(Sim.Prop, []); % Load Motor+Prop, parameters are polynomial coefficients

% Propulsion force application point (usually propeller hub) [x y z]
AC.Prop.rProp_S_m = [-0.075; 0; 0]; % [m] Propeller in front of reference point
AC.Prop.rProp_SB_m = AC.Geometry.T_S2SB * AC.Prop.rProp_S_m;

% Thrust alignment orientation (Body to Prop rotations 3-2-1), radians
AC.Prop.sProp_B_rad = [0, 0, -3] * pi/180; % FIXME - Thrust line is slightly up and slightly right of Body X

% Motor Power limits
AC.Prop.powerLimPos_w = 400;
AC.Prop.powerLimNeg_w = 0;

% Motor Rotation rate limits
AC.Prop.omegaLimPos_rps = 12000 * rpm2rps;
AC.Prop.omegaLimNeg_rps = 1;

% Motor Throttle command limits
AC.Prop.throtLimPos_nd = 1;
AC.Prop.throtLimNeg_nd = 0;

% Motor bus
Sim.Prop.elemNames = {'throttle_nd'};
Sim.Bus.Motor = CreateBus(Sim.Prop.elemNames);


%% Configure Effectors
Sim.Surf.surfList = {'elev', 'rud', 'ailL', 'ailR', 'flapL', 'flapR'};
Sim.Surf.servoList = repmat({'225BB'}, size(Sim.Surf.surfList));
for indxSurf = 1:length(Sim.Surf.surfList)
    surf = Sim.Surf.surfList{indxSurf};
    AC.Act.Def.(surf).servoType = Sim.Surf.servoList{indxSurf};
    [AC.Act.Def, AC.Act.(surf)] = ParamDef_Surf(AC.Act.Def.(surf), []);
    
    % Override settings
    AC.Act.(surf).servoLimPos_rad = 25 * d2r;
    AC.Act.(surf).servoLimNeg_rad = -25 * d2r;
    
    % Specify parameters for the linkage
    AC.Act.(surf).linkGain_nd = 1.0;
    AC.Act.(surf).linkFreeplay_rad = 0.5 * d2r;
end

% Define Actuator Bus
Sim.Act.elemNames = {'elev_rad', 'rud_rad', 'ailL_rad', 'ailR_rad', 'flapL_rad', 'flapR_rad'}; % Outputs of Servo Models
Sim.BusAct = CreateBus(Sim.Act.elemNames);

% Define Surf bus
Sim.Surf.elemNames = Sim.Act.elemNames; % Outputs of Linkage Models
Sim.BusSurf = CreateBus(Sim.Surf.elemNames);


%% Configure Sensor Models
% IMU Sensor Model
AC.Sens.IMU.rImu_S_m = [9.5; 0.0; 0.0] * in2m; % IMU sensor location
AC.Sens.IMU.rImu_SB_m = AC.Geometry.T_S2SB * AC.Sens.IMU.rImu_S_m;
AC.Sens.IMU.sImu_B_rad = [0.0; 0.0; 0.0] * d2r; % IMU sensor orientation
AC.Sens.IMU.T_B2IMU = eye(3); % FIXME - compute from orientation

Sim.Sens.IMU.type = 'ADIS16405';
[Sim.Sens.IMU, AC.Sens.IMU] = ParamDef_IMU(Sim.Sens.IMU, AC.Sens.IMU); % IMU Model
AC.Sens.IMU.errEnable = 1; % Enable the Error Model
AC.Sens.IMU.timeSample_s = 1/50; % time Sample, used for Noise Generation only


% AirData Sensor Model
AC.Sens.AirData.rAirData_S_m = [1.0; 14.0; 0.0] * in2m; % Pitot-Static location
AC.Sens.AirData.rAirData_SB_m = AC.Geometry.T_S2SB * AC.Sens.AirData.rAirData_S_m;
AC.Sens.AirData.sAirData_SB_rad = [0.0; 0.0; 0.0] * d2r; % Pitot-Static orientation
AC.Sens.AirData.T_B2AirData = eye(3); % FIXME - compute from orientation

Sim.Sens.AirData.type = 'pitot';
Sim.Sens.AirData.typePs = 'AMS5915-1200-B';
Sim.Sens.AirData.typePd = 'AMS5915-0020-D-B';
[Sim.Sens.AirData, AC.Sens.AirData] = ParamDef_AirData(Sim.Sens.AirData, AC.Sens.AirData);
AC.Sens.AirData.errEnable = 1;
AC.Sens.AirData.timeSample_s = 1/50; % time Sample, used for Noise Generation only

% GPS Sensor Model
AC.Sens.GPS.rGPS_S_m = [12; 0.0; 0.5] * in2m; % GPS antenna location
AC.Sens.GPS.rGPS_SB_m = AC.Geometry.T_S2SB * AC.Sens.GPS.rGPS_S_m;

Sim.Sens.GPS.type = 'UBlox_M8N';
[Sim.Sens.GPS, AC.Sens.GPS] = ParamDef_GPS(Sim.Sens.GPS, AC.Sens.GPS);
AC.Sens.GPS.errEnable = 1; % Enable the Error Model
AC.Sens.GPS.timeSample_s = 1/50; % time Sample, used for Noise Generation only


%% Define Buses
% Buses are defined by the ParamDef Functions and placed in the Sim Structure
% Bus Definitions need to be the base workspace for the Simulation to work
% Pilot Commands
Sim.Pilot.elemNames = {'thr_pilot', 'roll_pilot', 'pitch_pilot', 'yaw_pilot', 'mode'};
Sim.Pilot.BusPilot = CreateBus(Sim.Pilot.elemNames);
assignin('base', 'BusPilot', Sim.Pilot.BusPilot);

% Commands bus
Sim.Cmds.elemNames = [Sim.Prop.elemNames, Sim.Act.elemNames];
Sim.Cmds.BusCmds = CreateBus(Sim.Cmds.elemNames);
assignin('base', 'BusCmds', Sim.Cmds.BusCmds);

% Refs bus
Sim.Guid.elemNames = {'lat_D_deg', 'long_D_deg'};
Sim.Guid.BusGuid = CreateBus(Sim.Guid.elemNames);
assignin('base', 'BusGuid', Sim.Guid.BusGuid);

% Effectors bus
Sim.Eff.elemNames = {'BusMotor', 'BusAct', 'BusSurf'};
Sim.Eff.elemDataType = {'Bus: BusMotor', 'Bus: BusAct', 'Bus: BusSurf'};
Sim.Eff.BusEff = CreateBus(Sim.Eff.elemNames, Sim.Eff.elemDataType);
assignin('base', 'BusEff', Sim.Eff.BusEff);

% Sensor Subsystems
assignin('base', 'BusIMU', Sim.Sens.IMU.BusIMU);
assignin('base', 'BusGPS', Sim.Sens.GPS.BusGPS);
assignin('base', 'BusAirData', Sim.Sens.AirData.BusAirData);

% Sensors bus
Sim.Sens.elemNames = {'BusIMU', 'BusGPS', 'BusAirData'};
Sim.Sens.elemDataType = {'Bus: BusIMU', 'Bus: BusGPS', 'Bus: BusAirData'};
Sim.Sens.BusSens = CreateBus(Sim.Sens.elemNames, Sim.Sens.elemDataType);
assignin('base', 'BusSens', Sim.Sens.BusSens);

