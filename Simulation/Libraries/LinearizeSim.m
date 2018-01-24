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
linOpt.SampleTime = 0;
linOpt.UseBusSignalLabels = 'on';
linOpt.BlockReduction = 'off';
linOpt.StoreOffsets = true;

sysModel = linearize(simModel, Sim.Trim.opPoint, Sim.Trim.io, linOpt);


%% Fix I/O and State Names
% Fix Input Names
% Fix Input Names of the linear model
% inList = get(Sim.Trim.opSpec.inputs, 'Block');
inList = sysModel.InputName;

% Remove the input signal path
numIn = length(inList);
for indxIn = 1:numIn
    [~, inList{indxIn}] = fileparts(inList{indxIn});
end

% Write the signal names to the SS model
set(sysModel, 'InputName', inList);

% Fix Output Names of the linear model
% outList = get(Sim.Trim.opSpec.Outputs, 'Block');
outList = sysModel.OutputName;

% Remove the output signal path
numState = length(outList);
for indxOut = 1:numState
    [~, outList{indxOut}] = fileparts(outList{indxOut});
end

% Cleanup the strings
outList = regexprep(outList, '<|>', '');

% Write the signal names to the SS model
set(sysModel, 'OutputName', outList);

% Fix State Names
% Rotation Rates
indxW = strcmp(sysModel.StateName, 'wState_BI_B_rps');
if sum(indxW) == 3, sysModel.StateName(indxW) = {'p_rps', 'q_rps', 'r_rps'}; end

% Quaterions
indxQuat = strcmp(sysModel.StateName, 'quatState_BL_nd');
if sum(indxQuat) == 4, sysModel.StateName(indxQuat) = {'quatState1_nd', 'quatState2_nd', 'quatState3_nd', 'quatState4_nd'}; end

% Euler Angles
indxQuat = strcmp(sysModel.StateName, 'sState_BL_rad');
if sum(indxQuat) == 3, sysModel.StateName(indxQuat) = {'phi_rad', 'theta_rad', 'psi_rad'}; end

% Velocity
indxV = strcmp(sysModel.StateName, 'vState_BI_B_mps');
if sum(indxV) == 3, sysModel.StateName(indxV) = {'vX_mps', 'vY_mps', 'vZ_mps'}; end

% Position
indxR = strcmp(sysModel.StateName, 'rState_BI_L_m');
if sum(indxR) == 3, sysModel.StateName(indxR) = {'rN_m', 'rE_m', 'rD_m'}; end

%% Reduced Order Models
if nargout > 1
    %% Complete Model
    sys.sysModel = sysModel;
    
    
    %% Longitudinal Linear Model
    inNames = {'elev_rad', 'throttle_nd'};
    outNames = {'vTrue_mps', 'alpha_rad', 'q_rps', 'theta_rad', 'altAgl_m', 'aX_mps2', 'aZ_mps2'};
    stateNames = {'vX_mps', 'vZ_mps', 'q_rps', 'quatState1_nd', 'quatState2_nd', 'quatState3_nd', 'quatState4_nd', 'omegaState_rps', 'elevStateDef_rad', 'elevStateRate_rad'};
    
    sysLong = ModelReduce(sysModel, inNames, outNames, stateNames);
    sys.sysLong = sysLong;
    
    %% Short-Period Linear Model
    inNames = {'elev_rad'};
    outNames = {'alpha_rad', 'q_rps', 'aZ_mps2'};
    stateNames = {'q_rps', 'vZ_mps', 'elevStateDef_rad', 'elevStateRate_rad'};
    
    sysSP = ModelReduce(sysModel, inNames, outNames, stateNames);
    sys.sysSP = sysSP;
    
    
    %% Lateral-Directional Linear Model
    inNames = {'ailL_rad', 'ailR_rad', 'rud_rad'};
    outNames = {'beta_rad', 'p_rps', 'r_rps', 'phi_rad', 'psi_rad'};
    stateNames = {'vY_mps', 'p_rps', 'r_rps', 'quatState1_nd', 'quatState2_nd', 'quatState3_nd', 'quatState4_nd', 'ailLStateDef_rad', 'ailLStateRate_rad', 'ailRStateDef_rad', 'ailRStateRate_rad', 'rudStateDefl_rad', 'rudStateRate_rad'};
    
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
    indxInTemp = find(strcmp(inSys.InputName, inNames{indx}));
    if indxInTemp > 0, indxIn(indx) = indxInTemp; end
end

for indx = 1:length(outNames)
    indxOutTemp = find(strcmp(inSys.OutputName, outNames{indx}));
    if indxOutTemp > 0, indxOut(indx) = indxOutTemp; end
end

for indx = 1:length(stateNames)
    indxStateTemp = find(strcmp(inSys.StateName, stateNames{indx}));
    if indxStateTemp > 0, indxState(indx) = indxStateTemp; end
end

stateNum = 1:length(inSys.StateName);

% Reduce Model, Truncation
outSys = modred(inSys(indxOut, indxIn), setdiff(stateNum, indxState), 'Truncate');

end