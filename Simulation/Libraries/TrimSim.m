function [Trim] = TrimSim(simModel, Trim, verbose)
%
% Trims the UAV simulation to specified conditions.
%
% Inputs:
%   simModel - Simulink model
%   Trim
%   verbose  - boolean flag to suppress output; default "true"
%
% Outputs:
%   Trim
%
% Notes:
% The Sim structure contains I/O and State conditions in a similar style as opspec() expects.
% Unrecognized states are set to be "free", ie. the steadystate condition is set to 0.

%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.
%

if nargin < 3, verbose = []; end

if isempty(verbose), verbose = 0; end


%% Pull out target structures
trimTargIn = Trim.Targ.In;
trimTargOut = Trim.Targ.Out;
trimTargState = Trim.Targ.State;
trimInit = Trim.Init;


%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end


%% SET OPERATING POINT SPECIFICATIONS
opSpec = operspec(simModel);


%% STATE SPECIFICATIONS
% List of State names from the simulation
specStateNameList = get(opSpec.States, 'StateName');

% Set steadystate to zero by default
% for indxSpecState = 1:length(specStateNameList)
%     opSpec.States(indxSpecState).SteadyState = 0 * opSpec.States(indxSpecState).SteadyState;
% end

% Field names of the Target variables
targStateNameList = fieldnames(trimTargState);

% Loop over the defined Target States
numTargState = length(targStateNameList);
for indxSpecState = 1:numTargState
    % Current target signal name
    trimStateName = targStateNameList{indxSpecState};
    
    % Corresponding index of the opSpec
    indxStateFind = find(strcmp(specStateNameList, trimStateName));
    
    if ~isempty(indxStateFind) % Set State Conditions
        if isfield(trimTargState.(trimStateName), 'Known')
            opSpec.States(indxStateFind).Known = trimTargState.(trimStateName).Known;
        end
        if isfield(trimTargState.(trimStateName), 'steadystate')
            opSpec.States(indxStateFind).steadystate = trimTargState.(trimStateName).steadystate;
        end
        if isfield(trimTargState.(trimStateName), 'x')
            opSpec.States(indxStateFind).x = trimTargState.(trimStateName).x;
        end
        if isfield(trimTargState.(trimStateName), 'Min')
            opSpec.States(indxStateFind).Min = trimTargState.(trimStateName).Min;
        end
        if isfield(trimTargState.(trimStateName), 'Max')
            opSpec.States(indxStateFind).Max = trimTargState.(trimStateName).Max;
        end
        
    else % Target not found in the States
        error(['Target not defined in Spec: State = ' trimStateName]);
    end
end


%% OUTPUT SPECIFICATIONS
% Create a cell array of Output Names from the opSpec
specOutNameList = strrep(get(opSpec.Outputs, 'Block'), [simModel '/'], '');

% Field names of the Target variables
targOutNameList = fieldnames(trimTargOut);

numTargOut = length(targOutNameList);
for indxTargOut = 1:numTargOut
    % Current target signal name
    targOutName = targOutNameList{indxTargOut};
    
    % Corresponding index of the Output Signal
    indxOutFind = find(strcmp(specOutNameList, targOutName));
    
    if ~isempty(indxOutFind) % Set Output Conditions
        if isfield(trimTargOut.(targOutName), 'Known')
            opSpec.Outputs(indxOutFind).Known = trimTargOut.(targOutName).Known;
        end
        if isfield(trimTargOut.(targOutName), 'y')
            opSpec.Outputs(indxOutFind).y = trimTargOut.(targOutName).y;
        end
        if isfield(trimTargOut.(targOutName), 'Min')
            opSpec.Outputs(indxOutFind).Min = trimTargOut.(targOutName).Min;
        end
        if isfield(trimTargOut.(targOutName), 'Max')
            opSpec.Outputs(indxOutFind).Max = trimTargOut.(targOutName).Max;
        end
        
    else % Target not found in the Output signals
        error(['Target not defined in Spec: Output = ' targOutName]);
    end
end


%% INPUT SPECIFICATIONS
% Create a cell array of Output Names from the opSpec
specInNameList = strrep(get(opSpec.Inputs, 'Block'), [simModel '/'], '');

% Field names of the Target variables
targInNameList = fieldnames(trimTargIn);

numTargIn = length(targInNameList);
for indxSpecIn = 1:numTargIn
    % Current target signal name
    targInName = targInNameList{indxSpecIn};
    
    % Corresponding index of the Input Signal
    indxInFind = find(strcmp(specInNameList, targInName));
    
    if ~isempty(indxInFind) % Set Input Conditions
        if isfield(trimTargIn.(targInName), 'Known')
            opSpec.Inputs(indxInFind).Known = trimTargIn.(targInName).Known;
        end
        if isfield(trimTargIn.(targInName), 'u')
            opSpec.Inputs(indxInFind).u = trimTargIn.(targInName).u;
        end
        if isfield(trimTargIn.(targInName), 'Min')
            opSpec.Inputs(indxInFind).Min = trimTargIn.(targInName).Min;
        end
        if isfield(trimTargIn.(targInName), 'Max')
            opSpec.Inputs(indxInFind).Max = trimTargIn.(targInName).Max;
        end
        
    else % Target not found in the Input signals
        error(['Target not defined in Spec: Input = ' targInName]);
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
% opt.OptimizationOptions.MaxFunEvals = 1e4;
% opt.OptimizationOptions.MaxIter = 1e4;
opt.OptimizationOptions.Jacobian = 'on';
opt.OptimizationOptions.ScaleProblem = 'true';

[opPoint, opReport] = findop(simModel, opSpec, opt);

%
Trim.opSpec   = opSpec;
Trim.opPoint  = opPoint;
Trim.opReport = opReport;

%% Generate Initial Conditions, from the Trimmed State Spec
specStateNameList = get(opPoint.States, 'StateName');

% Loop over the Trimmed State Specs
numSpecState = length(specStateNameList);
for indxSpecState = 1:numSpecState
    % Current target signal name
    specStateName = specStateNameList{indxSpecState};
    
    if ~isempty(specStateName)
        % Copy States to Init Structure
        trimInit.(specStateName) = opPoint.States(indxSpecState).x;
    end
end

Trim.Init = trimInit;

%% Generate Input Conditions, from the Trimmed Input Spec
specInNameList = strrep(get(opPoint.Inputs, 'Block'), [simModel '/'], '');

% Loop over the Trimmed Input Specs
numSpecIn = length(specInNameList);
for indxSpecIn = 1:numSpecIn
    % Current target signal name
    specInName = specInNameList{indxSpecIn};
    
    % Copy States to Input Structure
    trimIn.(specInName) = opPoint.Inputs(indxSpecIn).u;
end

Trim.In = trimIn;


%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end

