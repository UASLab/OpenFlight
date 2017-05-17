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




AC.Geometry.T_S2SB = [-1, 0, 0; 0, 1, 0; 0, 0, -1];

% Constants
in2m = 0.0254;


%%
AC.aircraft = 'UltraStick25e';


%% Inertia, Mass and CG location
% Gross aircraft mass [kg] (including relevant hardware)
% AC.MassP.mass_kg  = 1.9; % Loki
AC.MassP.mass_kg  = 1.959; % Thor
% AC.MassP.mass_kg  = 1.865; % Frigg
% AC.MassP.mass_kg = 1.793; % AVL Model

% CG location [x y z], [m]
AC.MassP.rCG_S_m = [0.222; 0; 0.046]; % Current CG location
AC.MassP.rCG_SB_m = AC.Geometry.T_S2SB * AC.MassP.rCG_S_m;

AC.MassP.rCGRef_S_m = [0.222; 0; 0.046]; % Reference CG location, required for computing inertia when CG location is changed
AC.MassP.rCGRef_SB_m = AC.Geometry.T_S2SB * AC.MassP.rCGRef_S_m;

% Moments of inertia [kg*m^2]
% AC.MassP.IxxRef_B_kgm2 = 0.0894; % 
% AC.MassP.IyyRef_B_kgm2 = 0.1444; % 
% AC.MassP.IzzRef_B_kgm2 = 0.162; %
AC.MassP.IxxRef_B_kgm2 = 0.07151; %   % 10/29/11
AC.MassP.IyyRef_B_kgm2 = 0.08636; %  % 10/29/11
AC.MassP.IzzRef_B_kgm2 = 0.15364; %   % 10/29/11
AC.MassP.IxzRef_B_kgm2 = 0.014;

AC.MassP.IxyRef_B_kgm2 = 0.0;
AC.MassP.IyzRef_B_kgm2 = 0.0;

AC.MassP.IRef_B_kgm2 = [AC.MassP.IxxRef_B_kgm2, -AC.MassP.IxyRef_B_kgm2, -AC.MassP.IxzRef_B_kgm2;
    -AC.MassP.IxyRef_B_kgm2, AC.MassP.IyyRef_B_kgm2, -AC.MassP.IyzRef_B_kgm2;
    -AC.MassP.IxzRef_B_kgm2, -AC.MassP.IyzRef_B_kgm2, AC.MassP.IzzRef_B_kgm2];

% If the aircraft CG is not at the Reference location, then the inertia should be modified as well
AC.MassP.rCGRef_B_m = AC.MassP.rCG_SB_m - AC.MassP.rCGRef_SB_m; % CG is origin of B frame, pos vector from CG to Ref frame
AC.MassP.I_B_kgm2 = ...
    AC.MassP.IRef_B_kgm2 + AC.MassP.mass_kg * (dot(-AC.MassP.rCGRef_B_m, -AC.MassP.rCGRef_B_m)*eye(3) - (-AC.MassP.rCGRef_B_m)*(-AC.MassP.rCGRef_B_m)'); % I_CG = I_Ref + m(dot(r, r)*I + (r*r'), where r is from Ref to CG

%% Aircraft Geometric Parameters

% Remarks:
% ALL stability derivative units are radians.
% Forces are defined in the Wind frame, Moments in the Body frame

% Mean aerodynamic chord [m]
AC.Geometry.c = 0.25; % OLD
% Wing span [m]
AC.Geometry.b = 1.27; % OLD
% Wing area [m^2]
AC.Geometry.S = 0.3097; % OLD
% Wing Aspect Ratio [m^2]
AC.Geometry.AR = AC.Geometry.b^2 / AC.Geometry.S;

%%
% Aerodynamic center is Origin of the Aero Frame (force application point)
AC.Aero.rAero_S_m = [0.2175; 0; 0.046]; % OLD
AC.Aero.rAero_SB_m = AC.Geometry.T_S2SB * AC.Aero.rAero_S_m;

AC.Aero.T_Aero2W = [-1, 0, 0; 0, 1, 0; 0, 0, -1]; % Rotation Transform from Aero Frame to Wind Frame


% Flow Conditions

% Trim

