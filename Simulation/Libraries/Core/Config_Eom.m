function [Eom] = Config_Eom(Eom)
% Configures the Equations of Motion Simulation Environment
%
%Usage:  [Eom] = Config_Eom(Eom);
%
%Inputs:
% Eom       - Simulation Configuration Structure []
%
%Outputs:
% Eom       - Simulation Configuration Structure
%
%Notes:
% 

% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.


%% Check I/O Arguments
narginchk(0, 1);
if nargin < 1, Eom = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(Eom), Eom = []; end

% Set Default for VarSel
if ~isfield(Eom, 'VarSel'), Eom.VarSel = []; end
if isempty(Eom.VarSel),  Eom.VarSel = 'LocalLevelQuat'; end


%% Define all the variants
% Simulation EOM Variants Definition
assignin('base', 'VarEom_Simp', Simulink.Variant('VarEomSel == 1')); % Variant 1 - Simplified Open-Source
assignin('base', 'VarEom_AeroBlock', Simulink.Variant('VarEomSel == 2')); % Variant 2 - Aerospace Blockset
assignin('base', 'VarEom_LocalLevel', Simulink.Variant('VarEomSel == 3')); % Variant 3 - Local-Level
assignin('base', 'VarEom_LocalLevelQuat', Simulink.Variant('VarEomSel == 4')); % Variant 4 - Local-Level with Quaterions


%% Select the Variant
switch Eom.VarSel
    case {1, 'Simp'}
        Eom.VarSel = 1;
        busDef = 1;
        
    case {2, 'AeroBlock'}
        Eom.VarSel = 2;
        busDef = 1;
        
    case {3, 'LocalLevel'}
        Eom.VarSel = 3;
        busDef = 1;
        
    case {4, 'LocalLevel_Quat'}
        Eom.VarSel = 4;
        busDef = 1;
        
    otherwise
        error();
end


% Assign the Variant Select to the base Workspace
assignin('base', 'VarEomSel', Eom.VarSel);


%% Model Bus
% Define the bus
switch busDef
    case {1}
        busNames = {'rCG_SB_m', 'wDot_BL_B_rps2', 'w_BL_B_rps', 's_BL_rad', 'a_BI_B_mps2', 'aExt_BI_B_mps2', 'v_BE_B_mps', 'v_BE_L_mps', 'r_BE_E_m', 'r_BE_D_ddm', 'r_BE_L_m', 'T_L2B', 'T_E2L', 'T_I2E'};
        busDim = {[3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 1], [3, 3], [3, 3], [3, 3]};
    otherwise
        error();
end


Eom.BusEom = CreateBus(busNames, [], busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusEom', Eom.BusEom);

