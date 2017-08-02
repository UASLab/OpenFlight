function [Sim] = Config_Motor(Sim)
% Configures the Motor Simulation Environment
%
%Usage:  [Sim] = Config_Motor(Sim);
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
if isempty(Sim.VarSel),  Sim.VarSel = 2; end


%% Define all the variants
assignin('base', 'VarMotor_ElecLin1', Simulink.Variant('VarMotorSel == 1')); % Variant 1 - Electric, Power command from polynomial fit, 1st order response
assignin('base', 'VarMotor_ElecNL1', Simulink.Variant('VarMotorSel == 2')); % Variant 2 - Electric, Power command from polynomial fit, 1st order response with limits


%% Select the Variant
switch Sim.VarSel
    case {1, 'ElecLin1'}
        Sim.VarSel = 1;
    case {2, 'ElecNL1'}
        Sim.VarSel = 2;
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarMotorSel', Sim.VarSel);

%% Model Bus
% Define the bus
Sim.elemNames = {'omega_rps', 'torqueMotor_Nm'};
Sim.BusMotor = CreateBus(Sim.elemNames);

% Assign the bus to the base Workspace
assignin('base', 'BusMotor', Sim.BusMotor);

