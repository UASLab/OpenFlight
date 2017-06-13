function [Trim] = TrimSim(simModel, Trim, Sim, AC, fileSave, verbose)
%[Trim] = TrimSim(simModel, Trim, AC, fileSave, verbose)
%
% Trims the UAV simulation to target conditions.
% This function can be called from any of the three sim directories.
% However, this function will use your workspace variables. Requires 
% Simulink Control Design.
%
% Set the trim target as shown below.
%
% Inputs:
%     Trim         - Initial aircraft state, with a structure called
%     "target", which has some subset of the following fields:
%     V_s          - True airspeed (m/s)
%     alpha        - Angle of attack (rad)
%     beta         - Sideslip (rad), defaults to zero
%     gamma        - Flight path angle (rad), defaults to zero
%     phi          - roll angle (rad)
%     theta        - pitch angle (rad)
%     psi          - Heading angle (0-360)
%     phidot       - d/dt(phi) (rad/sec), defaults to zero
%     thetadot     - d/dt(theta) (rad/sec), defaults to zero
%     psidot       - d/dt(psi) (rad/sec), defaults to zero
%     p            - Angular velocity (rad/sec)
%     q            - Angular velocity (rad/sec)
%     r            - Angular velocity (rad/sec)
%     h            - Altitude above ground level (AGL) (m)
%     elevator     - elevator control input, rad. 
%     aileron      - combined aileron control input, rad. (da_r - da_l)/2
%     l_aileron    - left aileron control input, rad
%     r_aileron    - right aileron control input, rad
%     rudder       - rudder control input, rad. 
%     throttle     - throttle control input, nd. 
%     flap         - flap control input, rad. Defaults to fixed at zero.
%
%     AC       - Aircraft configuration structure, from UAV_config.m
%     fileSave - File to save the trim data
%     verbose  - boolean flag to suppress output; default "true"
%
% Outputs:
%   Trim  - values of state and control surfaces at trim.
%
% Unspecified variables are free, or defaulted to the values shown above.
% To force a defaulted variable to be free define it with an empty matrix.
% For example, by default beta=0  but "target.beta=[];" will allow beta
% to be free in searching for a trim condition.
%
% Examples:
% Trim.target = struct('V_s',17,'gamma',0); % straight and level
% Trim.target = struct('V_s',17,'gamma',5/180*pi); % level climb
% Trim.target = struct('V_s',17,'gamma',0,...
%                     'psidot',20/180*pi); % level turn
% Trim.target = struct('V_s',17,'gamma',5/180*pi,...
%                     'psidot',20/180*pi); % climbing turn
% Trim.target = struct('V_s',17,'gamma',0,...
%                      'beta',5/180*pi); % level steady heading sideslip
%
% Based in part on the trimgtm.m script by David Cox, NASA LaRC 
% (David.E.Cox@.nasa.gov)
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%

if nargin < 5, verbose = [];
    if nargin < 4, fileSave = []; end
end

if isempty(verbose), verbose = 1; end


%% Pull out target structure
target = Trim.target;

%% Invalid target checking. This section can be expanded greatly.
if isfield(target,'alpha') && isfield(target,'theta') && isfield(target,'gamma')
    error('Lacking free variable, cannot specify target in alpha, theta and gamma');
end
if isfield(target,'alpha') && isfield(target,'V_s') && isfield(target,'gamma')
    error('Lacking free variable, cannot specify target in alpha, V_s and gamma');
end
if isfield(target,'aileron') && isfield(target,'l_aileron') || isfield(target,'aileron') && isfield(target,'r_aileron')
    error('Cannot specify a target for l/r_aileron AND combined aileron input');
end

%% define names of control surfaces and set defaults for control surfaces 
% that are not used normally in trimming (flaps for UltraStick, flutter 
% surpression flaps for miniMUTT)
switch lower(Sim.type)
    case {'ultrastick120', 'ultrastick25e'}
        InputNames = {'elevator', 'rudder', 'aileron', 'l_flap', 'r_flap'};
        if ~isfield(target,'l_flap'), target.l_flap=0; end
        if ~isfield(target,'r_flap'), target.r_flap=0; end
    case 'minimutt'
        InputNames = {'elevator', 'aileron', 'L1','L4','R1','R4'};
        if ~isfield(target,'L1'), target.L1=0; end
        if ~isfield(target,'L4'), target.L4=0; end
        if ~isfield(target,'R1'), target.R1=0; end
        if ~isfield(target,'R4'), target.R4=0; end
