%% SetupNL.m
% Nonlinear Simulation setup

% 
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2017 Regents of the University of Minnesota. 
% All rights reserved.
%

%% Configure Aircraft
Sim.model = 'UltraStick25e';

% Simulation sample time
Sim.timeSample_s = 1/100; % sec

% Sim.MassP.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.MassP.type = 'Flight'; Sim.MassP.model = 'Thor';

% Sim.Aero.type = 'AVL'; % Use the reference model defined by the AVL model
Sim.Aero.type = 'Flight'; % Use aero Model as derived from flight data, use with Thor mass properties

% Aircraft Config
% Effector Variants Selections
Sim.EffSim = 'Eff_UltraStick25e'; % Effector Model
Sim.Motor.VarSel = 'ElecNL1'; % Select Motor Model Variant
Sim.Surf.VarServoSel = 'Lin1st'; % Select Servo Model Variant
Sim.Surf.VarLinkSel = 'Lin'; % Select Linkage Model Variant

% Sub-System Variant Selections
Sim.MassP.VarSel = 'Const'; % Select Mass Property Model Variant
Sim.Aero.VarSel = 'Gen'; % Select Aero Model Variant
Sim.Prop.VarSel = 'CoefPoly1'; % Select Prop Model Variant

% Sensor Variant Selections
Sim.SensSim = 'Sens_UltraStick25e';
Sim.IMU.VarSel = 'LocErr';
Sim.GPS.VarSel = 'LocErr';
Sim.Pitot.VarSel = 'LocErr';


% Define Aircraft Specific Parameters
AC = [];
[Sim, AC] = Param_UltraStick25e(Sim, AC);


%% Define the Core Simulation Parameters, Variants, and Buses
% Equation of Motion Configuration Selection
Sim.Eom.VarSel = 'LocalLevel_Quat'; % Equation of Motion Selection ['LocalLevel', 'LocalLevel_Quat', ...]

% Auxiliary Equation Configuration Selection
Sim.Nav.VarSel = 'Simp'; % Auxiliary Equation Nav Selection
Sim.Flow.VarSel = 'Simp'; % Auxiliary Equation Flow Selection

% Environment Model Configurations Selection
Sim.Atmos.VarSel = 'Const'; % Atmospheric Model Selection ['Const', 'AeroBlock', ...]
Sim.Terr.VarSel = 'Const'; % Terrain Model Selection ['Const', ...]
Sim.Grav.VarSel = 'Const'; % Gravity Model Selection ['Const', 'AeroBlock', ...]
Sim.Mag.VarSel = 'Const'; % Magnetic Model Selection ['Const', 'AeroBlock', ...]

Env.Atmos.windVel_L_mps = [2; 2; 0]; % Wind velocity; North, East, Down

% Configure Core Simulation Models
[Sim, Env] = Config_Core(Sim, Env);

% Configure Aircraft Specific Models
[Sim] = Config_UltraStick25e(Sim);


%% Set aircraft trim conditions
% Constants
d2r = pi/180;

% Set Initial Position
Env.Terr.altGrd_m = 287.0; % Ground Elevation at Jensen Field
Sim.Trim.Init.altAgl_m = 100.0; % Initial Altitude in AGL
Sim.Trim.Init.rInit_BE_D_ddm = [44.72701; -93.077205; Env.Terr.altGrd_m + Sim.Trim.Init.altAgl_m]; % Initial Position of Aircraft [Lat; Long; Alt]

% Initial Velocity of Aircraft
Sim.Trim.Targ.Out.vTrue_mps = struct('y', 17, 'Known', 1);

% Surface and Motor names
Sim.Trim.MotorNames = {'throttle_nd'};
Sim.Trim.SurfNames = Sim.Surf.elemNames;

% Effector Input values, Initial Guesses
Sim.Trim.Targ.In.throttle_nd = struct('u', 0.55, 'Known', 0, 'Min', 0.0, 'Max', 1.0);

Sim.Trim.Targ.In.elev_rad = struct('u', 0, 'Known', 0, 'Min', -25*d2r, 'Max', 25*d2r);
Sim.Trim.Targ.In.rud_rad = struct('u', 0, 'Known', 0, 'Min', -25*d2r, 'Max', 25*d2r);
Sim.Trim.Targ.In.ailL_rad = struct('u', 0, 'Known', 1, 'Min', -25*d2r, 'Max', 25*d2r);
Sim.Trim.Targ.In.ailR_rad = struct('u', 0, 'Known', 1, 'Min', -25*d2r, 'Max', 25*d2r);
Sim.Trim.Targ.In.flapL_rad = struct('u', 0, 'Known', 1, 'Min', -25*d2r, 'Max', 25*d2r);
Sim.Trim.Targ.In.flapR_rad = struct('u', 0, 'Known', 1, 'Min', -25*d2r, 'Max', 25*d2r);

% Effector State guesses
Sim.Trim.Targ.State.omegaState_rps = struct('x', 800, 'Known', 0, 'steadystate', 1);