% Breakpoint Definitions
AC.Aero.velBkPts = [10 12 14 16 18 20 25 30 40];
AC.Aero.betaBkPts = [-0.174532925199433 -0.0872664625997165 0 0.0872664625997165 0.174532925199433];

AC.Aero.breakPts = {AC.Aero.velBkPts, AC.Aero.betaBkPts};
AC.Aero.breakDesc = {'velocity_mps', 'beta_rad'};


%% Aero Table Setup
% Stability Table Fields, Sequence must match Simulink Model
AC.Aero.stabFields = {'zero', 'alpha', 'beta', 'alphaDot', 'betaDot', 'pHat', 'qHat', 'rHat'};
AC.Aero.stabDragFields = {'vis', 'osw'};

% Control Surfaces, Sequence must match that defined in Effector Subsystem
AC.Aero.cntrlFields = {'delev', 'drud', 'dailL', 'dailR', 'dflapL', 'dflapR'};

% Setup Lookup Tables
depList = [AC.Aero.stabFields{2:end}, AC.Aero.cntrlFields]; % Dependency vector, used to back compute the 'zero' term

% Dimension of the result of the table lookup
AC.Aero.tableDim = length(AC.Aero.breakPts) + 1;


%% Lift coefficient
AC.Aero.CL.tot = repmat(0.23, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.zero = repmat(0.1086, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.alpha = repmat(4.58, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.beta = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CL.alphaDot = repmat(0 * 1.9724, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts)); % Defined, but not used in the Old Sim
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

% Tables for Simulink
coef = 'CL';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabFields{1});
for indxSurf = 2:length(AC.Aero.stabFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields

%% Drag coefficient (CD = CD_vis + (CL - CL_minD)^2 / (pi*AR*osw) + CD_surf)
AC.Aero.CD.vis = repmat(0.0434, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.osw = repmat(0.75, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dflapR = repmat(0.5 * 0.1467, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dailR = repmat(0.5 * 0.0302, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.dailL = AC.Aero.CD.dailR;
AC.Aero.CD.dflapL = AC.Aero.CD.dflapR;
AC.Aero.CD.delev = repmat(0.0135, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CD.drud = repmat(0.0303, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

AC.Aero.CL.minD = AC.Aero.CL.tot; % This works because this model is a single condition

% Table for Simulink
coef = 'CD';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabDragFields{1});
for indxSurf = 2:length(AC.Aero.stabDragFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabDragFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields


%% Side Force coefficient
AC.Aero.CY.zero = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.alpha = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.beta = repmat(-0.4889, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.alphaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.betaDot = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.pHat = repmat(-0.0375, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.qHat = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.rHat = repmat(0.1500, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dflapR = repmat(0.5 * 0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dailR = repmat(0.5 * 0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.dailL = -AC.Aero.CY.dailR;
AC.Aero.CY.dflapL = -AC.Aero.CY.dflapR;
AC.Aero.CY.delev = repmat(0, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));
AC.Aero.CY.drud = repmat(0.1913, length(AC.Aero.velBkPts), length(AC.Aero.betaBkPts));

% Table for Simulink
coef = 'CY';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabFields{1});
for indxSurf = 2:length(AC.Aero.stabFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields


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
coef = 'Cl';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabFields{1});
for indxSurf = 2:length(AC.Aero.stabFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields


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
coef = 'Cm';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabFields{1});
for indxSurf = 2:length(AC.Aero.stabFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields


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
coef = 'Cn';

% Stability Table
AC.Aero.(coef).tableStab = AC.Aero.(coef).(AC.Aero.stabFields{1});
for indxSurf = 2:length(AC.Aero.stabFields)
    AC.Aero.(coef).tableStab = cat(AC.Aero.tableDim, AC.Aero.(coef).tableStab, AC.Aero.(coef).(AC.Aero.stabFields{indxSurf}));
end
AC.Aero.(coef).tableSelStab = 1:size(AC.Aero.(coef).tableStab, AC.Aero.tableDim); % Table select for choosing active fields

% Control Table
AC.Aero.(coef).tableCntrl = AC.Aero.(coef).(AC.Aero.cntrlFields{1});
for indxSurf = 2:length(AC.Aero.cntrlFields)
    AC.Aero.(coef).tableCntrl = cat(AC.Aero.tableDim, AC.Aero.(coef).tableCntrl, AC.Aero.(coef).(AC.Aero.cntrlFields{indxSurf}));
end
AC.Aero.(coef).tableSelCntrl = 1:size(AC.Aero.(coef).tableCntrl, AC.Aero.tableDim); % Table select for choosing active fields


%% PROPULSION

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

%Propulsion force application point (usually propeller hub) [x y z]
AC.Prop.rProp_S_m = [-0.075; 0; 0]; % [m] Propeller in front of reference point
AC.Prop.rProp_SB_m = AC.Geometry.T_S2SB * AC.Prop.rProp_S_m;

% Thrust alignment orientation (Body to Prop rotations 3-2-1), radians
AC.Prop.sProp_B_rad = [0, 0, -3] * pi/180; % FIXME - Thrust line is slightly up and slightly right of Body X

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

%Throttle
AC.Prop.throttle.PosLim = 1;  % [nd]
AC.Prop.throttle.NegLim = 0; %[nd]


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
AC.Sensors.IMU.variant = 1;
AC.Sensors.GPS.variant = 1;
AC.Sensors.AirData.variant = 1;


% Configure Sensors for specific simulation
assignin('base', 'AC_IMU_TYPE1', Simulink.Variant('AC_IMU == 1'));
assignin('base', 'AC_IMU_TYPE2', Simulink.Variant('AC_IMU == 2'));
assignin('base', 'AC_IMU', AC.Sensors.IMU.variant); % IMU

assignin('base', 'AC_GPS_TYPE1', Simulink.Variant('AC_GPS == 1'));
assignin('base', 'AC_GPS_TYPE2', Simulink.Variant('AC_GPS == 2'));
assignin('base', 'AC_GPS', AC.Sensors.GPS.variant); % GPS

assignin('base', 'AC_AIRDATA_TYPE1', Simulink.Variant('AC_AIRDATA == 1'));
assignin('base', 'AC_AIRDATA_TYPE2', Simulink.Variant('AC_AIRDATA == 2'));
assignin('base', 'AC_AIRDATA', AC.Sensors.AirData.variant); % Airdata


% IMU Sensor Model
AC.Sensors.IMU.rIMU_S_m = [9.5; 0.0; 0.0] * in2m; % IMU sensor location
AC.Sensors.IMU.rIMU_SB_m = AC.Geometry.T_S2SB * AC.Sensors.IMU.rIMU_S_m;
AC.Sensors.IMU.sIMU_SB_rad = [1.0; 0.0; 1.0] * d2r; % IMU sensor orientation
AC.Sensors.IMU.type = 'ADIS16405';
AC.Sensors.IMU = ParamDef_IMU(AC.Sensors.IMU); % IMU Error Model
AC.Sensors.IMU.errEnable = 1; % Enable the Error Model
AC.Sensors.IMU.timeSample_s = 1/50; % time Sample, used for Noise Generation only

% AirData
AC.Sensors.AirData.rAirData_S_m = [1.0; 14.0; 0.0] * in2m; % Pitot-Static location
AC.Sensors.AirData.rAirData_SB_m = AC.Geometry.T_S2SB * AC.Sensors.AirData.rAirData_S_m;
AC.Sensors.AirData.sAirData_SB_rad = [0.0; 0.0; 0.0] * d2r; % Pitot-Static orientation
AC.Sensors.AirData.type = 'pitot';
AC.Sensors.AirData.typePs = 'AMS5915-1200-B';
AC.Sensors.AirData.typePd = 'AMS5915-0020-D-B';
AC.Sensors.AirData = ParamDef_AirData(AC.Sensors.AirData);
AC.Sensors.AirData.errEnable = 1;
AC.Sensors.AirData.timeSample_s = 1/50; % time Sample, used for Noise Generation only

% GPS
AC.Sensors.GPS.rGPS_S_m = [12; 0.0; 0.5] * in2m; % GPS antenna location
AC.Sensors.GPS.rGPS_SB_m = AC.Geometry.T_S2SB * AC.Sensors.GPS.rGPS_S_m;
AC.Sensors.GPS.type = 'UBlox_M8N';
AC.Sensors.GPS = ParamDef_GPS(AC.Sensors.GPS);
AC.Sensors.GPS.errEnable = 1; % Enable the Error Model
AC.Sensors.GPS.timeSample_s = 1/50; % time Sample, used for Noise Generation only

