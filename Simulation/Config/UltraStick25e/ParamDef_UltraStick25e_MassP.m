function MassP = ParamDef_UltraStick25e_MassP(MassP, T_S2SB)

% Load the Reference Mass Properties
switch lower(MassP.type)
    case {'avl'}
        MassP = US25e_avl_v1();
    case {'flight', 'old'}
        MassP = US25e_flight_v1(MassP.model); % Established Aero PID derived from flight data with Thor using Goldy 1.
    otherwise
        
end

% Compute the Specific Mass Properties
% Current Mass
if ~isfield(MassP, 'mass_kg')
    MassP.mass_kg = MassP.massRef_kg;
end

% Current CG location
if ~isfield(MassP, 'rCG_S_m')
    MassP.rCG_S_m = MassP.rCGRef_S_m;
end
MassP.rCG_SB_m = T_S2SB * MassP.rCG_S_m;

% Current Aircraft Inertia, B-frame
MassP.rCGRef_SB_m = T_S2SB * MassP.rCGRef_S_m;
MassP.rCGRef_B_m = MassP.rCG_SB_m - MassP.rCGRef_SB_m; % CG is origin of B frame, pos vector from CG to Ref frame
MassP.I_B_kgm2 = ...
    MassP.IRef_B_kgm2 + MassP.mass_kg * (dot(-MassP.rCGRef_B_m, -MassP.rCGRef_B_m)*eye(3) - (-MassP.rCGRef_B_m)*(-MassP.rCGRef_B_m)'); % I_CG = I_Ref + m(dot(r, r)*I + (r*r'), where r is from Ref to CG

end

function MassP = US25e_flight_v1(model)
% Gross aircraft mass [kg]
switch lower(model)
    case 'loki'
        MassP.massRef_kg  = 1.9; % Loki
    case 'thor'
        MassP.massRef_kg  = 1.959; % Thor
    case 'frigg'
        MassP.massRef_kg  = 1.865; % Frigg
end

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.222; 0; 0.046];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = 0.07151;
MassP.IyyRef_B_kgm2 = 0.08636;
MassP.IzzRef_B_kgm2 = 0.15364;

MassP.IxyRef_B_kgm2 = 0.0;
MassP.IxzRef_B_kgm2 = 0.014;
MassP.IyzRef_B_kgm2 = 0.0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end


function MassP = US25e_avl_v1()
% Gross aircraft mass [kg]
MassP.massRef_kg = 1.793; % AVL Model

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.222417132; 0.0; 0.027170888];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = 0.0437912;
MassP.IyyRef_B_kgm2 = 0.08381;
MassP.IzzRef_B_kgm2 = 0.119344;

MassP.IxyRef_B_kgm2 = 0.0;
MassP.IxzRef_B_kgm2 = -0.000241577;
MassP.IyzRef_B_kgm2 = 0.0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end