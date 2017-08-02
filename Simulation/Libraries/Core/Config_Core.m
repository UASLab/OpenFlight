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


%% Subsystem Model Setup
% External Forces Bus
busNames = {'fExt_B_N', 'mExt_B_Nm'};
busDim = {[3, 1], [3, 1]};

Sim.BusExtForce = CreateBus(busNames, [], busDim);

assignin('base', 'BusExtForce', Sim.BusExtForce);


%% Equations of Motion
[Sim.Eom] = Config_Eom(Sim.Eom);


%% Auxiliary Equations
[Sim.Flow] = Config_Flow(Sim.Flow);
[Sim.Nav] = Config_Nav(Sim.Nav);

% Auxiliary Bus
busNames =    {'BusFlow', 'BusNav'};
busDataType = {'Bus: BusFlow', 'Bus: BusNav'};

Sim.BusAux = CreateBus(busNames, busDataType);

assignin('base', 'BusAux', Sim.BusAux);


%% Environment Models
% Earth Parameters
Env.Earth.radiusEquator_m = 6378137.0; % Earth Radius around Equator per WGS84
Env.Earth.radiusPolar_m = 6356752.3; % Earth Radius around Polar per WGS84

% Set Defaults
if ~isfield(Env, 'Atmos'), Env.Atmos = []; end
if ~isfield(Env, 'Terr'), Env.Terr = []; end
if ~isfield(Env, 'Grav'), Env.Grav = []; end
if ~isfield(Env, 'Mag'), Env.Mag = []; end

% Sub-system Models
[Sim.Atmos, Env.Atmos] = Config_Atmos(Sim.Atmos, Env.Atmos); % Atmosphere Model
[Sim.Terr, Env.Terr] = Config_Terr(Sim.Terr, Env.Terr); % Terrain Model
[Sim.Grav, Env.Grav] = Config_Grav(Sim.Grav, Env.Grav); % Gravity Model
[Sim.Mag, Env.Mag] = Config_Mag(Sim.Mag, Env.Mag); % Magnetic Model

% Environment Bus
busNames = {'BusAtmos', 'BusTerr', 'BusGrav', 'BusMag'};
busDataType = {'Bus: BusAtmos', 'Bus: BusTerr', 'Bus: BusGrav', 'Bus: BusMag'};

Sim.BusEnv = CreateBus(busNames, busDataType);

assignin('base', 'BusEnv', Sim.BusEnv);


%% Setup BusCore
busNames = {'BusEom', 'BusAux', 'BusEnv'};
busDataType = {'Bus: BusEom', 'Bus: BusAux', 'Bus: BusEnv'};

Sim.BusCore = CreateBus(busNames, busDataType);
assignin('base', 'BusCore', Sim.BusCore);



