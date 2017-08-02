function [Mag, Env] = Config_Mag(Mag, Env)
% Configures the Environmental Magnetic Model
%
%Usage:  [Mag, Env] = Config_Mag(Mag, Env);
%
%Inputs:
% Mag       - Simulation Configuration Structure []
%
%Outputs:
% Mag       - Simulation Configuration Structure
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
    if nargin < 1, Mag = []; end
end

nargoutchk(0, 2);

%% Default Values and Constants
if isempty(Mag), Mag = []; end
if isempty(Env), Env = []; end

% Set Default for VarSel
if ~isfield(Mag, 'VarSel'), Mag.VarSel = []; end
if isempty(Mag.VarSel),  Mag.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarMag_Const', Simulink.Variant('VarMagSel == 1')); % Variant 1 - Constant Values
assignin('base', 'VarMag_AeroBlock', Simulink.Variant('VarMagSel == 2')); % Variant 2 - Aerospace Blockset


%% Select the Variant
switch Mag.VarSel
    case {1, 'Const'} % Simple Magity Model; constant
        Mag.VarSel = 1;
        
        % Magnetic Field at Rosemount, MN
        Env.h_L_nT = [17.7; -0.0772; 51.6]; % FIXIT - Move to Param_Mag()
        
    case {2, 'AeroBlock'}
        Mag.VarSel = 2;
        
        % Create the Date String...
        nowout = datestr(now, 'yyyymmdd') ;

        % Env.year = decyear(now);
        Env.year = str2num((nowout(1:4))) + (str2num((nowout(5:6)))-1)/12 + str2num((nowout(7:8)))/30/12 ;
        Env.date = datestr(now);
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarMagSel', Mag.VarSel);


%% Model Bus
% Define the bus
busNames = {'h_L_nT'};
busDim = {3};

Mag.BusMag = CreateBus(busNames, [], busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusMag', Mag.BusMag);

