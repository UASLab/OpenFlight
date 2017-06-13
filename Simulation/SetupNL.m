%% setupNL.m
% Nonlinear Simulation setup
%
% This script will setup the nonlinear simulation and call
% trim and linearization routines. Select the desired aircraft here in this
% script, via the "UAV_config()" function call.
%
% Note: the model is not opened by default. This is not
% necessary to trim, linearize, and simulate via command line inputs.
% 
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%


%% Set default values and optional arguments
% Constants
d2r = pi/180;


%% Configure Simulation
Sim.model = 'UltraStick25e';
% Sim.MassP.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Thor';

% Sim.Aero.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.Aero.type = 'Flight'; % Use aero Model as derived from flight data, use with Thor mass properties

% Subsystem Variant Selections
Sim.Eom.VarSel = 1; % Equation of Motion Selection
Sim.MassP.VarSel = 1; % Select Mass Property Model Variant
Sim.Aero.VarSel = 1; % Select Aero Model Variant
Sim.Prop.VarSel = 1; % Select Propulsion Model Variant, Variant uses polynomial fitted data
Sim.Surf.VarSel = 1; % Select Effector Variant Type
Sim.Sens.IMU.VarSel = 1; % Select IMU Model Variants
Sim.Sens.GPS.VarSel = 1; % Select GPS Model Variants
Sim.Sens.AirData.VarSel = 1; % Select AirData Model Variants

% Aircraft Config
% Define Aircraft Specific Parameters
AC = [];
[Sim, AC] = ParamDef_UltraStick25e(Sim, AC);

% Define Environment Parameters
Env = [];
[~, Env] = ParamDef_Env(Sim, Env);


%% Define the Simulation Variants and apply selections
[Sim] = SimConfig(Sim);


%% Set aircraft initial conditions 
% Note: these are NOT the trim condition targets. If the trim fails to
% coverge, try using different initial conditions. Also note that the trim
% function will overwrite these initial conditions with the trimmed
% conditions.

% Set initial state values
Sim.Trim.InertialIni    = [0, 0, -100]'; % Initial Position in Inertial Frame [Xe Ye Ze], [m]
Sim.Trim.LLIni          = [44.7258357, -93.07501316]'; % Initial Latitude/Longitude of Aircraft [Lat Long], [deg]
Sim.Trim.AttitudeIni    = [0, 0.0217, 155*d2r]'; % Initial Euler orientation [roll, pitch, yaw], [rad], can't use 0 heading, causes large entry in C matrix for psi 
Sim.Trim.RatesIni       = [0, 0, 0]'; % Initial Body Frame rotation rates [p q r], [rad/s]

% Steady state wind values, m/s
Sim.Trim.Inputs.Wind     = [0, 0, 0]';

switch lower(AC.aircraft)
    case 'ultrastick120'
        % Control surface initial values, rad:
        % elevator, rudder, aileron, left flap, right flap
        Sim.Trim.Inputs.Effector = [0.091 0 0 0 0]';
        
        % number of the control surfaces (required to initialize the input
        % port dimension; dynamically relocating it returns an error)
        AC.nctrls = size(Sim.Trim.Inputs.Effector,1);
        
        % Throttle initial value, nd
        Sim.Trim.Inputs.Throttle = 0.559;
        
        % Initial velocity vector, m/s: [u v w]
        Sim.Trim.VelocitiesIni  = [23 0 0.369]';
        
        % Initial Engine Speed [rad/s]
        Sim.Trim.EngineSpeedIni = 827;
        
    case 'ultrastick25e'
        % Control surface initial values, rad:
        % elevator, rudder, aileron, left flap, right flap
        Sim.Trim.Inputs.Actuator = [0.091 0 0 0 0]';
        
        % number of the control surfaces (required to initialize the input
        % port dimension; dynamically relocating it returns an error)
        AC.nctrls = size(Sim.Trim.Inputs.Actuator,1);
        
        % Throttle initial value, nd
        Sim.Trim.Inputs.Motor = 0.559;
        
        % Initial velocity vector, m/s: [u v w]
        Sim.Trim.VelocitiesIni  = [17 0 0.369]';
        
        % Initial Engine Speed [rad/s]
        Sim.Trim.EngineSpeedIni = 827;
        
    case 'maewing1'
        % Control surface initial values, rad:
        % elevator, aileron, L1, L4, R1, R4
        Sim.Trim.Inputs.Effector = [-.09 0 0 0 0 0]';
        AC.nctrls = size(Sim.Trim.Inputs.Effector,1);
        
        % Throttle initial value, nd
        Sim.Trim.Inputs.Throttle = 0.559;
        
        % Initial velocity vector, m/s: [u v w]
        Sim.Trim.VelocitiesIni  = [23.6 0 0.369]';
        
        % Initial flexible state values:
        
        % Get dimensions of the structural and aerodynamics model
        nstates = size(AC.Aero.RFA.A0,1); %overall number of states
        nrigidstates = 6; %number of rigid body states
        nflexstates = nstates-nrigidstates; %number of flexible states
        nflaps = size(AC.Aero.RFA.A0,2)-nstates; %number of control surfaces
        nlagstates = size(AC.Aero.RFA.Alag,1); %number of lag states
        
        % Initial values of structural model
        % Displacements in modal coordinates
        Sim.Trim.FlexIni = zeros(nflexstates,1);
        % Velocities in modal coordinates
        Sim.Trim.FlexRatesIni = zeros(nflexstates,1);
        
        % Inital values of the unsteady aerodynamics
        % Lag states
        Sim.Trim.LagStatesIni = zeros(nlagstates,1);
        % DT1 filter states to obtain control surface velocities
        % (XXX not required if we have an actuator model, should we
        % consider that?)
        Sim.Trim.DT1CtrlSurfIni = zeros(nflaps,1);
        % DT1 filter states to obtain accelerations
        Sim.Trim.DT1AccAllModes = zeros(nstates+nflaps,1);
end


%% Trim aircraft to a specific flight condition
% Set the trim targets here. See trim_UAV for complete list of target
% variables. Sideslip angle (beta), flight path angle (gamma) and flap
% setting default to zero. If a fixed control input setting is desired,
% specify as a target.

% straight and level, (m/s, rad)
Sim.Trim.target = struct('V_s', Sim.Trim.VelocitiesIni(1), 'gamma', 0 * d2r, 'h', 100);
% Sim.Trim.target = struct('V_s', Sim.Trim.VelocitiesIni(1), 'gamma', 5 * d2r); % level climb, (m/s, rad)
% Sim.Trim.target = struct('V_s', Sim.Trim.VelocitiesIni(1), 'gamma', 0 * d2r, 'psidot', 20 * d2r); % level turn, (m/s, rad, rad/sec)
% Sim.Trim.target = struct('V_s', Sim.Trim.VelocitiesIni(1), 'gamma', 5 * d2r, 'psidot',20 * d2r); % climbing turn, (m/s, rad, rad/sec)
% Sim.Trim.target = struct('V_s', Sim.Trim.VelocitiesIni(1), 'gamma', 0 * d2r, 'beta', 5 * d2r); % level steady heading sideslip, (m/s, rad, rad)

% Find the trim solution
simModel = 'SimNL';
[Sim.Trim] = TrimSim(simModel, Sim.Trim, Sim, AC);


%% Linearize about the operating point
[longmod, spmod, latmod, linmodel] = LinearizeSim(simModel, Sim);

