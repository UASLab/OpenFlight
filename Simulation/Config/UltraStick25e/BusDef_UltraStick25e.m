%% Initialize pilot_cmds bus
busNames = {'dthr_pilot','de_pilot','dr_pilot','da_l_pilot','da_r_pilot','df_l_pilot','df_r_pilot','mode'};
assignin('base', 'PilotCommands', CreateBus(busNames));

%% Initialize Sensors buses
% IMU bus
busNames = {'p_rps','q_rps','r_rps','Ax_mpss','Ay_mpss','Az_mpss'};
assignin('base', 'IMU', CreateBus(busNames));

% GPS bus
busNames = {'GeodeticLatitude_deg','GeodeticLonggitude_deg','Altitude_m','Xdot_mps','Ydot_mps','Zdot_mps'};
assignin('base', 'GPS', CreateBus(busNames));

% Airdata Sensors bus
busNames = {'Vs_mps','AltitudeAboveGroundLevel_m','alpha_rad','beta_rad','Pd_kPa','Ps_kPa'};
assignin('base', 'AirdataSensors', CreateBus(busNames));

% Magnetic Field bus
busNames = {'MagneticFieldX_nT', 'MagneticFieldY_nT', 'MagneticFieldZ_nT'};
assignin('base', 'MagneticField', CreateBus(busNames));

%% Initialize Sensors bus
busNames = {'IMU', 'GPS', 'AirdataSensors', 'MagneticField'};
busDataType = {'Bus: IMU', 'Bus: GPS', 'Bus: AirdataSensors', 'Bus: MagneticField'};
assignin('base', 'Sensors', CreateBus(busNames, busDataType));


%% Initialize Refs bus
busNames = {'lat_cmd_guid','long_cmd_guid'};
assignin('base', 'Refs', CreateBus(busNames));


%% Initialize Commands bus
busNames = {'throttle_nd', 'elevator_rad', 'rudder_rad', 'l_aileron_rad', 'r_aileron_rad', 'l_flap_rad', 'r_flap_rad'};
assignin('base', 'Commands', CreateBus(busNames));


%% Effectors
% Motor bus
busNames = {'throttle_nd'};
assignin('base', 'Motor', CreateBus(busNames));

% Actuator bus
busNames = {'elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
assignin('base', 'Actuator', CreateBus(busNames));

% CtrlSurf bus
busNames = {'elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
assignin('base', 'CtrlSurf', CreateBus(busNames));


% Effectors bus
busNames = {'Motor', 'Actuator', 'CtrlSurf'};
busDataType = {'Bus: Motor', 'Bus: Actuator', 'Bus: CtrlSurf'};
assignin('base', 'Effectors', CreateBus(busNames, busDataType));


%% Cleanup
clear busNames busDataType busDim
