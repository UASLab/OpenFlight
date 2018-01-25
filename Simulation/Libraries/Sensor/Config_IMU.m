function [Sim, IMU] = Config_IMU(Sim, IMU)
% Define the IMU Model Parameters

hz2rps = 2*pi;

%
IMU.errEnable = 1;

%% Sensor Models
switch lower(Sim.type)
    case 'adis16405' % Analog Devices ADIS16405
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Gyro Transfer Function
        IMU.gyroBw_rps = 300 * hz2rps;
        IMU.gyroTF_num = IMU.gyroBw_rps;
        IMU.gyroTF_den = [1, IMU.gyroBw_rps];
        
        % Accel Transfer Function
        IMU.accelBw_rps = 300 * hz2rps;
        IMU.accelTF_num = IMU.accelBw_rps;
        IMU.accelTF_den = [1, IMU.accelBw_rps];
        
        % Mag Transfer Function
        IMU.magBw_rps = 1540 * hz2rps;
        IMU.magTF_num = IMU.magBw_rps;
        IMU.magTF_den = [1, IMU.magBw_rps];
        
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
        IMU.accelSeed = randi([1, intmax('int16')], size(IMU.accelScf)); % Noise Seed
                
        % Magnetometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.magScf = diag([1.0, 1.0, 1.0]);
        IMU.magBias = 0.0 * ones(length(IMU.accelScf), 1); % nT
        IMU.magSigma = [150; 150; 80000]; % nT
        IMU.magSeed = randi([1, intmax('int16')], size(IMU.magScf)); % Noise Seed
        
    case 'mpu9250' % MPU9250
        % Create Transfer Functions for the transducer response
        % Keep numerator and denominator seperate for entry into Simulink TF block
        % Gyro Transfer Function
        IMU.gyroBw_rps = 41 * hz2rps;
        IMU.gyroTF_num = IMU.gyroBw_rps;
        IMU.gyroTF_den = [1, IMU.gyroBw_rps];
        
        % Accel Transfer Function
        IMU.accelBw_rps = 41 * hz2rps;
        IMU.accelTF_num = IMU.accelBw_rps;
        IMU.accelTF_den = [1, IMU.accelBw_rps];
        
        % Mag Transfer Function
        IMU.magBw_rps = 41 * hz2rps;
        IMU.magTF_num = IMU.magBw_rps;
        IMU.magTF_den = [1, IMU.magBw_rps];
        
        % Time delay, measurement to signal
        IMU.timeDelay_s = 1/1000;
        
        % Gyro Error Model Parameters (meas = scf * (true + G * accelTrue) + bias + noise)
        IMU.gyroScf = diag([1.0, 1.0, 1.0]);
        IMU.gyroG = diag([0.0, 0.0, 0.0]); % rad/s / m/s^2
        IMU.gyroBias = 0.0 * ones(length(IMU.gyroScf), 1); % rad/s
        IMU.gyroSigma = sqrt(max([0.0000004834, 0.0000004631, 0.0000006518])) * ones(length(IMU.gyroScf), 1); % rad/s (Allen Variance Test Jan2018)
        IMU.gyroSeed = randi([1, intmax('int16')], size(IMU.gyroScf)); % Noise Seed
        
        % Accelerometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.accelScf = diag([1.0, 1.0, 1.0]);
        IMU.accelBias = 0.0 * ones(length(IMU.accelScf), 1); % m/s^2
        IMU.accelSigma = sqrt(max([0.0001057337, 0.0001080684, 0.0002311144])) * ones(length(IMU.accelScf), 1); % m/s^2
        IMU.accelSeed = randi([1, intmax('int16')], size(IMU.accelScf)); % Noise Seed
                
        % Magnetometer Error Model Parameters (meas = scf * true + bias + noise)
        IMU.magScf = diag([1.0, 1.0, 1.0]);
        IMU.magBias = 0.0 * ones(length(IMU.magScf), 1); % nT
        IMU.magSigma = sqrt(max([543.4415936, 472.5697935, 569.1919327])) * ones(length(IMU.magScf), 1); % nT
        IMU.magSeed = randi([1, intmax('int16')], size(IMU.magBias)); % Noise Seed
        
    otherwise
        
end

%% Bus Defintion
Sim.elemNames = {'wX_IMU_rps', 'wY_IMU_rps', 'wZ_IMU_rps', 'aX_IMU_mps2', 'aY_IMU_mps2', 'aZ_IMU_mps2', 'hX_IMU_nT', 'hY_IMU_nT', 'hZ_IMU_nT'};
Sim.BusIMU = CreateBus(Sim.elemNames);

