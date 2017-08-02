function [Sim, Env] = Config_Atmos(Sim, Env)
% Configures the Environmental Atmospheric Conditions Model
%
%Usage:  [Sim, Env] = Config_Atmos(Sim, Env);
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

% Default Wind velocity; North, East, Down
if ~isfield(Env, 'windVel_L_mps'), Env.windVel_L_mps = []; end
if isempty(Env.windVel_L_mps),  Env.windVel_L_mps = [0; 0; 0]; end


% Default Wind and Turbulence Switches
if ~isfield(Env, 'windOn'), Env.windOn = []; end
if isempty(Env.windOn),  Env.windOn = 1; end

if ~isfield(Env, 'turbOn'), Env.turbOn = []; end
if isempty(Env.turbOn),  Env.turbOn = 0; end

if ~isfield(Env, 'gustOn'), Env.gustOn = []; end
if isempty(Env.gustOn),  Env.gustOn = 0; end


%% Define all the variants
assignin('base', 'VarAtmos_Const', Simulink.Variant('VarAtmosSel == 1')); % Variant 1 - Constant Values
assignin('base', 'VarAtmos_AeroBlock', Simulink.Variant('VarAtmosSel == 2')); % Variant 2 - Aerospace Blockset


%% Select the Variant
switch Sim.VarSel
    case {1, 'Const'}
        Sim.VarSel = 1;
        
        % Simple Atmos Model; constants, no turbulence/gust
        % Atmostphere Properties
        Env.dens_kgpm3 = 1.225;
        Env.temp_K = 293.15;
        Env.presStatic_Pa = 101300;
        Env.vSound_mps = sqrt(1.400 * Env.presStatic_Pa / Env.dens_kgpm3);
        
        % Turbulence Model
        Env.turbVelMag_B_mps = [0; 0; 0]; % Turbulence magnitude; u, v, w
        Env.turbRotMag_B_rps = [0; 0; 0]; % Turbulence magnitude; p, q, r
        
        % Gust Model
        Env.gustVelMag_B_mps = [0; 0; 0]; % Gust amplitude
        
    case {2, 'AeroBlock'}
        Sim.VarSel = 2;
        
        % Atmostphere Properties
        % (empty)
        
        % Dryden Wind Turbulence Model
        Env.windVelMag_mps = norm(Env.windVel_L_mps, 2); % Wind Speed at Reference Altitude (6 m)
        Env.windVelDir_deg = atan2d(Env.windVel_L_mps(1), Env.windVel_L_mps(2)); % Wind Direction
        
        % Turbulence Length Scale, wing span
        if ~isfield(Env, 'turbSpan_m'), Env.turbSpan_m = []; end
        if isempty(Env.turbSpan_m),  Env.turbSpan_m = 1; end
        
        Env.turbTimeSample_s = Sim.timeSample_s; % Turbulence Time Sample
        Env.turbSeed = randi([1, intmax('int16')], 4, 1); % Turbulence Seed
        
        % Gust Model
        Env.gustTimeStart_s = 0; % Gust Start time
        Env.gustLen_m = [1; 1; 1]; % Gust Length
        Env.gustVelMag_B_mps = [0; 0; 0]; % Gust amplitude
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarAtmosSel', Sim.VarSel);


%% Model Bus
% Define the bus
busNames = {'temp_K', 'vSound_mps', 'presStatic_Pa', 'dens_kgpm3', 'vWind_mps', 'vGust_mps', 'wGust_rps'};
busDim = {1, 1, 1, 1, [3, 1], [3, 1], [3, 1]};

Sim.BusAtmos = CreateBus(busNames, [], busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusAtmos', Sim.BusAtmos);

