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
% Copyright 2017 Regents of the University of Minnesota.
% All rights reserved.
%


%% Set default values and optional arguments
% Constants
d2r = pi/180;


%% Configure Aircraft
if 0
    Sim.model = 'UltraStick25e';
    
    % Sim.MassP.type = 'AVL'; % Use the reference model defined by the AVL model
    Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Thor';
    
    % Sim.Aero.type = 'AVL'; % Use the reference model defined by the AVL model
    Sim.Aero.type = 'Flight'; % Use aero Model as derived from flight data, use with Thor mass properties
    
    % Define Aircraft Specific Parameters
    AC = [];
    [Sim, AC] = Config_UltraStick25e(Sim, AC);
    
    % Aircraft Config
    % Core Sub-System Variant Selections
    Sim.MassP.VarSel = 1; % Select Mass Property Model Variant
    Sim.Aero.VarSel = 1; % Select Aero Model Variant
    Sim.Prop.VarSel = 1; % Select Prop Model Variant
    
    % Configurable Subsystems Selections
    Sim.SensSim = 'Sensors_UltraStick25e';
    Sim.Sens.BlockChoiceList = {[Sim.SensSim '/Sensor_IMU'], 'IMU_Err'; ...
        [Sim.SensSim '/Sensor_GPS'], 'GPS_Err'; ...
        [Sim.SensSim '/Sensor_Pitot'], 'Pitot_Err'};
    
    Sim.EffSim = 'SubSys_UltraStick25e';
    Sim.Eff.BlockChoiceList = [];
    for indxSurf = 1:length(Sim.Surf.surfList)
        Sim.Eff.BlockChoiceList{indxSurf, 1} = [Sim.EffSim '/' Sim.Surf.surfList{indxSurf}];
        Sim.Eff.BlockChoiceList{indxSurf, 2} = 'act_NL1';
    end
    
end

if 1
    Sim.model = 'UltraStick120';
    
    % Sim.MassP.type = 'OpenVSP'; % Use the reference model defined by the OpenVSP model
    % Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Faser';
    Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Mjolnir';
    
    Sim.Aero.type = 'OpenVSP'; % Use the reference model defined by the AVL model
    % Sim.Aero.type = 'Faser'; % Use aero Model as derived from Faser Wind Tunnel data
    
    % Define Aircraft Specific Parameters
    AC = [];
    [Sim, AC] = Config_UltraStick120(Sim, AC);
    
    
    % Aircraft Config
    % Core Sub-System Variant Selections
    Sim.MassP.VarSel = 1; % Select Mass Property Model Variant
    Sim.Aero.VarSel = 2; % Select Aero Model Variant
    Sim.Prop.VarSel = 1; % Select Prop Model Variant
    
    % Configurable Subsystems Selections
    Sim.SensSim = 'Sensors_UltraStick120';
    Sim.Sens.BlockChoiceList = {[Sim.SensSim '/Sensor_IMU'], 'IMU_Err'; ...
        [Sim.SensSim '/Sensor_GPS'], 'GPS_Err'; ...
        [Sim.SensSim '/Sensor_Pitot'], 'Pitot_Err'};
    
    Sim.EffSim = 'SubSys_UltraStick120';
    Sim.Eff.BlockChoiceList = [];
    for indxSurf = 1:length(Sim.Surf.surfList)
        Sim.Eff.BlockChoiceList{indxSurf, 1} = [Sim.EffSim '/' Sim.Surf.surfList{indxSurf}];
        Sim.Eff.BlockChoiceList{indxSurf, 2} = 'act_NL1';
    end
    
end


%% Define the Core Simulation Parameters, Variants, and Buses
% Simulation sample time
Sim.timeSample_s = 0.02; % sec

% Define Environment Parameters
Env = [];

% Configure the Simulation (Apply Variants and Define Buses)
Sim.Atmos.VarSel = 1; % Atmospheric Model Selection
Sim.Terr.VarSel = 1; % Terrain Model Selection
Sim.Grav.VarSel = 1; % Gravity Model Selection
Sim.Mag.VarSel = 1; % Magnetic Model Selection

Sim.Eom.VarSel = 1; % Equation of Motion Selection

[Sim, Env] = Config_Core(Sim, Env);


%% Set aircraft trim conditions
% Set Initial Position
Env.Terr.altGrd_m = 287.0; % Ground Elevation at Jensen Field
Sim.Trim.Init.altAgl_m = 100.0; % Initial Altitude in AGL
Sim.Trim.Init.rInit_BE_D_ddm = [44.72701; -93.077205; Env.Terr.altGrd_m + Sim.Trim.Init.altAgl_m]; % Initial Position of Aircraft [Lat; Long; Alt]

