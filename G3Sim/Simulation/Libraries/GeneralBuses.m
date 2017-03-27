                         
%% Initialize RigidStates bus
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ______ _       _     _ _____ _        _            
% | ___ (_)     (_)   | /  ___| |      | |           
% | |_/ /_  __ _ _  __| \ `--.| |_ __ _| |_ ___  ___ 
% |    /| |/ _` | |/ _` |`--. \ __/ _` | __/ _ \/ __|
% | |\ \| | (_| | | (_| /\__/ / || (_| | ||  __/\__ \
% \_| \_|_|\__, |_|\__,_\____/ \__\__,_|\__\___||___/
%           __/ |                                    
%          |___/                                     

% Accels
names = {'Ax_mpss','Ay_mpss','Az_mpss'};
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
assignin('base', 'Accels', BusObject);
clear elems


% EulerDot
names = {'phidot_radps','thetadot_radps','psidot_radps'};
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
assignin('base', 'EulerDot', BusObject);
clear elems


% Euler
names = {'phi_rad','theta_rad','psi_rad'};
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
assignin('base', 'Euler', BusObject);
clear elems


% V_b
names = {'u_mps','v_mps','w_mps'};
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
assignin('base', 'V_b', BusObject);
clear elems


% AngVel
names = {'p_rps','q_rps','r_rps'};
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
assignin('base', 'AngVel', BusObject);
clear elems



% AngAccel
names = {'pdot_rpss','qdot_rpss','rdot_rpss'};
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
assignin('base', 'AngAccel', BusObject);
clear elems

% A_b
names = {'udot_mpss','vdot_mpss','wdot_mpss'};
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
assignin('base', 'A_b', BusObject);
clear elems


% Concatenate all the individual buses
elems(1) = Simulink.BusElement;
elems(1).Name = 'Accels';
elems(1).Dimensions = 1;
elems(1).DataType = 'Bus: Accels';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).SamplingMode = 'Sample based';

elems(2) = Simulink.BusElement;
elems(2).Name = 'EulerDot';
elems(2).Dimensions = 1;
elems(2).DataType = 'Bus: EulerDot';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).SamplingMode = 'Sample based';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Euler';
elems(3).Dimensions = 1;
elems(3).DataType = 'Bus: Euler';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).SamplingMode = 'Sample based';


elems(4) = Simulink.BusElement;
elems(4).Name = 'V_b';
elems(4).Dimensions = 1;
elems(4).DataType = 'Bus: V_b';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).SamplingMode = 'Sample based';


elems(5) = Simulink.BusElement;
elems(5).Name = 'AngVel';
elems(5).Dimensions = 1;
elems(5).DataType = 'Bus: AngVel';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).SamplingMode = 'Sample based';

elems(6) = Simulink.BusElement;
elems(6).Name = 'AngAccel';
elems(6).Dimensions = 1;
elems(6).DataType = 'Bus: AngAccel';
elems(6).SampleTime = -1;
elems(6).Complexity = 'real';
elems(6).SamplingMode = 'Sample based';

elems(7) = Simulink.BusElement;
elems(7).Name = 'A_b';
elems(7).Dimensions = 1;
elems(7).DataType = 'Bus: A_b';
elems(7).SampleTime = -1;
elems(7).Complexity = 'real';
elems(7).SamplingMode = 'Sample based';

elems(8) = Simulink.BusElement;
elems(8).Name = 'DCM';
elems(8).Dimensions = [3,3];
elems(8).DataType = 'double';
elems(8).SampleTime = -1;
elems(8).Complexity = 'real';
elems(8).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'RigidStates', BusObject);
clear elems






%% Initialize AuxVar bus
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   ___             _   _            
%  / _ \           | | | |           
% / /_\ \_   ___  _| | | | __ _ _ __ 
% |  _  | | | \ \/ / | | |/ _` | '__|
% | | | | |_| |>  <\ \_/ / (_| | |   
% \_| |_/\__,_/_/\_\\___/ \__,_|_|   
                                   
                                  
% V_e
names = {'Xdot_mps','Ydot_mps','Zdot_mps'};
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
assignin('base', 'V_e', BusObject);
clear elems

% X_e
names = {'X_mps','Y_mps','Z_mps'};
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
assignin('base', 'X_e', BusObject);
clear elems

% Nav
names = {'GeodeticLatitude_deg','GeodeticLongitude_deg','Altitude_m',...
    'AltAboveMeanSeaLevel_m','ACOnGround','AltAboveGroundLevel_m',...
    'gndtrack_rad','gamma_rad'};
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
assignin('base', 'Nav', BusObject);
clear elems


% InertialAccel
names = {'aXe_mpss','aYe_mpss','aZe_mpss'};
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
assignin('base', 'InertialAccel', BusObject);
clear elems


% WindAxesParams
names = {'Vs_mps','alpha_rad','beta_rad'};
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
assignin('base', 'WindAxesParams', BusObject);
clear elems


% AlphaBetaDot
names = {'alphadot_rps','betadot_rps'};
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
assignin('base', 'AlphaBetaDot', BusObject);
clear elems



elems(1) = Simulink.BusElement;
elems(1).Name = 'V_e';
elems(1).Dimensions = 1;
elems(1).DataType = 'Bus: V_e';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).SamplingMode = 'Sample based';

