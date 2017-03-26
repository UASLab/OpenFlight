%% Initialize pilot_cmds bus
names = {'dthr_pilot','de_pilot','dr_pilot','da_l_pilot','da_r_pilot','df_l_pilot','df_r_pilot','mode'};
for i = 1:length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i};
elems(i).Dimensions = 1;
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end
BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'PilotCommands', BusObject);
clear elems



%% Initialize Sensors bus
names = {'phi_rad','theta_rad','psi_rad','p_rps','q_rps','r_rps','Ax_mpss','Ay_mpss','Az_mpss',...
    'GeodeticLatitude_deg','GeodeticLonggitude_deg','Altitude_m','Xdot_mps','Ydot_mps','Zdot_mps',...
    'Vs_mps','AltitudeAboveGroundLevel_m','alpha_rad','beta_rad','Pd_kPa','Ps_kPa'};
for i = 1:length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i};
elems(i).Dimensions = 1;
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end

offset = i ;
elems(offset+1) = Simulink.BusElement;
elems(offset+1).Name = 'MagneticField_nT';
elems(offset+1).Dimensions = [1,3];
elems(offset+1).DataType = 'double';
elems(offset+1).SampleTime = -1;
elems(offset+1).Complexity = 'real';
elems(offset+1).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'Sensors', BusObject);
clear elems




%% Initialize Refs bus
names = {'lat_cmd_guid','long_cmd_guid'};
for i = 1:length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i};
elems(i).Dimensions = 1;
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end
BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'Refs', BusObject);
clear elems


%% Initialize Commands bus
names = {'throttle_nd','elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
for i = 1:length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i};
elems(i).Dimensions = 1;
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end
BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'Commands', BusObject);
clear elems




%% Initialize CtrlSurf bus
names = {'elevator_rad','rudder_rad','l_aileron_rad','r_aileron_rad','l_flap_rad','r_flap_rad'};
for i = 1:length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i};
elems(i).Dimensions = 1;
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end
BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'CtrlSurf', BusObject);
clear elems


%% Initialize Actuators bus
elems(1) = Simulink.BusElement;
elems(1).Name = 'throttle_nd';
elems(1).Dimensions = 1;
elems(1).DataType = 'double';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).SamplingMode = 'Sample based';


elems(2) = Simulink.BusElement;
elems(2).Name = 'CtrlSurf';
elems(2).Dimensions = 1;
elems(2).DataType = 'Bus: CtrlSurf';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'Actuators', BusObject);
clear elems


