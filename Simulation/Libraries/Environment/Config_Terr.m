function [Terr, Env] = Config_Terr(Terr, Env)
% Configures the Environmental Terrain Model
%
%Usage:  [Terr, Env] = Config_Terr(Terr, Env);
%
%Inputs:
% Terr       - Simulation Configuration Structure []
%
%Outputs:
% Terr       - Simulation Configuration Structure
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
    if nargin < 1, Terr = []; end
end

nargoutchk(0, 2);

%% Default Values and Constants
if isempty(Terr), Terr = []; end
if isempty(Env), Env = []; end

% Set Default for VarSel
if ~isfield(Terr, 'VarSel'), Terr.VarSel = []; end
if isempty(Terr.VarSel),  Terr.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarTerr_Const', Simulink.Variant('VarTerrSel == 1')); % Variant 1 - Constant Values


%% Select the Variant
switch Terr.VarSel
    case {1, 'Const'} % Simple Territy Model; constant
        Terr.VarSel = 1;
        
        % Terrain Parameters - FIXIT - Move to Param_Terr()
        Env.altGrd_m = 0; % Ground Altitude in Geodetic
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarTerrSel', Terr.VarSel);


%% Model Bus
% Define the bus
busNames = {'altGrnd_m'};

Terr.BusTerr = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusTerr', Terr.BusTerr);

