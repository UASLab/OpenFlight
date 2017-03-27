function [AC] = Config_UltraStick25e()
% function [AC] = Config_UltraStick25e()
% Ultra Stick 25e configuration file. Sets aircraft parameters.
% Called from: UAV_config.m
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. All rights reserved.
%
% SVN Info: $Id: Ultrastick_config.m 765 2012-01-25 20:14:05Z murch $

AC.aircraft = 'UltraStick25e';


%% Inertia, Mass and CG location
% Gross aircraft mass [kg] (including relevant hardware)
% AC.Mass  = 1.9; % Loki
AC.Mass  = 1.959; % Thor

% CG location [x y z], [m]
AC.Geometry.rCG = [0.222 0 0.046]; % 10/29/11

% Gross moments of inertia [Jx Jy Jz Jxz] [kg*m^2]
% AC.Inertia.Ixx = 0.0894; % 
% AC.Inertia.Iyy = 0.1444; % 
% AC.Inertia.Izz = 0.162; % 
AC.Inertia.Ixx = 0.07151; %   % 10/29/11
AC.Inertia.Iyy = 0.08636; %  % 10/29/11
AC.Inertia.Izz = 0.15364; %   % 10/29/11
AC.Inertia.Ixz = 0.014;
AC.Inertia.Matrix = [AC.Inertia.Ixx  0               -AC.Inertia.Ixz;...
    0         AC.Inertia.Iyy  0;...
    -AC.Inertia.Ixz 0               AC.Inertia.Izz];


%% Aircraft Geometric Parameters

% Aerodynamic force application point (usually the aerodynamic center)[x y z]
AC.Geometry.AeroCenter = [0.2175 0 0.046]; % Z aerocenter set at CG AMM 11/2/11
% Mean aerodynamic chord [m]
AC.Geometry.c = 0.25;
% Wing span [m]
AC.Geometry.b = 1.27;
% Wing area [m^2]
AC.Geometry.S = 0.3097;




%%

% Remarks:
% ALL stability derivative units are radians:
% Linear Derivative Model

% Force coefficients are in WIND axes.
% See Klein, Morelli, Aircraft System Identification, pg 41



%% Lift coefficient
% Zero-alpha lift
AC.Aero.CL.zero = 0.1086; % FASER
% alpha derivative
AC.Aero.CL.alpha = 4.58; %NASA DATA (UNCHANGED BY AD 3/16/2011)
% Lift control (flap) derivative
AC.Aero.CL.dflap = 0.7400;
% Aileron control derivative
AC.Aero.CL.dail = 0.4751;  %estimate based on roll power and moment arm
% Pitch control (elevator) derivative
AC.Aero.CL.delev = 0.0983; % AD 3/16/2011
% alpha-dot derivative
AC.Aero.CL.alphadot = 1.9724;
% Pitch rate derivative
AC.Aero.CL.q = 6.1639; % AD 3/16/2011

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CL.alpha ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CL.alpha_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CL.delev ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CL.dele_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CL.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CL.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CL.dflap/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CL.dflap_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CL.q ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CL.q_dat = temp ;



%% Drag coefficient
% Lift at minimum drag
AC.Aero.CL.minD = 0.23;
% Minimum drag
AC.Aero.CDw.min = 0.0434;
% Lift control (flap) derivative
AC.Aero.CDw.dflap = 0.1467;
% Pitch control (elevator) derivative
AC.Aero.CDw.delev = 0.0135;
% Roll control (aileron) derivative
AC.Aero.CDw.dail = 0.0302;
% Yaw control (rudder) derivative
AC.Aero.CDw.drud = 0.0303;
% Oswald's coefficient
AC.Aero.CDw.osw = 0.75;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CDw.delev ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CDw.dele_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CDw.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CDw.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CDw.dflap/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CDw.dflap_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CDw.drud ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CDw.drud_dat = temp ;



%% Side Force coefficient
% Sideslip derivative
AC.Aero.CYw.beta = -.4889; % AD 3/30/2011
% Roll control derivative
AC.Aero.CYw.dail = 0; % AD 3/30/2011
% Yaw control derivative
AC.Aero.CYw.drud = 0.1913; % AD 3/30/2011
% Roll rate derivative
AC.Aero.CYw.p = -0.0375; % AD 3/30/2011
% Yaw rate derivative
AC.Aero.CYw.r = 0.1500; % AD 3/30/2011

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CYw.beta ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CYw.beta_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CYw.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CYw.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CYw.drud ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CYw.drud_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CYw.p ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CYw.p_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.CYw.r ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.CYw.r_dat = temp ;




%% Roll moment coefficient
% Sideslip derivative
AC.Aero.Cl.beta = -0.0545; % AD 3/30/2011
% Roll control derivative
AC.Aero.Cl.dail = -0.1646; % AD 3/30/2011
% Flap control derivative
AC.Aero.Cl.dflap = -0.0692; % right flap.Scaled based on aileron power and relative geometry. Could also scale based on lift derivative for flap
% Yaw control derivative
AC.Aero.Cl.drud = 0.0115; % AD 3/30/2011
% Roll rate derivative
AC.Aero.Cl.p = -0.4496; % AD 3/30/2011
% Yaw rate derivative
AC.Aero.Cl.r = 0.1086; % AD 3/30/2011

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.beta ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.beta_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.dflap/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.dflap_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.drud ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.drud_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.p ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.p_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cl.r ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cl.r_dat = temp ;