end


%% Error checking for unknown fields
knownfields = {'V_s', 'alpha', 'beta', 'gamma', 'phi', 'theta', 'psi',...
    'phidot', 'thetadot', 'psidot', 'p', 'q', 'r', 'h'};
knownfields = [knownfields, InputNames];

saywhat = setdiff(fieldnames(target),knownfields);
if ~isempty(saywhat)
    for i = 1:length(saywhat), fprintf(1, 'Unknown field in target: %s\n', saywhat{i});end
    error('Unknown fields');
end

%% Set defaults if not specified
if ~isfield(target, 'beta'), target.beta=0; end
if ~isfield(target, 'gamma'), target.gamma=0; end

% If either of the individual ailerons are set, set combined aileron input
% to zero. Otherwise, use combined aileron input
% if isfield(target,'l_aileron') || isfield(target,'r_aileron')
%     target.aileron=0; 
% else
%     target.l_aileron=0;
%     target.r_aileron=0;
% end

%% Remove fields assocated with empty targets (overrides defaults);
fn = fieldnames(target);
for i = 1:length(fn)
    if isempty(target.(fn{i}))
        target = rmfield(target,fn{i});
    end
end

%% Load model into memory
isLoaded = bdIsLoaded(simModel); % check to see if model is loaded or open
if ~isLoaded
    load_system(simModel) % load model into system memory without opening diagram
end

%% SET OPERATING POINT SPECIFICATIONS
% Note: beware of overconstraining the states of the model. "findop" often
% fails (even if at a trim point!!) if the model is overconstrained.
%
op_spec = operspec(simModel);


%% STATE SPECIFICATIONS
% phi, theta, psi -- Euler angles
% op_spec.States(1).StateName   = '[phi theta psi]';
op_spec.States(1).Known       = [0 ; 0; 1];
op_spec.States(1).x           = Trim.AttitudeIni;
op_spec.States(1).steadystate = [1; 1; 1];

% p, q, r -- Angular rates
% op_spec.States(2).StateName   = '[p q r]';
op_spec.States(2).Known       = [0; 0; 0];
op_spec.States(2).x           = Trim.RatesIni;
op_spec.States(2).steadystate = [1; 1; 1];

% u, v, w -- Body velocities
% op_spec.States(3).StateName   = '[u v w]';
op_spec.States(3).Known       = [0; 0; 0];
op_spec.States(3).x           = Trim.VelocitiesIni;
op_spec.States(3).steadystate = [1; 1; 1];
op_spec.States(3).min         = [0 -inf -inf];

% Xe, Ye, Ze -- Inertial position
%op_spec.States(4).StateName   = '[Xe Ye Ze]';
op_spec.States(4).Known       = [0; 0; 1];
op_spec.States(4).x           = Trim.InertialIni;
op_spec.States(4).steadystate = [0; 0; 0];
op_spec.States(4).max         = [inf inf 0];

switch lower(Sim.type)
    case {'ultrastick120', 'ultrastick25e'}
        % omega  -- Engine Speed
        %op_spec.States(5).StateName = 'omega_engine';
        op_spec.States(5).Known       = 0;
        op_spec.States(5).x           = Trim.EngineSpeedIni;
        op_spec.States(5).steadystate = 1;
        
    case 'minimutt'
        % structural modes
        % displacements
        op_spec.States(8).Known = zeros(size(Trim.FlexIni));
        op_spec.States(8).x = Trim.FlexIni;
        op_spec.States(8).steadystate = ones(size(Trim.FlexIni));
        %velocities
        op_spec.States(9).Known = zeros(size(Trim.FlexRatesIni));
        op_spec.States(9).x = Trim.FlexRatesIni;
        op_spec.States(9).steadystate = ones(size(Trim.FlexRatesIni));

        % Lag states of the unsteady aero
        op_spec.States(7).Known = zeros(size(Trim.LagStatesIni));
        op_spec.States(7).x = Trim.LagStatesIni;
        op_spec.States(7).steadystate = ones(size(Trim.LagStatesIni));
        
        % DT1 filter states to obtain control surface velocities
        op_spec.States(6).Known = zeros(size(Trim.DT1CtrlSurfIni));
        op_spec.States(6).x = Trim.DT1CtrlSurfIni;
        op_spec.States(6).steadystate = ones(size(Trim.DT1CtrlSurfIni));
        
        % DT1 filter states to obtain accelerations
        op_spec.States(5).Known = zeros(size(Trim.DT1AccAllModes));
        op_spec.States(5).x = Trim.DT1AccAllModes;
        op_spec.States(5).steadystate = ones(size(Trim.DT1AccAllModes));

