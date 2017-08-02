function [Sim, AC] = Param_UltraStick25e(Sim, AC)
% Configures the Aircraft (UltraStick25e) for the Simulation.
%
%Usage:  [Sim, AC] = Param_UltraStick25e(Sim, AC);
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

% Generic Transformation from S to SB frame
AC.Geometry.T_S2SB = [-1, 0, 0; 0, 1, 0; 0, 0, -1];


%% Load Mass Properties
% Define the specific Mass Properties
AC.MassP = Param_MassP_UltraStick25e(Sim.MassP, AC.Geometry.T_S2SB);


%% Load Aerodynamics
% Define the specific Aero Model parameters
AC.Aero = Param_Aero_UltraStick25e(Sim.Aero, AC.Geometry.T_S2SB);


%% Propulsion
% Propulsion force application point (usually propeller hub) [x y z]
AC.Prop.rProp_S_m = [-0.075; 0; 0]; % [m] Propeller in front of reference point
AC.Prop.rProp_SB_m = AC.Geometry.T_S2SB * AC.Prop.rProp_S_m;

% Thrust alignment orientation (Body to Prop rotations 3-2-1), radians
AC.Prop.sProp_B_rad = [0; 0; -3] * pi/180; % FIXME - Thrust line is slightly up and slightly right of Body X

% Motor Model Parameters
AC.Motor.Def.motorType = 'Power25';
[AC.Motor] = Param_Motor(AC.Motor.Def, []);

% Propulsion Model Parameters
AC.Prop.Def.propType = 'APC_12X6e';
[AC.Prop] = Param_Prop(AC.Prop.Def, AC.Prop);

% Override Motor Inetia with Combined Inertia
AC.Motor.Jmp_kgm2 = AC.Prop.Jmp_kgm2 + AC.Motor.Jmp_kgm2;


%% Configure Control Surfaces
Sim.Surf.surfList = {'elev', 'rud', 'ailL', 'ailR', 'flapL', 'flapR'};
Sim.Surf.servoList = repmat({'225BB'}, size(Sim.Surf.surfList));

numSurf = length(Sim.Surf.surfList);
for indxSurf = 1:numSurf
    surfName = Sim.Surf.surfList{indxSurf};
    AC.Surf.Def.(surfName).servoType = Sim.Surf.servoList{indxSurf};
    [AC.Surf.(surfName)] = Param_Servo(AC.Surf.Def.(surfName), []);
    
    % Override settings for position limits
    AC.Surf.(surfName).servoLimPos_rad = 25 * d2r;
    AC.Surf.(surfName).servoLimNeg_rad = -25 * d2r;
    
    % Specify parameters for the linkage
    AC.Surf.(surfName).linkGain_nd = 1.0;
    AC.Surf.(surfName).linkFreeplay_rad = 0.5 * d2r;
    
    % Specify parameters for the control surface
    AC.Surf.(surfName).surfInertia_kgm2 = NaN;
end


%% Configure Sensor Models
% IMU Sensor Model
AC.IMU.rImu_S_m = [9.5; 0.0; 0.0] * in2m; % IMU sensor location
AC.IMU.rImu_SB_m = AC.Geometry.T_S2SB * AC.IMU.rImu_S_m;
AC.IMU.sImu_B_rad = [0.0; 0.0; 0.0] * d2r; % IMU sensor orientation
AC.IMU.T_B2IMU = eye(3); % FIXME - compute from orientation

Sim.IMU.type = 'ADIS16405';
[AC.IMU] = Param_IMU(Sim.IMU, AC.IMU); % IMU Model

% AirData Sensor Model
AC.Pitot.rPitot_S_m = [1.0; 14.0; 0.0] * in2m; % Pitot-Static location
AC.Pitot.rPitot_SB_m = AC.Geometry.T_S2SB * AC.Pitot.rPitot_S_m;
AC.Pitot.sPitot_SB_rad = [0.0; 0.0; 0.0] * d2r; % Pitot-Static orientation
AC.Pitot.T_B2Pitot = eye(3); % FIXME - compute from orientation

Sim.Pitot.typePs = 'AMS5915-1200-B';
Sim.Pitot.typePd = 'AMS5915-0020-D-B';
[AC.Pitot] = Param_Pitot(Sim.Pitot, AC.Pitot);

% GPS Sensor Model
AC.GPS.rGPS_S_m = [12; 0.0; 0.5] * in2m; % GPS antenna location
AC.GPS.rGPS_SB_m = AC.Geometry.T_S2SB * AC.GPS.rGPS_S_m;

Sim.GPS.type = 'UBlox_M8N';
[AC.GPS] = Param_GPS(Sim.GPS, AC.GPS);

