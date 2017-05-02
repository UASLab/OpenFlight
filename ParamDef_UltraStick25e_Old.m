function [AC] = ParamDef_UltraStick25e_Old()
% function [AC] = ParamDef_UltraStick25e_Old()
% Ultra Stick 25e configuration file. Sets aircraft parameters.
% Called from: SimConfig.m
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. All rights reserved.
%

%%
AC.aircraft = 'UltraStick25e';


%% Inertia, Mass and CG location
% Gross aircraft mass [kg] (including relevant hardware)
% AC.Mass  = 1.9; % Loki
AC.Mass  = 1.959; % Thor
% AC.Mass  = 1.865; % Frigg
% AC.Mass = 1.793; % AVL Model

% CG location [x y z], [m]
AC.Geometry.rCG = [0.222 0 0.046]; % OLD

% Moments of inertia [kg*m^2]
% AC.Inertia.Ixx = 0.0894; % 
% AC.Inertia.Iyy = 0.1444; % 
% AC.Inertia.Izz = 0.162; %
AC.Inertia.Ixx = 0.07151; %   % 10/29/11
AC.Inertia.Iyy = 0.08636; %  % 10/29/11
AC.Inertia.Izz = 0.15364; %   % 10/29/11
AC.Inertia.Ixz = 0.014;
% AC.Inertia.Ixx = 0.0437912; % AVL Model
% AC.Inertia.Iyy = 0.08381; % AVL Model
% AC.Inertia.Izz = 0.119344; % AVL Model
% AC.Inertia.Ixz = -0.000241577; % AVL Model
AC.Inertia.Ixy = 0.0;
AC.Inertia.Iyz = 0.0;
AC.Inertia.Matrix = [AC.Inertia.Ixx, -AC.Inertia.Ixy, -AC.Inertia.Ixz;
    -AC.Inertia.Ixy, AC.Inertia.Iyy, -AC.Inertia.Iyz;
    -AC.Inertia.Ixz, -AC.Inertia.Iyz, AC.Inertia.Izz];


%% Aircraft Geometric Parameters

% Remarks:
% ALL stability derivative units are radians.
% Forces are defined in the stability frame, Moments in the body frame

% Aerodynamic force application point (usually the aerodynamic center)[x y z]
AC.Geometry.AeroCenter = [0.2175 0 0.046]; % OLD
% Mean aerodynamic chord [m]
AC.Geometry.c = 0.25; % OLD
% Wing span [m]
AC.Geometry.b = 1.27; % OLD
% Wing area [m^2]
AC.Geometry.S = 0.3097; % OLD
% Wing Aspect Ratio [m^2]
AC.Geometry.AR = AC.Geometry.b^2 / AC.Geometry.S;

% Control Surfaces
AC.Aero.surfDesc = {'delev', 'dailL', 'dailR', 'drud', 'dflapL', 'dflapR'}; % Sequence as defined in Effector Subsystem

%%
% Flow Conditions

% Trim

% Breakpoint Definitions
AC.Aero.velBkPts = [10 12 14 16 18 20 25 30 40];
AC.Aero.betaBkPts = [-0.174532925199433 -0.0872664625997165 0 0.0872664625997165 0.174532925199433];

AC.Aero.breakPts = {AC.Aero.velBkPts, AC.Aero.betaBkPts};
AC.Aero.breakDesc = {'velocity_mps', 'beta_rad'};

% Setup Lookup Tables
depListStab = {'alpha', 'beta', 'alphaDot', 'betaDot', 'pHat', 'qHat', 'rHat'};
depListCntrl = AC.Aero.surfDesc;
depList = [depListStab, depListCntrl]; % Dependency vector

AC.Aero.tableDim = length(AC.Aero.breakPts) + 1; % Dimension of the result of the table lookup