Sim.Trim.Targ.State.elevStateDefl_rad = struct('x', 0, 'Known', 0, 'steadystate', 1);
Sim.Trim.Targ.State.rudStateDefl_rad = struct('x', 0, 'Known', 0, 'steadystate', 1);
Sim.Trim.Targ.State.ailLStateDefl_rad = struct('x', 0, 'Known', 1, 'steadystate', 1);
Sim.Trim.Targ.State.ailRStateDefl_rad = struct('x', 0, 'Known', 1, 'steadystate', 1);
Sim.Trim.Targ.State.flapLStateDefl_rad = struct('x', 0, 'Known', 1, 'steadystate', 1);
Sim.Trim.Targ.State.flapRStateDefl_rad = struct('x', 0, 'Known', 1, 'steadystate', 1);

% Trim aircraft to a specific flight condition
% Define the Output specifications - Steady-Level
Sim.Trim.Targ.Out.alpha_rad = struct('y', 4 * d2r, 'Known', 0, 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Targ.Out.beta_rad = struct('y', 0 * d2r, 'Known', 1, 'Min', -10 * d2r, 'Max', 10 * d2r);

Sim.Trim.Targ.Out.phi_rad = struct('y', 0 * d2r, 'Known', 1, 'Min', -90 * d2r, 'Max', 90 * d2r);
Sim.Trim.Targ.Out.theta_rad = struct('y', 4 * d2r, 'Known', 0, 'Min', -10 * d2r, 'Max', 20 * d2r);
Sim.Trim.Targ.Out.psi_rad = struct('y', 155 * d2r, 'Known', 1, 'Min', (155 - 15) * d2r, 'Max', (155 + 15) * d2r);

Sim.Trim.Targ.Out.p_rps = struct('y', 0 * d2r, 'Known', 1, 'Min', -1 * d2r, 'Max', 1 * d2r);
Sim.Trim.Targ.Out.q_rps = Sim.Trim.Targ.Out.p_rps;
Sim.Trim.Targ.Out.r_rps = Sim.Trim.Targ.Out.p_rps;

Sim.Trim.Targ.Out.altAgl_m = struct('y', Sim.Trim.Init.altAgl_m, 'Known', 0, 'Min', Sim.Trim.Init.altAgl_m - 10, 'Max', Sim.Trim.Init.altAgl_m + 10);
Sim.Trim.Targ.Out.gamma_rad = struct('y', 0 * d2r, 'Known', 1, 'Min', -10 * d2r, 'Max', 10 * d2r);

% Define State conditions, generally these are initial guesses
Sim.Trim.Targ.State.wState_BI_B_rps = struct('x', [0; 0; 0], 'Known', [1; 1; 1], 'steadystate', [1; 1; 1]);
Sim.Trim.Targ.State.quatState_BL_nd = struct('x', [0.25; 0; 0; 1], 'Known', [0; 0; 0; 0], 'steadystate', [1; 1; 1; 1]);
% Sim.Trim.Targ.State.sState_BL_rad = struct('x', [Sim.Trim.Targ.Out.phi_rad.y; Sim.Trim.Targ.Out.theta_rad.y; Sim.Trim.Targ.Out.psi_rad.y], 'Known', [0; 0; 0], 'steadystate', [1; 1; 1]);
Sim.Trim.Targ.State.vState_BI_B_mps = struct('x', [Sim.Trim.Targ.Out.vTrue_mps.y; 0; 0], 'Known', [0; 0; 0], 'steadystate', [1; 1; 1]);
Sim.Trim.Targ.State.rState_BI_L_m = struct('x', [0; 0; 0], 'Known', [1; 1; 1], 'steadystate', [0; 0; 1]);


% Transfer the Initial State Guesses to the Init Structure, these will be overwritten by TrimSim, but these are the mechanism the Sim actually uses
% Initialize Equations of Motion
Sim.Trim.Init.wState_BI_B_rps = Sim.Trim.Targ.State.wState_BI_B_rps.x;
Sim.Trim.Init.quatState_BL_nd = Sim.Trim.Targ.State.quatState_BL_nd.x;
% Sim.Trim.Init.sState_BL_rad = Sim.Trim.Targ.State.sState_BL_rad.x;
Sim.Trim.Init.vState_BI_B_mps = Sim.Trim.Targ.State.vState_BI_B_mps.x;
Sim.Trim.Init.rState_BI_L_m = Sim.Trim.Targ.State.rState_BI_L_m.x;

% Initialize Motors
Sim.Trim.Init.throttleState_nd = 0 * Sim.Trim.Targ.In.throttle_nd.u;
Sim.Trim.Init.omegaState_rps = Sim.Trim.Targ.State.omegaState_rps.x;

% Initialize Surfaces
Sim.Trim.Init.elevStateDefl_rad = Sim.Trim.Targ.State.elevStateDefl_rad.x;
Sim.Trim.Init.rudStateDefl_rad = Sim.Trim.Targ.State.rudStateDefl_rad.x;
Sim.Trim.Init.ailLStateDefl_rad = Sim.Trim.Targ.State.ailLStateDefl_rad.x;
Sim.Trim.Init.ailRStateDefl_rad = Sim.Trim.Targ.State.ailRStateDefl_rad.x;
Sim.Trim.Init.flapLStateDefl_rad = Sim.Trim.Targ.State.flapLStateDefl_rad.x;
Sim.Trim.Init.flapRStateDefl_rad = Sim.Trim.Targ.State.flapRStateDefl_rad.x;

% Initialize Core Bus, required due to using Memory delays to resolve algebraic loops
Sim.Trim.Init.alphaState_rad = Sim.Trim.Targ.Out.alpha_rad.y; % FIXIT
Sim.Trim.Init.betaState_rad = Sim.Trim.Targ.Out.beta_rad.y; % FIXIT

Sim.Trim.Init.alphaDotState_rps = 0; % FIXIT
Sim.Trim.Init.betaDotState_rps = 0; % FIXIT

Sim.Trim.Init.vTrueState_mps = Sim.Trim.Targ.Out.vTrue_mps.y; % FIXIT

%% Find the trim solution
simModel = 'SimNL_Subsystems';
% simModel = 'SimNL';
verbose = 1;

% Clear the values of the Simulation Inputs, The trim algorithm will solve for these
Sim.Trim.In.throttle_nd = 0 * Sim.Trim.Targ.In.throttle_nd.u;
Sim.Trim.In.elev_rad = 0 * Sim.Trim.Targ.In.elev_rad.u;
Sim.Trim.In.rud_rad = 0 * Sim.Trim.Targ.In.rud_rad.u;
Sim.Trim.In.ailL_rad = 0 * Sim.Trim.Targ.In.ailL_rad.u;
Sim.Trim.In.ailR_rad = 0 * Sim.Trim.Targ.In.ailR_rad.u;
Sim.Trim.In.flapL_rad = 0 * Sim.Trim.Targ.In.flapL_rad.u;
Sim.Trim.In.flapR_rad = 0 * Sim.Trim.Targ.In.flapR_rad.u;

% Run the Trim algorithm
[Sim.Trim] = TrimSim(simModel, Sim.Trim, verbose);

%%
if 0
    % Save variables to MAT file
    save(fileSave, 'Sim', 'AC');
    
    % Output a message to the screen
    fprintf('\n Simulation Configuration saved as:\t %s\n', fileSave);
end

%% Linearize about the operating point
[sysModel, sys] = LinearizeSim(simModel, Sim);

return;

%% Compare Linear and Non-linear Simulation
inSigName = 'elev_rad';
outSigName = 'q_rps';

indxInSig = find(strcmp(sysModel.InputName, inSigName));
indxOutSig = find(strcmp(sysModel.OutputName, outSigName));

[numOut, numIn] = size(sysModel);
numState = length(sysModel.StateName);

[uSqr, t_s] = gensig('square', 3, 10, 0.01);
u = zeros(numIn, length(t_s));
u(indxInSig, :) = 1*d2r * uSqr - 0.5*d2r;

[y,t,x] = lsim(sysModel, u, t_s);


% Prepare Non-linear Simulation
u0 = [Sim.Trim.In.throttle_nd, Sim.Trim.In.elev_rad, Sim.Trim.In.rud_rad, Sim.Trim.In.ailL_rad, Sim.Trim.In.ailR_rad, Sim.Trim.In.flapL_rad, Sim.Trim.In.flapR_rad];

simIn = [t_s, u' + repmat(u0, length(t_s), 1)];

paramNameValStruct.SimulationMode    = 'normal';
paramNameValStruct.AbsTol            = '1e-5';
paramNameValStruct.LoadExternalInput = 'on';
paramNameValStruct.ExternalInput     = 'simIn';
paramNameValStruct.SaveState         = 'on';
paramNameValStruct.StateSaveName     = 'simState';
paramNameValStruct.SaveOutput        = 'on';
paramNameValStruct.OutputSaveName    = 'simOut';
paramNameValStruct.SignalLogging     = 'on';
paramNameValStruct.SignalLoggingName = 'simLog';
paramNameValStruct.SaveFormat        = 'Dataset';
paramNameValStruct.CaptureErrors     = 'on';

% Run NL Sim
simRun = sim(simModel, paramNameValStruct);
simOutData = simRun.get('simOut');

%%
% Plot
figure;
subplot(2,1,1);
plot(t_s, simIn(:, indxInSig+1), t_s, y(:, indxOutSig)); grid on;
title('Linear Model Response'); legend({inSigName, outSigName}, 'Interpreter', 'none');
subplot(2,1,2);
plot(t_s, simIn(:, indxInSig+1)); hold on; plot(simOutData.getElement(indxOutSig).Values); grid on;
title('Non-Linear Model Response'); legend({inSigName, simOutData.getElement(indxOutSig).PropagatedName}, 'Interpreter', 'none');


