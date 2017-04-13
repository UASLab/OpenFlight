%% Initialize pilot_cmds bus
busNames = {'dthr_pilot','de_pilot','dr_pilot','da_l_pilot','da_r_pilot','df_l_pilot','df_r_pilot','mode'};
assignin('base', 'PilotCommands', CreateBus(busNames));


%% Initialize Sensors bus
busNames = {'phi_rad','theta_rad','psi_rad','p_rps','q_rps','r_rps','Ax_mpss','Ay_mpss','Az_mpss',...
    'GeodeticLatitude_deg','GeodeticLonggitude_deg','Altitude_m','Xdot_mps','Ydot_mps','Zdot_mps',...
    'Vs_mps','AltitudeAboveGroundLevel_m','alpha_rad','beta_rad','Pd_kPa','Ps_kPa'};

busDim = repmat({1}, size(busNames));
busNames{end+1} = 'MagneticField_nT';
busDim{end+1} = [1,3];

assignin('base', 'Sensors', CreateBus(busNames, [], busDim));


%% Initialize Refs bus
busNames = {'lat_cmd_guid','long_cmd_guid'};
assignin('base', 'Refs', CreateBus(busNames));


%% Initialize Commands bus
busNames = {'throttle_nd','elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
assignin('base', 'Commands', CreateBus(busNames));


%% Effectors
% Actuator bus
busNames = {'throttle_nd', 'elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
assignin('base', 'Actuator', CreateBus(busNames));

% CtrlSurf bus
busNames = {'elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
assignin('base', 'CtrlSurf', CreateBus(busNames));


% Effectors bus
busNames = {'Actuator', 'CtrlSurf'};
busDataType = {'Bus: Actuator', 'Bus: CtrlSurf'};
assignin('base', 'Effectors', CreateBus(busNames, busDataType));


%% Cleanup
clear busNames busDataType busDim
