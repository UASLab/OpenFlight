function [sysModel, sys] = LinearizeSim(simModel, Sim)
% [longmod, spmod, latmod, linmodel = LinearizeSim(simModel, Sim)
%
% Linearizes the UAV model about a given operating point.
% This function will use your workspace variables.
% Requires the Control System Toolbox and Simulink Control Design.
%
% Inputs:
%
% Outputs:
%   longmod  - longitudinal linear model
%   spmod    - short period approximation
%   latmod   - lateral directional linear model
%   linmodel - full linear model
%
%
% University of Minnesota
% Aerospace Engineering and Mechanics
% Copyright 2017 Regents of the University of Minnesota.
% All rights reserved.
%

%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end

%% Linearize

% Get the System I/O
% Model is setup with input pertubations on the desired system inputs, openloop breaks on the outputs
Sim.Trim.io = getlinio(simModel);


%% Obtain lineariziation
linOpt = linearizeOptions;
linOpt.UseBusSignalLabels = 'on';
linOpt.StoreOffsets = true;

sysModel = linearize(simModel, Sim.Trim.opPoint, Sim.Trim.io, linOpt);


%% Fix I/O and State Names
% Fix Input Names
% inListSig = [Sim.Trim.MotorNames, Sim.Trim.SurfNames];
% set(linmodel, 'InputName', inListSig);

% Fix Output Names of the linear model
outList = get(Sim.Trim.opSpec.Outputs, 'Block');
outListSig = strrep(outList, [simModel '/'], '');
set(sysModel, 'OutputName', outListSig);

% Fix State Names
% Rotation Rates
indxW = strcmp(sysModel.StateName, 'wState_BI_B_rps');
if sum(indxW) == 3, sysModel.StateName(indxW) = {'p_rps', 'q_rps', 'r_rps'}; end

% Quaterions
indxQuat = strcmp(sysModel.StateName, 'quatState');
if sum(indxQuat) == 4, sysModel.StateName(indxQuat) = {'quatState1', 'quatState2', 'quatState3', 'quatState4'}; end

% Velocity
indxV = strcmp(sysModel.StateName, 'vState_BI_B_mps');
if sum(indxV) == 3, sysModel.StateName(indxV) = {'vX_B_mps', 'vY_B_mps', 'vZ_B_mps'}; end

% Position
indxR = strcmp(sysModel.StateName, 'rState_BI_L_m');
if sum(indxR) == 3, sysModel.StateName(indxR) = {'rX_L_m', 'rY_L_m', 'rZ_L_m'}; end


if nargout > 1
    %% Complete Model
    sys.sysModel = sysModel;
    
    
    %% Longitudinal Linear Model
    inNames = {'elev_rad', 'throttle_nd'};
    outNames = {'vTrue_mps', 'alpha_rad', 'q_rps', 'theta_rad', 'altAgl_m', 'aX_mps2', 'aZ_mps2'};
    stateNames = {'vX_B_mps', 'vZ_B_mps', 'q_rps', 'quatState1', 'quatState2', 'quatState3', 'quatState4', 'omegaState_rps'};
    
    sysLong = ModelReduce(sysModel, inNames, outNames, stateNames);
    sys.sysLong = sysLong;
    
    %% Short-Period Linear Model
    inNames = {'elev_rad'};
    outNames = {'alpha_rad', 'q_rps', 'aZ_mps2'};
    stateNames = {'q_rps', 'vZ_B_mps'};
    
    sysSP = ModelReduce(sysModel, inNames, outNames, stateNames);
    sys.sysSP = sysSP;
    
    
    %% Lateral-Directional Linear Model
    inNames = {'ailL_rad', 'ailR_rad', 'rud_rad'};
    outNames = {'beta_rad', 'p_rps', 'r_rps', 'phi_rad', 'psi_rad'};
    stateNames = {'vY_B_mps', 'p_rps', 'r_rps', 'quatState1', 'quatState2', 'quatState3', 'quatState4'};
    
    sysLat = ModelReduce(sysModel, inNames, outNames, stateNames);
    sys.sysLat = sysLat;
    
end

%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end

end


%% Model Reduction via Named I/O
function outSys = ModelReduce(inSys, inNames, outNames, stateNames)
for indx = 1:length(inNames)
    indxIn(indx) = find(strcmp(inSys.InputName, inNames{indx}));
end

for indx = 1:length(outNames)
    indxOut(indx) = find(strcmp(inSys.OutputName, outNames{indx}));
end

for indx = 1:length(stateNames)
    indxState(indx) = find(strcmp(inSys.StateName, stateNames{indx}));
end

stateNum = 1:length(inSys.StateName);

% Reduce Model, Truncation
outSys = modred(inSys(indxOut, indxIn), setdiff(stateNum, indxState), 'Truncate');

end