function [GPS] = Config_GPS(GPS)
% Configures the GPS Model
%
%Usage:  [GPS] = Config_GPS(GPS);
%
%Inputs:
% GPS       - Simulation Configuration Structure []
%
%Outputs:
% GPS       - Simulation Configuration Structure
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
if nargin < 1, GPS = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(GPS), GPS = []; end

% Set Default for VarSel
if ~isfield(GPS, 'VarSel'), GPS.VarSel = []; end
if isempty(GPS.VarSel),  GPS.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarGPS_Pass', Simulink.Variant('VarGPSSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarGPS_Err', Simulink.Variant('VarGPSSel == 1')); % Variant 1 - Scale, Bias, Noise
assignin('base', 'VarGPS_LocErr', Simulink.Variant('VarGPSSel == 2')); % Variant 2 - Location Correction + Scale, Bias, Noise
assignin('base', 'VarGPS_LocTransErr', Simulink.Variant('VarGPSSel == 3')); % Variant 3 - Location Correction + Transducer Model + Scale, Bias, Noise


%% Select the Variant
switch GPS.VarSel
    case {1, 'Pass'}
        GPS.VarSel = 1;
        
    case {2, 'Err'}
        GPS.VarSel = 2;
        
    case {2, 'LocErr'}
        GPS.VarSel = 2;
        
    case {3, 'LocTransErr'}
        GPS.VarSel = 3;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarGPSSel', GPS.VarSel);


%% Model Bus
% Define the bus
busNames = {'lat_GPS_deg', 'long_GPS_deg', 'alt_GPS_m', 'vX_GPS_mps', 'vY_GPS_mps', 'vZ_GPS_mps'};
GPS.BusGPS = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusGPS', GPS.BusGPS);

