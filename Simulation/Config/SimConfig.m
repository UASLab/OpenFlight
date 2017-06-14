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
assignin('base', 'VarAero_Gen', Simulink.Variant('VarAeroSel == 1')); % Variant 1 - Generic, Table Look-ups with V, alpha, beta input
assignin('base', 'VarAero_120', Simulink.Variant('VarAeroSel == 2')); % Variant 1 - UltraStick120 Table Look-ups
assignin('base', 'VarAeroSel', Sim.Aero.VarSel);

% Simulation EOM Variants Definition
assignin('base', 'VarEom_Simp', Simulink.Variant('VarEomSel == 1')); % Variant 1 - Simplified Open-Source
assignin('base', 'VarEom_Adv', Simulink.Variant('VarEomSel == 2')); % Variant 2 - High-Fidelity, requires Aerospace Blockset
assignin('base', 'VarEomSel', Sim.Eom.VarSel);


%% Setup Simulation Buses
GeneralBuses; % FIXIT - Should define buses in the Sim Structure

