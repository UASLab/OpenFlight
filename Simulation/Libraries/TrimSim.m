function [Sim] = TrimSim(simModel, Sim, verbose)
%
% Trims the UAV simulation to specified conditions.
%
% Inputs:
%   simModel - Simulink model
%   Sim
%   verbose  - boolean flag to suppress output; default "true"
%
% Outputs:
%   Sim

%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.
%

if nargin < 3, verbose = []; end

if isempty(verbose), verbose = 0; end


%% Pull out target structures
trimIn = Sim.Trim.In;
trimOut = Sim.Trim.Out;
trimState = Sim.Trim.State;
trimInit = Sim.Trim.Init;


%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end


%% SET OPERATING POINT SPECIFICATIONS
opSpec = operspec(simModel);


%% STATE SPECIFICATIONS
stateList = get(opSpec.States, 'StateName');

% Field names of the Target variables
trimStateNames = fieldnames(trimState);

numTrimState = length(trimStateNames);
for indxState = 1:numTrimState
    % Current target signal name
    trimStateName = trimStateNames{indxState};
    
    % Corresponding index of the Output Signal
    indxStateFind = find(strcmp(stateList, trimStateName));
    
    if ~isempty(indxStateFind) % Set State Conditions
        if isfield(trimState.(trimStateName), 'Known')
            opSpec.States(indxStateFind).Known = trimState.(trimStateName).Known;
        end
        if isfield(trimState.(trimStateName), 'steadystate')
            opSpec.States(indxStateFind).steadystate = trimState.(trimStateName).steadystate;
        end
        if isfield(trimState.(trimStateName), 'x')
            opSpec.States(indxStateFind).x = trimState.(trimStateName).x;
        end
        if isfield(trimState.(trimStateName), 'Min')
            opSpec.States(indxStateFind).Min = trimState.(trimStateName).Min;
        end
        if isfield(trimState.(trimStateName), 'Max')
            opSpec.States(indxStateFind).Max = trimState.(trimStateName).Max;
        end
        
    else % Target not found in the States
        error(['Target not defined: State = ' trimStateName]);
    end
end


%% OUTPUT SPECIFICATIONS
% Create a cell array of Output Names from the opSpec
outList = strrep(get(opSpec.Outputs, 'Block'), [simModel '/'], '');

% Field names of the Target variables
trimOutNames = fieldnames(trimOut);

numTrimOut = length(trimOutNames);
for indxOut = 1:numTrimOut
    % Current target signal name
    trimOutName = trimOutNames{indxOut};
    
    % Corresponding index of the Output Signal
    indxOutFind = find(strcmp(outList, trimOutName));
    
    if ~isempty(indxOutFind) % Set Output Conditions
        if isfield(trimOut.(trimOutName), 'Known')
            opSpec.Outputs(indxOutFind).Known = trimOut.(trimOutName).Known;
        end
        if isfield(trimOut.(trimOutName), 'y')
            opSpec.Outputs(indxOutFind).y = trimOut.(trimOutName).y;
        end
        if isfield(trimOut.(trimOutName), 'Min')
            opSpec.Outputs(indxOutFind).Min = trimOut.(trimOutName).Min;
        end
        if isfield(trimOut.(trimOutName), 'Max')
            opSpec.Outputs(indxOutFind).Max = trimOut.(trimOutName).Max;
        end
        
    else % Target not found in the Output signals
        error(['Target not defined: Output = ' trimOutName]);
    end
end


%% INPUT SPECIFICATIONS
% Create a cell array of Output Names from the opSpec
inList = strrep(get(opSpec.Inputs, 'Block'), [simModel '/'], '');

% Field names of the Target variables
targInNames = fieldnames(trimIn);

numTargIn = length(targInNames);
for indxIn = 1:numTargIn
    % Current target signal name
    trimInName = targInNames{indxIn};
    
    % Corresponding index of the Input Signal
    indxInFind = find(strcmp(inList, trimInName));
    
    if ~isempty(indxInFind) % Set Input Conditions
        if isfield(trimIn.(trimInName), 'Known')
            opSpec.Inputs(indxInFind).Known = trimIn.(trimInName).Known;
        end
        if isfield(trimIn.(trimInName), 'u')
            opSpec.Inputs(indxInFind).u = trimIn.(trimInName).u;
        end
        if isfield(trimIn.(trimInName), 'Min')
            opSpec.Inputs(indxInFind).Min = trimIn.(trimInName).Min;
        end
        if isfield(trimIn.(trimInName), 'Max')
            opSpec.Inputs(indxInFind).Max = trimIn.(trimInName).Max;
        end
        
    else % Target not found in the Input signals
        error(['Target not defined: Input = ' trimInName]);
    end
end


%% FIND OPERATING POINT (TRIM)
% set_param(simModel, 'AlgebraicLoopSolver', 'LineSearch');
% set_param(simModel, 'AlgebraicLoopSolver', 'TrustRegion');

opt = findopOptions('OptimizerType', 'graddescent_elim', 'DisplayReport', 'off');  

if verbose
    opt.OptimizationOptions.Display = 'iter'; 
    opt.DisplayReport = 'on';
end

opt.OptimizationOptions.Algorithm = 'interior-point';
opt.OptimizationOptions.MaxFunEvals = 1e4;
opt.OptimizationOptions.MaxIter = 1e4;
opt.OptimizationOptions.Jacobian = 'on';
opt.OptimizationOptions.ScaleProblem = 'true';

[opPoint, opReport] = findop(simModel, opSpec, opt);

%
Sim.Trim.opSpec   = opSpec;
Sim.Trim.opPoint  = opPoint;
Sim.Trim.opReport = opReport;

%% Generate Initial Conditions
stateList = get(opPoint.States, 'StateName');

numSimState = length(stateList);
for indxState = 1:numSimState
    % Current target signal name
    simStateName = stateList{indxState};
    
    % Copy States to Init Structure
    trimInit.(simStateName) = opPoint.States(indxState).x;
end

Sim.Trim.Init = trimInit;

%% Generate Initial Conditions
inList = strrep(get(opPoint.Inputs, 'Block'), [simModel '/'], '');

numSimIn = length(inList);
for indxIn = 1:numSimIn
    % Current target signal name
    simInName = inList{indxIn};
    
    % Copy States to Init Structure
    trimInit.(simInName) = opPoint.Inputs(indxIn).u;
end

Sim.Trim.Init = trimInit;


%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end

