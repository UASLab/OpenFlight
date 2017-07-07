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
Sim.model = 'UltraStick25e';

% Simulation sample time
Sim.timeSample_s = 0.02; % sec

% Sim.MassP.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Thor';

% Sim.Aero.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.Aero.type = 'Flight'; % Use aero Model as derived from flight data, use with Thor mass properties

% Aircraft Config
% Define Aircraft Specific Parameters
AC = [];
[Sim, AC] = Config_UltraStick25e(Sim, AC);

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

% get_param([Sim.SensSim '/Sensor_IMU'], 'MemberBlocks');
% get_param([Sim.SensSim '/Sensor_IMU'], 'BlockChoice');
% set_param([Sim.SensSim '/Sensor_IMU'], 'BlockChoice', 'IMU_Err');
% indxBlock = 1;
% set_param(Sim.Sens.BlockChoiceList{indxBlock,1}, 'BlockChoice', Sim.Sens.BlockChoiceList{indxBlock,2});



%% Define the Core Simulation Parameters, Variants, and Buses
% Define Environment Parameters
Env = [];

% Configure the Simulation (Apply Variants and Define Buses)
Sim.Atmos.VarSel = 1; % Atmospheric Model Selection
Sim.Terr.VarSel = 1; % Terrain Model Selection
Sim.Grav.VarSel = 1; % Gravity Model Selection
Sim.Mag.VarSel = 1; % Magnetic Model Selection

Sim.Eom.VarSel = 1; % Equation of Motion Selection

[Sim, Env] = Config_Core(Sim, Env);


%% Set aircraft initial conditions 
% Note: these are NOT the trim condition targets. If the trim fails to
% coverge, try using different initial conditions. Also note that the trim
% function will overwrite these initial conditions with the trimmed
% conditions.

% Set Initializatons
Sim.Trim.Init.wInit_BL_B_rps = [0; 0; 0]; % Initial Body Frame rotation rates [p; q; r]
Sim.Trim.Init.sInit_BL_rad   = [0; 4 * d2r; 45 * d2r]; % Initial Euler orientation [bank; attitude; heading]; avoid 0 heading, causes large entry in C matrix for psi 

Env.Terr.altGrd_m = 287.0; % Ground Elevation at Jensen Field
Sim.Trim.Init.altAgl_m = 100.0; % Initial Altitude in AGL
Sim.Trim.Init.rInit_BE_D_ddm = [44.72701; -93.077205; Env.Terr.altGrd_m + Sim.Trim.Init.altAgl_m]; % Initial Position of Aircraft [Lat; Long; Alt]

switch lower(Sim.model)
    case 'ultrastick120'
        % Initial Velocity of Aircraft
        Sim.Trim.Init.vInit_BA_B_mps = [23; 0; 0];

        % Throttle initial values
        Sim.Trim.MotorNames = {'throttle_nd'};
        Sim.Trim.In.Motor = struct('Known', 0, 'u', 0.60);
        
        % Control surface initial values
        Sim.Trim.SurfNames = {'elev_rad', 'rud_rad', 'ail_rad', 'flapL_rad', 'flapR_rad'}; % elev, rud, (ailL + ailR), flapL, flapR
        Sim.Trim.In.Surf = struct('Known', [0; 0; 0; 1; 1], 'u', [0; 0; 0; 0; 0]);
        
        % Initial Motor Speed [rad/s]
        Sim.Trim.Init.omegaInit_rps = 800;
                
    case 'ultrastick25e'
        % Initial Velocity of Aircraft
        Sim.Trim.Init.vInit_BA_B_mps = [17; 0; 0];
        
        % Throttle initial values
        Sim.Trim.MotorNames = {'throttle_nd'};
        Sim.Trim.In.Motor = struct('Known', 0, 'u', 0.60, 'Min', 0, 'Max', 1.0);
        
        % Control surface initial values
        Sim.Trim.SurfNames = {'elev_rad', 'rud_rad', 'ail_rad', 'flapL_rad', 'flapR_rad'}; % elev, rud, (ailL + ailR), flapL, flapR
        Sim.Trim.In.Surf = struct('Known', [0; 0; 0; 1; 1], 'u', [0; 0; 0; 0; 0]*d2r, 'Min', [-30; -30; -30; -30; -30]*d2r, 'Max', [30; 30; 30; 30; 30]*d2r);
        
        % Initial Motor Speed [rad/s]
        Sim.Trim.Init.omegaInit_rps = 800;
        
end


%% Trim aircraft to a specific flight condition
% Define the Output specifications - Steady-Level
Sim.Trim.Out.vTrue_mps = struct('Known', 1, 'y', Sim.Trim.Init.vInit_BA_B_mps(1));
Sim.Trim.Out.alpha_rad = struct('Known', 0, 'y', Sim.Trim.Init.sInit_BL_rad(2), 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Out.beta_rad = struct('Known', 1, 'y', 0 * d2r, 'Min', -10 * d2r, 'Max', 10 * d2r);
Sim.Trim.Out.gamma_rad = struct('Known', 1, 'y', 0 * d2r, 'Min', -10 * d2r, 'Max', 10 * d2r);

Sim.Trim.Out.phi_rad = struct('Known', 1, 'y', Sim.Trim.Init.sInit_BL_rad(1), 'Min', -90 * d2r, 'Max', 90 * d2r);
Sim.Trim.Out.theta_rad = struct('Known', 0, 'y', Sim.Trim.Init.sInit_BL_rad(2), 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Out.psi_rad = struct('Known', 0, 'y', Sim.Trim.Init.sInit_BL_rad(3), 'Min', Sim.Trim.Init.sInit_BL_rad(3) - 15 * d2r, 'Max', Sim.Trim.Init.sInit_BL_rad(3) + 15 * d2r);

Sim.Trim.Out.p_rps = struct('Known', 0, 'y', 0 * d2r, 'Min', -10 * d2r, 'Max', 10 * d2r);
Sim.Trim.Out.q_rps = Sim.Trim.Out.p_rps;
Sim.Trim.Out.r_rps = Sim.Trim.Out.p_rps;

Sim.Trim.Out.altAgl_m = struct('Known', 0, 'y', Sim.Trim.Init.altAgl_m);

% Define State conditions, generally these are guesses
Sim.Trim.State.wState_BI_B_rps = struct('Known', [0; 0; 0], 'steadystate', [1; 1; 1], 'x', [0; 0; 0]);
Sim.Trim.State.quatState = struct('Known', [0; 0; 0; 0], 'steadystate', [1; 1; 1; 1]);
Sim.Trim.State.vState_BI_B_mps = struct('Known', [0; 0; 0], 'steadystate', [0; 0; 0], 'x', Sim.Trim.Init.vInit_BA_B_mps);
Sim.Trim.State.rState_BI_E_m = struct('Known', [0; 0; 0], 'steadystate', [0; 0; 0], 'x', [0; 0; 0]);

Sim.Trim.State.omegaState_rps = struct('Known', zeros(size(Sim.Trim.Init.omegaInit_rps)), 'steadystate', ones(size(Sim.Trim.Init.omegaInit_rps)), 'x', Sim.Trim.Init.omegaInit_rps);

% Find the trim solution
simModel = 'SimNL';
verbose = 1;
[Sim] = TrimSim(simModel, Sim, verbose);

%%
if 0
    % Save variables to MAT file
    save(fileSave, 'Sim', 'AC');
    
    % Output a message to the screen
    fprintf('\n Simulation Configuration saved as:\t %s\n', fileSave);
end

%% Linearize about the operating point
[linmodel] = LinearizeSim(simModel, Sim);

