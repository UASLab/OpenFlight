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
% AC.Mass  = 1.959; % Thor
AC.Mass = 1.793;

% CG location [x y z], [m]
AC.Geometry.rCG = [0.222428 0.000000 0.027178]; % 4/20/17

% Gross moments of inertia [Jx Jy Jz Jxz] [kg*m^2]
% AC.Inertia.Ixx = 0.0894; % 
% AC.Inertia.Iyy = 0.1444; % 
% AC.Inertia.Izz = 0.162; % 
AC.Inertia.Ixx = 0.043800; % 4/20/17
AC.Inertia.Iyy = 0.083800; % 4/20/17
AC.Inertia.Izz = 0.119000; % 4/20/17
AC.Inertia.Ixz = 0.000000; % 4/20/17
AC.Inertia.Matrix = [AC.Inertia.Ixx  0               -AC.Inertia.Ixz;...
    0         AC.Inertia.Iyy  0;...
    -AC.Inertia.Ixz 0               AC.Inertia.Izz];


%% Aircraft Geometric Parameters

% Aerodynamic force application point (usually the aerodynamic center)[x y z]
AC.Geometry.AeroCenter = [0.2175 0 0.046]; % Z aerocenter set at CG AMM 11/2/11 %don't have an updated value
% Mean aerodynamic chord [m]
AC.Geometry.c = 0.42; % 3/30/17 value from XFLR5 plane definition
% Wing span [m]
AC.Geometry.b = 1.93; % 3/30/17 value from XFLR5 plane definition
% Wing area [m^2]
AC.Geometry.S = 0.78; % 3/30/17 value from XFLR5 plane definition
% Wing Aspect Ratio [m^2]
AC.Geometry.AR = AC.Geometry.b^2 / AC.Geometry.S;




%%

% Remarks:
% ALL stability derivative units are radians:
% Linear Derivative Model

% Force coefficients are in WIND axes.
% See Klein, Morelli, Aircraft System Identification, pg 41

% Breakpoint Definitions
AC.Aero.alphaBkPts = [-10:1:10] * pi/180; % FIXME - Must be Monotonic Increasing
AC.Aero.betaBkPts = [-15, -10, -5, 0, 5, 10, 15] * pi/180 ; % FIXME - Must be Monotonic Increasing

