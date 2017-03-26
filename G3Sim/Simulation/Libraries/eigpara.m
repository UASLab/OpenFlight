function [wd, T, wn, zeta] = eigpara(lambda)
% function [wd, T, wn, zeta] = eigpara(lambda)
%
% [wd, T, wn, zeta] = eigparam(lambda)
%
% Return the parameters of a complex eigenvalue
% Inputs:
%   lambda = a complex eigenvalue
% Outputs:
%   wd = the damped natural frequency
%   T = the period
%   wn = the natural frequency
%   zeta = the damping
%
% University of Minnesota 
% Aerospace Engineering and Mechanics 
% Copyright 2011 Regents of the University of Minnesota. 
% All rights reserved.
%
% SVN Info: $Id: eigpara.m 284 2011-03-03 15:07:19Z murch $

a = real(lambda);
b = imag(lambda);

wd = abs(b);
T = 2*pi/wd;

wn = (a^2 + b^2)^0.5;
zeta = -a/wn;

end