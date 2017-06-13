function [Sim] = SimConfig(Sim)
% Configures the Simulation Environment
%
%Usage:  [Sim] = SimConfig(Sim);
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
narginchk(0, 1);
    if nargin < 1, Sim = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Sim), Sim = []; end


%

%% Configure Simulation System Variations
% Simulation sample time
Sim.SampleTime = 0.02; % sec

% Simulation Aerodynamic Variants Definition
Sim.Var.VarAero_Gen = Simulink.Variant('VarAeroSel == 1'); % Variant 1 - Generic, Table Look-ups with V, alpha, beta input
assignin('base', 'VarAeroSel', Sim.Aero.VarSel);

% Simulation EOM Variants Definition
Sim.Var.VarEom_Simp = Simulink.Variant('VarEomSel == 1'); % Variant 1 - Simplified Open-Source
Sim.Var.VarEom_Adv = Simulink.Variant('VarEomSel == 2'); % Variant 2 - High-Fidelity, requires Aerospace Blockset
assignin('base', 'VarEomSel', Sim.Eom.VarSel);


% Control Surface
% Configure Control Surface Variants
Sim.Var.VarSurf_Pass = Simulink.Variant('VarSurfSel == 0'); % Variant 0 - Passthrough
Sim.Var.VarSurf_Tf = Simulink.Variant('VarSurfSel == 1'); % Variant 1 - Simple Transfer Function only
Sim.Var.VarSurf_TfAdv = Simulink.Variant('VarSurfSel == 2'); % Variant 2 - Transfer Function w/Delay and Position and Rate Limits
Sim.Var.VarSurf_TfAdvLink = Simulink.Variant('VarSurfSel == 3'); % Variant 3 - Actuator + Linkage
assignin('base', 'VarSurfSel', Sim.Surf.VarSel); % Control Surface Variatint Select


% Sensors
% Configure IMU Variants
Sim.Var.VarImu_Pass = Simulink.Variant('VarImuSel == 0'); % Variant 0 - Passthrough
Sim.Var.VarImu_Err = Simulink.Variant('VarImuSel == 1'); % Variant 1 - Error Model Only
Sim.Var.VarImu_LocErr = Simulink.Variant('VarImuSel == 2'); % Variant 2 - Location + Error Model
Sim.Var.VarImu_LocTransErr = Simulink.Variant('VarImuSel == 3'); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarImuSel', Sim.Sens.IMU.VarSel); % IMU Variatint Select

% Configure GPS Variants
Sim.Var.VarGps_Pass = Simulink.Variant('VarGpsSel == 0'); % Variant 0 - Passthrough
Sim.Var.VarGps_Err = Simulink.Variant('VarGpsSel == 1'); % Variant 1 - Error Model Only
Sim.Var.VarGps_LocErr = Simulink.Variant('VarGpsSel == 2'); % Variant 2 - Location + Error Model
Sim.Var.VarGps_LocTransErr = Simulink.Variant('VarGpsSel == 3'); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarGpsSel', Sim.Sens.GPS.VarSel); % GPS Variatint Select

% Configure AirData Variants
Sim.Var.VarAirData_Pass = Simulink.Variant('VarAirDataSel == 0'); % Variant 0 - Passthrough
Sim.Var.VarAirData_Err = Simulink.Variant('VarAirDataSel == 1'); % Variant 1 - Error Model Only
Sim.Var.VarAirData_LocErr = Simulink.Variant('VarAirDataSel == 2'); % Variant 2 - Location + Error Model
Sim.Var.VarAirData_LocTransErr = Simulink.Variant('VarAirDataSel == 3'); % Variant 3 - Location + Transducer + Error Model
assignin('base', 'VarAirDataSel', Sim.Sens.AirData.VarSel); % AirData Variatint Select


%% Setup Simulation Buses
GeneralBuses; % FIXIT - Should define buses in the Sim Structure

