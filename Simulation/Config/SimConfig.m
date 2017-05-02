function [AC,Env] = SimConfig(aircraft, fileSave)
% function [AC,Env] = SimConfig(aircraft, fileSave)
%
% Defines aircraft parameters. Input desired aircraft and savefile boolean.
% Sets Env data structure.
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%

if nargin < 2, fileSave = []; end


switch lower(aircraft)
    case 'ultrastick120'
        % Defice Aircraft Specific Parameters
        AC = ParamDef_UltraStick120;
        
        % Define Aircraft Specific Buses
        BusDef_UltraStick120;
        
    case 'ultrastick25e'
        % Defice Aircraft Specific Parameters
        AC = ParamDef_UltraStick25e;
        
        % Define Aircraft Specific Buses
        BusDef_UltraStick25e;
        
    case 'maewing2'
        % Defice Aircraft Specific Parameters
        AC = ParamDef_mAEWing2;
        
        % Define Aircraft Specific Buses
        BusDef_mAEWing2;
end


%% Environmental Parameters
%%% Dryden Wind Turbulence Model (+q +r)
Env.Winds.TurbulenceOn=0;
Env.Winds.TurbWindSpeed = 2; % these params determine the turbulence level for 1000 ft and below
Env.Winds.TurbWindDir = 0;

%%% Wind Gust Model
Env.Winds.GustOn=0;
% Gust Start time (sec)
Env.Winds.GustStartTime = 0;
% Gust Length [dx dy dz] (m)
Env.Winds.GustLength = [1 1 1];
% Gust amplitude [ug vg wg] (m/s)
Env.Winds.GustAmplitude = [1 1 1];

%%% Horizontal Wind Model
Env.Winds.SteadyWindOn=0;
Env.Winds.WindSpeed = 0;
Env.Winds.WindDir = 0;

% Date
Env.DecimalYear = decyear(now);
Env.Date = datestr(now);

% Ground Altitude-for advanced simulation, import terrain data lookup here
Env.GroundAlt = 0;


%% Save workspace variables to MAT file
if ~isempty(fileSave)
    save(fileSave, 'AC', 'Env');
    
    % Output a message to the screen
    fprintf('\n Aircraft configuration saved as:\t %s\n', fileSave);
end
