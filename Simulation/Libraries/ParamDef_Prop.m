function [Def, Prop] = ParamDef_Prop(Def, Prop)

% Constants
in2m = 0.0254;

%% Propulsion Data
switch lower(Def.motorType)
    case lower({'E-flite Power25', 'Power25'}) % EFlite Power 25 motor
        switch lower(Def.propType)                
            case lower('apc_12x6e') % APC 12 x 6E propeller
                % EFlite Power 25, AEM wind tunnel test data Jan 2011
                % Castle Creations ICE Lite 50 used to collect motor data
                
                % Propeller radius %[m]
                Prop.radius_m = 12 / 2 * in2m;
                
                % Coefficient of Thrust, polynomial coefficients, advance ratio input
                Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ];
                
                % Coefficient of Power, polynomial coefficients, advance ratio input
                Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223];
                
                % Power, polynomial coefficients, throttle input
                Prop.power_w = [174.46 70.135 -4.39];
                
                % Electric motor and propeller combine moment of inertia
                Prop.Jmp_kgm2 = 0.00012991;  % experimental measurement (not updated with Jan 2011 data)
                
            otherwise % Prop not defined
                
        end
        
    otherwise % Motor not defined
        
end


%% Limits, populate with generic values as placeholder
% Power limits
Prop.powerPosLim_w = Inf;
Prop.powerNegLim_w = 0;

% Rotation rate limits
Prop.omegaPosLim_rps = Inf;
Prop.omegaNegLim_rps = 1; % FIXIT - should be -Inf, need to add divide by zero protection to block diagrams

% Throttle command limits
Prop.throtPosLim_nd = 1;  % [nd]
Prop.throtNegLim_nd = 0; % [nd]
