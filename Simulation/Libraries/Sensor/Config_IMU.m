function [IMU] = Config_IMU(IMU)
% Configures the IMU Model
%
%Usage:  [IMU] = Config_IMU(IMU);
%
%Inputs:
% IMU       - Simulation Configuration Structure []
%
%Outputs:
% IMU       - Simulation Configuration Structure
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
if nargin < 1, IMU = []; end

nargoutchk(0, 1);

%% Default Values and Constants
if isempty(IMU), IMU = []; end

% Set Default for VarSel
if ~isfield(IMU, 'VarSel'), IMU.VarSel = []; end
if isempty(IMU.VarSel),  IMU.VarSel = 1; end


%% Define all the variants
assignin('base', 'VarIMU_Pass', Simulink.Variant('VarIMUSel == 0')); % Variant 0 - Passthrough
assignin('base', 'VarIMU_Err', Simulink.Variant('VarIMUSel == 1')); % Variant 1 - Scale, Bias, Noise
assignin('base', 'VarIMU_LocErr', Simulink.Variant('VarIMUSel == 2')); % Variant 2 - Location Correction + Scale, Bias, Noise
assignin('base', 'VarIMU_LocTransErr', Simulink.Variant('VarIMUSel == 3')); % Variant 3 - Location Correction + Transducer Model + Scale, Bias, Noise


%% Select the Variant
switch IMU.VarSel
    case {1, 'Pass'}
        IMU.VarSel = 1;
        
    case {2, 'Err'}
        IMU.VarSel = 2;
        
    case {2, 'LocErr'}
        IMU.VarSel = 2;
        
    case {3, 'LocTransErr'}
        IMU.VarSel = 3;
        
    otherwise
        error()
end

% Assign the Variant Select to the base Workspace
assignin('base', 'VarIMUSel', IMU.VarSel);


%% Model Bus
% Define the bus
busNames = {'wX_IMU_rps', 'wY_IMU_rps', 'wZ_IMU_rps', 'aX_IMU_mps2', 'aY_IMU_mps2', 'aZ_IMU_mps2', 'hX_IMU_nT', 'hY_IMU_nT', 'hZ_IMU_nT'};
IMU.BusIMU = CreateBus(busNames);

% Assign the bus to the base Workspace
assignin('base', 'BusIMU', IMU.BusIMU);

