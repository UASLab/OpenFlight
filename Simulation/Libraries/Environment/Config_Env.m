function [Sim, Env] = Config_Env(Sim, Env)
% Configures the Atmospheric Environment
%
%Usage:  [Sim] = Config_Env(Sim);
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


%% Environment Models
% Earth Parameters - FIXIT - Move to Aux??
Env.Earth.radiusEquator_m = 6378137.0; % Earth Radius around Equator per WGS84
Env.Earth.radiusPolar_m = 6356752.3; % Earth Radius around Polar per WGS84

% Sub-system Models
[Sim.Atmos, Env.Atmos] = Config_Atmos(Sim.Atmos, Env.Atmos); % Atmosphere Model
[Sim.Terr, Env.Terr] = Config_Terr(Sim.Terr, Env.Terr); % Terrain Model
[Sim.Grav, Env.Grav] = Config_Grav(Sim.Grav, Env.Grav); % Gravity Model
[Sim.Mag, Env.Mag] = Config_Mag(Sim.Mag, Env.Mag); % Magnetic Model


%% Environment Bus
% BusEnv
busNames = {'BusAtmos', 'BusTerr', 'BusGrav', 'BusMag'};
busDataType = {'Bus: BusAtmos', 'Bus: BusTerr', 'Bus: BusGrav', 'Bus: BusMag'};
assignin('base', 'BusEnv', CreateBus(busNames, busDataType));


