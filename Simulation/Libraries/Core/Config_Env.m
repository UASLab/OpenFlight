function [Sim, Env] = Config_Env(Sim, Env)
%% Atmospheric

Env.Atmos.windOn = 0;
Env.Atmos.turbOn = 0;
Env.Atmos.gustOn = 0;

% Horizontal Wind Model
Env.Atmos.windVel_L_mps = [2; 2; 0]; % Wind velocity; North, East, Down

switch Sim.Atmos.VarSel
    case 1 % Simple Atmos Model; constants, no turbulence/gust
        % Atmostphere Properties
        Env.Atmos.dens_kgpm3 = 1.225;
        Env.Atmos.temp_K = 293.15;
        Env.Atmos.presStatic_Pa = 101300;
        Env.Atmos.vSound_mps = sqrt(1.400 * Env.Atmos.presStatic_Pa / Env.Atmos.dens_kgpm3);

        % Turbulence Model
        Env.Atmos.turbVelMag_B_mps = [0; 0; 0]; % Turbulence magnitude; u, v, w
        Env.Atmos.turbRotMag_B_rps = [0; 0; 0]; % Turbulence magnitude; p, q, r
        
        % Gust Model
        Env.Atmos.gustVelMag_B_mps = [0; 0; 0]; % Gust amplitude
        
    case 2 % Aeroblockset Models
        % Atmostphere Properties
        % (empty)
        
        % Dryden Wind Turbulence Model
        Env.Atmos.windVelMag_mps = norm(Env.Atmos.windVel_L_mps, 2); % Wind Speed at Reference Altitude (6 m)
        Env.Atmos.windVelDir_deg = atan2d(Env.Atmos.windVel_L_mps(1), Env.Atmos.windVel_L_mps(2)); % Wind Direction
        Env.Atmos.turbSpan_m = 1; % Turbulence length reference, FIXIT - Check definition
        Env.Atmos.turbTimeSample_s = Sim.timeSample_s; % Turbulence Time Sample
        Env.Atmos.turbSeed = randi([1, intmax('int16')], 4, 1); % Turbulence Seed
        
        % Gust Model
        Env.Atmos.gustTimeStart_s = 0; % Gust Start time
        Env.Atmos.gustLen_m = [1; 1; 1]; % Gust Length
        Env.Atmos.gustVelMag_B_mps = [0; 0; 0]; % Gust amplitude
    otherwise
%         error(['Atmosphere Model Selection not defined: Sim.Atmos.VarSel = ' num2str(Sim.Atmos.VarSel)])
end

% Atmospheric Model Bus
busNames = {'temp_K', 'vSound_mps', 'presStatic_Pa', 'dens_kgpm3', 'vWind_mps', 'vGust_mps', 'wGust_rps'};
busDim = {1, 1, 1, 1, [3, 1], [3, 1], [3, 1]};
assignin('base', 'BusAtmos', CreateBus(busNames, [], busDim));


%% Terrain
switch Sim.Terr.VarSel
    case 1 % Simple Terrain Model; constant
        Env.Terr.altGrd_m = 0; % Ground Altitude in Geodetic
    otherwise
%         error(['Terrain Model Selection not defined: Sim.Terr.VarSel = ' num2str(Sim.Terr.VarSel)])
end

% Terrain Model Bus
busNames = {'altGrnd_m'};
assignin('base', 'BusTerr', CreateBus(busNames));


%% Gravity
switch Sim.Grav.VarSel
    case 1 % Simple Gravity Model; constant
        Env.Grav.aGrav_L_mps2 = [-0.3293; -3.9e-4; 9.80736]; % Gravity Field at Rosemount, MN
    case 2 % Aeroblockset Models
        % (empty)
    otherwise
%         error(['Gravity Model Selection not defined: Sim.Grav.VarSel = ' num2str(Sim.Grav.VarSel)])
end

% Gravity Model Bus
busNames = {'aGrav_L_mps2'};
busDim = {3};
assignin('base', 'BusGrav', CreateBus(busNames, [], busDim));


%% Magnetic Model
switch Sim.Mag.VarSel
    case 1 % Simple Magnetic Model; constant
        Env.Mag.h_L_nT = [17.7; -0.0772; 51.6]; % Magnetic Field at Rosemount, MN
        
    case 2 % Aeroblockset Models
        nowout = datestr(now, 'yyyymmdd') ;

        % Env.Date.year = decyear(now);
        Env.Date.year = str2num((nowout(1:4))) + (str2num((nowout(5:6)))-1)/12 + str2num((nowout(7:8)))/30/12 ;
        Env.Date.date = datestr(now);
    otherwise
%         error(['Magnet Model Selection not defined: Sim.Mag.VarSel = ' num2str(Sim.Mag.VarSel)])
end

% Magnetic Model Bus
busNames = {'h_L_nT'};
busDim = {3};
assignin('base', 'BusMag', CreateBus(busNames, [], busDim));


%% Environment Bus
% BusEnv
busNames = {'BusAtmos', 'BusTerr', 'BusGrav', 'BusMag'};
busDataType = {'Bus: BusAtmos', 'Bus: BusTerr', 'Bus: BusGrav', 'Bus: BusMag'};
assignin('base', 'BusEnv', CreateBus(busNames, busDataType));


%% Earth
Env.Earth.radiusEquator_m = 6378137.0; % Earth Radius around Equator per WGS84
Env.Earth.radiusPolar_m = 6356752.3; % Earth Radius around Polar per WGS84