%% Pitch moment coefficient
% Zero-alpha pitch
AC.Aero.Cm.zero = -0.0278;% FASER
% alpha derivative
AC.Aero.Cm.alpha = -0.7230; % AD 3/16/2011
% Lift control derivative
AC.Aero.Cm.dflap  = 0.0467;
% Aileron control derivative
AC.Aero.Cm.dail  = 0.0467;    % guesstimate to be same as flaps
% Pitch control derivative
AC.Aero.Cm.delev = -0.8488; % AD 3/16/2011
% Pitch rate derivative
AC.Aero.Cm.q = -13.5664; % AD 3/16/2011

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cm.alpha ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cm.alpha_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cm.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cm.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cm.dflap/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cm.dflap_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cm.delev ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cm.delev_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cm.q ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cm.q_dat = temp ;



%% Yaw moment coefficient
% Sideslip derivative
AC.Aero.Cn.beta = 0.0723; % AD 3/30/2011
% Flap control derivative
AC.Aero.Cn.dflap = 0.0214; % estimate based on drag coeff and moment arm
% Roll control derivative
AC.Aero.Cn.dail = 0.0574; % AD 3/30/2011
% Yaw control derivative
AC.Aero.Cn.drud = -0.1811; % AD 3/30/2011
% Roll rate derivative
AC.Aero.Cn.p = 0.1180; % AD 3/30/2011
% Yaw rate derivative
AC.Aero.Cn.r = -0.1833; % AD 3/30/2011

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.beta ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.beta_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.dail/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.dail_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.dflap/2 ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.dflap_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.drud ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.drud_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.p ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.p_dat = temp ;

temp = [] ;
temp.alpha = [-10 -5 0 5 10]*pi/180 ;
temp.beta = [-15 -10 -5 0 5 10 15]*pi/180 ;
temp.data = ones(length(temp.alpha),length(temp.beta))*AC.Aero.Cn.r ;
temp.dim = 'Dimensions are [alpha]x[beta]' ;
AC.Aero.Cn.r_dat = temp ;







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

d2r = pi/180;                         % Degrees to Radians conversion

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

%% Configure Sensor Noise Parameters (taken from flight data)
AC.Sensors.NoiseOn = 1;
AC.Sensors.IMU.p_noise = 0.000001; % rad/s
AC.Sensors.IMU.q_noise = 0.000001; % rad/s
AC.Sensors.IMU.r_noise = 0.000001; % rad/s
AC.Sensors.IMU.hx_noise =150;   % nT 
AC.Sensors.IMU.hy_noise =150;   % nT
AC.Sensors.IMU.hz_noise =80000; % nT
AC.Sensors.IMU.ax_noise =0.0008; % m/s^2
AC.Sensors.IMU.ay_noise =0.004;  % m/s^2
AC.Sensors.IMU.az_noise =0.004;  % m/s^2
AC.Sensors.AirData.ias_noise = 0.001; % m/s
AC.Sensors.AirData.h_noise = 0.02; % m
% pressure based alpha/beta has larger noise; 
AC.Sensors.AirData.alpha_noise = 0.0000005; % rad
AC.Sensors.AirData.beta_noise = 0.0000005; % rad
AC.Sensors.AirData.Pd_noise = 0.00000015; % Kpa, AMS 5812
AC.Sensors.AirData.Ps_noise = 0.0000008; % Kpa, AMS 5812

%% Configure Sensor Bias Parameters
AC.Sensors.IMU.p_bias = 0; % rad/s
AC.Sensors.IMU.q_bias = 0; % rad/s
AC.Sensors.IMU.r_bias = 0; % rad/s
AC.Sensors.IMU.hx_bias = 0;   % nT 
AC.Sensors.IMU.hy_bias = 0;   % nT
AC.Sensors.IMU.hz_bias = 0; % nT
AC.Sensors.IMU.ax_bias = 0; % m/s^2
AC.Sensors.IMU.ay_bias = 0;  % m/s^2
AC.Sensors.IMU.az_bias = 0;  % m/s^2
AC.Sensors.AirData.ias_bias = 0; % m/s
AC.Sensors.AirData.h_bias = 0; % m
AC.Sensors.AirData.alpha_bias = 0; % rad
AC.Sensors.AirData.beta_bias = 0; % rad
AC.Sensors.AirData.Pd_bias = 0; % Kpa, AMS 5812
AC.Sensors.AirData.Ps_bias = 0; % Kpa, AMS 5812

%% Configure Sensor Scale Factor Parameters
AC.Sensors.IMU.p_scf = 1; % rad/s
AC.Sensors.IMU.q_scf = 1; % rad/s
AC.Sensors.IMU.r_scf = 1; % rad/s
AC.Sensors.IMU.hx_scf = 1;   % nT 
AC.Sensors.IMU.hy_scf = 1;   % nT
AC.Sensors.IMU.hz_scf = 1; % nT
AC.Sensors.IMU.ax_scf = 1; % m/s^2
AC.Sensors.IMU.ay_scf = 1;  % m/s^2
AC.Sensors.IMU.az_scf = 1;  % m/s^2
AC.Sensors.AirData.ias_scf = 1; % m/s
AC.Sensors.AirData.h_scf = 1; % m
AC.Sensors.AirData.alpha_scf = 1; % rad
AC.Sensors.AirData.beta_scf = 1; % rad
AC.Sensors.AirData.Pd_scf = 1; % Kpa, AMS 5812
AC.Sensors.AirData.Ps_scf = 1; % Kpa, AMS 5812