function [Sim] = Config_Aero(Sim)
% Configures the Simulation Environment
%
%Usage:  [Sim] = Config_Aero(Sim);
%
%Inputs:
% Aero       - Simulation Configuration Structure []
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
assignin('base', 'VarAero_Gen', Simulink.Variant('VarAeroSel == 1')); % Variant 1 - Generic, Table Look-ups with V, alpha, beta input
assignin('base', 'VarAero_120', Simulink.Variant('VarAeroSel == 2')); % Variant 2 - UltraStick120 Table Look-ups
assignin('base', 'VarAero_GenHM', Simulink.Variant('VarAeroSel == 3')); % Variant 1 - Generic, Table Look-ups with V, alpha, beta input; hinge moments


%% Select the Variant
switch Sim.VarSel
    case {1, 'Gen'}
        Sim.VarSel = 1;
    case {2, '120'}
        Sim.VarSel = 2;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarAeroSel', Sim.VarSel);

%% Aerodynamic Model Bus
% Define the bys
Sim.busNames = {'fAero_B_N', 'mAero_B_Nm'};
Sim.busDim = {[3, 1], [3, 1]};
Sim.BusAero = CreateBus(Sim.busNames, [], Sim.busDim);

% Assing the bus to the base Workspace
assignin('base', 'BusAero', Sim.BusAero);

