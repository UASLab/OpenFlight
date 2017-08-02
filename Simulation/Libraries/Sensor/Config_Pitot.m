function [Pitot] = Config_Pitot(Pitot)
% Configures the Pitot Model
%
%Usage:  [Pitot] = Config_Pitot(Pitot);
%
%Inputs:
% Pitot       - Simulation Configuration Structure []
%
%Outputs:
% Pitot       - Simulation Configuration Structure
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
if nargin < 1, Pitot = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Pitot), Pitot = []; end

% Set Default for VarSel
if ~isfield(Pitot, 'VarSel'), Pitot.VarSel = []; end
if isempty(Pitot.VarSel),  Pitot.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarPitot_Pass', Simulink.Variant('VarPitotSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarPitot_Err', Simulink.Variant('VarPitotSel == 1')); % Variant 1 - Scale, Bias, Noise
assignin('base', 'VarPitot_LocErr', Simulink.Variant('VarPitotSel == 2')); % Variant 2 - Location Correction + Scale, Bias, Noise
assignin('base', 'VarPitot_LocTransErr', Simulink.Variant('VarPitotSel == 3')); % Variant 3 - Location Correction + Transducer Model + Scale, Bias, Noise


%% Select the Variant
switch Pitot.VarSel
    case {1, 'Pass'}
        Pitot.VarSel = 1;
        
    case {2, 'Err'}
        Pitot.VarSel = 2;
        
    case {2, 'LocErr'}
        Pitot.VarSel = 2;
        
    case {3, 'LocTransErr'}
        Pitot.VarSel = 3;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarPitotSel', Pitot.VarSel);


%% Model Bus
% Define the bus
busNames = {'presDyn_AD_Pa', 'presStatic_AD_Pa', 'temp_K'};
Pitot.BusPitot = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusPitot', Pitot.BusPitot);

