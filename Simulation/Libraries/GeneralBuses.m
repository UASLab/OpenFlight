
%% Initialize BusEom
% Accels
busNames = {'Ax_mpss','Ay_mpss','Az_mpss'};
assignin('base', 'Accels', CreateBus(busNames));

% EulerDot
busNames = {'phidot_radps','thetadot_radps','psidot_radps'};
assignin('base', 'EulerDot', CreateBus(busNames));

% Euler
busNames = {'phi_rad','theta_rad','psi_rad'};
assignin('base', 'Euler', CreateBus(busNames));

% V_b
busNames = {'u_mps','v_mps','w_mps'};
assignin('base', 'V_b', CreateBus(busNames));

% AngVel
busNames = {'p_rps','q_rps','r_rps'};
assignin('base', 'AngVel', CreateBus(busNames));

% AngAccel
busNames = {'pdot_rpss','qdot_rpss','rdot_rpss'};
assignin('base', 'AngAccel', CreateBus(busNames));

% A_b
busNames = {'udot_mpss','vdot_mpss','wdot_mpss'};
assignin('base', 'A_b', CreateBus(busNames));


% BusEom
busNames = {'Accels', 'EulerDot', 'Euler', 'V_b', 'AngVel', 'AngAccel', 'A_b', 'DCM'};
busDataType = {'Bus: Accels', 'Bus: EulerDot', 'Bus: Euler', 'Bus: V_b', 'Bus: AngVel', 'Bus: AngAccel', 'Bus: A_b', 'double'};
busDim = {1, 1, 1, 1, 1, 1, 1, [3,3]};
assignin('base', 'BusEom', CreateBus(busNames, busDataType, busDim));


%% Initialize BusAux bus
% V_e
busNames = {'Xdot_mps','Ydot_mps','Zdot_mps'};
assignin('base', 'V_e', CreateBus(busNames));

% X_e
busNames = {'X_mps','Y_mps','Z_mps'};
assignin('base', 'X_e', CreateBus(busNames));

% Nav
busNames = {'GeodeticLatitude_deg','GeodeticLongitude_deg','Altitude_m',...
    'AltAboveMeanSeaLevel_m','ACOnGround','AltAboveGroundLevel_m',...
    'gndtrack_rad','gamma_rad'};
assignin('base', 'Nav', CreateBus(busNames));

% InertialAccel
busNames = {'aXe_mpss','aYe_mpss','aZe_mpss'};
assignin('base', 'InertialAccel', CreateBus(busNames));

% WindAxesParams
busNames = {'Vs_mps','alpha_rad','beta_rad'};
assignin('base', 'WindAxesParams', CreateBus(busNames));


% AlphaBetaDot
busNames = {'alphadot_rps', 'betadot_rps'};
assignin('base', 'AlphaBetaDot', CreateBus(busNames));


% BusAux Bus
busNames =    {'V_e',      'X_e',      'Nav',      'InertialAccel',      'WindAxesParams',      'AlphaBetaDot',      'MachNumber', 'qBar_Pa'};
busDataType = {'Bus: V_e', 'Bus: X_e', 'Bus: Nav', 'Bus: InertialAccel', 'Bus: WindAxesParams', 'Bus: AlphaBetaDot', 'double',     'double'};
assignin('base', 'BusAux', CreateBus(busNames, busDataType));


%% Initialize BusNav bus
% WindGust
busNames = {'ug_mps','vg_mps','wg_mps'};
assignin('base', 'WindGust', CreateBus(busNames));
clear elems

% WindAngVel
busNames = {'pg_rps','qg_rps','rg_rps'};
assignin('base', 'WindAngVel', CreateBus(busNames));
clear elems


% BusNav
busNames = {'Temperature_K', 'SpeedOfSound_mps', 'Pressure_kPa', 'Density_kgpm3', 'Gravity_mpss', 'MageneticField_nT', 'SteadyWind_mps', 'WindGust', 'WindAngVel'};
busDataType = {'double', 'double', 'double', 'double', 'double', 'double', 'double', 'Bus: WindGust', 'Bus: WindAngVel'};
busDim = {1, 1, 1, 1, [1,3], [1,3], [1,3], 1, 1};
assignin('base', 'BusNav', CreateBus(busNames, busDataType, busDim));


%% Initialize States bus
% States
busNames = {'BusNav', 'BusAux', 'BusEom'};
busDataType = {'Bus: BusNav', 'Bus: BusAux', 'Bus: BusEom'};
assignin('base', 'BusStates', CreateBus(busNames, busDataType, busDim));


%% Cleanup
clear busNames busDataType busDim