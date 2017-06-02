function [GPS] = ParamDef_GPS(type, GPS)
% Define the GPS Error Model Parameters

hz2rps = 2*pi;

GPS.errEnable = 1;

switch lower(type)
    case 'ublox_m8n' % UBlox M8N (FIXME - Check all values!!)
        
        % Create Transfer Functions for the response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % GPS Position Transfer Function
        posBw_rps = 20 * hz2rps; % Bandwidth of the GPS Position
        GPS.posTF_num = posBw_rps;
        GPS.posTF = [1, posBw_rps];
        
        % GPS Velocity Transfer Function
        velBw_rps = 20 * hz2rps; % Bandwidth of the GPS Velocity
        GPS.velTF_num = velBw_rps;
        GPS.velTF_den = [1, velBw_rps];
       
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

