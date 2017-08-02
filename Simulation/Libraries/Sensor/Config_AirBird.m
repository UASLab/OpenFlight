function [AirBird] = Config_AirBird(AirBird)
% Configures the AirBird Model
%
%Usage:  [AirBird] = Config_AirBird(AirBird);
%
%Inputs:
% AirBird       - Simulation Configuration Structure []
%
%Outputs:
% AirBird       - Simulation Configuration Structure
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
if nargin < 1, AirBird = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(AirBird), AirBird = []; end

% Set Default for VarSel
if ~isfield(AirBird, 'VarSel'), AirBird.VarSel = []; end
if isempty(AirBird.VarSel),  AirBird.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarAirBird_Pass', Simulink.Variant('VarAirBirdSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarAirBird_Err', Simulink.Variant('VarAirBirdSel == 1')); % Variant 1 - Scale, Bias, Noise
assignin('base', 'VarAirBird_LocErr', Simulink.Variant('VarAirBirdSel == 2')); % Variant 2 - Location Correction + Scale, Bias, Noise
assignin('base', 'VarAirBird_LocTransErr', Simulink.Variant('VarAirBirdSel == 3')); % Variant 3 - Location Correction + Transducer Model + Scale, Bias, Noise


%% Select the Variant
switch AirBird.VarSel
    case {1, 'Pass'}
        AirBird.VarSel = 1;
        
    case {2, 'Err'}
        AirBird.VarSel = 2;
        
    case {2, 'LocErr'}
        AirBird.VarSel = 2;
        
    case {3, 'LocTransErr'}
        AirBird.VarSel = 3;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarAirBirdSel', AirBird.VarSel);


%% Model Bus
% Define the bus
busNames = {'velTot_AD_mps', 'alpha_AD_rad', 'beta_AD_rad'};
AirBird.BusAirBird = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusAirBird', AirBird.BusAirBird);

