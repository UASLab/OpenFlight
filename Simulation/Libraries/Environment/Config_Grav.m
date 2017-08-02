function [Sim, Env] = Config_Grav(Sim, Env)
% Configures the Environmental Gravity Model
%
%Usage:  [Sim, Env] = Config_Grav(Sim, Env);
%
%Inputs:
% Sim       - Simulation Configuration Structure []
%
%Outputs:
% Sim       - Simulation Configuration Structure
%
%Notes:
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

% Set Default for VarSel
if ~isfield(Sim, 'VarSel'), Sim.VarSel = []; end
if isempty(Sim.VarSel),  Sim.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarGrav_Const', Simulink.Variant('VarGravSel == 1')); % Variant 1 - Constant Values
assignin('base', 'VarGrav_AeroBlock', Simulink.Variant('VarGravSel == 2')); % Variant 2 - Aerospace Blockset


%% Select the Variant
switch Sim.VarSel
    case {1, 'Const'} % Simple Gravity Model; constant
        Sim.VarSel = 1;
        
        Env.aGrav_L_mps2 = [0; 0; 9.81]; % FIXIT - Move to Param_Grav()
        
    case {2, 'AeroBlock'}
        Sim.VarSel = 2;
        
        % (empty)
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarGravSel', Sim.VarSel);


%% Model Bus
% Define the bus
busNames = {'aGrav_L_mps2'};
busDim = {3};

Sim.BusGrav = CreateBus(busNames, [], busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusGrav', Sim.BusGrav);

