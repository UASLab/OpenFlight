function MassP = Config_UltraStick120_MassP(Sim, T_S2SB)


% Load the Reference Mass Properties
switch lower(Sim.type)
    case {'flight', 'old'}
        MassP = US120_flight_v1(Sim); % Test derived mass properties
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

function MassP = US120_flight_v1(MassP)
% Gross aircraft mass [kg]
switch lower(MassP.model)
    case 'faser'
        MassP.massRef_kg  = 7.411; % AMM 10/29/11
    case 'mjolnir'
        MassP.massRef_kg  = 7.500; % Mjolnir Jan2018
end

% CG location [x y z], [m]
MassP.rCGRef_S_m = [0.315; 0; 0.072];

% Refernece Moments of Inertia [kg*m^2]
MassP.IxxRef_B_kgm2 = 0.8568; % 10/29/11
MassP.IyyRef_B_kgm2 = 1.0095; % 10/29/11
MassP.IzzRef_B_kgm2 = 1.7005; % 10/29/11

MassP.IxyRef_B_kgm2 = 0.0;
MassP.IxzRef_B_kgm2 = -0.759258051/4; % reduced to match flight data AMM 9/14/11
MassP.IyzRef_B_kgm2 = 0.0;

MassP.IRef_B_kgm2 = [MassP.IxxRef_B_kgm2, -MassP.IxyRef_B_kgm2, -MassP.IxzRef_B_kgm2;
    -MassP.IxyRef_B_kgm2, MassP.IyyRef_B_kgm2, -MassP.IyzRef_B_kgm2;
    -MassP.IxzRef_B_kgm2, -MassP.IyzRef_B_kgm2, MassP.IzzRef_B_kgm2];
end
