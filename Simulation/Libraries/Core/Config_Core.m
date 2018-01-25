function [Sim, Env] = Config_Core(Sim, Env)
% Configures the Simulation Environment
%
%Usage:  [Sim, Env] = Config_Core(Sim, Env);
%
%Inputs:
% Sim       - Simulation Configuration Structure []
%
%Outputs:
% Sim       - Simulation Configuration Structure
%
%Notes:
% 
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.


%% Check I/O Arguments
narginchk(0, 2);
if nargin < 2, Env = [];
    if nargin < 1, Sim = []; end
end
 
nargoutchk(0, 2);

%% Default Values and Constants
if isempty(Sim), Sim = []; end
if isempty(Env), Env = []; end


%

%% Configure Simulation System Variations
% Simulation sample time
Sim.SampleTime = 0.02; % sec


%% Subsystem Model Setup
% Simulation Aerodynamic Variants Definition
assignin('base', 'VarAero_Gen', Simulink.Variant('VarAeroSel == 1')); % Variant 1 - Generic, Table Look-ups with V, alpha, beta input
assignin('base', 'VarAero_Vsp', Simulink.Variant('VarAeroSel == 2')); % Variant 2 - OpenVSP Table Look-ups
assignin('base', 'VarAeroSel', Sim.Aero.VarSel);

% Aerodynamic Model Bus
busNames = {'fAero_B_N', 'mAero_B_Nm'};
busDim = {[3, 1], [3, 1]};
assignin('base', 'BusAero', CreateBus(busNames, [], busDim));


% Simulation Propulsion Variants Definition
assignin('base', 'VarProp_Lin1_1', Simulink.Variant('VarPropSel == 1')); % Variant 1 - Simple 1st order response, based on polynomial based coefficients
assignin('base', 'VarPropSel', Sim.Prop.VarSel);

% Propulsion Model Bus
busNames = {'fProp_B_N', 'mProp_B_Nm'};
busDim = {[3, 1], [3, 1]};
assignin('base', 'BusProp', CreateBus(busNames, [], busDim));


% External Forces Bus
busNames = {'fExt_B_N', 'mExt_B_Nm'};
busDim = {[3, 1], [3, 1]};
assignin('base', 'BusExtForce', CreateBus(busNames, [], busDim));


% Mass Properties Bus
busNames = {'mass_kg', 'massDot_kgps', 'rCG_SB_m', 'rCG_B_m', 'I_B_kgm2', 'IDot_B_kgm2ps'};
busDim = {1, 1, [3, 1], [3, 1], [3, 3], [3, 3]};
assignin('base', 'BusMassP', CreateBus(busNames, [], busDim));


%% Core-EOM Setup
% Simulation EOM Variants Definition
assignin('base', 'VarEom_Simp', Simulink.Variant('VarEomSel == 1')); % Variant 1 - Simplified Open-Source
assignin('base', 'VarEom_Adv', Simulink.Variant('VarEomSel == 2')); % Variant 2 - High-Fidelity, requires Aerospace Blockset
assignin('base', 'VarEom_LocalLevel', Simulink.Variant('VarEomSel == 3')); % Variant 3 - Local-Level with Quaterions
assignin('base', 'VarEomSel', Sim.Eom.VarSel);

% Equation of Motion Bus
switch Sim.Eom.VarSel
    case 3
        busNames = {'rCG_SB_m', 'wDot_BL_B_rps2', 'w_BL_B_rps', 's_BL_rad', 'a_BI_B_mps2', 'aExt_BI_B_mps2', 'v_BE_B_mps', 'v_BE_L_mps', 'r_BE_E_m', 'r_BE_D_ddm', 'r_BE_L_m', 'T_L2B', 'T_E2L', 'T_I2E'};
        busDim = {[3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 3], [3, 3], [3, 3]};
    otherwise
        busNames = {'rCG_SB_m', 'wDot_BL_B_rps2', 'w_BL_B_rps', 's_BL_rad', 'a_BI_B_mps2', 'aExt_BI_B_mps2', 'v_BE_B_mps', 'v_BE_L_mps', 'r_BE_E_m', 'r_BE_D_ddm', 'r_BE_L_m', 'T_L2B', 'T_E2L', 'T_I2E'};
        busDim = {[3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 3], [3, 3], [3, 3]};
end
assignin('base', 'BusEom', CreateBus(busNames, [], busDim));


%% Core-Auxiliary Equation Setup
% Flow Conditions Bus
busNames = {'mach_nd', 'qBar_Pa', 'vTrue_mps', 'alpha_rad', 'beta_rad', 'flank_rad', 'vDotTrue_mps2', 'alphaDot_rps', 'betaDot_rps', 'flankDot_rps'};
assignin('base', 'BusFlow', CreateBus(busNames));

% Navigation
% Load the EGM-96 Data
load('egm96');
Sim.Nav.lat_deg = Lat;
Sim.Nav.lon_deg = Lon;
Sim.Nav.altErr_m = Alterr;
Sim.Nav.wgs84Corr = -0.53;

% Navigation Equations Bus
busNames = {'altMsl_m', 'altAgl_m', 'vGrnd_mps', 'gamma_rad', 'course_rad'};
assignin('base', 'BusNav', CreateBus(busNames));


% Auxiliary Bus
busNames =    {'BusFlow', 'BusNav'};
busDataType = {'Bus: BusFlow', 'Bus: BusNav'};
assignin('base', 'BusAux', CreateBus(busNames, busDataType));


%% Setup BusEnv
% Environment Configuration
[Sim, Env] = Config_Env(Sim, Env);


%% Setup BusCore
busNames = {'BusEom', 'BusAux', 'BusEnv'};
busDataType = {'Bus: BusEom', 'Bus: BusAux', 'Bus: BusEnv'};
assignin('base', 'BusCore', CreateBus(busNames, busDataType));



