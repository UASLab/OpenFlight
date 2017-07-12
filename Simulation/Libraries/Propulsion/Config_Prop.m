function [Sim, Prop] = Config_Prop(Sim, Prop)

% Constants
in2m = 0.0254;

%% Propulsion Data
switch lower(Sim.propType)
    case lower('apc_12x6e') % APC 12 x 6E propeller
        % EFlite Power 25, AEM wind tunnel test data Jan 2011
        % Castle Creations ICE Lite 50 used to collect motor data
        
        % Propeller radius %[m]
        Prop.radius_m = 12 / 2 * in2m;
        
        % Coefficient of Thrust, polynomial coefficients, advance ratio input
        Prop.CT = [-0.4314 1.08 -0.896 0.1089 0.0604 ];
        
        % Coefficient of Power, polynomial coefficients, advance ratio input
        Prop.CP = [0.5054 -0.5304 0.0412 0.01664 0.0223];
        
        % Electric motor and propeller combine moment of inertia
        Prop.Jmp_kgm2 = 0.00012991;  % experimental measurement (not updated with Jan 2011 data)
        
    otherwise % Prop not defined
        
end


%% Limits, populate with generic values as placeholder
% Spin Direction
Prop.spinDir_nd = 1; % 1 - Normal, Positive about Body x-axis; -1 - Reversed

