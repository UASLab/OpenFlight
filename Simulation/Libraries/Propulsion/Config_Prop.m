function [Sim] = Config_Prop(Sim)
% Configures the Propulsion Simulation Environment
%
%Usage:  [Sim] = Config_Prop(Sim);
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

% Set Default for VarSel
if ~isfield(Sim, 'VarSel'), Sim.VarSel = []; end
if isempty(Sim.VarSel),  Sim.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarProp_CoefPoly1', Simulink.Variant('VarPropSel == 1')); % Variant 1 - Polynomial based coefficients, Single Prop
assignin('base', 'VarProp_CoefPoly2', Simulink.Variant('VarPropSel == 2')); % Variant 2 - Polynomial based coefficients, Two Prop


%% Select the Variant
switch Sim.VarSel
    case {1, 'CoefPoly1'}
        Sim.VarSel = 1;
        
    case {2, 'CoefPoly2'}
        Sim.VarSel = 2;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarPropSel', Sim.VarSel);

%% Model Bus
% Define the bus
Sim.elemNames = {'fProp_B_N', 'mProp_B_Nm', 'omega_rps', 'thrust_N', 'torque_Nm'};
Sim.busDim = {[3, 1], [3, 1], 1, 1, 1};
Sim.BusProp = CreateBus(Sim.elemNames, [], Sim.busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusProp', Sim.BusProp);