end



%% OUTPUT SPECIFICATIONS
% accelerations not included at this point
if isfield(target, 'V_s')
    op_spec.Outputs(1).Known = 1;
    op_spec.Outputs(1).y = target.V_s;
end

if isfield(target,'beta')
    op_spec.Outputs(2).Known = 1;
    op_spec.Outputs(2).y = target.beta;
    if target.beta ~=0
        op_spec.States(1).Known(1) = 0; % Free phi state
    end
end

if isfield(target,'alpha')
    op_spec.Outputs(3).Known = 1;
    op_spec.Outputs(3).y = target.alpha;
end

if isfield(target,'h')
    op_spec.Outputs(4).Known = 1;
    op_spec.Outputs(4).y = target.h;
    op_spec.States(4).Known(3) = 0; %Free Ze to prevent overconstraining
end

if isfield(target,'phi')
    op_spec.Outputs(5).Known = 1;
    op_spec.Outputs(5).y = target.phi;
    op_spec.States(1).Known(1) = 0; % Free phi state to prevent overconstraining
    op_spec.States(1).SteadyState(3) = 0; % Free psidot to prevent conflicting constraints
end

if isfield(target,'theta')
    op_spec.Outputs(6).Known = 1;
    op_spec.Outputs(6).y = target.theta;
end

if isfield(target,'psi')
    op_spec.Outputs(7).Known = 1;
    op_spec.Outputs(7).y = target.psi;
end

if isfield(target,'p')
    op_spec.Outputs(8).Known = 1;
    op_spec.Outputs(8).y = target.p;
    op_spec.States(1).SteadyState(1) = 0; % Free phidot to prevent conflicting constraints
end

if isfield(target,'q')
    op_spec.Outputs(9).Known = 1;
    op_spec.Outputs(9).y = target.q;
    op_spec.States(1).SteadyState(2) = 0; % Free thetadot to prevent conflicting constraints
end

if isfield(target,'r')
    op_spec.Outputs(10).Known = 1;
    op_spec.Outputs(10).y = target.r;
    op_spec.States(1).SteadyState(3) = 0; % Free psidot to prevent conflicting constraints
end

if isfield(target,'gamma')
    op_spec.Outputs(11).Known = 1;
    op_spec.Outputs(11).y = target.gamma;
end

if isfield(target,'phidot')||isfield(target,'thetadot')||isfield(target,'psidot')
    op_spec = addoutputspec(op_spec,'SimNL/Nonlinear UAV Model/6DoF EOM/Calculate DCM & Euler Angles/phidot thetadot psidot',1); % add output spec if eulerdot targets are used
    if isfield(target,'phidot')
        op_spec.Outputs(15).Known(1) = 1;
        op_spec.Outputs(15).y(1) = target.phidot;
        if target.phidot ~= 0
            op_spec.States(1).steadystate(1) = 0; % Free phidot
        end
    end
    if isfield(target,'thetadot')
        op_spec.Outputs(15).Known(2) = 1;
        op_spec.Outputs(15).y(2) = target.thetadot;
        if target.thetadot ~= 0
            op_spec.States(1).steadystate(2) = 0; % Free thetadot
        end
    end
    if isfield(target,'psidot')
        op_spec.Outputs(15).Known(3) = 1;
        op_spec.Outputs(15).y(3) = target.psidot;
        if target.psidot ~= 0
            op_spec.States(1).steadystate(3) = 0; % Free psidot
        end
    end
end

%% INPUT SPECIFICATIONS
% Loop over all of the root level inport blocks and find the control
% surface inputs by name. Assign values, limits, and "known" status. Warn
% on unrecognized inport block names.
%

