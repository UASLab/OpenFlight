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

%% Variance Subsystem Choice % 4/27/17
% Configure Effectors for specific simulation
AC_TYPE_SIMPLE = Simulink.Variant('AC_TYPE == 1');
AC_TYPE_DETAILED = Simulink.Variant('AC_TYPE == 2');

switch AC.Sim.Effectors
    case 1
        AC_TYPE = 1;
    case 2
        AC_TYPE = 2;
end

% Configure Sensors for specific simulation
AC_IMU_TYPE1 = Simulink.Variant('AC_IMU == 1');
AC_IMU_TYPE2 = Simulink.Variant('AC_IMU == 2');
AC_GPS_TYPE1 = Simulink.Variant('AC_GPS == 1');
AC_GPS_TYPE2 = Simulink.Variant('AC_GPS == 2');
AC_GPS_TYPE3 = Simulink.Variant('AC_GPS == 3');
AC_PITOT_TYPE1 = Simulink.Variant('AC_PITOT == 1');
AC_PITOT_TYPE2 = Simulink.Variant('AC_PITOT == 2');
AC_AIRDATA_TYPE1 = Simulink.Variant('AC_AIRDATA == 1');
AC_AIRDATA_TYPE2 = Simulink.Variant('AC_AIRDATA == 2');
AC_AIRDATA_TYPE3 = Simulink.Variant('AC_AIRDATA == 3');
AC_AIRDATA_TYPE4 = Simulink.Variant('AC_AIRDATA == 4');

% IMU
switch AC.Sim.Sensor.IMU
    case 1
        AC_IMU = 1;
    case 2
        AC_IMU = 2;
end

% GPS
switch AC.Sim.Sensor.GPS
    case 1
        AC_GPS = 1;
    case 2
        AC_GPS = 2;
    case 3
        AC_GPS = 3;
end

% Pitot Static
switch AC.Sim.Sensor.Pitot
    case 1
        AC_PITOT = 1;
    case 2
        AC_PITOT = 2;
end

% Airdata Sensors
switch AC.Sim.Sensor.Airdata
    case 1
        AC_AIRDATA = 1;
    case 2
        AC_AIRDATA = 2;
    case 3
        AC_AIRDATA = 3;
    case 4
        AC_AIRDATA = 4;
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
