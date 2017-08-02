function [MassP] = Config_MassP(MassP)
% Configures the MassProperty Simulation Environment
%
%Usage:  [MassP] = Config_MassP(MassP);
%
%Inputs:
% MassP       - Simulation Configuration Structure []
%
%Outputs:
% MassP       - Simulation Configuration Structure
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
if nargin < 1, MassP = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(MassP), MassP = []; end

% Set Default for VarSel
if ~isfield(MassP, 'VarSel'), MassP.VarSel = []; end
if isempty(MassP.VarSel),  MassP.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarMassP_Const', Simulink.Variant('VarMassPSel == 1')); % Variant 1 - Constant Values


%% Select the Variant
switch MassP.VarSel
    case {1, 'Const'}
        MassP.VarSel = 1;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarMassPSel', MassP.VarSel);


%% Model Bus
% Define the bus
busNames = {'mass_kg', 'massDot_kgps', 'rCG_SB_m', 'rCG_B_m', 'I_B_kgm2', 'IDot_B_kgm2ps'};
busDim = {1, 1, [3, 1], [3, 1], [3, 3], [3, 3]};
MassP.BusMassP = CreateBus(busNames, [], busDim);

% Assign the bus to the base Workspace
assignin('base', 'BusMassP', MassP.BusMassP);