% set wind input to specified known value
%op_spec.inputs(3).Known = [1; 1; 1];
%op_spec.inputs(3).u = Trim.Inputs.Wind;

% if a target motor, set as known and use target value
if isfield(target,'motor')
    op_spec.inputs(1).Known = 1;
    op_spec.inputs(1).u = target.motor;
else
    % else set to unkown and use intial value from setup.m
    op_spec.inputs(1).Known = 0;
    op_spec.inputs(1).u = Trim.Inputs.Motor;
end


%default is not known and intial guess as specified in setup.m
op_spec.inputs(2).Known = zeros(length(InputNames),1);
op_spec.inputs(2).u = Trim.Inputs.Actuator;

%default actutator position limits
op_spec.inputs(2).max = 0.4363*ones(length(InputNames),1); % 25deg default
op_spec.inputs(2).min = -0.4363*ones(length(InputNames),1); % -25deg default

for ii=1:length(InputNames)
    if isfield(target,InputNames{ii}) % if a target, set as known and use target value
        op_spec.inputs(2).Known(ii) = 1;
        op_spec.inputs(2).u(ii) = target.(InputNames{ii});
    end
    try
        op_spec.inputs(2).max(ii) = AC.Actuator.(InputNames{ii}).PosLim;
        op_spec.inputs(2).min(ii) = AC.Actuator.(InputNames{ii}).NegLim;
    catch
    end
end

%% FIND OPERATING POINT (TRIM)
opt1 = optimset('MaxFunEvals',1e+04,'Algorithm','interior-point');
opt = findopOptions('OptimizationOptions', opt1, 'DisplayReport', 'off');  
clear opt1
if verbose
    opt.OptimizationOptions.Display = 'iter'; 
    opt.DisplayReport = 'on';
end

[op_point, op_report] = findop(simModel, op_spec, opt);

%% SET NONLINEAR SIMULATION TO TRIM CONDITION
% Pull initial state for trim solution and initialize the nonlinear model
% to that state.
Trim.AttitudeIni    = op_point.States(1).x;
Trim.RatesIni       = op_point.States(2).x;
Trim.VelocitiesIni  = op_point.States(3).x;
Trim.InertialIni    = op_point.States(4).x;
Trim.AccelsIni = [op_report.Outputs(12).y;...
                            op_report.Outputs(13).y;...
                            op_report.Outputs(14).y];
Trim.WindAxesIni = [op_report.Outputs(1).y;...
                              op_report.Outputs(3).y;...
                              op_report.Outputs(2).y];                        

switch lower(Sim.type)
    case {'ultrastick120', 'ultrastick25e'}
        Trim.EngineSpeedIni = op_point.States(5).x;
    case 'minimutt'
        Trim.FlexIni = op_point.States(8).x;
        Trim.FlexRatesIni = op_point.States(9).x;
        Trim.LagStatesIni = op_point.States(7).x;
        Trim.DT1CtrlSurfIni = op_point.States(6).x;
        Trim.DT1AccAllModes = op_point.States(5).x;
end                          
                          

% Pull throttle value for trim solution
Trim.Inputs.Motor = op_point.Inputs(1).u;

% Pull control surface values for trim solution
Trim.Inputs.Actuator = op_point.Inputs(2).u;

% Handle combined aileron input option
% if isfield(target,'aileron')
%     if target.aileron ~= 0 % if aileron is targted to a non-zero condition, use that value
%         Trim.Inputs.l_aileron = -Trim.Inputs.aileron;
%         Trim.Inputs.r_aileron = Trim.Inputs.aileron;
%     end
% else
%     Trim.Inputs.l_aileron = -Trim.Inputs.aileron;
%     Trim.Inputs.r_aileron = Trim.Inputs.aileron; 
% end

% return as-trimmed target structure
Trim.target = target;

%% SAVE TO .MAT FILE
Trim.op_point  = op_point;
Trim.op_report = op_report;
Trim.op_spec   = op_spec;

if ~isempty(fileSave)
    % Save variables to MAT file
    save(fileSave, 'Trim');
    
    % Output a message to the screen
    fprintf('\n Trim conditions saved as:\t %s\n', fileSave);
end

%% Cleanup
if ~isLoaded
    bdclose(simModel) % clear model from system memory if we had to load it
end