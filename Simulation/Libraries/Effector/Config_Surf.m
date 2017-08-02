function [Sim] = Config_Surf(Sim)
% Configures the Control Surface Simulation Environment
%
%Usage:  [Sim] = Config_Surf(Sim);
%
%Inputs:
% Sim       - Simulation Configuration Structure []
%
%Outputs:
% Sim       - Simulation Configuration Structure
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
if nargin < 1, Sim = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Sim), Sim = []; end

% Set Default for VarSel
if ~isfield(Sim, 'VarSel'), Sim.VarSel = []; end
if isempty(Sim.VarSel),  Sim.VarSel = 2; end


%% Define all the variants
assignin('base', 'VarServo_Lin1st', Simulink.Variant('VarServoSel == 1')); % Variant 1 - 1st Order Linear
assignin('base', 'VarServo_Lin2nd', Simulink.Variant('VarServoSel == 2')); % Variant 2 - 2nd Order Linear
assignin('base', 'VarServo_NL1st', Simulink.Variant('VarServoSel == 3')); % Variant 3 - 1st Order NonLinear
assignin('base', 'VarServo_NL2nd', Simulink.Variant('VarServoSel == 4')); % Variant 4 - 2nd Order NonLinear

assignin('base', 'VarLink_Pass', Simulink.Variant('VarLinkSel == 1')); % Variant 1 - Passthrough
assignin('base', 'VarLink_Lin', Simulink.Variant('VarLinkSel == 2')); % Variant 2 - Linear, simple gain
assignin('base', 'VarLink_NL', Simulink.Variant('VarLinkSel == 3')); % Variant 3 - Nonlinear

%% Select the Variant
switch Sim.VarServoSel
    case {1, 'Lin1st'}
        Sim.VarSel = 1;
    case {2, 'Lin2nd'}
        Sim.VarSel = 2;
    case {3, 'NL1st'}
        Sim.VarSel = 3;
    case {4, 'NL2nd'}
        Sim.VarSel = 4;
        
    otherwise
        error()
end

switch Sim.VarLinkSel
    case {1, 'Pass'}
        Sim.VarLinkSel = 1;
    case {2, 'Lin'}
        Sim.VarLinkSel = 2;
    case {3, 'NL'}
        Sim.VarLinkSel = 3;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarSurfSel', Sim.VarSel);

%% Define the Model States
% Define States and Initial Conditions (The servo will use Sim.Trim.Init for initialization, states will pickup the defined names)
Sim.stateDeflList = strcat(Sim.surfList, 'StateDefl_rad'); % Deflection States
Sim.stateRateList = strcat(Sim.surfList, 'StateRate_rps'); % Rate States


%% Model Bus
% Define Servo Bus
Sim.elemNames = strcat(Sim.surfList, '_rad'); % Outputs of Servo Models
Sim.BusServo = CreateBus(Sim.elemNames);

% Define Surf bus
Sim.elemNames = Sim.elemNames; % Outputs of Linkage Models
Sim.BusSurf = CreateBus(Sim.elemNames);

% Assign the bus to the base Workspace
assignin('base', 'BusServo', Sim.BusServo);
assignin('base', 'BusSurf', Sim.BusSurf);