% Define aircraft specific parameters
switch lower(Sim.model)
    case 'ultrastick120'
        % Initial Velocity of Aircraft
        Sim.Trim.Out.vTrue_mps = struct('Known', 1, 'y', 23);
        
        % Throttle initial values
        Sim.Trim.MotorNames = {'throttle_nd'};
        Sim.Trim.In.Motor = struct('Known', 0, 'u', 0.6, 'Min', 0, 'Max', 1.0);
        
        % Control surface initial values
        Sim.Trim.SurfNames = {'elev_rad', 'rud_rad', 'ail_rad', 'flapL_rad', 'flapR_rad'}; % elev, rud, (ailL + ailR), flapL, flapR
        Sim.Trim.In.Surf = struct('Known', [0; 0; 0; 1; 1], 'u', [0; 0; 0; 0; 0]*d2r, 'Min', [-30; -30; -30; -30; -30]*d2r, 'Max', [30; 30; 30; 30; 30]*d2r);
        
        % Initial Motor Speed [rad/s]
        Sim.Trim.Init.omegaState_rps = 800;
        
    case 'ultrastick25e'
        % Initial Velocity of Aircraft
        Sim.Trim.Out.vTrue_mps = struct('Known', 1, 'y', 17);
        
        % Throttle initial values
        Sim.Trim.MotorNames = {'throttle_nd'};
        Sim.Trim.In.Motor = struct('Known', 0, 'u', 0.6, 'Min', 0.0, 'Max', 1.0);
        
        % Control surface initial values
        Sim.Trim.SurfNames = {'elev_rad', 'rud_rad', 'ail_rad', 'flapL_rad', 'flapR_rad'}; % elev, rud, (ailL + ailR), flapL, flapR
        Sim.Trim.In.Surf = struct('Known', [0; 0; 0; 1; 1], 'u', [0; 0; 0; 0; 0]*d2r, 'Min', [-30; -30; -30; -30; -30]*d2r, 'Max', [30; 30; 30; 30; 30]*d2r);
        
        % Initial Motor Speed [rad/s]
        Sim.Trim.Init.omegaState_rps = 800;
end


% Trim aircraft to a specific flight condition
% Define the Output specifications - Steady-Level
% Sim.Trim.Out.vTrue_mps = struct('Known', 1, 'y', 17);
Sim.Trim.Out.alpha_rad = struct('Known', 0, 'y', 4 * d2r, 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Out.beta_rad = struct('Known', 1, 'y', 0 * d2r, 'Min', -10 * d2r, 'Max', 10 * d2r);

Sim.Trim.Out.phi_rad = struct('Known', 1, 'y', 0 * d2r, 'Min', -90 * d2r, 'Max', 90 * d2r);
Sim.Trim.Out.theta_rad = struct('Known', 0, 'y', 4 * d2r, 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Out.psi_rad = struct('Known', 1, 'y', 155 * d2r, 'Min', (155 - 15) * d2r, 'Max', (155 + 15) * d2r);

Sim.Trim.Out.p_rps = struct('Known', 0, 'y', 0 * d2r, 'Min', -1 * d2r, 'Max', 1 * d2r);
Sim.Trim.Out.q_rps = Sim.Trim.Out.p_rps;
Sim.Trim.Out.r_rps = Sim.Trim.Out.p_rps;

Sim.Trim.Out.altAgl_m = struct('Known', 1, 'y', Sim.Trim.Init.altAgl_m);
Sim.Trim.Out.gamma_rad = struct('Known', 1, 'y', 0 * d2r, 'Min', -10 * d2r, 'Max', 10 * d2r);

% Define State conditions, generally these are initial guesses
Sim.Trim.State.wState_BI_B_rps = struct('Known', [0; 0; 0], 'steadystate', [1; 1; 1], 'x', [0; 0; 0]);
Sim.Trim.State.quatState = struct('Known', [0; 0; 0; 0], 'steadystate', [1; 1; 1; 1], 'x', [0.01; 0; 0; 0.01]);
% Sim.Trim.State.sState_BL_rad = struct('Known', [0; 0; 0], 'steadystate', [1; 1; 1], 'x', [Sim.Trim.Out.phi_rad.y; Sim.Trim.Out.theta_rad.y; Sim.Trim.Out.psi_rad.y]);
Sim.Trim.State.vState_BI_B_mps = struct('Known', [0; 0; 0], 'steadystate', [1; 1; 1], 'x', [Sim.Trim.Out.vTrue_mps.y; 0; 0]);
Sim.Trim.State.rState_BI_L_m = struct('Known', [1; 1; 1], 'steadystate', [0; 0; 1], 'x', [0; 0; 0]);

Sim.Trim.State.omegaState_rps = struct('Known', 0, 'steadystate', 1, 'x', Sim.Trim.Init.omegaState_rps);

% Transfer the Initial State Guesses to the Init Structure, these will be overwritten by TrimSim
% Initialize Equations of Motion
Sim.Trim.Init.wState_BI_B_rps = Sim.Trim.State.wState_BI_B_rps.x;
Sim.Trim.Init.quatState = Sim.Trim.State.quatState.x;
% Sim.Trim.Init.sState_BL_rad = Sim.Trim.State.sState_BL_rad.x;
Sim.Trim.Init.vState_BI_B_mps = Sim.Trim.State.vState_BI_B_mps.x;
Sim.Trim.Init.rState_BI_L_m = Sim.Trim.State.rState_BI_L_m.x;

% Initialize Motors
Sim.Trim.Init.omegaState_rps = Sim.Trim.State.omegaState_rps.x;

% Initialize Surfaces
Sim.Trim.Init.Surf = 0 * Sim.Trim.In.Surf.u;
% Sim.Trim.Init.Surf = Sim.Trim.In.Surf.u;
Sim.Trim.Init.Motor = 0 * Sim.Trim.In.Motor.u;
% Sim.Trim.Init.Motor = Sim.Trim.In.Motor.u;


%% Find the trim solution
simModel = 'SimNL';
verbose = 1;

[Sim] = TrimSim(simModel, Sim, verbose);

% Initialize Inputs
Sim.Trim.Init.Surf = Sim.Trim.In.Surf;
Sim.Trim.Init.Motor = Sim.Trim.In.Motor;

%%
if 0
    % Save variables to MAT file
    save(fileSave, 'Sim', 'AC');
    
    % Output a message to the screen
    fprintf('\n Simulation Configuration saved as:\t %s\n', fileSave);
end

%% Linearize about the operating point
[sysModel, sys] = LinearizeSim(simModel, Sim);