%% Lift coefficient
AC.Aero.CL.tot = repmat(0.23, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.zero = repmat(0.1086, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.alpha = repmat(4.58, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.beta = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.alphaDot = repmat(1.9724, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.pHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.qHat = repmat(6.1639, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.rHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.dflapR = repmat(0.5 * 0.7400, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.dailR = repmat(0.5 * 0.4751, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.dailL = AC.Aero.CL.dailR;
AC.Aero.CL.dflapL = AC.Aero.CL.dflapR;
AC.Aero.CL.delev = repmat(0.0983, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.drud = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
AC.Aero.CL.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.CL.zero, AC.Aero.CL.alpha, AC.Aero.CL.beta, AC.Aero.CL.alphaDot, AC.Aero.CL.betaDot, ...
    AC.Aero.CL.pHat, AC.Aero.CL.qHat, AC.Aero.CL.rHat);
AC.Aero.CL.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.CL.delev, AC.Aero.CL.dailL, AC.Aero.CL.dailR, AC.Aero.CL.drud, AC.Aero.CL.dflapL, AC.Aero.CL.dflapR);

AC.Aero.CL.tableSelStab = 1:size(AC.Aero.CL.tableStab, AC.Aero.tableDim);
AC.Aero.CL.tableSelCntrl = 1:size(AC.Aero.CL.tableCntrl, AC.Aero.tableDim);

%% Drag coefficient
AC.Aero.CD.vis = repmat(0.0434, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.ind = repmat(0.08519, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.osw = repmat(0.75, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dflapR = repmat(0.5 * 0.1467, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dailR = repmat(0.5 * 0.0302, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dailL = AC.Aero.CD.dflapR;
AC.Aero.CD.dflapL = AC.Aero.CD.dailR;
AC.Aero.CD.delev = repmat(0.0135, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.drud = repmat(0.0303, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

AC.Aero.CD.tot = AC.Aero.CD.vis + AC.Aero.CD.ind; % Fix Total Drag

% Table for Simulink
AC.Aero.CD.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.CD.vis, AC.Aero.CD.ind, AC.Aero.CD.osw);
AC.Aero.CD.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.CD.delev, AC.Aero.CD.dailL, AC.Aero.CD.dailR, AC.Aero.CD.drud, AC.Aero.CD.dflapL, AC.Aero.CD.dflapR);

AC.Aero.CD.tableSelStab = 1:size(AC.Aero.CD.tableStab, AC.Aero.tableDim);
AC.Aero.CD.tableSelCntrl = 1:size(AC.Aero.CD.tableCntrl, AC.Aero.tableDim);


%% Side Force coefficient
AC.Aero.CY.zero = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.alpha = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.beta = repmat(0.4889, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.alphaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.pHat = repmat(0.0375, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.qHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.rHat = repmat(-0.1500, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dflapR = repmat(0.5 * 0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dailR = repmat(0.5 * 0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dailL = -AC.Aero.CY.dailR;
AC.Aero.CY.dflapL = -AC.Aero.CY.dflapR;
AC.Aero.CY.delev = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.drud = repmat(-0.1913, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
AC.Aero.CY.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.CY.zero, AC.Aero.CY.alpha, AC.Aero.CY.beta, AC.Aero.CY.alphaDot, AC.Aero.CY.betaDot, ...
    AC.Aero.CY.pHat, AC.Aero.CY.qHat, AC.Aero.CY.rHat);
AC.Aero.CY.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.CY.delev, AC.Aero.CY.dailL, AC.Aero.CY.dailR, AC.Aero.CY.drud, AC.Aero.CY.dflapL, AC.Aero.CY.dflapR);

AC.Aero.CY.tableSelStab = 1:size(AC.Aero.CY.tableStab, AC.Aero.tableDim);
AC.Aero.CY.tableSelCntrl = 1:size(AC.Aero.CY.tableCntrl, AC.Aero.tableDim);

%% Roll moment coefficient
AC.Aero.Cl.zero = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.alpha = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.beta = repmat(-0.0545, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.alphaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.pHat = repmat(-0.4496, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.qHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.rHat = repmat(0.1086, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.dflapR = repmat(0.5 * -0.0692, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.dailR = repmat(0.5 * -0.1646, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.dailL = -AC.Aero.Cl.dailR;
AC.Aero.Cl.dflapL = -AC.Aero.Cl.dflapR;
AC.Aero.Cl.delev = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cl.drud = repmat(0.0115, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
AC.Aero.Cl.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.Cl.zero, AC.Aero.Cl.alpha, AC.Aero.Cl.beta, AC.Aero.Cl.alphaDot, AC.Aero.Cl.betaDot, ...
    AC.Aero.Cl.pHat, AC.Aero.Cl.qHat, AC.Aero.Cl.rHat);
AC.Aero.Cl.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.Cl.delev, AC.Aero.Cl.dailL, AC.Aero.Cl.dailR, AC.Aero.Cl.drud, AC.Aero.Cl.dflapL, AC.Aero.Cl.dflapR);

AC.Aero.Cl.tableSelStab = 1:size(AC.Aero.Cl.tableStab, AC.Aero.tableDim);
AC.Aero.Cl.tableSelCntrl = 1:size(AC.Aero.Cl.tableCntrl, AC.Aero.tableDim);

%% Pitch moment coefficient
AC.Aero.Cm.zero = repmat(-0.0278, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.alpha = repmat(-0.7230, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.beta = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.alphaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.pHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.qHat = repmat(-13.5664, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.rHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.dflapR = repmat(0.5 * 0.0467, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.dailR = repmat(0.5 * 0.0467, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.dailL = AC.Aero.Cm.dailR;
AC.Aero.Cm.dflapL = AC.Aero.Cm.dflapR;
AC.Aero.Cm.delev = repmat(-0.8488, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cm.drud = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
AC.Aero.Cm.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.Cm.zero, AC.Aero.Cm.alpha, AC.Aero.Cm.beta, AC.Aero.Cm.alphaDot, AC.Aero.Cm.betaDot, ...
    AC.Aero.Cm.pHat, AC.Aero.Cm.qHat, AC.Aero.Cm.rHat);
AC.Aero.Cm.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.Cm.delev, AC.Aero.Cm.dailL, AC.Aero.Cm.dailR, AC.Aero.Cm.drud, AC.Aero.Cm.dflapL, AC.Aero.Cm.dflapR);

AC.Aero.Cm.tableSelStab = 1:size(AC.Aero.Cm.tableStab, AC.Aero.tableDim);
AC.Aero.Cm.tableSelCntrl = 1:size(AC.Aero.Cm.tableCntrl, AC.Aero.tableDim);

%% Yaw moment coefficient
AC.Aero.Cn.zero = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.alpha = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.beta = repmat(0.0723, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.alphaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.pHat = repmat(0.1180, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.qHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.rHat = repmat(-0.1833, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.dflapR = repmat(0.5 * 0.0214, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.dailR = repmat(0.5 * 0.0574, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.dailL = -AC.Aero.Cn.dailR;
AC.Aero.Cn.dflapL = -AC.Aero.Cn.dflapR;
AC.Aero.Cn.delev = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.Cn.drud = repmat(-0.1811, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
AC.Aero.Cn.tableStab = cat(AC.Aero.tableDim, ...
    AC.Aero.Cn.zero, AC.Aero.Cn.alpha, AC.Aero.Cn.beta, AC.Aero.Cn.alphaDot, AC.Aero.Cn.betaDot, ...
    AC.Aero.Cn.pHat, AC.Aero.Cn.qHat, AC.Aero.Cn.rHat);
AC.Aero.Cn.tableCntrl = cat(AC.Aero.tableDim, ...
    AC.Aero.Cn.delev, AC.Aero.Cn.dailL, AC.Aero.Cn.dailR, AC.Aero.Cn.drud, AC.Aero.Cn.dflapL, AC.Aero.Cn.dflapR);

AC.Aero.Cn.tableSelStab = 1:size(AC.Aero.Cn.tableStab, AC.Aero.tableDim);
AC.Aero.Cn.tableSelCntrl = 1:size(AC.Aero.Cn.tableCntrl, AC.Aero.tableDim);


%% PROPULSION
%Propulsion force application point (usually propeller hub) [x y z]

AC.Geometry.rProp = [-0.075 0 0]; % [m] Propeller in front of reference point

% %*********************************
% %Using a APC 11 x 8 propeller data
% %**********************************
% % Advance ratio vector
% AC.Prop.J = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1];%11x8 prop
% 
% % Coefficient of thrust look-up table CT = CT(J)
% AC.Prop.CT = [0.0947 0.1 0.0974 0.088 0.0763 0.0632 0.0461 0.0301 0.00789 -0.0171 -0.0382]; %11x8 Prop
% 
% % Coefficient of power look-up table CP = CP(J)
% AC.Prop.CP = [0.0447 0.0476 0.0494 0.05 0.0494 0.0482 0.0424 0.0318 0.0176 0.0047 -0.01]; %11x8Prop
% %Motor_cal data, old data set
% AC.Prop.Throttle = [0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1.0];
% AC.Prop.Power = [0 0.2 0.4 1.3 3.1 6.1 10.4 16.4 24.2 34 45.9 60.1 76.6 95.7 117.3 141.4 168.1 196.7 228 261.4 296.6];
% Sea-level pressure and temperature at which the data above is given
%  pSL = 102300; % Pa
% TSL = 291.15; % deg K

% Thrust alignment orientation, radians
AC.Prop.Angles = [0 0 -3]/180*pi;

% Using an APC 12 x 6E propeller, EFlite Power 25 motor
% Coefficient of thrust polynomial model 
% AEM wind tunnel test data Jan 2011
AC.Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ];

% Coefficient of power polynomial model 
% AEM wind tunnel test data Jan 2011
AC.Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223];

% Propeller radius %[m] APC 12 x 6E propeller
AC.Prop.Radius = 0.1524;

% Motor polynomial model. Input throttle, output power in watts
% EFlite Power 25, AEM wind tunnel test data Jan 2011
% Castle Creations ICE Lite 50 used to collect motor data
AC.Prop.Power = [174.46 70.135 -4.39];

AC.Prop.ThrottleOutputLimit.Upper = 400;
AC.Prop.ThrottleOutputLimit.Lower = 0;
AC.Prop.OmegaSaturation.Upper = 1256; % 12,000 RPM
AC.Prop.OmegaSaturation.Lower = 1;

% Electric motor and propeller combine moment of inertia
AC.Prop.Jmp = 0.00012991;  % [kg*m^2] From experimental measurement (not updated with Jan 2011 data)

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

%Throttle
AC.Actuator.throttle.PosLim = 1;  % [nd]
AC.Actuator.throttle.NegLim = 0; %[nd]


%% Configure Sensor Error Models

% Model Variants
AC.Sim.Sensor.IMU = 2;
AC.Sim.Sensor.GPS = 3;
AC.Sim.Sensor.Pitot = 1;
AC.Sim.Sensor.Airdata = 4;

% Flag to enable noise
AC.Sensors.NoiseOn = 1;

% Gyro Error Model Parameters (meas = scf * (true + noise) + bias)
AC.Sensors.IMU.p_scf = 1; % rad/s
AC.Sensors.IMU.q_scf = 1; % rad/s
AC.Sensors.IMU.r_scf = 1; % rad/s
AC.Sensors.IMU.p_bias = 0; % rad/s
AC.Sensors.IMU.q_bias = 0; % rad/s
AC.Sensors.IMU.r_bias = 0; % rad/s
AC.Sensors.IMU.p_noise = 0.000001; % rad/s
AC.Sensors.IMU.q_noise = 0.000001; % rad/s
AC.Sensors.IMU.r_noise = 0.000001; % rad/s

% Accelerometer Error Model Parameters (meas = scf * (true + noise) + bias)
AC.Sensors.IMU.ax_scf = 1; % m/s^2
AC.Sensors.IMU.ay_scf = 1;  % m/s^2
AC.Sensors.IMU.az_scf = 1;  % m/s^2
AC.Sensors.IMU.ax_bias = 0; % m/s^2
AC.Sensors.IMU.ay_bias = 0;  % m/s^2
AC.Sensors.IMU.az_bias = 0;  % m/s^2
AC.Sensors.IMU.ax_noise = 0.0008; % m/s^2
AC.Sensors.IMU.ay_noise = 0.004;  % m/s^2
AC.Sensors.IMU.az_noise = 0.004;  % m/s^2

% Magnetometer Error Model Parameters (meas = scf * (true + noise) + bias)
AC.Sensors.IMU.hx_scf = 1;   % nT 
AC.Sensors.IMU.hy_scf = 1;   % nT
AC.Sensors.IMU.hz_scf = 1; % nT
AC.Sensors.IMU.hx_bias = 0;   % nT 
AC.Sensors.IMU.hy_bias = 0;   % nT
AC.Sensors.IMU.hz_bias = 0; % nT
AC.Sensors.IMU.hx_noise = 150;   % nT 
AC.Sensors.IMU.hy_noise = 150;   % nT
AC.Sensors.IMU.hz_noise = 80000; % nT


% AirData Error Model Parameters (meas = scf * (true + noise) + bias)
% Dynamic Pressure
AC.Sensors.AirData.Pd_scf = 1; % Kpa, AMS 5812
AC.Sensors.AirData.Pd_bias = 0; % Kpa, AMS 5812
AC.Sensors.AirData.Pd_noise = 0.00000015; % Kpa, AMS 5812

% Static Pressure
AC.Sensors.AirData.Ps_scf = 1; % Kpa, AMS 5812
AC.Sensors.AirData.Ps_bias = 0; % Kpa, AMS 5812
AC.Sensors.AirData.Ps_noise = 0.0000008; % Kpa, AMS 5812

% Indicated Airspeed
AC.Sensors.AirData.ias_scf = 1; % m/s
AC.Sensors.AirData.ias_bias = 0; % m/s
AC.Sensors.AirData.ias_noise = 0.001; % m/s

% Baro Altitude
AC.Sensors.AirData.h_scf = 1; % m
AC.Sensors.AirData.h_bias = 0; % m
AC.Sensors.AirData.h_noise = 0.02; % m

% Angle of Attack
AC.Sensors.AirData.alpha_scf = 1; % rad
AC.Sensors.AirData.alpha_bias = 0; % rad
AC.Sensors.AirData.alpha_noise = 0.0000005; % rad

% Angle of Sideslip
AC.Sensors.AirData.beta_scf = 1; % rad
AC.Sensors.AirData.beta_bias = 0; % rad
AC.Sensors.AirData.beta_noise = 0.0000005; % rad

