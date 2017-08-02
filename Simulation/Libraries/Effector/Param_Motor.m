function [Motor] = Param_Motor(Sim, Motor)

% Constants
rpm2rps = 2*pi / 60;

%% Motor Data
switch lower(Sim.motorType)
    case lower({'E-flite Power25', 'Power25'}) % E-Flite Power 25
                
        % Power, polynomial coefficients, throttle input (Tested with APC 12 X 6E Prop)
        Motor.power_w = [174.46 70.135 -4.39];
        
        % Motor Power limits
        Motor.powerLimPos_w = 400;
        Motor.powerLimNeg_w = 0;
        
        % Motor Rotation rate limits
        Motor.omegaLimPos_rps = 12000 * rpm2rps;
        Motor.omegaLimNeg_rps = 0.1;
        
        % Electric motor inertia
        Motor.Jmp_kgm2 = 0.0;  % FIXIT - Need Value
        
    case lower({'arco'}) % Arco motor
        
        % Power, polynomial coefficients, throttle input (Tested with APC 12 X 6E Prop)
        Motor.power_w = [174.46 70.135 -4.39]*6; % Multiplied by 6 to get peak power of 1440 watts.
        
        % Motor Power limits
        Motor.powerLimPos_w = 1900;
        Motor.powerLimNeg_w = 0;
        
        % Motor Rotation rate limits
        Motor.omegaLimPos_rps = 15000 * rpm2rps;
        Motor.omegaLimNeg_rps = 0.1;
        
        % Electric motor inertia
        Motor.Jmp_kgm2 = 0.0;  % FIXIT - Need Value
        
    otherwise % Motor not defined
        
end


%% Limits, populate with generic values as placeholder
% Motor Throttle command limits
Motor.throtLimPos_nd = 1;
Motor.throtLimNeg_nd = 0;