elems(2) = Simulink.BusElement;
elems(2).Name = 'X_e';
elems(2).Dimensions = 1;
elems(2).DataType = 'Bus: X_e';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).SamplingMode = 'Sample based';

elems(3) = Simulink.BusElement;
elems(3).Name = 'Nav';
elems(3).Dimensions = 1;
elems(3).DataType = 'Bus: Nav';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).SamplingMode = 'Sample based';

elems(4) = Simulink.BusElement;
elems(4).Name = 'InertialAccel';
elems(4).Dimensions = 1;
elems(4).DataType = 'Bus: InertialAccel';
elems(4).SampleTime = -1;
elems(4).Complexity = 'real';
elems(4).SamplingMode = 'Sample based';

elems(5) = Simulink.BusElement;
elems(5).Name = 'WindAxesParams';
elems(5).Dimensions = 1;
elems(5).DataType = 'Bus: WindAxesParams';
elems(5).SampleTime = -1;
elems(5).Complexity = 'real';
elems(5).SamplingMode = 'Sample based';

elems(6) = Simulink.BusElement;
elems(6).Name = 'AlphaBetaDot';
elems(6).Dimensions = 1;
elems(6).DataType = 'Bus: AlphaBetaDot';
elems(6).SampleTime = -1;
elems(6).Complexity = 'real';
elems(6).SamplingMode = 'Sample based';

elems(7) = Simulink.BusElement;
elems(7).Name = 'MachNumber';
elems(7).Dimensions = 1;
elems(7).DataType = 'double';
elems(7).SampleTime = -1;
elems(7).Complexity = 'real';
elems(7).SamplingMode = 'Sample based';

elems(8) = Simulink.BusElement;
elems(8).Name = 'qBar_Pa';
elems(8).Dimensions = 1;
elems(8).DataType = 'double';
elems(8).SampleTime = -1;
elems(8).Complexity = 'real';
elems(8).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'AuxVar', BusObject);
clear elems









%% Initialize EnvData bus
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  _____           _   _            
% |  ___|         | | | |           
% | |__ _ ____   _| | | | __ _ _ __ 
% |  __| '_ \ \ / / | | |/ _` | '__|
% | |__| | | \ V /\ \_/ / (_| | |   
% \____/_| |_|\_/  \___/ \__,_|_|   
                                  
                                  

% WindGust
names = {'ug_mps','vg_mps','wg_mps'};
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
assignin('base', 'WindGust', BusObject);
clear elems

% WindAngVel
names = {'pg_rps','qg_rps','rg_rps'};
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
assignin('base', 'WindAngVel', BusObject);
clear elems


names = {'Temperature_K','SpeedOfSound_mps','Pressure_kPa','Density_kgpm3'};
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

offset = length(names) ;
names = {'Gravity_mpss','MageneticField_nT','SteadyWind_mps'};
for i = offset+1:offset+length(names)
% Create BusElement for each field
elems(i) = Simulink.BusElement;
elems(i).Name = names{i-offset};
elems(i).Dimensions = [1,3];
elems(i).DataType = 'double';
elems(i).SampleTime = -1;
elems(i).Complexity = 'real';
elems(i).SamplingMode = 'Sample based';
end

offset = offset+length(names) ;

elems(offset+1) = Simulink.BusElement;
elems(offset+1).Name = 'WindGust';
elems(offset+1).Dimensions = 1;
elems(offset+1).DataType = 'Bus: WindGust';
elems(offset+1).SampleTime = -1;
elems(offset+1).Complexity = 'real';
elems(offset+1).SamplingMode = 'Sample based';

offset = offset+1 ;

elems(offset+1) = Simulink.BusElement;
elems(offset+1).Name = 'WindAngVel';
elems(offset+1).Dimensions = 1;
elems(offset+1).DataType = 'Bus: WindAngVel';
elems(offset+1).SampleTime = -1;
elems(offset+1).Complexity = 'real';
elems(offset+1).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'EnvData', BusObject);
clear elems





%% Initialize States bus
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  _____ _        _            
% /  ___| |      | |           
% \ `--.| |_ __ _| |_ ___  ___ 
%  `--. \ __/ _` | __/ _ \/ __|
% /\__/ / || (_| | ||  __/\__ \
% \____/ \__\__,_|\__\___||___/
                             
                             



elems(1) = Simulink.BusElement;
elems(1).Name = 'EnvData';
elems(1).Dimensions = 1;
elems(1).DataType = 'Bus: EnvData';
elems(1).SampleTime = -1;
elems(1).Complexity = 'real';
elems(1).SamplingMode = 'Sample based';

elems(2) = Simulink.BusElement;
elems(2).Name = 'AuxVar';
elems(2).Dimensions = 1;
elems(2).DataType = 'Bus: AuxVar';
elems(2).SampleTime = -1;
elems(2).Complexity = 'real';
elems(2).SamplingMode = 'Sample based';

elems(3) = Simulink.BusElement;
elems(3).Name = 'RigidStates';
elems(3).Dimensions = 1;
elems(3).DataType = 'Bus: RigidStates';
elems(3).SampleTime = -1;
elems(3).Complexity = 'real';
elems(3).SamplingMode = 'Sample based';

BusObject = Simulink.Bus;
BusObject.HeaderFile = '';
BusObject.Description = sprintf('');
BusObject.Elements = elems;
assignin('base', 'States', BusObject);
clear elems





