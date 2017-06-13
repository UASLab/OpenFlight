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
AC.Prop.powerPosLim_w = 400;
AC.Prop.powerNegLim_w = 0;

% Motor Rotation rate limits
AC.Prop.omegaPosLim_rps = 12000 * rpm2rps;
AC.Prop.omegaNegLim_rps = 1;

% Motor Throttle command limits
AC.Prop.throtPosLim_nd = 1;
AC.Prop.throtNegLim_nd = 0;

% Motor bus
Sim.Prop.elemNames = {'throttle_nd'};
Sim.Bus.Motor = CreateBus(Sim.Prop.elemNames);


%% Configure Effectors
surfList = {'elev', 'rud', 'ailL', 'ailR', 'flapL', 'flapR'};
servoList = repmat({'225BB'}, size(surfList));
for indxSurf = 1:length(surfList)
    surf = surfList{indxSurf};
    AC.Surf.Def.(surf).servoType = servoList{indxSurf};
    [AC.Surf.Def, AC.Surf.(surf)] = ParamDef_Surf(AC.Surf.Def.(surf), []);
    
    % Specify parameters for the linkage
    AC.Surf.(surf).linkPosLim_rad = 25 * d2r;
    AC.Surf.(surf).linkNegLim_rad = -25 * d2r;
    AC.Surf.(surf).linkFreeplay_rad = 0.5 * d2r;
end

% Define Actuator Bus
Sim.Act.elemNames = {'elevator_rad', 'rudder_rad', 'l_aileron_rad', 'r_aileron_rad', 'l_flap_rad', 'r_flap_rad'}; % Outputs of Servo Models
Sim.busAct = CreateBus(Sim.Act.elemNames);

% Define Surf bus
Sim.Surf.elemNames = Sim.Act.elemNames; % Outputs of Linkage Models
Sim.busSurf = CreateBus(Sim.Surf.elemNames);


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
% Pilot Commands
Sim.Pilot.elemNames = {'dthr_pilot', 'de_pilot', 'dr_pilot', 'da_l_pilot', 'da_r_pilot', 'df_l_pilot', 'df_r_pilot','mode'};
Sim.busPilot = CreateBus(Sim.Pilot.elemNames);

% Commands bus
Sim.Cmds.elemNames = [Sim.Prop.elemNames, Sim.Act.elemNames];
Sim.busCmds = CreateBus(Sim.Cmds.elemNames);

% Refs bus
Sim.Guid.elemNames = {'lat_cmd_guid', 'long_cmd_guid'};
Sim.busGuid = CreateBus(Sim.Guid.elemNames);

% Effectors bus
Sim.Eff.elemNames = {'busMotor', 'busAct', 'busSurf'};
Sim.Eff.elemDataType = {'Bus: busMotor', 'Bus: busAct', 'Bus: busSurf'};
Sim.busEff = CreateBus(Sim.Eff.elemNames, Sim.Eff.elemDataType);

% Sensor Subsystems
Sim.busIMU = CreateBus(Sim.Sens.IMU.elemNames);
Sim.busGPS = CreateBus(Sim.Sens.GPS.elemNames);
Sim.busAirData = CreateBus(Sim.Sens.AirData.elemNames);

% Sensors bus
Sim.Sens.elemNames = {'busIMU', 'busGPS', 'busAirData'};
Sim.Sens.elemDataType = {'Bus: busIMU', 'Bus: busGPS', 'Bus: busAirData'};
Sim.busSens = CreateBus(Sim.Sens.elemNames, Sim.Sens.elemDataType);

