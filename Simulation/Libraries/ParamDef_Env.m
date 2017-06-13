function [Def, Env] = ParamDef_Env(Def, Env)
% Environmental Parameters
%% Dryden Wind Turbulence Model (+q +r)
Env.Winds.TurbulenceOn = 0;
Env.Winds.TurbWindSpeed = 2; % these params determine the turbulence level for 1000 ft and below
Env.Winds.TurbWindDir = 0;


%% Wind Gust Model
Env.Winds.GustOn = 0;
% Gust Start time (sec)
Env.Winds.GustStartTime = 0;
% Gust Length [dx dy dz] (m)
Env.Winds.GustLength = [1 1 1];
% Gust amplitude [ug vg wg] (m/s)
Env.Winds.GustAmplitude = [1 1 1];


%% Horizontal Wind Model
Env.Winds.SteadyWindOn = 0;
Env.Winds.WindSpeed = 0;
Env.Winds.WindDir = 0;


%% Date
Env.DecimalYear = decyear(now);
Env.Date = datestr(now);


%% Ground Altitude-for advanced simulation, import terrain data lookup here
Env.GroundAlt = 0;