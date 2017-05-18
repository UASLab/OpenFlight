function [IMU] = ParamDef_IMU(IMU)
% Define the IMU Model Parameters

hz2rps = 2*pi;

%
IMU.errEnable = 1;

switch lower(IMU.type)
    case 'adis16405' % Analog Devices ADIS16405
        % Create Transfer Functions for the transducer response
        gyroBand_rps = 300 * hz2rps; % Bandwidth of the Gyro
        accelBand_rps = 300 * hz2rps; % Bandwidth of the Accel
        magBand_rps = 1540 * hz2rps; % Bandwidth of the Accel
        
        IMU.gyroTF = tf([gyroBand_rps], [1, gyroBand_rps]);
        IMU.accelTF = tf([accelBand_rps], [1, accelBand_rps]);
        IMU.magTF = tf([magBand_rps], [1, magBand_rps]);
        
        % Time delay, measurement to signal
        IMU.timeDelay_s = 1/1000;
        
        % Gyro Error Model Parameters (meas = scf * (true + G * accelTrue) + bias + noise)
        IMU.gyroScf = diag([1.0, 1.0, 1.0]);
        IMU.gyroG = diag([0.0, 0.0, 0.0]); % rad/s / m/s^2
        IMU.gyroBias = 0.0 * ones(length(IMU.gyroScf)); % rad/s
        IMU.gyroSigma = 0.000001 * ones(length(IMU.gyroScf)); % rad/s
        IMU.gyroSeed = randi([1, intmax('int16')], size(IMU.gyroBias)); % Noise Seed
        
        % Accelerometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.accelScf = diag([1.0, 1.0, 1.0]);
        IMU.accelBias = 0.0 * ones(length(IMU.accelScf)); % m/s^2
        IMU.accelSigma = [0.0008; 0.004; 0.004]; % m/s^2
        IMU.accelSeed = randi([1, intmax('int16')], size(IMU.accelBias)); % Noise Seed
                
        % Magnetometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.magScf = diag([1.0, 1.0, 1.0]);
        IMU.magBias = 0.0 * ones(length(IMU.accelScf)); % nT
        IMU.magSigma = [150; 150; 80000]; % nT
        IMU.magSeed = randi([1, intmax('int16')], size(IMU.magBias)); % Noise Seed
        
    otherwise
        
end

