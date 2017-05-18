function [GPS] = ParamDef_GPS(GPS)
% Define the GPS Error Model Parameters

hz2rps = 2*pi;

GPS.errEnable = 1;

switch lower(GPS.type)
    case 'ublox_m8n' % UBlox M8N (FIXME - Check all values!!)
        
        % Create Transfer Functions for the transducer response
        posBand_rps = 20 * hz2rps; % Bandwidth of the GPS Position
        velBand_rps = 20 * hz2rps; % Bandwidth of the GPS Velocity
        
        GPS.posTF = tf([posBand_rps], [1, posBand_rps]);
        GPS.velTF = tf([velBand_rps], [1, velBand_rps]);
       
        % Time delay, measurement to signal
        GPS.timeDelay_s = 0.300;
        
        % GPS Error Model Parameters (meas = scf * true + bias + noise)        
        GPS.posScf = diag([1.0, 1.0, 1.0]); 
        GPS.posBias = 0.0 * ones(length(GPS.posScf)); % deg
        GPS.posSigma = [0.000001; 0.000001; 1]; % deg
        GPS.posSeed = randi([1, intmax('int16')], size(GPS.posBias)); % Noise Seed
        
        % GPS Velocity Error Model Parameters (meas = scf * true + bias + noise)
        GPS.velScf = diag([1.0, 1.0, 1.0]);
        GPS.velBias =  0.0 * ones(length(GPS.velScf)); % m/s
        GPS.velSigma = 0.1 * ones(length(GPS.velScf)); % m/s
        GPS.velSeed = randi([1, intmax('int16')], size(GPS.velBias)); % Noise Seed
        
    otherwise
        
end

