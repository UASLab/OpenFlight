function [Def, IMU] = ParamDef_IMU(Def, IMU)
% Define the IMU Model Parameters

hz2rps = 2*pi;

%
IMU.errEnable = 1;

%% Sensor Models
switch lower(Def.type)
    case 'adis16405' % Analog Devices ADIS16405
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Gyro Transfer Function
        gyroBw_rps = 300 * hz2rps;
        IMU.gyroTF_num = gyroBw_rps;
        IMU.gyroTF_den = [1, gyroBw_rps];
        
        % Accel Transfer Function
        accelBw_rps = 300 * hz2rps;
        IMU.accelTF_num = accelBw_rps;
        IMU.accelTF_den = [1, accelBw_rps];
        
        % Mag Transfer Function
        magBw_rps = 1540 * hz2rps;
        IMU.magTF_num = magBw_rps;
        IMU.magTF_den = [1, magBw_rps];
        
        % Time delay, measurement to signal
        IMU.timeDelay_s = 1/1000;
        
        % Gyro Error Model Parameters (meas = scf * (true + G * accelTrue) + bias + noise)
        IMU.gyroScf = diag([1.0, 1.0, 1.0]);
        IMU.gyroG = diag([0.0, 0.0, 0.0]); % rad/s / m/s^2
        IMU.gyroBias = 0.0 * ones(length(IMU.gyroScf), 1); % rad/s
        IMU.gyroSigma = 0.000001 * ones(length(IMU.gyroScf), 1); % rad/s
        IMU.gyroSeed = randi([1, intmax('int16')], size(IMU.gyroBias)); % Noise Seed
        
        % Accelerometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.accelScf = diag([1.0, 1.0, 1.0]);
        IMU.accelBias = 0.0 * ones(length(IMU.accelScf), 1); % m/s^2
        IMU.accelSigma = [0.0008; 0.004; 0.004]; % m/s^2
        IMU.accelSeed = randi([1, intmax('int16')], size(IMU.accelBias)); % Noise Seed
                
        % Magnetometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.magScf = diag([1.0, 1.0, 1.0]);
        IMU.magBias = 0.0 * ones(length(IMU.accelScf), 1); % nT
        IMU.magSigma = [150; 150; 80000]; % nT
        IMU.magSeed = randi([1, intmax('int16')], size(IMU.magBias)); % Noise Seed
        
    otherwise
        
end

%% Bus Defintion
switch Def.VarSel
    case 1
        Def.elemNames = {'p_rps', 'q_rps', 'r_rps', 'ax_mpss', 'ay_mpss', 'az_mpss', 'hx_nT', 'hy_nT', 'hz_nT'};
    otherwise
end

