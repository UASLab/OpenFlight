function [Flow] = Config_Flow(Flow)
% Configures the Aux Flow Conditions Simulation Environment
%
%Usage:  [Flow] = Config_Flow(Flow);
%
%Inputs:
% Flow       - Simulation Configuration Structure []
%
%Outputs:
% Flow       - Simulation Configuration Structure
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
if nargin < 1, Flow = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Flow), Flow = []; end

% Set Default for VarSel
if ~isfield(Flow, 'VarSel'), Flow.VarSel = []; end
if isempty(Flow.VarSel),  Flow.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarFlow_Simp', Simulink.Variant('VarFlowSel == 1')); % Variant 1 - Simplified


%% Select the Variant
switch Flow.VarSel
    case {1, 'Simp'}
        Flow.VarSel = 1;
        
    case {2, 'AeroBlock'}
        Flow.VarSel = 2;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarFlowSel', Flow.VarSel);


%% Model Bus
% Define the bus
busNames = {'mach_nd', 'qBar_Pa', 'vTrue_mps', 'alpha_rad', 'beta_rad', 'flank_rad', 'vDotTrue_mps2', 'alphaDot_rps', 'betaDot_rps', 'flankDot_rps'};
Flow.BusFlow = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusFlow', Flow.BusFlow);