%% Lift coefficient
% CL_zero
AC.Aero.CL.zero = [0.1086 0.1086 0.1086 0.1086 0.1086 0.1086 0.1086 0.1086];%0.1086; %put value into an array % FASER
AC.Aero.CL.zero = repmat(AC.Aero.CL.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% CL_alpha (/rad)
AC.Aero.CL.alpha = [3.600744 3.902652 3.964720 3.969411 3.971401 3.972357 3.972859 3.973142]; %NASA DATA (UNCHANGED BY AD 3/16/2011) % 4/20/17
AC.Aero.CL.alpha = repmat(AC.Aero.CL.alpha, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_qHat (/rad); qHat = c / (2*V) * q
AC.Aero.CL.qHat = [7.497787 7.949705 8.105073 8.127211 8.139927 8.147931 8.153305 8.157091]; % 4/20/2017
AC.Aero.CL.qHat = repmat(AC.Aero.CL.qHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_alphaDot (/rps)
AC.Aero.CL.alphadot = [1.9724 1.9724 1.9724 1.9724 1.9724 1.9724 1.9724 1.9724];%1.9724; %put value into an array
AC.Aero.CL.alphadot = repmat(AC.Aero.CL.alphadot, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% CL_de (/rad)
AC.Aero.CL.delev = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.CL.delev = repmat(AC.Aero.CL.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_dailL (/rad)
AC.Aero.CL.dailL = [0.006421 0.007032 0.007155 0.007164 0.007168 0.007170 0.007171 0.007172];  % 4/20/17 %estimate based on roll power and moment arm
AC.Aero.CL.dailL = repmat(AC.Aero.CL.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_dailR (/rad)
AC.Aero.CL.dailR = AC.Aero.CL.dailL; % FIXME - Copy of Left Side
% CL_drud (/rad)
AC.Aero.CL.drud = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.CL.drud = repmat(AC.Aero.CL.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_dflapL (/rad)
AC.Aero.CL.dflapL = [4.873000e-03 5.354000e-03 5.451000e-03 5.458000e-03 5.461000e-03 5.463000e-03 5.464000e-03 5.464000e-03]; % 4/20/2017
AC.Aero.CL.dflapL = repmat(AC.Aero.CL.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CL_dflapR (/rad)
AC.Aero.CL.dflapR = AC.Aero.CL.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.CL.tableDim = 3;
AC.Aero.CL.table = cat(AC.Aero.CL.tableDim, ...
    AC.Aero.CL.zero, AC.Aero.CL.alpha, AC.Aero.CL.qHat, AC.Aero.CL.alphadot, ...
    AC.Aero.CL.delev, AC.Aero.CL.dailL, AC.Aero.CL.dailR, AC.Aero.CL.drud, AC.Aero.CL.dflapL, AC.Aero.CL.dflapR);
AC.Aero.CL.tableDesc = {'CL_zero', 'CL_alpha', 'CL_qHat', 'CL_alphaDot', 'CL_delev', 'CL_dailL', 'CL_dailR', 'CL_drud', 'CL_dflapL', 'CL_dflapR'};
AC.Aero.CL.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.CL.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.CL.tableSel = 1:size(AC.Aero.CL.table, AC.Aero.CL.tableDim);


%% Drag coefficient
% Lift at minimum drag
AC.Aero.CL.minD = 0.23;
% Minimum drag
AC.Aero.CDw.min = 0.0434;
% Oswald's coefficient
AC.Aero.CDw.osw = [0.777200 0.789600 0.794900 0.795800 0.796300 0.796700 0.796900 0.797100]; % 4/20/17

% CDw_zero
AC.Aero.CDw.zero = [0 0 0 0 0 0 0 0]; %4/20/2017
AC.Aero.CDw.zero = repmat(AC.Aero.CDw.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% CDw_de (/rad)
AC.Aero.CDw.delev = [2.290000e-04 1.320000e-04 5.200000e-05 3.700000e-05 2.700000e-05 2.100000e-05 1.700000e-05 1.400000e-05]; % 4/20/17
AC.Aero.CDw.delev = repmat(AC.Aero.CDw.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CDw_dailL (/rad)
AC.Aero.CDw.dailL = [1.126000e-03 5.010000e-04 1.800000e-04 1.250000e-04 9.200000e-05 7.000000e-05 5.500000e-05 4.500000e-05]; % 4/20/17
AC.Aero.CDw.dailL = repmat(AC.Aero.CDw.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CDw_dailR (/rad)
AC.Aero.CDw.dailR = AC.Aero.CDw.dailL; % FIXME - Copy of Left Side
% CDw_drud (/rad)
AC.Aero.CDw.drud = [0 0 0 0 0 0 0 0]; % 4/20/17
AC.Aero.CDw.drud = repmat(AC.Aero.CDw.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CDw_dflapL (/rad)
AC.Aero.CDw.dflapL = [8.440000e-04 3.780000e-04 1.360000e-04 9.400000e-05 6.900000e-05 5.300000e-05 4.200000e-05 3.400000e-05]; % 4/20/17
AC.Aero.CDw.dflapL = repmat(AC.Aero.CDw.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CDw_dflapR (/rad)
AC.Aero.CDw.dflapR = AC.Aero.CDw.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.CDw.tableDim = 3;
AC.Aero.CDw.table = cat(AC.Aero.CDw.tableDim, ...
    AC.Aero.CDw.zero, ...
    AC.Aero.CDw.delev, AC.Aero.CDw.dailL, AC.Aero.CDw.dailR, AC.Aero.CDw.drud, AC.Aero.CDw.dflapL, AC.Aero.CDw.dflapR);
AC.Aero.CDw.tableDesc = {'CDw_zero', 'CDw_delev', 'CDw_dailL', 'CDw_dailR', 'CDw_drud', 'CDw_dflapL', 'CDw_dflapR'};
AC.Aero.CDw.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.CDw.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.CDw.tableSel = 1:size(AC.Aero.CDw.table, AC.Aero.CDw.tableDim);


%% Side Force coefficient
% CYw_zero
AC.Aero.CYw.zero = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.CYw.zero = repmat(AC.Aero.CYw.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% CYw_beta (/rad)
AC.Aero.CYw.beta = [-0.116451 -0.114087 -0.110915 -0.110254 -0.109838 -0.109562 -0.109370 -0.109231]; % 4/20/2017
AC.Aero.CYw.beta = repmat(AC.Aero.CYw.beta, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_pHat (/rad); pHat = b / (2*V) * p
AC.Aero.CYw.pHat = [0.392617 0.170300 0.056280 0.036780 0.025042 0.017431 0.012217 0.008490]; % 4/20/2017
AC.Aero.CYw.pHat = repmat(AC.Aero.CYw.pHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_rHat (/rad); rHat = b / (2*V) * r
AC.Aero.CYw.rHat = [0.039175 0.128017 0.141584 0.141978 0.141948 0.141822 0.141686 0.141565]; % 4/20/2017
AC.Aero.CYw.rHat = repmat(AC.Aero.CYw.rHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% CYw_de (/rad)
AC.Aero.CYw.delev = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.CYw.delev = repmat(AC.Aero.CYw.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_dailL (/rad)
AC.Aero.CYw.dailL = [1.000000e-06 5.000000e-06 7.000000e-06 8.000000e-06 8.000000e-06 8.000000e-06 8.000000e-06 8.000000e-06]; % 4/20/2017
AC.Aero.CYw.dailL = repmat(AC.Aero.CYw.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_dailR (/rad)
AC.Aero.CYw.dailR = AC.Aero.CYw.dailL; % FIXME - Copy of Left Side
% CYw_drud (/rad)
AC.Aero.CYw.drud = [1.711000e-03 1.721000e-03 1.687000e-03 1.679000e-03 1.674000e-03 1.670000e-03 1.668000e-03 1.666000e-03]; % 4/20/2017
AC.Aero.CYw.drud = repmat(AC.Aero.CYw.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_dflapL (/rad)
AC.Aero.CYw.dflapL = [5.100000e-05 7.000000e-05 7.800000e-05 7.900000e-05 8.000000e-05 8.000000e-05 8.000000e-05 8.100000e-05]; % 4/20/2017 
AC.Aero.CYw.dflapL = repmat(AC.Aero.CYw.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% CYw_dflapR (/rad)
AC.Aero.CYw.dflapR = AC.Aero.CYw.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.CYw.tableDim = 3;
AC.Aero.CYw.table = cat(AC.Aero.CYw.tableDim, ...
    AC.Aero.CYw.zero, AC.Aero.CYw.beta, AC.Aero.CYw.pHat, AC.Aero.CYw.rHat, ...
    AC.Aero.CYw.delev, AC.Aero.CYw.dailL, AC.Aero.CYw.dailR, AC.Aero.CYw.drud, AC.Aero.CYw.dflapL, AC.Aero.CYw.dflapR);
AC.Aero.CYw.tableDesc = {'CYw_zero', 'CYw_beta', 'CYw_pHat', 'CYw_rHat', 'CYw_delev', 'CYw_dailL', 'CYw_dailR', 'CYw_drud', 'CYw_dflapL', 'CYw_dflapR'};
AC.Aero.CYw.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.CYw.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.CYw.tableSel = 1:size(AC.Aero.CYw.table, AC.Aero.CYw.tableDim);


%% Roll moment coefficient
% Cl_zero
AC.Aero.Cl.zero = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.Cl.zero = repmat(AC.Aero.Cl.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cl_beta (/rad)
AC.Aero.Cl.beta = [-1.181490e-01 -5.491100e-02 -2.124100e-02 -1.539700e-02 -1.186600e-02 -9.572000e-03 -7.998000e-03 -6.872000e-03]; % 4/20/2017
AC.Aero.Cl.beta = repmat(AC.Aero.Cl.beta, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_pHat (/rad); pHat = b / (2*V) * p
AC.Aero.Cl.pHat = [-0.362382 -0.390916 -0.397620 -0.398263 -0.398578 -0.398754 -0.398862 -0.398932]; % 4/20/2017
AC.Aero.Cl.pHat = repmat(AC.Aero.Cl.pHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_rHat (/rad); rHat = b / (2*V) * r
AC.Aero.Cl.rHat = [0.244031 0.109987 0.041471 0.029663 0.022537 0.017909 0.014735 0.012464]; % 4/20/2017
AC.Aero.Cl.rHat = repmat(AC.Aero.Cl.rHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cl_de (/rad)
AC.Aero.Cl.delev = [0.007770 0.008356 0.008476 0.008485 0.008490 0.008492 0.008493 0.008493]; % 4/20/2017
AC.Aero.Cl.delev = repmat(AC.Aero.Cl.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_dailL (/rad)
AC.Aero.Cl.dailL = [1.772000e-03 1.907000e-03 1.934000e-03 1.936000e-03 1.937000e-03 1.938000e-03 1.938000e-03 1.938000e-03]; % 4/20/2017
AC.Aero.Cl.dailL = repmat(AC.Aero.Cl.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_dailR (/rad)
AC.Aero.Cl.dailR = -AC.Aero.Cl.dailL; % FIXME - Copy of Left Side
% Cl_drud (/rad)
AC.Aero.Cl.drud = [0.007770 0.008356 0.008476 0.008485 0.008490 0.008492 0.008493 0.008493]; % 4/20/2017
AC.Aero.Cl.drud = repmat(AC.Aero.Cl.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_dflapL (/rad)
AC.Aero.Cl.dflapL = [7.480000e-04 8.080000e-04 8.200000e-04 8.210000e-04 8.220000e-04 8.220000e-04 8.220000e-04 8.220000e-04]; % 4/20/2017
AC.Aero.Cl.dflapL = repmat(AC.Aero.Cl.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cl_dflapR (/rad)
AC.Aero.Cl.dflapR = -AC.Aero.Cl.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.Cl.tableDim = 3;
AC.Aero.Cl.table = cat(AC.Aero.Cl.tableDim, ...
    AC.Aero.Cl.zero, AC.Aero.Cl.beta, AC.Aero.Cl.pHat, AC.Aero.Cl.rHat, ...
    AC.Aero.Cl.delev, AC.Aero.Cl.dailL, AC.Aero.Cl.dailR, AC.Aero.Cl.drud, AC.Aero.Cl.dflapL, AC.Aero.Cl.dflapR);
AC.Aero.Cl.tableDesc = {'Cl_zero', 'Cl_beta', 'Cl_pHat', 'Cl_rHat', 'Cl_delev', 'Cl_dailL', 'Cl_dailR', 'Cl_drud', 'Cl_dflapL', 'Cl_dflapR'};
AC.Aero.Cl.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.Cl.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.Cl.tableSel = 1:size(AC.Aero.Cl.table, AC.Aero.Cl.tableDim);


%% Pitch moment coefficient
% Cm_zero
AC.Aero.Cm.zero = [-0.0278 -0.0278 -0.0278 -0.0278 -0.0278 -0.0278 -0.0278 -0.0278];%-0.0278; %turned this value into a array
AC.Aero.Cm.zero = repmat(AC.Aero.Cm.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cm_alpha (/rad)
AC.Aero.Cm.alpha = [-1.828045 -1.681784 -1.615002 -1.603768 -1.597016 -1.592640 -1.589643 -1.587501]; % 4/20/2017
AC.Aero.Cm.alpha = repmat(AC.Aero.Cm.alpha, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_qHat (/rad); qHat = c / (2*V) * q
AC.Aero.Cm.qHat = [-10.372008 -10.841953 -10.951923 -10.963196 -10.968946 -10.972261 -10.974345 -10.975740]; % 4/20/2017
AC.Aero.Cm.qHat = repmat(AC.Aero.Cm.qHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_alphaDot (/rps)
AC.Aero.Cm.alphaDot = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.Cm.alphaDot = repmat(AC.Aero.Cm.alphaDot, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cm_de (/rad)
AC.Aero.Cm.delev = [-1.848800e-02 -1.998400e-02 -2.030100e-02 -2.032900e-02 -2.034100e-02 -2.034800e-02 -2.035200e-02 -2.035500e-02]; % 4/20/2017
AC.Aero.Cm.delev = repmat(AC.Aero.Cm.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_dailL (/rad)
AC.Aero.Cm.dailL = [-2.789000e-03 -2.948000e-03 -2.964000e-03 -2.963000e-03 -2.962000e-03 -2.961000e-03 -2.960000e-03 -2.960000e-03]; % 4/20/2017
AC.Aero.Cm.dailL = repmat(AC.Aero.Cm.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_dailR (/rad)
AC.Aero.Cm.dailR = AC.Aero.Cm.dailL; % FIXME - Copy of Left Side
% Cm_drud (/rad)
AC.Aero.Cm.drud = [0 0 0 0 0 0 0 0];
AC.Aero.Cm.drud = repmat(AC.Aero.Cm.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_dflapL (/rad)
AC.Aero.Cm.dflapL = [-3.250000e-04 -2.940000e-04 -2.720000e-04 -2.680000e-04 -2.650000e-04 -2.640000e-04 -2.620000e-04 -2.620000e-04]; % 4/20/2017
AC.Aero.Cm.dflapL = repmat(AC.Aero.Cm.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cm_dflapR (/rad)
AC.Aero.Cm.dflapR = AC.Aero.Cm.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.Cm.tableDim = 3;
AC.Aero.Cm.table = cat(AC.Aero.Cm.tableDim, ...
    AC.Aero.Cm.zero, AC.Aero.Cm.alpha, AC.Aero.Cm.qHat, AC.Aero.Cm.alphaDot, ...
    AC.Aero.Cm.delev, AC.Aero.Cm.dailL, AC.Aero.Cm.dailR, AC.Aero.Cm.drud, AC.Aero.Cm.dflapL, AC.Aero.Cm.dflapR);
AC.Aero.Cm.tableDesc = {'Cm_zero', 'Cm_alpha', 'Cm_qHat', 'Cm_alphaDot', 'Cm_delev', 'Cm_dailL', 'Cm_dailR', 'Cm_drud', 'Cm_dflapL', 'Cm_dflapR'};
AC.Aero.Cm.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.Cm.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.Cm.tableSel = 1:size(AC.Aero.Cm.table, AC.Aero.Cm.tableDim);


%% Yaw moment coefficient
% Cn_zero
AC.Aero.Cn.zero = [0 0 0 0 0 0 0 0]; % 4/20/17 
AC.Aero.Cn.zero = repmat(AC.Aero.Cn.zero, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cn_beta (/rad)
AC.Aero.Cn.beta = [0.105333 0.070854 0.062054 0.061087 0.060581 0.060282 0.060091 0.059961]; % 4/20/2017
AC.Aero.Cn.beta = repmat(AC.Aero.Cn.beta, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_pHat (/rad); pHat = b / (2*V) * p
AC.Aero.Cn.pHat = [-0.107037 -0.041185 -0.011902 -0.007045 -0.004136 -0.002255 -0.000968 -0.000049]; % 4/20/2017
AC.Aero.Cn.pHat = repmat(AC.Aero.Cn.pHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_rHat (/rad); rHat = b / (2*V) * r
AC.Aero.Cn.rHat = [-0.104692 -0.087533 -0.081097 -0.080170 -0.079638 -0.079302 -0.079078 -0.078919]; % 4/20/2017
AC.Aero.Cn.rHat = repmat(AC.Aero.Cn.rHat, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data

% Cn_de (/rad)
AC.Aero.Cn.delev = [0 0 0 0 0 0 0 0]; % 4/20/2017
AC.Aero.Cn.delev = repmat(AC.Aero.Cn.delev, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_dailL (/rad)
AC.Aero.Cn.dailL = [1.000000e-04 4.200000e-05 1.300000e-05 8.000000e-06 5.000000e-06 3.000000e-06 1.000000e-06 0]; % 4/20/2017
AC.Aero.Cn.dailL = repmat(AC.Aero.Cn.dailL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_dailR (/rad)
AC.Aero.Cn.dailR = -AC.Aero.Cn.dailL; % FIXME - Copy of Left Side
% Cn_drud (/rad)
AC.Aero.Cn.drud = [-1.050000e-03 -1.046000e-03 -1.021000e-03 -1.015000e-03 -1.011000e-03 -1.009000e-03 -1.007000e-03 -1.006000e-03]; % 4/20/2017
AC.Aero.Cn.drud = repmat(AC.Aero.Cn.drud, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_dflapL (/rad)
AC.Aero.Cn.dflapL = [1.300000e-05 -1.900000e-05 -3.400000e-05 -3.600000e-05 -3.800000e-05 -3.900000e-05 -4.000000e-05 -4.000000e-05]; % 4/20/2017
AC.Aero.Cn.dflapL = repmat(AC.Aero.Cn.dflapL, length(AC.Aero.alphaBkPts), length(AC.Aero.betaBkPts)); % FIXME - Force Monotonic Increasing, Force Beta Data
% Cn_dflapR (/rad)
AC.Aero.Cn.dflapR = -AC.Aero.Cn.dflapL; % FIXME - Copy of Left Side

% Create Table for use in Simulink
AC.Aero.Cn.tableDim = 3;
AC.Aero.Cn.table = cat(AC.Aero.Cn.tableDim, ...
    AC.Aero.Cn.zero, AC.Aero.Cn.beta, AC.Aero.Cn.pHat, AC.Aero.Cn.rHat, ...
    AC.Aero.Cn.delev, AC.Aero.Cn.dailL, AC.Aero.Cn.dailR, AC.Aero.Cn.drud, AC.Aero.Cn.dflapL, AC.Aero.Cn.dflapR);
AC.Aero.Cn.tableDesc = {'Cn_zero', 'Cn_beta', 'Cn_pHat', 'Cn_rHat', 'Cn_delev', 'Cn_dailL', 'Cn_dailR', 'Cn_drud', 'Cn_dflapL', 'Cn_dflapR'};
AC.Aero.Cn.breakPts = {AC.Aero.alphaBkPts, AC.Aero.betaBkPts};
AC.Aero.Cn.breakDesc = {'alpha_rad', 'beta_rad'};
AC.Aero.Cn.tableSel = 1:size(AC.Aero.Cn.table, AC.Aero.Cn.tableDim);


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
AC.Sensors.IMU.hx_noise = 150;   % nT 
AC.Sensors.IMU.hy_noise = 150;   % nT
AC.Sensors.IMU.hz_noise = 80000; % nT
AC.Sensors.IMU.ax_noise = 0.0008; % m/s^2
AC.Sensors.IMU.ay_noise = 0.004;  % m/s^2
AC.Sensors.IMU.az_noise = 0.004;  % m/s^2
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