function Prop = ParamDef_UltraStick25e_Prop(Prop, T_S2SB)

% Constants
in2m = 0.0254;
rpm2rps = 2*pi/60;

% Propulsion force application point (usually propeller hub) [x y z]
Prop.rProp_S_m = [-0.075; 0; 0]; % [m] Propeller in front of reference point
Prop.rProp_SB_m = T_S2SB * Prop.rProp_S_m;

% Thrust alignment orientation (Body to Prop rotations 3-2-1), radians
Prop.sProp_B_rad = [0, 0, -3] * pi/180; % FIXME - Thrust line is slightly up and slightly right of Body X


%% Limits
% Throttle limits
Prop.ThrottleOutputLimit.Upper = 400;
Prop.ThrottleOutputLimit.Lower = 0;

% Rotation rate limits
Prop.OmegaSaturation.Upper = 12000 * rpm2rps;
Prop.OmegaSaturation.Lower = 1;

% Throttle command limits
Prop.throttle.PosLim = 1;  % [nd]
Prop.throttle.NegLim = 0; %[nd]
        
%% Prop Data
switch lower(Prop.propType)
    case 'acp_11x8' % APC 11 x 8 propeller data, EFlite Power 25 motor

        % Advance ratio vector
        Prop.J = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1];
        
        % Coefficient of thrust look-up table CT = CT(J)
        Prop.CT = [0.0947 0.1 0.0974 0.088 0.0763 0.0632 0.0461 0.0301 0.00789 -0.0171 -0.0382];
        
        % Coefficient of power look-up table CP = CP(J)
        Prop.CP = [0.0447 0.0476 0.0494 0.05 0.0494 0.0482 0.0424 0.0318 0.0176 0.0047 -0.01];
        
        % Motor_cal data, old data set
        Prop.Throttle = [0 0.05 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.6 0.65 0.7 0.75 0.8 0.85 0.9 0.95 1.0];
        Prop.Power = [0 0.2 0.4 1.3 3.1 6.1 10.4 16.4 24.2 34 45.9 60.1 76.6 95.7 117.3 141.4 168.1 196.7 228 261.4 296.6];
        
    case 'apc_12x6e' % APC 12 x 6E propeller, EFlite Power 25 motor
        % Coefficient of thrust polynomial model
        % AEM wind tunnel test data Jan 2011
        Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ];

        % Coefficient of power polynomial model
        % AEM wind tunnel test data Jan 2011
        Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223];

        % Propeller radius %[m]
        Prop.Radius = 12 / 2 * in2m;

        % Motor polynomial model. Input throttle, output power in watts
        % EFlite Power 25, AEM wind tunnel test data Jan 2011
        % Castle Creations ICE Lite 50 used to collect motor data
        Prop.Power = [174.46 70.135 -4.39];

        % Electric motor and propeller combine moment of inertia
        Prop.Jmp = 0.00012991;  % [kg*m^2] From experimental measurement (not updated with Jan 2011 data)
        
    otherwise
end